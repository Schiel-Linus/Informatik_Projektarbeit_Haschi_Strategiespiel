
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spiel_Verwaltung.h
// BESCHREIBUNG: Deklaration der Spiel_Verwaltung
//               Definiert den Haupt-Spiel-Schleife sowie die 
//               Zustände für Menüführung und Spielmodi
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#pragma once
#include "Master_Spielregeln.h"
#include "menue.h"
using namespace std;


class Spiel_Verwaltung {
private:
	int schwierigkeit;
	int gewaehltes_Format;
	string spielername;

public:
	//Konstruktor
	Spiel_Verwaltung();

	//Methoden
	void Hauptmenue();
	void zeige_Regeln_mit_Menue();
	void zeige_Regeln();
	void starte_Solo_Modus();
	void direkter_Spielstart_Spieler();
	void starte_Testspiel_();
	void starte_Duell_Modus_();
};
