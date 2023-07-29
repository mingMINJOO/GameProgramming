#include "Game.h"
#include "GameMode1.h"
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;


// hold
vector<string> hold_paths = { "../../Resources/m1/downHold.png", "../../Resources/m1/leftHold.png", "../../Resources/m1/rightHold.png", "../../Resources/m1/upHold.png" };
vector<SDL_Surface*> hold_surfaces;
vector<SDL_Texture*> hold_textures;
vector<SDL_Rect> hold_rects;
vector<SDL_Rect> hold_dest_rects;

string a;
string nextHoldPath = "";

Mode1::Mode1() {
	g_flag_running = true;
	cur_i = 1;
	prevHold = 0;

	// state
	tutorial = true;
	ready = false;
	start = false;
	game_start = false;
	game_over = false;
	game_ending = false;

	// 배경 음악
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	bg_mus = Mix_LoadMUS("../../Resources/m1/mode1Bgm.mp3");

	// jump wav
	jump_wav = Mix_LoadWAV("../../Resources/m1/jump.wav");

	// btn wav
	btn_wav = Mix_LoadWAV("../../Resources/m1/btnSound.wav");

	// game clear wav
	gameClear_wav = Mix_LoadWAV("../../Resources/m1/gameClear.wav");

	// ready Start
	ready_sound = Mix_LoadWAV("../../Resources/m2/readySound.wav");

	// intro (tutorial)
	{
		SDL_Surface* temp_surface = IMG_Load("../../Resources/m1/tutorial_mode1.png");
		g_texture_intro = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		SDL_QueryTexture(g_texture_intro, NULL, NULL, &g_source_rectangle_intro.w, &g_source_rectangle_intro.h);
		g_source_rectangle_intro = { 0, 0, 800, 600 };
		g_destination_rectangle_intro = { 95, 40, 620, 480 };
	}

	// play Button (Start button)
	SDL_Surface* play_surface = IMG_Load("../../Resources/m1/play.png");
	g_texture_play = SDL_CreateTextureFromSurface(g_renderer, play_surface);
	SDL_FreeSurface(play_surface);
	SDL_QueryTexture(g_texture_play, NULL, NULL, &g_source_rectangle_play.w, &g_source_rectangle_play.h);
	g_source_rectangle_play = { 0, 0, 160, 80 };
	g_destination_rectangle_play = { 320, 510, 160, 80 };


	//뒤로가기
	introBack_surface = IMG_Load("../../Resources/m1/back.png");
	introBack_texture = SDL_CreateTextureFromSurface(g_renderer, introBack_surface);
	SDL_FreeSurface(introBack_surface);
	introBack_rect = { 0, 0, introBack_surface->w,introBack_surface->h };
	introBack_dest_rect = { 10, 10, introBack_surface->w, introBack_surface->h };

	// ready
	ready_surface = IMG_Load("../../Resources/m1/ready.png");
	ready_texture = SDL_CreateTextureFromSurface(g_renderer, ready_surface);
	SDL_FreeSurface(ready_surface);
	ready_rect = { 0, 0, ready_surface->w,ready_surface->h };
	ready_dest_rect = { 10, 10, ready_surface->w, ready_surface->h };

	// start
	start_surface = IMG_Load("../../Resources/m1/start.png");
	start_texture = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);
	start_rect = { 0, 0, start_surface->w,start_surface->h };
	start_dest_rect = { 10, 10, start_surface->w, start_surface->h };

	// 배경 이미지 로드
	bg_surface = IMG_Load("../../Resources/m1/bg_mode1.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU로 옮기기 
	SDL_FreeSurface(bg_surface);
	backgroundY = -1200; 	// 배경 이미지 초기 위치 설정 (화면 위로)


	// wall 이미지 로드
	wall_surface = IMG_Load("../../Resources/m1/wall_mode1.png");
	wall_texture = SDL_CreateTextureFromSurface(g_renderer, wall_surface);
	SDL_FreeSurface(wall_surface);
	wallY = -4800;

	// timeBg
	timeBg_surface = IMG_Load("../../Resources/m1/timeBg.png");
	timeBg_texture = SDL_CreateTextureFromSurface(g_renderer, timeBg_surface);
	SDL_FreeSurface(timeBg_surface);
	timeBg_rect = { 0, 0, timeBg_surface->w, timeBg_surface->h };
	timeBg_dest_rect = { 30, 20, timeBg_surface->w, timeBg_surface->h };

	// time
	font = TTF_OpenFont("../../Resources/m1/DungGeunMo.ttf", 30);



	// hold 이미지 로드
	srand((unsigned)time(NULL)); // srand는 한 번만 호출해야 합니다.
	for (int i = 0; i < 40; i++) {
		// int random_hold_idx = rand() % 4; // 0~3 중 하나의 인덱스를 무작위로 선택
		int random_hold_idx;
		do {
			random_hold_idx = rand() % 4; // 0~3 중 하나의 인덱스를 무작위로 선택
		} while (random_hold_idx == prevHoldIndex); // 현재 인덱스가 이전 인덱스와 같으면 새로운 인덱스를 계속 생성합니다
		prevHoldIndex = random_hold_idx;
		string hold_path = hold_paths[random_hold_idx];
		SDL_Surface* hold_surface = IMG_Load(hold_path.c_str());
		SDL_Texture* hold_texture = SDL_CreateTextureFromSurface(g_renderer, hold_surface);
		SDL_FreeSurface(hold_surface);
		hold_surfaces.push_back(hold_surface);
		hold_textures.push_back(hold_texture);
		SDL_Rect hold_rect = { 0, 0, hold_surface->w, hold_surface->h };
		hold_rects.push_back(hold_rect);


		if (i % 2 == 0) {
			SDL_Rect hold_dest_rect = { 300, leftHoldY , hold_surface->w, hold_surface->h }; // 원래 270
			hold_dest_rects.push_back(hold_dest_rect);
			leftHoldY -= 200;
		}
		else {
			SDL_Rect hold_dest_rect = { 430, rightHoldY , hold_surface->w, hold_surface->h }; // 원래 470
			hold_dest_rects.push_back(hold_dest_rect);
			rightHoldY -= 200;
		}

		if (hold_path == "../../Resources/m1/downHold.png") {
			nextHoldPath = hold_path;
			hold[i] = 1;
		}
		else if (hold_path == "../../Resources/m1/leftHold.png") {
			nextHoldPath = hold_path;
			hold[i] = 2;
		}
		else if (hold_path == "../../Resources/m1/rightHold.png") {
			nextHoldPath = hold_path;
			hold[i] = 3;
		}
		else if (hold_path == "../../Resources/m1/upHold.png") {
			nextHoldPath = hold_path;
			hold[i] = 4;
		}
		// printf("%d\n", hold);
	}
	// leftUser
	leftUser_surface = IMG_Load("../../Resources/m1/leftUser.png");
	leftUser_texture = SDL_CreateTextureFromSurface(g_renderer, leftUser_surface);
	SDL_FreeSurface(leftUser_surface);
	leftUser_rect = { 0, 0, leftUser_surface->w, leftUser_surface->h };
	leftUser_dest_rect = { 280, 427, leftUser_surface->w, leftUser_surface->h }; // 원래 240

	// rightUser
	rightUser_surface = IMG_Load("../../Resources/m1/rightUser.png");
	rightUser_texture = SDL_CreateTextureFromSurface(g_renderer, rightUser_surface);
	SDL_FreeSurface(rightUser_surface);
	rightUser_rect = { 0, 0, rightUser_surface->w, rightUser_surface->h };
	rightUser_dest_rect = { 410, 427, rightUser_surface->w, rightUser_surface->h }; // 원래 440

	/*
	stun_surface = IMG_Load("../src/stun.png");
	stun_texture = SDL_CreateTextureFromSurface(g_renderer, stun_surface);
	SDL_FreeSurface(stun_surface);
	stun_rect = { 0, 0, stun_surface->w, stun_surface->h };
	stun_dest_rect = { 0, 0, stun_surface->w, stun_surface->h };
	*/

	//For Texture
	{
		SDL_Surface* temp_surface = IMG_Load("../../Resources/m1/gameclear.png");
		g_texture_ending = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
		SDL_FreeSurface(temp_surface);
		SDL_QueryTexture(g_texture_ending, NULL, NULL, &g_source_rectangle_ending.w, &g_source_rectangle_ending.h);
		g_source_rectangle_ending = { 0, 0, temp_surface->w, temp_surface->h };
		g_destination_rectangle_ending = { 0, 0, temp_surface->w, temp_surface->h };
	}

	//home

	SDL_Surface* home_surface = IMG_Load("../../Resources/m1/home.png");
	g_texture_home = SDL_CreateTextureFromSurface(g_renderer, home_surface);
	SDL_FreeSurface(home_surface);
	SDL_QueryTexture(g_texture_home, NULL, NULL, &g_source_rectangle_home.w, &g_source_rectangle_home.h);
	g_source_rectangle_home = { 0, 0, 160, 80 };
	g_destination_rectangle_home = { 210, 460, 160, 80 };

	//retry
	SDL_Surface* retry_surface = IMG_Load("../../Resources/m1/retry.png");
	g_texture_retry = SDL_CreateTextureFromSurface(g_renderer, retry_surface);
	SDL_FreeSurface(retry_surface);
	SDL_QueryTexture(g_texture_retry, NULL, NULL, &g_source_rectangle_retry.w, &g_source_rectangle_retry.h);
	g_source_rectangle_retry = { 0, 0, 160, 80 };
	g_destination_rectangle_retry = { 440, 460, 160, 80 };

	// ending 화면 time
	font2 = TTF_OpenFont("../../Resources/m1/DungGeunMo.ttf", 42);
}

