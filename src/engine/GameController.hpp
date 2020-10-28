#ifndef LAKE_ENGINE_GAMECONTROLLER_HPP
#define LAKE_ENGINE_GAMECONTROLLER_HPP

#include <SDL.h>
#include <array>
#include <string_view>

namespace engine {
using GameControllerAxis = SDL_GameControllerAxis;
using GameControllerButton = SDL_GameControllerButton;

constexpr std::array CONTROLLER_BUTTON_LIST = {
    GameControllerButton::SDL_CONTROLLER_BUTTON_A,
    GameControllerButton::SDL_CONTROLLER_BUTTON_B,
    GameControllerButton::SDL_CONTROLLER_BUTTON_X,
    GameControllerButton::SDL_CONTROLLER_BUTTON_Y,
    GameControllerButton::SDL_CONTROLLER_BUTTON_BACK,
    GameControllerButton::SDL_CONTROLLER_BUTTON_GUIDE,
    GameControllerButton::SDL_CONTROLLER_BUTTON_START,
    GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSTICK,
    GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSTICK,
    GameControllerButton::SDL_CONTROLLER_BUTTON_LEFTSHOULDER,
    GameControllerButton::SDL_CONTROLLER_BUTTON_RIGHTSHOULDER,
    GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_UP,
    GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_DOWN,
    GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_LEFT,
    GameControllerButton::SDL_CONTROLLER_BUTTON_DPAD_RIGHT};

constexpr std::array CONTROLLER_AXIS_LIST = {
    GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTX,
    GameControllerAxis::SDL_CONTROLLER_AXIS_LEFTY,
    GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTX,
    GameControllerAxis::SDL_CONTROLLER_AXIS_RIGHTY,
    GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERLEFT,
    GameControllerAxis::SDL_CONTROLLER_AXIS_TRIGGERRIGHT};


struct GameController {
	int id;

	std::array<bool, CONTROLLER_BUTTON_LIST.size()> buttonState;
	std::array<int, CONTROLLER_AXIS_LIST.size()> axisState;

	void update();
};

constexpr std::string_view to_string(GameControllerAxis axis) {
	switch (axis)
	{
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

constexpr std::string_view to_string(GameControllerButton button) {
	switch (button)
	{
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
