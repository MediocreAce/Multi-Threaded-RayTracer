#include "Core.h"


///Deconstructor which handles deleting/cleaning/Quitting
/// SDL window, renderer and SDL itself
Core::~Core()
{
	///Delete the renderer
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	///Delete the window
	SDL_DestroyWindow(window);
	window = NULL;

	///Quit SDL
	SDL_Quit();
	///Log that THIS class' object has been deleted fully
	LOG(B_BLUE << "EVENT: Cleaned Program");
}

///Returns if SDL is initialised correctly
bool Core::init()
{
	///============SDL============///
	///Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		///If error, Log error then return error to main()
		LOG(B_RED << "\nERROR: Initializing SDL: " << SDL_GetError());
		return false;
	}
	///If successful, then return success/true
	return true;
}

///Asks user how many threads to divide the work into
int Core::askThreadCount()
{
	///For infinity
	for (; ;)
	{
		///Clear the console screen
		/// and ask user how many threads they'd like
		///  to split the screen into
		system("CLS");
		LOG(B_YELLOW << "Max Threads: " << MAX_THREADS
			<< "\nEnter the amount of threads you want to run the program with:");

		///Create a temporary string and get the user's input
		std::string line;
		std::getline(std::cin, line);

		///If the input is greater than the MAX_THREADS value
		/// AND the input is not a digit/number
		if (line.size() > 1 || !isdigit(line[0]))
		{
			///Log error, the user must input a number lower than MAX_THREADS
			LOG(B_RED << "\nERROR: Input betwen 0 and " << MAX_THREADS);
			///Wait for user to read error
			SDL_Delay(2000);
			///Return to start of for(; ;) to ask again
			continue;
		}

		///If valid input
		///create an int and set to the input value
		int choice = std::stoi(line);
		///If the input is greater than 0
		/// AND lesser than MAX_THREAD
		if (choice > 0 && choice <= MAX_THREADS)
		{
			///Log to show correct input, and return the choice
			LOG(B_YELLOW << "Threads for Program: " << choice);
			return choice;
		}

		///This is an insurance incase previous if statement fails
		/// Treat as an error, wait for 2 seconds, then return to for(; ;)
		LOG(B_RED << "\nERROR: Input betwen 0 and " << MAX_THREADS);
		SDL_Delay(2000);
	}
	///This should not be hit EVER
	/// HOWEVER if error, then just return
	///  run program with 1 thread
	return 1;
}

///Divide the screen in different chunks/sections
	/// Each thread handles one of those sections
void Core::divideScreen(const int& threadCount,
	std::vector<SDL_Rect>& _sectionRectList)
{
	///Divide the screen vertically
	///  1  |  2  |  3  |  4  |  5
	///     |     |     |     |
	int rectWidth = windowRect.w / threadCount;
	for (int i = 0; i < threadCount; i++)
	{
		///Add each new section to the section vector/list
		_sectionRectList.push_back(SDL_Rect{ rectWidth * i, 0, rectWidth, windowRect.h });
	}
}

///Run a loop which displays the realtime calculations
	/// to the SDL Renderer
