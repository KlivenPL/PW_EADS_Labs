//
// Created by oskar on 17.05.2020.
//

#include <sstream>
#include "../include/RingOtherOperationsTests.h"

Ring<int, std::string> RingOtherOperationsTests::GetTestRing1() {
    Ring<int, std::string> ring;
    ring.PushBack(1, "1a");
    ring.PushBack(2, "2a");
    ring.PushBack(3, "3a");
    ring.PushBack(4, "4a");
    ring.PushBack(5, "5a");

    return ring;
}

Ring<int, std::string> RingOtherOperationsTests::GetTestRing2() {
    Ring<int, std::string> ring;
    ring.PushBack(1, "1b");
    ring.PushBack(2, "2b");
    ring.PushBack(3, "3b");
    ring.PushBack(4, "4b");
    ring.PushBack(5, "5b");

    return ring;
}

Ring<int, std::string> RingOtherOperationsTests::GetTestRing3() {
    Ring<int, std::string> ring;
    ring.PushBack(100, "100a");
    ring.PushBack(100, "100b");
    ring.PushBack(200, "200a");
    ring.PushBack(200, "200b");
    ring.PushBack(300, "300");

    return ring;
}

Ring<int, std::string> RingOtherOperationsTests::GetTestRing4() {
    Ring<int, std::string> ring;
    ring.PushBack(100, "100a");
    ring.PushBack(100, "100b");
    ring.PushBack(200, "200a");
    ring.PushBack(200, "200b");
    ring.PushBack(500, "500");

    return ring;
}

Ring<int, std::string> RingOtherOperationsTests::GetTestRing5() {
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
    ring.PushBack(0, "0");

    return ring;
}

Ring<int, std::string> RingOtherOperationsTests::GetEmptyTestRing() {
    return Ring<int, std::string> ();
}

bool RingOtherOperationsTests::IntegrityCheck(Ring<int, std::string> &ring) {
    int count = 0;
    auto e1 = ring.GetEnumerator(0);
    if (e1->CanMove()) {
        do {
            count++;
            e1->MoveNext();
        } while (!e1->IsAny() && e1->CanMove());
    }

    auto e2 = ring.GetEnumerator(0);
    if (e2->CanMove()) {
        do {
            count--;
            e2->MoveBack();
        } while (!e2->IsAny() && e2->CanMove());
    }

    return count == 0;
}

bool RingOtherOperationsTests::TestGetEnumerator() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto tempEnum = emptyRing.GetEnumerator(0);
        if (tempEnum->CanMove())
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // checking if getting enumerator from empty ring is allowed
    }

    auto ring = GetTestRing1();

    auto enumerator = ring.GetEnumerator(0);

    if (enumerator->GetCurrentKey() != 1 || enumerator->GetCurrentInfo() != "1a" || !enumerator->CanMove())
        return false;

    enumerator->MoveNext();

    if (enumerator->GetCurrentKey() != 2 || enumerator->GetCurrentInfo() != "2a" || !enumerator->CanMove())
        return false;

    enumerator->MoveNext();

    if (enumerator->GetCurrentKey() != 3 || enumerator->GetCurrentInfo() != "3a" || !enumerator->CanMove())
        return false;

    enumerator->MoveNext();

    if (enumerator->GetCurrentKey() != 4 || enumerator->GetCurrentInfo() != "4a" || !enumerator->CanMove())
        return false;

    enumerator->MoveNext();

    if (enumerator->GetCurrentKey() != 5 || enumerator->GetCurrentInfo() != "5a" || !enumerator->CanMove())
        return false;

    // now backwards
    enumerator->MoveBack();

    if (enumerator->GetCurrentKey() != 4 || enumerator->GetCurrentInfo() != "4a" || !enumerator->CanMove())
        return false;

    enumerator->MoveBack();

    if (enumerator->GetCurrentKey() != 3 || enumerator->GetCurrentInfo() != "3a" || !enumerator->CanMove())
        return false;

    enumerator->MoveBack();

    if (enumerator->GetCurrentKey() != 2 || enumerator->GetCurrentInfo() != "2a" || !enumerator->CanMove())
        return false;

    enumerator->MoveBack();

    if (enumerator->GetCurrentKey() != 1 || enumerator->GetCurrentInfo() != "1a" || !enumerator->CanMove())
        return false;

    try {
        enumerator->MoveBack();
        enumerator->MoveBack();
        enumerator->MoveBack();
        enumerator->MoveBack();
        enumerator->MoveBack();
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // checking if moving next on finished ring is allowed
    }

    return true;
}

