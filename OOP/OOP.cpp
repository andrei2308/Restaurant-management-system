#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class materieprima
{
private:
	char* denumire;
	float cantitate;
	static int totalmaterie;
public:
	void afisare()
	{
		cout << "Denumire: " << denumire << endl;
		cout << "Cantitate: " << cantitate << endl;

	}
	static int gettotalmat()
	{
		return totalmaterie;
	}
	bool operator==(const materieprima& p) const
	{
		return (denumire == p.denumire && cantitate == p.cantitate);
	}
	bool operator!() const
	{
		return (cantitate == 0);
	}
	materieprima& operator++() {
		++cantitate;
		return *this;
	}
	materieprima operator+(const materieprima& p) const
	{
		materieprima rezultat = *this;
		rezultat.cantitate += p.cantitate;

		return rezultat;
	}
	materieprima() :denumire(nullptr), cantitate(0)
	{
		totalmaterie++;
	}
	materieprima(const char* nume, float cantitate) :cantitate(cantitate)
	{
		if (nume && nume[0] != '\0')
		{
			denumire = new char[strlen(nume) + 1];
			strcpy_s(denumire, strlen(nume) + 1, nume);
		}
		else
		{
			denumire = new char[1];
			denumire[0] = '\0';
		}
	}
	materieprima(const materieprima& p) : cantitate(p.cantitate)
	{
		denumire = new char[strlen(p.denumire) + 1];
		strcpy_s(denumire, strlen(p.denumire) + 1, p.denumire);
	}
	~materieprima()
	{
		delete[] denumire;
		totalmaterie--;
	}
	operator int() const
	{
		return static_cast<int>(cantitate);
	}
	materieprima& operator=(const materieprima& p)
	{
		if (this != &p) {
			delete[] denumire;

			cantitate = p.cantitate;

			denumire = new char[strlen(p.denumire) + 1];
			strcpy_s(denumire, strlen(p.denumire) + 1, p.denumire);
		}
		return *this;
	}
	bool operator>=(const materieprima& d) const {
		return cantitate >= d.cantitate;
	}

	friend ostream& operator<<(ostream& out, const materieprima& materie)
	{
		out << "Denumire: " << materie.denumire << endl;
		out << "Cantitate: " << materie.cantitate << endl;
		return out;
	}
	friend istream& operator>>(istream& in, materieprima& materie)
	{
		char buffer[100];
		cout << "Denumire: ";
		in >> buffer;
		materie.setdenumire(buffer);

		cout << endl;
		cout << "Cantitate: ";
		in >> materie.cantitate;
		cout << endl;

		return in;
	}
	void setdenumire(const char* den)
	{
		if (den && den[0] != '\0') {
			delete[] denumire;
			denumire = new char[strlen(den) + 1];
			strcpy_s(denumire, strlen(den) + 1, den);
		}
		else {
			cout << "Nume eronat." << endl;
		}
	}

	const char* getdenumire() const
	{
		return denumire;
	}

	void setcantitate(float cant)
	{
		if (cant >= 0)
		{
			cantitate = cant;
		}
		else
		{
			cout << "Cantitate eronata." << endl;
		}
	}

	float getcantitate() const
	{
		return cantitate;
	}
};
int materieprima::totalmaterie = 10000;
class reteta
{
private:
	vector<pair<materieprima, float>> ingrediente;

public:
	void afiseaza() const
	{
		cout << "Ingrediente: " << endl;
		for (const auto& ingredient : ingrediente) {
			cout << "Nume ingredient: " << ingredient.first.getdenumire() << " Cantitate: " << ingredient.second << endl;
		}
	}

	materieprima& operator[](int id)
	{
		if (id >= 0 && id < ingrediente.size())
		{
			return ingrediente[id].first;
		}
		else {
			throw out_of_range("Id prea mare.");
		}
	}

	void adaugaingredient(const materieprima& ingredient, float cantitate)
	{
		ingrediente.push_back(make_pair(ingredient, cantitate));
	}

