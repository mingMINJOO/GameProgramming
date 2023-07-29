#pragma once
#include "Gamefunc.h"

class Snake
{
public:
	Snake();
	~Snake();

	void HandleEvents();
	void Update();
	void Render();
	void Reset();
	void GenerateFood();
	void printscore(int score);

	bool ch_left;
	bool ch_right;
	bool ch_up;
	bool ch_down;
	bool start;
	bool gameover;

	// snake
	list <SDL_Rect> snake;
	SDL_Texture* snake_texture; // 뱀 복사 받을 곳
	SDL_Rect snake_dest; // 뱀 현재 위치
	SDL_Rect snake_rect; // 뱀 그림에서 잘라올 사각형

	// 먹이
	vector<SDL_Texture*> food_textures;
	SDL_Texture* food_texture;
	SDL_Rect food_dest;
	SDL_Rect food_rect;
	bool food;

private:
	const int WIDTH = 30;
	const int HEIGHT = 30;

	//배경
	SDL_Rect bg_dest_rect; // 배경
	SDL_Rect bg_source_rect; // 배경 잘라올 곳의 사각형
	SDL_Texture* bg_texture; //배경 복사받을 곳

	//Ready
	SDL_Texture* ready_texture;
	SDL_Rect ready_rect; // 배경 잘라올 곳의 사각형
	SDL_Rect ready_dest; // 배경

	//Gameover
	SDL_Texture* Gameover_texture;
	SDL_Rect Gameover_rect; // 배경 잘라올 곳의 사각형
	SDL_Rect Gameover_dest; // 배경

	//score
	SDL_Texture* g_scoreN_kr;
	SDL_Rect g_scoreN_kr_rect;

	//점수 :
	SDL_Texture* g_score_kr;
	SDL_Rect g_score_kr_rect;

	int score;

	int ch_x;
	int ch_y;

	// 위치
	int food_x, food_y;
	int snake_x, snake_y;
};

