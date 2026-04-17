
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Cursor.h
// BESCHREIBUNG: Deklaration der Klasse Cursor
//               Verwaltet die Positionsdaten und definiert
//               die Bewegungs-Funktionen auf dem Spielfeld
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include "Spielfeld.h"//wird integriert um auf Variable ARRAY_MAX_GROESSE Zugriff zu haben
using namespace std;

class Cursor {
private:
	int x_Koordinate_Spielfeld;//Position der Koordiante des Cursors wird gespeichert
	int y_Koordinate_Spielfeld;//Position der Koordiante des Cursors wird gespeichert
	int gewaehltes_Format; //das Format wird festgelegt sodass die Obergrenze der Prüfung in Abhängigkeit des gewählten Format funktionieren kann

public:
	//Konstruktoren
	Cursor();
	Cursor(int Startpunkt_x_Koordinate, int Startpunkt_Y_Koordinate, int Gewaehltes_Format);


	//Getter
	int get_X_Koordinate_Spielfeld();
	int get_Y_Koordinate_Spielfeld();

	//weitere Methoden
	void bewege_Cursor(char Eingabe);
};
