#include "game.hpp"
#include "SDL2/SDL_image.h"

Game::Game() {
}
Game::~Game() {
}

void Game::UpdateGame() {
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 1))
		;
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	std::cout << " FPS : " << static_cast<int>(1.0 / deltaTime) << std::endl;
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();
}

void Game::EnttUpdatePosition() {
	//static auto start = std::chrono::system_clock::now();
	auto view = registry.view<Position, Velocity>();
	// use forward iterators and get only the components of interest
	//for (auto entity : view) {
	view.each([&](auto &pos, auto &vel) {
		//	Velocity &vel = view.get<Velocity>(entity);
		//	Position &pos = view.get<Position>(entity);

		//Texture &tex = view.get<Texture>(entity);
		pos.x += vel.dx;
		pos.y += vel.dy;

		if (pos.y > 1080.f || pos.y < 0.f)
			vel.dy = -vel.dy;
	});
}

void Game::UpdatePosition() {
}

void Game::EnttDraw() {
	SDL_SetRenderDrawColor(sdl_render, 0, 0, 0, 255);
	SDL_RenderClear(sdl_render);

	auto view = registry.view<Position, Texture>();
	// use forward iterators and get only the components of interest
	//for (auto entity : view) {

	view.each([&](auto &pos, auto &tex) {
		//Position &pos = view.get<Position>(entity);
		//Texture &tex = view.get<Texture>(entity);

		SDL_Rect r;
		r.w = 38;
		r.h = 38;
		r.x = static_cast<int>(pos.x - r.w / 2);
		r.y = static_cast<int>(pos.y - r.h / 2);
		SDL_RenderCopyEx(sdl_render,
				tex.texture, nullptr, &r,
				0.0, nullptr, SDL_FLIP_NONE);
	});

	SDL_RenderPresent(sdl_render);
}

void Game::Draw() {
	SDL_SetRenderDrawColor(sdl_render, 0, 0, 0, 255);
	SDL_RenderClear(sdl_render);

	//TODO
	for (auto &s : sprites) {
		s.pos.x += s.vel.dx;
		s.pos.y += s.vel.dy;

		if (s.pos.y > 1080.f || s.pos.y < 0.f)
			s.vel.dy = -s.vel.dy;

		SDL_Rect r;
		r.w = 38;
		r.h = 38;
		r.x = static_cast<int>(s.pos.x - r.w / 2);
		r.y = static_cast<int>(s.pos.y - r.h / 2);
		SDL_RenderCopyEx(sdl_render,
				s.tex, nullptr, &r,
				0.0, nullptr, SDL_FLIP_NONE);
	}

	SDL_RenderPresent(sdl_render);
}

void Game::EnttCreateEntities() {
	for (auto i = 0; i < CubeNum; ++i) {
		const auto entity = registry.create();
		registry.emplace<Position>(entity, get_random_float() * 1920.f, get_random_float() * 1080.f);
		registry.emplace<Velocity>(entity, 0.f, get_random_float() * 10.f + 1.f);
		registry.emplace<Texture>(entity, GetTexture("Assets/icon.png"));
	}
}

void Game::CreateEntities() {
	for (auto i = 0; i < CubeNum; ++i) {
		Sprite *s = new Sprite();
		s->pos.x = get_random_float() * 1920.f;
		s->pos.y = get_random_float() * 1080.f;
		s->vel.dx = 0.f;
		s->vel.dy = get_random_float() * 10.f + 1.f;
		s->tex = GetTexture("Assets/icon.png");
		sprites.push_back(*s);
	}
}

SDL_Texture *Game::GetTexture(const std::string &fileName) {
	SDL_Texture *tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end()) {
		tex = iter->second;
	} else {
		// Load from file
		SDL_Surface *surf = IMG_Load(fileName.c_str());
		if (!surf) {
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(sdl_render, surf);
		SDL_FreeSurface(surf);
		if (!tex) {
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}

void Game::EnttGenerateOutput() {
	EnttUpdatePosition();
	EnttDraw();
}

void Game::GenerateOutput() {
	//UpdatePosition();
	Draw();
}

void Game::RunLoop() {
	while (mGameState != EQuit) {
		ProcessInput();
		UpdateGame();
		if (bUseEntt) {
			EnttGenerateOutput();
		} else {
			GenerateOutput();
		}
	}
}

void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				mGameState = EQuit;
				break;
			default:
				break;
		}
	}
}

void Game::Shutdown() {
	SDL_DestroyRenderer(sdl_render);
	SDL_DestroyWindow(sdl_window);
	SDL_Quit();
}

void Game::Init(const std::string &title, int x, int y, int width, int height) {
	SDL_Init(SDL_INIT_EVERYTHING);
	sdl_window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_SHOWN);
	sdl_render = SDL_CreateRenderer(sdl_window, -1, 0);
	assert(sdl_window != nullptr);
	mTicksCount = SDL_GetTicks();
	if (bUseEntt) {
		std::cout << "USE entt" << std::endl;
		EnttCreateEntities();
	} else {
		std::cout << "not USE entt" << std::endl;
		CreateEntities();
	}
}
