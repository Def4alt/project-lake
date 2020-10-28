#ifndef LAKE_ENGINE_GAME_HPP
#define LAKE_ENGINE_GAME_HPP

#include <string_view>
#include <SDL.h>
#include "GameController.hpp"

namespace engine {
class Game
{
  public:
	Game(std::string_view title, const int width, const int height, bool fullscreen);
	~Game();

	void handle_events();
	void update();
	void render();
	void imgui_render();
	void swap_window();

	[[nodiscard]] constexpr auto is_running() const noexcept { return is_running_; }

  protected:
	SDL_Window *window_;
	SDL_GLContext context_;
	GameController controller_;

	bool is_running_;
};
}// namespace engine

#endif// LAKE_ENGINE_GAME_HPP