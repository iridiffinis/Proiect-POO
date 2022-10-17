#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <list>

using namespace std;

//Atelier de origami

void afisareMeniu()
{
	cout << " ________________________________________________________________________\n";
	cout << "|\t\t\t\tMENIU\t\t\t\t\t |\n";
	cout << "|________________________________________________________________________|\n";
	cout << "1. Afisare informatii despre un elev la alegere\n";
	cout << "2. Afisare numar total formatori\n";
	cout << "3. Citire date din fisier CSV si transferarea lor intr-un fisier text\n";
	cout << "4. Afisare informatii despre o locatie la alegere\n";
	cout << "5. Generare raportul elevilor\n";
	cout << "6. Generare raportul formatorilor\n";
	cout << "7. Generare raportul echipamentelor\n";
	cout << "8. Generare raportul locatiilor\n";
	cout << "9. Generare raportul expozitiilor\n";
}

//clasa abstracta
class Abstract
{
public:
	virtual float marireSalariu() = 0;
	virtual int nrTotalOreLucrate() = 0;
};

class Activ
{
protected:
	float valoare = 0.0; //valoare achizitie/inchiriere
	int durataAm = 0;
	int vechime = 0; //in ani
public:
	Activ()
	{	}

	//functii accesor
	void setValoare(float valoare)
	{
		if (valoare > 0.0)
			this->valoare = valoare;
	}

	float getValoare()
	{
		return this->valoare;
	}

	void setDurataAm(int durataAm)
	{
		if (durataAm >= 0)
			this->durataAm = durataAm;
	}

	int getDurataAm()
	{
		return this->durataAm;
	}

	void setVechime(int vechime)
	{
		if (vechime >= 0)
			this->vechime = vechime;
	}

	int getVechime()
	{
		return this->vechime;
	}

	//metode virtuale
	virtual float calculAmPlata()
	{
		if (this->durataAm > 0)
			return this->valoare / this->durataAm;
		else return 0;
	}

	virtual void calculAmTerminat()
	{
		if (this->vechime - this->durataAm >= 0)
			cout << "S-a terminat de amortizat";
		if (this->durataAm - this->vechime > 0)
			cout << "Durata ramasa de amortizat: " << this->durataAm - this->vechime;
	}

	//constructor cu toti parametrii
	Activ(float valoare, int durataAm, int vechime): valoare(valoare), durataAm(durataAm), vechime(vechime)
	{	}

	//constructor copiere
	Activ(const Activ& a) : valoare(a.valoare), durataAm(a.durataAm), vechime(a.vechime)
	{	}

	//supraincarcare operator =
	Activ& operator=(const Activ& a)
	{
		this->valoare = a.valoare;
		this->durataAm = a.durataAm;
		this->vechime = a.vechime;
		return *this;
	}

	//destructor
	~Activ()
	{	}

	friend ostream& operator<<(ostream& out, const Activ& a)
	{
		out << "\nValoare: " << a.valoare;
		out << "\nDurata amortizare: " << a.durataAm;
		out << "\nVechime: " << a.vechime;
		return out;
	}

	friend istream& operator>>(istream& in, Activ& a)
	{
		cout << "\nValoare: ";
		in >> a.valoare;
		cout << "Durata amortizare: ";
		in >> a.durataAm;
		cout << "Vechime: ";
		in >> a.vechime;
		return in;
	}

	friend ofstream& operator<<(ofstream& out, const Activ& a)
	{
		out << a.valoare << endl;
		out << a.durataAm << endl;
		out << a.vechime << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Activ& a)
	{
		in >> a.valoare;
		in >> a.durataAm;
		in >> a.vechime;
		return in;
	}

};

class Elev
{
private:
	const int id = 0;
	string nume = "NA";
	int nrSaptamani = 0;
	int* nrLectii = NULL; //nr de lectii din fiecare saptamana (dimensiunea nrSaptamani)
	int nrLucrariExpozitie[12];
	int moduleTerminate = 0;
	static int nrElevi;

public:
	Elev()
	{
		//cout << "\nAPEL CONSTR FARA PARAM - ELEVI\n";
		nrElevi++;
	}

	//functii accesor
	const int getId()
	{
		return this->id;
	}

	void setNume(string nume)
	{
		if (nume.length() >= 2)
			this->nume = nume;
	}

	string getNume()
	{
		return this->nume;
	}

	void setNrSaptamani(int nrSaptamani)
	{
		if (nrSaptamani > 0)
			this->nrSaptamani = nrSaptamani;
	}

	int getNrSaptamani()
	{
		return this->nrSaptamani;
	}

	void setNrLectii(int nrSaptamani, int* nrLectii)
	{
		delete[] this->nrLectii;
		if (nrSaptamani >0 && nrLectii != NULL)
		{
			this->nrSaptamani = nrSaptamani;
			this->nrLectii = new int[nrSaptamani];
			for (int i = 0; i < nrSaptamani; i++)
				this->nrLectii[i] = nrLectii[i];
		}
		else
		{
			this->nrSaptamani = 0;
			this->nrLectii = NULL;
		}
	}

	int getNrLectii(int i)
	{
		if (i >= 0 && i < this->nrSaptamani)
			return this->nrLectii[i];
	}

	void setNrLucrariExpozitie(int nrLucrariExpozitie[12])
	{
		if (nrLucrariExpozitie != NULL)
			for (int i = 0; i < 12; i++)
				this->nrLucrariExpozitie[i] = nrLucrariExpozitie[i];
		else
			for (int i = 0; i < 12; i++)
				this->nrLucrariExpozitie[i] = 0;
	}

	int getNrLucrariExpozitie(int i)
	{
		return this->nrLucrariExpozitie[i];
	}

	void setModuleTerminate(int moduleTeminate)
	{
		if (moduleTeminate > 0)
			this->moduleTerminate = moduleTeminate;
	}

	int getModuleTerminate()
	{
		return this->moduleTerminate;
	}

	static void setNrElevi(int nrElevi)
	{
		Elev::nrElevi = nrElevi;
	}

	static int getNrElevi()
	{
		return Elev::nrElevi;
	}

	//metode de prelucrare/afisare
	int nrTotalLucrariExpuse()
	{
		int s = 0;
		for (int i = 0; i < 12; i++)
			s += this->nrLucrariExpozitie[i];
		return s;
	}

	void lectieBonus()
	{
		int totalLectii = 0;
		for (int i = 0; i < this->nrSaptamani; i++)
			totalLectii += this->nrLectii[i];
		if (totalLectii > 15)
			cout << this->nume << " primeste o lectie bonus.";
		else
			cout << this->nume << " nu primeste o lectie bonus.";
	}

	//constructor cu toti parametrii
	Elev(int id, string nume, int nrSaptamani, int* nrLectii, int nrLucrariExpozitie[12], int moduleTerminate)
		:id(id), nume(nume), moduleTerminate(moduleTerminate)
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - ELEV\n";
		if (nrSaptamani > 0 && nrLectii != NULL)
		{
			this->nrSaptamani = nrSaptamani;
			this->nrLectii = new int[nrSaptamani];
			for (int i = 0; i < nrSaptamani; i++)
				this->nrLectii[i] = nrLectii[i];
		}
		else
		{
			this->nrSaptamani = 0;
			this->nrLectii = NULL;
		}
		
			for (int i = 0; i < 12; i++)
				this->nrLucrariExpozitie[i] = nrLucrariExpozitie[i];
		nrElevi++;
	}

	//constructor cu mai putini parametrii
	Elev(int id, string nume, int nrSaptamani, int* nrLectii)
		:id(id), nume(nume)
	{
		//cout << "\nAPEL CONSTR CU MAI PUTINI PARAM - ELEV\n";
		if (nrSaptamani > 0 && nrLectii != NULL)
		{
			this->nrSaptamani = nrSaptamani;
			this->nrLectii = new int[nrSaptamani];
			for (int i = 0; i < nrSaptamani; i++)
				this->nrLectii[i] = nrLectii[i];
		}
		else
		{
			this->nrSaptamani = 0;
			this->nrLectii = NULL;
		}
		nrElevi++;
	}

	//constructor copiere
	Elev(const Elev& e) :id(e.id), nume(e.nume), nrSaptamani(e.nrSaptamani), moduleTerminate(e.moduleTerminate)
	{
		//cout << "\nAPEL CONSTR COPIERE - ELEV\n";
		if (e.nrSaptamani > 0 && e.nrLectii != NULL)
		{
			this->nrSaptamani = e.nrSaptamani;
			this->nrLectii = new int[e.nrSaptamani];
			for (int i = 0; i < e.nrSaptamani; i++)
				this->nrLectii[i] = e.nrLectii[i];
		}
		else
		{
			this->nrSaptamani = 0;
			this->nrLectii = NULL;
		}
	
			for (int i = 0; i < 12; i++)
				this->nrLucrariExpozitie[i] = e.nrLucrariExpozitie[i];
		nrElevi++;
	}

	//destructor
	~Elev()
	{
		//cout << "\nAPEL DESTRUCTOR - ELEVI\n";
		delete[] this->nrLectii;
	}

	//supraincarcare operator=
	Elev& operator=(Elev& e)
	{
		//cout << "\nAPEL OP=\n";
		this->nume = e.nume;
		this->moduleTerminate = e.moduleTerminate;
		this->nrSaptamani = e.nrSaptamani;
		delete[] this->nrLectii;
		if (e.nrSaptamani > 0 && e.nrLectii != NULL)
		{
			this->nrSaptamani = e.nrSaptamani;
			this->nrLectii = new int[e.nrSaptamani];
			for (int i = 0; i < e.nrSaptamani; i++)
				this->nrLectii[i] = e.nrLectii[i];
		}
		else
		{
			this->nrSaptamani = 0;
			this->nrLectii = NULL;
		}
		
			for (int i = 0; i < 12; i++)
				this->nrLucrariExpozitie[i] = e.nrLucrariExpozitie[i];
		nrElevi++;
		return *this;
	}

	//supraincarcare operator[]
	int& operator[](int index)
	{
		if (index >= 0 && index < this->nrSaptamani)
			return this->nrLectii[index];
		else
			throw exception("\nSaptamna inexistenta!");
	}

	//supraincarcare operator+
	Elev operator+(int val)
	{
		Elev aux = *this;
		aux.moduleTerminate += val;
		return aux;
	}

	//supraincarcare operator++ preincrementare
	Elev operator++()
	{
		this->moduleTerminate++;
		return *this;
	}

	//supraincarcare operator++ postincrementare
	Elev operator++(int)
	{
		Elev aux = *this;
		delete[] this->nrLectii;
		this->nrSaptamani++;
		this->nrLectii = new int[this->nrSaptamani];
		for (int i = 0; i < aux.nrSaptamani; i++)
			this->nrLectii[i] = aux.nrLectii[i];
		this->nrLectii[this->nrSaptamani - 1] = 0; //se adauga o saptamana in plus
		return aux;
	}

	//supraincarcare operator cast
	explicit operator int()
	{
		int nrTotalLectii = 0;
		if (this->nrSaptamani > 0 && this->nrLectii != NULL)
		{
			for (int i = 0; i < this->nrSaptamani; i++)
				nrTotalLectii += this->nrLectii[i];
		}
		return nrTotalLectii;
	}

	//supraincarcare operator!
	Elev operator!()
	{
		Elev aux = *this;
		aux.nrSaptamani = 0;
		delete[] aux.nrLectii;
		aux.nrLectii = NULL;
		return aux;
	}

	//supraincaracre operator <
	bool operator<(const Elev& e)
	{
		if (this->moduleTerminate < e.moduleTerminate)
			return true;
		return false;
	}

	//supraincarcare operator ==
	bool operator==(const Elev& e)
	{
		if (this->nrSaptamani == e.nrSaptamani)
			return true;
		return false;
	}

	//scriere fisier binar
	void writeToFile(fstream& f)
	{
		f.write((char*)&this->id, sizeof(int));
		int lg = this->nume.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume.data(), lg);
		f.write((char*)&this->nrSaptamani, sizeof(int));
		for (int i = 0; i < this->nrSaptamani; i++)
			f.write((char*)&this->nrLectii[i], sizeof(int));
		f.write((char*)&this->moduleTerminate, sizeof(int));
		int x = 12;
		f.write((char*)&x, sizeof(int));
		for (int i = 0; i < 12; i++)
			f.write((char*)&this->nrLucrariExpozitie[i], sizeof(int));
	}

	friend ostream& operator<<(ostream& out, const Elev& e);
	friend istream& operator>>(istream& in, Elev& e);

	friend ofstream& operator<<(ofstream& out, const Elev& e)
	{
		out << e.id;
		out << "\n" << e.nume;
		if (e.nrSaptamani > 0 && e.nrLectii != NULL)
		{
			out << "\n" << e.nrSaptamani << " : ";
			for (int i = 0; i < e.nrSaptamani; i++)
				out << e.nrLectii[i] << " ";
		}
		out << "\n" << e.moduleTerminate;
		out << "\n";
		for (int i = 0; i < 12; i++)
			out << e.nrLucrariExpozitie[i] << " ";
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Elev& e)
	{
		char nume[100];
		in.getline(nume, 100);
		e.nume = nume;
		in >> e.nrSaptamani;
		delete[] e.nrLectii;
		if (e.nrSaptamani > 0)
		{
			e.nrLectii = new int[e.nrSaptamani];
			for (int i = 0; i < e.nrSaptamani; i++)
				in >> e.nrLectii[i];
		}
		else
		{
			e.nrSaptamani = 0;
			e.nrLectii = NULL;
		}
		in >> e.moduleTerminate;

		for (int i = 0; i < 12; i++)
			in >> e.nrLucrariExpozitie[i];
		return in;
	}
};

