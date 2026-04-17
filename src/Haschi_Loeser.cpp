
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Haschi_Loeser.cpp
// BESCHREIBUNG: Implementierung der Lösungs-Algorithmen
//               Enthält die Prüfregeln für zwingende Züge
//               sowie die automatische Brücken-Platzierung
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#include"Haschi_Loeser.h"
using namespace std;


Haschi_Loeser::Haschi_Loeser() {
	//Standardkonstruktor
	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			computer_Loesung_intern[i][j] = ' ';
		}//computer Loesung Array wird mit Leerzeichen befüllt
	}
	gewaehltes_Format = 23;
	anzahl_Inseln = 0;
	anzahl_Zuege_Computer = 0;
	for (int i = 0; i < 100; i++) { //Insel DAten Array werden auf Null gesetzt
		Insel_X_Koordinate[i] = 0;
		Insel_Y_Koordinate[i] = 0;
		Insel_Soll_Bruecken[i] = 0;
		Insel_Ist_Bruecken[i] = 0;
	}
}

Haschi_Loeser::Haschi_Loeser(int Gewaehltes_Format) {
	//parametrisierter Konstruktor
	gewaehltes_Format = Gewaehltes_Format;
	anzahl_Inseln = 0;
	anzahl_Zuege_Computer = 0;
	for (int i = 0; i < 100; i++) { //Insel DAten Array werden auf Null gesetzt
		Insel_X_Koordinate[i] = 0;
		Insel_Y_Koordinate[i] = 0;
		Insel_Soll_Bruecken[i] = 0;
		Insel_Ist_Bruecken[i] = 0;
	}

	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			computer_Loesung_intern[i][j] = ' ';
		}//computer Loesung Array wird mit Leerzeichen befüllt
	}
}

void Haschi_Loeser::initialisiere_Loeser(char Computer_Spielfeld[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Aufgabe dieser Methode ist das "durchlaufen" des Arrays und dabei von jeder Insel die X & Y Koordinate in das jeweilige Array zu schreiben


	//===========================================================================================
	// 1. Spieler Array wird in internes Array kopiert
	//===========================================================================================
	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			computer_Loesung_intern[i][j] = Computer_Spielfeld[i][j];
		}
	}

	//===========================================================================================
	// 2. X und Y Koordinaten der Inseln in den jeweiligen Array speichern
	//===========================================================================================
	//Array wird durch zwei for Schleifen abgelaufen und jedes Feld wird auf zeichen zwischen '1'-'8' überprüft
	//--> bei Insel im Feld werden i j der Schleifen als Koordinaten übernommen
	//durch Anzahl der Inseln welche als Attribut gespeichert ist erhalten die X & Y Array neue Indizes
	anzahl_Inseln = 0;
	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			if ((computer_Loesung_intern[i][j] > '0') && (computer_Loesung_intern[i][j] < '9')) {
				//wenn im Feld eine Zahl zwischen 1-8 steht --> Insel --> übernahme der Koordinaten
				Insel_X_Koordinate[anzahl_Inseln] = j;
				Insel_Y_Koordinate[anzahl_Inseln] = i;

				//zusätzlich wird auch Inselzahl --> wie viele Brücken an die Insel gebaut werden darf übernommen

				//zur Zeit liegt in Array die Insel zahl als Zeichen vor um diese überprüfen und in das jeweilige Array schreiben zu können muss umgerechnet werden
				Insel_Soll_Bruecken[anzahl_Inseln] = computer_Loesung_intern[i][j] - '0'; //funktioniert da weil ASCII-WErte den gleichen Abstand zu einander haben wie die Zahlen

				//Zähler wie viele Inseln gefunden wurden muss erhöht werden
				anzahl_Inseln++;
			}
		}
	}
}

