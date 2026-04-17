
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Haschi_Loeser.h
// BESCHREIBUNG: Deklaration der Klasse Haschi_Loeser
//               Definiert die Algorithmen zur automatischen
//               Lösung und die Register für Inseldate
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#pragma once
#include <iomanip>
#include <iostream>
#include <stdlib.h> //für system("cls")
#include <fstream>// für Log_Dateien
#include <string> 
#include "Spielfeld.h"//inkludiert um Array_Max_Groesse nutzen zu können
using namespace std;


class Haschi_Loeser {
private:
	char computer_Loesung_intern[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE];
	int gewaehltes_Format;

	int Insel_X_Koordinate[100]; //speichert Spalte jeder Insel
	int Insel_Y_Koordinate[100]; //speichert Zeile jeder Insel
	int Insel_Soll_Bruecken[100]; //Zahl die auf der Insel steht --> wie viele Brücken verbunden werden müssen
	int Insel_Ist_Bruecken[100]; //wie viele Brücken sind bereits mit Insel verbunden

	int anzahl_Inseln; //wie viele Inseln es insgesamt gibt
	int anzahl_Zuege_Computer; //notwendig um Log Datei zu schreiben



public:
	//Konstruktoren
	Haschi_Loeser();
	Haschi_Loeser(int Gewaehltes_Format);


	//Methoden
	void initialisiere_Loeser(char Computer_Spielfeld[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]);
	int finde_Nachbar(int insel_index, char richtung);
	void aktualisiere_Ist_Stand();
	bool pruefe_unberuerhte_Inseln();
	bool pruefe_einfache_Restwerte_bei_Inseln();
	void kopiere_Loesung_zurueck(char zielArray[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]);
	void zeichne_Bruecke(int start_index, int ziel_index, char richtung);
	bool baue_EINE_Bruecke(char zielArray[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]);
};
