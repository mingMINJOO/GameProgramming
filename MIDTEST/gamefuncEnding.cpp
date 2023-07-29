#include "gamefunc.h"
#include "gamefuncEnding.h"

static SDL_Texture* g_texture_ending;
static SDL_Rect g_source_rectangle_ending;
static SDL_Rect g_destination_rectangle_ending;

//다시시작 버튼
SDL_Rect g_retry_button;

//다시시작 글씨
SDL_Texture* g_retry;
SDL_Rect g_retry_rect;

//게임오버 글씨
SDL_Texture* g_gameover;
SDL_Rect g_gameover_rect;

Ending::Ending() {
	//For Texture
	SDL_Surface* temp_surface = IMG_Load("../Resources/OUTRO.jpeg");
	g_texture_ending = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
	SDL_FreeSurface(temp_surface);

	SDL_QueryTexture(g_texture_ending, NULL, NULL, &g_source_rectangle_ending.w, &g_source_rectangle_ending.h);

	g_source_rectangle_ending = { 0, 0, 700, 500 };
	g_destination_rectangle_ending = { 0, 0, 800, 600 };

	//다시시작 버튼
	g_retry_button = { 300, 370, 200, 70 };

	//다시시작 폰트
	TTF_Font* retry = TTF_OpenFont("../resources/DungGeunMo.ttf", 50);
	SDL_Color white = { 255, 255, 255, 0 };
	SDL_Surface* retry_surface = TTF_RenderUTF8_Blended(retry, "RETRY", white);
	g_retry = SDL_CreateTextureFromSurface(g_renderer, retry_surface);
	g_retry_rect = { 0, 0, retry_surface->w, retry_surface->h };

	//gameover 폰트
	TTF_Font* gameover = TTF_OpenFont("../resources/DungGeunMo.ttf", 80);
	SDL_Color red = { 255, 0, 0, 0 };
	SDL_Surface* gameover_surface = TTF_RenderUTF8_Blended(gameover, "GAME OVER", red);
	g_gameover = SDL_CreateTextureFromSurface(g_renderer, gameover_surface);
	g_gameover_rect = { 0, 0, gameover_surface->w, gameover_surface->h };

	//폰트메모리해제
	SDL_FreeSurface(retry_surface);
	SDL_FreeSurface(gameover_surface);
	TTF_CloseFont(gameover);
	system("cls");
}

Ending::~Ending() {
	SDL_DestroyTexture(texture_ending_);
}

void Ending::Update() {

}

void Ending::Render() {
	SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
	SDL_RenderClear(g_renderer);

	SDL_RenderCopy(g_renderer, g_texture_ending, &g_source_rectangle_ending, &g_destination_rectangle_ending);
	SDL_RenderPresent(g_renderer);

	// 다시시작 버튼
	{
		SDL_SetRenderDrawColor(g_renderer, 62, 72, 204, 0);
		SDL_RenderFillRect(g_renderer, &g_retry_button);
	}

	//다시시작 폰트위치
	SDL_Rect tmp_r;
	tmp_r.x = 338;
	tmp_r.y = 377;
	tmp_r.w = g_retry_rect.w;
	tmp_r.h = g_retry_rect.h;
	SDL_RenderCopy(g_renderer, g_retry, &g_retry_rect, &tmp_r);

	//gameover 폰트위치
	SDL_Rect tmp_r2;
	tmp_r2.x = 210;
	tmp_r2.y = 85;
	tmp_r2.w = g_gameover_rect.w;
	tmp_r2.h = g_gameover_rect.h;
	SDL_RenderCopy(g_renderer, g_gameover, &g_gameover_rect, &tmp_r2);

	SDL_RenderPresent(g_renderer);

}

void Ending::HandleEvents() {
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

				if (mouse_x > g_retry_button.x &&
					mouse_y > g_retry_button.y &&
					mouse_x < g_retry_button.x + g_retry_button.w &&
					mouse_y < g_retry_button.y + g_retry_button.h
					)
					g_current_game_phase = PHASE_INTRO;

			}
			break;

		default:
			break;
		}
	}
}


void Ending::Clear() {

}