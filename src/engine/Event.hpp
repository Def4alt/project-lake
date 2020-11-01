
#ifndef LAKE_ENGINE_EVENT_HPP
#define LAKE_ENGINE_EVENT_HPP

#include <SDL.h>
#include <array>
#include <chrono>
#include <optional>
#include <string_view>
#include <variant>
#include "GameController.hpp"

namespace engine {
using KeyCode = SDL_KeyCode;
using ScanCode = SDL_Scancode;
using KeyMod = SDL_Keymod;
using clock = std::chrono::steady_clock;

template <typename Source> struct Pressed {
	constexpr static std::string_view name{"Pressed"};
	constexpr static std::array elements{std::string_view{"source"}};
	Source source;
};

template <typename Source> struct Released {
	constexpr static std::string_view name{"Released"};
	constexpr static std::array elements{std::string_view{"source"}};
	Source source;
};

template <typename Source> struct Moved {
	constexpr static std::string_view name{"Moved"};
	constexpr static std::array elements{std::string_view{"source"}};
	Source source;
};

struct GameControllerButton {
	constexpr static std::string_view name{"GameControllerButtonEnum"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"id", "button"});
	int id;
	uint8_t button;
};

struct GameControllerAxis {
	constexpr static std::string_view name{"GameControllerAxisEnum"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"id", "axis", "position"});
	int id;
	uint8_t axis;
	int position;
};

struct Mouse {
	constexpr static std::string_view name{"Mouse"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"id", "x", "y"});
	unsigned int id;
	int x;
	int y;
};

struct MouseButton {
	constexpr static std::string_view name{"MouseButton"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"button", "mouse"});
	uint8_t button;
	Mouse mouse;
};

struct Key {
	constexpr static std::string_view name{"Key"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"key", "scan", "mod"});
	KeyCode key;
	ScanCode scan;
	KeyMod mod;
};

struct CloseWindow {
	constexpr static std::string_view name{"CloseWindow"};
	constexpr static std::array<std::string_view, 0> elements{};
};

struct TimeElapsed {
	constexpr static std::string_view name{"TimeElapsed"};
	constexpr static auto elements =
	    std::to_array<std::string_view>({"elapsed"});
	clock::duration elapsed;

	[[nodiscard]] float toSDLTime() const {
		return static_cast<float>(
		           std::chrono::duration_cast<std::chrono::microseconds>(
		               elapsed)
		               .count()) /
		       1000.0F;
	}
};

using Event =
    std::variant<std::monostate, CloseWindow, Pressed<Key>, Released<Key>,
                 Pressed<GameControllerButton>, Released<GameControllerButton>,
                 Moved<GameControllerAxis>, Moved<Mouse>, Pressed<MouseButton>,
                 Released<MouseButton>,

                 TimeElapsed>;



} // namespace engine

#endif // LAKE_ENGINE_EVENT_HPP
