#pragma once
#include "Game.h"
#include <vector>

class Mode2 : public PhaseInterface {
public:
	Mode2();
	~Mode2();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
	void userMove();
	void holdMove();
	bool checkHold();
	void ResetGame();

private:
	Mix_Music* mode2_bgm; //mp3
	Mix_Chunk* jump_sound; // WAV 파일 로드
	Mix_Chunk* btn_sound;
	Mix_Chunk* mode2_gameover_bgm;
	Mix_Chunk* ready_sound;

	int cur_i;
	int prevHold;
	
	Uint32 startTime = 0;
	Uint32 gameoverTime = 0;

	//홀드갯수 폰트
	int holdCount = 0;

	// num
	TTF_Font* font;
	SDL_Surface* num_surface;
	SDL_Texture* num_texture;
	SDL_Rect num_rect;

	//인트로
	SDL_Texture* g_texture_intro;
	SDL_Rect g_source_rectangle_intro;
	SDL_Rect g_destination_rectangle_intro;

	//플레이버튼
	SDL_Texture* g_texture_play;
	SDL_Rect g_source_rectangle_play;
	SDL_Rect g_destination_rectangle_play;

	//뒤로가기버튼
	SDL_Surface* introBack_surface;
	SDL_Texture* introBack_texture;
	SDL_Rect introBack_rect;
	SDL_Rect introBack_dest_rect;

	//레디
	SDL_Surface* ready_surface;
	SDL_Texture* ready_texture;
	SDL_Rect ready_rect;
	SDL_Rect ready_dest_rect;

	//시작
	SDL_Surface* start_surface;
	SDL_Texture* start_texture;
	SDL_Rect start_rect;
	SDL_Rect start_dest_rect;

	// 배경 이미지 크기
	const int BACKGROUND_WIDTH = 800;
	const int BACKGROUND_HEIGHT = 3000;

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

	const int WALL_WIDTH = 400;
	const int WALL_HEIGHT = 600;

	// hold
	int leftHoldY = 475;
	int rightHoldY = 375;

	int hold[150]; // 1:red 2:green 3:blue
	int f_state; // 1:red 2: green 3:blue
	bool isLeftUser = true;
	int prevHoldIndex = -1;

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

	//게이지
	int gauge = 150; // 초기 게이지 값
	int gaugeDecreaseRate = 1; // 게이지 감소 속도
	int gaugeDecreaseRate2 = 2; //50개 지나면 게이지 감소 늘리기

	//엔딩사진
	SDL_Texture* g_texture_ending;
	SDL_Rect g_source_rectangle_ending;
	SDL_Rect g_destination_rectangle_ending;

	//홈버튼
	SDL_Texture* g_texture_home;
	SDL_Rect g_source_rectangle_home;
	SDL_Rect g_destination_rectangle_home;

	//다시시작버튼
	SDL_Texture* g_texture_retry;
	SDL_Rect g_source_rectangle_retry;
	SDL_Rect g_destination_rectangle_retry;

	bool tutorial;
	bool ready;
	bool start;
	bool game_start;
	bool game_over;
	bool game_ending;

	int currentCharacterIndex;
	bool correct_button;
};