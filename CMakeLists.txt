cmake_minimum_required(VERSION 3.10)
project(wince-api C CXX)

# Default target triple for ARM WinCE (i.MX28 ARMv5TE)
set(WINCE_TARGET_TRIPLE "armv5te-unknown-wince-pe" CACHE STRING "Target triple for Windows CE Clang cross-compilation")

# Include directory
set(WINCE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Verify clang compiler is available
find_program(CLANG_EXECUTABLE clang DOC "Clang compiler executable")
if(NOT CLANG_EXECUTABLE)
    message(WARNING "Clang executable not found. CTest syntax verification may fail if clang is not in PATH.")
    set(CLANG_EXECUTABLE "clang")
endif()

# Print status configuration
message(STATUS "wince-api include directory: ${WINCE_INCLUDE_DIR}")
message(STATUS "wince-api target triple: ${WINCE_TARGET_TRIPLE}")

# Header syntax verification test macro
function(add_header_syntax_test HEADER_NAME FILE_PATH)
    add_test(
        NAME "syntax_check_${HEADER_NAME}"
        COMMAND ${CLANG_EXECUTABLE}
            -target ${WINCE_TARGET_TRIPLE}
            -I${WINCE_INCLUDE_DIR}
            -D_WIN32_WCE=0x0500
            -DUNICODE -D_UNICODE
            -fsyntax-only
            -x c ${FILE_PATH}
    )
endfunction()

# Enable testing framework
enable_testing()

# Custom target for building / checking all headers
add_custom_target(check-headers
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMENT "Running header syntax verification tests"
)

# Install rules for headers and def files
install(DIRECTORY include/ DESTINATION include)
install(DIRECTORY def/ DESTINATION share/wince-api/def)

add_subdirectory(tests)
