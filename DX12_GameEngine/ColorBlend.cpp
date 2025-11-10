#include "ColorBlend.h"

void Color::Add()
{
}

Color Color::operator+(const BaseColor& code) const
{
	Color result;
	result.code.red = this->code.red + code.red;
	result.code.blue = this->code.blue + code.blue;
	result.code.green = this->code.green + code.green;
	result.code.alfa = this->code.alfa + code.alfa;
	return result;
}