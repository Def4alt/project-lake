#include "Game.hpp"

#include "ImGuiHelper.hpp"
#include <GL/glew.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>

namespace engine {
Game::Game(std::string_view title, const int width, const int height,
           bool fullscreen)
    : is_running_(true) {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) != 0) {
		spdlog::error("Failed to init SDL: {}", SDL_GetError());
		abort();
	}

	uint32_t flags = SDL_WINDOW_OPENGL;

	if (fullscreen)
		flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN;

	window_ =
	    SDL_CreateWindow(std::string(title).c_str(), SDL_WINDOWPOS_CENTERED,
	                     SDL_WINDOWPOS_CENTERED, width, height, flags);

	if (window_ == nullptr) {
		spdlog::error("Failed to create window: {}", SDL_GetError());
		abort();
	}

	context_ = SDL_GL_CreateContext(window_);

	if (glewInit() != GLEW_OK) {
		spdlog::error("Failed to init GLEW");
		abort();
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(window_, context_);
	ImGui_ImplOpenGL3_Init(reinterpret_cast<const char *>(
	    glGetString(GL_NUM_SHADING_LANGUAGE_VERSIONS)));
}

Game::~Game() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(context_);
	SDL_DestroyWindow(window_);
	SDL_Quit();
}

void Game::handle_events() {
	const auto event = gameState_.nextEvent(*window_);

	if (const auto sdlEvent = GameState::toSDLEvent(event); sdlEvent) {
		ImGui_ImplSDL2_ProcessEvent(
		    reinterpret_cast<const SDL_Event *>(&sdlEvent));
	}

	std::visit(overloaded{[](TimeElapsed &prev, const TimeElapsed &next) {
		                      prev.elapsed += next.elapsed;
	                      },
	                      [&](const auto &, const std::monostate &) {},
	                      [&](const auto &, const auto &next) {
		                      events.push_back(next);
	                      }},
	           events.back(), event);

	std::visit(overloaded{[&](const GameControllerEvent auto &gc) {
		                      gameState_.update(gc);
	                      },
	                      [&](const CloseWindow &) { is_running_ = false; },
	                      [&](const std::monostate &) {

	                      },
	                      [&](const auto &) {}},
	           event);
}

void Game::update() {}

void Game::imgui_render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window_);
	ImGui::NewFrame();

	const auto gc =
	    GameState::gameControllerById(gameState_.gameControllers, 0);

	for (std::size_t i = 0; i < engine::CONTROLLER_BUTTON_LIST.size(); i++) {
		ImGuiHelper::Text(
		    "{}: {}", engine::toString(engine::CONTROLLER_BUTTON_LIST.at(i)),
		    gc.buttonState.at(i));
	}

	for (std::size_t i = 0; i < engine::CONTROLLER_AXIS_LIST.size(); i++) {
		ImGuiHelper::Text("{}: {}",
		                  engine::toString(engine::CONTROLLER_AXIS_LIST.at(i)),
		                  gc.axisState.at(i));
	}

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Game::render() {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.3F, 0.5F, 0.5F, 1.0F);
}

void Game::swap_window() { SDL_GL_SwapWindow(window_); }
} // namespace engine