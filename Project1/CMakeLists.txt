cmake_minimum_required(VERSION 3.21)
project(DA_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA_Project
        main.cpp
        DeliveryManager/DeliveryManager.cpp
        DeliveryManager/DeliveryManager.h
        DeliveryManager/Van.cpp
        DeliveryManager/Van.h
        DeliveryManager/Order.cpp
        DeliveryManager/Order.h
        Menu/Menu.cpp
        Menu/Menu.h)
