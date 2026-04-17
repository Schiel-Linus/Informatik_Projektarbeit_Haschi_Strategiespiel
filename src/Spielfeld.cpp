
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spielfeld.cpp
// BESCHREIBUNG: Implementierung der Spielfeld-Methoden
//               Berechnung der Rahmenbegrenzungen (ASCII), 
//               Zentrierung der Ausgabe und Cursor-Logik
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#include"Spielfeld.h"
using namespace std;


Spielfeld::Spielfeld()//Standardkonstruktor: befüllt Array mit nur Leerzeichen
{
	Gewaehltes_Format = ARRAY_MAX_GROESSE;//Attribut aus Header DAtei wird auf Max_Wert gesetzt um Klasse zu initialisieren

	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			Spielbrett[i][j] = ' ';
		}
	}//Komplettes Array --> maximale Größe von 23 (siehe Konstante aus Spielfeld.h) wird mit Leerzeichen aufgefühlt
}

Spielfeld::Spielfeld(int gewaehltes_Format) {//parametrisierter Konstruktor
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//dieser Konstruktor befüllt das Array Spielbrett im Spielbereich mit Leerzeichen & setzt die Randbegrenzungen, diese Dinge werden in Abhängigkeit der gewählten Größe gemacht


	//===========================================================================================
	// 1. Array wird mit Leerzeichen gefüllt (komplette Größe --> ARRAY_MAX_GROESSE)
	//===========================================================================================

	Gewaehltes_Format = gewaehltes_Format;//Internes Attribut wird mit Variable aus Funktion welche in Master_Spielregeln aufgerufen wurde gleichgesetzt
	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			Spielbrett[i][j] = ' ';
		}
	}


	//===========================================================================================
	// 2. Randbegrenzungen werden gesetzt & in Abhängigkeit von gewählter Größe
	//===========================================================================================

	//da Array mit 0 startet sind Endpunkte um -1 von Array_Max_Groesse verschoben
	const int Grenzen_verschoben = Gewaehltes_Format - 1;//Konstante da Array sonst nicht erstellt werden kann


	//____________Eckpunkte____________
	Spielbrett[0][0] = 201; //linke Ecke oben
	Spielbrett[Grenzen_verschoben][0] = 200;//linke Ecke unten
	Spielbrett[0][Grenzen_verschoben] = 187;//rechte Ecke oben
	Spielbrett[Grenzen_verschoben][Grenzen_verschoben] = 188;//rechte Ecke unten



	//____________Randstreifen____________
	for (int z = 1; z < Grenzen_verschoben; z++) {
		Spielbrett[0][z] = (unsigned char)205;
		Spielbrett[Grenzen_verschoben][z] = (unsigned char)205;;
	}//untere Begrenzungen werden gesetzt
	for (int z = 1; z < Grenzen_verschoben; z++) {
		Spielbrett[z][0] = (unsigned char)186;
		Spielbrett[z][Grenzen_verschoben] = (unsigned char)186;
	}//obere Begrenzungen werden gesetzt

	// (unsigned char) Cast wird verwendet, um die Compiler-Warnung C4309 zu vermeiden. 
	// Da Standard-Chars oft nur den Bereich von -128 bis 127 abdecken, muessen ASCII-Sonderzeichen (wie 186 oder 205) explizit als vorzeichenlose Werte (0-255) interpretiert werden
	// siehe Skript Seite 26 Tabelle 1 --> unsigned char
}

