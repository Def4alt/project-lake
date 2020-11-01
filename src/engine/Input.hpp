#ifndef LAKE_ENGINE_INPUT_HPP
#define LAKE_ENGINE_INPUT_HPP

#include "Event.hpp"
#include <memory>
#include <spdlog/spdlog.h>
#include <thread>
#include <vector>
#include <vendor/imgui/imgui_impl_sdl.h>

namespace engine {

template <class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

struct GameState {
	clock::time_point lastTick{clock::now()};

	std::vector<Event> pendingEvents;

	static std::optional<SDL_Event>
	toSDLEvent([[maybe_unused]] const Event &event) {
		return {};
	}

	static Event toEvent(const SDL_Event &event) {
		switch (event.type) {
		case SDL_QUIT:
			return CloseWindow{};
		case SDL_CONTROLLERBUTTONDOWN:
			return Pressed<GameControllerButton>{event.cbutton.which,
			                                     event.cbutton.button};
		case SDL_CONTROLLERBUTTONUP:
			return Released<GameControllerButton>{event.cbutton.which,
			                                      event.cbutton.button};
		case SDL_CONTROLLERAXISMOTION:
			return Moved<GameControllerAxis>{
			    event.caxis.which, event.caxis.axis, event.caxis.value};
		case SDL_MOUSEBUTTONDOWN:
			return Pressed<MouseButton>{
			    event.button.button,
			    {event.button.which, event.button.x, event.button.y}};
		case SDL_MOUSEBUTTONUP:
			return Released<MouseButton>{
			    event.button.button,
			    {event.button.which, event.button.x, event.button.y}};
		case SDL_MOUSEMOTION:
			return Moved<Mouse>{event.motion.which, event.motion.x,
			                    event.motion.y};
		case SDL_KEYDOWN:
			return Pressed<Key>{static_cast<KeyCode>(event.key.keysym.sym),
			                    event.key.keysym.scancode,
			                    static_cast<KeyMod>(event.key.keysym.mod)};
		case SDL_KEYUP:
			return Released<Key>{static_cast<KeyCode>(event.key.keysym.sym),
			                     event.key.keysym.scancode,
			                     static_cast<KeyMod>(event.key.keysym.mod)};
		default:
			return std::monostate{};
		}
	}

	Event nextEvent(SDL_Window &window) {
		if (!pendingEvents.empty()) {
			auto event = pendingEvents.front();
			pendingEvents.erase(pendingEvents.begin());

			std::visit(
			    overloaded{[](const TimeElapsed &timeElapsed) {
				               std::this_thread::sleep_for(timeElapsed.elapsed);
			               },
			               [&](const Moved<Mouse> &me) {
				               SDL_WarpMouseInWindow(&window, me.source.x,
				                                     me.source.y);
			               },
			               [](const auto &) {}},
			    event);

			return event;
		}

		SDL_Event event{};
		if (SDL_PollEvent(&event))
			return toEvent(event);

		const auto nextTick = clock::now();
		const auto timeElapsed = nextTick - lastTick;
		lastTick = nextTick;

		return TimeElapsed{timeElapsed};
	}

	std::vector<GameController> gameControllers;

	static GameController &
	gameControllerById(std::vector<GameController> &gamecontrollers, int id) {
		auto controller =
		    std::find_if(begin(gamecontrollers), end(gamecontrollers),
		                 [id](const auto &gc) { return gc.id == id; });

		if (controller == gamecontrollers.end()) {
			gamecontrollers.push_back(GameController::load(id));
			return gamecontrollers.back();
		} else {
			return *controller;
		}
	}

	void update(const Pressed<GameControllerButton> &button) {
		auto &gc = gameControllerById(gameControllers, button.source.id);
		gc.buttonState[button.source.button] = true;
	}

	void update(const Released<GameControllerButton> &button) {
		auto &gc = gameControllerById(gameControllers, button.source.id);
		gc.buttonState[button.source.button] = false;
	}

	void update(const Moved<GameControllerAxis> &button) {
		auto &gc = gameControllerById(gameControllers, button.source.id);
		gc.axisState[button.source.axis] = button.source.position;
	}
};
template <typename T>
concept GameControllerEvent =
    std::is_same_v<T, Pressed<GameControllerButton>> ||
    std::is_same_v<T, Released<GameControllerButton>> ||
    std::is_same_v<T, Moved<GameControllerAxis>>;

} // namespace engine

#endif // LAKE_ENGINE_INPUT_HPP