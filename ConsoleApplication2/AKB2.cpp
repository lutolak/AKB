// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>

using namespace std;

ifstream wejscie;
ofstream wyjscie;

int** maciezNastepnikow;
int** maciezPopszednikow;
int** maciezPomocnicza;
int** maciezWyjsciowa;

int liczbaWierzcholkow = 0;

void stwozNatepniki()
{
	maciezNastepnikow = new int*[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		maciezNastepnikow[i] = new int[liczbaWierzcholkow];
	}

	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			maciezNastepnikow[i][j] = 0;
			cout << maciezNastepnikow[i][j] << " ";
		}
		cout << endl;
	}
}
void stozPopszedniki()
{
	maciezPopszednikow = new int*[liczbaWierzcholkow];

	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		maciezPopszednikow[i] = new int[liczbaWierzcholkow];
	}

	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		for (int j = 0; j < liczbaWierzcholkow; j++)
		{
			maciezPopszednikow[i][j] = 0;
		}
	}
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		for (int j = 0; j < liczbaWierzcholkow; j++)
		{
			if (maciezNastepnikow[i][j] == 1)
			{
				maciezPopszednikow[j][i] = 1;
			}
		}
	}
	for (int i = 0; i < liczbaWierzcholkow; i++)
	{
		for (int j = 0; j < liczbaWierzcholkow; j++)
		{
			cout << maciezPopszednikow[i][j] << " ";
		}
		cout << endl;
	}
}


bool sprawdzLinowosc(int i, int j, int k)
{
	//nastepniki wiersza1 nie powinny byæ powszednikami wiersza2
	//czy nastepniki a sa powszednikami b?

	//Za Rybarczyk: 
	//	je¿eli wieszcho³ki maj¹ wspólne nastêpniki ->
	//	->	Musz¹ mieæ identyczne zbiory nastêpników AND roz³¹czne zbiory poprzedników


	/** sprawdzanie indentycznych nastepnikow*/
	for (int kolumna = k; kolumna<liczbaWierzcholkow; kolumna++)
	{
		if (maciezNastepnikow[i][kolumna] && maciezPopszednikow[j][kolumna])
		{
			;
		}
		else
		{
			return false;
		}
	}
	/**sprawdzanie rozlocznosci zb. powszczednikow*/
	for (int x = 0; x<liczbaWierzcholkow; x++)
	{
		if ((maciezPopszednikow[i][x] != maciezPopszednikow[j][x]) || (maciezPopszednikow[i][x] == 0 && maciezPopszednikow[j][x] == 0))
		{
			;
		}
		else
		{
			return false;
		}
	}

	return true;
}

void transformacja()
{
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	//tworznie matrycy pomocniczej dla transformacji
	maciezPomocnicza = new int*[liczbaWierzcholkow];
	for (int i = 0; i< liczbaWierzcholkow; i++)
	{
		maciezPomocnicza[i] = new int[2];
	}

	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	//tworzenie krawedzi grafu orginalnego
	//	for(int i=0; i< liczbaWierzcholkow; i++)
	//	{
	//		maciezWyjsciowa[i] = new int [2];
	//	}


	//	for(int i=0; i< liczbaWierzcholkow; i++)
	//	{
	//		maciezWyjsciowa[i][0] = 0;
	//		maciezWyjsciowa[i][1] = 0;
	//	}


	cout << "@@@@@@@@@vvvvvvvvvvvvvvvv@@@@@@@@@@" << endl;


	//tworzenie matrycy dla grafu orginalnego
	for (int i = 0; i< liczbaWierzcholkow; i++)
	{
		maciezPomocnicza[i][0] = i;
		maciezPomocnicza[i][1] = i + liczbaWierzcholkow;
	}
	int temp = 0;
	for (int i = 0; i< liczbaWierzcholkow; i++)
	{
		//szukamy jakiejkolwiek jedynki
		for (int j = 0; j< liczbaWierzcholkow; j++)
		{
			//znalezienie nastepnika
			if (maciezNastepnikow[i][j] == 1)
			{
				//zapamietanie konca krawedzi(posrednio)
				temp = maciezPomocnicza[i][1];
				//koniec krawedzi i staje sie poczatkiem krawedzi j
				maciezPomocnicza[i][1] = maciezPomocnicza[j][0];// tu bu³o "==", zmieni³em
				for (int c = 0; c<liczbaWierzcholkow; c++)
				{
					if (maciezPomocnicza[c][0] == temp)
					{
						maciezPomocnicza[c][0] = maciezPomocnicza[j][0];
					}
				}
			}
		}
	}
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;

	for (int i = 0; i< liczbaWierzcholkow; i++)
	{
		cout << maciezPomocnicza[i][0] << " " << maciezPomocnicza[i][1] << endl;

	}
	cout << "@@''''''''''''''''''''''''''''@@@@@@@@" << endl;

	vector<int> zestawWartosciWynikowych;
	cout << "'''''''''''''111111111111''''''''''''" << endl;
	for (int i = 0; i<liczbaWierzcholkow; i++)
	{
		cout << "''''''''''''''''''''''''''''" << endl;
		int a = maciezPomocnicza[i][0];
		int b = maciezPomocnicza[i][1];
		zestawWartosciWynikowych.push_back(a);
		zestawWartosciWynikowych.push_back(b);
	}

	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	sort(zestawWartosciWynikowych.begin(), zestawWartosciWynikowych.end());
	set<int> unikalneWartosci(zestawWartosciWynikowych.begin(), zestawWartosciWynikowych.end());

	int podmieniacz = 0; //indeks w matrycy wynikowej

	for (int x = 0; x<zestawWartosciWynikowych.size(); x++)
	{
		int sprawdzanie = zestawWartosciWynikowych[x]; //wg tej zmaiennej bedziemy patrzec na nasza dwukolumnowa maciez
		for (int y = 0; y<liczbaWierzcholkow; y++)
		{
			if (maciezPomocnicza[y][0] == sprawdzanie)
			{
				maciezPomocnicza[y][0] = podmieniacz;
			}
			if (maciezPomocnicza[y][1] == sprawdzanie)
			{
				maciezPomocnicza[y][1] = podmieniacz;
			}
		}
		podmieniacz++;
	}
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	for (int i = 0; i< liczbaWierzcholkow; i++)
		cout << maciezPomocnicza[i][0] << " " << maciezPomocnicza[i][1] << endl;
}

