//
// Created by oskar on 16.05.2020.
//

#include "../include/RingAddOperationsTests.h"
#include <string>
#include <iostream>
#include <sstream>

Ring<int, std::string> RingAddOperationsTests::GetTestRing1() {
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

    return ring;
}

Ring<int, std::string> RingAddOperationsTests::GetEmptyTestRing() {
    return Ring<int, std::string>();
}

bool RingAddOperationsTests::IntegrityCheck(Ring<int, std::string> &ring) {
    int count = 0;
    auto e1 = ring.GetEnumerator(0);
    do {
        count++;
        e1->MoveNext();
    } while(!e1->IsAny());

    auto e2 = ring.GetEnumerator(0);
    do {
        count--;
        e2->MoveBack();
    } while(!e2->IsAny());
    return count == 0;
}

bool RingAddOperationsTests::TestPushFront() {
    auto emptyRing = GetEmptyTestRing();
    emptyRing.PushFront(453, "abc");
    if (emptyRing.GetByIndex(0) != "abc")
        return false;

    auto ring = GetTestRing1();

    ring.PushFront(9999, "9999");
    ring.PushFront(1, "1");
    ring.PushFront(8888, "8888");

    if (ring.GetByIndex(0) != "8888")
        return false;
    if (ring.GetByIndex(1) != "1")
        return false;
    if (ring.GetByIndex(2) != "9999")
        return false;

    if (!IntegrityCheck(ring))
        return false;
    return true;
}

bool RingAddOperationsTests::TestPushBack() {
    auto emptyRing = GetEmptyTestRing();
    emptyRing.PushBack(453, "abc");
    if (emptyRing.GetByIndex(0) != "abc")
        return false;

    auto ring = GetTestRing1();

    ring.PushBack(9999, "9999");
    ring.PushBack(1, "1");
    ring.PushBack(8888, "8888");

    if (ring.GetByIndex(10) != "9999")
        return false;
    if (ring.GetByIndex(11) != "1")
        return false;
    if (ring.GetByIndex(12) != "8888")
        return false;

    if (!IntegrityCheck(ring))
        return false;

    return true;
}

bool RingAddOperationsTests::TestInsertAfter() {
    auto emptyRing = GetEmptyTestRing();
    emptyRing.InsertAfter(453, "abc", 9999, 1);
    if (emptyRing.GetByIndex(0) != "abc")
        return false;

    auto ring = GetTestRing1();

    ring.InsertAfter(100, "2nd", 1, 1);
    ring.InsertAfter(200, "4th", 2, 1);
    ring.InsertAfter(10, "14th", 10, 1);
    ring.InsertAfter(10, "15th", 10, 2);
    ring.InsertAfter(10, "13th", 10, 1);

    if (ring.GetByIndex(1) != "2nd")
        return false;
    if (ring.GetByIndex(3) != "4th")
        return false;
    if (ring.GetByIndex(12) != "13th")
        return false;
    if (ring.GetByIndex(13) != "14th")
        return false;
    if (ring.GetByIndex(14) != "15th")
        return false;


    try {
        ring.InsertAfter(2, "shouldThrowException", 8239, 1);
        return false; // checking if inserting after non existing key if ring not empty is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    if (!IntegrityCheck(ring))
        return false;

    return true;
}

std::string RingAddOperationsTests::RunTests() {
    std::stringstream _stringstream;
    _stringstream << "\tTestPushFront:" << (TestPushFront() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestPushBack:" << (TestPushBack() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestInsertAfter:" << (TestInsertAfter() ? " success" : "fail") << std::endl;

    return _stringstream.str();
}
