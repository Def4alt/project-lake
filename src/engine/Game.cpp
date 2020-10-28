#include "Game.hpp"

#include "ImGuiHelper.hpp"
#include <GL/glew.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl.h>
#include <spdlog/spdlog.h>

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

	controller_ = GameController{0, {}, {}};
	controller_.update();
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
	SDL_Event event{};

	ImGui_ImplSDL2_ProcessEvent(&event);
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			is_running_ = false;
			break;
		case SDL_CONTROLLERBUTTONDOWN:
			controller_.buttonState[event.cbutton.button] = true;
			break;
		case SDL_CONTROLLERBUTTONUP:
			controller_.buttonState[event.cbutton.button] = false;
			break;
		case SDL_CONTROLLERAXISMOTION:
			controller_.axisState[event.caxis.axis] = event.caxis.value;
		}
	}
}

void Game::update() {
}

void Game::imgui_render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(window_);
	ImGui::NewFrame();

	for (std::size_t i = 0; i < engine::CONTROLLER_BUTTON_LIST.size(); i++) {
		ImGuiHelper::Text("{}: {}",
		                  engine::to_string(
		                      engine::CONTROLLER_BUTTON_LIST.at(i)),
		                  controller_.buttonState.at(i));
	}

	for (std::size_t i = 0; i < engine::CONTROLLER_AXIS_LIST.size(); i++) {
		ImGuiHelper::Text("{}: {}",
		                  engine::to_string(
		                      engine::CONTROLLER_AXIS_LIST.at(i)),
		                  controller_.axisState.at(i));
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