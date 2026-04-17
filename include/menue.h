
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        menue.h
// BESCHREIBUNG: Deklaration der Menü-Funktionen
//               Definiert die Benutzeroberfläche, das 
//               Tutorial-System und die Eingabemasken
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#pragma once
#include <string>
#include <iomanip>
#include <iostream>
using namespace std;


void zeige_Begruessung();
void zeige_Hauptmenue();


void zeichne_erste_Regel();
void zeichne_zweite_Regel();
void zeichne_dritte_Regel();
void zeichne_vierte_Regel();
void zeichne_fuenfte_Regel();
void zeichne_Tutorial_Menue();

void zeichne_Ueberschrift();

string erfrage_Name();
int erfrage_Schwierigkeit();
int erfrage_Spielfeldgroesse();

void zeichne_Steuerungs_Kasten();
bool frage_log_anzeigen();
bool frage_neues_Spiel();

void zeichne_Phase_Spieler();
void zeichne_Phase_Computer();

char lese_einzelnes_Zeichen();
void warte_auf_Enter();

void zeichne_Abschluss_Banner();