ostream& operator<<(ostream& out, const Elev& e)
{
	out << "\n-----------------------------------";
	out << "\nId: " << e.id;
	out << "\nNume elev: " << e.nume;
	if (e.nrSaptamani > 0 && e.nrLectii != NULL)
	{
		out << "\nNr saptamani: " << e.nrSaptamani;
		out << "\nNr lectii in fiecare saptamana: ";
		for (int i = 0; i < e.nrSaptamani; i++)
			out << e.nrLectii[i] << " ";
	}
	else
		out << "\nNu s-a ales nr de saptamani";
	out << "\nModule terminate: " << e.moduleTerminate;
	out << "\nNr lucrari expuse la expoxitii:";
	for (int i = 0; i < 12; i++)
		out << e.nrLucrariExpozitie[i] << " ";
	out << "\n-----------------------------------";
	return out;
}

istream& operator>>(istream& in, Elev& e)
{
	cout << "\nNume elev:";
	char nume[100];
	in.getline(nume, 100);
	e.nume = nume;
	cout << "Nr saptamani: ";
	in >> e.nrSaptamani;
	delete[] e.nrLectii;
	if (e.nrSaptamani > 0)
	{
		cout << "Nr de lectii in fiecare saptamana: ";
		e.nrLectii = new int[e.nrSaptamani];
		for (int i = 0; i < e.nrSaptamani; i++)
			in >> e.nrLectii[i];
	}
	else
	{
		e.nrSaptamani = 0;
		e.nrLectii = NULL;
	}
	cout << "Module terminate: ";
	in >> e.moduleTerminate;
	cout << "Nr lucrari expuse la expozitii: ";
	
		for (int i = 0; i < 12; i++)
			in >> e.nrLucrariExpozitie[i];
	return in;
}

//clasa compusa cu Elev si derivata din Abstract
class Formator : public Abstract
{
private:
	const int id = 0;
	string nume = "NA";
	Elev** listaElevi = NULL; //lista elevilor pe care ii are atribuiti (dim nrElevi)
	int nrElevi = 0; //cati elevi are atribuiti
	float salariu = 0.0;
	int oreLucrate[44]; 
	static int nrFormatori;

public:
	Formator()
	{
		//cout << "\nAPEL CONSTR FARA PARAM - FORMATOR\n";
		nrFormatori++;
	}

	//functii accesor
	const int getId()
	{
		return this->id;
	}

	void setNume(string nume)
	{
		if (nume.length() > 2)
			this->nume = nume;
	}

	string getNume()
	{
		return this->nume;
	}

	void setListaElevi(int nrElevi, Elev** listaElevi)
	{
		for (int i = 0; i < this->nrElevi; i++)
			delete this->listaElevi;
		delete[] this->listaElevi;

		if (listaElevi != NULL && nrElevi > 0)
		{
			this->nrElevi = nrElevi;
			this->listaElevi = new Elev * [this->nrElevi];
			for (int i = 0; i < nrElevi; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrElevi = 0;
			this->listaElevi = NULL;
		}
	}

	Elev getListaElevi(int i)
	{
		if (i >= 0 && i < this->nrElevi)
			return *this->listaElevi[i];
	}

	void setNrElevi(int nrElevi)
	{
		if (nrElevi > 0)
			this->nrElevi = nrElevi;
	}

	int getNrElevi()
	{
		return this->nrElevi;
	}

	void setSalariu(float salariu)
	{
		if (salariu > 0.0)
			this->salariu = salariu;
	}

	float getSalariu()
	{
		return this->salariu;
	}

	void setOreLucrate(int oreLucrate[44])
	{
		if (oreLucrate != NULL)
			for (int i = 0; i < 44; i++)
				this->oreLucrate[i] = oreLucrate[i];
		else
			for (int i = 0; i < 44; i++)
				this->oreLucrate[i] = 0;
	}

	int getOreLucrate(int i)
	{
		return this->oreLucrate[i];
	}

	static void setNrFormatori(int nrFormatori)
	{
		Formator::nrFormatori = nrFormatori;
	}

	static int getNrFormatori()
	{
		return Formator::nrFormatori;
	}

	//metode de prelucrare/afisare
	int nrTotalOreLucrate()
	{
		int s = 0;
		for (int i = 0; i < 44; i++)
			s += this->oreLucrate[i];
		return s;
	}

	float marireSalariu()
	{
		if (this->nrElevi > 30)
		{
			this->salariu = this->salariu * 1.25;
			return this->salariu;
		}
		else
		{
			this->salariu = this->salariu * 1.1;
			return this->salariu;
		}
	}

	//constructor cu toti parametrii
	Formator(int id, string nume, Elev** listaElevi, int nrElevi, float salariu, int oreLucrate[44])
		:id(id), nume(nume), salariu(salariu)
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - FORMATOR\n";
		if (listaElevi != NULL && nrElevi > 0)
		{
			this->nrElevi = nrElevi;
			this->listaElevi = new Elev * [this->nrElevi];
			for (int i = 0; i < nrElevi; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrElevi = 0;
			this->listaElevi = NULL;
		}

			for (int i = 0; i < 44; i++)
				this->oreLucrate[i] = oreLucrate[i];
		nrFormatori++;
	}

	//constructor cu mai putini parametrii
	Formator(int id, string nume, Elev** listaElevi, int nrElevi)
		:id(id), nume(nume)
	{
		//cout << "\nAPEL CONSTR CU MAI PUTINI PARAM - FORMATOR\n";
		if (listaElevi != NULL && nrElevi > 0)
		{
			this->nrElevi = nrElevi;
			this->listaElevi = new Elev * [this->nrElevi];
			for (int i = 0; i < nrElevi; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrElevi = 0;
			this->listaElevi = NULL;
		}
		nrFormatori++;
	}

	//constructor de copiere
	Formator(const Formator& f) : id(f.id),nume(f.nume), salariu(f.salariu)
	{
		//cout << "\nAPEL CONSTR COPIERE - FORMATOR\n";
		if (f.listaElevi != NULL && f.nrElevi > 0)
		{
			this->nrElevi = f.nrElevi;
			this->listaElevi = new Elev * [this->nrElevi];
			for (int i = 0; i < f.nrElevi; i++)
				this->listaElevi[i] = new Elev(*f.listaElevi[i]);
		}
		

			for (int i = 0; i < 44; i++)
				this->oreLucrate[i] = f.oreLucrate[i];
		nrFormatori++;
	}

	//destructor
	~Formator()
	{
		//cout << "\nAPEL DESTRUCTOR - FORMATOR\n";
		for (int i = 0; i < this->nrElevi; i++)
			delete this->listaElevi[i];
		delete[] this->listaElevi;
	}

	//supraincarcare operator=
	Formator& operator=(const Formator& f)
	{
		//cout << "\nAPEL OP= - FORMATOR\n";
		for (int i = 0; i < this->nrElevi; i++)
			delete this->listaElevi[i];
		delete[] this->listaElevi;

		this->nume = f.nume;
		this->salariu = f.salariu;
		if (f.listaElevi != NULL && f.nrElevi > 0)
		{
			this->nrElevi = f.nrElevi;
			this->listaElevi = new Elev * [this->nrElevi];
			for (int i = 0; i < f.nrElevi; i++)
				this->listaElevi[i] = new Elev(*f.listaElevi[i]);
		}
		else
		{
			this->nrElevi = 0;
			this->listaElevi = NULL;
		}

			for (int i = 0; i < 44; i++)
				this->oreLucrate[i] = f.oreLucrate[i];
		nrFormatori++;
		return *this;
	}

	//supraincarcare operator[]
	Elev operator[](int index)
	{
		if (index >= 0 && index < this->nrElevi)
			return *this->listaElevi[index];
		else
			throw exception("\nIndex invalid!");
	}

	//supraincarcare operator+
	Formator operator+(float val)
	{
		Formator aux = *this;
		aux.salariu += val;
		return aux;
	}

	//supraincarcare operator*
	Formator operator*(float val)
	{
		Formator aux = *this;
		aux.salariu = aux.salariu * (1 + val / 100);
		return aux;
	}

	//supraincarcare operator++ preincrementare
	Formator operator++()
	{
		this->salariu++;
		return *this;
	}

	//supraincarcare operator++ postincrementare
	Formator operator++(int)
	{
		Formator aux = *this;
		this->oreLucrate[43]++;
		return aux;
	}

	//supraincarcare operator cast
	explicit operator string()
	{
		return this->nume;
	}

	//supraincarcare operaor!
	Formator operator!()
	{
		Formator aux = *this;
		aux.nrElevi = 0;
		for (int i = 0; i < aux.nrElevi; i++)
			delete aux.listaElevi[i];
		delete[] aux.listaElevi;
		aux.listaElevi = NULL;
		return aux;
	}

	//supraincarcare operator >
	bool operator>(const Formator& f)
	{
		if (this->nrElevi > f.nrElevi)
			return true;
		return false;
	}

	//supraincarcare oparator ==
	bool operator==(const Formator& f)
	{
		if (this->salariu == f.salariu)
			return true;
		return false;
	}

	void writeToFile(fstream& f)
	{
		f.write((char*)&this->id, sizeof(int));
		int lg = this->nume.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->nume.data(), lg);
		f.write((char*)&this->nrElevi, sizeof(int));
		
		f.write((char*)&this->salariu, sizeof(float));
		int x = 44;
		f.write((char*)&x, sizeof(int));
		for (int i = 0; i < 44; i++)
			f.write((char*)&this->oreLucrate[i], sizeof(int));
	}

	friend ostream& operator<<(ostream& out, const Formator& f);
	friend istream& operator>>(istream& in, Formator& f);

	friend ofstream& operator<<(ofstream& out, const Formator& f)
	{
		out << f.id;
		out << "\n" << f.nume;
		if (f.nrElevi > 0 && f.listaElevi != NULL)
		{
			out << "\n" << f.nrElevi <<"\n";
			for (int i = 0; i < f.nrElevi; i++)
				out << *f.listaElevi[i] << " ";
		}
		out << "\n" << f.salariu;
		for (int i = 0; i < 44; i++)
			out << f.oreLucrate[i] << " ";
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Formator& f)
	{
		for (int i = 0; i < f.nrElevi; i++)
			delete f.listaElevi[i];
		delete[] f.listaElevi;

		char nume[100];
		in.getline(nume, 100);
		f.nume = nume;
		in >> f.nrElevi;
		if (f.nrElevi > 0)
		{
			f.listaElevi = new Elev * [f.nrElevi];
			for (int i = 0; i < f.nrElevi; i++)
			{
				Elev e;
				in >> e;
				f.listaElevi[i] = new Elev(e);
			}
		}
		else
		{
			f.nrElevi = 0;
			f.listaElevi = NULL;
		}
		in >> f.salariu;
		for (int i = 0; i < 44; i++)
			in >> f.oreLucrate[i];
		return in;
	}
};

ostream& operator<<(ostream& out, const Formator& f)
{
	out << "\n-----------------------------------";
	out << "\nId: " << f.id;
	out << "\nNume formator: " << f.nume;
	if (f.nrElevi > 0 && f.listaElevi != NULL)
	{
		out << "\nNr elevi: " << f.nrElevi;
		out << "\nLista elevilor: ";
		for (int i = 0; i < f.nrElevi; i++)
			out << *f.listaElevi[i] << " ";
	}
	else
		out << "\nNu are inca elevi";
	out << "\nSalariu: " << f.salariu;
	out << "\nNr ore lucrate in fiecare saptamana:";
	for (int i = 0; i < 44; i++)
		out << f.oreLucrate[i] << " ";
	out << "\n-----------------------------------";
	return out;
}

istream& operator>>(istream& in, Formator& f)
{
	for (int i = 0; i < f.nrElevi; i++)
		delete f.listaElevi[i];
	delete[] f.listaElevi;
		
	cout << "\nNumele formator:";
	char nume[100];
	in.getline(nume, 100);
	f.nume = nume;
	cout << "Nr elevi: ";
	in >> f.nrElevi;
	if (f.nrElevi > 0)
	{
		cout << "Lista elevilor: ";
		f.listaElevi = new Elev * [f.nrElevi];
		for (int i = 0; i < f.nrElevi; i++)
		{
			Elev e;
			in >> e;
			f.listaElevi[i] = new Elev(e);
		}
	}
	else
	{
		f.nrElevi = 0;
		f.listaElevi = NULL;
	}
	cout << "Salariu: ";
	in >> f.salariu;
	cout << "Nr ore lucrate in cele 44 de saptamani: ";

		for (int i = 0; i < 44; i++)
			in >> f.oreLucrate[i];
	return in;
}

//clasa Echipament este derivata din clasa Activ
class Echipament : public Activ
{
private:
	string denumire = "NA";
	int nrBucati = 0;
	int nrBucDefecte = 0;
	int* nrPeFormator = NULL; //cate bucati din obiect are repartizat fiecare formator
	bool restoc[12]; //daca s-a refacut sau nu stocul in respectiva luna
	int nrFormatori = Formator::getNrFormatori();

public:
	
