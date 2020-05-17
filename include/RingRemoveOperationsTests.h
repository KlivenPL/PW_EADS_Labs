//
// Created by oskar on 16.05.2020.
//

#ifndef PW_EADS_LABS_RINGREMOVEOPERATIONSTESTS_H
#define PW_EADS_LABS_RINGREMOVEOPERATIONSTESTS_H
#include "Ring.h"

class RingRemoveOperationsTests {
private:
    Ring<int, std::string> GetTestRing2();
    Ring<int, std::string> GetTestRing();
    Ring<int, std::string> GetEmptyTestRing();
    bool IntegrityCheck(Ring<int, std::string> &ring);
public:
    bool TestRemove();
    bool TestRemoveAll();
    bool TestRemoveAtIndex();
    std::string RunTests();
};


#endif //PW_EADS_LABS_RINGREMOVEOPERATIONSTESTS_H