	friend ostream& operator<<(ostream& out, const reteta& r)
	{
		out << "Ingrediente: " << endl;
		for (const auto& ingredient : r.ingrediente) {
			out << "Nume ingredient: " << ingredient.first.getdenumire() << " Cantitate: " << ingredient.second << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, reteta& r)
	{
		int nring;
		cout << "Numarul de ingrediente: ";
		in >> nring;

		for (int i = 0; i < nring; ++i) {
			materieprima ingredient;
			float cantitate;
			in >> ingredient >> cantitate;
			r.ingrediente.push_back(make_pair(ingredient, cantitate));
		}
		return in;
	}
	void setingredient(int id, float noua_cantitate)
	{
		if (id >= 0 && id < ingrediente.size()) {
			ingrediente[id].second = noua_cantitate;
		}
		else {
			cout << "Id invalid." << endl;
		}
	}
	int getnringrediente()
	{
		return ingrediente.size();
	}
	~reteta()
	{

	}
	const vector<pair<materieprima, float>>& getingrediente() const
	{
		return ingrediente;
	}
	vector<pair<materieprima, float>>& getingredientemod()
	{
		return ingrediente;
	}

};

class preparate
{
private:
	char* nume;
	reteta retet;
public:
	~preparate()
	{
		delete[] nume;
	}

	void afisare() const
	{
		cout << "Nume: " << nume << endl;
	}
	preparate(const char* den, const reteta& reteta) : retet(reteta)
	{
		if (retet.getnringrediente() == 0) {
			cout << "Reteta nu exista." << endl;
		}
		if (den && den[0] != '\0') {
			nume = new char[strlen(den) + 1];
			strcpy_s(nume, strlen(den) + 1, den);
		}
		else {
			nume = new char[1];
			nume[0] = '\0';
		}
	}
	preparate(const preparate& p) : retet(p.retet)
	{
		if (p.nume) {
			nume = new char[strlen(p.nume) + 1];
			strcpy_s(nume, strlen(p.nume) + 1, p.nume);
		}
		else {
			nume = nullptr;
		}
	}
	preparate() :nume() {}
	void setnume(const char* num)
	{
		if (num) {
			delete[] nume;
			nume = new char[strlen(num) + 1];
			strcpy_s(nume, strlen(num) + 1, num);
		}
	}
	const char* getnume() const
	{
		return nume ? nume : "";
	}
	void setreteta(reteta& ret)
	{
		if (ret.getnringrediente() > 0) {
			retet = ret;
		}
		else {
			cout << "Reteta trebuie sa contina cel putin un ingredient.";
		}
	}
	const reteta& getreteta() const
	{
		return retet;
	}
	preparate& operator=(preparate& p)
	{
		if (this != &p) {
			delete[] nume;
			if (p.nume) {
				nume = new char[strlen(p.nume) + 1];
				strcpy_s(nume, strlen(p.nume) + 1, p.nume);
			}
			else {
				nume = nullptr;
			}
			retet = p.retet;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const preparate& p)
	{
		out << "Nume preparat: " << (p.nume ? p.nume : "") << endl;
		out << "Reteta:" << endl << p.retet;
		return out;
	}

	friend istream& operator>>(istream& in, preparate& p)
	{
		char buffer[100];
		cout << "Nume preparat: ";
		in.getline(buffer, sizeof(buffer));
		p.setnume(buffer);
		return in;
	}
};
class comanda
{
private:
	vector<preparate> preparatele;

public:
	void afiseaza() const
	{
		for (const auto& prep : preparatele) {
			cout << prep << endl;
		}
	}
	comanda(const comanda& p) : preparatele(p.preparatele)
	{

	}
	const vector<preparate>& getprep() const
	{
		return preparatele;
	}
	void setprep(const vector<preparate>& preparat)
	{
		if (!preparat.empty()) {
			preparatele = preparat;
		}
		else {
			cout << "Vectorul este gol" << endl;
		}
	}
	void adaugapreparat(const preparate& p)
	{
		preparatele.push_back(p);
	}
	comanda() {}
	comanda(const vector<preparate>& prepar) : preparatele(prepar) {}
	comanda(comanda& p) :preparatele(p.preparatele) {}
	comanda& operator=(comanda& p)
	{
		if (this != &p)
		{
			preparatele = p.preparatele;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const comanda& c)
	{
		for (const auto& prep : c.preparatele)
		{
			out << prep << endl;
		}
		return out;
	}

	friend istream& operator>>(istream& in, comanda& c)
	{
		cout << "Introduceti preparatele din comanda:" << endl;
		preparate prep;
		in >> prep;
		c.adaugapreparat(prep);
		return in;
	}

};
class restaurant
{
private:
	vector<materieprima> stoc;
	vector<comanda> comenzi;
	vector<preparate> prep;
	static const int maxim = 15;
public:
	void adaugacomanda(const comanda& com)
	{
		if (comenzi.size() < maxim) {
			comenzi.push_back(com);
		}
		else {
			cout << "Numarul maxim de comenzi a fost atins." << endl;
			exit(3);
		}
	}

