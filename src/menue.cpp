
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        menue.cpp
// BESCHREIBUNG: Implementierung der grafischen Benutzeroberfläche
//               Enthält die Logik für Menü-Strukturen,
//               ASCII-Banner und interaktive Benutzerabfragen
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#include "menue.h"
using namespace std;

//===========================================================================================
//Gobale Variablen
//===========================================================================================
//da diese "Werte/Zeichen" in vielen Funktionen benötigt werden diese einmalig (gobal) definiert
int breite_des_Kasten = 50;
string Abstand = "      "; //Einrückung innerhalb des Rahmens
string Randabstand = "\t"; //Einrückung vom Bildschirmrand
string Regelabstand = "  ";//Einrückung von der Nummerierung der Regeln 1.,2. 



void zeige_Begruessung() {
    string randabstand = "\t                        ";
    cout << endl << endl;
    cout << randabstand << " #   #   ###    ####  #   #  ### " << endl;
    cout << randabstand << " #   #  #   #  #      #   #   #  " << endl;
    cout << randabstand << " #####  #####   ###   #####   #  " << endl;
    cout << randabstand << " #   #  #   #      #  #   #   #  " << endl;
    cout << randabstand << " #   #  #   #  ####   #   #  ### " << endl << endl;
    cout << randabstand << "---- JAPANISCHES LOGIKRAETSEL ---" << endl << endl;

    //damit Spieler es lesen kann muss eine TAste gedrückt werden
    cout << randabstand << " Druecken Sie Enter zum Starten...";
    getchar();//durch getchar() wird auf das nächste Zeichen gewartet --> auch die Enter welche zuvor schon gedrückt worden sind werden so genommen --> da in erlaubten Code keine Lösung zur Löschung des Eingabespeichers ist; Rückgabewert wird ignoriert
}

void zeige_Hauptmenue() {
    //diese Funktion gibt Zeile für Zeile das Menü aus

    //festgelegte Bestandteile welche überall gleich aussehen und so die Nutzung vereinfacht wird
    string abstand = "      "; //Einrückung innerhalb des Rahmens
    string randabstand = "\t                   "; //Einrückung vom Bildschirmrand

    //Obere Begrenzung
    cout << randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < 40; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    //Titel
    cout << randabstand << (unsigned char)186 << "            H A U P T M E N U E         " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 1: Regeln ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 1 " << (unsigned char)179 << "  Regeln                     " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 2: Testspiel ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 2 " << (unsigned char)179 << "  Testspiel                  " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 3: Solo-Modus ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 3 " << (unsigned char)179 << "  Solo-Modus                 " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 4: Computer-Duell ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 4 " << (unsigned char)179 << "  KI-Duell                   " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 5: Beenden ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 5 " << (unsigned char)179 << "  Beenden                    " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;


    //Untere Begrenzung
    cout << randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < 40; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)188 << endl;//Rechte Ecke


    cout << randabstand << " Deine Wahl: ";
}

void zeichne_erste_Regel() {


    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //diese Funktion ist dafür da, dass in den Kästen nur Inhalte für die erste Regel angezeigt werden



    //===========================================================================================
    // 1. Inhalte in der Ausgabe werden gelöscht
    //===========================================================================================
    //mit system ("cls") sieht es so aus als ob Bildschirm aktualisiert werden würde

    system("cls");

    //===========================================================================================
    // 2. Ausgabe
    //===========================================================================================
    //Zeile für Zeile wird ausgegeben
    //dabei wird aber nur der TExt der ersten Regel
    //--> in nächster Funktion wird dann auch Regel zwei ausgegeben


    //-------------------------------------------------------------------------------------------
    // 2a) Ausgabe des Titels
    //-------------------------------------------------------------------------------------------
    zeichne_Ueberschrift();


    //-------------------------------------------------------------------------------------------
    // 2b) Ausgabe der einzelnen Zeilen
    //-------------------------------------------------------------------------------------------

    //------------------------0. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187;//Rechte Ecke

    //rechter Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke


    //------------------------1. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //Rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------2. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    cout << "=======================REGELN=====================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------3. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                         2                  " << (unsigned char)186 << endl;


    //------------------------4. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "1.  Zu Beginn siehst du nur Inseln (Zahlen)     ";

    cout << (unsigned char)186 << Randabstand << (unsigned char)186;


    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;



    //------------------------5. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "--> Zahl zeigt an wie viele Bruecken insgesamt  ";

    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen


    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------6. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "    von dieser Insel abgehen                    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------7. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                  2                         1     " << (unsigned char)186 << endl;


    //ab hier wird linker Kasten leer ausgeben da ab der nachfolgenden Zeile Regel 2 dran wäre!!


    //------------------------8. Zeile & 9. Zeile & 10. Zeile------------------------
    //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        //linker Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }


    //------------------------11. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                                            " << (unsigned char)186 << endl;


    //------------------------12. Zeile & 13. Zeile & 14. Zeile------------------------
    //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        //linker Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }

    //------------------------15. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                               1                  " << (unsigned char)186 << endl;


    //------------------------16. Zeile & 17. Zeile & 18. Zeile------------------------
        //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        //linker Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten
        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }


    //------------------------19. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     3            6                         3     " << (unsigned char)186 << endl;

    //------------------------20. Zeile & 21. Zeile & 22. Zeile------------------------
        //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        //linker Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }

    ////------------------------23. Zeile------------------------
    cout << Randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << Randabstand << (unsigned char)200;
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << endl;

}

