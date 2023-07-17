#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
#include "Audio/AudioSystem.h"
#include "Framework/Scene.h"
#include "Player.h"
#include "Enemy.h"

#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Star
{
public:
	Star(const kiko::Vector2 pos, const kiko::Vector2 vel) : m_pos{ pos }, m_vel{vel} {}

	void Update(int width, int height)
	{
		m_pos += m_vel * kiko::g_time.GetDeltaTime();
		if (m_pos.x >= width) m_pos.x = 0;
		if (m_pos.y >= height) m_pos.y = 0;
	}

	void Draw(kiko::Renderer& renderer)
	{
		renderer.DrawPoint(m_pos.x, m_pos.y);
	}

public:
	kiko::Vector2 m_pos;
	kiko::Vector2 m_vel;
};

int main(int argc, char* argv[])
{

	auto m1 = kiko::Max(4.0f, 3.0f);
	auto m2 = kiko::Max(4, 3);

	//constexpr float a = kiko::DegreesToRad(180);

	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");

	kiko::g_renderer.Initialize();
	kiko::g_renderer.CreateWindow("CSC195", 800, 600);

	kiko::g_audioSystem.Initialize();
	kiko::g_audioSystem.AddAudio("jump", "Jump.wav");
	
	kiko::g_inputSystem.Initialize();

	kiko::Model model;
	model.Load("star.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::random(kiko::g_renderer.GetWidth()), kiko::random(kiko::g_renderer.GetHeight()));
		kiko::Vector2 vel(kiko::Vector2(kiko::randomf(1, 4), 0.0f));

		stars.push_back(Star(pos, vel));
	}

	kiko::Transform transform{ { 400, 300 }, 0, 3 };

	kiko::vec2 position{ 400, 300 };
	float speed = 100;
	constexpr float turnRate = kiko::DegreesToRad(180);

	kiko::Scene scene;

	scene.Add(new Player{ speed, turnRate, { { 400, 300 }, 0, 3 }, model });
	
	for (int i = 0; i < 10; i++)
	{
		Enemy* enemy = new Enemy{300, turnRate, { { kiko::random(800), kiko::random(600) }, kiko::randomf(kiko::twoPi), 3}, model};
		scene.Add(enemy);
	}

	// main game loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		kiko::g_inputSystem.Update();
		kiko::g_audioSystem.Update();
		cout << kiko::g_inputSystem.GetMousePosition().x << " " << kiko::g_inputSystem.GetMousePosition().y << endl;
		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		//update
		scene.Update(kiko::g_time.GetDeltaTime());
		//draw


		//kiko::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		//position += direction * speed * kiko::g_time.GetDeltaTime();

		if (kiko::g_inputSystem.GetMouseButtonDown(0))
		{
			cout << "left mouse pressed " << endl;
		}
		if (kiko::g_inputSystem.GetMouseButtonDown(1))
		{
			cout << "middle mouse pressed " << endl;
		}
		 if (kiko::g_inputSystem.GetMouseButtonDown(2))
		{
			cout << "right mouse pressed " << endl;
		}

		kiko::g_renderer.SetColor(0, 0, 0, 0);
		kiko::g_renderer.BeginFrame();
		//draw
		kiko::Vector2 velocity(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update(kiko::g_renderer.GetWidth(), kiko::g_renderer.GetHeight());

			kiko::g_renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			kiko::g_renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE))
		{
			kiko::g_audioSystem.PlayOneShot("jump");
		}

		scene.Draw(kiko::g_renderer);

		kiko::g_renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}