	Echipament()
	{
	}

	//functii accesor
	void setDenumire(string denumire)
	{
		if (denumire.length() >= 2)
			this->denumire = denumire;
	}

	string getDenumire()
	{
		return this->denumire;
	}

	void setNrBucati(int nrBucati)
	{
		if (nrBucati > 0)
			this->nrBucati = nrBucati;
	}

	int getNrBucati()
	{
		return this->nrBucati;
	}

	void setNrBucDefecte(int nrDefecte)
	{
		if (nrDefecte > 0)
			this->nrBucDefecte = nrDefecte;
	}

	int getNrBucDefecte()
	{
		return this->nrBucDefecte;
	}

	void setNrPeFormator(int* nrPeFormator)
	{
		delete[] this->nrPeFormator;
		if (this->nrFormatori > 0 && nrPeFormator != NULL)
		{
			this->nrPeFormator = new int[this->nrFormatori];
			for (int i = 0; i < this->nrFormatori; i++)
				this->nrPeFormator[i] = nrPeFormator[i];
		}
		else
		{
			this->nrPeFormator = NULL;
		}
	}

	int getNrPeFormator(int i)
	{
		if (i >= 0 && i < this->nrFormatori)
			return this->nrPeFormator[i];
	}

	void setRestoc(bool restoc[12])
	{
		if (restoc != NULL)
			for (int i = 0; i < 12; i++)
				this->restoc[i] = restoc[i];
		else
			for (int i = 0; i < 12; i++)
				this->restoc[i] = 0;
	}

	int getRestoc(int i)
	{
		return this->restoc[i];
	}

	//metode de prelucrare/afisare
	int nrTotalRestoc()
	{
		int s = 0;
		for (int i = 0; i < 12; i++)
			if (this->restoc[i])
				++s;
		return s;
	}

	int nrTotalBucDistribuite()
	{
		int total = 0;
		for (int i = 0; i < this->nrFormatori; i++)
			total += nrPeFormator[i];
		return total;
	}

	//constructor cu toti parametrii
	Echipament(string denumire, int nrBucati,int nrBucDefecte, int* nrPeFormator, bool restoc[12], float valoare, int durataAm, int vechime)
		:Activ(valoare,durataAm,vechime)
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - ECHIPAMENT\n";
		this->denumire = denumire;
		this->nrBucati = nrBucati;
		this->nrBucDefecte = nrBucDefecte;
		if (this->nrFormatori > 0 && nrPeFormator != NULL)
		{
			this->nrPeFormator = new int[this->nrFormatori];
			for (int i = 0; i < this->nrFormatori; i++)
				this->nrPeFormator[i] = nrPeFormator[i];
		}
		else
		{
			this->nrPeFormator = NULL;
		}
	
			for (int i = 0; i < 12; i++)
				this->restoc[i] = restoc[i];
	}

	//constructor cu mai putini parametrii
	Echipament(string denumire, int nrBucati, int* nrPeFormator)
	{
		//cout << "\nAPEL CONSTR CU MAI PUTINI PARAM - ECHIPAMENT\n";
		this->denumire = denumire;
		this->nrBucati = nrBucati;
		if (this->nrFormatori > 0 && nrPeFormator != NULL)
		{
			this->nrPeFormator = new int[this->nrFormatori];
			for (int i = 0; i < this->nrFormatori; i++)
				this->nrPeFormator[i] = nrPeFormator[i];
		}
		else
		{
			this->nrPeFormator = NULL;
		}
	}

	//constructor de copiere
	Echipament(const Echipament& ek):Activ(ek)
	{
		//cout << "\nAPEL CONSTR COPIERE - ECHIPAMENT\n";
		this->denumire = ek.denumire;
		this->nrBucati = ek.nrBucati;
		this->nrBucDefecte = ek.nrBucDefecte;
		if (this->nrFormatori > 0 && ek.nrPeFormator != NULL)
		{
			this->nrPeFormator = new int[this->nrFormatori];
			for (int i = 0; i < this->nrFormatori; i++)
				this->nrPeFormator[i] = ek.nrPeFormator[i];
		}
		else
		{
			this->nrPeFormator = NULL;
		}
		
			for (int i = 0; i < 12; i++)
				this->restoc[i] = ek.restoc[i];
	}

	//destructor
	~Echipament()
	{
		//cout << "\nAPEL DESTRUCTOR - ECHIPAMENT\n";
		delete[] this->nrPeFormator;
	}

	//supraincarcare operator=
	Echipament& operator=(const Echipament& ek)
	{
		delete[] nrPeFormator;
		//cout << "\nAPEL OP= - ECHIPAMENT\n";
		this->denumire = ek.denumire;
		this->nrBucati = ek.nrBucati;
		this->nrBucDefecte = ek.nrBucDefecte;
		if (this->nrFormatori > 0 && ek.nrPeFormator != NULL)
		{
			this->nrPeFormator = new int[this->nrFormatori];
			for (int i = 0; i < this->nrFormatori; i++)
				this->nrPeFormator[i] = ek.nrPeFormator[i];
		}
		else
		{
			this->nrPeFormator = NULL;
		}
		
			for (int i = 0; i < 12; i++)
				this->restoc[i] = ek.restoc[i];
			Activ::operator=(ek);
		return *this;
	}

	//supraincarcare operator[]
	int& operator[](int index)
	{
		if (index >= 0 && index < this->nrFormatori)
			return this->nrPeFormator[index];
		else
			throw exception("Index invalid!");
	}

	//supraincarcare operator+
	Echipament operator+(int val)
	{
		Echipament aux = *this;
		aux.nrBucati += val;
		return aux;
	}

	//supraincaracre operator-
	Echipament operator-(int val)
	{
		Echipament aux = *this;
		aux.nrBucati -= val;
		return aux;
	}

	//supraincarcare operator++ preincrementare
	//se mareste nr de bucati alocate primului formator
	Echipament operator++()
	{
		this->nrPeFormator[0]++;
		return *this;
	}

	//supraincarcare operator++ posincrementare
	//se mareste nr de bucati alocate ultimului formator
	Echipament operator++(int)
	{
		Echipament aux = *this;
		this->nrPeFormator[this->nrFormatori - 1]++;
		return aux;
	}

	//supraincarcare operator cast
	explicit operator int()
	{
		return this->nrBucati - this->nrBucDefecte;
	}

	//supraincarcare operator!
	bool operator!()
	{
		if (this->nrPeFormator != NULL)
			return true;
		return false;
	}

	//supraincarcare operator>=
	bool operator>=(const Echipament& ek)
	{
		if (this->nrBucati >= ek.nrBucati)
			return true;
		return false;
	}

