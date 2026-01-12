#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <exception>

// S: Single Responsiblity Principle

class Report
{
	std::string text;
public:
	Report(std::string text = "")
		: text{ text } {};

	std::string Text() const { return text; }

	void GoToFirstPage()
	{
		std::cout << "Go to First Page\n";
	}
	void GoToLastPage()
	{
		std::cout << "Go to Last Page\n";
	}
	void GoToPage(int page)
	{
		std::cout << "Go to " << page << " Page\n";
	}
	/*void Print()
	{
		std::cout << "Report:\n";
		std::cout << text;
	}*/
};

class IReportPrinter
{
protected:
	Report* report;
public:
	IReportPrinter(Report* report)
		: report{ report } {};
	
	virtual void Print() = 0;
};

class ReportTextPrinter : public IReportPrinter
{
public:
	ReportTextPrinter(Report* report) : IReportPrinter(report){}

	void Print() override
	{
		std::cout << "Text Report Print:\n";
		std::cout << report->Text() << "\n";
	}
};

class ReportHtmlPrinter : public IReportPrinter
{
public:
	ReportHtmlPrinter(Report* report) : IReportPrinter(report) {}

	void Print() override
	{
		std::cout << "Html Report Print:\n";
		std::cout << "<p>" << report->Text() << "</p>\n";
	}
};

//
class Product
{
	std::string name;
	int price;
public:
	Product(std::string name, int price)
		: name{ name }, price{ price } {}

	std::string Name() const { return name; }
	int Price() const { return price; }

	friend std::ostream& operator<<(std::ostream& out, const Product& product)
	{
		out << "Product Name: " << product.Name() << ", Price: " << product.Price();
		return out;
	}
};

class Store
{
	std::vector<Product*> products;

	void Trim(std::string& str)
	{
		auto it1 = std::ranges::find_if(str, [](char symbol) {
			return symbol != ' ';
			});
		str.erase(str.begin(), it1);

		auto it2 = str.find_last_not_of(' ');
		str.erase(str.begin() + it2 + 1, str.end());
	}

public:
	void Process()
	{
		// inpud product
		std::string name;
		std::string price;

		std::cout << "Input Name of Product: ";
		std::cin >> name;

		std::cout << "Input Price of Product: ";
		std::cin >> price;

		// validate product
		Trim(name);
		if (name.length() == 0)
			throw new std::exception("Empty name of product");

		int priceInt;
		try
		{
			priceInt = std::stoi(price);
			if (priceInt <= 0)
				throw;
		}
		catch (...)
		{
			throw new std::exception("Invalid price of product");
		}

		// save to container
		products.push_back(new Product(name, priceInt));

		// save to file
		std::ofstream fileOut("products.data", std::ios::out);
		
		for (auto product : products)
			fileOut << *product << "\n";

		fileOut.close();
	}
};
