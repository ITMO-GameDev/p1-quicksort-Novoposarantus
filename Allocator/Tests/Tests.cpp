#include "pch.h"
#include "CppUnitTest.h"
#include <iostream>
#include "../Allocator/MemoryAllocator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tests
{
	TEST_CLASS(Tests)
	{
	public:
		
		TEST_METHOD(TestAllocator)
		{
			lab4::MemoryAllocator allocator;
			allocator.init();
			int* pi = (int*)allocator.alloc(1000*sizeof(int));
			double* pd = (double*)allocator.alloc(200*sizeof(double));
			int* pa = (int*)allocator.alloc(50 * sizeof(int));
			allocator.free(pi);
			allocator.free(pd);
			allocator.free(pa);
			allocator.destroy();
		}
	};
}
