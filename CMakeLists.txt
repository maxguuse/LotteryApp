cmake_minimum_required(VERSION 3.25)
project(LotteryApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include_directories(LotteryApp/include)
include_directories(LotteryApp/tools)

add_executable(LotteryApp
        LotteryApp/include/Circulation.hpp
        LotteryApp/include/Ticket.hpp
        LotteryApp/main.cpp LotteryApp/include/TicketNums.hpp)
