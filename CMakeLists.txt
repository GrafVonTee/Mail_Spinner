cmake_minimum_required(VERSION 3.20)
project(Mail_Spinner C)

set(CMAKE_C_STANDARD 99)

add_executable(Mail_Spinner main.c spin_menu.c spin_menu.h)

find_library(LIST_LIBRARY list libs)
find_library(STACK_LIBRARY stack libs)
find_library(QUEUE_LIBRARY queue libs)

include_directories(includes/general)

target_link_libraries(Mail_Spinner LINK_PUBLIC ${STACK_LIBRARY} ${LIST_LIBRARY} ${QUEUE_LIBRARY})