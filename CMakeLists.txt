cmake_minimum_required(VERSION 3.17)
project(philo C)

set(CMAKE_C_STANDARD 99)

add_executable(philo philo.c philo.h helpers.c actions.c)