int Haschi_Loeser::finde_Nachbar(int insel_index, char richtung) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Aufgabe dieser Methode ist das bei einem übergebenen Insel_Index und einer Richtung geprüft wird ob es einen Insel Nachbarn gibt. Falls es den gibt wird der jeweilige Index
	//dieser INsel zurückgegeben --> daduch können Koordinaten der Nachbar Insel direkt bestimmt werden

	//!!Hinweis!!
	//die Funktion/Prinzip der "Nachbar" Suche wurde so ähnlich schon in Methode Baue Bruecke von Master Spielregeln verwendet daher wird hier "recycling" betrieben


	//===========================================================================================
	// 1. Startpunkt bestimmen
	//===========================================================================================
	//durch Insel Index können die X & Y Koordinate einfach druch die Arrays herangezogen werden

	int Startpunkt_X_Koordinate = Insel_X_Koordinate[insel_index];
	int Startpunkt_Y_Koordinate = Insel_Y_Koordinate[insel_index];

	//===========================================================================================
	// 2. Richtung in Form eines Vektors bestimmen
	//===========================================================================================
	//durch einen einfachen switch case wird das übergebene Richtung Zeichen in einen Vektor bzw. zwei Hilfsvariablen umgewandelt

	//um Eingabe der Richtung in einen Vektor umzuwandeln nutzung zweier Hilfsvariablen & switch case
	int x_Hilfsvariable = 0;
	int y_Hilfsvariable = 0;

	//!!Hinweis:!!
	//Koordinatensystem ist gedreht, daher ist der Nullpunkt oben links in der Ecke, daher wird genau entgegen der Richtung der Tasteingabe verschoben

	switch (richtung) { //durch switch case werden die Hilfsvariablen "befüllt"
	case('W'):
	case('w'):
		x_Hilfsvariable = 0;
		y_Hilfsvariable = -1;
		break;
	case('S'):
	case('s'):
		x_Hilfsvariable = 0;
		y_Hilfsvariable = 1;
		break;
	case('A'):
	case('a'):
		x_Hilfsvariable = -1;
		y_Hilfsvariable = 0;
		break;
	case('D'):
	case('d'):
		x_Hilfsvariable = 1;
		y_Hilfsvariable = 0;
		break;
		//Einheitsvektor ist damit erstellt

	default:
		x_Hilfsvariable = 0;
		y_Hilfsvariable = 0;
		return -1; //bei falschem Richtungszeichen soll die Methode sofort -1 zurückgeben --> -1 steht dafür das kein Nachbar gefunden worden ist
	}


	//===========================================================================================
	//3. Such Funktion um Verbindungsinsel zwischen denen Linie gezogen werden soll zu finden
	//===========================================================================================

	// boolsche Variable ziel_gefunden --> beim Bau der Brücke kann nur in Abhängigkeit von gefundenem ziel gebaut werden
	bool ziel_gefunden = false; //noch auf false da nichts gefunden wurde

	//-------------------------------------------------------------------------------------------
	// 3a) Startpunkt für Suche
	//-------------------------------------------------------------------------------------------
	//für die Suchschleife brauchen wir Startpunkte

	// da Insel auf der Cursor bereits bekannt ist, kann der nächste Punkt überprüft werden daher wird Einheitsvektor direkt addiert
	int X_Such = Startpunkt_X_Koordinate + x_Hilfsvariable;
	int Y_Such = Startpunkt_Y_Koordinate + y_Hilfsvariable;


	//-------------------------------------------------------------------------------------------
	// 3b) Suchschleife
	//-------------------------------------------------------------------------------------------
	//Suchschleife läuft solange bis Rand des Arrays erreicht wird

	while ((X_Such >= 0) && (X_Such < gewaehltes_Format) && (Y_Such >= 0) && (Y_Such < gewaehltes_Format)) {

		//Fehlermeldung/Hinweistext --> deswegen If-Bedingung mit Pufferüberlauf
			//Pufferüberlauf muss verhindert werden (X/Y Such dürfen nicht über die Array Grenzen hinaus laufen)
		if ((X_Such < 0) || (X_Such >= ARRAY_MAX_GROESSE) || (Y_Such < 0) || (Y_Such >= ARRAY_MAX_GROESSE)) {
			break;
		} // falls die Koordinaten über die Grenzen hinaus laufen wird die (Such) Schleife sofort beendet


		//=====================Fall A: Insel (Ziel)!!=====================

		if ((computer_Loesung_intern[Y_Such][X_Such] >= '1') && (computer_Loesung_intern[Y_Such][X_Such] <= '9')) {
			// wenn eine Zahl im Array Platz steht --> Insel
			ziel_gefunden = true; // Ziel (Insel) wurde gefunden daher kann in Abhängigkeit dieser boolschen Variable eine Brücke gebaut werden
			break; //(Such-)Schleife wird abgebrochen da ziel gefunden ist
		}


		//=====================Fall B: Hindernisse in Form anderer Brücken=====================

		else {
			//durch Eingabe der Bruecken-Richtung gibt es zwei Fälle welche durch eine If-Bedingung überprüft wird

			if ((richtung == 'W') || (richtung == 'w') || (richtung == 'S') || (richtung == 's')) {
				
				if (((unsigned char)computer_Loesung_intern[Y_Such][X_Such] == Horizontal_Einfach) || ((unsigned char)computer_Loesung_intern[Y_Such][X_Such] == Horizontal_Doppelt)) {
					break; //wenn Hindernis gefunden wird schleife verlassen
				}
			}
			else {
				
				if (((unsigned char)computer_Loesung_intern[Y_Such][X_Such] == Vertikal_Einfach) || ((unsigned char)computer_Loesung_intern[Y_Such][X_Such] == Vertikal_Doppelt)) {
					break; //wenn Hindernis gefunden wird schleife verlassen
				}
			}
		}
		//"Sucher" Startkoordinaten müssen eine Koordinate weiterspringen, sodass nächstes Feld gecheckt werden kann
		X_Such = X_Such + x_Hilfsvariable;
		Y_Such = Y_Such + y_Hilfsvariable;
	}//schlussendlich sind die x/y_Such die Ziel Koordinaten der gesuchten Insel (werden so lange aufaddiert bis Ziel erreicht ist oder Hindernis)
	//--> diese aufaddierten Koordinaten können nun in einen Insel_index umgewandelt werden


	//===========================================================================================
	// 4. Aus Koordinaten Insel Index bestimmen
	//===========================================================================================
	// um die Arrays X & Y Koordinaten zu erhalten wird mit Indexen gearbeitet
	// wenn die boolsche Variable ziel gefunden auf true gesetzt wurde, wurde ein Nachbar gefunden --> nun kann in Abhängigkeit der Koordinaten der Insel Index des "Nachbars" gesucht werden


	if (ziel_gefunden == true) {

		for (int index = 0; index < anzahl_Inseln; index++) {

			if ((Insel_X_Koordinate[index] == X_Such) && (Insel_Y_Koordinate[index] == Y_Such)) { //Index wird hochgezählt --> wenn Index bei Eingabe in X & Y Arrays passende Koordinaten ausgibt --> passender Index gefunden

				return index;
			}
		}
	}

	//wenn Programm hier ankommt --> entweder zielgefunden war false oder passender Index wurde nicht gefunden --> -1 wird zurückgegeben

	return -1;
}