void zeichne_zweite_Regel() {


    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //diese Funktion ist dafür da, dass in den Kästen nur Inhalte bis zur zweiten Regel angezeigt werden



    //===========================================================================================
    // 1. Inhalte in der Ausgabe werden gelöscht
    //===========================================================================================
    //mit system ("cls") sieht es so aus als ob Bildschirm aktualisiert werden würde

    system("cls");

    //===========================================================================================
    // 2. Ausgabe
    //===========================================================================================
    //Zeile für Zeile wird ausgegeben
    //dabei wird aber nur der TExt der ersten & zweiten Regel ausgegeben
    //--> in nächster Funktion wird dann auch Regel drei ausgegeben


    //-------------------------------------------------------------------------------------------
    // 2a) Ausgabe des Titels
    //-------------------------------------------------------------------------------------------
    zeichne_Ueberschrift();


    //-------------------------------------------------------------------------------------------
    // 2b) Ausgabe der einzelnen Zeilen
    //-------------------------------------------------------------------------------------------

    //------------------------0. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187;//Rechte Ecke

    //rechter Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke


    //------------------------1. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten
    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------2. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    cout << "=======================REGELN=====================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------3. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                         2                  " << (unsigned char)186 << endl;


    //------------------------4. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "1.  Zu Beginn siehst du nur Inseln (Zahlen)     ";

    cout << (unsigned char)186 << Randabstand << (unsigned char)186;


    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;



    //------------------------5. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "--> Zahl zeigt an wie viele Bruecken insgesamt  ";

    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen


    //rechter Kasten    
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------6. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "    von dieser Insel abgehen                    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;

    //------------------------7. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                  2-------------------------1     " << (unsigned char)186 << endl;


    //------------------------8. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "2. Bruecken duerfen nur waagerecht oder senk-   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------9. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   recht verlaufen                              ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------10. Zeile------------------------
    //Leerzeile
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //ab hier wird linker Kasten leer ausgeben da ab der nachfolgenden Zeile Regel 3 dran wäre!!


    //------------------------11. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                                            " << (unsigned char)186 << endl;


    //------------------------12. Zeile & 13. Zeile & 14. Zeile------------------------
    for (int i = 0; i < 3; i++) {
        //Leerzeile bei linken Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "     |                                            " << (unsigned char)186 << endl;
    }


    //------------------------15. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |                         1                  " << (unsigned char)186 << endl;


    //------------------------16. Zeile & 17. Zeile & 18. Zeile------------------------
    for (int i = 0; i < 3; i++) {
        //Leerzeile bei linken Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "     |                                            " << (unsigned char)186 << endl;
    }


    //------------------------19. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     3            6                         3     " << (unsigned char)186 << endl;


    //------------------------20. Zeile & 21. Zeile & 22. Zeile------------------------
        //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        //linker Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }

    //------------------------23. Zeile------------------------
    cout << Randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << Randabstand << (unsigned char)200;
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << endl;
}

