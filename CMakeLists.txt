cmake_minimum_required(VERSION 3.15)
project(PokerDice C)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_BUILD_TYPE Debug)

add_executable(PokerDice main.c base_functions.h point_computing.h table_point_sum.h can_must_table.h pyramid.h)