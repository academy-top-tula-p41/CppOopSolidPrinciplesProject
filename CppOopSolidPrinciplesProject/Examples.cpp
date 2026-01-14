#include "Examples.h"

void Examples::PrincipleSExample()
{
	/*Report report("Hello world");

	IReportPrinter* printer = new ReportTextPrinter(&report);
	printer->Print();

	printer = new ReportHtmlPrinter(&report);
	printer->Print();*/

	/*Store store;
	store.Process();*/

	StoreRefactor store(
		new ConsoleReader(),
		new ProductValidator(),
		new ProductCreator(),
		new ProductXmlSaver("products.xml"));

	char answer;

	do
	{
		std::cout << "Iput product? <y/n>: ";
		std::cin >> answer;

		if (answer == 'n')
			break;

		store.Process();

	} while (true);
}

void Examples::PrincipleOExample()
{
	Discount* discount = new Discount();
	std::cout << discount->GetDiscount(1000) << "\n";

	delete discount;

	discount = new VipDiscount();
	std::cout << discount->GetDiscount(1000) << "\n";
}
