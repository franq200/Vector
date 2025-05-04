#include "Vector.h"
#include <iostream>

int main()
{
	Vector<int> vec;
	vec.PushBack(2);
	vec.PushBack(3);
	vec.PushBack(6);
	std::cout << vec.At(2) << vec.At(1) << vec[0];
	Vector<int> vec2;
	vec2 = vec;
	if (vec == vec2)
	{
		std::cout << "\n" << vec2[2];
	}
	vec2.Reserve(6);
	std::cout << "\n" << vec2.Capacity() << vec2.Size();
	//vec.At(5);
	vec.Resize(10);
	std::cout << "\n" << vec.Capacity() << vec.Size();
	vec2.ShrinkToFit();
	std::cout << "\n" << vec2.Capacity() << vec2.Size();
	vec.Erase(vec.begin() + 2);
	std::cout << "\n" << vec.Capacity() << vec.Size();
	vec.PushBack(6);
	std::cout << "\n" << vec[0] << vec[2];
	vec.Resize(1);
	std::cout << "\n" << vec[0] << vec[2];
	return 0;
}