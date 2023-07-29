
#include "Game.h"
#include "GameIntro.h"
#include "GameHome.h"
#include "GameMode1.h"
#include "GameMode2.h"
#include "GameMode3.h"

/////////////////////////////////////////////////
// Declaration
SDL_Window* g_window;
SDL_Renderer* g_renderer;
bool g_flag_running;
Uint32 g_last_time_ms;

// Game Phases
int g_current_game_phase;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();


	g_window = SDL_CreateWindow("First Window", 100, 100, 800, 600, 0);
	g_renderer = SDL_CreateRenderer(g_window, -1, 0);

	InitGame();

	PhaseInterface* game_phases[8];
	game_phases[0] = new Intro;
	game_phases[1] = new Home;
	game_phases[2] = new Mode1;
	game_phases[3] = new Mode2;
	game_phases[4] = new Mode3;

	g_current_game_phase = PHASE_INTRO;

	while (g_flag_running)
	{
		Uint32 cur_time_ms = SDL_GetTicks();

		if (cur_time_ms - g_last_time_ms < 33)
			continue;

		game_phases[g_current_game_phase]->HandleEvents();
		game_phases[g_current_game_phase]->Update();
		game_phases[g_current_game_phase]->Render();

		g_last_time_ms = cur_time_ms;


	}

	delete game_phases[0];
	delete game_phases[1];
	delete game_phases[2];
	delete game_phases[3];
	delete game_phases[4];

	ClearGame();

	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);

	Mix_CloseAudio();
	SDL_Quit();

	return 0;
}
