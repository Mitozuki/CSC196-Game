#include "Core/Core.h"
#include "Renderer/Renderer.h"
#include "Renderer/Model.h"
#include "Input/InputSystem.h"
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
	//constexpr float a = kiko::DegreesToRad(180);

	kiko::seed_random((unsigned int)time(nullptr));
	kiko::setFilePath("Assets");

	kiko::Renderer renderer;
	renderer.Initialize();
	renderer.CreateWindow("CSC195", 800, 600);

	kiko::InputSystem inputSystem;
	inputSystem.Initialize();


	//std::vector<kiko::vec2> points{ { 10, 0 }, { 5, 5 }, { 0, -5 }, { 10, 0 } };
	kiko::Model model;
	model.Load("star.txt");

	kiko::vec2 v{5, 5};
	v.Normalize();

	vector<Star> stars;
	for (int i = 0; i < 1000; i++)
	{
		kiko::Vector2 pos(kiko::random(renderer.GetWidth()), kiko::random(renderer.GetHeight()));
		kiko::Vector2 vel(kiko::Vector2(kiko::randomf(1, 4), 0.0f));

		stars.push_back(Star(pos, vel));
	}

	kiko::Transform transform{ { 400, 300 }, 0, 3 };

	kiko::vec2 position{ 400, 300 };
	float speed = 100;
	float turnRate = kiko::DegreesToRad(180);

	// main game loop
	bool quit = false;
	while (!quit)
	{
		kiko::g_time.Tick();
		inputSystem.Update();
		cout << inputSystem.GetMousePosition().x << " " << inputSystem.GetMousePosition().y << endl;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_ESCAPE))
		{
			quit = true;
		}

		float rotate = 0;
		if(inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
		if(inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
		transform.rotation += rotate * turnRate * kiko::g_time.GetDeltaTime();

		float thrust = 0;
		if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

		kiko::vec2 foward = kiko::vec2{ 0, -1 }.Rotate(transform.rotation);
		transform.position += foward * speed * thrust * kiko::g_time.GetDeltaTime();
		transform.position.x = kiko::Wrap(transform.position.x, renderer.GetWidth());
		transform.position.y = kiko::Wrap(transform.position.y, renderer.GetHeight());


		//kiko::vec2 direction;
		//if (inputSystem.GetKeyDown(SDL_SCANCODE_W)) direction.y = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_A)) direction.x = -1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_S)) direction.y = 1;
		//if(inputSystem.GetKeyDown(SDL_SCANCODE_D)) direction.x = 1;

		//position += direction * speed * kiko::g_time.GetDeltaTime();

		if (inputSystem.GetMouseButtonDown(0))
		{
			cout << "left mouse pressed " << endl;
		}
		if (inputSystem.GetMouseButtonDown(1))
		{
			cout << "middle mouse pressed " << endl;
		}
		 if (inputSystem.GetMouseButtonDown(2))
		{
			cout << "right mouse pressed " << endl;
		}

		renderer.SetColor(0, 0, 0, 0);
		renderer.BeginFrame();
		//draw
		kiko::Vector2 velocity(1.0f, 0.3f);

		for (auto& star : stars)
		{
			star.Update( renderer.GetWidth(), renderer.GetHeight());

			renderer.SetColor(kiko::random(256), kiko::random(256), kiko::random(256), 255);
			renderer.DrawPoint(star.m_pos.x, star.m_pos.y);
		}

		model.Draw(renderer, transform.position, transform.rotation, transform.scale);

		renderer.EndFrame();

		//this_thread::sleep_for(chrono::milliseconds(100));
	}

	return 0;
}
