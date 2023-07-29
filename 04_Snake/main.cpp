#include "Gamefunc.h"
#include "snake.h"

SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

int speed;

int main(int argc, char* argv[]) {
	SDL_Init(SDL_INIT_EVERYTHING);
	InitGame();
	TTF_Init();

	g_window = SDL_CreateWindow("SNAKE GAME", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	Snake snake; // Snake °´Ã¼ »ý¼º

	g_flag_running = true;
	Uint32 cur_time_ms = SDL_GetTicks();
	speed = 80;
	int last_score = 0;

	while (g_flag_running)
	{
		snake.HandleEvents();
		snake.Update();
		snake.Render();
		snake.HandleEvents();
	}
	g_last_time_ms = cur_time_ms;

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();

	return 0;
}