void Spielfeld::zeichneSpielfeld(int cursor_X_Koordinate, int cursor_Y_Koordinate, char aktuelles_Spielbrett[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Aufgabe dieser Methode ist, dass ein vorgefertigtes Spielfeld (Randbegrenzungen, sonst leer) und ein übergebenes Spielbrett in welchem Insel und Brücken
	//gespeichert sind, zusammen ausgegeben werden. Dabei muss auch die Cursor Position berücksichtigt werden.

	//--> die Methode soll demnach die Information (Brücken,Inseln) welche im aktuellen Spielerbrett gespeichert sind in einer spielerfreundlichen (Randbegrenzungen,Cursor) Form ausgeben. Dabei wird auch berücksichtigt, dass der Cursor
	//drei Zeichen breit ist weswegen hierbei Fuellzeichen benötigt werden


	//===========================================================================================
	//1. Ausgabe des Spielfelds 
	//===========================================================================================

	//-------------------------------------------------------------------------------------------
	// 1a) Abstandsbrechnung zur Zentrierung des Spielfelds
	//-------------------------------------------------------------------------------------------
	//Spielfeld muss immer unter der Überschrift zentriert werden, da es verschiedene Spielfeldgrößen gibt muss der passende Abstand berechnet werden

	int Ueberschrift_Breite = 81;
	int Spielfeldbreite = Gewaehltes_Format * 3; //um Spielfeldbreite auszurechnen wird gewähltes format * 3 gerechnet, da jedes Feld im Array auf 3 Zeichen gestreckt ist um den Cursor darstellen zu können

	int abstand = (Ueberschrift_Breite - Spielfeldbreite) / 2; //in der Klammer wird zuerst berechnet wie viel Leerzeichen Platz insgesamt ist --> danach wird es durch 2 geteilt um Abstand für eine einzelne Seite zu erhalten

	string Zeichenabstand = "";//auf diesen String werden die jeweilige Zeichenanzahl welche berechnet wurde aufaddiert --> for Schleife läuft demnach so lange wie groß der Abstand berechnet wurde
	for (int i = 0; i < abstand; i++) {
		Zeichenabstand = Zeichenabstand + " ";
	}


	cout << "\n\n";
	for (int i = 0; i < Gewaehltes_Format; i++) {
		cout << "\t" << Zeichenabstand;
		for (int j = 0; j < Gewaehltes_Format; j++) {


			//-------------------------------------------------------------------------------------------
			// 1b) Prüfung welches Füllzeichen im Array Feld ist --> Prüfung links und rechts
			//-------------------------------------------------------------------------------------------

				//im Normalfall ist links & rechts vom Inhalt Luft (Leerzeichen) bei der Ausgabe
				//wenn aber eine horizontale Bruecke im Array Platz ist müssen wir die Spaces mit den Leerzeichen durch die passende Linienart auffüllen
				//dabei Unterscheidung zwischen horizontaler einfacher oder doppelter Bruecke notwendig (-------- oder ======)
				// auch muss auf Randstreifenbegrenzung überprüft werden --> auch in diesem Fall wird das fuellzeichen angepasst
				//um dies zu machen nutzen wir zwei char Fuellzeichen welches in Abhängigkeit des im aktuellen_Spielbrett stehenden Zeichen verändert wird

			char fuellzeichen_L = ' '; //Standardfall: Leerzeichen
			char fuellzeichen_R = ' '; //Standardfall: Leerzeichen rechts

			//unterscheidung welches Zeichen im Spielfeld

			//=============Brücken im Spielfeld=============
			if ((unsigned char)aktuelles_Spielbrett[i][j] == Horizontal_Einfach) { //wenn Zeichen - war werden beide Fuellzeichen zu -
				fuellzeichen_L = Horizontal_Einfach;
				fuellzeichen_R = Horizontal_Einfach;
			}
			else if ((unsigned char)aktuelles_Spielbrett[i][j] == Horizontal_Doppelt) { //wenn Zeichen = war werden beide Fuellzeichen zu =
				fuellzeichen_L = Horizontal_Doppelt;
				fuellzeichen_R = Horizontal_Doppelt;
			}


			//============Spielfeldrand=====================
			//Nutzung von unsigned char um WArnung C4309 zu vermeiden

			//Fall 1: Horizontale Linie am oberen/Rand (=)
			if ((unsigned char)Spielbrett[i][j] == 205) {
				fuellzeichen_L = (unsigned char)205;
				fuellzeichen_R = (unsigned char)205;
			}

			//Fall 2: Ecken am linken Rand
			else if (((unsigned char)Spielbrett[i][j] == 201) || ((unsigned char)Spielbrett[i][j] == 200)) {
				fuellzeichen_L = ' '; // außen links an der Ecke muss ein Leerzeichen --> außerhalb vom Spielfeld
				fuellzeichen_R = (unsigned char)205; // Rechts innen an der Ecke muss fehlendes Zeichen (leerzeichen) aufgefüllt (ersetzt) werden
			}

			//Fall 3: Ecken am rechten Rand
			else if (((unsigned char)Spielbrett[i][j] == 187) || ((unsigned char)Spielbrett[i][j] == 188)) {
				fuellzeichen_L = (unsigned char)205; // Links innen an der Ecke muss fehlendes Zeichen (leerzeichen) aufgefüllt (ersetzt) werden
				fuellzeichen_R = ' '; // außen rechts an der Ecken muss ein Leerzeichen --> außerhalb vom Spielfeld
			}

			//!!Hinweis!!
			//für vertikale Linie irrelevant da Feld nicht auf dreier Höhe gestreckt wurde


			//-------------------------------------------------------------------------------------------
			// 1c) Unterscheidung zwischen Cursor oder Inhalt & Ausgabe dieses Zeichen
			//-------------------------------------------------------------------------------------------


			//Cursor
			if ((i == cursor_Y_Koordinate) && (j == cursor_X_Koordinate)) {
				//wenn Schleifenposition gleich der Cursor Position (in Form x/y Koordinate) welche für diese Methode übergeben wurde, wird Cursor übergeben

				cout << "["; //Linker Teil des Cursors

				//in Mitte des Cursors wird Inhalt des übergeben Arrays aktuelles Spielbrett ausgegeben
				cout << aktuelles_Spielbrett[i][j];

				cout << "]";//REchter Teil des Cursor
			}
			else {//falls kein Cursor an der jeweiligen Position steht müssen fuellzeichen genutzt werden

				cout << fuellzeichen_L; //Ausgabe des zuvor angepasstem Fuellzeichen

				//Inhalt Mitte
				if (aktuelles_Spielbrett[i][j] != ' ') {//wenn dass Zeichen im übergebenen Spielbrett kein Leerzeichen ist (Brücke/Insel) wird das jeweilige Zeichen ausgegeben
					cout << aktuelles_Spielbrett[i][j];
				}

				else {//wenn Zeichen im übergebenen ein Leerzeichen ist wird Spielbrett ausgegeben --> dadurch ist gewährleistet dass Randbegrenzungen ausgegeben werden
					cout << (unsigned char)Spielbrett[i][j]; // wieder Nutzung des cast Operator
				}

				cout << fuellzeichen_R; //Ausgabe des zuvor angepasstem Fuellzeichen
			}
		}
		cout << endl; //Zeilensprung nach jeder Zeile
	}
}

