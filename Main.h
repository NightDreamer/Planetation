#pragma once
#include <iostream>
#include <cmath>
#include "SFML\OpenGL.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
const float  PI = 3.14159265358979f;

struct Vars
{
	Vars(){ running = true; howtoplay = false; };
	bool running, howtoplay;
};