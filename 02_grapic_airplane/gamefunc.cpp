#include "gamefunc.h"
#include <windows.h>
#include <queue>
#include "SDL.h"
#include "SDL_image.h"
using namespace std;

int g_input;
int g_elapsed_time_ms;

//비행기
int f_state;
int f_x;
int f_y;
string f_output;

//미사일
int m_state;
int m_x;
int m_y;
string m_output;


//미사일 배열의 인덱스
bool bullet[30];
int cnt;
short m_pos[30][2];


SDL_Rect g_destination_rect; // 비행기 위치
SDL_Rect g_source_rect; // 비행기 잘라올 곳의 사각형
SDL_Texture* g_airplane_texture; // 비행기 복사받을 곳

SDL_Rect g_bullet_destination_rect[30]; // 미사일의 현재 위치
SDL_Rect g_bullet_source_rect; // 미사일 잘라올 곳의 사각형
SDL_Texture* g_bullet_texture; //미사일 복사받을 곳

SDL_Rect g_bg_destination_rect; // 배경
SDL_Rect g_bg_source_rect; // 배경 잘라올 곳의 사각형
SDL_Texture* g_bg_texture; //배경 복사받을 곳


//프로그램 시작 시 처음 한번 실행되는 함수
void InitGame() {

	g_input = 0;
	g_elapsed_time_ms = 0;
	g_flag_running = true;

	cnt = 0;


	//비행기그림
	SDL_Surface* airplane_surface = IMG_Load("../resources/airplane_image.png");
	// SDL_SetColorKey(airplane_surface, SDL_TRUE, SDL_MapRGB(airplane_surface->format, 0, 0, 0)); //옆 배경 투명색으로
	g_airplane_texture = SDL_CreateTextureFromSurface(g_renderer, airplane_surface);
	SDL_FreeSurface(airplane_surface);

	g_source_rect = { 0, 0, 512, 512 };
	g_destination_rect = { 200, 500, 60, 50 };

	//배경그림
	SDL_Surface* bg_surface = IMG_Load("../resources/bg.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface); //필요없울듯??!

	g_bg_source_rect = { 0, 0, 600, 900 };
	g_bg_destination_rect = { 0, 0, 800, 600 };

	//미사일
	g_bullet_source_rect = { 0, 0, 640, 1280 };

	SDL_Surface* bullet_surface = IMG_Load("../resources/bullet.png");
	g_bullet_texture = SDL_CreateTextureFromSurface(g_renderer, bullet_surface);
	SDL_FreeSurface(bullet_surface);
	system("cls");
}

void Update() {
	if (f_state == 1) {
		g_destination_rect.x -= 10;
	}
	else if (f_state == 2) {
		g_destination_rect.x += 10;
	}
	else if (f_state == 3) {
		g_destination_rect.y -= 10;
	}
	else if (f_state == 4) {
		g_destination_rect.y += 10;
	}
	else {
		g_destination_rect.x = g_destination_rect.x;
		g_destination_rect.y = g_destination_rect.y;
	}

	//범위바깥으로 나가지못하게하기
	if (g_destination_rect.x > 740)
		g_destination_rect.x = 740;
	else if (g_destination_rect.x < 0)
		g_destination_rect.x = 0;

	if (g_destination_rect.y > 550)
		g_destination_rect.y = 550;
	else if (g_destination_rect.y<0)
		g_destination_rect.y = 0;

	g_elapsed_time_ms += 33;
}

void Render() {
	//배경
	/*SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderClear(g_renderer);*/

	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

	//비행기
	/*SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(g_renderer, &g_char_pos);*/

	//airplane_texture
	SDL_RenderCopy(g_renderer, g_airplane_texture, &g_source_rect, &g_destination_rect);


	// 미사일 그리기
	for (int i = 0; i < 30; i++) {
		if (bullet[i]) {
			if (g_bullet_destination_rect[i].y < 0) bullet[i] = false;

			g_bullet_destination_rect[i].y -= 10;
			SDL_RenderCopy(g_renderer, g_bullet_texture, &g_bullet_source_rect, &g_bullet_destination_rect[i]);
		}
	}
	SDL_RenderPresent(g_renderer);
}

void HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				f_state = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				f_state = 2;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				f_state = 3;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				f_state = 4;
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				bullet[cnt] = true;
				g_bullet_destination_rect[cnt] = { g_destination_rect.x, g_destination_rect.y - 50, 52, 52 };				
				m_pos[cnt][1] = f_y;
				cnt++;
				if (cnt > 29) cnt = 0;
			}
			break;


		case SDL_KEYUP:
			f_state = 0;
			break;

		default:
			break;

		}
	}
}

void ClearGame() {
	SDL_DestroyTexture(g_bg_texture);
	SDL_DestroyTexture(g_airplane_texture);
	SDL_DestroyTexture(g_bullet_texture);
}

