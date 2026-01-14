#pragma once
#include <iostream>

class Discount
{
public:
	virtual double GetDiscount(double amount)
	{
		return amount * 0.1;
	}

	/*double GetDiscount(double amount, std::string type)
	{
		if (type == "vip")
			return amount * 0.3;

		return amount * 0.1;
	}*/
};

class VipDiscount : public Discount
{
public:
	double GetDiscount(double amount) override
	{
		return amount * 0.3;
	}
};




class OrderAbstract
{
public:
	virtual void Payment() = 0;
};

class CashOrder : public OrderAbstract
{
public:
	void Payment() override
	{
		std::cout << "Cash payment\n";
	}
};

class CardOrder : public OrderAbstract
{
public:
	void Payment() override
	{
		std::cout << "Card payment\n";
	}
};

class CryptoOrder : public OrderAbstract
{
public:
	void Payment() override
	{
		std::cout << "Crypto payment\n";
	}
};


class IPayment
{
public:
	virtual void Pay() = 0;
};

class Order : public IPayment
{
	IPayment* payment;
public:
	Order(IPayment* payment) : payment{ payment }{}

	IPayment*& Payment() { return payment; }
	
	void Pay() override
	{
		payment->Pay();
	}
};

class CashPayment : public IPayment
{
public:
	void Pay() override
	{
		std::cout << "Cash payment\n";
	}
};