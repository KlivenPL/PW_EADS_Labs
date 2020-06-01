//
// Created by oskar on 16.05.2020.
//

#include "../include/DictionaryTests.h"
#include <string>
#include <iostream>
#include <sstream>

Dictionary<int, std::string> DictionaryTests::GetTestDictionary1() {
    Dictionary<int, std::string> dictionary;
    dictionary.Insert(1, "1");
    dictionary.Insert(2, "2");
    dictionary.Insert(3, "3");
    dictionary.Insert(4, "4");
    dictionary.Insert(5, "5");
    dictionary.Insert(6, "6");
    dictionary.Insert(7, "7");
    dictionary.Insert(8, "8");
    dictionary.Insert(9, "9");
    dictionary.Insert(10, "10");

    return dictionary;
}

Dictionary<int, std::string> DictionaryTests::GetEmptyTestDictionary() {
    return Dictionary<int, std::string>();
}

Dictionary<int, std::string> DictionaryTests::GetTestDictionary2() {
    Dictionary<int, std::string> dictionary;
    dictionary.Insert(1, "1a");
    dictionary.Insert(2, "2a");
    dictionary.Insert(3, "3a");
    dictionary.Insert(4, "4a");
    dictionary.Insert(5, "5a");

    return dictionary;
}

Dictionary<int, std::string> DictionaryTests::GetTestDictionary3() {
    Dictionary<int, std::string> dictionary;
    dictionary.Insert(1, "1b");
    dictionary.Insert(2, "2b");
    dictionary.Insert(3, "3b");
    dictionary.Insert(4, "4b");
    dictionary.Insert(5, "5b");

    return dictionary;
}

Dictionary<int, std::string> DictionaryTests::GetTestDictionary4() {
    Dictionary<int, std::string> dictionary;
    dictionary.Insert(6, "6");
    dictionary.Insert(7, "7");
    dictionary.Insert(8, "8");
    dictionary.Insert(9, "9");
    dictionary.Insert(10, "10");

    return dictionary;
}

bool DictionaryTests::CheckInOrder(std::string expected, Dictionary<int, std::string> &dictionary) {
    auto result = dictionary.PrintAll(true);
    return expected == result;
}
bool DictionaryTests::TestInsert() {
    auto dict = GetTestDictionary1();

    if (dict.Count() != 10)
        return false;

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", dict))
        return false;

    try {
        dict.Insert(1, "ShouldNotBeAllowed");
        return false;
    } catch (...){}

    return true;
}

bool DictionaryTests::TestContains() {
    auto empty = GetEmptyTestDictionary();

    try {
        empty.Contains(0); // should not throw an error
    } catch (...){
        return false;
    }

    auto dict = GetTestDictionary1();

    if (!dict.Contains(1))
        return false;
    if (!dict.Contains(2))
        return false;
    if (!dict.Contains(3))
        return false;
    if (!dict.Contains(4))
        return false;
    if (!dict.Contains(5))
        return false;
    if (!dict.Contains(6))
        return false;
    if (!dict.Contains(7))
        return false;
    if (!dict.Contains(8))
        return false;
    if (!dict.Contains(9))
        return false;
    if (!dict.Contains(10))
        return false;

    if (dict.Contains(11))
        return false;

    return true;
}

bool DictionaryTests::TestGet() {
    auto empty = GetEmptyTestDictionary();

    try {
        empty.Get(0); // should not be allowed
        return false;
    } catch (...){}

    auto dict = GetTestDictionary1();

    if (dict.Get(1) != "1")
        return false;
    if (dict.Get(2) != "2")
        return false;
    if (dict.Get(3) != "3")
        return false;
    if (dict.Get(4) != "4")
        return false;
    if (dict.Get(5) != "5")
        return false;
    if (dict.Get(6) != "6")
        return false;
    if (dict.Get(7) != "7")
        return false;
    if (dict.Get(8) != "8")
        return false;
    if (dict.Get(9) != "9")
        return false;
    if (dict.Get(10) != "10")
        return false;

    if (dict.Get(1) == "anything else")
        return false;

    try {
        empty.Get(11); // should not be allowed
        return false;
    } catch (...){}

    return true;
}

bool DictionaryTests::TestRemove() {
    auto empty = GetEmptyTestDictionary();

    try {
        empty.Remove(0); // should not be allowed
        return false;
    } catch (...){}

    auto dict = GetTestDictionary1();

    dict.Remove(1);
    dict.Remove(3);
    dict.Remove(7);
    dict.Remove(10);
    dict.Remove(2);

    if (dict.Count() != 5)
        return false;

    if (!CheckInOrder("4, 5, 6, 8, 9", dict))
        return false;

    try {
        empty.Remove(11); // should not be allowed
        return false;
    } catch (...){}

    return true;
}

bool DictionaryTests::TestClear() {
    auto empty = GetEmptyTestDictionary();

    try {
        empty.Clear(); // should not throw an error
    } catch (...){
        return false;
    }

    auto dict = GetTestDictionary1();

    dict.Clear();

   if (!dict.IsEmpty())
       return false;

    return true;
}

