#include"Renderer.h"

namespace kiko
{
	Renderer g_renderer;

	bool Renderer::Initialize()
	{
		SDL_Init(SDL_INIT_VIDEO);

		return true;
	}
	void Renderer::Shutdown()
	{
	}
	void Renderer::CreateWindow(const std::string& title, int width, int height)
	{
		m_width = width;
		m_height = height;

		m_window = SDL_CreateWindow(title.c_str(), 100, 100, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
	}
	void Renderer::BeginFrame()
	{
		SDL_RenderClear(m_renderer);
	}
	void Renderer::EndFrame()
	{
		SDL_RenderPresent(m_renderer);
	}
	void Renderer::SetColor(uint8_t R, uint8_t G, uint8_t B, uint8_t A)
	{
		SDL_SetRenderDrawColor(m_renderer, R, G, B, A);
	}
	void Renderer::DrawLine(int x1, int y1, int x2, int y2)
	{
		SDL_RenderDrawLine(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawLine(float x1, float y1, float x2, float y2)
	{
		SDL_RenderDrawLineF(m_renderer, x1, y1, x2, y2);
	}
	void Renderer::DrawPoint(int x, int y)
	{
		SDL_RenderDrawPoint(m_renderer, x, y);
	}
	void Renderer::DrawPoint(float x, float y)
	{
		SDL_RenderDrawPointF(m_renderer, x, y);
	}
}
