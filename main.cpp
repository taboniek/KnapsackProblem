#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std; 
int **tab;
int c;
int n;
clock_t start, stop; 
long stoper;

void read() {
	int p, w;
	int g = 0;
	string line;
	fstream file;


	file.open("example.txt", std::ios::in);
	if (file.good() == false)
		cout << "Could not open file!" << endl;
	else {
		getline(file, line);
		c = atoi(line.c_str());
		getline(file, line);
		n = atoi(line.c_str());
		tab = new int*[n+1];
		for (int i = 0; i < n; i++)
			tab[i] = new int[2];

		while (g<n) {
			file >> p >> w;
			tab[g][0] = p;
			tab[g][1] = w;
			g++;

		}
		file.close();
		cout << "File successfully loaded! " << endl;
	}
}

void result(int **backpack, bool **decision) {

	int i = n;
	int j = c;
	while (i) {
		if (decision[i][j] == 1) {
			cout << i << "  ";
			j = backpack[i - 1][j - tab[i - 1][1]];
			i -= 1;
		}
		if (decision[i][j] == 0) 
			i-=1;
		
	}
}

void dynamic_backpack(int **backpack, bool **decision ) {

	int i=0; 
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= c; j++)
		{
			if (tab[i - 1][1] > j)
			{
				backpack[i][j] = backpack[i - 1][j]; 
				decision[i][j] = 0;
			}
			if(tab[i-1][1]<=j) {
				if (backpack[i - 1][j] > (backpack[i - 1][j - tab[i - 1][1]] + tab[i - 1][0])) {
					backpack[i][j] = backpack[i - 1][j];
					decision[i][j] = 0;
				}
				else {
					backpack[i][j] = backpack[i - 1][j - tab[i - 1][1]] + tab[i - 1][0];
					decision[i][j] = 1;
				}
			}
		}
	}
}
void quickrandom(double tab_brute[], double left, double right)
{

	int losowe = rand() % n;
	double klucz = tab_brute[losowe];
	double x;
	int n, p;
	n = left;
	p = right;
	do
	{
		while (tab_brute[n]>klucz) n++;
		while (tab_brute[p]<klucz) p--;
		if (n <= p)
		{
			x = tab_brute[n];
			tab_brute[n] = tab_brute[p];
			tab_brute[p] = x;
			n++;
			p--;
		}
	} while (n <= p);
	if (p>left) quickrandom(tab_brute, left, p);
	if (n<right) quickrandom(tab_brute, n, right);

}

void brute_force() {

	double *tab_brute = new double[n];
	bool *seen = new bool [n];
	float m, k;
	int waga = 0;

	for (int i = 0; i < n; i++) {
		seen[i] = 0;
		m = tab[i][0];
		k = tab[i][1];
		tab_brute[i] = m/k;
	}
	quickrandom(tab_brute, 0, n-1);
	for (int i = 0; i < n; i++) {
		if (tab[i][1] + waga < c) {
			waga += tab[i][1];
			seen[i] = 1;
		}
	}
}

void brute_force_better() {
	
	int a = 0; 
	int x = 0; 
	int p; 
	int obj = 0, result =0;
	int maximum_result = 0; 

	int **tabb = new int*[n];
	for (int i = 0; i < n; i++)
		tabb[i] = new int[pow(2,n)];

	for (int i = 0; i < pow(2,n); i++, x++) {
		p = x;
		for (int j = n - 1; j >= 0; j--) {
			a = p % 2;
			p = p / 2;
			tabb[j][i] = a;
		}
	}
	int i = 0; 
	for (int j = 0; j < pow(2, n); j++) {
		for (i = 0; i < n; i++) {
			if (tabb[i][j] == 1) {
				result += tab[i][1];
				obj += tab[i][0];
			}
		}
		if (obj <= c && result > maximum_result) {
			maximum_result = result;
		}
		result = 0; obj = 0;

	}

}



int main()
{
	int menu;
	int a = 0;
	cout << " Welcome to the program that will help you pack." << endl << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	do {
		cout << "Press 1 if you are ready" << endl;
		cout << "Press 7 to end this program" << endl;
		cin >> menu;
		while (menu != 1 && menu != 7) {
			system("cls");
			cout << "Relax, you have as much time as you need to get ready." << endl;
			cout << " Press 1 if you are ready this time" << endl;
			cout << "Press 7 if you are never ready." << endl;
			cin >> menu;
		}
		if (menu == 1) {
			read();
			system("cls");

			if (menu == 7) {
				system("cls");
				cout << "OOkeyyy :(  " << endl;
				a = 1;
				system("pause");
				return 0;
			}


			cout << "Tell me what algorithm is to help you take only the most important things? " << endl;
			cout << "1. Dynamic programming." << endl;
			cout << "2.  Brute force" << endl;
			cout << "7. To end the program." << endl;
			cin >> menu;
			while (menu != 1 && menu != 2 && menu != 7) {
				system("cls");
				cout << "Select options again " << endl;
				cout << "1. Dynamic programming." << endl;
				cout << "2.  Brute force" << endl;
				cout << "7. To end the program." << endl;
				cin >> menu;

			}
			if (menu == 1) {
				system("cls");
				int** plecak = new int* [n + 1];
				for (int i = 0; i < n + 1; i++)
					plecak[i] = new int[c + 1];

				bool** decyzja = new bool* [n + 1];
				for (int i = 0; i < n + 1; i++)
					decyzja[i] = new bool[c + 1];

				for (int i = 0; i < c + 1; i++)
					plecak[0][i] = decyzja[0][i] = 0;
				for (int i = 0; i < n + 1; i++)
					plecak[i][0] = decyzja[i][0] = 0;

				start = clock();
				dynamic_backpack(plecak, decyzja);
				stop = clock();
				stoper = (long)(stop - start);
				cout << endl << " Dynamic algorithm time is: " << stoper << endl;

			}
			else if (menu == 2) {
				system("cls");
				start = clock();
				//brute_force();
				brute_force_better();
				stop = clock();
				stoper = (long)(stop - start);
				cout << endl << "Time for the brute force method is: " << stoper << endl;
			}
			else if (menu == 7) {
				system("cls");
				cout << "Okeeyy :( " << endl;
				a = 1;
				system("pause");
				return 0;
			}
		}
	} while (a == 0);
}
	
