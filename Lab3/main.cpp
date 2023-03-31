#include <iostream>
#include <random>
#include <ctime>
#include <algorithm>
#include <iomanip>     // konieczne do użycia << setprecision <<

using namespace std;

bool lessThan(float x, float y) {
    return x < y;
}

bool greaterThan(float x, float y) {
    return x > y;
}

void print(const vector<float> &vector) {
    for (auto number : vector) {
        cout << number << '\n';
    }
   cout  << endl;
}

void print_integer(const vector<int> &vector) {
    for (auto number : vector) {
        cout << number << ", ";
    }
    cout  << endl;
}

bool IsOdd (int i) {
  return ((i%2)==1);
}

// time(0) podaje bieżący czas w sekundach

// Losuje wartości zmiennoprzecinkowe z przedziału 0..1.

float randomFloat01() {
  static default_random_engine e{static_cast<long unsigned int>(time(0))};
  uniform_real_distribution<float> d{0.0f, 1.0f};
  return d(e);
}

// Losuje wartości całkowite z przedziału 0 - 10

float randomInteger() {
  static default_random_engine e{static_cast<long unsigned int>(time(0))};
  uniform_int_distribution<int> d{0,10};
  return d(e);
}

enum class Spozywcze {chleb,mleko,jogurt,czekolada,herbata,kawa};

struct Zakupy {
    Spozywcze typ;
    string nazwa;
    float cena;
    int ile;
};

using Koszyk = vector<Zakupy>;  // deklaracja "using" pozwala na nadanie juz istniejącemu typowi dodatkowej nazwy - aliasu

// przeładowaniem operatora << (operator działa na typach wbudowanych oraz na typach zdefiniowanych przez użytkowwnika)

ostream& operator<<(ostream& out, const Zakupy& produkty){
    float koszt = produkty.cena*produkty.ile;
    return out <<  fixed << right << setprecision(2) << setw(25) <<  produkty.nazwa << setw(4)  << produkty.ile <<" x " <<  setw(6) << produkty.cena <<  " = "  << setw(6) << koszt <<'\n';
}

// *******************************************************************************

// przykład przeładowania operatora dodawania: jak dodawać do siebie wektory

vector<int> operator+(vector<int> a, vector<int> b)
{
vector<int> suma;
for(unsigned i = 0 ; i < a.size() ; ++i) {
    suma.emplace_back(a[i] + b[i]);
    }
return suma;
}

// *******************************************************************************

// wydruk zawartości koszyka

void print(const Koszyk &wek) {
    for (auto &el : wek)
         cout << el ;
    cout << endl ;
   }


// wydruk paragonu z sumaryczną kwotą do zapłaty

void paragon(const Koszyk &wek) {
    cout << "Moj paragon :" << endl;
    print(wek);            // wywolanie funkcji "print" zdefiniowanej wcześniej
    float suma = 0.0;
    for (auto &element : wek)
        suma += element.cena*element.ile;
         cout << fixed << right << setprecision(2) << setw(25) << "Suma do zaplaty" << setw(22) << suma << endl;
         cout << endl ;
    }

void promocja_jogurty(Koszyk wek, float promocja) {   // przekazujemy "wek" przez wartość - promocja nie dokona zmian na stałe
    for (auto &element : wek)
        if (element.typ == Spozywcze::jogurt){
            element.cena *= (1.0 - promocja/100);
        }
    paragon(wek);            // wywolanie funkcji "paragon" zdefiniowanej wcześniej
    }

int zlicz_rodzaje_herbata(const Koszyk &koszyk)
{
    return count_if(
           koszyk.begin(),
           koszyk.end(),
           [](const Zakupy &produkty) { return produkty.typ == Spozywcze::herbata; }
    );
}

int zlicz_herbata(const Koszyk &koszyk)
{   int ile_jest=0;
    for (auto &el : koszyk)
        if (el.typ == Spozywcze::herbata){
          ile_jest += el.ile;
        };
        return ile_jest;
}

int zlicz_produkty(const Koszyk &koszyk)
{   int ile_jest=0;
    for (auto &el : koszyk)
           ile_jest += el.ile;
        return ile_jest;
}


int zlicz_tansze_niz(const Koszyk &koszyk, float limit_ceny)
{   int ile_jest=0;
    for (auto &el : koszyk)
        if (el.cena < limit_ceny){
          ile_jest += el.ile;
        };
        return ile_jest;
}