void Haschi_Loeser::aktualisiere_Ist_Stand() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Aufgabe dieser Methode ist das Speichern der Anzahl der anliegenden Brücken an einer Insel


	//===========================================================================================
	// 1. Hautpschleife
	//===========================================================================================
	//Schleife, welche jede Insel bzw. jeden Index durchgeht

	for (int index = 0; index < anzahl_Inseln; index++) {

		//===========================================================================================
		// 2. Werte für die aktuelle Insel zurücksetzen
		//===========================================================================================
		//Nur wert der aktuellen Insel wird auf Null gesetzt

		Insel_Ist_Bruecken[index] = 0;

		//===========================================================================================
		// 3. Startpunkt bestimmen
		//===========================================================================================
		//durch Insel Index welcher durch i größer wird, können die X & Y Koordinate einfach durch die Arrays herangezogen werden

		int Startpunkt_X_Koordinate = Insel_X_Koordinate[index];
		int Startpunkt_Y_Koordinate = Insel_Y_Koordinate[index];


		//===========================================================================================
		// 4. Zähl-Prinzip
		//===========================================================================================
		//die Brücken Zählung ist in zwei Blöcken aufgebaut (horizontal,vertikal) --> hierbei wird addiert wie viele Brücken anliegen


		//-------------------------------------------------------------------------------------------
		// 4a) Horizontaler Check
		//-------------------------------------------------------------------------------------------

		//-----------------Links-----------------
		if (Startpunkt_X_Koordinate - 1 >= 0) {//geprüfter Punkt muss im Array liegen --> größer als Spielfeldrandkoordinate sein
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate][Startpunkt_X_Koordinate - 1] == Horizontal_Einfach) {

				Insel_Ist_Bruecken[index]++;//Array Anzahl zum jeweiligen Index wird um 1 erhöht, wegen einfacher Brücke
			}
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate][Startpunkt_X_Koordinate - 1] == Horizontal_Doppelt) {

				Insel_Ist_Bruecken[index] = Insel_Ist_Bruecken[index] + 2;//Array Anzahl zum jeweiligen Index wird um 2 erhöht, wegen doppelter Brücke
			}
		}
		//-----------------Rechts-----------------
		if (Startpunkt_X_Koordinate + 1 < gewaehltes_Format) {//geprüfter Punkt muss im Array liegen --> größer als Spielfeldrandkoordinate sein
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate][Startpunkt_X_Koordinate + 1] == Horizontal_Einfach) {

				Insel_Ist_Bruecken[index]++;//Array Anzahl zum jeweiligen Index wird um 1 erhöht, wegen einfacher Brücke
			}
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate][Startpunkt_X_Koordinate + 1] == Horizontal_Doppelt) {

				Insel_Ist_Bruecken[index] = Insel_Ist_Bruecken[index] + 2;//Array Anzahl zum jeweiligen Index wird um 2 erhöht, wegen doppelter Brücke
			}
		}

		//-------------------------------------------------------------------------------------------
		// 4a) Horizontaler Check
		//-------------------------------------------------------------------------------------------

		//-----------------Oben-----------------
		if (Startpunkt_Y_Koordinate - 1 >= 0) {//geprüfter Punkt muss im Array liegen --> größer als Spielfeldrandkoordinate sein
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate - 1][Startpunkt_X_Koordinate] == Vertikal_Einfach) {

				Insel_Ist_Bruecken[index]++;//Array Anzahl zum jeweiligen Index wird um 1 erhöht, wegen einfacher Brücke
			}
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate - 1][Startpunkt_X_Koordinate] == Vertikal_Doppelt) {

				Insel_Ist_Bruecken[index] = Insel_Ist_Bruecken[index] + 2;//Array Anzahl zum jeweiligen Index wird um 2 erhöht, wegen doppelter Brücke
			}
		}
		//-----------------Unten-----------------
		if (Startpunkt_Y_Koordinate + 1 < gewaehltes_Format) {//geprüfter Punkt muss im Array liegen --> größer als Spielfeldrandkoordinate sein
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate + 1][Startpunkt_X_Koordinate] == Vertikal_Einfach) {

				Insel_Ist_Bruecken[index]++;//Array Anzahl zum jeweiligen Index wird um 1 erhöht, wegen einfacher Brücke
			}
			if ((unsigned char)computer_Loesung_intern[Startpunkt_Y_Koordinate + 1][Startpunkt_X_Koordinate] == Vertikal_Doppelt) {

				Insel_Ist_Bruecken[index] = Insel_Ist_Bruecken[index] + 2;//Array Anzahl zum jeweiligen Index wird um 2 erhöht, wegen doppelter Brücke
			}
		}
	}
}

