#include <iostream>
#include "../include/DictionaryTests.h"

int main() {
    std::cout << "Testing Dictionary" << std::endl;
    auto dictionaryTests = DictionaryTests();
    std::cout << dictionaryTests.RunTests();

   /* std::cout << "Testing Get operations" << std::endl;
    auto dictionaryGetOperationsTests = DictionaryGetOperationsTests();
    std::cout << dictionaryGetOperationsTests.RunTests();

    std::cout << std::endl << "Testing Add operations" << std::endl;
    auto dictionaryAddOperationsTests = DictionaryTests();
    std::cout << dictionaryAddOperationsTests.RunTests();

    std::cout << std::endl << "Testing Remove operations" << std::endl;
    auto dictionaryRemoveOperationsTests = DictionaryRemoveOperationsTests();
    std::cout << dictionaryRemoveOperationsTests.RunTests();

    std::cout << std::endl << "Testing Other operations" << std::endl;
    auto dictionaryOtherOperationsTests = DictionaryOtherOperationsTests();
    std::cout << dictionaryOtherOperationsTests.RunTests();   // this test contains dynamic allocation tests as well
*/

    return 0;
}
