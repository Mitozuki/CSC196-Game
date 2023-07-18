#pragma once
#include "Actor.h"
#include <list>

namespace kiko
{
	class Renderer;

	class Scene
	{
	public:
		Scene() = default;

		void Update(float dt);
		void Draw(Renderer& renderer);

		void Add(Actor* actor);
		void Remove(Actor* actor);
		void RemoveAll();

	private:
		std::list<Actor*> m_actors;
	};
}