cmake_minimum_required(VERSION 3.5.1)
project(lab4 C)

set(SRC src/main.c src/int_calculator.c src/float_calculator.c src/stack.c src/float_stack.c)

add_executable(${PROJECT_NAME} ${SRC})

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../modules")
include(common_lab)
