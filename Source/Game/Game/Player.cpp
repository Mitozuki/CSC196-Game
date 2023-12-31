#include "Player.h"
#include "Weapon.h"
#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Input/InputSystem.h"
#include "Renderer/Renderer.h"
#include "Renderer/Emitter.h"
#include "Renderer/ModelManager.h"

void Player::Update(float dt)
{
	Actor::Update(dt);

	float rotate = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_A)) rotate = -1;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_D)) rotate = 1;
	m_transform.rotation += rotate * m_turnRate * kiko::g_time.GetDeltaTime();

	float thrust = 0;
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_W)) thrust = 1;

	kiko::vec2 forward = kiko::vec2{ 0, -1 }.Rotate(m_transform.rotation);
	AddForce(forward * m_speed * thrust);

	m_transform.position += forward * m_speed * thrust * kiko::g_time.GetDeltaTime();
	m_transform.position.x = kiko::Wrap(m_transform.position.x, (float)kiko::g_renderer.GetWidth());
	m_transform.position.y = kiko::Wrap(m_transform.position.y, (float)kiko::g_renderer.GetHeight());

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_SPACE) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_SPACE))
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, m_transform.scale };
		//  + kiko::DegreesToRad(10.0f)
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>( 400.0f, transform, kiko::g_manager.Get("bolt.txt"));
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon));
	}
	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_B) && !kiko::g_inputSystem.GetPreviousKeyDown(SDL_SCANCODE_B))
	{
		kiko::Transform transform{ m_transform.position, m_transform.rotation, m_transform.scale };
		kiko::Transform transform1{ m_transform.position, m_transform.rotation + kiko::DegreesToRad(10.0f), m_transform.scale };
		kiko::Transform transform2{ m_transform.position, m_transform.rotation - kiko::DegreesToRad(10.0f), m_transform.scale };
		//  + kiko::DegreesToRad(10.0f)
		std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(400.0f, transform, kiko::g_manager.Get("bolt.txt"));
		std::unique_ptr<Weapon> weapon1 = std::make_unique<Weapon>(400.0f, transform1, kiko::g_manager.Get("bolt.txt"));
		std::unique_ptr<Weapon> weapon2 = std::make_unique<Weapon>(400.0f, transform2, kiko::g_manager.Get("bolt.txt"));
		weapon->m_tag = "Player";
		m_scene->Add(std::move(weapon));
		m_scene->Add(std::move(weapon1));
		m_scene->Add(std::move(weapon2));
	}

	if (kiko::g_inputSystem.GetKeyDown(SDL_SCANCODE_T)) kiko::g_time.SetTimeScale(0.5f);
	else kiko::g_time.SetTimeScale(1.0f);
}

void Player::OnCollision(Actor* other)
{
	if (other->m_tag == "Enemy")
	{
		m_game->SetLives(m_game->GetLives() - 1);
		dynamic_cast<SpaceGame*>(m_game)->setState(SpaceGame::eState::PlayerDeadStart);
		m_destroyed = true;
	}
}