	//supraincarcare operator ==
	bool operator==(const Echipament& ek)
	{
		if (this->denumire == ek.denumire)
			return true;
		return false;
	}

	void writeToFile(fstream& f)
	{
		int lg = this->denumire.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->denumire.data(), lg);
		f.write((char*)&this->nrBucati, sizeof(int));
		f.write((char*)&this->nrFormatori, sizeof(int));
		for (int i = 0; i < this->nrFormatori; i++)
			f.write((char*)&this->nrPeFormator[i], sizeof(int));
	}

	friend ostream& operator<<(ostream& out, const Echipament& ek);
	friend istream& operator>>(istream& in, Echipament& ek);

	friend ofstream& operator<<(ofstream& out, const Echipament& ek)
	{
		out << ek.denumire;
		out << "\n" << ek.nrBucati;
		if (ek.nrFormatori > 0 && ek.nrPeFormator != NULL)
		{
			if (ek.nrBucati > 0)
			{
				out << "\n";
				for (int i = 0; i < ek.nrFormatori; i++)
					out << ek.nrPeFormator[i] << " ";
			}
		}
		out << "\n";
		for (int i = 0; i < 12; i++)
			if (ek.restoc[i])
				out << i + 1 << " ";
		out << (Activ)ek;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Echipament& ek)
	{
		char denumire[100];
		in.getline(denumire, 100);
		ek.denumire = denumire;
		in >> ek.nrBucati;
		delete[] ek.nrPeFormator;
		if (ek.nrFormatori > 0)
		{
			ek.nrPeFormator = new int[ek.nrFormatori];
			for (int i = 0; i < ek.nrFormatori; i++)
				in >> ek.nrPeFormator[i];
		}
		else
		{
			ek.nrPeFormator = NULL;
		}

		for (int i = 0; i < 12; i++)
			in >> ek.restoc[i];
		in >> (Activ&)ek;
		return in;
	}

	//reluare metode virtuale din clasa de baza
	float calculAmPlata()
	{
		if (this->durataAm > 0)
			return (this->valoare * 1.19) / this->durataAm;
	}

	void claculAmTerminat()
	{
		if (this->vechime - this->durataAm >= 0)
			cout << "S-a terminat de amortizat";
		if (this->durataAm - this->vechime > 0)
			cout << "Durata de amortizare ramasa: " << this->durataAm - this->vechime;
	}

};

ostream& operator<<(ostream& out, const Echipament& ek)
{
	out << "\n-----------------------------------";
	out << "\nDenumire: " << ek.denumire;
	out << "\nNr bucati: " << ek.nrBucati;
	if (ek.nrFormatori > 0 && ek.nrPeFormator != NULL)
	{
		if (ek.nrBucati > 0)
		{
			out << "\nNr buc alocate fiecarui formator: ";
			for (int i = 0; i < ek.nrFormatori; i++)
				out << ek.nrPeFormator[i] << " ";
		}
	}
	else
		out << "\nNu sunt formatori";
	out << "\nLunile in care s-a refacut stocul:";
	for (int i = 0; i < 12; i++)
		if (ek.restoc[i])
			out << i + 1 << " ";
	out << (Activ)ek;
	out << "\n-----------------------------------";
	return out;
}

istream& operator>>(istream& in, Echipament& ek)
{
	cout << "\nDenumire:";
	char denumire[100];
	in.getline(denumire, 100);
	ek.denumire = denumire;
	cout << "Nr bucati: ";
	in >> ek.nrBucati;
	delete[] ek.nrPeFormator;
	if (ek.nrFormatori > 0)
	{
		cout << "Nr buc alocate fiecarui formator: ";
		ek.nrPeFormator = new int[ek.nrFormatori];
		for (int i = 0; i < ek.nrFormatori; i++)
			in >> ek.nrPeFormator[i];
	}
	else
	{
		ek.nrPeFormator = NULL;
	}
	
	cout << "Lunile in care s-a refacut stocul: ";
		for (int i = 0; i < 12; i++)
			in >> ek.restoc[i];
		in >> (Activ&)ek;
	return in;
}

//clasa compusa cu Elev si derivata din clasa Activ
class Locatie : public Activ
{
private:
	string adresa = "NA";
	int nrSali = 0;
	int nrLocuri = 0;
	int nrPersonal = 0;
	bool gazduireExpozitie[12];
	Elev** listaElevi = NULL; //lista elevilor care sunt repartizati la locatia curenta (dim nrLocuri)

public:
	Locatie()
	{
	}

	//functii accesor
	void setAdresa(string adresa)
	{
		if (adresa.length() > 10)
			this->adresa = adresa;
	}

	string getAdresa()
	{
		return this->adresa;
	}

	void setNrSali(int nrSali)
	{
		if (nrSali > 0)
			this->nrSali = nrSali;
	}

	int getNrSali()
	{
		return this->nrSali;
	}

	void setNrLocuri(int nrLocuri)
	{
		if (nrLocuri > 0)
			this->nrLocuri = nrLocuri;
	}

	int getNrLocuri()
	{
		return this->nrLocuri;
	}

	void setNrPersonal(int nrPersonal)
	{
		if (nrPersonal > 0)
			this->nrPersonal = nrPersonal;
	}

	int getNrPersonal()
	{
		return this->nrPersonal;
	}

	void setGazduireExpozitie(bool val[12])
	{
		if (val != NULL)
			for (int i = 0; i < 12; i++)
				this->gazduireExpozitie[i] = val[i];
		else
			for (int i = 0; i < 12; i++)
				this->gazduireExpozitie[i] = 0;
	}

	int getGazduireExpozitie(int i)
	{
		return this->gazduireExpozitie[i];
	}

	void setListaElevi(int nrLocuri, Elev** listaElevi)
	{
		for (int i = 0; i < this->nrLocuri; i++)
			delete this->listaElevi;
		delete[] this->listaElevi;
		if (listaElevi != NULL && nrLocuri > 0)
		{
			this->nrLocuri = nrLocuri;
			this->listaElevi = new Elev * [this->nrLocuri];
			for (int i = 0; i < nrLocuri; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrLocuri = 0;
			this->listaElevi = NULL;
		}
	}

	Elev getListaElevi(int i)
	{
		if (i >= 0 && i < this->nrLocuri)
			return *this->listaElevi[i];
	}

	//metode de prelucrare/afisare
	int nrTotalGazduireExpozitie()
	{
		int s = 0;
		for (int i = 0; i < 12; i++)
			s += this->gazduireExpozitie[i];
		return s;
	}

	void poateGazduiExpozitie()
	{
		if (this->nrSali >= 3)
			cout << "\nLocatia de la adresa " << this->adresa << " poate gazdui expozitii";
	}

	//constructor cu toti parametrii
	Locatie(string adresa, int nrSali, int nrLocuri,int nrPersonal, Elev** listaElevi, bool gazduireExpozitie[12], float valoare, int durataAm, int vechime)
		:adresa(adresa), nrSali(nrSali), nrPersonal(nrPersonal), Activ(valoare, durataAm, vechime)
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - LOCATIE\n";
		if (listaElevi != NULL && nrLocuri > 0)
		{
			this->nrLocuri = nrLocuri;
			this->listaElevi = new Elev * [this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrLocuri = 0;
			this->listaElevi = NULL;
		}
	
			for (int i = 0; i < 12; i++)
				this->gazduireExpozitie[i] = gazduireExpozitie[i];
	}

	//constructor cu mai putini parametrii
	Locatie(string adresa, int nrLocuri, Elev** listaElevi)
		:adresa(adresa), nrLocuri(nrLocuri)
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - LOCATIE\n";
		if (listaElevi != NULL && nrLocuri > 0)
		{
			this->nrLocuri = nrLocuri;
			this->listaElevi = new Elev * [this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
				this->listaElevi[i] = new Elev(*listaElevi[i]);
		}
		else
		{
			this->nrLocuri = 0;
			this->listaElevi = NULL;
		}
	}

	//constructor de copiere
	Locatie(const Locatie& l) :adresa(l.adresa), nrSali(l.nrSali), nrPersonal(l.nrPersonal), Activ(l)
	{
		//cout << "\nAPEL CONSTR COPIERE - LOCATIE\n";
		if (l.listaElevi != NULL && l.nrLocuri > 0)
		{
			this->nrLocuri = l.nrLocuri;
			this->listaElevi = new Elev * [this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
				this->listaElevi[i] = new Elev(*l.listaElevi[i]);
		}
		else
		{
			this->nrLocuri = 0;
			this->listaElevi = NULL;
		}
	
			for (int i = 0; i < 12; i++)
				this->gazduireExpozitie[i] = l.gazduireExpozitie[i];
	}

	//destructor
	~Locatie()
	{
		//cout << "\nAPEL DESTRUCTOR - LOCATIE\n";
		for (int i = 0; i < this->nrLocuri; i++)
			delete this->listaElevi[i];
		delete[] this->listaElevi;
	}

	//supraincarcare operator=
	Locatie& operator=(const Locatie& l)
	{
		//cout << "\nAPEL OP= - LOCATIE\n";
		for (int i = 0; i < this->nrLocuri; i++)
			delete this->listaElevi[i];
		delete[] this->listaElevi;

		this->adresa = l.adresa;
		this->nrSali = l.nrSali;
		this->nrLocuri = l.nrLocuri;
		this->nrPersonal = l.nrPersonal;
		if (l.listaElevi != NULL && l.nrLocuri > 0)
		{
			this->nrLocuri = l.nrLocuri;
			this->listaElevi = new Elev * [this->nrLocuri];
			for (int i = 0; i < this->nrLocuri; i++)
				this->listaElevi[i] = new Elev(*l.listaElevi[i]);
		}
		else
		{
			this->nrLocuri = 0;
			this->listaElevi = NULL;
		}
	
			for (int i = 0; i < 12; i++)
				this->gazduireExpozitie[i] = l.gazduireExpozitie[i];
			Activ::operator=(l);
			return *this;
	}

	//supraincarcare operator[]
	Elev operator[](int index)
	{
		if (index >= 0 && index < this->nrLocuri)
			return *this->listaElevi[index];
		else
			throw exception("\nIndex invalid!");
	}

	//supraincarcare operator-
	Locatie operator-(int val)
	{
		Locatie aux = *this;
		aux.nrPersonal -= val;
		return aux;
	}

	//supraincarcare operator++ preincrementare
	Locatie operator++()
	{
		this->nrSali++;
		return *this;
	}

	//supraincarcare operator++ postincrementare
	Locatie operator++(int)
	{
		Locatie aux = *this;
		this->nrPersonal++;
		return aux;
	}

	//supraincarcare operator cast
	explicit operator string()
	{
		return this->adresa;
	}

	//supraincarcare operator!
	Locatie operator!()
	{
		Locatie aux = *this;
		aux.nrPersonal = 0;
		return aux;
	}

	//supraincarcare operator >
	bool operator>(const Locatie& l)
	{
		if (this->nrSali > l.nrSali)
			return true;
		return false;
	}

	//supraincarcare oprator ==
	bool operator==(const Locatie& l)
	{
		if (this->nrLocuri == l.nrLocuri)
			return true;
		return false;
	}

	void writeToFile(fstream& f)
	{
		int lg = this->adresa.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->adresa.data(), lg);
		f.write((char*)&this->nrSali, sizeof(int));
		f.write((char*)&this->nrLocuri, sizeof(int));
		f.write((char*)&this->nrPersonal, sizeof(int));
		int x = 12;
		f.write((char*)&x, sizeof(int));
		for (int i = 0; i < 12; i++)
			if (this->gazduireExpozitie[i])
				f.write((char*)(&i + 1), sizeof(bool));
		
	}

	friend ostream& operator<<(ostream& out, const Locatie& l);
	friend istream& operator>>(istream& in, Locatie& l);

	friend ofstream& operator<<(ofstream& out, const Locatie& l)
	{
		out << l.adresa;
		out << "\n" << l.nrSali;
		if (l.nrLocuri > 0 && l.listaElevi != NULL)
		{
			out << "\n" << l.nrLocuri;
			out << "\n";
			for (int i = 0; i < l.nrLocuri; i++)
				out << *l.listaElevi[i] << " ";
		}
		out << "\n" << l.nrPersonal;
		out << "\n";
		for (int i = 0; i < 12; i++)
			if (l.gazduireExpozitie[i])
				out << i + 1 << " ";
		out << (Activ)l;
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Locatie& l)
	{
		for (int i = 0; i < l.nrLocuri; i++)
			delete l.listaElevi[i];
		delete[] l.listaElevi;

		char adresa[100];
		in.getline(adresa, 100);
		l.adresa = adresa;
		in >> l.nrSali;
		in >> l.nrLocuri;
		if (l.nrLocuri > 0)
		{
			l.listaElevi = new Elev * [l.nrLocuri];
			for (int i = 0; i < l.nrLocuri; i++)
			{
				Elev e;
				in >> e;
				l.listaElevi[i] = new Elev(e);
			}
		}
		else
		{
			l.nrLocuri = 0;
			l.listaElevi = NULL;
		}
		in >> l.nrPersonal;
		for (int i = 0; i < 12; i++)
			in >> l.gazduireExpozitie[i];
		in >> (Activ&)l;
		return in;
	}

	//reluare metode virtuale din clasa de baza
	float calculAmPlata()
	{
		if (this->durataAm > 0)
			return (this->valoare * 1.05) / this->durataAm;
	}

	void claculAmTerminat()
	{
		if (this->vechime - this->durataAm >= 0)
			cout << "S-a terminat de amortizat";
		if (this->durataAm - this->vechime > 0)
			cout << "Durata de amortizare nu s-a terminat";
	}

};

ostream& operator<<(ostream& out, const Locatie& l)
{
	out << "\n-----------------------------------";
	out << "\nAdresa: " << l.adresa;
	out << "\nNr sali: " << l.nrSali;
	if (l.nrLocuri > 0 && l.listaElevi != NULL)
	{
		out << "\nNr locuri: " << l.nrLocuri;
		out << "\nLista elevilor: ";
		for (int i = 0; i < l.nrLocuri; i++)
			out << *l.listaElevi[i] << " ";
	}
	else
		out << "\nNu sunt inca elevi repartizati";
	out << "\nNr personal: " << l.nrPersonal;
	out << "\nLunile in care a gazduit o expozitie: ";
	for (int i = 0; i < 12; i++)
		if (l.gazduireExpozitie[i])
			out << i + 1 << " ";
	out << (Activ)l;
	out << "\n-----------------------------------";
	return out;
}

istream& operator>>(istream& in, Locatie& l)
{
	for (int i = 0; i <l.nrLocuri; i++)
		delete l.listaElevi[i];
	delete[] l.listaElevi;

	cout << "\nAdresa:";
	char adresa[100];
	in.getline(adresa, 100);
	l.adresa = adresa;
	cout << "Nr sali: ";
	in >> l.nrSali;
	cout << "Nr locuri: ";
	in >> l.nrLocuri;
	if (l.nrLocuri > 0)
	{
		l.listaElevi = new Elev * [l.nrLocuri];
		for (int i = 0; i < l.nrLocuri; i++)
		{
			Elev e;
			in >> e;
			l.listaElevi[i] = new Elev(e);
		}
	}
	else
	{
		l.nrLocuri = 0;
		l.listaElevi = NULL;
	}
	cout << "Nr personal: ";
	in >> l.nrPersonal;
	cout << "Gazduire expozitie: ";

		for (int i = 0; i < 12; i++)
			in >> l.gazduireExpozitie[i];
		in >> (Activ&)l;
	return in;
}

class Expozitie
{
private:
	string numeGazda = "NA";
	int nrVitrine = 0;
	float pretBilet = 0.0;
	int nrVizitatori = 0;
	int nrParticipanti = 0; //nr persoane care prezinta creatiile
	int* nrLucrari = NULL; //cate lucrari expune fiecare participant (dim nrParticipanti)
	float punctajLucrari[5]; //contine punctajul celor mai bune 5 lucrari

public:
	Expozitie()
	{
	}

