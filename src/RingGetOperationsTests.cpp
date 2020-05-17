//
// Created by oskar on 16.05.2020.
//

#include "../include/RingGetOperationsTests.h"
#include <sstream>

Ring<int, std::string> RingGetOperationsTests::GetTestRing() {
    Ring<int, std::string> ring;
    ring.PushBack(1, "1");
    ring.PushBack(2, "2");
    ring.PushBack(3, "3");
    ring.PushBack(4, "4");
    ring.PushBack(5, "5");
    ring.PushBack(6, "6");
    ring.PushBack(7, "7");
    ring.PushBack(8, "8");
    ring.PushBack(9, "9");
    ring.PushBack(10, "10");
    ring.PushBack(100, "100");
    ring.PushBack(100, "110");
    ring.PushBack(100, "120");
    ring.PushBack(3, "33");
    ring.PushBack(3, "333");

    return ring;
}

Ring<int, std::string> RingGetOperationsTests::GetEmptyTestRing() {
    return Ring<int, std::string>();
}

bool RingGetOperationsTests::TestGet() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.Get(222, 1);
        return false; // checking if getting non-existing key in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing();

    if (ring.Get(1) != "1")
        return false;
    if (ring.Get(10) != "10")
        return false;
    if (ring.Get(100) != "100")
        return false;
    if (ring.Get(100, 2) != "110")
        return false;
    if (ring.Get(100, 3) != "120")
        return false;
    if (ring.Get(3, 2) != "33")
        return false;
    if (ring.Get(3, 3) != "333")
        return false;

    try {
        ring.Get(3,4);
        return false; // checking if getting non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    return true;
}


bool RingGetOperationsTests::TestGetByIndex() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.GetByIndex(222);
        return false; // checking if getting non-existing index in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing();

    if (ring.GetByIndex(0) != "1")
        return false;
    if (ring.GetByIndex(9) != "10")
        return false;
    if (ring.GetByIndex(11) != "110")
        return false;
    if (ring.GetByIndex(14) != "333")
        return false;

    try {
        ring.GetByIndex(333);
        return false; // checking if getting non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    return true;
}

bool RingGetOperationsTests::TestGetIndex() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.GetIndex(1, 1);
        return false; // checking if getting non-existing index in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing();

    if (ring.GetIndex(1, 1) != 0)
        return false;
    if (ring.GetIndex(10, 1) != 9)
        return false;
    if (ring.GetIndex(100, 1) != 10)
        return false;
    if (ring.GetIndex(100, 2) != 11)
        return false;
    if (ring.GetIndex(100, 3) != 12)
        return false;
    if (ring.GetIndex(3, 2) != 13)
        return false;
    if (ring.GetIndex(3, 3) != 14)
        return false;

    try {
        ring.GetIndex(3, 4);
        return false; // checking if getting non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    return true;
}

std::string RingGetOperationsTests::RunTests() {
    std::stringstream _stringstream;
    _stringstream << "\tTestGet:" << (TestGet() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestGetByIndex:" << (TestGetByIndex() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestGetIndex:" << (TestGetIndex() ? " success" : " fail") << std::endl;

    return _stringstream.str();
}
