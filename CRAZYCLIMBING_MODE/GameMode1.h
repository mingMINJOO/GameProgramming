#pragma once

#include "SDL.h"

class Mode1 : public PhaseInterface
{
public:
	Mode1();
	~Mode1();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
	void userMove();
	void holdMove();
	bool checkHold();
	void ResetGame();
	//void stun_effect();

private:


	// 배경 이미지 크기
	const int BACKGROUND_WIDTH = 800;
	const int BACKGROUND_HEIGHT = 1800;

	const int WALL_WIDTH = 400;
	const int WALL_HEIGHT = 5400;


	//인트로 (tuto)
	SDL_Texture* g_texture_intro;
	SDL_Rect g_source_rectangle_intro;
	SDL_Rect g_destination_rectangle_intro;

	//플레이버튼
	SDL_Texture* g_texture_play;
	SDL_Rect g_source_rectangle_play;
	SDL_Rect g_destination_rectangle_play;

	//ready
	SDL_Surface* ready_surface;
	SDL_Texture* ready_texture;
	SDL_Rect ready_rect;
	SDL_Rect ready_dest_rect;

	// start
	SDL_Surface* start_surface;
	SDL_Texture* start_texture;
	SDL_Rect start_rect;
	SDL_Rect start_dest_rect;

	// introBack button
	SDL_Surface* introBack_surface;
	SDL_Texture* introBack_texture;
	SDL_Rect introBack_rect;
	SDL_Rect introBack_dest_rect;

	// bg
	SDL_Surface* bg_surface;
	SDL_Texture* bg_texture;
	SDL_Rect bg_rect;
	SDL_Rect bg_dest_rect;
	int backgroundY; // 배경 이미지의 Y 좌표

	// wall
	SDL_Surface* wall_surface;
	SDL_Texture* wall_texture;
	SDL_Rect wall_rect;
	SDL_Rect wall_dest_rect;
	int wallY;

	// timeBg
	SDL_Surface* timeBg_surface;
	SDL_Texture* timeBg_texture;
	SDL_Rect timeBg_rect;
	SDL_Rect timeBg_dest_rect;

	// time
	TTF_Font* font;
	SDL_Surface* time_surface;
	SDL_Texture* time_texture;
	SDL_Rect time_rect;


	TTF_Font* font2;
	SDL_Surface* time2_surface;
	SDL_Texture* time2_texture;
	SDL_Rect time2_rect;

	int leftHoldY = 475; //원래 150 차이여서 75 차이 현재는 200 차이니까 100차이나게
	int rightHoldY = 375;

	// leftUser
	SDL_Surface* leftUser_surface;
	SDL_Texture* leftUser_texture;
	SDL_Rect leftUser_rect;
	SDL_Rect leftUser_dest_rect;

	// rightUser
	SDL_Surface* rightUser_surface;
	SDL_Texture* rightUser_texture;
	SDL_Rect rightUser_rect;
	SDL_Rect rightUser_dest_rect;

	// stun 효과
	SDL_Surface* stun_surface;
	SDL_Texture* stun_texture;
	SDL_Rect stun_rect;
	SDL_Rect stun_dest_rect;

	// ending BG
	SDL_Texture* g_texture_ending;
	SDL_Rect g_source_rectangle_ending;
	SDL_Rect g_destination_rectangle_ending;

	// ending home button
	SDL_Texture* g_texture_home;
	SDL_Rect g_source_rectangle_home;
	SDL_Rect g_destination_rectangle_home;

	// ending retry button
	SDL_Texture* g_texture_retry;
	SDL_Rect g_source_rectangle_retry;
	SDL_Rect g_destination_rectangle_retry;

	// 배경 음악
	Mix_Music* bg_mus;
	// jump wav
	Mix_Chunk* jump_wav;
	// btn
	Mix_Chunk* btn_wav;
	// game clear wav
	Mix_Chunk* gameClear_wav;
	//readyStart
	Mix_Chunk* ready_sound;


	int hold[41]; // 1:down 2:left 3: right 4: up
	int f_state; // 1:down 2:left 3: right 4: up
	bool isLeftUser = true;

	int prevHoldIndex = -1;

	Uint32 startTime = 0;
	Uint32 gameoverTime = 0;

	Uint32 startsTime;



	int cur_i;
	int prevHold;
	bool tutorial;
	bool ready;
	bool start;
	bool game_start;
	bool game_over;
	bool game_ending;

};