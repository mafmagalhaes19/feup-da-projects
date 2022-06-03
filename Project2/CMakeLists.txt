
cmake_minimum_required(VERSION 3.20)
project(DA_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA_Project
        main.cpp
        TravelAgency/TravelAgency.cpp
        TravelAgency/TravelAgency.h
        TravelAgency/Vehicle.cpp
        TravelAgency/Vehicle.h
        TravelAgency/Local.cpp
        TravelAgency/Local.h
        TravelAgency/Graph.cpp
        TravelAgency/Graph.h
        Menu/Menu.cpp
        Menu/Menu.h
        TravelAgency/maxHeap.h)