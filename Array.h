#pragma once
#include <stdlib.h>


// Notes:
// It isn't 100% necessary to zero newly allocated sector. May remove it later.
// The decission to rather throw an error on buffer overrun is probably better than silently fixing the problem.
// Do not forget to 'remove' after use of arr!


namespace arr
{
	class FloatArr
	{
	private:
		float* pointer;
		int size;

		void sector_zero()
		{
			for (int i = 0; i < size; ++i)
				pointer[i] = 0;
		}
		int sanitize_pointer(int inputPointer)
		{
			int sanitizedPointer = inputPointer;
			if (sanitizedPointer < 0) { throw; }
			if (sanitizedPointer >= size) { throw; }
			return sanitizedPointer;
		}
	public:
		FloatArr()
		{
			size = 0;
		}
		FloatArr(int inputSize)
		{
			if (inputSize < 0)
				throw;
			size = inputSize;
			pointer = (float*)malloc(size * sizeof(float));
			sector_zero();
		}

		void set(int inputPointer, float inputValue)
		{
			int sanitizedPointer = sanitize_pointer(inputPointer);
			pointer[sanitizedPointer] = inputValue;
		}
		float get(int inputPointer)
		{
			int sanitizedPointer = sanitize_pointer(inputPointer);
			return pointer[sanitizedPointer];
		}
		void remove()
		{
			sector_zero();
			free(pointer);
		}
		int getSize()
		{
			return size;
		}
	};
}
