cmake_minimum_required(VERSION 3.22)
project(OOP5)

set(CMAKE_CXX_STANDARD 11)

add_executable(Part1 part1/Observer.h part1/Subject.h part1/OOP5EventException.h part1/Part1Examples.cpp part1/MyTest.h part1/TestUtils.h)
add_executable(Part2 part2/List.h part2/Utilities.h part2/Part2Examples.cpp part2/CellType.h part2/Direction.h part2/BoardCell.h part2/GameBoard.h part2/MoveVehicle.h part2/RushHour.h)
add_executable(TestLev part2/testCheckWinSolved1.cpp part2/List.h part2/Utilities.h part2/CellType.h part2/Direction.h part2/BoardCell.h part2/GameBoard.h part2/MoveVehicle.h part2/RushHour.h part2/OOP5_Part2_TestHeader.h)