bool RingOtherOperationsTests::TestCount() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto count = emptyRing.Count();
        if (count != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false;
    }

    auto ring1 = GetTestRing1();

    return ring1.Count() == 5;
}

bool RingOtherOperationsTests::TestEqualOperator() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto testRng = emptyRing;
        if (testRng.Count() != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // setting to empty rings should not throw an error
    }

    auto testRing = GetTestRing1();

    /*if (!IntegrityCheck(testRing))
        return false;*/

    if (testRing.Count() != 5)
        return false;

    if (testRing.GetByIndex(0) != "1a")
        return false;
    if (testRing.GetByIndex(1) != "2a")
        return false;
    if (testRing.GetByIndex(2) != "3a")
        return false;
    if (testRing.GetByIndex(3) != "4a")
        return false;
    if (testRing.GetByIndex(4) != "5a")
        return false;

    auto ring2 = GetTestRing2();
    testRing = ring2;

    /*if (!IntegrityCheck(testRing))
        return false;*/

    if (testRing.Count() != 5)
        return false;

    if (testRing.GetByIndex(0) != "1b")
        return false;
    if (testRing.GetByIndex(1) != "2b")
        return false;
    if (testRing.GetByIndex(2) != "3b")
        return false;
    if (testRing.GetByIndex(3) != "4b")
        return false;
    if (testRing.GetByIndex(4) != "5b")
        return false;

    testRing = testRing;

    /*if (!IntegrityCheck(testRing))
        return false;*/

    if (testRing.Count() != 5)
        return false;

    if (testRing.GetByIndex(0) != "1b")
        return false;
    if (testRing.GetByIndex(1) != "2b")
        return false;
    if (testRing.GetByIndex(2) != "3b")
        return false;
    if (testRing.GetByIndex(3) != "4b")
        return false;
    if (testRing.GetByIndex(4) != "5b")
        return false;

    testRing = emptyRing;

   /* if (!IntegrityCheck(testRing))
        return false;*/

    if (testRing.Count() != 0)
        return false;

    return true;
}

bool RingOtherOperationsTests::TestPlusOperator() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto testSeq = emptyRing + emptyRing;
        if (testSeq.Count() != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // adding to empty rings should not throw an error
    }

    auto *ring1 = new Ring<int, std::string> (GetTestRing1());
    auto *ring2 = new Ring<int, std::string> (GetTestRing2());

    auto *testRing = new Ring<int, std::string>(*ring1 + *ring2);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 10)
        return false;

    if (testRing->GetByIndex(0) != "1a")
        return false;
    if (testRing->GetByIndex(1) != "2a")
        return false;
    if (testRing->GetByIndex(2) != "3a")
        return false;
    if (testRing->GetByIndex(3) != "4a")
        return false;
    if (testRing->GetByIndex(4) != "5a")
        return false;
    if (testRing->GetByIndex(5) != "1b")
        return false;
    if (testRing->GetByIndex(6) != "2b")
        return false;
    if (testRing->GetByIndex(7) != "3b")
        return false;
    if (testRing->GetByIndex(8) != "4b")
        return false;
    if (testRing->GetByIndex(9) != "5b")
        return false;

    testRing = new Ring<int,std::string>(*testRing + *testRing);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 20)
        return false;

    if (testRing->GetByIndex(0) != "1a")
        return false;
    if (testRing->GetByIndex(1) != "2a")
        return false;
    if (testRing->GetByIndex(2) != "3a")
        return false;
    if (testRing->GetByIndex(3) != "4a")
        return false;
    if (testRing->GetByIndex(4) != "5a")
        return false;
    if (testRing->GetByIndex(5) != "1b")
        return false;
    if (testRing->GetByIndex(6) != "2b")
        return false;
    if (testRing->GetByIndex(7) != "3b")
        return false;
    if (testRing->GetByIndex(8) != "4b")
        return false;
    if (testRing->GetByIndex(9) != "5b")
        return false;
    if (testRing->GetByIndex(10) != "1a")
        return false;
    if (testRing->GetByIndex(11) != "2a")
        return false;
    if (testRing->GetByIndex(12) != "3a")
        return false;
    if (testRing->GetByIndex(13) != "4a")
        return false;
    if (testRing->GetByIndex(14) != "5a")
        return false;
    if (testRing->GetByIndex(15) != "1b")
        return false;
    if (testRing->GetByIndex(16) != "2b")
        return false;
    if (testRing->GetByIndex(17) != "3b")
        return false;
    if (testRing->GetByIndex(18) != "4b")
        return false;
    if (testRing->GetByIndex(19) != "5b")
        return false;


    delete testRing;
    delete ring1;
    delete ring2;
    return true;
}

