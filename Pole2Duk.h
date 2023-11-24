#pragma once
#include <exception>
#include <iostream>
using namespace std;

class Pole2Duk
{
private:
	int m, n;	// m ... pocet radku; n ... pocet sloupcu
	int** p;

public:
	Pole2Duk(int m, int n);
	virtual ~Pole2Duk();
	int PocetRadku() const;
	int PocetSloupcu() const;
	void SetValue(int value, int m_pos, int n_pos);
	int GetValue(int m_pos, int n_pos) const;
	int** operator[](int index);
	int IndexOf(int value, int* m_pos, int* n_pos) const;

	void init(int m, int n);
	Pole2Duk* operator+(const Pole2Duk m1);
	Pole2Duk* operator*(const Pole2Duk m1);
	void realoc(int m_new, int n_new);
	static void tisk(const Pole2Duk& m);
};

Pole2Duk::Pole2Duk(int m, int n)
{
	// init vektoru
	init(m, n);
	/*
	this->m = m;
	this->n = n;
	p = new int*[this->m * this->n];
	for (int i = 0; i < this->m * this->n; i++)
		p[i] = new int();
	*/
}

/* virtual */ Pole2Duk::~Pole2Duk()
{
	// dealokace
	for (int i = 0; i < this->m * this->n; i++)
	{
		delete p[i];
		p[i] = NULL;
	}
	delete[]* p;   // !!!
	p = NULL;
}

void Pole2Duk::init(int m, int n)
{
	if (p != NULL)
	{
		// odstranit starou alookaci
		for (int i = 0; i < this->m * this->n; i++)
		{
			delete p[i];
			p[i] = NULL;
		}
		delete[]* p;   // !!!
		p = NULL;
	}
	// vytvorit novou alokaci
	this->m = m;
	this->n = n;
	p = new int*[this->m * this->n];
	for (int i = 0; i < this->m * this->n; i++)
		p[i] = new int();
}

int Pole2Duk::PocetRadku() const
{
	return m;
}

int Pole2Duk::PocetSloupcu() const
{
	return n;
}

void Pole2Duk::SetValue(int value, int m_pos, int n_pos)
{
	// {m_pos, n_pos} -> {index}
	if ((m_pos >= 0 && n_pos >= 0) && (m_pos < m && n_pos < n))		// !!! kontrola pristupu k prvku na pozici
		*p[m_pos * n + n_pos] = value;
}

int Pole2Duk::GetValue(int m_pos, int n_pos) const
{
	// {m_pos, n_pos} -> {index}
	if ((m_pos >= 0 && n_pos >= 0) && (m_pos < m && n_pos < n))		// !!! kontrola pristupu k prvku na pozici
		return *p[m_pos * n + n_pos];
}

int** Pole2Duk::operator[](int index)
{
	if (index >= 0 && index < m)		// !!! kontrola existujiciho radku
		return p + index * this->n;
	else
		return NULL;
}

int Pole2Duk::IndexOf(int value, int* m_pos, int* n_pos) const
{
	// vyuziti transformace {r, s} -> {index}, {index} -> {r, s}

	// verze 1
	for (int i = 0; i < m * n; i++)
		if (*p[i] == value)
		{
			*m_pos = i / n; // this->n;
			*n_pos = i % n; // this->n;
			return 1;
		}
	*m_pos = -1;
	*n_pos = -1;
	return 0;

	// ---
	/*
	// verze 2
	for (int i = 0; i < this->m; i++)
		for (int j = 0; j < this->n; j++)
			if (GetValue(i, j) == value)
			{
				*m_pos = i;
				*n_pos = j;
				return 1;
			}
	*m_pos = -1;
	*n_pos = -1;
	return 0;
	*/
}

// --- todo DU
Pole2Duk* Pole2Duk::operator+(const Pole2Duk m1)
{
	if (this->m != m1.m || this->n != m1.n)
	{
		std::cout << ("Matice nemaji stejny rozmer");
		return NULL;
	}

	Pole2Duk* result = new Pole2Duk(this->m, this->n);

	for (int i = 0; i < this->m; i++)
	{
		for (int j = 0; j < this->n; j++)
		{
			result->SetValue(this->GetValue(i, j) + m1.GetValue(i, j), i, j);
		}
	}

	return result;
}

Pole2Duk* Pole2Duk::operator*(const Pole2Duk m1)
{
	if (this->n != m1.m)
	{
		std::cout << ("Nelze nasobit matice");
		return NULL;
	}

	Pole2Duk* result = new Pole2Duk(this->m, m1.n);

	for (int i = 0; i < this->m; i++)
	{ // projdi radky prvni matice
		for (int j = 0; j < m1.n; j++)
		{ // projdi sloupce druhe matice
			int sum = 0;
			for (int k = 0; k < this->n; k++)
			{ // projdi sloupce prvni matice
				sum += this->GetValue(i, k) * m1.GetValue(k, j);
			}
			result->SetValue(sum, i, j);
		}
	}

	return result;
}

void Pole2Duk::realoc(int m_new, int n_new)
{
	// realokace
	int** new_p = new int* [m_new * n_new];
	for (int i = 0; i < m_new * n_new; i++)
	{
		new_p[i] = new int();
	}
	
	// nove pole
	int min_m = std::min(m, m_new);
	int min_n = std::min(n, n_new);
	for (int i = 0; i < min_m; i++)
	{
		for (int j = 0; j < min_n; j++)
		{
			*new_p[(i*n_new) + j] = *p[(i*n) + j];
		}
	}

	// smaz stareho pole
	for (int i = 0; i < m * n; i++)
	{
		delete p[i];
		p[i] = NULL;
	}
	delete[] *p;
	p = NULL;

	// zmen hodnoty
	m = m_new;
	n = n_new;

	p = new_p;
}

// --

/* static */ void Pole2Duk::tisk(const Pole2Duk& m)
{
	for (int i = 0; i < m.m; i++)
	{
		for (int j = 0; j < m.n; j++)
			cout << m.GetValue(i, j) << ';';
		cout << '\n';
	}
}