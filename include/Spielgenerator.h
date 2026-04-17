
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spielgenerator.h
// BESCHREIBUNG: Deklaration der Spielgenerator-Klasse
//               Definiert die Funktionen zur Erzeugung 
//               dynamischer und lösbarer Level-Layouts
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#pragma once
#include "Spielfeld.h"//inkludiert um Array_Max_Groesse nutzen zu können
#include <stdlib.h>
#include <ctime>

class Spielgenerator {
private:
	//keine Attribute in dieser Klasse

public:
	//Standardkonstruktor
	Spielgenerator();

	//weitere Methode
	void generiere_Spiel(char ziel_Array[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE], int gewaehltes_Format, int schwierigkeit);
};