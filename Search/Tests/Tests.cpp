#include "pch.h"
#include "CppUnitTest.h"
#include "../Search/Search.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestSizeEmptyConstructor)
		{
			lab3::Dictionary<int, double> dictionary;
			Assert::AreEqual(dictionary.size(), 0);
		}

		TEST_METHOD(TestPut)
		{
			lab3::Dictionary<int, double> dictionary;
			dictionary.put(2, 2.3);
			dictionary.put(3, 4.3);
			Assert::AreEqual(dictionary[2], 2.3);
		}

		TEST_METHOD(TestPutIfExist)
		{
			lab3::Dictionary<int, double> dictionary;
			dictionary.put(2, 2.3);
			Assert::AreEqual(dictionary[2], 2.3);
			Assert::AreEqual(dictionary.size(), 1);
			dictionary.put(2, 4.5);
			Assert::AreEqual(dictionary[2], 4.5);
			Assert::AreEqual(dictionary.size(), 1);
		}

		TEST_METHOD(TestContains)
		{
			lab3::Dictionary<int, double> dictionary;
			dictionary.put(2, 2.3);
			dictionary.put(3, 4.3);
			Assert::IsTrue(dictionary.contains(2));
			Assert::IsTrue(dictionary.contains(3));
			Assert::IsFalse(dictionary.contains(1));
		}

		TEST_METHOD(TestRemove)
		{
			lab3::Dictionary<int, double> dictionary;
			dictionary.put(2, 2.3);
			dictionary.put(3, 4.3);
			Assert::IsTrue(dictionary.contains(2));
			Assert::IsTrue(dictionary.contains(3));
			dictionary.remove(2);
			Assert::IsFalse(dictionary.contains(2));
		}

		TEST_METHOD(TestIteratorRoot)
		{
			lab3::Dictionary<int, double> dictionary;
			dictionary.put(2, 2.3);
			Assert::AreEqual(dictionary.iterator().get(), 2.3);
			Assert::AreEqual(dictionary.iterator().key(), 2);
		}

		TEST_METHOD(TestTree)
		{
			lab3::Dictionary<int, int> dictionary;
			int* arr = new int[10] {2, 6, 78, 23, 45, 36, 87, 89, 12, 63};
			for (int i = 0; i < 10; ++i) {
				dictionary.put(arr[i], arr[i]);
			}
			for (int i = 0; i < 9; ++i) {
				Assert::AreEqual(dictionary[arr[i]], arr[i]);
			}
		}

		TEST_METHOD(TestIteratorSet)
		{
			lab3::Dictionary<int, int> dictionary;
			dictionary.put(2, 31);
			Assert::AreEqual(dictionary[2], 31);
			auto iterator = dictionary.iterator();
			iterator.set(62);
			Assert::AreEqual(dictionary[2], 62);
		}

		TEST_METHOD(TestIteratorAll)
		{
			lab3::Dictionary<int, int> dictionary;
			int* arr = new int[10]{ 2, 6, 78, 23, 45, 36, 87, 89, 12, 63 };
			for (int i = 0; i < 10; ++i) {
				dictionary.put(arr[i], arr[i]);
			}
			auto iterator = dictionary.iterator();
			Assert::AreEqual(iterator.key(), 45);
			iterator.next();
			Assert::AreEqual(iterator.key(), 6);
			iterator.next();
			Assert::AreEqual(iterator.key(), 2);
			iterator.next();
			Assert::AreEqual(iterator.key(), 23);
			iterator.next();
			Assert::AreEqual(iterator.key(), 12);
			iterator.next();
			Assert::AreEqual(iterator.key(), 36);
			iterator.next();
			Assert::AreEqual(iterator.key(), 87);
			iterator.next();
			Assert::AreEqual(iterator.key(), 78);
			iterator.next();
			Assert::AreEqual(iterator.key(), 63);
			iterator.next();
			Assert::AreEqual(iterator.key(), 89);
			Assert::IsFalse(iterator.hasNext());
			iterator.prev();
			Assert::AreEqual(iterator.key(), 63);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 78);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 87);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 36);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 12);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 23);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 2);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 6);
			iterator.prev();
			Assert::AreEqual(iterator.key(), 45);
			Assert::IsFalse(iterator.hasPrev());

		}
	};
}
