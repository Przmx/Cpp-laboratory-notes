#include <iostream>
#include <string>
#include <vector>
#include <fstream>     // operacje we/wy na plikach zewnętrznych
#include <sstream>     // operacje we/wy na obiektach klasy string
#include <iomanip>     // konieczne do użycia << setprecision <<

using namespace std;

// definicja struktury, która posłuży do wczytywania pliku csv z kursami walut

struct Exchange_rate
{
    string date;
    double usd;
    double eur;
    string table_id;
};

int main()
{

    string text = "Pan kotek byl chory i lezal w lozeczku i przyszedl kot doktor - jak sie masz koteczku";

    cout << text << endl;    // wydruk ciągu znaków
    int szer = text.size();
    cout << "Dlugosc tekstu = " << szer << endl;  // długość ciągu znaków wraz ze spacjami - całośc ujęta w cudzysłów

    // size_t position = text.find('k');
    // cout << "Pierwsze wystapienie litery k znajduje sie na pozycji " << position << endl;  // liczone od zera

    // position = text.find('k', position + 1); // position + 1 szukamy od kolejnego znaku po pierwszym wystapieniu
    // cout << "Kolejne: " << position << endl;

    size_t position = 0;  // zaczynamy wyszukiwanie od początku


    // zapisujemy wynik wyszukiwania w zmiennej position, rozpoczynamy wyszukiwanie od znaku
    // następującego po poprzedniej wartości position
    while ((position = text.find('k', position + 1)) != string::npos) {
        // wyszukujemy tak długo, jak find() zwraca wartości różne od npos
        cout << "Trafienie: " << position << endl;
    }

   // przykłady innych operacji na zmiennej "string"
   
   // podział na poszczególne słowa

                  string slowo;
                  stringstream strumien_wejsciowy(text);    // tworzymy striumień wejściowy którego żródłem jest zmienna text
                  while (getline(strumien_wejsciowy, slowo, ' ')) {  // wczytuje poszczegolne slowa - separatorem jest spacja
                      cout << slowo << endl;
                  }   

   // metoda susbstr zwraca fragment oryginalnego tekstu, zgodnie z przekazanymi wartościami - indeksem początku fragmentu, oraz, opcjonalnie - jego długością

    string text2 = text.substr(14); // "chory" - od pozycji 14 do końca
    cout << text2 << endl;

    string text3 = text.substr(4, 5); // "kotek" - od pozycji 4, 5 znaków
    cout << text3 << endl;

   // dodawanie

   string text2p = text.substr(14,6);  // "chory "

   string text2p3 = text2p + text3;

   cout << text2p3 << endl;  // "chory kotek"

   // znajdowanie pozycji ciągu znaków

    size_t position_of_kot = text.find("kot"); // 4
    cout << "Pierwsze wystapienie ciagu znakow <<kot>> na pozycji " << position_of_kot << endl;

    string text4 = text.substr(position_of_kot); // od początku wyrazu "kot" do końca
    cout << text4 << endl;
	
   // zamiana fragmentu tekstu

      text.replace(4,5,"lew");  // od pozycji 4 zamieniamy 5 znaków ("kotek") na "lew" 

      cout << text << endl;    // zmieniony tekst  "Pan lew był chory ... "
	

   //  find_first_of poszukiwanie pierwszego znaku, który pasuje do któregokolwiek ze znaków określonych w argumentach

      size_t found = text.find_first_of("aeiouy");    // wyszukuje pierwszą samogłoskę
      while (found!=string::npos)
      {
        text[found]='*';                            // znalezione samogloski zastepuje gwiazdką
        found=text.find_first_of("aeiouy",found+1);  // wyszukuje kolejne samogłoski
      }

      cout << text << '\n';    // wydruk zmienionego tekstu

   // operacja swap - zamiana ciągów znaków - ich długości mogą być różne

        string buyer ("money");
        string seller ("product");

        cout << "Before the swap, buyer has " << buyer;
        cout << " and seller has " << seller << '\n';

        seller.swap (buyer);

        cout << "After the swap, buyer has " << buyer;
        cout << " and seller has " << seller << '\n';

   // porównywanie ciągów lub ich fragmentów: string::compare

          string str1 ("green apple");
          string str2 ("red apple");
		  
        // 	funkcja compare porównuje alfabetycznie ciągi znaków i może przyjmować następujące wartości:
        //  < 0, gdy nasz string według kolejnoœci alfabetycznej umiejscawia się przed stringiem wysłanym jako argument		
		//  > 0, gdy nasz string według kolejnoœci alfabetycznej umiejscawia się po stringu przysłanym jako argument
		//  = 0, oba ciągi sa umieszczone alafabetycznie w tym samym miejscu co oznacza że są identyczne

          if (str1.compare(str2) != 0)                    // porównuje całe ciągi
            cout << str1 << " is not " << str2 << '\n';

          if (str1.compare(6,5,"apple") == 0)   // 6,5  = fragment str1 od pozycji 6 liczący 5 znaków
            cout << "still, " << str1 << " is an apple\n";

          if (str2.compare(str2.size()-5,5,"apple") == 0) // fragment str2 liczący 5 znaków
            cout << "and " << str2 << " is also an apple\n";

          if (str1.compare(6,5,str2,4,5) == 0) // fragment str1 od pozycji 6 liczący 5 znaków i fragment str1 od pozycji 4 liczący 5 znaków
            cout << "therefore, both are apples\n";

  // przykład wczytywania pliku csv
  
  // wykomentowane fragmenty są rozszerzeniem oryginalnego kodu z instrukcji lab 3

    fstream file("kursy_usd_eur.csv", fstream::in);   // określenie nazwy pliku wejściowego; powinien być w katalogu roboczym
//    fstream output("kursy_usd_eur.txt", fstream::out);  // określenie nazwy pliku wyjściowego
    vector<Exchange_rate> rates;
//    int numlin = 0;    // inicjalizacja licznika liczby wczytanych linii
//    double ratio = 0.0;  // inicjalizacja wartości relacji kursów EUR / USD

    if (file.is_open()) {
        string line;
        getline(file, line); // wczytuje pierwszą linię z nagłówkiem i ją ignoruje
        while (getline(file, line)) {//wczytuje kolejne linie aż do końca pliku

//            numlin++;  // inkrementacja licznika po wczytaniu kolejnej linii

            stringstream str(line);//tworzy strumień, którego źródłem jest wczytana linia
			
            Exchange_rate er;
            getline(str, er.date, ','); //wczytuje date (pierwszy element wiersza); separatorem jest przecinek
            string double_str;
            getline(str, double_str, ',');  // wczytuje kurs USD (jako tekst)
            er.usd = stod(double_str);      //zamiana string->double
            getline(str, double_str, ',');  // wczytuje kurs EUR (jako tekst)
            er.eur = stod(double_str);      //zamiana string->double
            getline(str, er.table_id, ','); // wczytuje ostatnią kolumnę z numerem tabeli NBP
            rates.emplace_back(er); //dodaje element do kolekcji

//            ratio = er.eur/er.usd;

//          output <<  numlin << "," << er.date << "," << er.usd << "," << er.eur << "," << ratio << endl;

//            // setw(n) - zapisuje wartość za pomocą n znaków
//            // fixed - liczby zmiennoprzecinkowe zapisuje z taką samą liczbą miejsc po przecinku - nie obcina zer na końcu

 //       output << setw(4) << fixed << setprecision(6) << numlin << setw(10) << er.date << setw(12) << er.usd << setw(12) <<er.eur << setw(12) <<ratio << endl;

        }
 //       cout << "wczytano " << numlin << " linii" << endl;
 //       output.close ();  // zamknięcie pliku wyjściowego
    }
	
//     else cout << "File not found "<< endl;	

}
