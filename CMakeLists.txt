cmake_minimum_required(VERSION 3.11)

project(SnakeGame VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(${PROJECT_NAME} "src/main.cpp")

if(WIN32)
    if(MSVC)
        # Downloaded from "https://github.com/raysan5/raylib/releases"
        # Release version "raylib-5.5_win64_msvc16.zip"
        # Extracted to "C:/raylib_vs"
        set(RAYLIB_ROOT "C:/raylib_vs")

        set(RAYLIB_LIB_PATH "${RAYLIB_ROOT}/lib/raylib.lib")

        if(EXISTS "${RAYLIB_ROOT}")
            message(STATUS "MSVC: Found Raylib Root at ${RAYLIB_ROOT}")
            
            if(EXISTS "${RAYLIB_LIB_PATH}")
                message(STATUS "MSVC: Linking directly to ${RAYLIB_LIB_PATH}")
                include_directories("${RAYLIB_ROOT}/include")
                
                target_link_libraries(${PROJECT_NAME} PRIVATE 
                "${RAYLIB_LIB_PATH}" 
                legacy_stdio_definitions.lib
                winmm gdi32 user32 shell32
                )

                # Required for linker to find the correct entry point for a GUI application
                set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/ENTRY:mainCRTStartup")
            else()
                message(FATAL_ERROR "Could not find library file at: ${RAYLIB_LIB_PATH}. Check if the folder structure matches.")
            endif()
        else()
             message(FATAL_ERROR "Raylib VS directory not found at ${RAYLIB_ROOT}.")
        endif()
    else()
        # GCC/MinGW
        set(RAYLIB_ROOT "C:/raylib/raylib")
        include_directories("${RAYLIB_ROOT}/include")
        link_directories("${RAYLIB_ROOT}/lib")
        target_link_libraries(${PROJECT_NAME} PRIVATE raylib opengl32 gdi32 winmm)
    endif()
    # Prevents a console window from appearing
    set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE ON)

elseif(UNIX)
    find_package(raylib REQUIRED)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
endif()