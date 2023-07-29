#pragma once

#include "gamefunc.h"

class Intro : public PhaseInterface {
public:
	Intro();
	~Intro();

	virtual void HandleEvents() override; //오버라이드는 위에서 작성한 내용이 있던없던 다시 작성하겠다
	virtual void Update() override;
	virtual void Render() override;
	virtual void Clear() override;

private:
	SDL_Texture* texture_intro_;
	SDL_Rect source_rectangle_intro_;
	SDL_Rect destination_rectangle_intro_;
};