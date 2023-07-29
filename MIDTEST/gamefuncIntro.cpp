#include "gamefunc.h"
#include "gamefuncIntro.h"
#include <windows.h>

using namespace std;

static SDL_Texture* g_texture_intro;
static SDL_Rect g_source_rectangle_intro;
static SDL_Rect g_destination_rectangle_intro;

//스타트 버튼
SDL_Rect g_start_button;

//스타트 글씨
SDL_Texture* g_start;
SDL_Rect g_start_rect;

//게임제목글씨
SDL_Texture* g_title;
SDL_Rect g_title_rect;

Intro::Intro() {
	//For Texture
	SDL_Surface* temp_surface = IMG_Load("../Resources/INTRO.png");
	g_texture_intro = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_intro, NULL, NULL, &g_source_rectangle_intro.w, &g_source_rectangle_intro.h);
	g_destination_rectangle_intro = { 0, 0, 810, 700 };
	source_rectangle_intro_ = { 0, 0, 500, 720 };

	//스타트 버튼
	g_start_button = { 300, 230, 200, 70 }; 

	//스타트 폰트
	TTF_Font* start = TTF_OpenFont("../resources/DungGeunMo.ttf", 50);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* start_surface = TTF_RenderUTF8_Blended(start, "START", black);
	g_start = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	g_start_rect = { 0, 0, start_surface->w, start_surface->h };

	//제목 폰트
	TTF_Font* title = TTF_OpenFont("../resources/DungGeunMo.ttf", 70);
	SDL_Color blue = { 37, 50, 120, 0 };
	SDL_Surface* title_surface = TTF_RenderUTF8_Blended(title, "Shooting Plane", blue);
	g_title = SDL_CreateTextureFromSurface(g_renderer, title_surface);
	g_title_rect = { 0, 0, title_surface->w, title_surface->h };

	//폰트메모리해제
	SDL_FreeSurface(start_surface);
	SDL_FreeSurface(title_surface);
	TTF_CloseFont(start);
	TTF_CloseFont(title);
	system("cls");
}

void Intro::Update() {

}

void Intro::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_texture_intro, &g_source_rectangle_intro, &g_destination_rectangle_intro);
	SDL_RenderPresent(g_renderer);

	// 스타트버튼
	{
		SDL_SetRenderDrawColor(g_renderer, 62, 72, 204, 0);
		SDL_RenderFillRect(g_renderer, &g_start_button);
	}

	//스타트 폰트위치
	SDL_Rect tmp_r;
	tmp_r.x = 340;
	tmp_r.y = 238;
	tmp_r.w = g_start_rect.w;
	tmp_r.h = g_start_rect.h;
	SDL_RenderCopy(g_renderer, g_start, &g_start_rect, &tmp_r);

	//제목 폰트위치
	SDL_Rect tmp_r2;
	tmp_r2.x = 160;
	tmp_r2.y = 110;
	tmp_r2.w = g_title_rect.w;
	tmp_r2.h = g_title_rect.h;
	SDL_RenderCopy(g_renderer, g_title, &g_title_rect, &tmp_r2);

	SDL_RenderPresent(g_renderer);
}

void Intro::HandleEvents() {
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			//if the mouse left button is pressed
			if (event.button.button == SDL_BUTTON_LEFT) {

				// Get the cursor's x position.
				int mouse_x = event.button.x;
				int mouse_y = event.button.y;

				if (mouse_x > g_start_button.x &&
					mouse_y > g_start_button.y &&
					mouse_x < g_start_button.x + g_start_button.w &&
					mouse_y < g_start_button.y + g_start_button.h
					)
				g_current_game_phase = PHASE_STAGE1;
			}
			break;

		default:
			break;
		}
	}
}

void Intro::Clear() {
	SDL_DestroyTexture(g_texture_intro);
}