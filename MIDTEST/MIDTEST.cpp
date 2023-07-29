#include "SDL.h"
#include <iostream>
#include "gamefunc.h"
#include "gamefuncIntro.h"
#include "gamefuncStage1.h"
#include "gamefuncEnding.h"

using namespace std;

bool g_flag_running;
SDL_Window* g_window;
Uint32 g_last_time_ms;
SDL_Renderer* g_renderer;

//게임 페이즈
int g_current_game_phase;

int main(int argc, char* argv[]) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();

	if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		cout << "Mix_OpenAudio " << Mix_GetError << endl;
		exit(2);
	}
	  
	g_window = SDL_CreateWindow("Ascii_Airplane", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();
	PhaseInterface* game_phases[3];
	game_phases[PHASE_INTRO] = new Intro;
	game_phases[PHASE_STAGE1] = new Stage1;
	game_phases[PHASE_ENDING] = new Ending;

	g_current_game_phase = PHASE_INTRO;

	g_last_time_ms = SDL_GetTicks();

	while (g_flag_running) {
		Uint32 cur_time_ms = SDL_GetTicks();
		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;
	}

	ClearGame();

	for (int i = 0; i < 3; i++)
	{
		delete game_phases[i];
	}

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}