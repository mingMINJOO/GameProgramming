#include "gamefunc.h"
#include <windows.h>
#include <queue>
#include "SDL.h"
#include <atlstr.h>

using namespace std;

int g_input;
int g_elapsed_time_ms;

//�����
int f_state;
int f_x;
int f_y;
string f_output;

//�̻���
int m_state;
int m_x;
int m_y;
string m_output;


//�̻��� �迭�� �ε���
bool bullet[30];
int cnt;
short m_pos[30][2];

int score;

SDL_Rect g_destination_rect; // ����� ��ġ
SDL_Rect g_source_rect; // ����� �߶�� ���� �簢��
SDL_Texture* g_airplane_texture; // ����� ������� ��

SDL_Rect g_bullet_destination_rect[30]; // �̻����� ���� ��ġ
SDL_Rect g_bullet_source_rect; // �̻��� �߶�� ���� �簢��
SDL_Texture* g_bullet_texture; //�̻��� ������� ��

SDL_Rect g_bg_destination_rect; // ���
SDL_Rect g_bg_source_rect; // ��� �߶�� ���� �簢��
SDL_Texture* g_bg_texture; //��� ������� ��

Mix_Music* g_bg_mus;
Mix_Chunk* g_missile_sound;

//���� :
SDL_Texture* g_score_kr;
SDL_Rect g_score_kr_rect;

//score
SDL_Texture* g_scoreN_kr;
SDL_Rect g_scoreN_kr_rect;

//���α׷� ���� �� ó�� �ѹ� ����Ǵ� �Լ�
void InitGame() {

	g_input = 0;
	g_elapsed_time_ms = 0;
	g_flag_running = true;

	score = 0;
	cnt = 0;

	//�����׸�
	SDL_Surface* airplane_surface = IMG_Load("../resources/airplane_image.png");
	// SDL_SetColorKey(airplane_surface, SDL_TRUE, SDL_MapRGB(airplane_surface->format, 0, 0, 0)); //�� ��� ���������
	g_airplane_texture = SDL_CreateTextureFromSurface(g_renderer, airplane_surface);
	SDL_FreeSurface(airplane_surface);

	g_source_rect = { 0, 0, 512, 512 };
	g_destination_rect = { 360, 500, 60, 50 };

	//���׸�
	SDL_Surface* bg_surface = IMG_Load("../resources/bg.jpg");
	g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
	SDL_FreeSurface(bg_surface); //�ʿ�����??!

	g_bg_source_rect = { 0, 0, 600, 900 };
	g_bg_destination_rect = { 0, 0, 800, 600 };

	//�̻���
	g_bullet_source_rect = { 0, 0, 640, 1280 };

	SDL_Surface* bullet_surface = IMG_Load("../resources/bullet.png");
	g_bullet_texture = SDL_CreateTextureFromSurface(g_renderer, bullet_surface);
	SDL_FreeSurface(bullet_surface);


	//��Ʈ
	TTF_Font* font1 = TTF_OpenFont("../resources/DungGeunMo.ttf", 30);
	SDL_Color black = { 0, 0, 0, 0 };
	SDL_Surface* tmp_surface = TTF_RenderUTF8_Blended(font1, CW2A(L"���� : ", CP_UTF8), black);

	//����:
	g_score_kr_rect.x = 0;
	g_score_kr_rect.y = 0;
	g_score_kr_rect.w = tmp_surface->w;
	g_score_kr_rect.h = tmp_surface->h;

	g_score_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);

	//����� ���⼭ �÷���, wav�� �̻��� �߻��ϸ� �÷���
	g_bg_mus = Mix_LoadMUS("../resources/bgm.mp3");
	Mix_VolumeMusic(100);
	Mix_PlayMusic(g_bg_mus, -1);
	g_missile_sound = Mix_LoadWAV("../resources/missile.wav");

	//�޸�����
	SDL_FreeSurface(tmp_surface);
	TTF_CloseFont(font1);
	system("cls");
}

void printscore(int score) {

	//������ ���ڿ��� ��ȯ�ؼ� 5�ڸ����� ������ 0ä���ֱ�
	string now_score = to_string(score);
	string print_score = string(5 - now_score.length(), '0') + now_score;

	TTF_Font* font1 = TTF_OpenFont("../resources/DungGeunMo.ttf", 30);
	string text = print_score;
	SDL_Color red = { 255, 0, 0, 0 }; //RGB, ����
	SDL_Surface* tmp_surface2 = TTF_RenderUTF8_Blended(font1, text.c_str(), red);

	//score
	g_scoreN_kr_rect.x = 0;
	g_scoreN_kr_rect.y = 0;
	g_scoreN_kr_rect.w = tmp_surface2->w;
	g_scoreN_kr_rect.h = tmp_surface2->h;

	g_scoreN_kr = SDL_CreateTextureFromSurface(g_renderer, tmp_surface2);

	SDL_FreeSurface(tmp_surface2);
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

	//�����ٱ����� ���������ϰ��ϱ�
	if (g_destination_rect.x > 740)
		g_destination_rect.x = 740;
	else if (g_destination_rect.x < 0)
		g_destination_rect.x = 0;

	if (g_destination_rect.y > 550)
		g_destination_rect.y = 550;
	else if (g_destination_rect.y < 0)
		g_destination_rect.y = 0;

	g_elapsed_time_ms += 33;
}

void Render() {
	//���
	/*SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
	SDL_RenderClear(g_renderer);*/

	SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

	//�����
	/*SDL_SetRenderDrawColor(g_renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(g_renderer, &g_char_pos);*/

	//airplane_texture
	SDL_RenderCopy(g_renderer, g_airplane_texture, &g_source_rect, &g_destination_rect);


	// �̻��� �׸���
	for (int i = 0; i < 30; i++) {
		if (bullet[i]) {
			if (g_bullet_destination_rect[i].y < 0) bullet[i] = false;

			g_bullet_destination_rect[i].y -= 10;  //�ӵ�
			SDL_RenderCopy(g_renderer, g_bullet_texture, &g_bullet_source_rect, &g_bullet_destination_rect[i]);
		}
	}

	//���� : (��ġ)
	SDL_Rect tmp_r;
	tmp_r.x = 15;
	tmp_r.y = 15;
	tmp_r.w = g_score_kr_rect.w;
	tmp_r.h = g_score_kr_rect.h;
	SDL_RenderCopy(g_renderer, g_score_kr, &g_score_kr_rect, &tmp_r);

	//score (��ġ)
	SDL_Rect tmp_r2;
	tmp_r2.x = 130;
	tmp_r2.y = 16;
	tmp_r2.w = g_scoreN_kr_rect.w;
	tmp_r2.h = g_scoreN_kr_rect.h;
	SDL_RenderCopy(g_renderer, g_scoreN_kr, &g_scoreN_kr_rect, &tmp_r2);
	
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
				g_bullet_destination_rect[cnt] = { g_destination_rect.x + 15, g_destination_rect.y + 20 - 50, 30, 30 }; //�̻��� ��ġ, ũ������
				m_pos[cnt][1] = f_y;
				cnt++;
				score += 10;
				printscore(score);
				Mix_PlayChannel(1, g_missile_sound, 0);
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
	Mix_FreeMusic(g_bg_mus);
	Mix_FreeChunk(g_missile_sound);
	SDL_DestroyTexture(g_score_kr);
	SDL_DestroyTexture(g_scoreN_kr);
}