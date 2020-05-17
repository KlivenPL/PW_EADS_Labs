//
// Created by oskar on 16.05.2020.
//

#include "../include/RingRemoveOperationsTests.h"
#include <sstream>

Ring<int, std::string> RingRemoveOperationsTests::GetTestRing() {
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

Ring<int, std::string> RingRemoveOperationsTests::GetTestRing2() {
    Ring<int, std::string> ring;
    ring.PushBack(5, "5");
    ring.PushBack(2, "2");
    ring.PushBack(3, "3");
    ring.PushBack(4, "4");
    ring.PushBack(5, "5");
    ring.PushBack(5, "5");
    ring.PushBack(5, "5");
    ring.PushBack(5, "5");
    ring.PushBack(5, "5");
    ring.PushBack(5, "5");

    return ring;
}

Ring<int, std::string> RingRemoveOperationsTests::GetEmptyTestRing() {
    return Ring<int, std::string>();
}

bool RingRemoveOperationsTests::IntegrityCheck(Ring<int, std::string> &ring) {
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

bool RingRemoveOperationsTests::TestRemove() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.Remove(1, 1);
        return false; // checking if removing non-existing key in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing();
    ring.PushBack(10, "666");

    ring.Remove(1, 1);
    ring.Remove(3, 1);
    ring.Remove(5, 1);
    ring.Remove(7, 1);
    ring.Remove(10, 2);

    if (ring.GetByIndex(0) != "2")
        return false;
    if (ring.GetByIndex(1) != "4")
        return false;
    if (ring.GetByIndex(2) != "6")
        return false;
    if (ring.GetByIndex(3) != "8")
        return false;
    if (ring.GetByIndex(4) != "9")
        return false;
    if (ring.GetByIndex(5) != "10")
        return false;

    try {
        ring.Remove(2,2);
        return false; // checking if removing non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    if (!IntegrityCheck(ring))
        return false;

    return true;
}

bool RingRemoveOperationsTests::TestRemoveAll() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.RemoveAll(1);
        return false; // checking if removingAll non-existing key in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing2();

    ring.RemoveAll(5);

    if (ring.GetByIndex(0) != "2")
        return false;
    if (ring.GetByIndex(1) != "3")
        return false;
    if (ring.GetByIndex(2) != "4")
        return false;

    try {
        ring.RemoveAll(2222);
        return false; // checking if removing non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    if (!IntegrityCheck(ring))
        return false;

    return true;
}

bool RingRemoveOperationsTests::TestRemoveAtIndex() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.RemoveAtIndex(1);
        return false; // checking if removing at non-existing index in empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring = GetTestRing();

    ring.RemoveAtIndex(0);
    ring.RemoveAtIndex(8);
    ring.RemoveAtIndex(3);
    ring.RemoveAtIndex(4);
    ring.RemoveAtIndex(1);
    ring.RemoveAtIndex(4);

    if (ring.GetByIndex(0) != "2")
        return false;
    if (ring.GetByIndex(1) != "4")
        return false;
    if (ring.GetByIndex(2) != "6")
        return false;
    if (ring.GetByIndex(3) != "8")
        return false;

    try {
        ring.RemoveAtIndex(10);
        return false; // checking if removing at non-existing key in non-empty ring is not allowed
    } catch (Ring<int, std::string>::RingException &ex) { }

    if (!IntegrityCheck(ring))
        return false;

    return true;
}

std::string RingRemoveOperationsTests::RunTests() {
    std::stringstream _stringstream;
    _stringstream << "\tTestRemove:" << (TestRemove() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestRemoveAll:" << (TestRemoveAll() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestRemoveAtIndex:" << (TestRemoveAtIndex() ? " success" : " fail") << std::endl;

    return _stringstream.str();
}

