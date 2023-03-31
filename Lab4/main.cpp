#include <iostream>
#include <string>
#include <vector>
#include <fstream>     // operacje we/wy na plikach zewnętrznych
#include <sstream>     // operacje we/wy na obiektach klasy string
#include <regex>       // wyrażenia regularne
#include <cmath>       // wywołanie funkcji sin(x)
#include <algorithm>   // algorytmy standardowe min_element, max_element
#include <numeric>     // accumulate

using namespace std;

// definicja krotki - funkcja "statystyka" zwraca trzy wartości

tuple<int, int, double> statystyka(const vector<int>& data)
{
    auto min = *min_element(data.begin(), data.end());
    auto max = *max_element(data.begin(), data.end());
    auto avg = accumulate(data.begin(), data.end(), 0.0) / data.size();  // wartość początkowa sumy  = 0.0

    return tuple<int, int, double>(min, max, avg);
}

// surowe stałe tekstowe - raw string : R"(tekst)"

int main()
{

//  regex_match

  {
   cout << "regex_match" << endl;
   regex re(R"(\d+)");   // wzorzec: co najmniej jedna cyfra
   smatch m;             // zmienna typu smatch przechowuje wynik dopasowania
   string text = "1234";
   cout << regex_match (text, m, re) << " " << m[0] << endl; //zwróci wartość true
   text = "1234m";
   cout <<  regex_match (text, m, re) << " "<< m[0] << endl; //zwróci wartość false
   }

// regex_search

   {
    cout << "regex_search" << endl;
    regex re(R"(\d+)");
    smatch m;
    string text = "1234";
    bool res = regex_search(text, m, re); //zwróci wartość true
    cout << res << " " << m[0] << endl;
    text = "1234m 78910";
    res = regex_search(text, m, re); //zwróci wartość true i zwróci do m pierwszy pasujący podciąg czyli 1234
    cout << res << " " << m[0] <<  endl;
   }

// regex_search all

   {
        cout << endl << "regex_search all" << endl;
        string log(R"(
              Speed: 366
              Mass: 35
              Speed: 378
              Mass: 32
              Speed: 400
              Mass: 30)");
        regex re(R"(Speed:\s(\d+))");  // szukamy tekstu "Speed:" + spacja + grupa cyfr
        smatch sm;
        while (regex_search(log, sm, re)) {
              cout << sm[0] << endl; // podciąg dla którego wzorzec jest w pełni dopasowany
              cout << "Group 1: " << sm[1] << endl << endl; //grupa nr 1 (\d*)

              log = sm.suffix(); // przycięcie napisu do dalszego przeszukania = szukaj dalej a nie od początku
        }
   }

//  regex_iterator

   {
        cout << endl << "regex_iterator" << endl;
        string log(R"(
              Speed: 366
              Mass: 35
              Speed: 378
              Mass: 32
              Speed: 400
              Mass: 30)");
        regex re(R"(Speed:\s(\d+))");
        auto words_begin = sregex_iterator(log.begin(), log.end(), re);
        auto words_end = sregex_iterator();
        cout << "Found " << distance(words_begin, words_end) << " full matches:" << endl;
        for (auto i = words_begin; i != words_end; ++i)
        {
            smatch match = *i;
            cout << match[0] << endl;
            cout << "Group 1: " << match[1] << endl << endl;
        }

    }

  // zadanie 7 - tablice rejestracyjne

    {
            cout << endl << "ex_7" << endl;
            vector<string> lines = {"PO12345", "PO 12345", "PZ973ND", "WE20456", "PGN 2045E", "POZ 40457", "P3 USER"};

            regex re(R"(((PO)|(PZ)) ?[A-Z0-9]{5})");
            // alternative: ((((PO)|(PZ)) ?\w{5}))
            smatch m;

            for (auto &l : lines)
            {
                if(regex_search(l, m, re))
                {
                    cout << m[0] << endl;
                }
            }
    }

// Wczytanie pliku wyraz po wyrazie

    {
//        string filename;
//        cout << "Podaj nazwe pliku wejsciowego: ";  //
//        cin >> filename;

        fstream input_file("filename", ios::in); // plik filename powinien znajdować się w katalogu roboczym
        vector<string> words;
        if (input_file.is_open()) {
              while (!input_file.eof()) {
                    string word;
                    input_file >> word; //wczytuje słowo
                    words.emplace_back(word); //dodaje słowo do kolekcji
              }
        }
        else cout << "File not found" << endl;
    }


// Wczytanie całego pliku do pamięci

    {
        fstream input_file("filename", ios::in);
        if(input_file.is_open()){
              stringstream str_stream;
              str_stream << input_file.rdbuf(); // przepisuje zawartość pliku do strumienia; rdbuf - Pobierz/ustaw bufor strumienia
              string full_text = str_stream.str(); //zapisuje całą zawartość strumienia do string
         }
         else cout << "File not found" << endl;

    }

// Zapisywanie danych do pliku

    {
        fstream output("filename", ios::out);
        if (output.is_open()) {
              for (float x = 0.0; x < 6.3; x += 0.01) {
                    output << x << ";" << sin(x) << endl;  // argument x wyrażony jest w radianach
              }
              output.close();
        }

     }

// pair :  wzorzec struktury o dwóch polach: first i second  (zamiast reprezentacji jako struktura)

    // definicja pary przechowującej nazwę produktu oraz cenę

        // para z wartościami domyślnymi "" i 0:
        pair<string, double> produkt_1;

        // zmiana wartości pary:
        produkt_1 = {"Herbata", 6.50}; // lub
        produkt_1 = make_pair<string,double>("Herbata",6.50);

        // definicja:  para z zainicjowaną dwoma wartościami:
        pair<string, double> produkt_2("Kawa",14.10);

        // lub definicja za pomoca pól first i second
        produkt_2.first = "Kawa";
        produkt_2.second = 14.10;

   // odwołanie się do pól pary

       //odwołanie się do pól first i second
       cout << "Cena " << produkt_1.first << " wynosi " << produkt_1.second << endl;

       //lub z użyciem structured binding od C++17
       auto[produkt, cena] = produkt_2;
       cout << "Produkt: " << produkt << " - cena: " << cena << endl;

// tuple :  krotka - może składać się z liczby pól > 2

       // krotkę możemy użyć np. do zwracania przez funkcję więcej niż jednej wartości

          vector<int> data = { 5, 1, 35, 321, 23, 5, 9, 88, 44, 324 };

          auto stats = statystyka(data);

          cout << "Min: " << get<0>(stats)
               << "; Max: " << get<1>(stats)
               << "; Avg: " << get<2>(stats) << endl;

// mapa - tablica asocjacyjna zawierajaca parę: klucz, wartość zorganizowaną w formie drzewa binarnego (BST)

   // Definiowanie mapy: map<key_type,value_type> container_name;

          map<string, int> word_statistics;

   // Dodawanie elementu do mapy

   // Element dodawany do mapy musi być umieszczony w ściśle określonym miejscu wynikającym z organizacji BST
   // Stąd kontener ten nie posiada metody emplace_back, tylko metodę emplace i metodę try_emplace.

   word_statistics.emplace("the",1);
   // dodaje słowo "the" i przyporządkowaną mu wartość: 1
   // odpowiada to dodaniu pary: make_pair<std:string, int>("the",1)

   // odwołanie się do klucza z wykorzystaniem operatora indeksowania

   word_statistics["the"] = 1;
   // dodaje słowo "the" i przyporządkowaną mu wartość: 1
   // jeśli element istnieje wartość zostanie nadpisana

   // Odczyt wartości przypisanej do danego klucza

   cout << word_statistics["the"]<< endl;
   // zostanie odczytana wartość 1
   cout << word_statistics["computer"]<< endl;
   // element nie istnieje, zostanie utworzony i przypisana zostanie wartość domyślna dla int -> 0

   // Sprawdzanie czy element istnieje

   // metoda "find"

   string word2find = "elephant";
   auto search = word_statistics.find(word2find); // zwraca iterator
   if(search != word_statistics.end()) {
         int val = search->second;  //znaleziona wartość
         cout << val << endl;
   }
   else {
         cout << "Element nie zostal znaleziony" << endl;
   }

   // Iterowanie po mapie: tak jak dla kontenera <vector> przy pomocy iteratorów lub range-based for loop


   for(auto it = word_statistics.begin(); it != word_statistics.end(); it++){ // it jest iteratorem typu: map<string,int>::iterator
         cout<< it->first << " - " << it->second<< endl; // wyświetla klucz i wartość poszczególnych elementów listy
   }

   // lub z wykorzystaniem structure binding i for range loop

   for(const auto &[word, frequency] : word_statistics){ // rzutowanie klucza i wartości elementu na zmienną word (klucz) i frequency (wartość)
         cout<< word << " - " << frequency << endl;
   }

// zadanie końcowe

   cout << endl << "Statystyka wystepowania wyrazow w tekscie" << endl;
   map<string, int> slowa_statystyka;         // mapa zawierająca statystykę występowania wyrazów
   fstream input_file("Textfile.txt", ios::in);  // wczytanie tekstu z pliku - należy wpisać właściwą nazwę
   if(input_file.is_open())
   {
       while (!input_file.eof())
       {
             string word;             // czytanie wyraz po wyrazie
             input_file >> word;

             string w = word;

// Zmodyfikuj program tak, aby używając wyrażeń regularnych wybrać z wczytywanego tekstu tylko słowa,
// usuwając znaki, które nie są literami (np. znaki interpunkcyjne)

// Używając algorytmu std::transform i predykatu std::tolower przed dodaniem słowa do mapy
// zmień wielkość liter tak by w mapie umieszczone były unikalne słowa pisane małymi literami.

             slowa_statystyka[w] += 1;
       }

       for(const auto &[word, frequency] : slowa_statystyka)
       {
             cout<< word << " - " << frequency << endl;
       }
       vector<pair<string,int>> slowa_statystyka_vector;  // definicja wektora zawierającego pary: słowo, liczba wystapień

       copy(slowa_statystyka.begin(), slowa_statystyka.end(), back_inserter(slowa_statystyka_vector));  // skopiowanie danych z mapy do wektora

       sort(slowa_statystyka_vector.begin(), slowa_statystyka_vector.end(),    // sortowanie wg liczby wystąpień
                 [](const pair<string,int> &a, const pair<string,int> &b){
           return a.second > b.second;
       });
       fstream output("word_stats.txt", ios::out);                // utworzenie pliku wyjściowego
       if (output.is_open())
       {
           for(const auto &w : slowa_statystyka_vector)
           {
               output << w.first << " - " << w.second << endl;    // zapis do pliku wyjściowego
           }
           output.close();
       }
   }
   else cout << "File not found" << endl;

   for(const auto &[word, frequency] : slowa_statystyka)
   {
          cout<< word << " - " << frequency << endl;
   }


}
