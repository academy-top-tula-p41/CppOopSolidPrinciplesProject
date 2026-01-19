#pragma once
#include <iostream>

class IWalkable
{
public:
	virtual void Walk() = 0;
};

class IFlyable
{
public:
	virtual void Fly() = 0;
};

class ISwimable
{
public:
	virtual void Swim() = 0;
};


class IAnimal : public IWalkable, public IFlyable, public ISwimable
{
	std::string name;
public:
	IAnimal(std::string name) : name{ name }{}
};


class Dog : public IWalkable, public ISwimable
{

};