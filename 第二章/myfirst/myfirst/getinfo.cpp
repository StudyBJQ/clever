#include <iostream>
using namespace std;
int getinfo()
{
	int carrots;
	cout << "How many carrots do you have?" << endl;
	cin >> carrots;
	cout << "Here are two more.";
	carrots = carrots + 2;
	cout << "Now you have " << carrots << " carrots." << endl;
	return 0;
}