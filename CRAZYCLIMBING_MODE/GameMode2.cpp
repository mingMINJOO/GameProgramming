//GameMode2.cpp
#include "Game.h"
#include "GameMode2.h"
#include <vector>
#include <cstdlib>
#include <chrono>

using namespace std;
vector<string> hold2_paths = { "../../Resources/m2/redHold.png", "../../Resources/m2/greenHold.png", "../../Resources/m2/blueHold.png" };
vector<SDL_Surface*> hold2_surfaces;
vector<SDL_Texture*> hold2_textures;
vector<SDL_Rect> hold2_rects;
vector<SDL_Rect> hold2_dest_rects;

string nextHoldPath2 = "";

Mode2::Mode2() {
	//오디오
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
	mode2_bgm = Mix_LoadMUS("../../Resources/m2/mode2_bgm.mp3"); //mp3
	jump_sound = Mix_LoadWAV("../../Resources/m2/jump.wav"); // WAV 파일 로드
	btn_sound = Mix_LoadWAV("../../Resources/m2/Button_Sound.wav");
	mode2_gameover_bgm = Mix_LoadWAV("../../Resources/m2/wrong_hold.wav");
	ready_sound = Mix_LoadWAV("../../Resources/m2/readySound.wav");

	g_flag_running = true;
	cur_i = 1;
	prevHold = 0;

	//STATE
	tutorial = true;
	ready = false;
	start = false;
	game_start = false;
	game_over = false;
	game_ending = false;

	//인트로 튜토리얼
	SDL_Surface* intro_surface = IMG_Load("../../Resources/m2/intro.png");
	g_texture_intro = SDL_CreateTextureFromSurface(g_renderer, intro_surface);
	SDL_FreeSurface(intro_surface);
	SDL_QueryTexture(g_texture_intro, NULL, NULL, &g_source_rectangle_intro.w, &g_source_rectangle_intro.h);
	g_source_rectangle_intro = { 0, 0, 800, 600 };
	g_destination_rectangle_intro = { 95, 40, 620, 480 };

	//play버튼
	SDL_Surface* play_surface = IMG_Load("../../Resources/m2/play.png");
	g_texture_play = SDL_CreateTextureFromSurface(g_renderer, play_surface);
	SDL_FreeSurface(play_surface);
	SDL_QueryTexture(g_texture_play, NULL, NULL, &g_source_rectangle_play.w, &g_source_rectangle_play.h);
	g_source_rectangle_play = { 0, 0, 160, 80 };
	g_destination_rectangle_play = { 320, 510, 160, 80 };

	//뒤로가기
	introBack_surface = IMG_Load("../../Resources/m2/back.png");
	introBack_texture = SDL_CreateTextureFromSurface(g_renderer, introBack_surface);
	SDL_FreeSurface(introBack_surface);
	introBack_rect = { 0, 0, introBack_surface->w,introBack_surface->h };
	introBack_dest_rect = { 10, 10, introBack_surface->w, introBack_surface->h };

	//레디
	ready_surface = IMG_Load("../../Resources/m2/ready.png");
	ready_texture = SDL_CreateTextureFromSurface(g_renderer, ready_surface);
	SDL_FreeSurface(ready_surface);
	ready_rect = { 0, 0, ready_surface->w,ready_surface->h };
	ready_dest_rect = { 10, 10, ready_surface->w, ready_surface->h };

	//스타트
	start_surface = IMG_Load("../../Resources/m2/start.png");
	start_texture = SDL_CreateTextureFromSurface(g_renderer, start_surface);
	SDL_FreeSurface(start_surface);
	start_rect = { 0, 0, start_surface->w,start_surface->h };
	start_dest_rect = { 10, 10, start_surface->w, start_surface->h };

	// 배경 이미지 로드
	bg_surface = IMG_Load("../../Resources/m2/bg_mode2.png");
	bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface); // GPU로 옮기기 
	SDL_FreeSurface(bg_surface);
	backgroundY = -2400; 	// 배경 이미지 초기 위치 설정 (화면 위로)

	// wall 이미지 로드
	wall_surface = IMG_Load("../../Resources/m2/wall_mode2.png");
	wall_texture = SDL_CreateTextureFromSurface(g_renderer, wall_surface); // GPU로 옮기기 
	SDL_FreeSurface(wall_surface);
	wall_rect = { 0, 0, 400, 600 };
	wall_dest_rect = { 200, 0, 400, 600 };


	//홀드 이미지 로드
	srand((unsigned)time(NULL)); // srand는 한 번만 호출해야 합니다.
	for (int i = 0; i < 150; i++) {
		int random_hold_idx;
		do {
			random_hold_idx = rand() % 3; // 0~3 중 하나의 인덱스를 무작위로 선택
		} while (random_hold_idx == prevHoldIndex); // 현재 인덱스가 이전 인덱스와 같으면 새로운 인덱스를 계속 생성합니다
		
		prevHoldIndex = random_hold_idx;
		string hold_path = hold2_paths[random_hold_idx];
		SDL_Surface* hold_surface = IMG_Load(hold_path.c_str());
		SDL_Texture* hold_texture = SDL_CreateTextureFromSurface(g_renderer, hold_surface);
		SDL_Rect hold_rect = { 0, 0, hold_surface->w, hold_surface->h };

		hold2_surfaces.push_back(hold_surface);
		hold2_textures.push_back(hold_texture);
		hold2_rects.push_back(hold_rect);

		if (i % 2 == 0) {
			SDL_Rect hold_dest_rect = { 315, leftHoldY , 50, 50 };
			hold2_dest_rects.push_back(hold_dest_rect);
			leftHoldY -= 200;
		}
		else {
			SDL_Rect hold_dest_rect = { 440, rightHoldY , 50, 50 };
			hold2_dest_rects.push_back(hold_dest_rect);
			rightHoldY -= 200;
		}

		if (hold_path == "../../Resources/m2/redHold.png") {
			nextHoldPath2 = hold_path;
			hold[i] = 1;
		}
		else if (hold_path == "../../Resources/m2/greenHold.png") {
			nextHoldPath2 = hold_path;
			hold[i] = 2;
		}
		else if (hold_path == "../../Resources/m2/blueHold.png") {
			nextHoldPath2 = hold_path;
			hold[i] = 3;
		}
	}

	// leftUser
	leftUser_surface = IMG_Load("../../Resources/m2/leftUser.png");
	leftUser_texture = SDL_CreateTextureFromSurface(g_renderer, leftUser_surface);
	SDL_FreeSurface(leftUser_surface);
	leftUser_rect = { 0, 0, leftUser_surface->w, leftUser_surface->h };
	leftUser_dest_rect = { 280, 427, leftUser_surface->w, leftUser_surface->h };

	// rightUser
	rightUser_surface = IMG_Load("../../Resources/m2/rightUser.png");
	rightUser_texture = SDL_CreateTextureFromSurface(g_renderer, rightUser_surface);
	SDL_FreeSurface(rightUser_surface);
	rightUser_rect = { 0, 0, rightUser_surface->w, rightUser_surface->h };
	rightUser_dest_rect = { 410, 427, rightUser_surface->w, rightUser_surface->h };

	//ENDING
	//엔딩사진
	SDL_Surface* ending_surface = IMG_Load("../../Resources/m2/bg_mode2_ending.png");
	g_texture_ending = SDL_CreateTextureFromSurface(g_renderer, ending_surface);
	SDL_FreeSurface(ending_surface);
	SDL_QueryTexture(g_texture_ending, NULL, NULL, &g_source_rectangle_ending.w, &g_source_rectangle_ending.h);
	g_source_rectangle_ending = { 0, 0, 800, 600 };
	g_destination_rectangle_ending = { 0, 0, 800, 600 };

	//home 버튼
	SDL_Surface* home_surface = IMG_Load("../../Resources/m2/home_btn.png");
	g_texture_home = SDL_CreateTextureFromSurface(g_renderer, home_surface);
	SDL_FreeSurface(home_surface);
	SDL_QueryTexture(g_texture_home, NULL, NULL, &g_source_rectangle_home.w, &g_source_rectangle_home.h);
	g_source_rectangle_home = { 0, 0, 160, 80 };
	g_destination_rectangle_home = { 210, 435, 160, 80 };

	//retry
	SDL_Surface* retry_surface = IMG_Load("../../Resources/m2/retry.png");
	g_texture_retry = SDL_CreateTextureFromSurface(g_renderer, retry_surface);
	SDL_FreeSurface(retry_surface);
	SDL_QueryTexture(g_texture_retry, NULL, NULL, &g_source_rectangle_retry.w, &g_source_rectangle_retry.h);
	g_source_rectangle_retry = { 0, 0, 160, 80 };
	g_destination_rectangle_retry = { 440, 435, 160, 80 };

	// num
	font = TTF_OpenFont("../../Resources/m2/DungGeunMo.ttf", 60);
}

