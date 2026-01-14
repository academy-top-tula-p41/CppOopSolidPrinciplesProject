#pragma once
#include <iostream>

class Shape
{
	int x;
	int y;

public:
	virtual double Area() = 0;
};

class Rectangle : public Shape
{
protected:
	int width;
	int height;
public:

	int& Width() { return width; }
	int& Height() { return height; }
	
	double Area() override { return width * height; }
};

class Square : public Shape
{
	int side;
public:
	int& Side() { return side; }

	double Area() override { return side * side; }
};
