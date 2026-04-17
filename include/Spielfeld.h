
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spielfeld.h
// BESCHREIBUNG: Deklaration der Klasse Spielfeld.
//               Definiert das visuelle Grundgerüst, die 
//               Spielfeldgrössen und die Anzeige-Funktionen
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#pragma once
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

const int ARRAY_MAX_GROESSE = 23;//dieses Variable legt im ganzen Programm die maximale Spielfeld(/Array)-Größe fest
const unsigned char Horizontal_Einfach = 196;
const unsigned char Horizontal_Doppelt = 205;
const unsigned char Vertikal_Einfach = 179;
const unsigned char Vertikal_Doppelt = 186;



class Spielfeld {
private:
	int Gewaehltes_Format;
	char Spielbrett[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];
	//fürs Spielfeld wird die maximale Groeße von 23 * 23 reserviert --> dabei wird die maximale Größe mit der Zahl definiert da das Spielfeld für eine bessere Ansicht gestreckt worden ist
	// genaue Zusammensetzung --> 10 Inseln + 9 Lücken + 2 RAhmen + 2 Puffer = 23
public:
	Spielfeld(); //Standardkonstruktor in cpp Datei um Array mit Leerzeichen "befüllen" zu können
	Spielfeld(int gewaehltes_Format);

	//weitere Methoden
	void zeichneSpielfeld(int cursor_X_Koordinate, int cursor_Y_Koordinate, char aktuelles_Spielbrett[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]);
};