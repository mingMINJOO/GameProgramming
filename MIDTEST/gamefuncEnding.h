#pragma once

#include "gamefunc.h"

class Ending : public PhaseInterface{
public:
	Ending();
	~Ending();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Clear() override;

private:
	SDL_Texture* texture_ending_;
	SDL_Rect source_rectangle_ending_;
	SDL_Rect destination_rectangle_ending_;
};