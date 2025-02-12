#include <cppunit/CompilerOutputter.h>
#include <cppunit/Portability.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "../src/common/tetris_royal_lib/foo/foo.hpp"

int main() {
    Foo foo;

    // informs test-listener about testResults
    CppUnit::TestResult testResult;

    // register listener for collecting the testResults
    CppUnit::TestResultCollector collectedResults;
    testResult.addListener(&collectedResults);

    // insert test-suite at test-runner by registry
    CppUnit::TestRunner testRunner;
    testRunner.addTest(CppUnit::TestFactoryRegistry::getRegistry().makeTest());
    testRunner.run(testResult);

    // output results in compiler-format
    CppUnit::CompilerOutputter compilerOutputter(&collectedResults, std::cerr);
    compilerOutputter.write();

    // return 0 if tests were successful
    return collectedResults.wasSuccessful() ? 0 : 1;
}
