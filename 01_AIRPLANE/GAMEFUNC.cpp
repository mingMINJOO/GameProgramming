#include "GAMEFUNC.h"
#include <windows.h>
#include <queue>
#include "SDL.h"

using namespace std;

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


//���α׷� ���� �� ���� �ѹ� ����Ǵ� �Լ�
void InitGame() {
	f_state = 0;
	f_x = 10;
	f_y = 29;
	f_output = "*";

	m_output = "!";

	g_flag_running = true;

	cnt = 0;

	system("cls");
}

void Update() {
	if (f_state == 1) {
		if (f_x > 0) {
			f_x --;
		}
	}
	else if (f_state == 2) {
		if (f_x < 19) {
			f_x ++;
		}
	}
	else if (f_state == 3) {
		if (f_y > 0) {
			f_y --;
		}
	}
	else if (f_state == 4) {
		if (f_y < 29) {
			f_y ++;
		}
	}


	//�����ٱ����� ���������ϰ��ϱ�
	if (f_x > 20) {
		f_x = 0;
	}

	else if (f_x < 0) {
		f_x = 0;
	}

	if (f_y > 29) {
		f_y = 29;
	}
	else if (f_y < 0) {
		f_y = 0;
	}
}

void Render() {
	COORD cur;
	cur.X = 0, cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	
	// ���
	for (int i = 0; i < 30; i++) {
		for (int j = 0; j < 20; j++) {
			cout << "_";
		}
		cout << endl;
	}

	cur.X = f_x, cur.Y = f_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// ����� �׸���
	cout << f_output;

	// �̻��� �׸���
	for (int i = 0; i < 30; i++) {
		if (bullet[i]) {
			COORD pos = { m_pos[i][0], m_pos[i][1]-- };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);

			if (m_pos[i][1] < 0) bullet[i] = false;

			// �̻��� �߻�
			cout << m_output;
		}
	}
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
				m_pos[cnt][0] = f_x;
				m_pos[cnt][1] = f_y;
				cnt++;
				if (cnt > 29) cnt = 0;

				break;


		case SDL_KEYUP:
			f_state = 0;
			break;

		default:
			break;

			}
		}
	}
}

void ClearGame() {

}

