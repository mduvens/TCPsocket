cmake_minimum_required(VERSION 3.16.3)

project(ServerTCP)

add_executable(ServerTCP ServerTCP.c helpers/HandleTCP.c helpers/DieWithError.c)