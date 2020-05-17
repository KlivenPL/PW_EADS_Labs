#include <iostream>
#include "../include/RingAddOperationsTests.h"
#include "../include/RingGetOperationsTests.h"
#include "../include/RingRemoveOperationsTests.h"
#include "../include/RingOtherOperationsTests.h"

int main() {

    std::cout << "Testing Get operations" << std::endl;
    auto ringGetOperationsTests = RingGetOperationsTests();
    std::cout << ringGetOperationsTests.RunTests();

    std::cout << std::endl << "Testing Add operations" << std::endl;
    auto ringAddOperationsTests = RingAddOperationsTests();
    std::cout << ringAddOperationsTests.RunTests();

    std::cout << std::endl << "Testing Remove operations" << std::endl;
    auto ringRemoveOperationsTests = RingRemoveOperationsTests();
    std::cout << ringRemoveOperationsTests.RunTests();

    std::cout << std::endl << "Testing Other operations" << std::endl;
    auto ringOtherOperationsTests = RingOtherOperationsTests();
    std::cout << ringOtherOperationsTests.RunTests();   // this test contains dynamic allocation tests as well

    return 0;
}
