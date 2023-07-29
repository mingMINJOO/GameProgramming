#include "GAMEFUNC.h"

bool g_flag_running;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("Ascii_Airplane", 100, 100, 800, 600, 0);

	InitGame();

	while (g_flag_running) {
		HandleEvents();
		Update();
		Render();

		SDL_Delay(30);
	}

	ClearGame();
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}