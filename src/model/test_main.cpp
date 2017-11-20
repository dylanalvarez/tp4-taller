//
// Created by facundo on 10/10/17.
//

#include <cppunit/ui/text/TextTestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>

int main(int argc, char *argv[]) {
    CppUnit::Test *test =
            CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    CppUnit::TextTestRunner runner;
    runner.addTest(test);

    runner.run();
    return 0;
}
