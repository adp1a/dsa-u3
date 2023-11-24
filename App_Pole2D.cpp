#include <iostream>
#include "Pole2Duk.h"

void test() {
	Pole2Duk* pole1 = new Pole2Duk(2, 2);
	Pole2Duk* pole2 = new Pole2Duk(2, 2);
	
	pole1->SetValue(1, 0, 0);   // |  1  2 |
	pole1->SetValue(2, 0, 1);   // | -1  0 |
	pole1->SetValue(-1, 1, 0);  
	pole1->SetValue(0, 1, 1);  

	pole2->SetValue(3, 0, 0); // | 3  2 |
	pole2->SetValue(2, 0, 1); // | 1 -2 |
	pole2->SetValue(1, 1, 0);
	pole2->SetValue(-2, 1, 1);

	// | 4  4 |
	// | 0 -2 |
	Pole2Duk* poleVysledek = *pole1 + *pole2;
	
	// -----------------------------------------
	Pole2Duk* pole3 = new Pole2Duk(2, 3);
	Pole2Duk* pole4 = new Pole2Duk(3, 2);

	pole3->SetValue(1, 0, 0); // | 1  2  3 |
	pole3->SetValue(2, 0, 1); // | 4  5  6 |
	pole3->SetValue(3, 0, 2); 
	pole3->SetValue(4, 1, 0); 
	pole3->SetValue(5, 1, 1);
	pole3->SetValue(6, 1, 2);

	pole4->SetValue(7, 0, 0); // | 7   8   | 
	pole4->SetValue(8, 0, 1); // | 9   10  |
	pole4->SetValue(9, 1, 0); // | 11  12  |
	pole4->SetValue(10, 1, 1);
	pole4->SetValue(11, 2, 0);
	pole4->SetValue(12, 2, 1);

	// |58   64|
	// |139 154|
	Pole2Duk* poleVysledek2 = *pole3 * *pole4;

	// --------------------------------------------
	std::cout << "Vysledek 1:\n";
	poleVysledek->tisk(*poleVysledek);
	std::cout << "\nVysledek 2:\n";
	poleVysledek2->tisk(*poleVysledek2);
}


int main()
{
	test();
	return 0;
}