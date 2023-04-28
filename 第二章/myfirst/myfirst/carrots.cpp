#include <iostream>
using namespace std;
int carrots()
{
	int carrot;
	carrot = 25;
	cout << "I have ";
	cout << carrot;
	cout << " carrots_1.";
	cout << endl;
	carrot = carrot - 1;
	cout << "Crunch,crunch.Now I have " << carrot << " carrots_2." << endl;
	carrot = carrot - 2;
	cout << "Crunch,crunch.Now I have "
		<< carrot
		<< " carrots_3."
		<< endl;
	return 0;
}