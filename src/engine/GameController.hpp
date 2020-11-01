#ifndef LAKE_ENGINE_GAMECONTROLLER_HPP
#define LAKE_ENGINE_GAMECONTROLLER_HPP

#include <SDL.h>
#include <array>
#include <string_view>

namespace engine {

using GameControllerAxisEnum = SDL_GameControllerAxis;
using GameControllerButtonEnum = SDL_GameControllerButton;

constexpr std::array CONTROLLER_BUTTON_LIST = {
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_A,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_B,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_X,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_Y,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_BACK,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_GUIDE,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_START,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_LEFTSTICK,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_DPAD_UP,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    GameControllerButtonEnum::SDL_CONTROLLER_BUTTON_DPAD_RIGHT};

constexpr std::array CONTROLLER_AXIS_LIST = {
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_LEFTX,
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_LEFTY,
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_RIGHTX,
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_RIGHTY,
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    GameControllerAxisEnum::SDL_CONTROLLER_AXIS_TRIGGERRIGHT};

struct GameController {
	int id;

	std::array<bool, CONTROLLER_BUTTON_LIST.size()> buttonState;
	std::array<int, CONTROLLER_AXIS_LIST.size()> axisState;

    void refresh() {
        SDL_GameControllerUpdate();
        const auto controller = SDL_GameControllerOpen(id);

        const auto axis_start = CONTROLLER_AXIS_LIST.begin();

        for (std::size_t i = 0; i < CONTROLLER_AXIS_LIST.size(); i++) {
            axisState[i] =
                SDL_GameControllerGetAxis(controller, *std::next(axis_start));
        }

        const auto button_start = CONTROLLER_BUTTON_LIST.begin();

        for (std::size_t i = 0; i < CONTROLLER_BUTTON_LIST.size(); i++) {
            buttonState[i] = SDL_GameControllerGetButton(
                controller, *std::next(button_start));
        }
    }

    static GameController load(int id) {
        GameController gc {id, {}, {}};
        gc.refresh();

        return gc;
    }
};



constexpr std::string_view toString(GameControllerAxisEnum axis) {
	switch (axis) {
	case SDL_CONTROLLER_AXIS_LEFTX:
		return "Left X";
	case SDL_CONTROLLER_AXIS_LEFTY:
		return "Left Y";
	case SDL_CONTROLLER_AXIS_RIGHTX:
		return "Right X";
	case SDL_CONTROLLER_AXIS_RIGHTY:
		return "Right Y";
	case SDL_CONTROLLER_AXIS_TRIGGERLEFT:
		return "Left Trigger";
	case SDL_CONTROLLER_AXIS_TRIGGERRIGHT:
		return "Right Trigger";
	default:
		return "Invalid";
	}
}

constexpr std::string_view toString(GameControllerButtonEnum button) {
	switch (button) {
	case SDL_CONTROLLER_BUTTON_A:
		return "A";
	case SDL_CONTROLLER_BUTTON_B:
		return "B";
	case SDL_CONTROLLER_BUTTON_X:
		return "X";
	case SDL_CONTROLLER_BUTTON_Y:
		return "Y";
	case SDL_CONTROLLER_BUTTON_BACK:
		return "Back";
	case SDL_CONTROLLER_BUTTON_GUIDE:
		return "Guide";
	case SDL_CONTROLLER_BUTTON_START:
		return "Start";
	case SDL_CONTROLLER_BUTTON_LEFTSTICK:
		return "Left Stick";
	case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
		return "Right Stick";
	case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
		return "Left Shoulder";
	case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
		return "Right Shoulder";
	case SDL_CONTROLLER_BUTTON_DPAD_UP:
		return "DPAD Up";
	case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
		return "DPAD Down";
	case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
		return "DPAD Left";
	case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
		return "DPAD Right";
	default:
		return "Invalid";
	}
}

} // namespace engine

#endif // PROJECT_LAKE_GAMECONTROLLER_HPP