void zeichne_dritte_Regel() {


    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //diese Funktion ist dafür da, dass in den Kästen nur Inhalte bis zur dritten Regel angezeigt werden



    //===========================================================================================
    // 1. Inhalte in der Ausgabe werden gelöscht
    //===========================================================================================
    //mit system ("cls") sieht es so aus als ob Bildschirm aktualisiert werden würde

    system("cls");

    //===========================================================================================
    // 2. Ausgabe
    //===========================================================================================
    //Zeile für Zeile wird ausgegeben
    //dabei wird aber nur der TExt der ersten & zweiten & dritten Regel ausgegeben
    //--> in nächster Funktion wird dann auch Regel vier ausgegeben


    //-------------------------------------------------------------------------------------------
    // 2a) Ausgabe des Titels
    //-------------------------------------------------------------------------------------------
    zeichne_Ueberschrift();


    //-------------------------------------------------------------------------------------------
    // 2b) Ausgabe der einzelnen Zeilen
    //-------------------------------------------------------------------------------------------

    //------------------------0. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187;//Rechte Ecke

    //rechter Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke


    //------------------------1. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten
    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------2. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    cout << "=======================REGELN=====================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------3. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  ";//Randstreifen linke Seite
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                         2                  " << (unsigned char)186 << endl;


    //------------------------4. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "1.  Zu Beginn siehst du nur Inseln (Zahlen)     ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Randstreifen + Leerzeichen


    //------------------------5. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "--> Zahl zeigt an wie viele Bruecken insgesamt  ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen


    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl; //Randstreifen + Leerzeichen


    //------------------------6. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "    von dieser Insel abgehen                    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;//Leerzeichen + Randstreifen

    //------------------------7. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                  2-------------------------1     " << (unsigned char)186 << endl;


    //------------------------8. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "2. Bruecken duerfen nur waagerecht oder senk-   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                  " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;



    //------------------------9. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   recht verlaufen                              ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                  " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;


    //------------------------10. Zeile------------------------
    // Leerzeile bei linkem Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten
    //rechter Kasten
    cout << "                  " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;


    //------------------------11. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "3. Erlaubt sind einfache oder doppelte Bruecken ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2            " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;


    //ab hier wird linker Kasten leer ausgeben da ab der nachfolgenden Zeile Regel 4 dran wäre!!

    //------------------------12. Zeile & 13. Zeile & 14. Zeile------------------------
    for (int i = 0; i < 3; i++) {
        //Leerzeile bei linken Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "     |            " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;
    }


    //------------------------15. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            1                  " << (unsigned char)186 << endl;


    //------------------------16. Zeile & 17. Zeile & 18. Zeile------------------------
    for (int i = 0; i < 3; i++) {
        //Leerzeile bei linken Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "     |            " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;
    }


    //------------------------19. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     3            6=========================3     " << (unsigned char)186 << endl;


    //------------------------20. Zeile & 21. Zeile & 22. Zeile------------------------
        //3 Leerzeilen  --> nur Randbegrenzung
    for (int i = 0; i < 3; i++) {
        cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten
        cout << "                                                  " << (unsigned char)186 << endl; //Randstreifen + Leerzeichen
    }

    //------------------------23. Zeile------------------------
    cout << Randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << Randabstand << (unsigned char)200;
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << endl;
}