	//functii accesor
	void setNumeGazda(string numeGazda)
	{
		if (numeGazda.length() >= 2)
			this->numeGazda = numeGazda;
	}

	string getNumeGazda()
	{
		return this->numeGazda;
	}

	void setNrVitrine(int nrVitrine)
	{
		if (nrVitrine > 0)
			this->nrVitrine = nrVitrine;
	}

	int getNrVitrine()
	{
		return this->nrVitrine;
	}

	void setPretBilet(float pretBilet)
	{
		if (pretBilet > 0)
			this->pretBilet = pretBilet;
	}

	float getPretBilet()
	{
		return this->pretBilet;
	}

	void setNrVizitatori(int nrVizitatori)
	{
		if (nrVizitatori > 0)
			this->nrVizitatori = nrVizitatori;
	}

	int getNrVizitatori()
	{
		return this->nrVizitatori;
	}

	void setNrParticipanti(int nrParticipanti)
	{
		if (nrParticipanti > 0)
			this->nrParticipanti = nrParticipanti;
	}

	int getNrPaticipanti()
	{
		return this->nrParticipanti;
	}

	void setNrLucrari(int nrParticipanti, int* nrLucrari)
	{
		delete[] this->nrLucrari;
		if (nrParticipanti > 0 && nrLucrari != NULL)
		{
			this->nrParticipanti = nrParticipanti;
			this->nrLucrari = new int[nrParticipanti];
			for (int i = 0; i < nrParticipanti; i++)
				this->nrLucrari[i] = nrLucrari[i];
		}
		else
		{
			this->nrParticipanti = 0;
			this->nrLucrari = NULL;
		}
	}

	int getNrLucrari(int i)
	{
		if (i >= 0 && i < this->nrParticipanti)
			return this->nrLucrari[i];
	}

	void setPunctajLucrari(float nr[5])
	{
		if (nr != NULL)
			for (int i = 0; i < 5; i++)
				this->punctajLucrari[i] = nr[i];
		else
			for (int i = 0; i < 5; i++)
				this->punctajLucrari[i] = 0;
	}

	float getPunctajLucrari(int i)
	{
		return this->punctajLucrari[i];
	}

	//metode prelucrare/afisare
	int nrTotalLucrariExpuse()
	{
		int s = 0;
		for (int i = 0; i < this->nrParticipanti; i++)
			s += this->nrLucrari[i];
		return s;
	}

	float profitBilete()
	{
		float p = this->nrVizitatori * this->pretBilet;
		return p;
	}

	//constructor cu toti parametrii
	Expozitie(string numeGazda,int nrVitrine, float pretBilet, int nrVizitatori, int nrParticipanti, int* nrLucrari, float punctajLucrari[5])
	{
		//cout << "\nAPEL CONSTR CU TOTI PARAM - EXPOZITIE\n";
		this->numeGazda = numeGazda;
		this->nrVitrine = nrVitrine;
		this->pretBilet = pretBilet;
		this->nrVizitatori = nrVizitatori;
		if (nrParticipanti > 0 && nrLucrari != NULL)
		{
			this->nrParticipanti = nrParticipanti;
			this->nrLucrari = new int[nrParticipanti];
			for (int i = 0; i < nrParticipanti; i++)
				this->nrLucrari[i] = nrLucrari[i];
		}
		else
		{
			this->nrParticipanti = 0;
			this->nrLucrari = NULL;
		}
		
			for (int i = 0; i < 5; i++)
				this->punctajLucrari[i] = punctajLucrari[i];
	}

	//constructor cu mai putini parametrii
	Expozitie(string numeGazda, int nrParticipanti, int* nrLucrari)
	{
		//cout << "\nAPEL CONSTR CU MAI PUTINI PARAM - EXPOZITIE\n";
		this->numeGazda = numeGazda;
		if (nrParticipanti > 0 && nrLucrari != NULL)
		{
			this->nrParticipanti = nrParticipanti;
			this->nrLucrari = new int[nrParticipanti];
			for (int i = 0; i < nrParticipanti; i++)
				this->nrLucrari[i] = nrLucrari[i];
		}
		else
		{
			this->nrParticipanti = 0;
			this->nrLucrari = NULL;
		}
	}

	//constructor de copiere
	Expozitie(const Expozitie& ex)
	{
		//cout << "\nAPEL CONSTR COPIERE - EXPOZITIE\n";
		this->numeGazda = ex.numeGazda;
		this->nrVitrine = ex.nrVitrine;
		this->pretBilet = ex.pretBilet;
		this->nrVizitatori = ex.nrVizitatori;
		if (ex.nrParticipanti > 0 && ex.nrLucrari != NULL)
		{
			this->nrParticipanti = ex.nrParticipanti;
			this->nrLucrari = new int[ex.nrParticipanti];
			for (int i = 0; i < ex.nrParticipanti; i++)
				this->nrLucrari[i] = ex.nrLucrari[i];
		}
		else
		{
			this->nrParticipanti = 0;
			this->nrLucrari = NULL;
		}
		
			for (int i = 0; i < 5; i++)
				this->punctajLucrari[i] = ex.punctajLucrari[i];
	}

	//destructor
	~Expozitie()
	{
		//cout << "\nAPEL DESTRUCTOR - EXPOZITIE\n";
		delete[] nrLucrari;
	}

	//supraincarcare operator=
	Expozitie& operator=(Expozitie& ex)
	{
		delete[] nrLucrari;
		//cout << "\nAPEL OP= - EXPOZITIE\n";
		this->numeGazda = ex.numeGazda;
		this->nrVitrine = ex.nrVitrine;
		this->pretBilet = ex.pretBilet;
		this->nrVizitatori = ex.nrVizitatori;
		if (ex.nrParticipanti > 0 && ex.nrLucrari != NULL)
		{
			this->nrParticipanti = ex.nrParticipanti;
			this->nrLucrari = new int[ex.nrParticipanti];
			for (int i = 0; i < ex.nrParticipanti; i++)
				this->nrLucrari[i] = ex.nrLucrari[i];
		}
		else
		{
			this->nrParticipanti = 0;
			this->nrLucrari = NULL;
		}
		for (int i = 0; i < 5; i++)
				this->punctajLucrari[i] = ex.punctajLucrari[i];
		return *this;
	}

