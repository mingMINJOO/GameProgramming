#include "Gamefunc.h"
#include "snake.h"
#include <windows.h>
#include <queue>
#include "SDL.h"
#include <atlstr.h>

Snake::Snake()
{
	srand(time(NULL));

	// For Character
	ch_x = 400, ch_y = 300;
	score = 0;

	//배경 이미지로드
	SDL_Surface* bg_surface = IMG_Load("../Resources/bg1.jpg");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface);
	bg_source_rect = { 0, 0, 600, 900 };
	bg_dest_rect = { 0, 0, 800, 600 };

	//snake 이미지로드
	SDL_Surface* snake_surface = IMG_Load("../Resources/snake.png");
	snake_texture = SDL_CreateTextureFromSurface(g_renderer, snake_surface);
	SDL_FreeSurface(snake_surface);
	snake_rect = { 0, 0, 402, 402 };
	snake.push_front({ ch_x, ch_y, WIDTH, HEIGHT });

	// food 이미지로드
	vector<string> foodPaths = { "../Resources/food1.png", "../Resources/food2.png", "../Resources/food3.png", "../Resources/food4.png", "../Resources/food5.png", "../Resources/food6.png" };
	for (const auto& path : foodPaths) {
		SDL_Surface* food_surface = IMG_Load(path.c_str());
		SDL_Texture* food_texture = SDL_CreateTextureFromSurface(g_renderer, food_surface);
		SDL_FreeSurface(food_surface);
		food_textures.push_back(food_texture);
	}
	food_rect = { 0, 0, 600, 480 };

	//Ready 이미지로드
	SDL_Surface* ready_surface = IMG_Load("../Resources/Ready.png");
	SDL_SetSurfaceAlphaMod(ready_surface, 200); // 투명도 값을 설정 (0~255 범위, 0이 완전 투명, 255가 완전 불투명)
	ready_texture = SDL_CreateTextureFromSurface(g_renderer, ready_surface);
	SDL_FreeSurface(ready_surface);
	ready_rect = { 0, 0, 600, 600 };
	ready_dest = { 265, 160, 270, 270 };

	//Gameover 이미지로드
	SDL_Surface* Gameover_surface = IMG_Load("../Resources/Gameover.png");
	Gameover_texture = SDL_CreateTextureFromSurface(g_renderer, Gameover_surface);
	SDL_FreeSurface(Gameover_surface);
	Gameover_rect = { 0, 0, 623, 580 };
	Gameover_dest = { 270, 155, 270, 270 };

	//폰트
	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 30);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, CW2A(L"길이 : ", CP_UTF8), black);

	//점수:
	g_score_kr_rect.x = 0;
	g_score_kr_rect.y = 0;
	g_score_kr_rect.w = tmp_surface->w;
	g_score_kr_rect.h = tmp_surface->h;

	g_score_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	food = false;
	GenerateFood(); // 음식 랜덤 생성
	printscore(0);

	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font1);
}

void Snake::printscore(int score) {
	string now_score = to_string(score);

	TTF_Font* font1 = TTF_OpenFont("../Resources/DungGeunMo.ttf", 30);
	string text = now_score;
	SDL_Color red = { 255, 0, 0, 0 }; //RGB, 투명도
	SDL_Surface* tmp_surface2 = TTF_RenderUTF8_Blended(font1, text.c_str(), red);

	//score
	g_scoreN_kr_rect.x = 0;
	g_scoreN_kr_rect.y = 0;
	g_scoreN_kr_rect.w = tmp_surface2->w;
	g_scoreN_kr_rect.h = tmp_surface2->h;
	g_scoreN_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);

	SDL_FreeSurface(tmp_surface2);
}

void Snake::GenerateFood()
{
	// 음식 위치 랜덤 생성
	food_x = rand() % 750;
	food_y = rand() % 550;

	if (food == false) {
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == food_x && (*iter).y == food_y) {
				food_x = rand() % 950 + 10;
				food_y = rand() % 550 + 10;
			}
			else continue;
		}
		food_dest = { food_x, food_y, WIDTH + 10, HEIGHT + 10 };
		food = true;
	}
	// 랜덤한 음식 선택
	int randomIndex = rand() % food_textures.size();
	food_texture = food_textures[randomIndex];
}


Snake::~Snake()
{
	SDL_RenderClear(g_renderer);
	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(snake_texture);
	SDL_DestroyTexture(ready_texture);
	SDL_DestroyTexture(Gameover_texture);
}

void Snake::Reset()
{
	start = false;
	ch_left = false;
	ch_right = false;
	ch_up = false;
	ch_down = false;

	printscore(0);
	score = 0;

	SDL_RenderCopy(g_renderer, ready_texture, &ready_rect, &ready_dest);
	snake.clear();
	ch_x = 485, ch_y = 285;
	snake.push_front({ ch_x, ch_y, WIDTH, HEIGHT });

	gameover = false;

	SDL_RenderCopy(g_renderer, bg_texture, &bg_source_rect, &bg_dest_rect);

	food = false;
	GenerateFood(); // 음식 재생성

	SDL_RenderCopy(g_renderer, food_texture, &food_rect, &food_dest);
	SDL_RenderCopy(g_renderer, snake_texture, &snake_rect, &(snake.front()));
	
}

