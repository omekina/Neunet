#pragma once
#include <iostream>



namespace console
{
	void write(float x)
	{
		std::cout << x << std::endl;
	}
	void write()
	{
		std::cout << std::endl;
	}
	float get()
	{
		float x;
		std::cin >> x;
	}
}