Mode2::~Mode2() {
	SDL_DestroyTexture(g_texture_intro);
	SDL_DestroyTexture(g_texture_play);

	SDL_DestroyTexture(bg_texture);
	SDL_DestroyTexture(wall_texture);

	for (SDL_Texture* texture : hold2_textures) {
		SDL_DestroyTexture(texture);
	}
	SDL_DestroyTexture(leftUser_texture);
	SDL_DestroyTexture(rightUser_texture);
	SDL_DestroyTexture(introBack_texture);

	SDL_DestroyTexture(g_texture_ending);
	SDL_DestroyTexture(g_texture_home);
	SDL_DestroyTexture(g_texture_retry);

	TTF_CloseFont(font);

	Mix_FreeMusic(mode2_bgm);
	Mix_FreeChunk(jump_sound);
	Mix_FreeChunk(btn_sound);
	Mix_FreeChunk(mode2_gameover_bgm);
}

void Mode2::Update()
{
	Uint32 currentTime = SDL_GetTicks();

	//레디
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
	//스타트
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
		//맞는돌 눌렀을 때
		if (checkHold()) {
			Mix_PlayChannel(2, jump_sound, 0); //무한반복 안하기

			userMove();
			holdMove();
			cur_i++;
			gauge += 5;
			backgroundY += 30;
			holdCount++;

			if (cur_i >= 50) { //홀드 50개 넘으면 스피드 업!
				gaugeDecreaseRate = gaugeDecreaseRate2;
			}
		}
		else {
			gauge -= gaugeDecreaseRate;
			if (gauge < 0) {
				gauge = 0;
			}
		}
		// 게이지가 0이면 게임 오버
		if (gauge == 0) {
			tutorial = false;
			ready = false;
			start = false;
			game_start = false;
			game_over = true;
			game_ending = false;
		}

		if (checkHold()) {
			//wall
			if (wall_dest_rect.y >= 600) {
				wall_dest_rect.y = 0;
			}
		}
	}

	if (game_over) {
		//wav는 여기서 플레이 (엔딩에서만 재생)
		Mix_VolumeChunk(mode2_gameover_bgm, MIX_MAX_VOLUME);
		Mix_PlayChannel(1, mode2_gameover_bgm, 0); //무한반복 안하기 

		Uint32 elapsedTime = currentTime - gameoverTime;
		if (game_over && elapsedTime >= 2000) {
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

		// 시간을 화면에 표시하기 위해 문자열로 변환
		std::string gameTimeString = std::to_string(holdCount);

		SDL_Color black = { 0, 0, 0, 0 };
		num_surface = TTF_RenderText_Blended(font, gameTimeString.c_str(), black);

		// 표면을 텍스처로 변환
		num_texture = SDL_CreateTextureFromSurface(g_renderer, num_surface);
		SDL_FreeSurface(num_surface);

		SDL_QueryTexture(num_texture, NULL, NULL, &(num_rect.w), &(num_rect.h));
		num_rect.x = 630;
		num_rect.y = 303;
	}
}

