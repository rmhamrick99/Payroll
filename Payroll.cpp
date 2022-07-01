#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>

using namespace std;

class PayrollReports
{
public:
	void mainLine();
private:
	string PT1;
	string PT2;
	string PT3;
	string HL1;

	double dStateTax;
	double dNetPay;
	double dGross;
	string sName1;
	string sName2;
	double dFedTax;
	int iEmployeeNum;
	double dFica;
	double dTotalGross;
	double dTotalStateTax;
	double dTotalFedTax;
	double dTotalFica;
	double dTotalNetPay;


	ifstream payFile;
	bool bEndFlag;
	void accumulate();
	void calculate();
	void eoj();
	void initialization();
	void process();
	void readIt();
	void writeIt();
	void OpenFile(void);
	void PrnHeadings(void);


	
};

int main()
{
	PayrollReports PR1;
	PR1.mainLine();

	system("pause");
	return 0;
}

void PayrollReports::accumulate()
{
	dTotalGross = dTotalGross + dGross;
	dTotalStateTax = dTotalStateTax + dStateTax;
	dTotalFedTax = dTotalFedTax + dFedTax;
	dTotalFica = dTotalFica + dFica;
	dTotalNetPay = dTotalNetPay + dNetPay;
	return;
}

void PayrollReports::calculate()
{
	dNetPay = dGross - (dStateTax + dFedTax + dFica);
	return;
}

void PayrollReports::eoj()
{
	//print totals
	cout << "Total Gross Pay: " << dTotalGross << endl;
	cout << "Total State Tay: " << dTotalStateTax << endl;
	cout << "Total Federal Tax: " << dTotalFedTax << endl;
	cout << "Total Fica: " << dTotalFica << endl;
	cout << "Total Net Pay: " << dTotalNetPay <<endl << endl;

	cout << "The End - Totals are Above";
	payFile.close();
}

void PayrollReports::initialization()
{
	// setting up the report title here
	PT1 = "Company Pay System";
	PT2 = "Payroll Report";
	PT3 = "February 2019";
	HL1 = "EmpNum   EmpName   Gross  StateTax  FedTax  Fica    NetPay";
	
	bEndFlag = true;

	OpenFile();
	if (!payFile.fail())
	{
		PrnHeadings();
		readIt();
		bEndFlag = false;
	}
	
}

void PayrollReports::mainLine()
{
	initialization();
	while (bEndFlag == false)
	{
		process();
	}
	eoj();
}

void PayrollReports::process()
{
	calculate();
	accumulate();
	writeIt();
	readIt();
}

void PayrollReports::readIt()
{
	payFile >> iEmployeeNum >> sName1 >> sName2 >> dGross >> dStateTax >> dFedTax >> dFica;

	if (iEmployeeNum == 0)
		bEndFlag = true;
}

void PayrollReports::writeIt()
{
	cout <<setw(4) << iEmployeeNum
		<< setw(6)<< sName1<< setw(6) << sName2
		<< setw(7) << dGross 
		<< setw(8) << dStateTax
		<< setw(9) << dFedTax << setw(9) << dFica
		<< setiosflags(ios::fixed)
		<< setiosflags(ios::showpoint)
		<< setw(10) << setprecision(2) << dNetPay << endl << endl;
	return;
}

void PayrollReports::OpenFile(void)
{
	payFile.open("payroll.dat");
	if (payFile.fail())
		cout << "Payroll file open failed." << endl;
	return;
}
void PayrollReports::PrnHeadings(void)
{
	// print the report title here
	cout << PT1 << endl;
	cout << PT2 << endl;
	cout << PT3 << endl << endl;
	cout << HL1 << endl << endl;
}

