//
// Created by oskar on 17.05.2020.
//

#ifndef PW_EADS_LABS_RINGOTHEROPERATIONSTESTS_H
#define PW_EADS_LABS_RINGOTHEROPERATIONSTESTS_H
#include "Ring.h"
#include "Split.h"

class RingOtherOperationsTests {
private:
    Ring<int, std::string> GetTestRing1();
    Ring<int, std::string> GetTestRing2();
    Ring<int, std::string> GetTestRing3();
    Ring<int, std::string> GetTestRing4();
    Ring<int, std::string> GetTestRing5();
    Ring<int, std::string> GetEmptyTestRing();
    bool IntegrityCheck(Ring<int, std::string> &ring);
public:
    bool TestGetEnumerator();
    bool TestSplit();
    bool TestReverse();
    bool TestRotate();
    bool TestSubring();
    bool TestCount();
    bool TestEqualOperator();
    bool TestPlusOperator();
    bool TestMinusOperator();
    std::string RunTests();
};


#endif //PW_EADS_LABS_RINGOTHEROPERATIONSTESTS_H
