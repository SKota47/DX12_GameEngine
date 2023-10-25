#include "ColorBlend.h"

void Color::Add()
{
}

void Color::operator+(const BaseColor code)
{
	this->code.red += code.red;
	this->code.blue += code.blue;
	this->code.green += code.green;
}