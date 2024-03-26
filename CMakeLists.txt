cmake_minimum_required(VERSION 3.5)

project(chad_shell)

add_executable(chadshell chadshell.c builtins.c)

target_link_libraries(chadshell)
