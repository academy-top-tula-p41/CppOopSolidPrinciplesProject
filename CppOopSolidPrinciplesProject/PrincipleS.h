#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <exception>

typedef std::map<std::string, std::string> ProductData;

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

class IReader
{
public:
	virtual ProductData Read() = 0;
};

class IValidator
{
public:
	virtual bool IsValid(ProductData data) = 0;
};

class ICreator
{
public:
	virtual Product* Create(ProductData data) = 0;
};

class ISaver
{
protected:
	std::string fileName;

public:
	ISaver(std::string fileName) : fileName{ fileName }{}

	virtual void Save(std::vector<Product*> products) = 0;
};

class StoreRefactor
{
	std::vector<Product*> products;
	
	IReader* reader;
	IValidator* validator;
	ICreator* creator;
	ISaver* saver;
public:

	StoreRefactor(
		IReader* reader,
		IValidator* validator,
		ICreator* creator,
		ISaver* saver)
		: reader{ reader },
		validator{ validator },
		creator{ creator },
		saver{ saver }{}

	void Process()
	{
		auto data = reader->Read();
		if (!validator->IsValid(data))
			throw new std::exception("Data of product not valid");

		auto product = creator->Create(data);
		products.push_back(product);
		
		saver->Save(products);
	}
};


class StringAdv : public std::string
{
public:
	static void Trim(std::string& str)
	{
		auto it1 = std::ranges::find_if(str, [](char symbol) {
			return symbol != ' ';
			});
		str.erase(str.begin(), it1);

		auto it2 = str.find_last_not_of(' ');
		str.erase(str.begin() + it2 + 1, str.end());
	}
};


class ConsoleReader : public IReader
{
public:
	ProductData Read() override
	{
		ProductData data;

		std::cout << "Input Name of Product: ";
		std::cin >> data["name"];

		std::cout << "Input Price of Product: ";
		std::cin >> data["price"];

		return data;
	}
};

class ProductValidator : public IValidator
{
public:
	bool IsValid(ProductData data) override
	{
		std::string name{ data["name"] };
		std::string price{ data["price"] };

		StringAdv::Trim(name);
		if (name.length() == 0)
			return false;

		int priceInt;
		try
		{
			StringAdv::Trim(price);
			if (price.length() == 0)
				throw 1;

			priceInt = std::stoi(price);

			if (priceInt <= 0)
				throw 1;
		}
		catch (...)
		{
			return false;
		}

		return true;
	}
};

class ProductCreator : public ICreator
{
public:
	Product* Create(ProductData data) override
	{
		StringAdv::Trim(data["name"]);
		StringAdv::Trim(data["price"]);

		std::string name = data["name"];
		int price = std::stoi(data["price"]);
		return new Product(name, price);
	}
};


class ProductTextSaver : public ISaver
{
public:
	ProductTextSaver(std::string fileName) : ISaver(fileName){}

	void Save(std::vector<Product*> products) override
	{
		std::ofstream fileOut(fileName, std::ios::out);

		for (auto product : products)
			fileOut << *product << "\n";

		fileOut.close();
	}
};

class ProductXmlSaver : public ISaver
{
public:

	ProductXmlSaver(std::string fileName) : ISaver(fileName) {}

	void Save(std::vector<Product*> products) override
	{
		std::ofstream fileOut(fileName, std::ios::out);

		fileOut << "<products>\n";

		for (auto product : products)
		{
			fileOut << "\t<product>\n";

			fileOut << "\t\t<name>" << product->Name() << "</name>\n";
			fileOut << "\t\t<price>" << product->Price() << "</price>\n";
			
			fileOut << "\t</product>\n";
		}

		fileOut << "</products>\n";

		fileOut.close();
	}
};