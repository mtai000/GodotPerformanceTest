#pragma once
#include "pch.hpp"
#include <vector>

class Game final {
private:
    void ProcessInput();
    void UpdateGame();
    void EnttGenerateOutput();
    void GenerateOutput();

    SDL_Window* sdl_window;
    SDL_Renderer* sdl_render;
    std::unordered_map<std::string, SDL_Texture*> mTextures;
	//SDL_Texture *tmpTex;
    entt::registry registry;

    enum GameState
    {
	    EGameplay,
	    EPaused,
	    EQuit
    };
    GameState mGameState;
    Uint32 mTicksCount;
    
    struct Position {
        float x;
        float y;
    };

    struct Velocity {
        float dx;
        float dy;
    };


    struct Texture{
        SDL_Texture* texture;
    };

    struct Scale{
        float scale;
    };

    struct Sprite{
        Position pos;
        Velocity vel;
        SDL_Texture* tex;
    };

    std::vector<Sprite> sprites;
    
public:
    Game();
    ~Game();
    bool bUseEntt = false;
    uint32_t CubeNum = 0;
    void EnttUpdatePosition();
    void EnttDraw();
    void EnttCreateEntities();

    void UpdatePosition();
    void Draw();
    void CreateEntities();

    void Init(const std::string& title, int x, int y, int width,int height);
    void RunLoop();
    void Shutdown();
    SDL_Texture* GetTexture(const std::string& filename);
};
