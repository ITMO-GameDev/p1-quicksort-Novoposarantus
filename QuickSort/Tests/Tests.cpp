#include "pch.h"
#include "CppUnitTest.h"
#include <tuple>
#include <algorithm>
#include <chrono> 
#include "../Sort/QuickSort.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template < typename T >
void ArrayEquals(T* arrFirst, T* arrSecond, int size) {
	int index = 0;
	while (index < size)
	{
		Assert::AreEqual(*(arrFirst + index), *(arrSecond + index));
		++index;
	}
}

std::tuple<int*, int*, int*> RandomArray(int length) {
	int* arr = new int[length];
	int* sortedArr = new int[length];
	for (int i = 0; i < length; i++) {
		int randInt = rand() % 10000;
		arr[i] = randInt;
		sortedArr[i] = randInt;
	}
	std::sort(sortedArr, sortedArr + length);
	return { arr, arr + length - 1, sortedArr };
}

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(TestSwap)
		{
			int a[3] = { 1, 2, 3 };
			Swap(a, a + 1);
			Assert::AreEqual(a[0], 2);
			Assert::AreEqual(a[1], 1);
		}


		TEST_METHOD(TestSize)
		{
			int a[3] = { 1, 2, 3 };
			int size = Size(a, a + 2);
			Assert::AreEqual(size, 3);
		}

		TEST_METHOD(InsertionSort_SingleElement)
		{
			int a[] = {1};
			InsertionSort(a, a, [](int a, int b) { return a < b; });
			Assert::AreEqual(a[0], 1);
		}

		TEST_METHOD(InsertionSort_20Element)
		{
			int length = 20;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			InsertionSort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}


		TEST_METHOD(InsertionSort_100Element)
		{
			int length = 100;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			InsertionSort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}


		TEST_METHOD(InsertionSort_1000Element)
		{
			int length = 1000;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			InsertionSort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}


		TEST_METHOD(QuickSort_SingleElement)
		{
			int a[] = { 1 };
			Sort(a, a, [](int a, int b) { return a < b; });
			Assert::AreEqual(a[0], 1);
		}

		TEST_METHOD(QuickSort_20Element)
		{
			int length = 20;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			Sort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}


		TEST_METHOD(QuickSort_100Element)
		{
			int length = 100;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			Sort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}


		TEST_METHOD(QuickSort_1000Element)
		{
			int length = 1000;
			int* first;
			int* last;
			int* sortedFirst;
			std::tie(first, last, sortedFirst) = RandomArray(length);
			Sort(first, last, [](int a, int b) { return a < b; });
			ArrayEquals(first, sortedFirst, length);
			delete[] first;
			delete[] sortedFirst;
		}
	};
}