	//supraincarcare operator[]
	int& operator[](int index)
	{
		if (index >= 0 && index < this->nrParticipanti)
			return this->nrLucrari[index];
		else
			throw exception("\nIndex invalid!");
	}

	//supraincarcare operator+
	Expozitie operator+(int val)
	{
		Expozitie aux = *this;
		aux.nrVizitatori += val;
		return aux;
	}

	//supraincarcare operator/
	Expozitie operator/(float val)
	{
		Expozitie aux = *this;
		aux.pretBilet = aux.pretBilet * (1 - val / 100);
		return aux;
	}

	//supraincarcare operator++ preincrementare
	Expozitie operator++()
	{
		this->nrVitrine++;
		return *this;
	}

	//supraincarcare operator++ postincrementare
	Expozitie operator++(int)
	{
		Expozitie aux = *this;
		delete[] this->nrLucrari;
		this->nrParticipanti++;
		this->nrLucrari = new int[this->nrParticipanti];
		for (int i = 0; i < aux.nrParticipanti; i++)
			this->nrLucrari[i] = aux.nrLucrari[i];
		this->nrLucrari[this->nrParticipanti - 1] = 0;
		return aux;
	}

	//supraincarcare operator cast
	explicit operator float()
	{
		return this->pretBilet;
	}

	//supraincare operator!
	Expozitie operator!()
	{
		Expozitie aux = *this;
		aux.nrVizitatori = 0;
		return aux;
	}

	//supraincarcare operator <=
	bool operator<=(const Expozitie& ex)
	{
		if (this->nrVitrine <= ex.nrVitrine)
			return true;
		return false;
	}

	//supraincarcare operator ==
	bool operator==(const Expozitie& ex)
	{
		if (this->nrParticipanti == ex.nrParticipanti)
			return true;
		return false;
	}

	void writeToFile(fstream& f)
	{
		int lg = this->numeGazda.length() + 1;
		f.write((char*)&lg, sizeof(int));
		f.write(this->numeGazda.data(), lg);
		f.write((char*)&this->nrVitrine, sizeof(int));
		f.write((char*)&this->pretBilet, sizeof(float));
		f.write((char*)&this->nrVizitatori, sizeof(int));
		f.write((char*)&this->nrParticipanti, sizeof(int));
		for (int i = 0; i < this->nrParticipanti; i++)
			f.write((char*)&this->nrLucrari[i], sizeof(int));
		int x = 5;
		f.write((char*)&x, sizeof(int));
		for (int i = 0; i < 5; i++)
			f.write((char*)&this->punctajLucrari[i], sizeof(float));
	}

	friend ostream& operator<<(ostream& out, const Expozitie& ex);
	friend istream& operator>>(istream& in, Expozitie& ex);

	friend ofstream& operator<<(ofstream& out, const Expozitie& ex)
	{
		out << ex.numeGazda;
		out << "\n" << ex.nrVitrine;
		out << "\n" << ex.pretBilet;
		out << "\n" << ex.nrVizitatori;
		out << "\n" << ex.nrParticipanti;
		if (ex.nrParticipanti > 0 && ex.nrLucrari != NULL)
		{
			out << "\n";
			for (int i = 0; i < ex.nrParticipanti; i++)
				out << ex.nrLucrari[i] << " ";
			out << "\n";
			for (int i = 0; i < 5; i++)
				out << ex.punctajLucrari[i] << " ";
		}
		return out;
	}

