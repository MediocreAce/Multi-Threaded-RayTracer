#pragma once

///Reset the cout stream's color
#define RESET	"\033[0m"

///======Bold Text Colour======///
///Defines different color values for debugging purposed
#define B_BLACK		"\033[1m\033[30m"
#define B_WHITE		"\033[1m\033[37m"
#define B_RED		"\033[1m\033[31m"
#define B_MAGENTA	"\033[1m\033[35m"
#define B_GREEN		"\033[1m\033[32m"
#define B_YELLOW	"\033[1m\033[33m"
#define B_BLUE		"\033[1m\033[34m"
#define B_CYAN		"\033[1m\033[36m"

///Include ability to std::cout to the console
#include <iostream>

///Define a macro which cout's the given message
/// then resets the color value, and end line
#define LOG(x) \
	std::cout << x << RESET << std::endl