void Mode2::Render() {

	//배경이어지기
	SDL_Rect backgroundRect = { 0, backgroundY, BACKGROUND_WIDTH, BACKGROUND_HEIGHT };
	SDL_RenderCopy(g_renderer, bg_texture, NULL, &backgroundRect);

	//벽이어지기
	{
		int currentY = wall_dest_rect.y + wall_dest_rect.h;
		while (currentY > -wall_rect.h) {
			SDL_Rect tmp_r;
			tmp_r.x = wall_dest_rect.x;
			tmp_r.y = currentY - 600;
			tmp_r.w = wall_dest_rect.w;
			tmp_r.h = wall_dest_rect.h;
			SDL_RenderCopy(g_renderer, wall_texture, &wall_rect, &tmp_r);
			currentY -= wall_rect.h;
		}
	}

	//브금은 여기서 플레이 (튜토리얼 상태에서만 재생)
	if (!Mix_PlayingMusic()) { //홈이랑 합치면 느낌표지우기
		Mix_VolumeMusic(100);
		Mix_PlayMusic(mode2_bgm, -1); // 무한반복
	}

	if (tutorial) {
		//Tutorial
		SDL_RenderCopy(g_renderer, g_texture_intro, &g_source_rectangle_intro, &g_destination_rectangle_intro);
		// Play Button
		SDL_RenderCopy(g_renderer, g_texture_play, &g_source_rectangle_play, &g_destination_rectangle_play);
		// Back Button
		SDL_RenderCopy(g_renderer, introBack_texture, &introBack_rect, &introBack_dest_rect);


	}

	else if (ready) {
		SDL_RenderCopy(g_renderer, ready_texture, &ready_rect, &ready_dest_rect); 
	
	}

	else if (start) {
		SDL_RenderCopy(g_renderer, start_texture, &start_rect, &start_dest_rect);
	}

	else if (game_start || game_over) {
		SDL_Rect gaugeRect = { 615, 20, gauge, 30 }; // 게이지 위치와 크기 설정
		SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255); // 게이지 색상 (빨간색)
		SDL_RenderFillRect(g_renderer, &gaugeRect);

		// 게이지 테두리 그리기
		SDL_Rect gaugeBorderRect = { 615, 20, 150, 30 }; // 게이지 테두리 위치와 크기 설정
		SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255); // 게이지 테두리 색상 (흰색)
		int borderWidth = 4; // 테두리 두께 설정
		for (int i = 0; i < borderWidth; i++) {
			SDL_Rect borderRect = { gaugeBorderRect.x - i, gaugeBorderRect.y - i, gaugeBorderRect.w + 2 * i, gaugeBorderRect.h + 2 * i };
			SDL_RenderDrawRect(g_renderer, &borderRect);
		}

		//홀드그리기
		for (size_t i = 0; i < hold2_textures.size(); i++) {
			SDL_RenderCopy(g_renderer, hold2_textures[i], &hold2_rects[i], &hold2_dest_rects[i]);
		}

		//사람
		SDL_RenderCopy(g_renderer, leftUser_texture, &leftUser_rect, &leftUser_dest_rect);
	}
	else if (game_ending) {
		SDL_RenderCopy(g_renderer, g_texture_ending, &g_source_rectangle_ending, &g_destination_rectangle_ending);
		SDL_RenderCopy(g_renderer, g_texture_home, &g_source_rectangle_home, &g_destination_rectangle_home);
		SDL_RenderCopy(g_renderer, g_texture_retry, &g_source_rectangle_retry, &g_destination_rectangle_retry);

		// 홀드 개수 출력
		SDL_RenderCopy(g_renderer, num_texture, NULL, &num_rect);

	}
		SDL_RenderPresent(g_renderer);
}


