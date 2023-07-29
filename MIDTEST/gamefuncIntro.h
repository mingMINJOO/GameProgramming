#pragma once

#include "gamefunc.h"

class Intro : public PhaseInterface {
public:
	Intro();
	~Intro();

	virtual void HandleEvents() override; //�������̵�� ������ �ۼ��� ������ �ִ����� �ٽ� �ۼ��ϰڴ�
	virtual void Update() override;
	virtual void Render() override;
	virtual void Clear() override;

private:
	SDL_Texture* texture_intro_;
	SDL_Rect source_rectangle_intro_;
	SDL_Rect destination_rectangle_intro_;
};