void zeichne_vierte_Regel() {


    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //diese Funktion ist dafür da, dass in den Kästen nur Inhalte bis zur 4 Regel angezeigt werden



    //===========================================================================================
    // 1. Inhalte in der Ausgabe werden gelöscht
    //===========================================================================================
    //mit system ("cls") sieht es so aus als ob Bildschirm aktualisiert werden würde

    system("cls");

    //===========================================================================================
    // 2. Ausgabe
    //===========================================================================================
    //Zeile für Zeile wird ausgegeben
    //dabei wird aber nur der TExt der ersten & zweiten & dritten & vierten Regel ausgegeben
    //--> in nächster Funktion wird dann auch Regel 5 ausgegeben


    //-------------------------------------------------------------------------------------------
    // 2a) Ausgabe des Titels
    //-------------------------------------------------------------------------------------------
    zeichne_Ueberschrift();


    //-------------------------------------------------------------------------------------------
    // 2b) Ausgabe der einzelnen Zeilen
    //-------------------------------------------------------------------------------------------

    //------------------------0. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187;//Rechte Ecke

    //rechter Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke


    //------------------------1. Zeile------------------------
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten
    cout << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------2. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    cout << "=======================REGELN=====================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------3. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                         2                  " << (unsigned char)186 << endl;


    //------------------------4. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "1.  Zu Beginn siehst du nur Inseln (Zahlen)     ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;



    //------------------------5. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "--> Zahl zeigt an wie viele Bruecken insgesamt  ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;


    //------------------------6. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "    von dieser Insel abgehen                    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;;

    //------------------------7. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                  2------------|------------1     " << (unsigned char)186 << endl;


    //------------------------8. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "2. Bruecken duerfen nur waagerecht oder senk-   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;



    //------------------------9. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   recht verlaufen                              ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;

    //------------------------10. Zeile------------------------
    // Leerzeile bei linkem Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten
    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;



    //------------------------11. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "3. Erlaubt sind einfache oder doppelte Bruecken ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2                         |                  " << (unsigned char)186 << endl;

    //------------------------12. Zeile------------------------
    //Leerzeile bei linken Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;

    //------------------------13. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "4. Bruecken duerfen sich NIEMALS kreuzen oder   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;


    //------------------------14. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   andere Inseln schneiden/passieren            ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                               |                  " << (unsigned char)186 << endl;


    //------------------------15. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                               1                  " << (unsigned char)186 << endl;



    //ab hier wird linker Kasten leer ausgeben da ab der nachfolgenden Zeile Regel 5 dran wäre!!


//------------------------16. Zeile & 17. Zeile------------------------
    for (int i = 0; i < 2; i++) {
        //Leerzeile bei linken Kasten
        cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
        cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

        //rechter Kasten
        cout << "                                                  " << (unsigned char)186 << endl;
    }


    //------------------------18. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    // Nachfolgend wird im Spielfeld das Wort Fehler ausgegeben sodass der Nutzer direkt erkennt dass das GAme so nicht gelöst werden kann
    //cout << "     |            " << (unsigned char)186 << "                               " << (unsigned char)186 << endl;
    cout << "        ##### ##### #   # #     ##### ####        " << (unsigned char)186 << endl;

    //------------------------19. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    //falls das originale Spielfeld (alle Inseln) angezeigt werden sollte kann bei nachfolgender Zeile // entfernt werden
    //cout << "     3            6=========================3     " << (unsigned char)186 << endl;
    cout << "        #     #     #   # #     #     #   #       " << (unsigned char)186 << endl;

    //------------------------20. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    //falls das originale Spielfeld (alle Inseln) angezeigt werden sollte kann bei nachfolgender Zeile // entfernt werden
    //cout << "                                                  " << (unsigned char)186 << endl;
    cout << "        ####  ####  ##### #     ####  ####        " << (unsigned char)186 << endl;

    //------------------------21. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    //falls das originale Spielfeld (alle Inseln) angezeigt werden sollte kann bei nachfolgender Zeile // entfernt werden
    //cout << "                                                  " << (unsigned char)186 << endl;
    cout << "        #     #     #   # #     #     #  #        " << (unsigned char)186 << endl;

    //------------------------22. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "        #     ##### #   # ##### ##### #   #       " << (unsigned char)186 << endl;


    //------------------------23. Zeile------------------------
    cout << Randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << Randabstand << (unsigned char)200;
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << endl;
}