float koszt_herbata(const Koszyk &koszyk)
{   float ile_kosztuje=0.0;
    for (auto &el : koszyk)
        if (el.typ == Spozywcze::herbata){
          ile_kosztuje += el.ile*el.cena;
        };
        return ile_kosztuje;
}

bool czy_mam_produkt(const Koszyk &koszyk, string produkt)
{
    for (auto &el : koszyk)
        if (el.nazwa == produkt){
          return true;
        };
        return false;
}

int main() {

// zawartość koszyka

    Koszyk koszyk;
    koszyk.emplace_back(Zakupy{Spozywcze::chleb, "Chleb razowy", 5.50, 1}),
    koszyk.emplace_back(Zakupy{Spozywcze::chleb, "Chleb pszenny", 4.40, 1}),
    koszyk.emplace_back(Zakupy{Spozywcze::mleko, "Mleko chude", 4.15, 2}),
    koszyk.emplace_back(Zakupy{Spozywcze::jogurt, "Jogurt naturalny",1.80, 2}),
    koszyk.emplace_back(Zakupy{Spozywcze::jogurt, "Jogurt malinowy",2.45, 3}),
    koszyk.emplace_back(Zakupy{Spozywcze::czekolada, "Czekolada mleczna",4.20, 2}),
    koszyk.emplace_back(Zakupy{Spozywcze::czekolada, "Czekolada gorzka",4.90, 1}),
    koszyk.emplace_back(Zakupy{Spozywcze::herbata, "Herbata zielona", 3.40, 3}),
    koszyk.emplace_back(Zakupy{Spozywcze::herbata, "Herbata owocowa", 3.70, 2}),
    koszyk.emplace_back(Zakupy{Spozywcze::kawa, "Kawa mielona", 19.90, 1}),
    koszyk.emplace_back(Zakupy{Spozywcze::kawa, "Kawa rozpuszczalna", 23.90, 1});

    print(koszyk);

    sort(koszyk.begin(), koszyk.end(),
      [](const Zakupy& produkt1, const Zakupy& produkt2){
         return produkt1.cena < produkt2.cena;
      }
    );

        cout << "Posortowane wg ceny" << endl;

   print(koszyk);

   sort(koszyk.begin(), koszyk.end(),
     [](const Zakupy& produkt1, const Zakupy& produkt2){
        return produkt1.nazwa < produkt2.nazwa;
     }
   );

       cout << "Posortowane wg nazwy" << endl;

  print(koszyk);

  sort(koszyk.begin(), koszyk.end(),
    [](const Zakupy& produkt1, const Zakupy& produkt2){
       return produkt1.cena*produkt1.ile < produkt2.cena*produkt2.ile;
    }
  );

      cout << "Posortowane wg kosztu zakupu" << endl;

 print(koszyk);

// wydruk paragonu

 paragon(koszyk);

cout << "W koszyku jest " << zlicz_rodzaje_herbata(koszyk) << " rodzaje herbaty " << endl;

cout << "W koszyku jest " << zlicz_herbata(koszyk) << " paczek herbaty " << endl;

cout << "Za herbate zaplacono " << koszt_herbata(koszyk) << endl;

cout << "W koszyku mam " << zlicz_produkty(koszyk) << " produktow" << endl;

float limit = 5.0;

cout << "Mam " << zlicz_tansze_niz(koszyk,limit) << " produktow tanszych niz " << limit << endl;

string czy_mam = "Herbata zielona";

if(czy_mam_produkt(koszyk,czy_mam))
{
    cout << "Mam: "<< czy_mam << endl;
}
else
{
    cout << "Nie mam: "<< czy_mam << endl;
}


// paragon po promocji -20% na jogurty

cout << "Promocyjny paragon:" << endl;

promocja_jogurty(koszyk,20);

// a tak było bez promocji

cout << "Paragon bez promocji:" << endl;

 paragon(koszyk);

// ***************************

    const int N = 10;
    vector<float> numbers(N);
    generate(numbers.begin(), numbers.end(), randomFloat01); // Zwróć uwagę na brak nawiasów () po `randomFloat01`.

// algorytm standardowy "sort"

    // 1
    sort(numbers.begin(), numbers.end()); // sortuje w kolejności rosnącej wykorzystując operator <
    print(numbers);
    // 2 - równoważne z 1
    sort(numbers.begin(), numbers.end(), lessThan); // sortuje w kolejności rosnącej wykorzystując predykat - zdefiniowana funkcję (lessThan)
    print(numbers);
    // 3
    sort(numbers.begin(), numbers.end(), [](float x, float y) { return x > y;}); // sortuje malejąco wykorzystując wyrażenie lambda
    print(numbers);
    // 4 - równoważne z 3
    sort(numbers.begin(), numbers.end(), greaterThan); // sortuje malejąco wykorzystując predykat - zdefiniowana funkcję (greaterThan)
    print(numbers);
    // 5 - równoważne z 3 i 4
    auto greaterThan2 = [](float x, float y) { return x > y;};  // def. funkcji analogicznej do greaterThan za pomoca wyrażenia lambda
    sort(numbers.begin(), numbers.end(), greaterThan2);// Sortuje w kolejności malejącej
    print(numbers);


// losowe liczby całkowite

    const int NN = 20;
    vector<int> calkowite(NN);
    generate(calkowite.begin(), calkowite.end(), randomInteger);

    print_integer(calkowite);

    int ile_3 = count(calkowite.begin(), calkowite.end(), 3);
      cout << "zbior zawiera " << ile_3  << " liczb = 3\n";

    int ile_3_l = count_if(calkowite.begin(), calkowite.end(), [](int i) { return i  == 3; });  // wykorzystanie wyrażenia lambda
    cout << "zbior zawiera " << ile_3_l  << " liczb = 3\n";


    // determine how many integers match a target value.

        for (const int target: {3, 7, 9})
        {
            const int num_items = count(calkowite.begin(), calkowite.end(), target);
            cout << "wartosc : " << target << ", liczba wystapien : " << num_items << endl;
        }


    if (any_of(calkowite.begin(), calkowite.end(), [](int i){return i>8;}) )  // wykorzystanie wyrażenia lambda
      cout << "zbior zawiera liczby wieksze od 8.\n";
    else
      cout << "zbior nie zawiera liczb wiekszych od 8\n";


    vector<int>::iterator it = find_if (calkowite.begin(), calkowite.end(), IsOdd);  // wykorzystanie predykatu jednoargumentowego
    cout << "pierwsza nieparzysta wielkoscia jest " << *it << endl;

    int ile_nieparzyste = count_if (calkowite.begin(), calkowite.end(), IsOdd);   // wykorzystanie predykatu jednoargumentowego
    cout << "zbior zawiera " << ile_nieparzyste  << " liczb nieparzystych\n";

    int podzielne_3 = count_if(calkowite.begin(), calkowite.end(), [](int i) { return i % 3 == 0 && i > 0; }); // wykorzystanie wyrażenia lambda
    cout << "zbior zawiera " << podzielne_3 << " liczb podzielnych przez 3" <<endl;

// algorytmy standardowe "for_each" oraz "transform"

// for_each – dla każdego elementu kontenera (np. wektora)  wykonywana jest jakaś operacja, ale samee elementy nie zmieniają się
// transform – na każdym elemencie wykonuje jakąś operację, a jej rezultat wpisuje we wskazane miejsce - możliwe jest nadpisywanie

// transform (InputIterator first1, InputIterator last1, OutputIterator result, UnaryOperator op) - op = funkcja jednoargumentowa lub wyrażenie lambda

    vector <int> vec1(5);
    vector <int> vec2(5);

    vec1 = { 1, 2, 3, 4, 5 };

    transform( vec1.begin(), vec1.end(), vec2.begin(),[](int x){return 3*x;} );   // operator zdefiniowany przez wyrazenie lambda

    for( const auto & x: vec2 )
    {
         cout << x << ' ';
    }
         cout << endl;

// funkcja "rand" - genertor całkowitych liczb pseudolosowych

    for (unsigned i=0; i<10; i++) {
        int liczba  = rand() % 100 + 1;   // liczby z zakresu od 1 do 100
        cout << liczba << ", ";           // wielokrotne uruchomienie programu daje te same ciągi liczb
    }
    cout << endl;

// przykład dodawania wektorów z użyciem przeładowanego operatora "+"

    vector<int> a(3), b(3), c(3);

    a = {3,5,-1};
    b = {-2,4,7};

    c = a + b;    // używamy przeładowanego operatora

    for (auto &el : c)
    {
         cout << el << ", ";
    }
         cout << endl;


}