	void afiseaza() const
	{
		cout << "Stocul materiilor prime:" << endl;
		for (const auto& materie : stoc)
		{
			cout << materie.getdenumire() << " " << materie.getcantitate() << endl;
		}

		for (const auto& prep : prep)
		{
			cout << "Nume: " << prep.getnume() << endl;
			prep.getreteta().afiseaza();
		}

		cout << "Lista de comenzi:" << endl;
		for (const auto& comanda : comenzi)
		{
			comanda.afiseaza();
		}
	}

	const vector<preparate>& getprep() const
	{
		return prep;
	}
	const vector<materieprima>& getstoc() const
	{
		return stoc;
	}
	void setstoc(const vector<materieprima>& stooc)
	{
		if (stooc.size() <= maxim) {
			stoc = stooc;
		}
		else {
			cout << "Stoc prea mare" << endl;
		}
	}
	void adaugaMateriePrima(const materieprima& materie)
	{
		if (stoc.size() < materieprima::gettotalmat()) {
			stoc.push_back(materie);
		}
		else {
			cout << "Stocul maxim de materii prime a fost atins." << endl;
		}
	}

	const vector<comanda>& getcomenzi() const {
		return comenzi;
	}
	void setcomenzi(const vector<comanda>& comenz)
	{
		if (comenz.size() <= maxim)
		{
			comenzi = comenz;
		}
		else {
			cout << "Numarul de comenzi este prea mare." << endl;
		}
	}
	restaurant() {}
	restaurant(const vector<materieprima>& stooc, const vector<comanda>& comenz)
		: stoc(stooc), comenzi(comenz)
	{
		if (stooc.size() > maxim || comenz.size() > maxim)
		{
			cout << "Numarul maxim de comenzi sau stocul este prea mare." << endl;
		}
	}
	restaurant(restaurant& p) :stoc(p.stoc), comenzi(p.comenzi) {}
	restaurant& operator=(restaurant& p)
	{
		if (this != &p)
		{
			stoc = p.stoc;
			comenzi = p.comenzi;
		}
		return *this;
	}
	friend ostream& operator<<(ostream& out, const restaurant& rest)
	{
		out << "Stoc: " << endl;
		for (const auto& d : rest.stoc)
		{
			out << d << endl;
		}

		out << "Comenzi: " << endl;
		for (const auto& comanda : rest.comenzi)
		{
			out << comanda << endl;
		}

		return out;
	}
	friend istream& operator>>(istream& in, restaurant& rest)
	{
		cout << "Introduceti detaliile pentru stoc:" << endl;
		int nrstoc;;
		cout << "Numar de ingrediente in stoc: ";
		in >> nrstoc;

		rest.stoc.clear();
		for (int i = 0; i < nrstoc; ++i)
		{
			materieprima mat;
			in >> mat;
			rest.stoc.push_back(mat);
		}
		cout << "Introduceti detaliile pentru comenzi:" << endl;
		int nrcomenzi;
		cout << "Numarul de comenzi: ";
		in >> nrcomenzi;

		rest.comenzi.clear();
		for (int i = 0; i < nrcomenzi; ++i)
		{
			comanda comandaaa;
			in >> comandaaa;
			rest.comenzi.push_back(comandaaa);
		}

		return in;
	}
	~restaurant()
	{
		comenzi.clear();
		stoc.clear();
	}
	bool verificaDisponibilitate(const reteta& retetacomanda)
	{
		const auto& ingrediente = retetacomanda.getingrediente();

		for (const auto& ingredient : ingrediente)
		{
			bool disponibil = false;

			for (auto& materie : stoc)
			{
				if (strcmp(materie.getdenumire(), ingredient.first.getdenumire()) == 0)
				{
					if (materie.getcantitate() >= ingredient.second)
					{
						disponibil = true;
						break;
					}
					else
					{
						cout << "Nu exista suficienta cantitate de " << materie.getdenumire() << " in stoc." << endl;
						return false;
					}
				}
			}

			if (!disponibil)
			{
				cout << "Nu exista " << ingredient.first.getdenumire() << " in stoc." << endl;
				return false;
			}
		}
		for (const auto& ingredient : ingrediente)
		{
			for (auto& materie : stoc)
			{
				if (strcmp(materie.getdenumire(), ingredient.first.getdenumire()) == 0)
				{
					materie.setcantitate(materie.getcantitate() - ingredient.second);
					break;
				}
			}
		}

		return true;
	}

