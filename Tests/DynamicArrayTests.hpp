#ifndef DYNAMICARRAYTESTS_HPP
#define DYNAMICARRAYTESTS_HPP

void RunDynamicArrayTests();
void TestConstructorValidSize();
void TestCopyConstructorDynamicArray();
void TestGetAndSet();
void TestInitializerConstructor();
void TestGetOutOfRangeThrowsLinkedList();
void TestSetOutOfRangeThrows();
void TestResizeLarger();
void TestResizeSmaller();
void TestResizeZeroThrows();
void TestOperatorAddition();
void TestOperatorAdditionSizeMismatchThrows();
void TestOperatorScalarMultiplication();
void TestDotProduct();
void TestDotProductSizeMismatchThrows();
void TestNorm();

#endif