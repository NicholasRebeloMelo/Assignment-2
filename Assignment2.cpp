#include "Assignment2.h"
#include "Body.h"
#include <SDL.h>
#include <math.h>


Assignment2::Assignment2(SDL_Window* sdlWindow_) {
	window = sdlWindow_;
	elapsedTime = 0.0f;
	frameCount = 0L;
	for (int i = 0; i < NUM_BODIES; i++)
	{
		bodies[i] = nullptr;
	}
}

Assignment2::~Assignment2() {
}


bool Assignment2::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	projectionMatrix = MMath::viewportNDC(w, h) * MMath::orthographic(0.0f, 40.0f, 0.0f, 15.0f, 0.0f, 1.0f);
	bodies[0] = new Body("arcturus1.bmp", 90.0f, Vec3(5.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1);
	bodies[1] = new Body("mars1.bmp", 1.5f, Vec3(20.0f, 5.0f, .0f), Vec3(1.0f, 1.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1);
	bodies[2] = new Body("arcturus1.bmp", 90.0f, Vec3(30.0f, 5.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f), 1);
	for(int i = 0; i < 3; i++)
	if (bodies[i] == nullptr) {
		return false;
	}
	return true;
}

void Assignment2::OnDestroy() {
	for (int i = 0; i < NUM_BODIES; i++) {

		if (bodies[i]) {
			delete bodies[i];
			bodies[i] = nullptr;
		}
	}
}


void Assignment2::Update(const float time) {
	elapsedTime += time;

	//First Star 
	float planetStarX1 = bodies[0]->pos.x - bodies[1]->pos.x;// Direction Vector from star to planet
	float planetStarY1 = bodies[0]->pos.y - bodies[1]->pos.y;

	float radius1 = sqrt(planetStarX1 * planetStarX1 + planetStarY1 * planetStarY1);
	float magnatitudeForce1 = (1.0  * bodies[1]->mass * bodies[0]->mass) / (radius1 * radius1);
	float nPlanetX1 = planetStarX1 / radius1;// normalize planet
	float nPlanetY1 = planetStarY1 / radius1;
	float forceGravityX1 = magnatitudeForce1 * nPlanetX1; 
	float forceGravityY1 = magnatitudeForce1 * nPlanetY1;

	//Second Star
	float planetStarX2 = bodies[2]->pos.x - bodies[1]->pos.x;// Direction Vector from star to planet
	float planetStarY2 = bodies[2]->pos.y - bodies[1]->pos.y;

	float radius2 = sqrt(planetStarX2 * planetStarX2 + planetStarY2 * planetStarY2);
	float magnatitudeForce2 = (1.0  * bodies[1]->mass * bodies[2]->mass) / (radius2 * radius2);
	float nPlanetX2 = planetStarX2 / radius2;// normailize planet
	float nPlanetY2 = planetStarY2 / radius2;
	float forceGravityX2= magnatitudeForce2 * nPlanetX2;
	float forceGravityY2 = magnatitudeForce2 * nPlanetY2;

	//Apply Force
		bodies[1]->ApplyForce(Vec3(forceGravityX1 + forceGravityX2, forceGravityY1 + forceGravityY2, 0));
		bodies[1]->Update(time);
	/*
	for (int i = 0; i < NUM_BODIES; ++i) {
		if (bodies[i]) bodies[i]->Update(time);
	}*/
	//++frameCount;
}
void Assignment2::HandleEvents(const SDL_Event &event) {
	/*switch (event.type) {
	case SDL_KEYDOWN:
		printf("Key Press Detected\n");
		break;
	case SDL_KEYUP:
		printf("Key Press Detected\n");
		break;


	default:
		break;
	}*/
}
void Assignment2::Render() const {
	SDL_Rect imageRectangle;

	SDL_Surface *screenSurface = SDL_GetWindowSurface(window);

	SDL_FillRect(screenSurface, nullptr, SDL_MapRGB(screenSurface->format, 0xff, 0xff, 0xff));

	for (int i = 0; i < NUM_BODIES; i++) {
		Vec3 screenCoords = projectionMatrix * bodies[i]->pos;
		imageRectangle.h = bodies[i]->getImage()->h;
		imageRectangle.w = bodies[i]->getImage()->w;
		imageRectangle.x = screenCoords.x; /// implicit type conversions BAD - probably causes a compiler warning
		imageRectangle.y = screenCoords.y; /// implicit type conversions BAD - probably causes a compiler warning



		SDL_BlitSurface(bodies[i]->getImage(), nullptr, screenSurface, &imageRectangle);
	}
	SDL_UpdateWindowSurface(window);
}