void zeichne_fuenfte_Regel() {


    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //diese Funktion ist dafür da, dass in den Kästen nur Inhalte bis zur 5. Regel/Ziel angezeigt werden



    //===========================================================================================
    // 1. Inhalte in der Ausgabe werden gelöscht
    //===========================================================================================
    //mit system ("cls") sieht es so aus als ob Bildschirm aktualisiert werden würde

    system("cls");

    //===========================================================================================
    // 2. Ausgabe
    //===========================================================================================
    //Zeile für Zeile wird ausgegeben
    //dabei wird aber nur der TExt der ersten & zweiten & dritten & vierten Regel & Ziel 


    //-------------------------------------------------------------------------------------------
    // 2a) Ausgabe des Titels
    //-------------------------------------------------------------------------------------------
    cout << endl;
    cout << "                            #   #   ###    ####  #   #  ###     ####  #   #  ###  ####   #####" << endl;
    cout << "                            #   #  #   #  #      #   #   #     #      #   #   #   #   #  #" << endl;
    cout << "                            #####  #####   ###   #####   #     #  ##  #   #   #   #   #  ####" << endl;
    cout << "                            #   #  #   #      #  #   #   #     #   #  #   #   #   #   #  #" << endl;
    cout << "                            #   #  #   #  ####   #   #  ###     ####   ###   ###  ####   #####" << endl;
    cout << endl;



    //-------------------------------------------------------------------------------------------
    // 2b) Ausgabe der einzelnen Zeilen
    //-------------------------------------------------------------------------------------------

    //------------------------0. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187;//Rechte Ecke

    //rechter Kasten
    cout << Randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke


    //------------------------1. Zeile------------------------
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten
    cout << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------2. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    cout << "=======================REGELN=====================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << endl;//Randstreifen ganz rechts + Zeilensprung


    //------------------------3. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2-------------------------2                  " << (unsigned char)186 << endl;



    //------------------------4. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "1.  Zu Beginn siehst du nur Inseln (Zahlen)     ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "     |                         |                  " << (unsigned char)186 << endl;



    //------------------------5. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "--> Zahl zeigt an wie viele Bruecken insgesamt  ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "     |                         |                  " << (unsigned char)186 << endl;


    //------------------------6. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "    von dieser Insel abgehen                    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //zwischenstück zwischen Kästen

    //rechter Kasten
    cout << "     |                         |                  " << (unsigned char)186 << endl;

    //------------------------7. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;//Randstreifen linke Seite
    for (int i = 0; i < breite_des_Kasten; i++) {//Leerzeichen zwischen den Randstreifen
        cout << " ";
    }
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            2            |            1     " << (unsigned char)186 << endl;


    //------------------------8. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "2. Bruecken duerfen nur waagerecht oder senk-   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;



    //------------------------9. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   recht verlaufen                              ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186;

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;

    //------------------------10. Zeile------------------------
    // Leerzeile bei linkem Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten
    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;


    //------------------------11. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "3. Erlaubt sind einfache oder doppelte Bruecken ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     2            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;


    //------------------------12. Zeile------------------------
    //Leerzeile bei linken Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;


    //------------------------13. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "4. Bruecken duerfen sich NIEMALS kreuzen oder   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;


    //------------------------14. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << "   andere Inseln schneiden/passieren            ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            |            |     " << (unsigned char)186 << endl;


    //------------------------15. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "            1            |     " << (unsigned char)186 << endl;

    //------------------------16. Zeile------------------------

    //Leerzeile bei linken Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "                         |     " << (unsigned char)186 << endl;



    //------------------------17. Zeile------------------------
    //Linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << "==================ZIEL DES SPIELS=================";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "     |            " << (unsigned char)186 << "                         |     " << (unsigned char)186 << endl;


    //------------------------18. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    //cout << "     3============6=========================3     " << (unsigned char)186 << endl;
    cout << "     |            " << (unsigned char)186 << "                         |     " << (unsigned char)186 << endl;


    //------------------------19. Zeile------------------------
    //linker Kasten
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << " Verbinde alle Inseln so, dass jede Insel mit   ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    //cout << "                                                  " << (unsigned char)186 << endl;
    cout << "     3============6=========================3     " << (unsigned char)186 << endl;


    //------------------------20. Zeile------------------------
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << " der passenden Anzahl Bruecken verbunden ist    ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;

    //------------------------21. Zeile------------------------
    cout << Randabstand << (unsigned char)186;
    cout << Regelabstand << " und ein zusammenhaengendes Netzwerk entsteht!! ";
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger Rándstreifen für rechten Kasten

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------16. Zeile-----------------------
    //Leerzeile bei linken Kasten
    cout << Randabstand << (unsigned char)186 << "                                                  "; //Randstreifen + Leerzeichen
    cout << (unsigned char)186 << Randabstand << (unsigned char)186; //mittiger Randstreifen für linken Kasten dann Abstand dann mittiger RAndstreifen für rechten Kasten

    //rechter Kasten
    cout << "                                                  " << (unsigned char)186 << endl;


    //------------------------23. Zeile------------------------
    cout << Randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << Randabstand << (unsigned char)200;
    for (int i = 0; i < breite_des_Kasten; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken
    }
    cout << (unsigned char)188 << endl;



}

void zeichne_Tutorial_Menue() {
    //===========================================================================================
    //Aufgabe dieser Methode
    //===========================================================================================
    //diese Methode ist dafür zuständig dass das Untermenü angezeigt werden kann
    //es basiert auf dem Prinzip des Hauptmenüs

    //festgelegte Bestandteile welche überall gleich aussehen und so die Nutzung vereinfacht wird
    string abstand = "      "; //Einrückung innerhalb des Rahmens
    string randabstand = "\t                   "; //Einrückung vom Bildschirmrand


    system("cls"); // Bildschirm leeren für saubere Optik

    //Obere Begrenzung
    cout << randabstand << (unsigned char)201; //linke Ecke
    for (int i = 0; i < 40; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)187 << endl;//Rechte Ecke

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    //Titel
    cout << randabstand << (unsigned char)186 << "    H A S H I - G U I D E - M E N U E   " << (unsigned char)186 << endl;

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 1: Nochmal ansehen ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 1 " << (unsigned char)179 << " Tutorial nochmal ansehen    " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 2: Testspiel starten ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 2 " << (unsigned char)179 << " Testspiel starten           " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    // --- PUNKT 3: Hauptmenü ---
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 3 " << (unsigned char)179 << " Hauptmenue                  " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;

    //Leerzeile
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    //Untere Begrenzung
    cout << randabstand << (unsigned char)200; //linke Ecke
    for (int i = 0; i < 40; i++) {
        cout << (unsigned char)205; //Linie zwischen den Ecken wird 40 mal ausgegeben
    }
    cout << (unsigned char)188 << endl;//Rechte Ecke

    cout << randabstand << " Deine Wahl: ";
}

