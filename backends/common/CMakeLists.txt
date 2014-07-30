add_subdirectory(pinout/)
include_directories(include/)
add_library(syscall OBJECT syscall.c)
add_library(error OBJECT error.c)
