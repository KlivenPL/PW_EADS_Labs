cmake_minimum_required(VERSION 3.15)
project(PW_EADS_Labs)

set(CMAKE_CXX_STANDARD 14)

add_executable(PW_EADS_Labs src/main.cpp include/Ring.h src/RingAddOperationsTests.cpp include/RingAddOperationsTests.h src/RingGetOperationsTests.cpp include/RingGetOperationsTests.h src/RingRemoveOperationsTests.cpp include/RingRemoveOperationsTests.h src/RingOtherOperationsTests.cpp include/RingOtherOperationsTests.h include/Split.h)