void zeichne_Ueberschrift() {
    cout << endl;
    cout << "                            #   #   ###    ####  #   #  ###     ####  #   #  ###  ####   #####" << endl;
    cout << "                            #   #  #   #  #      #   #   #     #      #   #   #   #   #  #" << endl;
    cout << "                            #####  #####   ###   #####   #     #  ##  #   #   #   #   #  ####" << endl;
    cout << "                            #   #  #   #      #  #   #   #     #   #  #   #   #   #   #  #" << endl;
    cout << "                            #   #  #   #  ####   #   #  ###     ####   ###   ###  ####   #####" << endl;
    cout << endl;

}

string erfrage_Name() {

    string name;
    string randabstand = "\t                   ";

    system("cls");
    cout << randabstand << (unsigned char)201;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)187 << endl;

    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "          SPIELERANMELDUNG              " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "  Bitte gib deinen Namen ein:           " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)200;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)188 << endl;

    cout << "\n" << randabstand << "Name: ";
    getline(cin, name);//so könnte auch ein Namen mit Leerzeichen eingegeben werden

    //der abgefragte Name wird genutzt um in die Log DAtei zu schreiben und die Anzahl der züge wird ausgegeben
    //bei der Ausgabe der Züge ist die Breite begrenzt --> der gesamte Name kann nur insgesamt 18 Zeichen haben --> falls er das übersteigt wird er abgeschnitten

    if (name.length() > 18) { //wenn der Name länger als 18 Zeichen ist
        name.erase(15, name.length()); //ab Zeichen 15 werden alle zeichen bis zum Ende gelöscht
        name = name + "...";//dann werden drei Punkte "addiert" --> insgesamt 18 Zeichen
    }


    return name;//eingegebener Name wird zurückgegeben --> wird für Spielstart gebraucht
}

int erfrage_Schwierigkeit() {
    string abstand = "      ";
    string randabstand = "\t                   ";
    char wahl_char;
    int wahl_int = 0;

    system("cls");

    do {//do while schleife sodass der Nutzer so lange in der Schleife bleibt bis die Eingabe richtig ist

        system("cls");

        // Obere Begrenzung
        cout << randabstand << (unsigned char)201;
        for (int i = 0; i < 40; i++) cout << (unsigned char)205;
        cout << (unsigned char)187 << endl;

        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "          SCHWIERIGKEITSGRAD            " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Leicht
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 1 " << (unsigned char)179 << " Leicht                      " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Mittel
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 2 " << (unsigned char)179 << " Mittel                      " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Schwer
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 3 " << (unsigned char)179 << " Schwer                      " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;

        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)200;
        for (int i = 0; i < 40; i++) cout << (unsigned char)205;
        cout << (unsigned char)188 << endl;

        cout << "\n" << randabstand << "Schwierigkeitsgrad: ";
        wahl_char = lese_einzelnes_Zeichen(); //durch diese Funktion können mehrere Zeichen eingegeben werden es wird aber nur das erste Zeichen beachtet
        
        //da Zeichen in char vorliegt aber in int benötigt wird --> Umwandlung von Zeichen in Zahl
        // '1' hat ASCII-Wert 49, '0' hat 48 --> 49 - 48 = 1
        wahl_int = wahl_char - '0';


    } while ((wahl_int != 1) && (wahl_int != 2) && (wahl_int != 3));

    return wahl_int;
}

