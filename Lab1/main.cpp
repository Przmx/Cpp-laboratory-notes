#include <iostream>
#include <vector>
#include <cmath>      // zawiera min. definicję potegowania
#include <algorithm>  // konieczne do użycia algorytmu sortowania
#include <iomanip>    // konieczne do użycia << setprecision <<

using namespace std;

// przekazywanie zmiennej przez referencję

void print_vector_x2_r(vector<int> &wek) {
    for (unsigned i=0; i<wek.size(); i++) {
        wek[i] = 2*wek[i];
        cout << wek[i] << ", ";
    }

    cout << endl;
}

// przekazywanie zmiennej przez stałą referencję

void print_vector_x2_r2(const vector<int> &wek) {
    for (unsigned i=0; i<wek.size(); i++) {
//        wek[i] = 2*wek[i];		błąd: stała referencja uniemożliwia modyfikację zmiennej
        cout << 2*wek[i] << ", ";
    }

    cout << endl;
}

// przekazywanie zmiennej przez wartość

void print_vector_x2_v(vector<int> wek) {
    for (unsigned i=0; i<wek.size(); i++) {
        wek[i] = 2*wek[i];
        cout << wek[i] << ", ";
    }

    cout << endl;
}

int main()
{
    cout << "Moj pierwszy program" << endl;

// deklaracja wektora poprzez podanie wszystkich elementów ****

    vector<string> planety = {"Merkury", "Wenus", "Ziemia", "Mars", "Jowisz", "Saturn", "Uran", "Neptun", "Pluton"};

    cout << "Rozmiar wektora wynosi: " << planety.size() << endl;

// planety.size() jest zmienną int bez znaku (unsigned) natomiast zmienna "i" ma znak - stąd uwaga

    for(int i = 0 ; i < planety.size() ; ++i) {
    cout << planety[i] << endl;
    }

// deklaracja wektora poprzez jawne podanie rozmiaru ****

    vector<int> wektor_1(5);

    for(int i = 0 ; i < 5 ; ++i) {
          wektor_1[i] = pow(2,i+1); // (i+1)^2
          }

    for(int i = 0 ; i < 5 ; ++i) {
    cout << wektor_1[i] << endl;
    }

// deklaracja wektora poprzez jawne podanie rozmiaru oraz wartości ****

        vector<float> wektor_1p(5, sqrt(2.0));   // pięć elementów o wartości = pierwiastek z 2

//    pętla skrócona typu range-based for loop

    for (auto &el : wektor_1)     // el jest referencją do każdego z elementów wektora, auto wykrywa typ zmiennej
            cout << el << endl;

//    wykorzystanie iteratorów

    for (vector<float>::iterator it = wektor_1p.begin(); it != wektor_1p.end(); it++) {
           cout << setprecision(9) << *it << endl;     // ustalamy liczbę miejśc po przecinku na (9-1) = 8
    }

//   bez iteratorów

     for (auto element : wektor_1p)
      cout << setprecision(9) << element << endl;


// deklaracja wektora poprzez zmienną określającą rozmiar ****

    int rozmiar;

    cout << "Podaj rozmiar wektora : ";
    cin >> rozmiar;

    vector<int> wektor_2(rozmiar);

    for(int i = 0 ; i < rozmiar ; ++i) {
          wektor_2[i] = 3*i;
          }

    for(int i = 0 ; i < rozmiar ; ++i) {
    cout << wektor_2[i] << endl;
    }

// deklaracja wektora bez podania rozmiaru ****

    vector<int> wektor_3;

    cout << "Rozmiar wektora 3 wynosi: " << wektor_3.size() << endl;   // rozmiar wektora = 0

    for(int i = 0 ; i < 4 ; ++i) {
          wektor_3.emplace_back(5*(i+1));   //  emplace_back konstruuje i dodaje element na końcu wektora
          }

    for(int i = 0 ; i < wektor_3.size() ; ++i) {
    cout << wektor_3[i] << endl;
    }

// wyszukiwanie elementu wektor_3 = {5,10,15,12}

    auto it = find(wektor_3.begin(), wektor_3.end(), 15);   // szukamy elementu 15

      if (it != wektor_3.end())
        cout << "Element " << *it <<" found at position : " << it - wektor_3.begin() << " (counting from zero)"<< endl;
      else
        cout << "Element not found.";

// kopiowanie wektora

     vector<int> kopia_3 = wektor_3;

     for(int i = 0 ; i < kopia_3.size() ; ++i) {
     cout << kopia_3[i] << endl;
     }

//   przekazanie wektor_1 do funkcji przez wartość

     print_vector_x2_v(wektor_1);

//   przekazanie wektor_1 do funkcji przez referencję

     print_vector_x2_r(wektor_1);

//   przekazanie wektor_1 do funkcji przez stałą referencję

     print_vector_x2_r2(wektor_1);

// wydruk wartości wektor_1 po zadziałaniu funkcji

    for (auto &el : wektor_1)
            cout << el << endl;

// sortowanie wektora

     vector<char> klawiatura = {'q','w','e','r','t','y','u','i','o','p'};

     sort(klawiatura.begin(), klawiatura.end());

         cout << "Posortowane litery \n";
         for (auto x : klawiatura)
             cout << x << ", ";
         cout << "\n";

// przestawianie elementów wektora - swap

// elementy wektora

      vector<int> wektor_4 = {1,2,3,4,5};
      swap(wektor_4[0], wektor_4[4]);

// po wzajemnym przestawieniu elementów  0 i 4

     cout << "wektor = {1,2,3,4,5} po przestawieniu elementow 0 i 4" << endl;

     for (auto &el : wektor_4)
            cout << el << ", ";
     cout << endl;

 // reszta z dzielenia

      int liczba;
      int dzielnik;
      cout << "Podaj liczbe calkowita : ";
      cin >> liczba;
      cout << "Podaj dzielnik : ";
      cin >> dzielnik;
      cout << endl << "Reszta z dzielenia liczby "<< liczba <<
              " przez " << dzielnik << " wynosi : "<< liczba%dzielnik << endl;


    return 0;
}


