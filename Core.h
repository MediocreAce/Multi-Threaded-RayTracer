#pragma once
///Include ability to create a vector(list) of data types
#include <vector>
///Used to create threads to optimise workflow
#include <thread>

///Used to render each pixel out to the window
#include <SDL.h>
///Used for basic glm data types and functions
#include <glm.hpp>

///Used to Log errors or events to the console
#include "Utility/Log.h"
///Used to time certain processes for debugging
#include "Utility/Timer.h"

///Used to call a Tracer class which handles calculating each pixel
#include "Tracer.h"


///Class which handles rendering,
///  and dividing the workflow into threads
class Core
{
private:
	///Window used to add a renderer
	SDL_Window* window = nullptr;
	///Renderer which visualises the calculated pixels
	SDL_Renderer* renderer = nullptr;
	///The x, y Position, Width, Height of the window
	const SDL_Rect windowRect{ 30, 50, 500, 500 };

	///The maximum amount of threads the program can run
	/// To make sure the user doesn't crash their setup so easily
	const int MAX_THREADS = 5;

public:
	///Constructor
	Core() { }
	///Deconstructor which handles deleting/cleaning/Quitting
	/// SDL window, renderer and SDL itself
	~Core();
	
	///Returns if SDL is initialised correctly
	bool init();
	
	///Asks user how many threads to divide the work into
	int askThreadCount();
	
	///Divide the screen in different chunks/sections
	/// Each thread handles one of those sections
	void divideScreen(const int& threadCount,
		std::vector<SDL_Rect>& _sectionRectList);

	///Run a loop which displays the realtime calculations
	/// to the SDL Renderer
	void programLoop();
};