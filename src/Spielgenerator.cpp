
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spielgenerator.cpp
// BESCHREIBUNG: Implementierung des Level-Generators
//               Algorithmus zur Erstellung zusammenhaengender
//               Graphen, Kollisionsprüfung und Insel-Setup
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#include "Spielgenerator.h"
using namespace std;


Spielgenerator::Spielgenerator() {
	//Initialisierung des zufallgenerator sodass die Zahlen "zufällig" erstellt werden
	srand(clock());
}

void Spielgenerator::generiere_Spiel(char ziel_Array[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE], int gewaehltes_Format, int schwierigkeit) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Aufgabe dieser Methode ist ein lösbares Haschi Game in Abhängigkeit verschiedener Parameter (schwierigkeit, gewähltes Format) in einem übergebenen Array zu erstellen


	//===========================================================================================
	// A. Organisatorisches
	//===========================================================================================


		//===========================================================================================
		// 1. Ziel Array "leeren"
		//===========================================================================================
		//ziel_Array mit Leerzeichen befüllen


	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			ziel_Array[i][j] = ' ';
		}
	}

	//===========================================================================================
	// 2. Insel Anzahl in Abhängigkeit von Schwierigkeit festlegen
	//===========================================================================================
	//Basierend auf dem Schwierigkeitsgrad legen wir die Anzahl der Inseln fest welche im Array enthalten sein sollen


	int Anzahl_Inseln;
	switch (schwierigkeit) {
	case(0):
		Anzahl_Inseln = 3;//Testspiel
		break;
	case(1):
		Anzahl_Inseln = 6; //leicht
		break;
	case(2):
		Anzahl_Inseln = 9; //Mittel
		break;
	case(3):
		Anzahl_Inseln = 12; //Schwer
		break;
	default:
		return; //bei anderen Zahlen soll die Methode sofort beendet werden
	}

	//===========================================================================================
	// 3. Register für bereits vorhandene Inseln & Variable für Anzahl der Inseln
	//===========================================================================================
	//um komplettes Array nicht nach bereits gespeicherten Inseln durchsuchen zu müssen, wird Register(zwei 1 dimensionale Arrays) benutzt
	//die X und Y Koordinaten werden getrennt in zwei Arrays gespeichert --> leichterer Zugriff auf die Werte

	int Inseln_X_Werte[100] = {};
	int Inseln_Y_Werte[100] = {};

	//Variable die Zählt wie viele Inseln bereits im Array enthalten sind
	int Insel_Zähler = 0;


	//===========================================================================================
	// B. Generierung
	//===========================================================================================
	//Ziel ist: Einen zusammenhängenden Graph (Wurm) per Zufall über das Array ausbreiten dafür wird zu Beginn ein Startpunkt benötigt
	//--> eine zufällige Gerade Koordinate (Koordinaten müssen Greade sein da Array Spielfeld verdoppelt wurde um Darstellung zu verbessern daher dürfen Inseln nur an Geraden Koordinaten stehen


	//===========================================================================================
	// 1. Zufällige Startkoordinate
	//===========================================================================================
	//durch Zufall Erzeugung einer Startkoordinate für eine INsel sowie Speicherung im Register der Start Insel


	//-------------------------------------------------------------------------------------------
	// 1a) Startkoordinate bestimmen
	//-------------------------------------------------------------------------------------------
	//diese zufällige Koordinate muss sich irgendwo im Spielfeld befinden -- > Grenze 0 bis gewähltes Format
	//Inseln dürfen nur an Gerade Koordinaten im Array (Verdopplung zur Entzerrung während Beibehaltung gleicher möglicher Positionen für Inseln)
	//Insel mit Platzhalter in ziel_Array speichern

	//Problem: Mit nachfolgender Formel wären Inseln auch im Spielfeldrand gewesen was falsch wäre
	//int Startpunkt_X = rand() % (gewaehltes_Format / 2) * 2; Formel muss verändert werden siehe unten
	//int Startpunkt_Y = rand() % (gewaehltes_Format / 2) * 2; Formel muss verändert werden siehe unten
	//Zufallszahlen im Intervall [0,gewähltes Format-1]

	//um dieses Problem zu umgehen wurde neue Formel benötigt --> Nutzung neuer Formel welche für geraden Zahlen im Intervall von 2 bis (gewähltes Format minus 2) sorgt
	int Startpunkt_X = (rand() % ((gewaehltes_Format - 2) / 2)) * 2 + 2;
	int Startpunkt_Y = (rand() % ((gewaehltes_Format - 2) / 2)) * 2 + 2;


	//nun ist die Startkoordinate der ersten Insel per Zufall gewählt
	//da die Insel aber später erst eine Zahl erhält, erhält sie einen Platzhalter
	ziel_Array[Startpunkt_Y][Startpunkt_X] = '#';


	//-------------------------------------------------------------------------------------------
	// 1b) Speichern der Koordinate im Register
	//-------------------------------------------------------------------------------------------
	//nun werden Koordinaten der Insel in den Inseln X/Y Werten Arrays gespeichert
	Inseln_X_Werte[0] = Startpunkt_X;
	Inseln_Y_Werte[0] = Startpunkt_Y;

	//Aktualiesierung des Insel Zählers
	Insel_Zähler = 1;//nun ist genau eine Insel vorhanden

	//===========================================================================================
	// 2. Schleife zur Erstellung weiterer Inseln
	//===========================================================================================
	//da Programm einmal wegen zu vielen Versuchen abgestürzt ist, wird while Schleife durch eine bestimmte Anzahl möglicher Versuche begrenzt
	int Versuche = 0;

	//Schleife läuft so lange bis genug Inseln (die Anzahl die vorher durch Schwierigkeitsgrad festgelegt worden ist) im Array sind und der Versuchszähler nicht zu hoch ist
	while ((Insel_Zähler < Anzahl_Inseln) && (Versuche < 2000)) {

		Versuche = Versuche + 1;//Versuche werden hochgezählt --> falls es zu viele Versuche gab, wird die while Schleife beendet


		//===========================================================================================
		// 2.1. Um den Graph fortführen zu können muss eine zufällige Insel genommen werden
		//===========================================================================================

		//es wird eine Zufallszahl "gewürfelt" --> nur Zufallszahlen welche beim einsetzen ins Register (Inseln_X_Werte/Inseln_Y_Werte) nur schon vorhandene Insel Koordinaten liefern
		int Zufalls_Index = rand() % Insel_Zähler;
		//Zufallszahlen im Intervall [0,Insel_Zähler - 1]
		//Bsp: Insel Zähler 3; rand()%3 --> Indize 0,1,2 (es wird immer eine existierende Insel getroffen)


		//nun werden die Koordinate dieser zufälligen Insel abgefragt
		int x_Koordinate_now = Inseln_X_Werte[Zufalls_Index];
		int y_Koordinate_now = Inseln_Y_Werte[Zufalls_Index];



		//===========================================================================================
		// 2.2. Planung einer MÖGLICHEN Brücke
		//===========================================================================================
		//nur mögliche Brücke, weil nachdem per Zufall eine Richtung gewählt wurde, muss diese Richtung (bzw. Länge) erst noch überprüft werden sodass kein Hinderniss im Weg ist


		//-------------------------------------------------------------------------------------------
		// 2.2.1. Richtung bestimmen
		//-------------------------------------------------------------------------------------------
		//Entscheidung ob Oben (0), Unten (1), Links (2), Rechts (3) //um dies in einen Vektor (Richtung) umzuwandeln nutzung zweier Hilfsvariablen & switch case

		//!!Hinweis:!!
		//Koordinatensystem ist gedreht, daher ist der Nullpunkt oben links in der Ecke

		int x_Hilfsvariable = 0;
		int y_Hilfsvariable = 0;

		int Zufalls_Richtung = rand() % 4; //Zufallszahlen im Intervall [0,3]

		switch (Zufalls_Richtung) {
		case(0):
			x_Hilfsvariable = 0;
			y_Hilfsvariable = -1;
			break;
		case(1):
			x_Hilfsvariable = 0;
			y_Hilfsvariable = 1;
			break;
		case(2):
			x_Hilfsvariable = -1;
			y_Hilfsvariable = 0;
			break;
		case(3):
			x_Hilfsvariable = 1;
			y_Hilfsvariable = 0;
			break;
		}
		//Einheitsvektor ist damit erstellt


		//-------------------------------------------------------------------------------------------
		// 2.2.2 Länge des Vektors bestimmen 
		//-------------------------------------------------------------------------------------------
		//die Länge muss gerade sein, sodass gewährleistet ist dass nur bei Geraden Koordinaten Inseln entstehen
		//multiplizieren des Einheitsvektor mit der zufällig gewählten Länge

		int Laenge = (rand() % 3 + 1) * 2; //Zufallszahl im Intervall --> nur Gerade zahlen

		int x_Hilfsvariable_Laenge = x_Hilfsvariable * Laenge;
		int y_Hilfsvariable_Laenge = y_Hilfsvariable * Laenge;


		//-------------------------------------------------------------------------------------------
		// 2.2.3 Zielkoordinate der neuen Insel berechnen
		//-------------------------------------------------------------------------------------------
		// der Vektor wird mit der Start Koordinate addiert und so wird die Zielkoordinate berechnet

		int moeglicher_Endpunkt_X = x_Hilfsvariable_Laenge + x_Koordinate_now;
		int moeglicher_Endpunkt_Y = y_Hilfsvariable_Laenge + y_Koordinate_now;


		//-------------------------------------------------------------------------------------------
		// 2.2.4 Kontrolle auf Hindernisse
		//-------------------------------------------------------------------------------------------
		// Prüfung erfolgt in 3 Stufen (Spielfeldrand, Zielplatz Insel bereits belegt, Strecke durch andere Hindernisse belegt (andere Insel/ Brücken)


		//Prio 1: Spielfeldrand

		//liegt Endpunkt auf dem Brett (gewähltes Format ist dabei von Relevanz und nicht das ganze Array)
		if ((moeglicher_Endpunkt_X > 0) && (moeglicher_Endpunkt_X < gewaehltes_Format - 1) && (moeglicher_Endpunkt_Y > 0) && (moeglicher_Endpunkt_Y < gewaehltes_Format - 1)) {

			//Prio 2: Zielplatz Insel bereits belegt?

			if (ziel_Array[moeglicher_Endpunkt_Y][moeglicher_Endpunkt_X] == ' ') {//wenn Zielplatz mit nichts belegt ist Array an dieser Stelle mit Leerzeichen "befüllt"

				//Prio 3: Strecke für Hinderniss durch Brücken oder Inseln belegt?

				bool kein_Hinderniss = true; //da die Bedingung Prio 3 nicht in einfacher if () KLammer untergebracht werden kann Nutzung einer boolschen Variable welche später im Fall kein Hinderniss auf true bleibt
				//und dann durch ein if Befehl überprüft wird

				//Start mit einem Punkt nach der Insel (sonst geht spätere Prüfung nicht da der Arrayplatz des Startpunkt
				// mit Platzhalter belegt ist)
				int X_Such = x_Koordinate_now + x_Hilfsvariable;
				int Y_Such = y_Koordinate_now + y_Hilfsvariable;

				//Schleife läuft so lange bis Endpunkt erreicht ist
				while ((X_Such != moeglicher_Endpunkt_X) || (Y_Such != moeglicher_Endpunkt_Y)) {

					if (ziel_Array[Y_Such][X_Such] != ' ') {
						kein_Hinderniss = false;
						break; //wenn ein Hinderniss gefunden wurde dann muss schleife direkt beendet werden und eine neue Insel muss gesucht werden
					}

					//"Sucher" Startkoordinaten müssen eine Koordinate weiterspringen, sodass nächstes Feld gecheckt werden kann
					X_Such = X_Such + x_Hilfsvariable;
					Y_Such = Y_Such + y_Hilfsvariable;
				}



				//===========================================================================================
				// 3. Bau der MÖGLICHEN Brücke
				//===========================================================================================
				// da es zwei verschiedene Brückenarten gibt muss per Zufall ausgewählt werden welche gesetzt wird 


				if (kein_Hinderniss == true) {
					//nun ist jede Prio gecheckt und die Brücke kann/wird gebaut werden
					char bauZeichen;

					//-------------------------------------------------------------------------------------------
					// 3.1 Auswahl der Brücke
					//-------------------------------------------------------------------------------------------
					//einfache Brücke 0; doppelte Brücke 1 // 50 prozentige Wahrscheinlichkeit zwischen den beiden Brückenarten

					if (rand() % 2 == 0) { //Fall A: einfache Brücke '|' / '-'

						if ((Zufalls_Richtung == 0) || (Zufalls_Richtung == 1)) { //um mit richtigem Zeichen die Brücke zu bauen, wird die Richtung welche davor per Zufall entschieden wurde
							//als if Bedingung genutzt
							bauZeichen = Vertikal_Einfach;
						}
						else // wenn in X Richtung gebaut wird horizontale Brücke
							bauZeichen = Horizontal_Einfach;
					}
					else { //Fall B: doppelte Brücke '=' / (unsigned char)186


						if ((Zufalls_Richtung == 0) || (Zufalls_Richtung == 1)) { //um mit richtigem Zeichen die Brücke zu bauen, wird die Richtung welche davor per Zufall entschieden wurde
							//als if Bedingung genutzt
							bauZeichen = Vertikal_Doppelt;
						}
						else // wenn in X Richtung gebaut wird horizontale Brücke
							bauZeichen = Horizontal_Doppelt;
					}

					//-------------------------------------------------------------------------------------------
					// 3.2. Bau der ausgewählten Brücke
					//-------------------------------------------------------------------------------------------
					//nun müssen die Platzhalter aus Leerzeichen zwischen den beiden INseln mit dem jeweiligen bauZeichen ersetzt werden

					//dafür wird gleiche Schleife wie zur Überprüfung genutzt

					//der neue Endpunkt ist die Summe aller Additionen der Suchkoordinaten
					//um eine einfachere Verständlichkeit zu erhalten wird neue Variable vergeben
					int Endpunkt_X = moeglicher_Endpunkt_X;
					int Endpunkt_Y = moeglicher_Endpunkt_Y;

					//Startpunkt 
					int X_Bau = x_Koordinate_now + x_Hilfsvariable;//Start mit einem Punkt nach der Insel (sonst wird Insel mit bauZeichen überschrieben)
					int Y_Bau = y_Koordinate_now + y_Hilfsvariable;//Start mit einem Punkt nach der Insel (sonst wird Insel mit bauZeichen überschrieben)

					//Schleife läuft so lange bis Endpunkt erreicht ist
					while ((X_Bau != Endpunkt_X) || (Y_Bau != Endpunkt_Y)) {
						//im Array wird die Linie gezogen
						ziel_Array[Y_Bau][X_Bau] = bauZeichen;

						//Baukoordinaten müssen eine Koordinate weiterspringen, sodass nächstes Feld "gebaut" werden kann
						X_Bau = X_Bau + x_Hilfsvariable;
						Y_Bau = Y_Bau + y_Hilfsvariable;
					}
					//-------------------------------------------------------------------------------------------
					// 3.3. Eintragung der Koordinaten ins "Register" 
					//-------------------------------------------------------------------------------------------
					// nur so können später die Koordinaten abgerufen werden (Inseln_X_Werte[0],Inseln_Y_Werte[0],Insel_Zähler = 1)

					Inseln_X_Werte[Insel_Zähler] = Endpunkt_X;
					Inseln_Y_Werte[Insel_Zähler] = Endpunkt_Y;
					Insel_Zähler = Insel_Zähler + 1;

					//-------------------------------------------------------------------------------------------
					// 3d) Platzhalter als Insel setzen
					//-------------------------------------------------------------------------------------------
					ziel_Array[Endpunkt_Y][Endpunkt_X] = '#';

				}
			}
		}
	}
	//===========================================================================================
	// 4. Inselzahl berechnen
	//===========================================================================================
	// aus Platzhaltern (#) werden Zahlen
	// Prinzip: ablaufen jedes einzelnen Arrayplatz --> bis # gefunden wurde --> dann prüfen was links rechts oben unten ist und die Linienanzahl addieren
	// --> doppelte Linien zählen doppelt


	//-------------------------------------------------------------------------------------------
	// 4.1. Spielfeld auf # prüfen
	//-------------------------------------------------------------------------------------------

	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			if (ziel_Array[i][j] == '#') {

				//-------------------------------------------------------------------------------------------
				// 4.2. Nachbarnzellen prüfen & Aufsummierung der Brückenanzahl
				//-------------------------------------------------------------------------------------------
				// Prüfung ob Insel mit Platzhalter an der Feldgrenze steht denn dann ist eine Prüfung auf Linien in die jeweilige Richtung nicht möglich
				int Summe_Bruecken = 0;

				//gewaehltes Format wird mit 1 subtrahiert da das Array schon mit 0 startet
				//Richtung nach oben (y-1)
				if (i > 0) {//obere Feldgrenzen 0 ist Grenze bei der Prüfung in die Richtung nicht möglich ist
					if ((unsigned char)ziel_Array[i - 1][j] == Vertikal_Einfach)
						Summe_Bruecken = Summe_Bruecken + 1;
					else if ((unsigned char)ziel_Array[i - 1][j] == Vertikal_Doppelt)
						Summe_Bruecken = Summe_Bruecken + 2;
				}

				//Richtung nach unten (y +1)
				if (i < gewaehltes_Format - 1) { //untere Feldgrenzen minus 1 ist Grenze bei der Prüfung in die Richtung nicht möglich ist
					if ((unsigned char)ziel_Array[i + 1][j] == Vertikal_Einfach)
						Summe_Bruecken = Summe_Bruecken + 1;
					else if ((unsigned char)ziel_Array[i + 1][j] == Vertikal_Doppelt)
						Summe_Bruecken = Summe_Bruecken + 2;
				}

				//Richtung nach links (x-1)
				if (j > 0) { //Linke Feldgrenzen 0 ist Grenze bei der Prüfung in die Richtung nicht möglich ist
					if ((unsigned char)ziel_Array[i][j - 1] == Horizontal_Einfach)
						Summe_Bruecken = Summe_Bruecken + 1;
					else if ((unsigned char)ziel_Array[i][j - 1] == Horizontal_Doppelt)
						Summe_Bruecken = Summe_Bruecken + 2;
				}

				//Richtung nach rechts (x+1)
				if (j < gewaehltes_Format - 1) { //Rechte Feldgrenzen minus 1 ist Grenze bei der Prüfung in die Richtung nicht möglich ist
					if ((unsigned char)ziel_Array[i][j + 1] == Horizontal_Einfach)
						Summe_Bruecken = Summe_Bruecken + 1;
					else if ((unsigned char)ziel_Array[i][j + 1] == Horizontal_Doppelt)
						Summe_Bruecken = Summe_Bruecken + 2;
				}


				//-------------------------------------------------------------------------------------------
				// 4.3. Zahl ins Array schreiben
				//-------------------------------------------------------------------------------------------
				// die Zahl liegt als integer vor, muss jedoch in ein char Array eingetragen werden, daher muss die Zahl in ein char umgewandelt werden
				// Trick: '0' + summe_Bruecken ergibt das Zeichen der Zahl --> ASCII Code von 0 ist 48 und ab dann wird einfach zahl addiert


				//nun wird diese errechnete Summe der Bruecken ins Array anstatt des Platzahlters (#) eingetragen
				ziel_Array[i][j] = '0' + Summe_Bruecken;
			}
		}
	}
}
