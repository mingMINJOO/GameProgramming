#pragma once

#include <iostream>
#include <string>
#include "SDL.h" 
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "SDL_image.h"

// Game Phases
const int PHASE_INTRO = 0;
const int PHASE_HOME = 1;
const int PHASE_MODE1 = 2;
const int PHASE_MODE2 = 3;
const int PHASE_MODE3 = 4;

void InitGame();
void ClearGame();

extern int g_current_game_phase;
extern bool g_flag_running;
extern SDL_Renderer* g_renderer;
extern SDL_Window* g_window;

class PhaseInterface
{
public:
	PhaseInterface() {};
	virtual ~PhaseInterface() {};

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

};