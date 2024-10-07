project(MiniMotor)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo" CACHE STRING "" FORCE)

file(GLOB_RECURSE Sources "*.h" "*.cpp" "*.txt")

if(WIN32)
    # Sous Windows, utiliser une commande PowerShell pour trouver les dossiers nommés "Public"
    execute_process(
        COMMAND powershell -Command "Get-ChildItem -Recurse -Directory | Where-Object { $_.Name -eq 'Public' } | ForEach-Object { $_.FullName }"
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE PUBLIC_DIRS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    # Sous Linux/macOS, utiliser la commande Unix `find`
    execute_process(
        COMMAND find ${CMAKE_SOURCE_DIR} -type d -name Public
        OUTPUT_VARIABLE PUBLIC_DIRS
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
endif()

# Remplacer les nouvelles lignes par des espaces pour garantir que les chemins sont bien séparés
string(REPLACE "\n" " " PUBLIC_DIRS "${PUBLIC_DIRS}")

# Transformer le résultat en une liste CMake
separate_arguments(PUBLIC_DIRS)

# Ajouter chaque dossier trouvé dans les includes
foreach(DIR ${PUBLIC_DIRS})
    include_directories(${DIR})
endforeach()

macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})

        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

# Execute the macro
GroupSources(Sources)

find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
find_package(ImGui-SFML CONFIG REQUIRED)

add_Library(${PROJECT_NAME} SHARED ${Sources})

set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

target_link_libraries(MiniMotor PRIVATE
    sfml-system sfml-graphics sfml-window ImGui-SFML::ImGui-SFML
)

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:Debug>:DEBUG>)
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<CONFIG:RelWithDebInfo>:DO_CHECK>)

target_precompile_headers(MiniMotor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Sources/Core/Public/CoreMinimal.h")

set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)