/*
Sloan Kiechel
ssk0006
hw2.cpp
compile hw2.cpp then run it.
*/

#include <iostream>
using namespace std;

int main()
{
	//Format output
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	//Get information from user
	cout << "Loan Amount: ";
	double loanAmount;
	cin >> loanAmount;
	cout << "Interest rate (% per year): ";
	double rate;
	cin >> rate;
	cout << "Monthly Payments: ";
	double payment;
	cin >> payment;

	//change interest to a decimal
	rate = rate/100;
	//Make it monthly interest
	rate = rate / 12;

	//Initialize variables
	double balance = loanAmount;
	double interest = 0.0;
	double principal = 0.0;
	double totalInterest = 0.0;
	int month = 0;
	//make sure monthly payment is enough to pay interest
	bool canPay;
	interest = balance * rate;
	if (payment <= interest) {
		cout << "You will need a higher monthly payment, otherwise you will not be able to pay off the loan" << endl;
		canPay = false;
	}
	else {
		canPay = true;
	}
	if (canPay) {
		//Start table (format it)
		cout << "******************************************************" << endl;
		cout << "	Amortization Table" << endl;
		cout << "******************************************************" << endl;
		cout << "Month\tBalance    Payment\tRate\tInterest  Principal" << endl;
		cout << "0\t" << loanAmount << "    N/A\t   N/A\tN/A\t  N/A" << endl;

		//Caclulate each monthly payment
		while (balance > 0.0) {
			month++;
			interest = balance * rate;
			totalInterest = totalInterest + interest;
			//Checks if payment is more than what we can actually pay
			if (payment > (balance + interest)) {
				payment = balance + interest;
			}
			principal = payment - interest;
			balance = balance - principal; 
			//Output results
			cout << month << "\t$" << balance << "    $" << payment << "\t" << rate * 100 << "\t$" << interest << "\t$" << principal << endl;
		}
		//output total numbers
		cout << "******************************************************" << endl << endl;
		cout << "It takes " << month << " months to pay off the loan." << endl;
		cout << "Total interest paid is: $" << totalInterest << endl;
	}
}