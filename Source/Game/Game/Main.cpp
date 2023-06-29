#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>

using namespace std;

int main()
{
	kiko::g_memoryTracker.DisplayInfo();
	int* p = new int;
	kiko::g_memoryTracker.DisplayInfo();
	delete p;
	kiko::g_memoryTracker.DisplayInfo();

	kiko::Time timer;
	for (int i = 0; i < 100000; i++) {}
	cout << timer.GetElapsedSeconds() << endl;

	/*cout << kiko::getFilePath() << endl;
	kiko::setFilePath("Assets");
	cout << kiko::getFilePath() << endl;
	size_t size;
	kiko::getFileSize("game.txt", size);
	cout << size << endl;

	std::string s;
	kiko::readFile("game.txt", s);
	cout << s << endl;

	kiko::seed_random((unsigned int)time(nullptr));
	for (int i = 0; i < 10; i++)
	{
		cout << kiko::random(5, 10) << endl;
	}*/
}
