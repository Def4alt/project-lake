#include <spdlog/spdlog.h>
#include <docopt/docopt.h>
#include <SDL.h>
#include <map>

#include "Game.hpp"
#include <memory>

#undef main

static constexpr auto USAGE =
  R"(Project Lake.

	Usage:
		  project-lake [options]

	Options:
		  -h --help			        Show this screen.
          --width=WIDTH             Screen width in pixels [default: 1024].
          --height=HEIGHT           Screen height in pixels [default: 768].
          --fullscreen              Start in fullscreen.
)";

int main(int argc, const char **argv)
{
	std::map<std::string, docopt::value> args = docopt::docopt(USAGE,
	  { std::next(argv), std::next(argv, argc) },
	  true,// show help if requested
	  "Project Lake 1.0");// version string

	const auto width = args["--width"].asLong();
	const auto height = args["--height"].asLong();
	const auto fullscreen = args["--fullscreen"].asBool();

	for (auto const &arg : args) {
		if (arg.second.isString()) {
			spdlog::info("Parameter set '{}': {}", arg.first, arg.second.asString());
		}
	}

	auto game = std::make_unique<engine::Game>("Project Lake", static_cast<int>(width), static_cast<int>(height), fullscreen);

	while (game->is_running()) {
		game->handle_events();

		game->update();
        game->render();
        game->imgui_render();
		
		game->swap_window();
	}

	return 0;
}
