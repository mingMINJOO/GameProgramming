#include "gamefunc.h"
#include "SDL_image.h"

bool g_flag_running;
SDL_Window* g_window;
Uint32 g_last_time_ms;
SDL_Renderer* g_renderer;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	g_window = SDL_CreateWindow("Ascii_Airplane", 100, 100, 800, 600, 0);

	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();

	g_last_time_ms = SDL_GetTicks();


	while (g_flag_running) {
		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;
		HandleEvents();
		Update();
		Render();

		g_last_time_ms = cur_time_ms;
	}

	ClearGame();
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	ClearGame();
	SDL_Quit();

	return 0;
}