int main()
{
	string nazwaPliku = "sprz1.txt";
	//	cout<<"wprowadz nawzwe pliku"<<endl;
	//	cin>>nazwaPliku;

	wejscie.open(nazwaPliku.c_str());
	int liczbaNastepnikow = 0;
	int ktoryNastepnik = 0;
	bool jestSprzezony = false;

	while (wejscie) {
		wejscie >> liczbaWierzcholkow;
		stwozNatepniki();
		for (int i = 0; i < liczbaWierzcholkow; i++) {
			wejscie >> liczbaNastepnikow;
			for (int j = 0; j < liczbaNastepnikow; j++) {
				wejscie >> ktoryNastepnik;
				maciezNastepnikow[i][ktoryNastepnik] = 1;
			}
		}
		break;
	}

	cout << endl << endl;
	for (int i = 0; i < liczbaWierzcholkow; i++) {
		for (int j = 0; j < liczbaWierzcholkow; j++) {
			cout << maciezNastepnikow[i][j] << " ";
		}
		cout << endl;
	}

	/**SPRZEZENIE**/
	for (int wiersz1 = 0; wiersz1<liczbaWierzcholkow; wiersz1++)
	{
		for (int wiersz2 = wiersz1 + 1; wiersz2<liczbaWierzcholkow; wiersz2++)
		{
			if (maciezNastepnikow[wiersz1][0] == maciezNastepnikow[wiersz2][0])
			{
				for (int kolumna = 1; kolumna<liczbaWierzcholkow; kolumna++)
				{
					if (maciezNastepnikow[wiersz1][kolumna] != maciezNastepnikow[wiersz2][kolumna])
					{
						if (maciezNastepnikow[wiersz1][0] == 0)
						{
							goto F;
						}
						jestSprzezony = false;
						goto S;
					}
					if (kolumna == liczbaWierzcholkow - 1)
					{
						jestSprzezony = true;
					}
				}
			}
			else if (maciezNastepnikow[wiersz1][0] != maciezNastepnikow[wiersz2][0])
			{
			F:for (int kolumna = 1; kolumna<liczbaWierzcholkow; kolumna++)
			{
				if (maciezNastepnikow[wiersz1][kolumna] != maciezNastepnikow[wiersz2][kolumna] || (maciezNastepnikow[wiersz1][kolumna] == 0 && maciezNastepnikow[wiersz2][kolumna] == 0));
				else
				{
					jestSprzezony = false;
					goto S;
				}
				if (kolumna == liczbaWierzcholkow - 1)
				{
					jestSprzezony = true;
				}
			}
			}
		}
	}

S:;

	/**LINIWOSC*/
	stozPopszedniki();
	bool jestLiniowy = false;


	for (int wiersz1 = 0; wiersz1 < liczbaWierzcholkow; wiersz1++)
	{
		for (int wiersz2 = wiersz1 + 1; wiersz2 < liczbaWierzcholkow; wiersz2++)
		{
			for (int kolumna = 0; kolumna < liczbaWierzcholkow; kolumna++)
			{
				if (maciezNastepnikow[wiersz1][kolumna] == 1 && maciezNastepnikow[wiersz2][kolumna] == 1)
				{
					if (sprawdzLinowosc(wiersz1, wiersz2, kolumna + 1) == true)
					{
						jestLiniowy = true;
						break;
					}
					else
					{
						jestLiniowy = false;
						goto X;
					}

				}
			}
		}
	}
X:;
	if (jestLiniowy == true)
	{
		if (jestSprzezony == true)
		{
			cout << "Graf jest sprzezony oraz jest liniowy" << endl;
		}
		else
		{
			cout << "Graf jest liniowy ale nie jest sprzezony" << endl;
			return 0;
		}
	}
	else
	{
		if (jestSprzezony == true)
		{
			cout << "Graf jest sprzezony ale nie jest liniowy" << endl;
		}
		else
		{
			cout << "Graf nie jest sprzezony i nie jest liniowy" << endl;
			return 0;
		}
	}
	transformacja();
	return 0;
}