Mode1::~Mode1() {

	SDL_DestroyTexture(g_texture_intro); // tuto
	SDL_DestroyTexture(g_texture_play); // play Button

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(wall_texture);
	SDL_DestroyTexture(time_texture);
	SDL_DestroyTexture(timeBg_texture);

	for (SDL_Texture* texture : hold_textures) {
		SDL_DestroyTexture(texture);
	}
	SDL_DestroyTexture(leftUser_texture);
	SDL_DestroyTexture(rightUser_texture);
	SDL_DestroyTexture(introBack_texture);

	SDL_DestroyTexture(g_texture_ending);
	SDL_DestroyTexture(g_texture_home);
	SDL_DestroyTexture(g_texture_retry);

	Mix_FreeMusic(bg_mus);
	Mix_FreeChunk(jump_wav);
	Mix_FreeChunk(gameClear_wav);
	Mix_FreeChunk(btn_wav);
	Mix_FreeChunk(ready_sound);
}

void Mode1::Update()
{

	Uint32 currentTime = SDL_GetTicks();

	// Ready, Start
	if (ready) {
		if (currentTime - startTime >= 1000) {

			startTime = currentTime;

			tutorial = false;
			ready = false;
			start = true;
			game_start = false;
			game_over = false;
			game_ending = false;
		}
	}
	else if (start) {
		if (currentTime - startTime >= 1000) {

			startTime = currentTime;

			tutorial = false;
			ready = false;
			start = false;
			game_start = true;
			game_over = false;
			game_ending = false;
		}
	}
	if (game_start && !game_over) {
		// 현재 시간 가져오기
		Uint32 current2Time = SDL_GetTicks();
		Uint32 elapsed2Time = current2Time - startsTime - 3000;  // 경과 시간 계산 // 3 100
		Uint32 seconds = elapsed2Time / 1000; // 3
		Uint32 mseconds = elapsed2Time - seconds * 1000;// 경과 시간을 초로 변환 3100 - 3000


		// 시간을 화면에 표시하기 위해 문자열로 변환
		std::string gameTimeString = std::to_string(seconds) + "." + std::to_string(mseconds);

		a = gameTimeString;

		// 문자열을 표시할 표면 생성
		SDL_Color black = { 0, 0, 0, 0 };
		time_surface = TTF_RenderText_Solid(font, gameTimeString.c_str(), black);


		// 표면을 텍스처로 변환
		time_texture = SDL_CreateTextureFromSurface(g_renderer, time_surface);
		SDL_FreeSurface(time_surface);

		// 텍스처의 크기 및 위치 설정
		SDL_QueryTexture(time_texture, NULL, NULL, &(time_rect.w), &(time_rect.h));
		time_rect.x = 57;
		time_rect.y = 28;


		if (checkHold() == true) {

			Mix_PlayChannel(-1, jump_wav, 0);

			userMove();
			holdMove();
			cur_i++;

			backgroundY += 30;
			wallY += 118;

		}

		if (cur_i == 40) {

			gameoverTime = SDL_GetTicks();
			tutorial = false;
			ready = false;
			start = false;
			game_start = false;
			game_over = true;
			game_ending = false;

		}
	}
	if (game_over) {
		Mix_PlayChannel(-1, gameClear_wav, 0);
		Uint32 elapsedTime = currentTime - gameoverTime;

		if (game_over && elapsedTime >= 2000) {
			startsTime = SDL_GetTicks();

			tutorial = false;
			ready = false;
			start = false;
			game_start = false;
			game_over = false;
			game_ending = true;
		}
	}
	if (game_ending) {
		tutorial = false;
		ready = false;
		start = false;
		game_start = false;
		game_over = false;
	}

}

