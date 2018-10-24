#ifndef Assignment2_H
#define Assignment2_H

#include "MMath.h"
#define NUM_BODIES 3
#include "Scene.h"

//#include <SDL.h>

using namespace MATH;

class Assignment2 : public Scene {
private:
	SDL_Window * window;

	Matrix4 projectionMatrix;

	Body* bodies[NUM_BODIES];
	float elapsedTime;
	unsigned long frameCount;

public:
	Assignment2(SDL_Window* sdlWindow);
	~Assignment2();
	bool OnCreate();
	void OnDestroy();
	void Update(const float time);
	void Render()const;
	void HandleEvents(const SDL_Event &event_ );
};

#endif


