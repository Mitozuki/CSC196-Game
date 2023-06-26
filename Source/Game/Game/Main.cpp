#include <iostream>

int main()
{
#ifdef _DEBUG
	std::cout << "debug!\n";
#endif
	std::cout << "hello world!\n";
}
