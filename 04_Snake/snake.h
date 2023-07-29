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
	SDL_Texture* snake_texture; // �� ���� ���� ��
	SDL_Rect snake_dest; // �� ���� ��ġ
	SDL_Rect snake_rect; // �� �׸����� �߶�� �簢��

	// ����
	vector<SDL_Texture*> food_textures;
	SDL_Texture* food_texture;
	SDL_Rect food_dest;
	SDL_Rect food_rect;
	bool food;

private:
	const int WIDTH = 30;
	const int HEIGHT = 30;

	//���
	SDL_Rect bg_dest_rect; // ���
	SDL_Rect bg_source_rect; // ��� �߶�� ���� �簢��
	SDL_Texture* bg_texture; //��� ������� ��

	//Ready
	SDL_Texture* ready_texture;
	SDL_Rect ready_rect; // ��� �߶�� ���� �簢��
	SDL_Rect ready_dest; // ���

	//Gameover
	SDL_Texture* Gameover_texture;
	SDL_Rect Gameover_rect; // ��� �߶�� ���� �簢��
	SDL_Rect Gameover_dest; // ���

	//score
	SDL_Texture* g_scoreN_kr;
	SDL_Rect g_scoreN_kr_rect;

	//���� :
	SDL_Texture* g_score_kr;
	SDL_Rect g_score_kr_rect;

	int score;

	int ch_x;
	int ch_y;

	// ��ġ
	int food_x, food_y;
	int snake_x, snake_y;
};