int erfrage_Spielfeldgroesse() {
    string abstand = "      ";
    string randabstand = "\t                   ";
    char wahl;
    int gewaehltes_Format;

    do {//do while schleife sodass der Nutzer so lange in der Schleife bleibt bis die Eingabe richtig ist

        system("cls");
        // Obere Begrenzung
        cout << randabstand << (unsigned char)201;
        for (int i = 0; i < 40; i++) cout << (unsigned char)205;
        cout << (unsigned char)187 << endl;

        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "           SPIELFELDGROESSE             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Option 1
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 1 " << (unsigned char)179 << " Klein (8x8)                 " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Option 2
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 2 " << (unsigned char)179 << " Mittel (9x9)                " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

        // Option 3
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)218 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)191 << "                             " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)179 << " 3 " << (unsigned char)179 << " Gross (10x10)               " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)186 << abstand << (unsigned char)192 << (unsigned char)196 << (unsigned char)196 << (unsigned char)196 << (unsigned char)217 << "                             " << (unsigned char)186 << endl;

        // Untere Begrenzung
        cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
        cout << randabstand << (unsigned char)200;
        for (int i = 0; i < 40; i++) cout << (unsigned char)205;
        cout << (unsigned char)188 << endl;

        cout << "\n" << randabstand << "Spielfeldgroesse: ";
        wahl = lese_einzelnes_Zeichen();
    } while ((wahl != '1') && (wahl != '2') && (wahl != '3'));

    switch (wahl) {
    case '1':
        gewaehltes_Format = 19;
        break;
    case '2':
        gewaehltes_Format = 21;
        break;
    case '3':
        gewaehltes_Format = 23;
        break;

    default:
        gewaehltes_Format = 17;
        break; // Standardfall
    }

    return gewaehltes_Format;

}

void zeichne_Steuerungs_Kasten() {
    string randabstand = "\t                   "; // Gleiche Einrückung wie das Spielfeld

    // Obere Begrenzung (Breite 40)
    cout << randabstand << (unsigned char)218;
    for (int i = 0; i < 40; i++) cout << (unsigned char)196;
    cout << (unsigned char)191 << endl;

    // Zeile 1: Bewegung
    cout << randabstand << (unsigned char)179 << "  BEWEGEN: [W,A,S,D]                    " << (unsigned char)179 << endl;

    // Zeile 2: Aktionen
    cout << randabstand << (unsigned char)179 << "  BRUECKE: [B]           BEENDEN: [X]   " << (unsigned char)179 << endl;

    // Untere Begrenzung
    cout << randabstand << (unsigned char)192;
    for (int i = 0; i < 40; i++) cout << (unsigned char)196;
    cout << (unsigned char)217 << endl;

    cout << randabstand << " Deine Eingabe: ";
}

bool frage_log_anzeigen() {
    char wahl;
    string randabstand = "\t                   "; //abstand zum seitenrand
    

    do {//do while schleife sodass der Nutzer so lange in der Schleife bleibt bis die Eingabe richtig ist

        system("cls");

        cout << endl;
        // Obere Begrenzung
        cout << randabstand << (unsigned char)218;
        for (int i = 0; i < 40; i++) cout << (unsigned char)196;
        cout << (unsigned char)191 << endl;

        // Inhalt
        cout << randabstand << (unsigned char)179 << "        LOG-DATEI ANZEIGEN?             " << (unsigned char)179 << endl;
        cout << randabstand << (unsigned char)179 << "      [J] Ja           [N] Nein         " << (unsigned char)179 << endl;

        // Untere Begrenzung
        cout << randabstand << (unsigned char)192;
        for (int i = 0; i < 40; i++) cout << (unsigned char)196;
        cout << (unsigned char)217 << endl;

        cout << randabstand << " Deine Wahl: ";
        wahl = lese_einzelnes_Zeichen();//sodass Doppeleingabe abgefangen wird wird eigene Funktion genutzt

        if ((wahl == 'j') || (wahl == 'J')) {
            return true;
        }
        if ((wahl == 'n') || (wahl == 'N')) {
            return false;
        }
    } while (true);
}

bool frage_neues_Spiel() {
    char wahl;
    string randabstand = "\t                   ";

    do {//do while schleife sodass der Nutzer so lange in der Schleife bleibt bis die Eingabe richtig ist

        system("cls");


        cout << endl;

        // Obere Begrenzung
        cout << randabstand << (unsigned char)218;
        for (int i = 0; i < 40; i++) cout << (unsigned char)196;
        cout << (unsigned char)191 << endl;

        //Inhalt 
        cout << randabstand << (unsigned char)179 << "        REVANCHE GEFAEHLIG?             " << (unsigned char)179 << endl;
        cout << randabstand << (unsigned char)179 << "      [J] Ja           [N] Nein         " << (unsigned char)179 << endl;

        // Untere Begrenzung
        cout << randabstand << (unsigned char)192;
        for (int i = 0; i < 40; i++) cout << (unsigned char)196;
        cout << (unsigned char)217 << endl;

        cout << randabstand << " Deine Wahl: ";

        wahl = lese_einzelnes_Zeichen();//sodass Doppeleingabe abgefangen wird wird eigene Funktion genutzt


        if ((wahl == 'j') || (wahl == 'J')) {
            return true;
        }
        if ((wahl == 'n') || (wahl == 'N')) {
            return false;
        }
    } while (true);
}

