cmake_minimum_required(VERSION 3.16)

project(TaskSchedulerProject LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(taskscheduler_lib STATIC
    TaskScheduler.cpp
)

target_include_directories(taskscheduler_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(app
    main.c
)

target_link_libraries(app PRIVATE taskscheduler_lib)