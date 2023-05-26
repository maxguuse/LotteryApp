cmake_minimum_required(VERSION 3.25)
project(LotteryApp)

set(CMAKE_CXX_STANDARD 14)

include_directories(LotteryApp/include)
include_directories(LotteryApp/tools)

add_executable(LotteryApp
        LotteryApp/include/Circulation.hpp
        LotteryApp/include/Ticket.hpp
        LotteryApp/src/Circulation.cpp
        LotteryApp/tools/CirculationType.hpp
        LotteryApp/main.cpp)
