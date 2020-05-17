//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_RINGADDOPERATIONSTESTS_H
#define PW_EADS_LABS_RINGADDOPERATIONSTESTS_H
#include "Ring.h"

class RingAddOperationsTests {
private:
    Ring<int, std::string> GetTestRing1();
    Ring<int, std::string> GetEmptyTestRing();
    bool IntegrityCheck(Ring<int, std::string> &ring);
public:
    bool TestPushFront();
    bool TestPushBack();
    bool TestInsertAfter();
    std::string RunTests();
};


#endif //PW_EADS_LABS_RINGADDOPERATIONSTESTS_H
