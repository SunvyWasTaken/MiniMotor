project(Boids VERSION 1.0)

file(GLOB_RECURSE Sources "*.h" "*.cpp" ".txt")

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

add_executable(${PROJECT_NAME} ${Sources})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})

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
        COMMAND find ${CMAKE_CURRENT_SOURCE_DIR} -type d -name Public
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
    target_include_directories(${PROJECT_NAME} PRIVATE ${DIR})
endforeach()

target_link_libraries(${PROJECT_NAME} PUBLIC
    MiniMotor
    MiniMotor_compiler_flags
)

target_precompile_headers(${PROJECT_NAME} REUSE_FROM MiniMotor)

