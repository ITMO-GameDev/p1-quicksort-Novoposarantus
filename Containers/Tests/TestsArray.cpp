#include "pch.h"
#include "CppUnitTest.h"
#include "../Array/Array.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:

		TEST_METHOD(TestSizeEmptyConstructor)
		{
			containers::DynamicArray<int> arr;
			Assert::AreEqual(arr.size(), 0);
		}

		TEST_METHOD(TestSize)
		{
			containers::DynamicArray<int> arr(17);
			Assert::AreEqual(arr.size(), 17);
		}

		TEST_METHOD(TestSetAndGetByOperator)
		{
			containers::DynamicArray<int> arr(10);
			arr[0] = 0;
			arr[1] = 1;
			Assert::AreEqual(arr[0], 0);
			Assert::AreEqual(arr[1], 1);
			arr[0] = 999;
			Assert::AreEqual(arr[0], 999);
		}

		TEST_METHOD(TestOperatorExceptionSmallerIndex)
		{
			containers::DynamicArray<int> arr(10);
			try {
				arr[-2];
			} catch (std::out_of_range) {

			} catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestOperatorExceptionGreaterIndex)
		{
			containers::DynamicArray<int> arr(10);
			try {
				arr[100];
			}
			catch (std::out_of_range) {

			}
			catch (...) {
				Assert::Fail();
			}
		}

		TEST_METHOD(TestInsert)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr;
			for (int i = 0; i < 10; ++i) {
				arr.insert(a[i]);
			}
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}
		}

		TEST_METHOD(TestInsertByIndex_ToCenter)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr;
			for (int i = 0; i < 10; ++i) {
				arr.insert(i, a[i]);
			}
			arr.insert(2, value);
			Assert::AreEqual(arr[2], value);
		}

		TEST_METHOD(TestInsertByIndex_ToEnd)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr.insert(i, a[i]);
			}
			arr.insert(10, value);
			Assert::AreEqual(arr[10], value);
			for (int i = 0; i < 10; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}
		}

		TEST_METHOD(TestInsertByIndex_ToStart)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr.insert(i, a[i]);
			}
			arr.insert(0, value);
			Assert::AreEqual(arr[0], value);
			for (int i = 1; i <= 10; ++i) {
				Assert::AreEqual(arr[i], a[i-1]);
			}
		}

		TEST_METHOD(TestRemove_FromCenter)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			arr.remove(5);
			Assert::AreEqual(arr.size(), 9);
			Assert::AreEqual(arr[5], 7);
		}

		TEST_METHOD(TestRemove_FromStart)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			arr.remove(0);
			Assert::AreEqual(arr.size(), 9);
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i + 1]);
			}
		}

		TEST_METHOD(TestRemove_FromEnd)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			arr.remove(9);
			Assert::AreEqual(arr.size(), 9);
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}
		}

		//Test Iterator

		TEST_METHOD(TestIterator_Get)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			Assert::AreEqual(arr.iterator().get(), a[0]);
		}

		TEST_METHOD(TestIterator_Set)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.set(value);
			Assert::AreEqual(arr[0], value);
		}
		
		TEST_METHOD(TestIterator_Next)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.next();
			iterator.set(value);
			Assert::AreEqual(arr[1], value);
		}

		TEST_METHOD(TestIterator_ToIndex)
		{
			int value = 1080;
			int index = 8;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(index);
			iterator.set(value);
			Assert::AreEqual(arr[index], value);
		}

		TEST_METHOD(TestIterator_Prev)
		{
			int value = 1080;
			int index = 8;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(index);
			iterator.prev();
			iterator.set(value);
			Assert::AreEqual(arr[index - 1], value);
		}

		TEST_METHOD(TestIterator_HasPrevInStart)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			Assert::IsFalse(iterator.hasPrev());
		}

		TEST_METHOD(TestIterator_HasPrevInCenter)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(5);
			Assert::IsTrue(iterator.hasPrev());
		}

		TEST_METHOD(TestIterator_HasNextInEnd)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(9);
			Assert::IsFalse(iterator.hasNext());
		}

		TEST_METHOD(TestIterator_HasNextInCenter)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(5);
			Assert::IsTrue(iterator.hasNext());
		}

		TEST_METHOD(TestIterator_InsertToStart)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.insert(value);
			Assert::AreEqual(arr[0], value);
			Assert::AreEqual(arr.size(), 11);
			for (int i = 1; i <= 10; ++i) {
				Assert::AreEqual(arr[i], a[i - 1]);
			}
		}

		TEST_METHOD(TestIterator_InsertToCenter)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(5);
			iterator.insert(value);
			Assert::AreEqual(arr[5], value);
			Assert::AreEqual(arr.size(), 11);
			for (int i = 1; i < 5; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}

			for (int i = 5; i < 10; ++i) {
				Assert::AreEqual(arr[i + 1], a[i]);
			}
		}

		TEST_METHOD(TestIterator_InsertToEnd)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(9);
			iterator.insert(value);
			Assert::AreEqual(arr[9], value);
			Assert::AreEqual(arr.size(), 11);
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}
			Assert::AreEqual(arr[10], a[9]);
		}

		TEST_METHOD(TestIterator_RemoveFromStart)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.remove();
			Assert::AreEqual(arr.size(), 9);
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i + 1]);
			}
		}

		TEST_METHOD(TestIterator_RemoveFromCenter)
		{
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(5);
			iterator.remove();
			Assert::AreEqual(arr.size(), 9);
			for (int i = 0; i < 5; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}

			for (int i = 5; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i + 1]);
			}
		}

		TEST_METHOD(TestIterator_RemoveFromEnd)
		{
			int value = 1080;
			int a[10] = { 1,2,3,4,5,6,7,8,9,10 };
			containers::DynamicArray<int> arr(10);
			for (int i = 0; i < 10; ++i) {
				arr[i] = a[i];
			}
			auto iterator = arr.iterator();
			iterator.toIndex(arr.size() - 1);
			iterator.remove();
			Assert::AreEqual(arr.size(), 9);
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(arr[i], a[i]);
			}
		}

	};
}
