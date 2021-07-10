cmake_minimum_required(VERSION 3.17)
project(philo C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -pthread -g")

add_executable(philo philo.c philo.h helpers.c actions.c time_helpers.c)