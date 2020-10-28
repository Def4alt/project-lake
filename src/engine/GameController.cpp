#include "GameController.hpp"

namespace engine {
void GameController::update() {
	const auto controller = SDL_GameControllerOpen(id);

	const auto axis_start = CONTROLLER_AXIS_LIST.begin();

	for (std::size_t i = 0; i < CONTROLLER_AXIS_LIST.size(); i++) {
		axisState[i] =
		    SDL_GameControllerGetAxis(controller, *std::next(axis_start));
	}

	const auto button_start = CONTROLLER_BUTTON_LIST.begin();

	for (std::size_t i = 0; i < CONTROLLER_BUTTON_LIST.size(); i++) {
		buttonState[i] =
		    SDL_GameControllerGetButton(controller, *std::next(button_start));
	}
}
} // namespace engine