void Snake::Update()
{
	if (gameover) {
		return;
	}

	static int updateCounter = 0;  // Counter to control snake movement speed
	const int movementDelay = 60; // Delay between each movement update

	if (updateCounter >= movementDelay) {
		updateCounter = 0;

		//움직임
		if (ch_left) {
			snake_x = -10;
			snake_y = 0;
		}
		else if (ch_right) {
			snake_x = 10;
			snake_y = 0;
		}
		else if (ch_up) {
			snake_x = 0;
			snake_y = -10;
		}
		else if (ch_down) {
			snake_x = 0;
			snake_y = 10;
		}
		else {
			snake_x = 0;
			snake_y = 0;
		}

		int new_x = snake.front().x + snake_x;
		int new_y = snake.front().y + snake_y;

		// 뱀 item check
		if ((snake.front().x >= food_dest.x - 10) && (snake.front().x <= food_dest.x + 20)
			&& (snake.front().y >= food_dest.y - 10) && (snake.front().y <= food_dest.y + 20)) {
			snake.push_front({ snake.front().x + snake_x, snake.front().y + snake_y, WIDTH, HEIGHT });

			score += 1;
			printscore(score);
			food = false;
			GenerateFood(); // Generate new random food
		}

		// 화면 끝에 닿으면 게임오버
		if ((snake.front().x < 0) || (snake.front().x > 760) || (snake.front().y < 0) || (snake.front().y > 560)) {
			gameover = true;
		}
		snake.push_front({ snake.front().x + snake_x , snake.front().y + snake_y, WIDTH, HEIGHT });

		// 음식먹기
		if ((snake.front().x >= food_rect.x - 10) && (snake.front().x <= food_rect.x + 20)
			&& (snake.front().y >= food_rect.y - 10) && (snake.front().y <= food_rect.y + 20)) {
			snake.push_front({ snake.front().x + snake_x, snake.front().y + snake_y, WIDTH, HEIGHT });

			score += 1;
			printscore(score);
			
			food = false;
			GenerateFood(); // Generate new random food
		}
		else {
			snake.pop_back();
		}

		// 몸에 닿으면 게임오버
		int head_x = snake.front().x, head_y = snake.front().y;
		for (auto iter = ++snake.begin(); iter != snake.end(); iter++) {
			if ((*iter).x == head_x && (*iter).y == head_y) {
				gameover = true;
			}
		}
	}
	else {
		updateCounter++;
	}
}

void Snake::Render()
{
	// 배경 
	SDL_RenderCopy(g_renderer, bg_texture, &bg_source_rect, &bg_dest_rect); // clear the renderer to the draw color

	// snake
	for (auto iter = snake.begin(); iter != snake.end(); iter++) {
		SDL_RenderCopy(g_renderer, snake_texture, &snake_rect, &(*iter));
	}

	//음식
	if (food) {
		SDL_RenderCopy(g_renderer, food_texture, &food_rect, &food_dest);
	}

	//점수 : (위치)
	SDL_Rect tmp_r;
	tmp_r.x = 15;
	tmp_r.y = 15;
	tmp_r.w = g_score_kr_rect.w;
	tmp_r.h = g_score_kr_rect.h;
	SDL_RenderCopy(g_renderer, g_score_kr, &g_score_kr_rect, &tmp_r);

	//score (위치)
	SDL_Rect tmp_r2;
	tmp_r2.x = 130;
	tmp_r2.y = 16;
	tmp_r2.w = g_scoreN_kr_rect.w;
	tmp_r2.h = g_scoreN_kr_rect.h;
	SDL_RenderCopy(g_renderer, g_scoreN_kr, &g_scoreN_kr_rect, &tmp_r2);

	//레디
	if (!start) {
		SDL_RenderCopy(g_renderer, ready_texture, &ready_rect, &ready_dest);
		SDL_RenderPresent(g_renderer);
		return;
	}
	//게임오버
	if (gameover){
		SDL_RenderCopy(g_renderer, Gameover_texture, &Gameover_rect, &Gameover_dest);
	}

	SDL_RenderPresent(g_renderer); // draw to the screen
}


void Snake::HandleEvents()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (!start) {
				start = true;
			}

			if (event.key.keysym.sym == SDLK_LEFT) {
				ch_left = true;
				ch_right = false;
				ch_up = false;
				ch_down = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				ch_left = false;
				ch_right = true;
				ch_up = false;
				ch_down = false;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				ch_left = false;
				ch_right = false;
				ch_up = true;
				ch_down = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				ch_left = false;
				ch_right = false;
				ch_up = false;
				ch_down = true;
			}
			break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) {
					if (gameover) {
						start = true;
						Reset();
					}
				}
		default:
			break;
		}
	}
}