bool DictionaryTests::TestEnumerator() {
    auto empty = GetEmptyTestDictionary();

    try {
        auto emptyE = empty.GetEnumerator(); // should not throw an error
        if (emptyE->CanMoveRight())
            return false;
        if (emptyE->CanMoveLeft())
            return false;
    } catch (...){
        return false;
    }

    try {
        auto emptyE = empty.GetEnumerator();
        emptyE->GetCurrentInfo(); // should not be allowed
        return false;
    } catch (...){}

    auto dict = GetTestDictionary1();

    auto e1 = dict.GetEnumerator();

    e1->MoveRight();
    e1->MoveLeft();

    if (e1->GetCurrentKey() != 6)
        return false;

    e1->MoveToKey(4); // move back to root

    if (e1->GetCurrentKey() != 4)
        return false;

    e1->MoveToKey(7); // move to leaf

    if (e1->GetCurrentKey() != 7)
        return false;

    if (e1->CanMoveRight() || e1->CanMoveLeft())
        return false;

    try {
        e1->MoveToKey(11);  // should throw an error
        return false;
    } catch (...){}

    return true;
}

bool DictionaryTests::TestCopy() {
    auto empty = GetEmptyTestDictionary();
    auto result = GetTestDictionary1();
    try {
        empty.Copy(result); // should clear result and leave empty
        if (!result.IsEmpty())
            return false;
    } catch (...){
        return false;
    }

    GetTestDictionary1().Copy(result);

    if (result.Count() != 10)
        return false;

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", result))
        return false;

    return true;
}

bool DictionaryTests::TestEqualOperator() {
    auto empty = GetEmptyTestDictionary();
    auto result = GetTestDictionary1();
    try {
       result = empty;
        if (!result.IsEmpty())
            return false;
    } catch (...){
        return false;
    }

    auto test = GetTestDictionary1();
    result = test;

    if (result.Count() != 10)
        return false;

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", result))
        return false;

    return true;
}

bool DictionaryTests::TestPlusOperator() {
    auto emptyDictionary = GetEmptyTestDictionary();
    try {
        auto testSeq = emptyDictionary + emptyDictionary;
        if (testSeq.Count() != 0)
            return false;
    } catch (Dictionary<int, std::string>::DictionaryException &ex) {
        return false; // adding to empty dictionarys should not throw an error
    }

    auto *dictionary1 = new Dictionary<int, std::string> (GetTestDictionary3());
    auto *dictionary2 = new Dictionary<int, std::string> (GetTestDictionary4());

    auto *testDictionary = new Dictionary<int, std::string>(*dictionary1 + *dictionary2);

    if (testDictionary->Count() != 10)
        return false;

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", *testDictionary))
        return false;

    testDictionary = new Dictionary<int,std::string>(*testDictionary + *testDictionary);

    if (testDictionary->Count() != 10)
        return false;

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", *testDictionary))
        return false;

    delete testDictionary;
    delete dictionary1;
    delete dictionary2;
    return true;
}

bool DictionaryTests::TestMinusOperator() {
    auto emptyDictionary = GetEmptyTestDictionary();
    try {
        auto testSeq = emptyDictionary - emptyDictionary;
        if (testSeq.Count() != 0)
            return false;
    } catch (Dictionary<int, std::string>::DictionaryException &ex) {
        return false; // subtracting to empty dictionaries should not throw an error
    }

    auto *dictionary1 = new Dictionary<int, std::string> (GetTestDictionary3());
    auto *dictionary2 = new Dictionary<int, std::string> (GetTestDictionary4());

    auto *testDictionary = new Dictionary<int, std::string>(*dictionary2 + *dictionary1);

    if (!CheckInOrder("1, 2, 3, 4, 5, 6, 7, 8, 9, 10", *testDictionary))
        return false;

    testDictionary = new Dictionary<int, std::string>(*testDictionary - *dictionary1);

    if (testDictionary->Count() != 5)
        return false;

    if (!CheckInOrder("6, 7, 8, 9, 10", *testDictionary))
        return false;

    testDictionary = new Dictionary<int,std::string>(*testDictionary - *testDictionary);

    if (testDictionary->Count() != 0)
        return false;


    delete testDictionary;
    delete dictionary1;
    delete dictionary2;
    return true;
}

std::string DictionaryTests::RunTests() {
    std::stringstream _stringstream;
    _stringstream << "\tTestInsert: " << (TestInsert() ? "success" : "fail") << std::endl;
    _stringstream << "\tTestContains: " << (TestContains() ? "success" : "fail") << std::endl;
    _stringstream << "\tTestGet:" << (TestGet() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestRemove:" << (TestRemove() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestClear:" << (TestClear() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestEnumerator:" << (TestEnumerator() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestCopy:" << (TestCopy() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestEqualOperator:" << (TestEqualOperator() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestPlusOperator:" << (TestPlusOperator() ? " success" : "fail") << std::endl;
    _stringstream << "\tTestMinusOperator:" << (TestMinusOperator() ? " success" : "fail") << std::endl;

    return _stringstream.str();
}

