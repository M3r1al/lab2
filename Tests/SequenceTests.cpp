#include <iostream>
#include <stdexcept>
#include "SequenceTests.hpp"

using namespace std;

void RunSequenceTests()
{
    cout << "Testing Sequence" << endl;
    // Тесты для Append
    int values1[] = {1, 2};
    int expectedAppend[] = {1, 2, 3};
    
    TestImmutableAppend<int>(CreateImmutableArray<int>(values1, 2), values1, 2, 3, expectedAppend, 3, "TestImmutableArrayAppend");
    TestImmutableAppend<int>(CreateImmutableList<int>(values1, 2), values1, 2, 3, expectedAppend, 3, "TestImmutableListAppend");
    TestMutableAppend<int>(CreateMutableArray<int>(values1, 2), values1, 2, 3, expectedAppend, 3, "TestMutableArrayAppend");
    TestMutableAppend<int>(CreateMutableList<int>(values1, 2), values1, 2, 3, expectedAppend, 3, "TestMutableListAppend");
    TestMutableAppend<int>(CreateAdaptiveSequence<int>(values1, 2), values1, 2, 3, expectedAppend, 3, "TestAdaptiveSequenceAppend");
    TestMutableAppend<int>(CreateSegmentedList<int>(values1, 2, 1024), values1, 2, 3, expectedAppend, 3, "TestSegmentedListAppend");

    int expectedNullAppend[] = {3};
    TestImmutableAppend<int>(CreateImmutableArray<int>(nullptr, 0), nullptr, 0, 3, expectedNullAppend, 1, "TestImmutableArrayEmptyAppend");
    
    // Тесты для Prepend
    int values2[] = {2, 3};
    int expectedPrepend[] = {1, 2, 3};
    
    TestImmutablePrepend<int>(CreateImmutableArray<int>(values2, 2), values2, 2, 1, expectedPrepend, 3, "TestImmutableArrayPrepend");
    TestImmutablePrepend<int>(CreateImmutableList<int>(values2, 2), values2, 2, 1, expectedPrepend, 3, "TestImmutableListPrepend");
    TestMutablePrepend<int>(CreateMutableArray<int>(values2, 2), values2, 2, 1, expectedPrepend, 3, "TestMutableArrayPrepend");
    TestMutablePrepend<int>(CreateMutableList<int>(values2, 2), values2, 2, 1, expectedPrepend, 3, "TestMutableListPrepend");
    TestMutablePrepend<int>(CreateAdaptiveSequence<int>(values2, 2), values2, 2, 1, expectedPrepend, 3, "TestAdaptiveSequencePrepend");
    TestMutablePrepend<int>(CreateSegmentedList<int>(values2, 2, 1024), values2, 2, 1, expectedPrepend, 3, "TestSegmentedListPrepend");
    
    // Тесты для GetSubsequence
    int values3[] = {1, 2, 3, 4, 5};
    int expectedSub[] = {2, 3, 4};
    
    TestGetSubsequence<int>(CreateImmutableArray<int>(values3, 5), values3, 5, 1, 3, expectedSub, 3, "TestImmutableArrayGetSubsequence");
    TestGetSubsequence<int>(CreateImmutableList<int>(values3, 5), values3, 5, 1, 3, expectedSub, 3, "TestImmutableListGetSubsequence");
    TestGetSubsequence<int>(CreateMutableArray<int>(values3, 5), values3, 5, 1, 3, expectedSub, 3, "TestMutableArrayGetSubsequence");
    TestGetSubsequence<int>(CreateMutableList<int>(values3, 5), values3, 5, 1, 3, expectedSub, 3, "TestMutableListGetSubsequence");
    TestGetSubsequence<int>(CreateAdaptiveSequence<int>(values3, 5), values3, 5, 1, 3, expectedSub, 3, "TestAdaptiveSequenceGetSubsequence");
    TestGetSubsequence<int>(CreateSegmentedList<int>(values3, 5, 1024), values3, 5, 1, 3, expectedSub, 3, "TestSegmentedListGetSubsequence");
    
    // Тесты для GetSubsequence с ошибкой
    TestGetSubsequence<int>(CreateImmutableArray<int>(values3, 5), values3, 5, 3, 5, nullptr, 0, "TestTooBigIndexGetSubsequense");
    TestGetSubsequence<int>(CreateImmutableArray<int>(values3, 5), values3, 5, -1, 3, nullptr, 0, "TestNegativeIndexGetSubsequense");

    // Тесты для Concat
    int values4[] = {1, 2};
    int values5[] = {3, 4};
    int expectedConcat[] = {1, 2, 3, 4};

    TestImmutableConcat<int>(CreateImmutableArray<int>(values4, 2), CreateImmutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableArrayConcat");
    TestImmutableConcat<int>(CreateImmutableList<int>(values4, 2), CreateImmutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableListConcat");
    TestMutableConcat<int>(CreateMutableArray<int>(values4, 2), CreateMutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableArrayConcat");
    TestMutableConcat<int>(CreateMutableList<int>(values4, 2), CreateMutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableListConcat");
    TestMutableConcat<int>(CreateAdaptiveSequence<int>(values4, 2), CreateAdaptiveSequence<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestAdaptiveSequenceConcat");
    TestMutableConcat<int>(CreateSegmentedList<int>(values4, 2, 1024), CreateSegmentedList<int>(values5, 2, 1024), values4, 2, values5, 2, expectedConcat, 4, "TestSegmentedListConcat");

    // Mutable and Immutable
    TestImmutableConcat<int>(CreateImmutableArray<int>(values4, 2), CreateMutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableAndMutableArrayConcat");
    TestImmutableConcat<int>(CreateImmutableList<int>(values4, 2), CreateMutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableAndMutableListConcat");
    TestMutableConcat<int>(CreateMutableArray<int>(values4, 2), CreateImmutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableAndImmutableArrayConcat");
    TestMutableConcat<int>(CreateMutableList<int>(values4, 2), CreateImmutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableAndImmutableListConcat");

    // Разные типы
    TestImmutableConcat<int>(CreateImmutableArray<int>(values4, 2), CreateImmutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableArrayAndListConcat");
    TestImmutableConcat<int>(CreateImmutableList<int>(values4, 2), CreateImmutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestImmutableListAndArrayConcat");
    TestMutableConcat<int>(CreateMutableArray<int>(values4, 2), CreateMutableList<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableArrayAndListConcat");
    TestMutableConcat<int>(CreateMutableList<int>(values4, 2), CreateMutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestMutableListAndArrayConcat");
    TestMutableConcat<int>(CreateAdaptiveSequence<int>(values4, 2), CreateImmutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestAdaptiveSequenceAndImmutableArrayConcat");
    TestMutableConcat<int>(CreateSegmentedList<int>(values4, 2, 1024), CreateAdaptiveSequence<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestSegmentedListAndAdaptiveSequenceConcat");
    TestMutableConcat<int>(CreateAdaptiveSequence<int>(values4, 2), CreateSegmentedList<int>(values5, 2, 1024), values4, 2, values5, 2, expectedConcat, 4, "TestAdaptiveSequenceAndSegmentedListConcat");
    TestMutableConcat<int>(CreateSegmentedList<int>(values4, 2, 1024), CreateImmutableArray<int>(values5, 2), values4, 2, values5, 2, expectedConcat, 4, "TestSegmentedListAndImmutableArrayConcat");


    // Тест для Concat с ошибкой
    TestImmutableConcat<int>(CreateImmutableArray<int>(nullptr, 0), CreateImmutableArray<int>(values5, 2), nullptr, 0, values5, 2, values5, 2, "TestConcatWithEmpty");
}