	void lanseazaComanda(const comanda& com)
	{
		const vector<preparate>& preparatele = com.getprep();
		for (const auto& preparat : preparatele)
		{
			const reteta& retetacomanda = preparat.getreteta();
			if (verificaDisponibilitate(retetacomanda))
			{
				cout << "Comanda a fost realizata." << endl;
			}
			else
			{
				cout << "Comanda nu poate fi realizata din cauza lipsei de materie prima in stoc." << endl;
			}
		}
	}
};
int main()
{
	materieprima zahar("Zahar", 25);
	materieprima faina("Faina", 25);
	materieprima oua("Oua", 150);
	materieprima ulei("Ulei", 23);
	materieprima carne("Carne", 12);
	materieprima lapte("Lapte", 10);
	materieprima legume("Legume", 35);
	materieprima paste("Paste", 10);
	materieprima sos("Sos", 15);
	materieprima hamburger("Carne hamburger", 12);
	materieprima paine("Paine", 12);
	materieprima insuficient("Rosii", 10);
	reteta insuficienta;
	reteta pastele;
	reteta cioorba;
	reteta reteta1;
	reteta reteta2;
	reteta burger;
	insuficienta.adaugaingredient(insuficient, 15);
	insuficienta.adaugaingredient(oua, 2);
	burger.adaugaingredient(paine, 0.5);
	burger.adaugaingredient(legume, 0.3);
	burger.adaugaingredient(sos, 0.4);
	burger.adaugaingredient(hamburger, 1);
	reteta1.adaugaingredient(zahar, 10);
	reteta1.adaugaingredient(faina, 5);
	reteta2.adaugaingredient(oua, 3);
	reteta2.adaugaingredient(ulei, 10);
	pastele.adaugaingredient(paste, 1);
	pastele.adaugaingredient(sos, 0.5);
	cioorba.adaugaingredient(legume, 1);

	preparate prajitura("Prajitura", reteta1);
	preparate omleta("Omleta", reteta2);
	preparate burg("Burger", burger);
	preparate past("Paste bolo", pastele);
	preparate ciorb("Ciorba", cioorba);
	preparate insufi("Oua cu rosii", insuficienta);//preparat insuficient
	vector<materieprima> stocmaterie = { zahar, faina,oua,ulei,carne,paine,legume,sos,hamburger,paste,sos,insuficient };
	vector<preparate> preparateee = { prajitura, omleta,burg,past,ciorb,insufi };
	vector<comanda> comenzi;
	restaurant rest(stocmaterie, comenzi);
	int numar;
	do {
		cout << "\nMeniu:" << endl;
		cout << "1. Afiseaza detalii restaurant." << endl;
		cout << "2. Adauga o comanda." << endl;
		cout << "3. Iesire." << endl;
		cout << "Alege o optiune: ";
		cin >> numar;

		switch (numar)
		{
		case 1:
			rest.afiseaza();
			break;
		case 2:
		{
			cout << "Preparate disponibile in meniu: " << endl;
			for (size_t i = 0; i < preparateee.size(); ++i)
			{
				cout << i << ". ";
				preparateee[i].afisare();
			}

			cout << "Introduceti indexul preparatului dorit: ";
			int index;
			cin >> index;

			if (index >= 0 && index < preparateee.size())
			{
				const reteta& retetacomanda = preparateee[index].getreteta();
				if (rest.verificaDisponibilitate(retetacomanda))
				{
					comanda com;
					com.adaugapreparat(preparateee[index]);
					rest.adaugacomanda(com);
					cout << "Comanda a fost adaugata cu succes." << endl;

					rest.afiseaza();
				}
				else
				{
					cout << "Comanda nu poate fi adaugata din cauza lipsei de materie prima in stoc." << endl;
				}
			}
			else
			{
				cout << "Indexul selectat nu este valid." << endl;
			}
			break;
		}


		case 3:
			cout << "Iesire" << endl;
			break;
		default:
			cout << "Optiunea nu exista. Alegeti o optiune valida." << endl;
			break;
		}
	} while (numar != 3);
	return 0;
}