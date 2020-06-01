//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_DICTIONARYTESTS_H
#define PW_EADS_LABS_DICTIONARYTESTS_H
#include "Dictionary.hh"

class DictionaryTests {
private:
    Dictionary<int, std::string> GetTestDictionary1();
    Dictionary<int, std::string> GetTestDictionary2();
    Dictionary<int, std::string> GetTestDictionary3();
    Dictionary<int, std::string> GetTestDictionary4();
    Dictionary<int, std::string> GetEmptyTestDictionary();
    bool CheckInOrder(std::string expected, Dictionary<int, std::string> &dictionary);
public:
    bool TestInsert();
    bool TestContains();
    bool TestGet();
    bool TestRemove();
    bool TestClear();
    bool TestEnumerator();
    bool TestCopy();
    bool TestEqualOperator();
    bool TestPlusOperator();
    bool TestMinusOperator();

    std::string RunTests();
};


#endif //PW_EADS_LABS_DICTIONARYTESTS_H
