cmake_minimum_required(VERSION 3.22)

project(lorenz_system)

add_executable(lorenz src/main.cxx)
target_compile_features(lorenz PRIVATE cxx_std_20)