bool Haschi_Loeser::pruefe_unberuerhte_Inseln() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da Brücken zu finden welche zwingend gebaut werden müssen --> diese werden durch eine weitere Methode gebaut --> Methode gibt true zurück wenn ein Zug erfolgreich war
	//wenn Zug nicht erfolgreich --> false


	//===========================================================================================
	// 1. Hautpschleife
	//===========================================================================================
	//Schleife, welche jede Insel bzw. durchgeht Index durchgeht

	for (int index = 0; index < anzahl_Inseln; index++) {

		//===========================================================================================
		// 2. Hat Insel schon passende Anzahl an Brücken
		//===========================================================================================
		//wenn Insel nicht schon passende Anzahl an Brücken hat --> nachfolgende Prüfung ob Kriterium für Brücken bauen auf die Insel zu trifft, kann starten

		if (Insel_Ist_Bruecken[index] < Insel_Soll_Bruecken[index]) {
			//wenn Bedingung wahr können weitere Kriterien geprüft werden

			//===========================================================================================
			// 3. Nachbar Inseln zählen
			//===========================================================================================
			//hierbei muss geprüft werden wie viele Nachbar INseln die ausgewählte Insel hat

			int Nachbar_Insel_Zaehler = 0;
			int Nachbar_index;
			char feld_daneben;

			//----------------------------------Richtung oben (w)-----------------------
			if (finde_Nachbar(index, 'w') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde ein Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

				Nachbar_index = finde_Nachbar(index, 'w');
				//Zeichen direkt neben Start insel muss geprüft werden
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] - 1][Insel_X_Koordinate[index]];

				//Nachbar Insel zählt nur wenn diese noch Insel braucht und keine doppelte vorhanden ist
				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					Nachbar_Insel_Zaehler++;
				}
			}

			//----------------------------------Richtung unten (s)-----------------------
			if (finde_Nachbar(index, 's') != -1) {

				Nachbar_index = finde_Nachbar(index, 's');
				//zeichen direkt unter der Start Insel muss geprüft werden
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] + 1][Insel_X_Koordinate[index]];

				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					Nachbar_Insel_Zaehler++;
				}
			}

			//----------------------------------Richtung links (a)-----------------------
			if (finde_Nachbar(index, 'a') != -1) {

				Nachbar_index = finde_Nachbar(index, 'a');
				// zeichen direkt links neben der Start Insel muss geprüft werden
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] - 1];

				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					Nachbar_Insel_Zaehler++;
				}
			}

			//----------------------------------Richtung rechts (d)-----------------------
			if (finde_Nachbar(index, 'd') != -1) {

				Nachbar_index = finde_Nachbar(index, 'd');
				// zeichen direkt rechts neben der Start Insel muss geprüft werden 
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] + 1];

				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char) feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					Nachbar_Insel_Zaehler++;
				}
			}


			//===========================================================================================
			// 4. Entscheidung ob Zug (Brücke bauen) unumgänglich ist
			//===========================================================================================
			//die Insel hat die Zahl 3 und zwei Nachbarn --> es muss zu jeder Nachbarinsel mindestens eine Brücke gehen (eine muss später natürlich eine doppelte sein --> erstmal irrelevant)

			//Logik: (Nachbar -1) sind alle Insel Nachbarn bis auf eine --> wenn deren Maximale Kapazität (daher * 2 weil doppelte Bruecken auch beachtet werden müssen) nicht ausreichend ist, um das
			//		Soll (Zahl auf der INsel) zu erfüllen --> muss zu jedem Nachbar mindestens eine Bruecke führen

			if (Insel_Soll_Bruecken[index] > (Nachbar_Insel_Zaehler - 1) * 2) {

				//-------------------------------------------------------------------------------------------
				// 4a) Nachbar Insel finden und auf verbundene Brücken überprüfen
				//-------------------------------------------------------------------------------------------
				//alle vier Richtungen werden durchgegangen und bei der ersten die keine Brücke hat wird eine Brücke gebaut --> die Methode wird dann beendet und gibt true zurück --> so wird immer nur eine Brücke gebaut und der Spieler sieht immer eine Brücke als Fortschritt
				int Nachbar_index;
				int Startpunkt_X_Koordinate = Insel_X_Koordinate[index];
				int Startpunkt_Y_Koordinate = Insel_Y_Koordinate[index];
				char feld_daneben;

				//----------------------------------Richtung oben (w)-----------------------
				if (finde_Nachbar(index, 'w') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden 
					//nun wird Nachbar Index benötigt
					Nachbar_index = finde_Nachbar(index, 'w');

					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] - 1][Insel_X_Koordinate[index]];

					//wenn im Feld daneben keine Brücke bisher gebaut worden ist --> Feld ist leer --> kann einfache Bruecke gebaut werden
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {

						//Methode Brücke bauen wird aufgerufen
						zeichne_Bruecke(index, Nachbar_index, 'w');

						//Methode wird direkt durch Rückgabe von true beendet
						return true;
					}
				}

				//----------------------------------Richtung unten (s)-----------------------
				if (finde_Nachbar(index, 's') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden 
					//nun wird Nachbar Index benötigt
					Nachbar_index = finde_Nachbar(index, 's');

					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] + 1][Insel_X_Koordinate[index]];

					//wenn im Feld daneben keine Brücke bisher gebaut worden ist --> Feld ist leer --> kann einfache Bruecke gebaut werden
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && (unsigned char)(feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {

						//Methode Brücke bauen wird aufgerufen
						zeichne_Bruecke(index, Nachbar_index, 's');

						//Methode wird direkt durch Rückgabe von true beendet
						return true;
					}
				}

				//----------------------------------Richtung links (a)-----------------------
				if (finde_Nachbar(index, 'a') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden 
					//nun wird Nachbar Index benötigt
					Nachbar_index = finde_Nachbar(index, 'a');

					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] - 1];

					//wenn im Feld daneben keine Brücke bisher gebaut worden ist --> Feld ist leer --> kann einfache Bruecke gebaut werden
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {

						//Methode Brücke bauen wird aufgerufen
						zeichne_Bruecke(index, Nachbar_index, 'a');

						//Methode wird direkt durch Rückgabe von true beendet
						return true;
					}
				}
				//----------------------------------Richtung rechts (d)-----------------------
				if (finde_Nachbar(index, 'd') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden 
					//nun wird Nachbar Index benötigt
					Nachbar_index = finde_Nachbar(index, 'd');

					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] + 1];

					//wenn im Feld daneben keine Brücke bisher gebaut worden ist --> Feld ist leer --> kann einfache Bruecke gebaut werden
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {

						//Methode Brücke bauen wird aufgerufen
						zeichne_Bruecke(index, Nachbar_index, 'd');

						//Methode wird direkt durch Rückgabe von true beendet
						return true;
					}
				}
			}
		}
	}
	//===========================================================================================
	// 5. wenn Compiler hier gelandet --> kein Zug gefunden
	//===========================================================================================

	return false;
}

