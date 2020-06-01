cmake_minimum_required(VERSION 3.15)
project(PW_EADS_Labs)

set(CMAKE_CXX_STANDARD 14)

add_executable(PW_EADS_Labs src/main.cpp include/Dictionary.hh src/DictionaryTests.cpp include/DictionaryTests.h include/IEnumerator.h)

#add_executable(PW_EADS_Labs src/main.cpp include/Dictionary.h)