	friend ifstream& operator>>(ifstream& in, Expozitie& ex)
	{
		char nume[100];
		in.getline(nume, 100);
		ex.numeGazda = nume;
		delete[] ex.nrLucrari;
		in >> ex.nrVitrine;
		in >> ex.pretBilet;
		in >> ex.nrVizitatori;
		in >> ex.nrParticipanti;
		if (ex.nrParticipanti > 0)
		{
			ex.nrLucrari = new int[ex.nrParticipanti];
			for (int i = 0; i < ex.nrParticipanti; i++)
				in >> ex.nrLucrari[i];
		}
		else
		{
			ex.nrParticipanti = 0;
			ex.nrLucrari = NULL;
		}
		for (int i = 0; i < 5; i++)
			in >> ex.punctajLucrari[i];
		return in;
	}
};

ostream& operator<<(ostream& out, const Expozitie& ex)
{
	out << "\n-----------------------------------";
	out << "\nNume gazda: " << ex.numeGazda;
	out << "\nNr vitrine: " << ex.nrVitrine;
	out << "\nPret bilet intrare: " << ex.pretBilet;
	out << "\nNr vizitatori: " << ex.nrVizitatori;
	out << "\nNr participanti: " << ex.nrParticipanti;
	if (ex.nrParticipanti > 0 && ex.nrLucrari != NULL)
	{
		out << "\nNr lucrari ale fiecarui participant: ";
		for (int i = 0; i < ex.nrParticipanti; i++)
			out << ex.nrLucrari[i] << " ";
		out << "\nPunctajul celor mai bune 5 lucrari: ";
		for (int i = 0; i < 5; i++)
			out << ex.punctajLucrari[i] << " ";
	}
	else
		out << "\nNu sunt participanti";
	out << "\n-----------------------------------";
	return out;
}

istream& operator>>(istream& in, Expozitie& ex)
{
	cout << "\nNume gazda:";
	char nume[100];
	in.getline(nume, 100);
	ex.numeGazda = nume;
	delete[] ex.nrLucrari;
	cout << "Nr vitrine: ";
	in >> ex.nrVitrine;
	cout << "Pret bilet intrare: ";
	in >> ex.pretBilet;
	cout << "Nr vizitatori:";
	in >> ex.nrVizitatori;
	cout << "Nr participanti: ";
	in >> ex.nrParticipanti;
	if (ex.nrParticipanti > 0)
	{
		cout << "Nr luncrari ale fiecarui participant: ";
		ex.nrLucrari = new int[ex.nrParticipanti];
		for (int i = 0; i < ex.nrParticipanti; i++)
			in >> ex.nrLucrari[i];
	}
	else
	{
		ex.nrParticipanti = 0;
		ex.nrLucrari = NULL;
	}
	cout << "Punctajul celor mai bune 5 lucrari: ";
		for (int i = 0; i < 5; i++)
			in >> ex.punctajLucrari[i];
	return in;
}

int Elev::nrElevi = 0;
int Formator::nrFormatori = 0;
//citire din fisiere CSV
void citire_CSV()
{
	string numef;
	cout << "\nNumele fisierului de unde sa se citeasca datele (fisier existent): ";
	cin >> numef;
	ifstream fin(numef);
	ofstream fout("dateCSV.txt");
	while (fin.good())
	{
		string linie;
		getline(fin, linie, ',');
		cout << linie << endl;
		fout << linie << endl;
	}
	fin.close();
	fout.close();
}

int main()
{
	//cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASA ELEV~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	////apel constructor cu toti parametrii
	Elev e1(1, "Popescu Marian", 3, new int[] {2, 3, 2}, new int[12] {0, 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 0},2);
	//cout << e1;

	////apel constructor cu mai putini parametrii
	Elev e2(2, "Marinescu Ion", 5, new int[] {3, 2, 4, 5, 2});
	//cout << e2;

	////apel functii accesor
	Elev e3;
	//cout << "\nId: " << e1.getId();
	e3.setNume("Ionescu Florentina");
	//cout << "\nNume: " << e3.getNume();
	e3.setNrSaptamani(4);
	//cout << "\nNr saptamani: " << e3.getNrSaptamani();
	e3.setNrLectii(e3.getNrSaptamani(), new int[] {3, 4, 3, 5});
	//cout << "\nNr lectii: " << e3.getNrLectii(0) << " " << e3.getNrLectii(1) << " " << e3.getNrLectii(2) << " " << e3.getNrLectii(3) << " ";
	e3.setNrLucrariExpozitie(new int[] {0, 0, 0, 0, 3, 4, 6, 0, 0, 0, 0, 0});
	//cout << "\nNr lucrari expuse la expozitii: " << e3.getNrLucrariExpozitie(5);
	e3.setModuleTerminate(3);
	//cout << "\nModue terminate: " << e3.getModuleTerminate();
	//cout << "\nNr elevi: " << e3.getNrElevi();

	////apel metode de prelucrare/afisare
	//cout << "\n" << e3.getNume() << " are in total " << e3.nrTotalLucrariExpuse() << " lucrari expuse.\n";
	//e2.lectieBonus(); cout << endl;
	//e3.lectieBonus();

	////apel constructor copiere
	Elev e4(e1);
	//cout << e4;

	////apel operator =
	Elev e5;
	e5 = e2;
	//cout << e5;

	////apel cin si cout
	Elev e6;
	////cin >> e6;
	//cout << e6;

	////apel op []
	//try
	//{
	//	int aux = e2[5];
	//	cout << endl << aux;
	//}
	//catch (exception ex)
	//{
	//	cout << ex.what();
	//}

	////apel op +
	//cout<< endl<<e2 + 2;

	////apel op ++
	//cout <<endl<< ++e3;
	//cout <<endl<< e3++;
	//cout << endl << e3;

	////apel op cast
	//int lectii = (int)e2;
	//cout << endl << lectii;

	////apel op !
	Elev e7 = !e1;
	//cout << e7 << endl;

	////apel op <
	//if (e3 < e4)
	//	cout << e3.getNume() << " a terminat mai putine module ca " << e4.getNume() << endl;
	//else
	//	cout << e4.getNume() << " a terminat mai putine module ca " << e3.getNume() << endl;

	////apel op ==
	//if (e3 == e4)
	//	cout << "Cei doi elevi au acs nr de saptamani " << endl;
	//else
	//	cout << "Cei doi elevi au nr diferit de saptamani " << endl;

	//fisiere text
	/*ofstream ge("elev2.txt");
	ge << e1;
	ge << e2 << e4;
	ge.close();

	ifstream fe("elev_in.txt");
	Elev e8;
	fe >> e8;
	cout << e8;
	fe.close();*/

	//fisiere binare
	/*fstream fe_out("elevbin.txt", ios::out | ios::binary);
	e1.writeToFile(fe_out);
	fe_out.close();*/

	//raport
	//afisare elevi in ordine alfabetica
	set<string> listaNume;
	set<string>::iterator iLN;
	ofstream re_out("elev_raport.txt");
	listaNume.insert(e1.getNume());
	listaNume.insert(e2.getNume());
	listaNume.insert(e3.getNume());
	listaNume.insert(e4.getNume());
	listaNume.insert(e5.getNume());
	/*for (iLN = listaNume.begin(); iLN != listaNume.end(); iLN++)
	{
		cout << *iLN << "\n";
		re_out << *iLN << "\n";
	}
	*/

	//citire CSV
	/*citire_CSV("elevCSV.csv");*/

	Elev* listaElevi[] = { &e1,&e2,&e3,&e4,&e5,&e6,&e7 };

	//cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASA FORMATOR~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	Elev* le1[] = { &e1,&e2,&e3 };
	Elev* le2[] = { &e4,&e5 };
	Elev* le3[] = { &e6,&e7 };
	int ore1[44] = { 25,12,13,29,10,14,30,16,21,24,11,22,17,15,28,10,0,0,0,0,0,24,21,29,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int ore2[44] = { 25,12,13,29,10,14,30,16,21,24,11,22,17,15,28,10,0,0,0,0,0,24,21,29,10,0,12,13,29,10,14,30,16,21,0,0,0,0,0,0,0,0,0,0 };
	////apel constructor cu toti parametrii
	Formator f1(1, "Martha Bibescu", le1, 3, 1234.56, ore1);
	//cout << f1;

	////apel constructor cu mai putini parametrii
	Formator f2(2, "Ion Ratiu", le2, 2);
	//cout << f2;

	////apel functii accesor
	Formator f3;
	//cout << "\nId: " << f2.getId();
	f3.setNume("Dominique Loreanu");
	//cout << "\nNume: " << f3.getNume();
	f3.setNrElevi(2);
	//cout << "\nNr elevi atribuiti: " << f3.getNrElevi();
	f3.setListaElevi(2, le3);
	//cout << "\nLista elevi: " << f3.getListaElevi(0) << f3.getListaElevi(1);
	f3.setSalariu(2322.0);
	//cout << "\nSalariu: " << f3.getSalariu();
	f3.setOreLucrate(ore2);
	//cout << "\nOre lucrate: " << f3.getOreLucrate(24);
	//cout << "\nNr formatori: " << f3.getNrFormatori();

	////apel metode prelucrare/afisare
	//cout << "\nNr total ore lucrate: " << f1.nrTotalOreLucrate();
	//cout << "\nSalariu : " << f1.marireSalariu();

	////apel constructor copiere
	Formator f4(f1);
	//cout << f4;

	////apel operator =
	Formator f5;
	//f5 = f2;
	//cout << f5;

	////apel cin si cout
	Formator f6;
	////cin >> f6;
	//cout << f6;

	////apel op []
	//try
	//{
	//	Elev aux = f2[5];
	//	cout << endl << aux;
	//}
	//catch (exception ex)
	//{
	//	cout << ex.what();
	//}

	////apel op +
	//f6 = f1 + 100;
	//cout << f6;

	////apel op *
	//f5 = f3 * 20.0;
	//cout << f5;

	////apel op ++
	//cout << endl << ++f2;
	//f6++;
	//cout << endl << f6;

	////apel op cast
	//string nume = (string)f4;
	//cout << "\nNume: " << nume;

	////apel op !
	//f6 = !f3;
	//cout << f6 << endl;

	////apel op >
	//if (f1 > f3)
	//	cout << f1.geNume() << " are mai multi elevi ca " << f3.geNume() << endl;
	//else
	//	cout << f3.geNume() << " are mai multi elevi ca " << f1.geNume() << endl;

	////apel op ==
	//if (f1 == f3)
	//	cout << f1.geNume() << " are salariul mai mare ca " << f3.geNume() << endl;
	//else
	//	cout << f3.geNume() << " are salariul mai mare ca " << f1.geNume() << endl;

	//fisiere text
	/*ofstream gf("formator.txt");
	gf << f1;
	gf.close();

	ifstream ff("formator2.txt");
	ff >> f3;
	cout << f3;
	ff.close();*/

	//fisiere binare
	/*fstream ff_out("formatorbin.txt", ios::out | ios::binary);
	f1.writeToFile(ff_out);
	ff_out.close();*/

	//raport
	//afisare lista formatori cu salariul aferent fiecaruia
	ofstream rf_out("formator_raport.txt");
	map<string, float> mapFormator;
	map<string, float>::iterator iMF;
	mapFormator[f1.getNume()] = f1.getSalariu();
	mapFormator[f2.getNume()] = f2.getSalariu();
	mapFormator[f3.getNume()] = f3.getSalariu();
	mapFormator[f4.getNume()] = f4.getSalariu();
	mapFormator[f5.getNume()] = f5.getSalariu();
	mapFormator[f6.getNume()] = f6.getSalariu();
	/*for (iMF = mapFormator.begin(); iMF != mapFormator.end(); iMF++)
	{
		cout << iMF->first << " " << iMF->second << endl;
		rf_out << iMF->first << " " << iMF->second << endl;
	}
	*/

	//cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASA ECHIPAMENT~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	//cout << Formator::getNrFormatori();
	////apel costructor cu toti paramentrii
	Echipament ek1("Hartie alba", 200, 2, new int[6]{ 23,12,15,17,20,13 }, new bool[12]{ 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 },20.0,0,0);
	//cout << ek1;

	////apel constructor cu mai putini parametrii
	Echipament ek2("Foarfece", 50, new int[6]{ 5,7,6,9,10,8 });
	//cout << ek2;

	////apel functii accesor
	Echipament ek3;
	ek3.setDenumire("Hartie creponata");
	//cout << "\nDenumire: " << ek3.getDenumire();
	ek3.setNrBucati(200);
	//cout << "\nNr bucati: " << ek3.getNrBucati();
	ek3.setNrBucDefecte(3);
	//cout << "\nNr bucati defecte: " << ek3.getNrBucDefecte();
	ek3.setNrPeFormator(new int[6]{ 23,12,15,17,20,13 });
	//cout << "\nNr buc pt fiecare formator: " << ek3.getNrPeFormator(2);
	ek3.setRestoc(new bool[12]{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0 });
	//cout << "\nRefacere stoc: " << ek3.getRestoc(5);
	ek3.setValoare(30.0);
	ek3.setDurataAm(0);
	ek3.setVechime(1);

	////apel metode de prelucrare/afisare
	//cout << "\nNr total de luni: " << ek1.nrTotalRestoc();
	//cout << "\nNr total buc distribuite: " << ek2.nrTotalBucDistribuite();

	////apel constr copiere
	Echipament ek4(ek1);
	//cout << ek4;
	ek4.setValoare(25.0);
	ek4.setDurataAm(2);
	ek4.setVechime(1);

	////apel op =
	Echipament ek5;
	ek5 = ek2;
	//cout << ek5;
	ek5.setValoare(50.5);
	ek5.setDurataAm(1);
	ek5.setVechime(1);

	////apel cin si cout
	Echipament ek6;
	////cin >> ek6;
	//cout << ek6;

	////apel op []
	//try
	//{
	//	int buc = ek2[5];
	//	cout << endl << buc;
	//}
	//catch (exception ex)
	//{
	//	cout << ex.what();
	//}

	////apel op +
	//cout<<endl<< ek3 + 50;

	////apel op -
	//cout << endl << ek2 - 20;

	////apel op ++
	//cout << endl << ++ek2;
	//ek2++;
	//cout << endl << ek2;

	////apel op cast
	//int nr = (int)ek3;
	//cout << endl << nr;

	////apel op !
	//bool ok = !ek5;
	//if (ok)
	//	cout << "\nDa";
	//else
	//	cout << "\nNu";

	////apel op >=
	//if (ek4 >= ek2)
	//	cout << endl << ek4.getDenumire() << " are mai multe bucati ca " << ek2.getDenumire();
	//else
	//	cout << endl << ek2.getDenumire() << " are mai multe bucati ca " << ek4.getDenumire();

	////apel op ==
	//if (ek4 == ek1)
	//	cout << endl << "Cele 2 echipamente au acs denumire.";
	//else
	//	cout << endl << "Au denumire diferita";
	
	//fisiere text
	/*ofstream gek("echipament.txt");
	gek << ek1;
	gek.close();

	ifstream fek("echipament2.txt");
	fek >> ek3;
	cout << ek3;
	fek.close();*/

	//fisiere binare
	/*fstream fek_out("echipamentbin.txt", ios::out | ios::binary);
	ek1.writeToFile(fek_out);
	fek_out.close();*/

	//raport
	//afisare denumire echipament si diferenta dintre nr de buc total si nr buc defecte
	ofstream rek_out("echipament_raport.txt");
	map<string, int> mapEchipament;
	map<string, int>::iterator iME;
	mapEchipament[ek1.getDenumire()] = ek1.getNrBucati() - ek1.getNrBucDefecte();
	mapEchipament[ek2.getDenumire()] = ek2.getNrBucati() - ek2.getNrBucDefecte();
	mapEchipament[ek3.getDenumire()] = ek3.getNrBucati() - ek3.getNrBucDefecte();
	/*for (iME = mapEchipament.begin(); iME != mapEchipament.end(); iME++)
	{
		cout << iME->first << " " << iME->second << endl;
		rek_out << iME->first << " " << iME->second << endl;
	}
	*/

	//cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASA LOCATIE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	////apel constr cu toti parametrii
	Locatie l1("Str Leonard, nr 5", 3, 3, 4, le1, new bool[12]{ 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0 }, 1200.0, 3, 1);
	//cout << l1;

	////apel constr cu mai putini parametrii
	Locatie l2("Str Carpati, nr 2", 2, le2);
	//cout << l2;

	////apel functii accesor
	Locatie l3;
	l3.setAdresa("Str Marasesti, nr 15");
	//cout << "\nAdresa: " << l3.getAdresa();
	l3.setNrSali(5);
	//cout << "\nNr sali: " << l3.getNrSali();
	l3.setNrLocuri(2);
	//cout << "\nNr locuri: " << l3.getNrLocuri();
	l3.setListaElevi(2, le3);
	//cout << "\nLista elevi: " << l3.getListaElevi(1);
	l3.setNrPersonal(3);
	//cout << "\nNr personal: " << l3.getNrPersonal();
	l3.setGazduireExpozitie(new bool[12]{ 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0 });
	//cout << "\nExpozitie gazduita: " << l3.getGazduireExpozitie(6);
	l3.setValoare(1236.0);
	l3.setDurataAm(3);
	l3.setVechime(1);

	////apel metode prelucrare/afisare
	//cout << "\nNr total de expozitii gazduite: " << l1.nrTotalGazduireExpozitie();
	//l3.poateGazduiExpozitie();

	////apel constr copiere
	Locatie l4(l2);
	//cout << l4;
	l4.setValoare(1366.0);
	l4.setDurataAm(4);
	l4.setVechime(1);

	////apel op =
	Locatie l5;
	l5 = l3;
	//cout << l5;
	l5.setValoare(1455.5);
	l5.setDurataAm(4);
	l5.setVechime(2);

	////apel cin si cout
	Locatie l6;
	////cin >> l6;
	//cout << l6;

	////apel op []
	//try
	//{
	//	Elev a = l2[5];
	//	cout << endl << a;
	//}
	//catch (exception ex)
	//{
	//	cout << ex.what();
	//}

	////apel op -
	//l5 = l3 - 1;
	//cout << l5;

	////apel op ++
	//cout << endl << ++l2;
	//l2++;
	//cout << endl << l2;

	////apel op cast
	//string adresa = (string)l3;
	//cout << endl << adresa;

	////apel op !
	l6 = !l2;
	//cout << l6 << endl;

	////apel op >
	//if (l2 > l3)
	//	cout << "Locatia de la adresa " << l2.getAdresa() << " are mai multe sali dacat locatia de la adresa " << l3.getAdresa() << endl;
	//else
	//	cout << "Locatia de la adresa " << l3.getAdresa() << " are mai multe sali dacat locatia de la adresa " << l2.getAdresa() << endl;

	////apel op ==
	//if (l2 == l3)
	//	cout << "Locatiile au nr egal de locuri" << endl;
	//else
	//	cout << "Locatiile au nr fiferit de locuri" << endl;

	//fisiere text
	/*ofstream gl("locatie.txt");
	gl << l1;
	gl.close();

	ifstream fl("locatie2.txt");
	fl >> l6;
	cout << l6;
	fl.close();*/

	//fisiere binare
	/*fstream fl_out("locatiebin.txt", ios::out | ios::binary);
	l1.writeToFile(fl_out);
	fl_out.close();*/

	//raport
	ofstream rl_out("locatie_raport.txt");
	vector<Locatie> vectorLocatii;
	vectorLocatii.push_back(l1);
	vectorLocatii.push_back(l2);
	vectorLocatii.push_back(l3);
	vectorLocatii.push_back(l4);
	vectorLocatii.push_back(l5);
	vectorLocatii.push_back(l6);
	/*for (int i = 0; i < vectorLocatii.size(); i++)
	{
		cout << vectorLocatii[i].getAdresa() << " ; nr locuri: " << vectorLocatii[i].getNrLocuri() << endl;
		rl_out << vectorLocatii[i].getAdresa() << " ; nr locuri: " << vectorLocatii[i].getNrLocuri() << endl;
	}*/
	

	//cout << "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~CLASA EXPOZITIE~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	////apel constr cu toti parametrii
	Expozitie ex1("Mircea Ganga", 12, 5.5, 15, 3, new int[]{ 12,10,15 }, new float[5]{ 10.0,10.0,9.85,9.65,9.45 });
	//cout << ex1;

	////apel constr cu mai putini parametrii
	Expozitie ex2("Georgeta Burtea", 4, new int[]{ 10,5,12,9 });
	//cout << ex2;

	////apel functii accesor
	Expozitie ex3;
	ex3.setNumeGazda("Jean des Cars");
	//cout << "\nNume gazda: " << ex3.getNumeGazda();
	ex3.setNrVitrine(5);
	//cout << "\nNr vitrine: " << ex3.getNrVitrine();
	ex3.setPretBilet(3.5);
	//cout << "\nPret bilet: " << ex3.getPretBilet();
	ex3.setNrVizitatori(10);
	//cout << "\nNr vizitatori: " << ex3.getNrVizitatori();
	ex3.setNrParticipanti(3);
	//cout << "\nNr participanti: " << ex3.getNrPaticipanti();
	ex3.setNrLucrari(ex3.getNrPaticipanti(), new int[] {20, 15, 19});
	//cout << "\nNr lucrari expuse: " << ex3.getNrLucrari(1);
	ex3.setPunctajLucrari(new float[5]{ 10.0,9.89,9.72,9.51,9.42 });
	//cout << "\nPunctaj lucrare: " << ex3.getPunctajLucrari(3);

	////apel metode prelucrare/afisare
	//cout << "\nNr total lucrari expuse: " << ex3.nrTotalLucrariExpuse();
	//cout << "\nProfit total: " << ex1.profitBilete();

	////apel constr copiere
	Expozitie ex4(ex1);
	//cout << ex4;

	////apel op=
	Expozitie ex5;
	ex5 = ex3;
	//cout << ex5;

	////apel cin si cout
	Expozitie ex6;
	////cin >> ex6;
	//cout << ex6;

	////apel op []
	//try
	//{
	//	int p = ex4[6];
	//	cout << endl << p;
	//}
	//catch (exception ex)
	//{
	//	cout << ex.what();
	//}

	////apel op +
	//cout << endl << ex3 + 2;

	////apel op /
	//cout<< endl << ex1 / 5.0;

	////apel op ++
	//cout << endl << ++ex2;
	//ex4++;
	//cout << endl << ex4;

	////apel op cast
	//float pret = (float)ex4;
	//cout << "\npret: " << pret;

	////apel op !
	//cout << endl << !ex5;

	////apel op <=
	//if (ex4 <= ex5)
	//	cout << "\nEpozitia gazduita de " << ex4.getNumeGazda() << " are mai putine vitrine dacat expozitia gazduita de " << ex5.getNumeGazda();
	//else
	//	cout << "\nEpozitia gazduita de " << ex5.getNumeGazda() << " are mai putine vitrine dacat expozitia gazduita de " << ex4.getNumeGazda();

	////apel op ==
	//if (ex3 == ex6)
	//	cout << "\nCele 2 expozitii au acs nr de paricipanti";
	//else
	//	cout << "\nAu nr diferit de participanti";

	//fisiere text
	/*ofstream gex("expozitie.txt");
	gex << ex1;
	gex.close();

	ifstream fex("expozitie.txt");
	fex >> ex6;
	cout << ex6;
	fex.close();*/

	//fisiere binare
	/*fstream fex_out("expozitiebin.txt", ios::out | ios::binary);
	ex1.writeToFile(fex_out);
	fex_out.close();*/

	list<Expozitie> listaExpozitie;
	listaExpozitie.push_back(ex1);
	listaExpozitie.push_back(ex2);
	listaExpozitie.push_back(ex3);
	listaExpozitie.push_back(ex4);
	listaExpozitie.push_back(ex5);
	listaExpozitie.push_back(ex6);
	list<Expozitie>::iterator iLE;
	ofstream rex_out("expozitie_raport.txt");

	//-------------------------------------------------------------------------------------
	//cout << "\n-------------------------------CLASA ACTIV------------------------------------\n";
	//vectori de pointeri la clasa de baza Activ
	/*Activ* listaActive[] = {&ek1,&ek2,&ek3,&ek4,&ek5,&l1,&l2,&l3,&l4,&l5};
	cout << "Prima metoda virtuala\n";
	for (int i = 0; i < 10; i++)
	{
		cout << endl <<listaActive[i]->getDurataAm()<<"\t" << listaActive[i]->calculAmPlata();
	}
	cout << "\nA doua metoda virtuala\n";
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
		listaActive[i]->calculAmTerminat();
	}*/

	//-------------------------------------------------------------------------------------
	
	
	afisareMeniu();
	int varianta;
	string confirm;
	do
	{
		cout << "Alege una din variante(1-9): ";
		cin >> varianta;
		switch (varianta)
		{
		case 1://afisare informatii elevi
			int nrElev, nrInfoE;
			cout << "Alege un elev (1-7):";
			cin >> nrElev;
			cout << "Alege  ce tip de informatie sa se afiseze \n\tnumele - 1 \n\tnr saptamani programate - 2 \n\tnr lectii programate - 3 \n\tnr lucrari expozitie - 4 \n\tnr module terminate - 5 \n\ttoate datele - 6 ";
			cout << "\n\tpoate avea o lectie bonus - 7: ";
			cin >> nrInfoE;
			switch (nrInfoE)
			{
			case 1:
				cout << listaElevi[nrElev]->getNume() << endl;
				break;
			case 2:
				cout << listaElevi[nrElev]->getNrSaptamani() << endl;
				break;
			case 3:
				int i;
				cout << "Alege saptamana: ";
				cin >> i;
				cout << listaElevi[nrElev]->getNrLectii(i) << endl;
				break;
			case 4:
				int j;
				cout << "Alege luna: ";
				cin >> j;
				cout << listaElevi[nrElev]->getNrLucrariExpozitie(j) << endl;
				break;
			case 5:
				cout << listaElevi[nrElev]->getModuleTerminate() << endl;
				break;
			case 6:
				cout << listaElevi[nrElev] << endl;
				break;
			case 7:
				listaElevi[nrElev]->lectieBonus();
				cout << endl;
				break;
			default:
				cout << "Varianta inexistenta\n";
				break;
			}
			break;
		case 2://afisare nr formatori
			cout << Formator::getNrFormatori() << endl;
			break;
		case 3://citire fisier CSV si scriere in fisier txt
			citire_CSV();
			break;
		case 4://afisare informatii locatie
			int nrLoc, nrInfo;
			cout << "Alege o locatie (1-6):";
			cin >> nrLoc;
			cout << "Alege  ce tip de informatie sa se afiseze \n\tadresa - 1 \n\tnr sali - 2 \n\tnr locuri - 3 \n\tnr personal - 4 \n\tgazduire expozitie - 5 \n\ttoate datele - 6 ";
			cout << "\n\tde cate ori a gazduit o expozitie - 7: ";
			cin >> nrInfo;
			switch (nrInfo)
			{
			case 1:
				cout << vectorLocatii[nrLoc].getAdresa() << endl;
				break;
			case 2:
				cout << vectorLocatii[nrLoc].getNrSali() << endl;
				break;
			case 3:
				cout << vectorLocatii[nrLoc].getNrLocuri() << endl;
				break;
			case 4:
				cout << vectorLocatii[nrLoc].getNrPersonal() << endl;
				break;
			case 5:
				int i;
				cout << "Alege luna: ";
				cin >> i;
				cout << vectorLocatii[nrLoc].getGazduireExpozitie(i) << endl;
				break;
			case 6:
				cout << vectorLocatii[nrLoc] << endl;
				break;
			case 7:
				cout << vectorLocatii[nrLoc].nrTotalGazduireExpozitie() << endl;
				break;
			default:
				cout << "Varianta inexistenta\n";
				break;
			}
			break;
		case 5://raport elevi
			for (iLN = listaNume.begin(); iLN != listaNume.end(); iLN++)
			{
				cout << *iLN << "\n";
				re_out << *iLN << "\n";
			}
			break;
		case 6://raport formatori
			for (iMF = mapFormator.begin(); iMF != mapFormator.end(); iMF++)
			{
				cout << iMF->first << " " << iMF->second << endl;
				rf_out << iMF->first << " " << iMF->second << endl;
			}
			break;
		case 7://raport echipamente
			for (iME = mapEchipament.begin(); iME != mapEchipament.end(); iME++)
			{
				cout << iME->first << " " << iME->second << endl;
				rek_out << iME->first << " " << iME->second << endl;
			}
			break;
		case 8://raport locatii
			for (int i = 0; i < vectorLocatii.size(); i++)
			{
				cout << vectorLocatii[i].getAdresa() << " ; nr locuri: " << vectorLocatii[i].getNrLocuri() << endl;
				rl_out << vectorLocatii[i].getAdresa() << " ; nr locuri: " << vectorLocatii[i].getNrLocuri() << endl;
			}
			break;
		case 9://raport expozitii
			for (iLE=listaExpozitie.begin();iLE!=listaExpozitie.end();iLE++)
			{
				cout << "Gazda: " << iLE->getNumeGazda() << " ; nr vizitatori: " << iLE->getNrVizitatori() << " ; nr participanti: " << iLE->getNrPaticipanti() << endl;
				rex_out << "Gazda: " << iLE->getNumeGazda() << " ; nr vizitatori: " << iLE->getNrVizitatori() << " ; nr participanti: " << iLE->getNrPaticipanti() << endl;
			}
			break;
		default:
			cout << "Varianta inexistenta\n";
			break;
		}
		cout << "Apasa y sau Y pentru a continua; apasa orice tasta pentru a termina: ";
		cin >> confirm;
	} while (confirm =="y" || confirm=="Y");

	re_out.close();
	rf_out.close();
	rek_out.close();
	rl_out.close();
	rex_out.close();
	
	
	return 0;
}