bool Haschi_Loeser::pruefe_einfache_Restwerte_bei_Inseln() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da nach Inseln zu suchen welche nur noch genau eine Möglichkeit haben um eine Brücke zu bauen


	//===========================================================================================
	// 1. Hautpschleife
	//===========================================================================================
	//Schleife, welche jede Insel bzw. durchgeht Index durchgeht


	for (int index = 0; index < anzahl_Inseln; index++) {

		//===========================================================================================
		// 2. Hat Insel schon passende Anzahl an Brücken
		//===========================================================================================
		//wenn Insel nicht schon passende Anzahl an Brücken hat --> nachfolgende Prüfung ob Kriterium für Brücken bauen auf die Insel zu trifft, kann starten

		if (Insel_Ist_Bruecken[index] < Insel_Soll_Bruecken[index]) {
			//wenn Bedingung wahr können weitere Kriterien geprüft werden


			//-------------------------------------------------------------------------------------------
			// 2a) wie viel Nachbarn können noch Brücken aufnehmen
			//-------------------------------------------------------------------------------------------

			int Nachbar_Insel_Zaehler = 0;
			int Nachbar_index;
			char feld_daneben;

			//----------------------------------Richtung oben (w)-----------------------
			if (finde_Nachbar(index, 'w') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

				//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
				Nachbar_index = finde_Nachbar(index, 'w');
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] - 1][Insel_X_Koordinate[index]];

				//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					//--> Nachbar INsel hat noch nicht genug Brücken

					Nachbar_Insel_Zaehler++;
				}
			}
			//----------------------------------Richtung unten (s)-----------------------
			if (finde_Nachbar(index, 's') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

				//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
				Nachbar_index = finde_Nachbar(index, 's');
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] + 1][Insel_X_Koordinate[index]];

				//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					//--> Nachbar INsel hat noch nicht genug Brücken

					Nachbar_Insel_Zaehler++;
				}
			}

			//----------------------------------Richtung links (a)-----------------------
			if (finde_Nachbar(index, 'a') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

				//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
				Nachbar_index = finde_Nachbar(index, 'a');
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] - 1];

				//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					//--> Nachbar INsel hat noch nicht genug Brücken

					Nachbar_Insel_Zaehler++;
				}
			}

			//----------------------------------Richtung rechts (d)-----------------------
			if (finde_Nachbar(index, 'd') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

				//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
				Nachbar_index = finde_Nachbar(index, 'd');
				feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] + 1];

				//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
				if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
					//--> Nachbar INsel hat noch nicht genug Brücken

					Nachbar_Insel_Zaehler++;
				}
			}


			//===========================================================================================
			// 3. Fehlende Brücke berechnen
			//===========================================================================================
			//wie viele Brücken fehlen der Insel noch (Soll - Ist)

			int fehlende_Bruecken = Insel_Soll_Bruecken[index] - Insel_Ist_Bruecken[index];

			//===========================================================================================
			// 4. Zwingende Brücke
			//===========================================================================================
			//wenn Insel noch Brücken braucht und nur noch genau ein Nachbar frei ist --> Nachbar_Insel_Zaehler ==1

			if ((fehlende_Bruecken > 0) && (Nachbar_Insel_Zaehler == 1)) {

				//-------------------------------------------------------------------------------------------
				// 4a) Richtung der Brücke
				//-------------------------------------------------------------------------------------------

				//----------------------------------Richtung oben (w)-----------------------
				if (finde_Nachbar(index, 'w') != -1) {//wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

					//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
					Nachbar_index = finde_Nachbar(index, 'w');
					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] - 1][Insel_X_Koordinate[index]];

					//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
						//--> Nachbar INsel hat noch nicht genug Brücken

						//wenn Compiler bis hier gelangt ist --> ist der Nachbar in w Richtung und Methode bruecke zeichnen kann aufgerufen werden
						zeichne_Bruecke(index, Nachbar_index, 'w');

						//da nur eine Bruecke gebaut werden soll wird sofort return true zurückgegeben
						return true;
					}
				}

				//----------------------------------Richtung unten (s)-----------------------
				if (finde_Nachbar(index, 's') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

					//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
					Nachbar_index = finde_Nachbar(index, 's');
					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index] + 1][Insel_X_Koordinate[index]];

					//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
						//--> Nachbar INsel hat noch nicht genug Brücken

						//wenn Compiler bis hier gelangt ist --> ist der Nachbar in s Richtung und Methode bruecke zeichnen kann aufgerufen werden
						zeichne_Bruecke(index, Nachbar_index, 's');

						//da nur eine Bruecke gebaut werden soll wird sofort return true zurückgegeben
						return true;
					}
				}

				//----------------------------------Richtung links (a)-----------------------
				if (finde_Nachbar(index, 'a') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

					//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
					Nachbar_index = finde_Nachbar(index, 'a');
					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] - 1];

					//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
						//--> Nachbar INsel hat noch nicht genug Brücken

						//wenn Compiler bis hier gelangt ist --> ist der Nachbar in a Richtung und Methode bruecke zeichnen kann aufgerufen werden
						zeichne_Bruecke(index, Nachbar_index, 'a');

						//da nur eine Bruecke gebaut werden soll wird sofort return true zurückgegeben
						return true;
					}
				}

				//----------------------------------Richtung rechts (d)-----------------------
				if (finde_Nachbar(index, 'd') != -1) { //wenn die Methode findeNachbar einen Wert nicht -1 wurde eine Nachbar gefunden --> was der Index der Nachbar Insel ist erstmal irrelevant

					//um Nachbar Inseln zu prüfen wird Index der Nachbar benötigt
					Nachbar_index = finde_Nachbar(index, 'd');
					feld_daneben = computer_Loesung_intern[Insel_Y_Koordinate[index]][Insel_X_Koordinate[index] + 1];

					//Prüfung ob Nachbar Inseln schon passenden Anzahl an Brücken hat und keine Doppelbruecke im Weg ist
					if ((Insel_Ist_Bruecken[Nachbar_index] < Insel_Soll_Bruecken[Nachbar_index]) && ((unsigned char)feld_daneben != Horizontal_Doppelt) && ((unsigned char)feld_daneben != Vertikal_Doppelt)) {
						//--> Nachbar INsel hat noch nicht genug Brücken

						//wenn Compiler bis hier gelangt ist --> ist der Nachbar in d Richtung und Methode bruecke zeichnen kann aufgerufen werden
						zeichne_Bruecke(index, Nachbar_index, 'd');

						//da nur eine Bruecke gebaut werden soll wird sofort return true zurückgegeben
						return true;
					}
				}
			}
		}
	}

	//===========================================================================================
	// 5. wenn Compiler hier gelandet --> kein Zug gefunden
	//===========================================================================================

	return false;
}