void zeichne_Phase_Spieler() {
    string abstand = "      ";
    string randabstand = "\t                   ";

    cout << endl << endl << endl;

    // Obere Begrenzung
    cout << randabstand << (unsigned char)201;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)187 << endl;

    //Inhalt
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                  DUELL                 " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "          Computer vs. Spieler          " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "            Phase 1: SPIELER            " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    //Untere Begrenzung
    cout << randabstand << (unsigned char)200;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)188 << endl;

}

void zeichne_Phase_Computer() {
    string abstand = "      ";
    string randabstand = "\t                   ";

    cout << endl << endl << endl;
    // Obere Begrenzung
    cout << randabstand << (unsigned char)201;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)187 << endl;

    //Inhalt
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                  DUELL                 " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "          Computer vs. Spieler          " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "            Phase 2: COMPUTER           " << (unsigned char)186 << endl;
    cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;

    //Untere Begrenzung
    cout << randabstand << (unsigned char)200;
    for (int i = 0; i < 40; i++) cout << (unsigned char)205;
    cout << (unsigned char)188 << endl;

}

char lese_einzelnes_Zeichen() {
    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //in funktion kann ein string eingegeben werden, jedoch wird immer nur das erste Zeichen genutzt --> also eine Mehreingabe von Zeichen wird abgefangen indem nur das erste Zeichen der Eingabe weiter genutzt wird
    //dieses Zeichen wird zurückgegeben und kann so für die weiteren Methoden verwendet werden


    string eingabe;
    bool eingabe_korrekt = false;

    while (eingabe_korrekt == false) {

        getline(cin, eingabe);

        if (eingabe.length() > 0) {//nur wenn eine Eingabe gemacht wurde, ein zeichen eingegeben wurde wird das zeichen überprüft
            
            //es wird nur das erste Zeichen genommen --> so kommt es zu keiner Doppeleinnahme --> und das Zeichen wird zurückgegeben sodass die Methoden wie Bruecke bauen nur ein Zeichen bekommen
            return eingabe.at(0);
        }
    }
}

void zeichne_Abschluss_Banner() {
    system("cls");
    
    string randabstand = "\t                        ";
    string bannerEinzug = "            ";

    cout << endl << endl << endl << endl;
    cout << randabstand << bannerEinzug << " #   #   ###   ####  #   #  ### " << endl;
    cout << randabstand << bannerEinzug << " #   #  #   #  #      #   #   #  " << endl;
    cout << randabstand << bannerEinzug << " #####  #####   ###   #####   #  " << endl;
    cout << randabstand << bannerEinzug << " #   #  #   #      #  #   #   #  " << endl;
    cout << randabstand << bannerEinzug << " #   #  #   #  ####   #   #  ### " << endl << endl;
    cout << randabstand << "            ---- JAPANISCHES LOGIKRAETSEL ---" << endl << endl;


    cout << randabstand << "=========================================================" << endl;
    cout << randabstand << "PROJEKT HASCHI | Programm beendet" << endl;
    cout << randabstand << "---------------------------------------------------------" << endl;
    cout << randabstand << "Software-Architektur: Linus Schiel" << endl;
    cout << randabstand << "Konzeption:           Linus Schiel & Emil Kern" << endl;
    cout << randabstand << "Release:              v1.0.0 (Final)" << endl;
    cout << randabstand << "=========================================================" << endl << endl;
}

void warte_auf_Enter() {
    //===========================================================================================
    //Aufgabe dieser Funktion
    //===========================================================================================
    //Diese Funktion dient dazu, den Eingabepuffer komplett zu leeren und das Programm erst fortzuführen, wenn Enter-Taste gedrueckt wurde --> Dadurch werden Mehrfacheingaben 
    //(wie z.B. "bb") abgefangen, die sonst nachfolgende Menüs oder Abfragen überspringen wuerden


    string Eingabe_Inhalt;

    //getline liest die komplette Zeile + aller eventuell vorhandenen Fehlzeichen ein, bis ein Zeilenumbruch \n erkannt wird
    //Inhalt wird in Eingabe_Inhalt gespeichert und danach sofort verworfen wenn Funktion wieder beendet wurde

    getline(cin, Eingabe_Inhalt);
}

