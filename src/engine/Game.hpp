#ifndef LAKE_ENGINE_GAME_HPP
#define LAKE_ENGINE_GAME_HPP

#include "Input.hpp"
#include <string_view>

namespace engine {
class Game {
  public:
	Game(std::string_view title, const int width, int height,
	     bool fullscreen);
	~Game();

	void handle_events();
	void update();
	void render();
	void imgui_render();
	void swap_window();

	[[nodiscard]] constexpr auto is_running() const noexcept {
		return is_running_;
	}

  protected:
	SDL_Window *window_;
	SDL_GLContext context_;
	GameState gameState_;

	std::vector<Event> events{TimeElapsed{}};

	bool is_running_;
};
} // namespace engine

#endif // LAKE_ENGINE_GAME_HPP