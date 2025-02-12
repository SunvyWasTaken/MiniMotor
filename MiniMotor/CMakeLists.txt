project(MiniMotor VERSION 0.1)

file(GLOB_RECURSE Sources "*.h" "*.cpp" "*.txt" "*.vert" "*.frag")

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
find_package(EnTT CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)

add_library(${PROJECT_NAME} SHARED ${Sources})
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
set_target_properties(${PROJECT_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ${BUILD_SHARED_LIBS})


if(WIN32)
    # Sous Windows, utiliser une commande PowerShell pour trouver les dossiers nomm s "Public"
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

# Remplacer les nouvelles lignes par des espaces pour garantir que les chemins sont bien s par s
string(REPLACE "\n" " " PUBLIC_DIRS "${PUBLIC_DIRS}")

# Transformer le r sultat en une liste CMake
separate_arguments(PUBLIC_DIRS)

# Ajouter chaque dossier trouv  dans les includes
foreach(DIR ${PUBLIC_DIRS})
    target_include_directories(${PROJECT_NAME} PUBLIC ${DIR})
endforeach()

# Permet d'aller chercher les fichiers g n r s par CMake
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} PUBLIC
    EnTT::EnTT
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    MiniMotor_compiler_flags
    OpenGL::GL
    glfw
    glad::glad
    glm::glm-header-only
)

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <algorithm>
    <array>
    <atomic>
    <chrono>
    <cmath>
    <cstdint>
    <functional>
    <fstream>
    <sstream>
    <iostream>
    <limits>
    <map>
    <memory>
    <optional>
    <string>
    <thread>
    <variant>
    <vector>

    "Sources/Core/Public/ImportExportDLL.h"
)