void Haschi_Loeser::kopiere_Loesung_zurueck(char zielArray[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da das interne Computer Array in das ziel Array zu kopieren

	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {

			//jedes Feld wird kopiert
			zielArray[i][j] = computer_Loesung_intern[i][j];
		}
	}
}

void Haschi_Loeser::zeichne_Bruecke(int start_index, int ziel_index, char richtung) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da dass, wenn ein Startpunkt ein Endpunkt und eine richtung vorgegeben wurde eine Brücke zwischen den beiden Punkten gebaut wird
	//--> dabei können auch einfache Brücken zu doppelten Brücken gemacht werden



	//===========================================================================================
	// 1. Brueckenbau
	//===========================================================================================
	//für den Startpunkt wo die Methode anfangen soll zu bauen springen wir ein Feld weiter wie die Insel --> sonst wird Insel mit Brücken überschrieben
	//--> ab dann wird immer ein Feld weitergesprungen und die Linie (Bruecke) "gezogen"

	//!!Hinweis!!
	//die Funktion/Prinzip des Bruecken Bauens wurde so ähnlich schon in Methode Baue Bruecke von Master Spielregeln verwendet daher wird hier "Recycling" betrieben

	//um Eingabe der Richtung in einen Vektor umzuwandeln nutzung zweier Hilfsvariablen & switch case
	int x_Hilfsvariable = 0;
	int y_Hilfsvariable = 0;

	switch (richtung) { //durch switch case werden die Hilfsvariablen "befüllt"
	case('W'):
	case('w'):
		x_Hilfsvariable = 0;
		y_Hilfsvariable = -1;
		break;
	case('S'):
	case('s'):
		x_Hilfsvariable = 0;
		y_Hilfsvariable = 1;
		break;
	case('A'):
	case('a'):
		x_Hilfsvariable = -1;
		y_Hilfsvariable = 0;
		break;
	case('D'):
	case('d'):
		x_Hilfsvariable = 1;
		y_Hilfsvariable = 0;
		break;
		//Einheitsvektor ist damit erstellt

	default:
		x_Hilfsvariable = 0;
		y_Hilfsvariable = 0;
		return; //bei falschem Richtungszeichen soll die Methode sofort -1 zurückgeben --> -1 steht dafür das kein Nachbar gefunden worden ist
	}

	int X_Start_Insel = Insel_X_Koordinate[start_index] + x_Hilfsvariable;
	int Y_Start_Insel = Insel_Y_Koordinate[start_index] + y_Hilfsvariable;

	int X_Ziel_Insel = Insel_X_Koordinate[ziel_index];
	int Y_Ziel_Insel = Insel_Y_Koordinate[ziel_index];


	//sodass bei der späteren Log_DAtei einfacher ein String erzeugt werden kann welcher eingefügt werden kann
			//Nutzung einer boolschen_Variablen welche bei der jeweiligen Brückenwahl auf true umschaltet und später geprüft werden kann

	bool vertikale_einfache_Bruecke = false;
	bool vertikale_doppelte_Bruecke = false;
	bool horizontale_einfache_Bruecke = false;
	bool horizontale_doppelte_Bruecke = false;
	bool Bruecke_entfernt = false;


	//Schleife läuft solange bis die Start Koordinaten identisch mit der Ziel Insel sind, Schleife wird daher davor aufhören sodass Ziel Insel nicht überschrieben wird
	while ((X_Start_Insel != X_Ziel_Insel) || (Y_Start_Insel != Y_Ziel_Insel)) {

		//Fehlermeldung/Hinweistext weswegen If-Bedingung mit Pufferüberlauf erstellt wurde
				//Pufferüberlauf muss verhindert werden (X/Y Such dürfen nicht über die Array Grenzen hinaus laufen)
		if ((X_Start_Insel < 0) || (X_Start_Insel >= ARRAY_MAX_GROESSE) || (Y_Start_Insel < 0) || (Y_Start_Insel >= ARRAY_MAX_GROESSE)) {
			break;
		} // falls die Koordinaten über die Grenzen hinaus laufen wird die (Such) Schleife sofort beendet


		//=====================Fall A: Vertikale Richtung=====================

		if ((richtung == 'W') || (richtung == 'w') || (richtung == 'S') || (richtung == 's')) {
			//wenn Bruecke_Richtung vertikal werden vertikale Brücken gesetzt
			//Nutzung eines "Kreislaufs": Feld leer --> eine Linie --> zwei Linien --> Feld leer

			//wenn kein Zeichen in dem Array Feld ist, zeichne einfache Linie
			if (computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == ' ') {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = Vertikal_Einfach;//Bauen

				vertikale_einfache_Bruecke = true; //spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
			//ist bereits einfache Linie gezogen, überschreibe den Inhalt mit einer Doppellinie
			else if ((unsigned char)computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == Vertikal_Einfach) {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = Vertikal_Doppelt;// Doppellinie (erweiterter Ascii Code)

				vertikale_doppelte_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
			//ist bereits Doppellinie gezogen, lösche den Inhalt durch Überschreibung mit Leerzeichen
			else if ((unsigned char)computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == Vertikal_Doppelt) {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = ' ';//lösche Inhalt und ersetze durch Leerzeichen

				Bruecke_entfernt = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
		}

		//=====================Fall B: Horizontale Richtung=====================

		else {
			//wenn Breucken_Richtung horizontal werden horizontale Bruecken gesetzt

			//wenn kein Zeichen in dem Array Feld ist, zeichne einfache Linie
			if (computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == ' ') {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = Horizontal_Einfach;//Bauen

				horizontale_einfache_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
			//ist bereits einfache Linie gezogen, überschreibe den Inhalt mit einer Doppellinie
			else if ((unsigned char)computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == Horizontal_Einfach) {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = Horizontal_Doppelt;

				horizontale_doppelte_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
			//ist bereits Doppellinie gezogen, lösche den Inhalt durch Überschreibung mit Leerzeichen
			else if ((unsigned char)computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] == Horizontal_Doppelt) {
				computer_Loesung_intern[Y_Start_Insel][X_Start_Insel] = ' ';//lösche Inhalt und ersetze durch Leerzeichen

				Bruecke_entfernt = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
			}
		}
		X_Start_Insel = X_Start_Insel + x_Hilfsvariable;
		Y_Start_Insel = Y_Start_Insel + y_Hilfsvariable;
	}

	//anzahl Züge muss um eins erhöht werden
	anzahl_Zuege_Computer++;

	//===========================================================================================
	//5. Inhalt für Log Datei erstellen und integrieren
	//===========================================================================================
	//da es zu aufwändig wäre die Koordinaten welche integer sind in string durch bspw. switch case umzuwandeln wird die Aktion
	//des Spielers direkt in die Log Datei geschrieben



	//-------------------------------------------------------------------------------------------
	// 5a) Start- & Zielkoordinaten zwischenspeichern
	//-------------------------------------------------------------------------------------------
	//die einzelnen Start- & Zielkoordinaten werden hier nochmal zwischengespeichert sodass eine bessere Übersichtlichkeit gewährleistet ist

	//Startkoordinaten --> (Start-Insel)
	int Start_Insel_X_Log = Insel_X_Koordinate[start_index];
	int Start_Insel_Y_Log = Insel_Y_Koordinate[start_index];

	//Zielkoordinaten --> (Ziel-Insel)
	int Ziel_Insel_X_Log = Insel_X_Koordinate[ziel_index];
	int Ziel_Insel_Y_Log = Insel_Y_Koordinate[ziel_index];

	//-------------------------------------------------------------------------------------------
	// 5b) Log-Datei wird erweitert 
	//-------------------------------------------------------------------------------------------
	//durch boolsche Variablen welche angeben welche Linienart gewählt wurde wird ein String angefertigt und dieser mit weiteren Elementen in die Log DAtei geschrieben


			//if else bedingung wodurch der passenden string gewählt werden kann
	string welche_Bruecke;
	if (vertikale_einfache_Bruecke == true) {
		welche_Bruecke = "Vertikale einfache Bruecke wurde gebaut zwischen Insel ";
	}
	else if (vertikale_doppelte_Bruecke == true) {
		welche_Bruecke = "Vertikale doppelte Bruecke wurde gebaut zwischen Insel ";
	}
	else if (horizontale_einfache_Bruecke) {
		welche_Bruecke = "Horizontale einfache Bruecke wurde gebaut zwischen Insel ";
	}
	else if (horizontale_doppelte_Bruecke == true) {
		welche_Bruecke = "Horizontale einfache Bruecke wurde gebaut zwischen Insel ";
	}
	else if (Bruecke_entfernt == true) {
		welche_Bruecke = "Bruecke wurde entfernt zwischen Insel ";
	}

	//oeffnen der Log Datei --> in Append Modus dadurch kann etwas angehängt werden und die Datei wird nicht überschrieben
	ofstream Spielverlauf_aus;
	Spielverlauf_aus.open("Spielverlauf", ios::app);


	if (!Spielverlauf_aus) {
		cout << "Datei konnte nicht geöffnet werden!\n";
		return;
	}
	// da integer zu aufwändig zum unwandeln wäre wird direkt in die Datei geschrieben ohne einen vorgefertigten String der Methode mit der Log datei zu übergeben
	Spielverlauf_aus << anzahl_Zuege_Computer << ".Zug: " << welche_Bruecke << "(" << Start_Insel_X_Log << "|" << Start_Insel_Y_Log << ")" " und der Insel (" << Ziel_Insel_X_Log << "|" << Ziel_Insel_Y_Log << ").\n";
	// Log Datei schließen
	Spielverlauf_aus.close();
}

bool Haschi_Loeser::baue_EINE_Bruecke(char zielArray[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da dass der Compiler nach und nach die einzelnen Regeln durchgeht --> immer nur eine Brücke wird gebaut sodass Spieler Fortschritt nach und nach sehen kann

	// 1. aktuelle Spielfeld von Master Spielregeln in das interne Computer Array kopieren
	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {

			//jedes Feld wird kopiert
			computer_Loesung_intern[i][j] = zielArray[i][j];
		}
	}

	// 2. Ist Stand zählen
	aktualisiere_Ist_Stand();

	// 3. Regel 1 versuchen
	if (pruefe_unberuerhte_Inseln() == true) {

		kopiere_Loesung_zurueck(zielArray);
		return true;
	}

	//4. Regel 2 versuchen
	if (pruefe_einfache_Restwerte_bei_Inseln() == true) {

		kopiere_Loesung_zurueck(zielArray);
		return true;
	}

	//5. Wenn keine Regel mehr einen Zug findet ist der Löser am Ende
	return false;
}