void Core::programLoop()
{
	///Set threadCount to the return
	/// of the function askThreadCount()
	///  (GET USER INPUT)
	int threadCount = askThreadCount();

	///Vector containing the color values
	/// of EACH pixel on the renderer
	std::vector<std::vector<glm::ivec3>> pixelData;
	{
		///Time this scope
		Timer t("PixelData Storage:");
		///For each row on the window
		for (int y = 0; y < windowRect.h; y++)
		{
			///Create a temporary vector
			std::vector<glm::ivec3> tmp;
			///For each column on the window
			for (int x = 0; x < windowRect.w; x++)
			{
				///Add black to the temporary vector
				tmp.emplace_back(0, 0, 0);
			}
			///Add the temporary vector to the pixelData storage
			pixelData.emplace_back(tmp);
		}
	}


	///Vector containing dimensions of each section of the window
	std::vector<SDL_Rect> sectionRectList;
	///Vector holding each thread the program uses
	std::vector<std::thread> threadList;

	///Call the function divideScreen(...)
	/// sectionRectList is a reference which hold new dimension sizes
	divideScreen(threadCount, sectionRectList);


	///============Sphere============///
	///Position of the sphere in the screen (middle, back a bit)
	glm::vec3 spherePosition(windowRect.w / 2, windowRect.h / 2, 50.0f);
	///Radius of the sphere
	float sphereRadius = 130.0f;
	///Color of the sphere (RGB) : (greeny blue)
	glm::vec3 sphereColor(0.0f, 175.0f, 200.0f);


	///==========Light Src==========///
	///Position of light source in scene (Top Left = World Origin)
	glm::vec3 lightPosition(0.0f, 0.0f, 0.0f);
	///Light Source's radius
	float lightRadius = 1.0f;
	///Light source's color (RGB) : (White)
	glm::vec3 lightColor(255.0f, 255.0f, 255.0f);


	///============Create Tracer============///
	///Create a Tracer class object and pass in the
	/// Sphere's values
	/// Light Source's values
	Tracer tracer = Tracer(spherePosition, sphereRadius, sphereColor,
		lightPosition, lightRadius, lightColor);


	///==========Create Window==========///
	{
		///Time how long to creat a SDL Window
		Timer t("Created Window:\t");
		///Create an SDL Window and set to class' values
		window = SDL_CreateWindow("RayTracer", windowRect.x, windowRect.y, windowRect.w, windowRect.h, SDL_WINDOW_SHOWN);
		///Check if window is created successfuly
		/// If successful, move on
		if (!window)
		{
			///If error, Log error then return to main()
			LOG(B_RED << "\nERROR: Creating SDL Window: " << SDL_GetError());
			return;
		}
	}


	///=========Create Renderer=========///
	{
		///Timer to time creation of renderer
		Timer t("Created Renderer:");
		///Create an SDL Renderer on the SDL Window just created
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		///Check if renderer is successfully created
		/// If success, move on
		if (!renderer)
		{
			///If error, Log error, and return to main()
			LOG(B_RED << "\nERROR: Creating SDL Renderer: " << SDL_GetError());
			return;
		}
	}


	///Usedd to split up console to read faster
	/// (For debugging)
	LOG(B_MAGENTA << "========================================");
	///=======Loop Viewing=======///

	///Create a enumeration holding 4 values
	/// Directional values (Up, Down, Left, Right)
	///  Set the default value to Left
	///   This enumeration is used to direct where
	///    the light source is moving to
	enum
	{
		UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
	}dir = LEFT;
	///This is the speed the light travels
	/// around the screen/scene
	int lightSpeed = 20;

	///Program loop, which calculates
	/// EVERY pixel on every frame
	///  then outputs colors to the SDL Renderer
	bool quit = false;
	while (!quit)
	{
		///Timer in scope called every loop
		/// Used to see how long EACH frame took
		///  to calculate data then render
		Timer t("Frame Delay:");

		///============Handle Input============///
		///Get User's input
		SDL_Event e;
		SDL_PollEvent(&e);
		///Check if user closed window
		if (e.type == SDL_QUIT)
		{
			///If closed window, Log event
			/// Then break the while loop to exit program
			LOG(B_YELLOW << "INPUT: Quitting");
			quit = true;
			return;
		}


		///===============Update===============///
		///Calculate the next position the light source has
		/// by using it's current direction
		///  If the light has reached it's next corner,
		///   then turn 90 degrees clockwise
		switch (dir)
		{
		case UP:
			lightPosition.y -= lightSpeed;
			if (lightPosition.y < 0)
				dir = RIGHT;
			break;

		case DOWN:
			lightPosition.y += lightSpeed;
			if (lightPosition.y > windowRect.h)
				dir = LEFT;
			break;

		case LEFT:
			lightPosition.x -= lightSpeed;
			if (lightPosition.x < 0)
				dir = UP;
			break;

		case RIGHT:
			lightPosition.x += lightSpeed;
			if (lightPosition.x > windowRect.w)
				dir = DOWN;
			break;
		}
		///Update the tracer object's light source position
		/// for the next calculation
		tracer.setLightPosition(lightPosition);


		///============Create Scene============///
		///For every divided section on the screen
		for (int i = 0; i < (int)sectionRectList.size(); i++)
		{
			///Create a std::thread
			/// running the Tracer's function createScene(...)
			///  Then add that thread to the vector of threads
			threadList.push_back(std::thread(&Tracer::createScene, tracer,
				std::ref(pixelData), sectionRectList[i], i));
		}


		///==========Wait For Threads==========///
		///For each thread in the thread vector
		for (size_t curThread = 0; curThread < threadList.size(); curThread++)
		{
			///If the current thread need to be waited for
			if (threadList[curThread].joinable())
				///Wait for the thread to finish before continuing
				threadList[curThread].join();
		}
		///When all threads are finished calculating their pixels
		/// clear the thread vector
		threadList.clear();

		///===========Render Output===========///
		///Clear the renderer's previous frame data
		SDL_RenderClear(renderer);

		///For each section/chunk of the window
		int i = 0;
		for (SDL_Rect rect : sectionRectList)
		{
			///For each row of the window
			for (int y = rect.y; y < rect.h; y++)
			{
				///For each column of the window
				for (int x = rect.x; x < (rect.w + (rect.w * i)); x++)
				{
					///Create temporary (RGB) storage and set to current pixel's color
					glm::ivec3 color = pixelData[y][x];
					///Set the next drawn pixel's color to the current pixel's color
					SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 255);
					///Draw the current pixel color at current pixel coordinates
					SDL_RenderDrawPoint(renderer, x, y);
				}
			}
			i++;
		}
		
		///Render the drawn pixels to the SDL Renderer/Window
		SDL_RenderPresent(renderer);
	}
}