void Mode2::userMove() {
	//배경 아래로 움직이기
	wall_dest_rect.y += 20;

	//왼쪽유저일때 오른쪽유저로 바꾸기
	if (isLeftUser) {
		leftUser_dest_rect.x += 150;
		rightUser_dest_rect.x -= 150;
		
	}
	//오른쪽유저일때 왼쪽유저로 바꾸기
	else {
		leftUser_dest_rect.x -= 150;
		rightUser_dest_rect.x += 150;
		
	}
	SDL_Surface* tempSurface = leftUser_surface;
	leftUser_surface = rightUser_surface;
	rightUser_surface = rightUser_surface;

	SDL_Texture* tempTexture = leftUser_texture;
	leftUser_texture = rightUser_texture;
	rightUser_texture = tempTexture;

	isLeftUser = !isLeftUser;
	
}

void Mode2::holdMove() {
	for (SDL_Rect& hold_dest_rect : hold2_dest_rects) {
		hold_dest_rect.y += 100;
	}
}

bool Mode2::checkHold() {
	if (hold[cur_i] == f_state) {
		prevHold = f_state;
		return true;
	}
	else {
		prevHold = 0; // hold가 일치하지 않으면 prevHold 값을 초기화합니다.
	}
	return false;
}

void Mode2::HandleEvents() {
	SDL_Event event;

	if (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			// If the mouse left button is pressed. 
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				int mouseX = event.button.x;
				int mouseY = event.button.y;
				//뒤로가기(home으로)
				if (mouseX >= introBack_rect.x && mouseX < introBack_dest_rect.x + introBack_dest_rect.w
					&& mouseY >= introBack_dest_rect.y && mouseY < introBack_dest_rect.y + introBack_dest_rect.h
					&& g_current_game_phase == PHASE_MODE2 && tutorial == true){
					g_current_game_phase = PHASE_HOME;
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					Mix_FadeOutMusic(1000);

					//wav은 여기서 플레이
					Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기
				}

				//game start
				if (mouseX >= g_destination_rectangle_play.x && 
					mouseX < g_destination_rectangle_play.x + g_destination_rectangle_play.w &&
					mouseY >= g_destination_rectangle_play.y &&
					mouseY < g_destination_rectangle_play.y + g_destination_rectangle_play.h
					&& g_current_game_phase == PHASE_MODE2 && tutorial) {
					tutorial = false;
					ready = true;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					startTime = SDL_GetTicks();

					//wav은 여기서 플레이
					Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기

					//wav는 여기서 플레이
					Mix_VolumeChunk(ready_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(1, ready_sound, 0); //무한반복 안하기
					
				}
				// retry
				if (
					mouseX >= g_destination_rectangle_retry.x &&
					mouseX <= g_destination_rectangle_retry.x + g_destination_rectangle_retry.w &&
					mouseY >= g_destination_rectangle_retry.y &&
					mouseY <= g_destination_rectangle_retry.y + g_destination_rectangle_retry.h && game_ending) {
					ResetGame();
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;

					//wav은 여기서 플레이
					Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기
				}

				// home 버튼
				if (mouseX >= g_destination_rectangle_home.x &&
					mouseX <= g_destination_rectangle_home.x + g_destination_rectangle_home.w &&
					mouseY >= g_destination_rectangle_home.y &&
					mouseY <= g_destination_rectangle_home.y + g_destination_rectangle_home.h && game_ending) {
					g_current_game_phase = PHASE_HOME;
					ResetGame();
					tutorial = true;
					ready = false;
					start = false;
					game_start = false;
					game_over = false;
					game_ending = false;
					Mix_FadeOutMusic(1000);

					//wav은 여기서 플레이
					Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
					Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기
				}
			}
				break;

		case SDL_KEYDOWN:
			if (!tutorial && !ready && !start && event.key.keysym.sym)
			{
				if (event.key.keysym.sym == SDLK_r) {
					f_state = 1;
					gauge += 10;
					if (gauge > 100) {
						gauge = 100;
					}
				}
				else if (event.key.keysym.sym == SDLK_g) {
					f_state = 2;
					gauge += 10; // 버튼을 누를 때 게이지를 증가시킴
					if (gauge > 100) {
						gauge = 100;
					}
				}
				else if (event.key.keysym.sym == SDLK_b) {
					f_state = 3;
					gauge += 10; // 버튼을 누를 때 게이지를 증가시킴
					if (gauge > 100) {
						gauge = 100;
					}
				}
				//틀렸을때 게임오버
				if (f_state != hold[cur_i]) {
					SDL_Delay(2000); //맞는 효과음 넣으면 ㄱㅊ을듯!!
					tutorial = false;
					ready = false;
					start = false;
					game_start = false;
					game_over = true;
					game_ending = true;
				}
				break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_DOWN) {
				// 아래 키를 떼면 f_state 값을 초기화합니다.
				f_state = 0;
			}
			}
			break;
		default:
			break;
			}
		}
	}

	void Mode2::ResetGame() {
		userMove();
		f_state = 0;
		cur_i = 1;
		prevHold = 0;
		gauge = 150;
		holdCount = 0;
		gaugeDecreaseRate = 1;

		backgroundY = -2400;

		if (!isLeftUser) {
			isLeftUser = !isLeftUser;
		}
		else {
			isLeftUser = isLeftUser;
		}
		
		leftUser_dest_rect.x = 280;
		rightUser_dest_rect.x = 410;
		//leftUser_dest_rect = { 280, 427, leftUser_surface->w, leftUser_surface->h };
		//rightUser_dest_rect = { 410, 427, rightUser_surface->w, rightUser_surface->h };

		// Reset hold positions
		leftHoldY = 475;
		rightHoldY = 375;

		for (size_t i = 0; i < hold2_dest_rects.size(); i++) {
			if (i % 2 == 0) {
				hold2_dest_rects[i].y = leftHoldY;
				leftHoldY -= 200;
			}
			else {
				hold2_dest_rects[i].y = rightHoldY;
				rightHoldY -= 200;
			}
		}
	}