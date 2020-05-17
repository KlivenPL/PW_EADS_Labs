//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_RINGGETOPERATIONSTESTS_H
#define PW_EADS_LABS_RINGGETOPERATIONSTESTS_H
#include "Ring.h"

class RingGetOperationsTests {
private:
    Ring<int, std::string> GetTestRing();
    Ring<int, std::string> GetEmptyTestRing();
public:
    bool TestGet();
    bool TestGetByIndex();
    bool TestGetIndex();
    std::string RunTests();
};


#endif //PW_EADS_LABS_RINGGETOPERATIONSTESTS_H
