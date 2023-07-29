#include "gamefunc.h"


bool g_flag_running;
SDL_Window* g_window;
Uint32 g_last_time_ms;
SDL_Renderer* g_renderer;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	//Mix_OpenAudio(44100, AUDIO_S16SYS, 2, 4096);
	//Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096);


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
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}