bool RingOtherOperationsTests::TestMinusOperator() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto testSeq = emptyRing - emptyRing;
        if (testSeq.Count() != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // adding to empty rings should not throw an error
    }

    auto *ring1 = new Ring<int, std::string> (GetTestRing1());
    auto *ring2 = new Ring<int, std::string> (GetTestRing2());

    auto *testRing = new Ring<int, std::string>(*ring1 - *ring2);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 0)
        return false;

    testRing = new Ring<int, std::string>(GetTestRing3());
    testRing = new Ring<int, std::string>(*testRing - *ring1);

    if (testRing->GetByIndex(0) != "100a")
        return false;
    if (testRing->GetByIndex(1) != "100b")
        return false;
    if (testRing->GetByIndex(2) != "200a")
        return false;
    if (testRing->GetByIndex(3) != "200b")
        return false;
    if (testRing->GetByIndex(4) != "300")
        return false;

    auto ring3 = GetTestRing3();
    auto ring4 = GetTestRing4();

    testRing = new Ring<int, std::string> (ring3 - ring4);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 1)
        return false;

    if (testRing->GetByIndex(0) != "300")
        return false;

    testRing = new Ring<int, std::string> (ring4 - ring3);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 1)
        return false;

    if (testRing->GetByIndex(0) != "500")
        return false;

    testRing = new Ring<int, std::string> (*ring1 - *ring1);

    if (!IntegrityCheck(*testRing))
        return false;

    if (testRing->Count() != 0)
        return false;

    delete testRing;
    delete ring1;
    delete ring2;
    return true;
}

bool RingOtherOperationsTests::TestReverse() {
    auto emptyRing = GetEmptyTestRing();
    try {
        auto testSeq = emptyRing.Reversed();
        if (testSeq.Count() != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // reversing empty rings should not throw an error
    }

    auto ring1 = GetTestRing1();
    auto reversed = ring1.Reversed();

    if (!IntegrityCheck(reversed))
        return false;

    if (reversed.Count() != 5)
        return false;

    if (reversed.GetByIndex(0) != "5a")
        return false;
    if (reversed.GetByIndex(1) != "4a")
        return false;
    if (reversed.GetByIndex(2) != "3a")
        return false;
    if (reversed.GetByIndex(3) != "2a")
        return false;
    if (reversed.GetByIndex(4) != "1a")
        return false;
    return true;
}

bool RingOtherOperationsTests::TestRotate() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.Rotate(false);
        if (emptyRing.Count() != 0)
            return false;
    } catch (Ring<int, std::string>::RingException &ex) {
        return false; // reversing empty rings should not throw an error
    }

    auto ring1 = GetTestRing1();
    ring1.Rotate(true);
    ring1.Rotate(true);
    ring1.Rotate(true);
    ring1.Rotate(false);
    ring1.Rotate(false);
    ring1.Rotate(false);
    ring1.Rotate(true);

    if (!IntegrityCheck(ring1))
        return false;

    if (ring1.Count() != 5)
        return false;

    if (ring1.GetByIndex(0) != "2a")
        return false;
    if (ring1.GetByIndex(1) != "3a")
        return false;
    if (ring1.GetByIndex(2) != "4a")
        return false;
    if (ring1.GetByIndex(3) != "5a")
        return false;
    if (ring1.GetByIndex(4) != "1a")
        return false;

    return true;
}

