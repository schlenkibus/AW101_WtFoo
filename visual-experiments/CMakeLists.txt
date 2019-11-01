cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(autoencoder)

find_package(Torch REQUIRED)

add_executable(autoencoder src/autoencoder.cpp)
target_link_libraries(autoencoder "${TORCH_LIBRARIES}")
set_property(TARGET autoencoder PROPERTY CXX_STANDARD 11)