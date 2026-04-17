
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Master_Spielregeln.h
// BESCHREIBUNG: Deklaration der zentralen Spielsteuerung
//               Verknüpft Anzeige, Steuerung, Generator 
//               und Löser zu einem Gesamtsystem
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#pragma once
#include "menue.h"
#include "Haschi_Loeser.h"
#include "Cursor.h"
#include "Spielfeld.h"
#include "Spielgenerator.h"
#include <stdlib.h> //für system("cls")
#include <fstream>// für Log_Dateien
#include <string> 

using namespace std;

class Master_Spielregeln {
private:
	Spielfeld Anzeige;
	Cursor Steuerung;
	Spielgenerator Haschi_Game_Generator;
	Haschi_Loeser Computer_Loeser;

	string spielername;
	int gewaehltes_Format;
	int schwierigkeit;
	int anzahl_Zuege;
	int anzahl_Zuege_Computer;


	char Fertige_Loesung[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];
	char Start_Spielfeld[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];

	char Spieler_Loesung[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];
	char Computer_Loesung[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];


public:
	//Konstruktoren
	Master_Spielregeln();
	Master_Spielregeln(int Gewaehltes_Format, int Schwierigkeit, string Spielername);

	//Getter
	int get_anzahl_Zuege()const;
	string get_Spielername()const;

	//weitere Methoden
	void eingabe_verarbeiten(char Eingabe);
	void spielzeichnen();
	void spielzeichnen_Computer();
	void baue_Bruecke();
	void wandle_Fertige_Loesung_um();
	bool pruefe_ob_gewonnen(char ziel_Array[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]);
	void schreibe_Log_Datei(string Aktion);

	bool hat_Computer_gewonnen();
	bool hat_Spieler_gewonnen();

	void vorbereiten_Computer_Durchlauf();
	void vorbereiten_Spieler_Durchlauf();
	void starte_Computer_Durchlauf();

	void zeichne_Ueberschrift_Spielfeld();
	void zeichne_Anzahl_Spielzuege_Spieler();
	void zeichne_Anzahl_Spielzuege_Computer();
	void zeichne_Vergleich_Statistik();


	//nur aus Testzwecken
	void zeige_Loesung();
};