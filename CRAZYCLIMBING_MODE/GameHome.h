#pragma once

#include "SDL.h"

class Home : public PhaseInterface
{
public:
	Home();
	~Home();
	virtual void HandleEvents();
	virtual void Update();
	virtual void Render();

private:
	Mix_Chunk* btn_sound;
	Mix_Music* home_bgm;

	//Background
	SDL_Rect g_bg_source_rect;
	SDL_Rect g_bg_destination_rect;
	SDL_Texture* g_bg_texture;

	// Mode1_Button
	SDL_Texture* texture_m1;
	SDL_Rect source_rectangle_m1;
	SDL_Rect destination_rectangle_m1;

	// Mode2_Button
	SDL_Texture* texture_m2;
	SDL_Rect source_rectangle_m2;
	SDL_Rect destination_rectangle_m2;

	// Mode3_Button
	SDL_Texture* texture_m3;
	SDL_Rect source_rectangle_m3;
	SDL_Rect destination_rectangle_m3;
};