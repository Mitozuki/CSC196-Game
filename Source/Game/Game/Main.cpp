#include "Core/Random.h"
#include "Core/FileIO.h"
#include "Core/Memory.h"
#include "Core/Time.h"
#include "Renderer/Renderer.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC195", 800, 600);

	while (true)
	{
		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//draw
		for (int i = 0; i < 1000; i++) {
			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.DrawPoint(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
			renderer.DrawLine(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()), kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
			renderer.EndFrame();
		}
	}

	return 0;
}
