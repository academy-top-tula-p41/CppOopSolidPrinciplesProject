// CppOopSolidPrinciplesProject.cpp 
#include <iostream>

#include "PrincipleS.h"

int main()
{
	/*Report report("Hello world");

	IReportPrinter* printer = new ReportTextPrinter(&report);
	printer->Print();

	printer = new ReportHtmlPrinter(&report);
	printer->Print();*/

	Store store;
	store.Process();
}

