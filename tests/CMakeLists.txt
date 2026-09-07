# Verification Test Suite CMake Configuration

# Header syntax verification tests
add_header_syntax_test("sdkddkver" "${CMAKE_CURRENT_SOURCE_DIR}/../include/sdkddkver.h")
add_header_syntax_test("windef" "${CMAKE_CURRENT_SOURCE_DIR}/../include/windef.h")
add_header_syntax_test("winnt" "${CMAKE_CURRENT_SOURCE_DIR}/../include/winnt.h")
add_header_syntax_test("winerror" "${CMAKE_CURRENT_SOURCE_DIR}/../include/winerror.h")
add_header_syntax_test("winbase" "${CMAKE_CURRENT_SOURCE_DIR}/../include/winbase.h")
add_header_syntax_test("winuser" "${CMAKE_CURRENT_SOURCE_DIR}/../include/winuser.h")
add_header_syntax_test("wingdi" "${CMAKE_CURRENT_SOURCE_DIR}/../include/wingdi.h")
add_header_syntax_test("kfuncs" "${CMAKE_CURRENT_SOURCE_DIR}/../include/kfuncs.h")
add_header_syntax_test("tchar" "${CMAKE_CURRENT_SOURCE_DIR}/../include/tchar.h")
add_header_syntax_test("excpt" "${CMAKE_CURRENT_SOURCE_DIR}/../include/excpt.h")
add_header_syntax_test("windows" "${CMAKE_CURRENT_SOURCE_DIR}/../include/windows.h")
add_header_syntax_test("sipapi" "${CMAKE_CURRENT_SOURCE_DIR}/../include/sipapi.h")
add_header_syntax_test("aygshell" "${CMAKE_CURRENT_SOURCE_DIR}/../include/aygshell.h")
add_header_syntax_test("commctrl" "${CMAKE_CURRENT_SOURCE_DIR}/../include/commctrl.h")
add_header_syntax_test("ws2def" "${CMAKE_CURRENT_SOURCE_DIR}/../include/ws2def.h")
add_header_syntax_test("winsock2" "${CMAKE_CURRENT_SOURCE_DIR}/../include/winsock2.h")

# Application syntax verification tests
add_test(
    NAME "test_fundamental_types"
    COMMAND ${CLANG_EXECUTABLE}
        -target ${WINCE_TARGET_TRIPLE}
        -fshort-wchar
        -I${WINCE_INCLUDE_DIR}
        -D_WIN32_WCE=0x0500
        -DUNICODE -D_UNICODE
        -fsyntax-only
        -x c ${CMAKE_CURRENT_SOURCE_DIR}/test_fundamental_types.c
)

add_test(
    NAME "test_primary_headers"
    COMMAND ${CLANG_EXECUTABLE}
        -target ${WINCE_TARGET_TRIPLE}
        -fshort-wchar
        -I${WINCE_INCLUDE_DIR}
        -D_WIN32_WCE=0x0500
        -DUNICODE -D_UNICODE
        -fsyntax-only
        -x c ${CMAKE_CURRENT_SOURCE_DIR}/test_primary_headers.c
)

add_test(
    NAME "test_additional_headers"
    COMMAND ${CLANG_EXECUTABLE}
        -target ${WINCE_TARGET_TRIPLE}
        -fshort-wchar
        -I${WINCE_INCLUDE_DIR}
        -D_WIN32_WCE=0x0500
        -DUNICODE -D_UNICODE
        -fsyntax-only
        -x c ${CMAKE_CURRENT_SOURCE_DIR}/test_additional_headers.c
)