void Mode1::Render() {
	//배경이어지기
	SDL_Rect backgroundRect = { 0, backgroundY, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
	SDL_RenderCopy(g_renderer, bg_texture, NULL, &backgroundRect);

	//벽이어지기
	SDL_Rect wallRect = { 200, wallY, WALL_WIDTH, WALL_HEIGHT };
	SDL_RenderCopy(g_renderer, wall_texture, NULL, &wallRect);
	//SDL_RenderCopy(g_renderer, time_texture, NULL, &time_rect);

	//SDL_RenderCopy(g_renderer, timeBg_texture, &timeBg_rect, &timeBg_dest_rect);
	//SDL_RenderCopy(g_renderer, time_texture, NULL, &time_rect);

	// bgm

	if (!Mix_PlayingMusic()) {

		Mix_PlayMusic(bg_mus, -1);
		Mix_VolumeMusic(100); // 배경 음악 소리 볼륨
	}



	if (tutorial) {

		SDL_RenderCopy(g_renderer, g_texture_intro, &g_source_rectangle_intro, &g_destination_rectangle_intro);
		SDL_RenderCopy(g_renderer, g_texture_play, &g_source_rectangle_play, &g_destination_rectangle_play);
		SDL_RenderCopy(g_renderer, introBack_texture, &introBack_rect, &introBack_dest_rect);
	}
	else if (ready) {

		SDL_RenderCopy(g_renderer, ready_texture, &ready_rect, &ready_dest_rect);
	}
	else if (start) {

		SDL_RenderCopy(g_renderer, start_texture, &start_rect, &start_dest_rect);

	}
	else if (game_start || game_over) {
		for (size_t i = 0; i < hold_textures.size(); i++) {
			SDL_RenderCopy(g_renderer, hold_textures[i], &hold_rects[i], &hold_dest_rects[i]);
		}
		SDL_RenderCopy(g_renderer, leftUser_texture, &leftUser_rect, &leftUser_dest_rect);
		SDL_RenderCopy(g_renderer, timeBg_texture, &timeBg_rect, &timeBg_dest_rect);
		SDL_RenderCopy(g_renderer, time_texture, NULL, &time_rect);
	}

	else if (game_ending) {
		SDL_RenderCopy(g_renderer, g_texture_ending, &g_source_rectangle_ending, &g_destination_rectangle_ending);
		SDL_RenderCopy(g_renderer, g_texture_home, &g_source_rectangle_home, &g_destination_rectangle_home);
		SDL_RenderCopy(g_renderer, g_texture_retry, &g_source_rectangle_retry, &g_destination_rectangle_retry);

		SDL_Color black = { 0, 0, 0, 0 };
		time2_surface = TTF_RenderText_Solid(font2, a.c_str(), black);
		time2_texture = SDL_CreateTextureFromSurface(g_renderer, time2_surface);
		SDL_FreeSurface(time2_surface);
		SDL_QueryTexture(time2_texture, NULL, NULL, &(time2_rect.w), &(time2_rect.h));
		time2_rect.x = 543;
		time2_rect.y = 283;

		SDL_RenderCopy(g_renderer, time2_texture, NULL, &time2_rect);


	}

	SDL_RenderPresent(g_renderer);
}
// bg, wall 아래로 내려가고 user는 좌우 움직이기
void Mode1::userMove() {


	if (isLeftUser) {
		leftUser_dest_rect.x += 150;
		rightUser_dest_rect.x -= 150;
	}
	else {
		leftUser_dest_rect.x -= 150;
		rightUser_dest_rect.x += 150;
	}
	SDL_Surface* tempSurface = leftUser_surface;
	leftUser_surface = rightUser_surface;
	rightUser_surface = tempSurface;

	SDL_Texture* tempTexture = leftUser_texture;
	leftUser_texture = rightUser_texture;
	rightUser_texture = tempTexture;

	isLeftUser = !isLeftUser;

}

void Mode1::holdMove() {
	for (SDL_Rect& hold_dest_rect : hold_dest_rects) {
		hold_dest_rect.y += 100;
	}
	/*
	if (cur_i == 40) {
		SDL_Delay(1000);
		g_current_game_phase = PHASE_ENDING1;
	}
	*/
}


bool Mode1::checkHold() {


	if (hold[cur_i] == f_state) {

		prevHold = f_state;
		return true;
	}

	return false;

}

void Mode1::HandleEvents() {

	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {

				int mouse_x = event.button.x;
				int mouse_y = event.button.y;


				// introBack 버튼
				if (mouse_x >= introBack_dest_rect.x &&
					mouse_x <= introBack_dest_rect.x + introBack_dest_rect.w &&
					mouse_y >= introBack_dest_rect.y &&
					mouse_y <= introBack_dest_rect.y + introBack_dest_rect.h && tutorial) {
					Mix_PlayChannel(-1, btn_wav, 0);

					g_current_game_phase = PHASE_HOME;
					//ResetGame();
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					Mix_FadeOutMusic(1000);
				}

				// game start 버튼
				if (mouse_x >= g_destination_rectangle_play.x &&
					mouse_x <= g_destination_rectangle_play.x + g_destination_rectangle_play.w &&
					mouse_y >= g_destination_rectangle_play.y &&
					mouse_y <= g_destination_rectangle_play.y + g_destination_rectangle_play.h && tutorial) {
					Mix_PlayChannel(-1, btn_wav, 0);

					tutorial = false;
					ready = true;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					startTime = SDL_GetTicks();
					startsTime = SDL_GetTicks();

					//wav는 여기서 플레이
					Mix_VolumeChunk(ready_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(1, ready_sound, 0); //무한반복 안하기
				}

				// home 버튼
				if (mouse_x >= g_destination_rectangle_home.x &&
					mouse_x <= g_destination_rectangle_home.x + g_destination_rectangle_home.w &&
					mouse_y >= g_destination_rectangle_home.y &&
					mouse_y <= g_destination_rectangle_home.y + g_destination_rectangle_home.h && game_ending)
				{
					Mix_PlayChannel(-1, btn_wav, 0);

					g_current_game_phase = PHASE_HOME;
					ResetGame();
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					Mix_FadeOutMusic(1000);
				}

				// game retry 버튼
				if (mouse_x >= g_destination_rectangle_retry.x &&
					mouse_x <= g_destination_rectangle_retry.x + g_destination_rectangle_retry.w &&
					mouse_y >= g_destination_rectangle_retry.y &&
					mouse_y <= g_destination_rectangle_retry.y + g_destination_rectangle_retry.h && game_ending)
				{
					Mix_PlayChannel(-1, btn_wav, 0);
					ResetGame();
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;

				}
			}

			break;


		case SDL_KEYDOWN: // 1:down 2:left 3: right 4: up


			if (event.key.keysym.sym == SDLK_LEFT) {
				// 다음 돌이 leftHold일 때 hold, wall, bg 내려가기 
				// 아닌경우 stun효과?
				f_state = 2;
				// 배경 이미지 이동


			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				// 다음 돌이 rightHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
				f_state = 3;
				// 배경 이미지 이동


			}
			else if (event.key.keysym.sym == SDLK_UP) {
				// 다음 돌이 upHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
				f_state = 4;
				// 배경 이미지 이동


			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				// 다음 돌이 downHold일 때 hold, wall, bg 내려가기
				// 아닌경우 stun효과?
				f_state = 1;
				// 배경 이미지 이동

			}


			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_DOWN) {
				// 아래 키를 떼면 f_state 값을 초기화합니다.
				f_state = 0;
			}
			break;

		default:
			break;
		}
	}

}


void Mode1::ResetGame() {
	f_state = 0;
	cur_i = 1;
	prevHold = 0;

	wallY = -4800;
	backgroundY = -1200;

	userMove();
	//isLeftUser = !isLeftUser;
	leftUser_dest_rect.x = 280;
	rightUser_dest_rect.x = 410;
	//leftUser_dest_rect = { 280, 427, leftUser_surface->w, leftUser_surface->h };
	//rightUser_dest_rect = { 410, 427, rightUser_surface->w, rightUser_surface->h };

	// Reset hold positions
	leftHoldY = 475;
	rightHoldY = 375;
	for (size_t i = 0; i < hold_dest_rects.size(); i++) {
		if (i % 2 == 0) {
			hold_dest_rects[i].y = leftHoldY;
			leftHoldY -= 200;
		}
		else {
			hold_dest_rects[i].y = rightHoldY;
			rightHoldY -= 200;
		}
	}
}