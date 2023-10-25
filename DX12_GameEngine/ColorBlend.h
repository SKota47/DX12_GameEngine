#pragma once

/*-------
–¢ŽÀ‘•‚Å‚·
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
	void operator+(const BaseColor code);
private:
	BaseColor code;
};