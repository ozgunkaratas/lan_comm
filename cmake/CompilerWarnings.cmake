# lancomm_set_warnings(<target>) - consistent strict warnings on MSVC and GCC/Clang
function(lancomm_set_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive- /utf-8)
        # Target Windows 10+ so Asio doesn't warn about _WIN32_WINNT
        target_compile_definitions(${target} PRIVATE _WIN32_WINNT=0x0A00 NOMINMAX WIN32_LEAN_AND_MEAN)
    else()
        target_compile_options(${target} PRIVATE
            -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wsign-conversion)
    endif()
endfunction()