bool RingOtherOperationsTests::TestSubring() {
    auto emptyRing = GetEmptyTestRing();
    try {
        emptyRing.Subring(0, 1);
        return false; // subringing empty rings should throw an error
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring1 = GetTestRing1();

    auto subring = ring1.Subring(2,4);

    if (!IntegrityCheck(subring))
        return false;

    if (subring.Count() != 3)
        return false;

    if (subring.GetByIndex(0) != "3a")
        return false;
    if (subring.GetByIndex(1) != "4a")
        return false;
    if (subring.GetByIndex(2) != "5a")
        return false;

    return true;
}

bool RingOtherOperationsTests::TestSplit() {
    auto extMethods = RingExtentionMethods<int, std::string>();
    auto emptyRing = GetEmptyTestRing();
    Ring<int, std::string> resRing1;
    Ring<int, std::string> resRing2;

    try {
        extMethods.Split(emptyRing, 0, 2, true, resRing1, 1, true, resRing2, 1, false);
        return false; // subringing empty rings should throw an error
    } catch (Ring<int, std::string>::RingException &ex) { }

    auto ring1 = GetTestRing5();

    extMethods.Split(ring1, 2, 16, true, resRing1, 3, true, resRing2, 2, false);

    if (!IntegrityCheck(ring1))
        return false;

    if (!IntegrityCheck(resRing1))
        return false;

    if (!IntegrityCheck(resRing2))
        return false;

    if (resRing1.Count() != 10)
        return false;

    if (resRing2.Count() != 6)
        return false;

    if (resRing1.GetByIndex(0) != "3")
        return false;
    if (resRing1.GetByIndex(1) != "4")
        return false;
    if (resRing1.GetByIndex(2) != "5")
        return false;
    if (resRing1.GetByIndex(3) != "8")
        return false;
    if (resRing1.GetByIndex(4) != "9")
        return false;
    if (resRing1.GetByIndex(5) != "0")
        return false;
    if (resRing1.GetByIndex(6) != "3")
        return false;
    if (resRing1.GetByIndex(7) != "4")
        return false;
    if (resRing1.GetByIndex(8) != "5")
        return false;
    if (resRing1.GetByIndex(9) != "8")
        return false;


    if (resRing2.GetByIndex(0) != "6")
        return false;
    if (resRing2.GetByIndex(1) != "7")
        return false;
    if (resRing2.GetByIndex(2) != "6")
        return false;
    if (resRing2.GetByIndex(3) != "2")
        return false;
    if (resRing2.GetByIndex(4) != "1")
        return false;
    if (resRing2.GetByIndex(5) != "7")
        return false;

    return true;
}

std::string RingOtherOperationsTests::RunTests() {
    std::stringstream _stringstream;
    _stringstream << "\tTestGetEnumerator:" << (TestGetEnumerator() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestReverse:" << (TestReverse() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestRotate:" << (TestRotate() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestSubring:" << (TestSubring() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestCount:" << (TestCount() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestEqualOperator:" << (TestEqualOperator() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestPlusOperator:" << (TestPlusOperator() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestMinusOperator:" << (TestMinusOperator() ? " success" : " fail") << std::endl;
    _stringstream << "\tTestSplit:" << (TestSplit() ? " success" : " fail") << std::endl;

    return _stringstream.str();
}

