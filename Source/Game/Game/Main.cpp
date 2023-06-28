#include "Core/Random.h"
#include "Core/FileIO.h"
#include <iostream>

using namespace std;

int main()
{
	cout << kiko::getFilePath() << endl;
	kiko::seed_random((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++)
	{
		cout << kiko::random(5, 10) << endl;
	}
}
