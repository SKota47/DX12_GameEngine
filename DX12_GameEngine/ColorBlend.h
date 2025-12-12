#pragma once

/*-------
�������ł�
-------*/

struct BaseColor
{
	unsigned int red;
	unsigned int blue;
	unsigned int green;
	unsigned int alfa;
};

class Color
{
public:
	void Add();
	Color operator+(const BaseColor& code) const;
private:
	BaseColor code;
};