#ifndef SEQUENCETESTS_HPP
#define SEQUENCETESTS_HPP

void RunSequenceTests();
void TestAddVectors();
void TestScalarMultiply();
void TestArraySequenceNorm();
void TestImmutableAppend();
void TestImmutablePrepend();
void TestGetSubsequenceEdgeCases();
void TestConcatWithEmpty();
void TestInsertAtOutOfRange();
void TestGetOutOfRange();
void TestConcatSizeMismatchAdd();

#endif