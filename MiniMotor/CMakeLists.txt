project(MiniMotor VERSION 0.1)

configure_file(Config.h.in Config.h)

file(GLOB_RECURSE SOURCES "*.h" "*.cpp" "*.txt")

# Macro to group files in the IDE
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
GroupSources("Sources")


find_package(OpenGL REQUIRED)

if (EMSCRIPTEN)
    find_package(EnTT CONFIG REQUIRED)
    find_package(glad CONFIG REQUIRED)
else()
    find_package(glad CONFIG REQUIRED)
    find_package(EnTT CONFIG REQUIRED)
    find_package(glew CONFIG REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(SFML CONFIG REQUIRED COMPONENTS system window graphics)
    find_package(ImGui-SFML CONFIG REQUIRED)
endif()

add_Library(${PROJECT_NAME} SHARED ${SOURCES})

if(WIN32)
    # Sous Windows, utiliser une commande PowerShell pour trouver les dossiers nommés "Public"
    execute_process(
        COMMAND powershell -Command "Get-ChildItem -Recurse -Directory | Where-Object { $_.Name -eq 'Public' } | ForEach-Object { $_.FullName }"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
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
    if(NOT ${DIR} MATCHES "Sources/ECS/")
        target_include_directories(${PROJECT_NAME} PUBLIC ${DIR})
    endif()
endforeach()

# Permet d'aller chercher les fichiers générés par CMake
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC 
    EnTT::EnTT
)

target_link_libraries(${PROJECT_NAME} PRIVATE
	OpenGL::GL
    imgui::imgui
    glad::glad
    MiniMotor_compiler_flags
)

if(EMSCRIPTEN)
#target_link_libraries(${PROJECT_NAME} PRIVATE
#)
else()
target_link_libraries(${PROJECT_NAME} PRIVATE
    sfml-system sfml-graphics sfml-window ImGui-SFML::ImGui-SFML
    GLEW::GLEW
    glfw
)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <array>
    <atomic>
    <chrono>
    <cmath>
    <functional>
    <intrin.h>
    <iostream>
    <map>
    <memory>
    <string>
    <thread>
    <variant>
    <vector>
    #====================================================
    #Need to be last cause they need the standard library
    #====================================================
    "Sources/Core/Public/CoreMinimal.h"
)

#if($<OR:<$CONFIG:Debug>,$<CONFIG:RelWithDEbInfo>:$<CONFIG>>)
#	target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG)
#	target_compile_options(${PROJECT_NAME} PRIVATE DO_CHECK)
#endif()
