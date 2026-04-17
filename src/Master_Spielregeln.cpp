
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Master_Spielregeln.cpp
// BESCHREIBUNG: Implementierung der Kern-Spielregeln
//               Verwaltet Spielzüge, Eingabe-Verarbeitung,
//               Siegbedingungen und das Logging-System
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#include "Master_Spielregeln.h"


Master_Spielregeln::Master_Spielregeln() :
	//die Standardkonstruktoren der anderen Klassen werden aufgerufen
	Anzeige(),
	Steuerung(),
	Haschi_Game_Generator(),
	Computer_Loeser() {
	//Initialisierung der Mitgliederobjekte, dabei wird Standardkonstruktor dieser Methoden aufgerufen
	gewaehltes_Format = 23;
	schwierigkeit = 1; //die leichte Schwierigkeitsstufe wird initialisiert
	anzahl_Zuege = 0;//am Anfang sind es 0 Züge
	anzahl_Zuege_Computer = 0;
	spielername = "Unbekannt";
	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			Spieler_Loesung[i][j] = ' ';
			Fertige_Loesung[i][j] = ' ';
			Computer_Loesung[i][j] = ' ';
			Start_Spielfeld[i][j] = ' ';
		}//alle Arrays werden leer befüllt
	}
}

Master_Spielregeln::Master_Spielregeln(int Gewaehltes_Format, int Schwierigkeit, string Spielername):
	//die parametrisierten Konstruktoren der anderen Klassen werden aufgerufen
	Anzeige(Gewaehltes_Format),
	Steuerung(2, 2, Gewaehltes_Format),
	Haschi_Game_Generator(),//Standardkonsturktor --> parametrisierter Konstruktor nicht notwendig, da keine Attribute in der Klasse
	Computer_Loeser(Gewaehltes_Format) {
	
	//den Attributen wird der passende WErt welcher aus der Spielverwaltung kommt zugeordnet
	gewaehltes_Format = Gewaehltes_Format;
	schwierigkeit = Schwierigkeit;
	spielername = Spielername;
	anzahl_Zuege = 0;//am Anfang sind es 0 Züge
	anzahl_Zuege_Computer = 0;
	for (int i = 0; i < ARRAY_MAX_GROESSE; i++) {
		for (int j = 0; j < ARRAY_MAX_GROESSE; j++) {
			Spieler_Loesung[i][j] = ' ';
			Fertige_Loesung[i][j] = ' ';
			Computer_Loesung[i][j] = ' ';
			Start_Spielfeld[i][j] = ' ';
		}//alle Arrays werden leer befüllt
	}

	//um Haschi Spielen zu können muss direkt beim aufrufen des Konstruktors ein lösbares Haschi Game erzeugt werden und dieses umgewandelt werden
	//sodass Spieler & Computer nur Inseln und keine Brücken angezeigt bekommt --> dafür wird Methode wandle_Fertige_Loesung_um() verwendet
	wandle_Fertige_Loesung_um();


	//sodass für Spieler direkt das Array Spieler Lösung mit den Inseln befüllt wird, wird schon im Konstruktor die Kopie vom Start Spielfeld in das Spieler Lösungs Array durchgeführt
	vorbereiten_Spieler_Durchlauf();


	//==================================================================
	// Log Datei
	//==================================================================
	// im nachfolgenden Code wird die Einleitung für die Log DAtei geschrieben --> so kann in der Methode baue Brücke einfach der passende String in die Log DAtei geschrieben werden
	
	
	//Beginn Log datei zu schreiben

	// 1. Log Datei wird einmalig überschrieben (gelöscht) 
	ofstream Spielverlauf_aus("Spielverlauf");
	Spielverlauf_aus.close();

	//!Hinweis!: Es gäbe die Möglichkeit die Log DAtei mit allen Spielverläufen der gestarteten Spiele in einer Sitzung zu schreiben --> dafür müsste oberer Befehl ganz am Anfang von Spielverwaltung bei starte Spiel geschrieben werden
	// --> diese Lösung ist so aber nicht vorgesehen. daher wird bei jedem neuen Spielstart eine Log DAtei geschrieben


	//2. In Log wird Spielername, Schwierigkeitsgrad sowie Spielfeldgröße geschrieben
	string Abgrenzung = "=================================================================\n";
	string Einleitung = "Neues Spiel gestartet\n";
	string Trennstreifen = "_________________________________________________________________\n";
	string Name = "Spieler: " + spielername + " hat das Spiel gestartet\n";

	string schwierigkeitsgrad;
	switch (schwierigkeit) {
	case(0):
		schwierigkeitsgrad = "Schwierigkeitsgrad: Training\n"; //Testspiel Variante
		break;
	case (1):
		schwierigkeitsgrad = "Schwierigkeitsgrad: Einfach\n";
		break;
	case(2):
		schwierigkeitsgrad = "Schwierigkeitsgrad: Mittel\n";
		break;
	case(3):
		schwierigkeitsgrad = "Schwierigkeitsgrad: Schwer\n";
		break;
	default:
		schwierigkeitsgrad = "Fehler\n";
		break;
	}

	string spielfeldgroesse;
	switch (gewaehltes_Format) {
	case(13):
		spielfeldgroesse = "Spielfeldgroesse: 5 * 5\n";//Testspiel Variante
		break;
	case(17):
		spielfeldgroesse = "Spielfeldgroesse: 7 * 7\n";
		break;
	case(19):
		spielfeldgroesse = "Spielfeldgroesse: 8 * 8\n";
		break;
	case(21):
		spielfeldgroesse = "Spielfeldgroesse: 9 * 9\n";
		break;
	case(23):
		spielfeldgroesse = "Spielfeldgroesse: 10 * 10\n";
		break;
	default:
		spielfeldgroesse = "Fehler\n";
		break;
	}

	string Ueberschrift = "\n\n" + Abgrenzung + Einleitung + Abgrenzung + Name + schwierigkeitsgrad + spielfeldgroesse + Trennstreifen;

	//durch die Methode schreibe Lpg DAtei muss nur der string übergeben werden --> so könnte falls weitere strings in die Log DAtei geschrieben werden müssten einfach die Methode genutzt werden
	schreibe_Log_Datei(Ueberschrift);
}

int Master_Spielregeln::get_anzahl_Zuege()const {
	return anzahl_Zuege;
}

string Master_Spielregeln::get_Spielername()const {
	return spielername;
}

void Master_Spielregeln::eingabe_verarbeiten(char eingabe) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//dieser Methode kann ein Zeichen übergeben werden und diese entscheidet welche weitere Methode aufgerufen wird
	//so wird bei einer WASD Eingabe die Cursor Methode aufgerufen --> bewege Cursor
	//bei B wird die eigene Methode Brücken bauen gestartet
	//Falscheingaben werden komplett abgefangen




	//===========================================================================================
	//1. Unterscheidung welche Eingabe
	//===========================================================================================


	if ((eingabe == 'W') || (eingabe == 'w') || (eingabe == 'A') || (eingabe == 'a') || (eingabe == 'S') || (eingabe == 's') || (eingabe == 'D') || (eingabe == 'd')) {
		//wenn WASD gedrückt wurde wird Cursor-Methode gestartet und das geprüfte Zeichen übergeben
		Steuerung.bewege_Cursor(eingabe);

	}
	else if ((eingabe == 'b') || (eingabe == 'B')) {//wenn nicht WASD gedrückt wurde und B gedrückt wurde wird eigene Methode Bruecke bauen gestartet
		baue_Bruecke();
	}

	//===========================================================================================
	//2. Aufruf der eigenen Methode spielzeichnen()
	//===========================================================================================
	//nach jeder Eingabe muss das Spiel neu und in aktualisierter Form angezeigt werden, da möglicherweise Veränderung wie Cursor Position oder Brücken vorgenommen wurden


	spielzeichnen();
}

void Master_Spielregeln::spielzeichnen() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da, dass das Spielfeld gezeichnet wird bzw. "aktualisiert" wird oder bei völliger Gleichheit der beiden Arrays Spieler und Fertige Lösung eine gewonnen Meldung ausgegeben wird


	//===========================================================================================
	//1. Löschen des altes Zustands
	//===========================================================================================


	system("cls");


	//===========================================================================================
	//2. Spielfeld zeichnen
	//===========================================================================================
	//Spielfeld wird gezeichnet, sodass Spieler in jedem Fall den Zwischenstand sieht auch wenn Spiel schon gewonnen

	//zuerst soll Übeschrift gezeichnet werden
	zeichne_Ueberschrift_Spielfeld();

	//um Anzahl der gemachten Züge auszugeben wird interne Methode genutzt
	zeichne_Anzahl_Spielzuege_Spieler();

	//um das Spielfeld zu zeichnen nutzen wir die Getter Methoden des Cursors, da so die x und y Koordinate des Cursors erlangt werden können
	int x_Koordinate_now = Steuerung.get_X_Koordinate_Spielfeld();
	int y_Koordinate_now = Steuerung.get_Y_Koordinate_Spielfeld();

	//Aufrufen der Spielfeld Methode & übergabe der x,y now Koordinaten und das Array Spieler_Lösung mit den gespeicherten Inseln und Brücken
	Anzeige.zeichneSpielfeld(x_Koordinate_now, y_Koordinate_now, Spieler_Loesung);

	//===========================================================================================
	//3. Prüfung ob Spiel gewonnen
	//===========================================================================================

		//hierbei wird durch eine If Bedingung erstens eigene Methode pruefe_ob_gewonnen aufgerufen und zweitens die Aussage dieser aufgerufenen Methode überprüft
	if (pruefe_ob_gewonnen(Spieler_Loesung) == true) { //wenn Methode pruefe ob gewonnen true zurückgibt --> Spiel ist gewonnen und Ausgabe des Siegs

		//dass Spieler noch Lösung betrachten kann, wird auf Bildschirm unter dem Spielfeld erstmal nur kleiner Text mit gewonnen Ausgabe gemacht
		string einzug = "\t                   ";


		cout << endl;

		//Obere Begrenzung
		cout << endl << endl;
		cout << einzug << (unsigned char)218;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)191 << endl;

		cout << einzug << (unsigned char)179 << "        HERZLICHEN GLUECKWUNSCH!        " << (unsigned char)179 << endl;
		cout << einzug << (unsigned char)179 << "            SPIEL GEWONNEN!             " << (unsigned char)179 << endl;

		// Untere Begrenzung
		cout << einzug << (unsigned char)192;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)217 << endl;

		cout << endl;

		//damit Spieler es lesen kann muss eine TAste gedrückt werden
		cout << einzug << " [Enter] Weiter....";
		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

		//Bildschirm wird gelöscht, sodass nachfolgender Text erkennbar ist
		system("cls");

		zeichne_Ueberschrift_Spielfeld();

		//obere Begrenzung
		cout << endl << endl;
		cout << einzug << (unsigned char)218;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)191 << endl;

		cout << einzug << (unsigned char)179 << "        HERZLICHEN GLUECKWUNSCH!        " << (unsigned char)179 << endl;
		cout << einzug << (unsigned char)179 << "       DU HAST DAS SPIEL GELOEST!       " << (unsigned char)179 << endl;
		cout << einzug << (unsigned char)179 << "                                        " << (unsigned char)179 << endl;

		cout << einzug << (unsigned char)179 << "       Zuege: " << left << setw(26) << anzahl_Zuege << (unsigned char)179 << endl;

		// Untere Begrenzung
		cout << einzug << (unsigned char)192;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)217 << endl;

		cout << endl << endl;


		//===========================================================================================
		//4. Eintrag in Log-Datei
		//===========================================================================================
		//da Spiel gewonnen, wird ein abschließender Eintrag in die Log Datei geschrieben

		//oeffnen der Log Datei --> in Append Modus dadurch, kann etwas angehängt werden und die Datei wird nicht überschrieben
		ofstream Spielverlauf_aus;
		Spielverlauf_aus.open("Spielverlauf", ios::app);


		if (!Spielverlauf_aus) {
			cout << "Datei konnte nicht geöffnet werden!\n";
			return;
		}
		Spielverlauf_aus << "_________________________________________________________________\n";
		Spielverlauf_aus << "Spieler: " << spielername << " hat das Spiel nach " << anzahl_Zuege << " Zuegen gewonnen.\n";
		Spielverlauf_aus << "_________________________________________________________________\n";

		Spielverlauf_aus.close();
	}
}

void Master_Spielregeln::spielzeichnen_Computer() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür da, dass das Spielfeld gezeichnet wird bzw. "aktualisiert" wird oder bei völliger Gleichheit der beiden Arrays Spieler und Fertige Lösung
	//eine gewonnen Meldung ausgeben


	//===========================================================================================
	//1. Löschen des altes Zustands
	//===========================================================================================

	system("cls");

	//===========================================================================================
	//2. Spielfeld zeichnen
	//===========================================================================================
	//Spielfeld wird gezeichnet, sodass Spieler in jedem Fall den Zwischenstand sieht auch wenn Spiel schon gewonnen

	//zuerst soll Übeschrift gezeichnet werden
	zeichne_Ueberschrift_Spielfeld();

	//um Anzahl der gemachten Züge auszugeben wird interne Methode genutzt
	zeichne_Anzahl_Spielzuege_Computer();

	//Spielfeld anzeigen --> Wichtig: ohne Cursor --> daher wird als Cursor Position -1,-1 genutzt
	Anzeige.zeichneSpielfeld(-1, -1, Computer_Loesung);

	//===========================================================================================
	//3. Prüfung ob Spiel gewonnen
	//===========================================================================================
	//durch interne Methode kann das computer Spielfeld mit der Lösung abgeglichen werden

	if (pruefe_ob_gewonnen(Computer_Loesung) == true) {

		//unter Spielfeld wird kleiner Kasten ausgegeben um Nutzer zu signalisieren das Computer fertig ist
		string einzug = "\t                   ";

		cout << endl;

		//Obere Begrenzung
		cout << endl << endl;
		cout << einzug << (unsigned char)218;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)191 << endl;

		//Inhalt
		cout << einzug << (unsigned char)179 << "  DER COMPUTER HAT DAS SPIEL GELOEST!   " << (unsigned char)179 << endl;

		// Untere Begrenzung
		cout << einzug << (unsigned char)192;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)217 << endl;

		cout << endl;


		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

	}
}

void Master_Spielregeln::baue_Bruecke() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode hat die Aufgabe Bruecken zu bauen, indem die Richtung abgefragt wird und durch eine Such Schleife ein Ziel(Insel) gefunden wird.
	//und dadurch zwischen dem Startpunkt und dem Ziel eine Bruecke gezogen wird
	//Hinweis!!:
	//nicht als eigene Klasse da diese Methode massiv auf die einzelnen Attribute wie Spieler Lösung zugreift und diese verändern muss


	//===========================================================================================
	//1. Position des Cursors prüfen 
	//===========================================================================================
	//nur wenn Cursor auf Position einer Insel steht kann eine Bruecke gebaut werden


	//dafür Koordinate des cursors notwendig --> Getter von Steuerung
	int x_Koordinate_now = Steuerung.get_X_Koordinate_Spielfeld();
	int y_Koordinate_now = Steuerung.get_Y_Koordinate_Spielfeld();

	if ((Spieler_Loesung[y_Koordinate_now][x_Koordinate_now] < '1') || (Spieler_Loesung[y_Koordinate_now][x_Koordinate_now] > '9')) {
		//wenn keine Zahl zwischen 1 & 9 an der Position des Cursors steht, ist der Punkt keine Insel --> keine Brücke kann gebaut werden
		return; //Methode wird daher direkt mit Return abgebrochen

	}
	else {
		//Cursor steht auf Insel --> Bruecke darf gebaut werden
		// erste Idee war es, es mit einem zusätzlichen Attribut zu lösen, welches die letzte Richtung (WASD Eingabe) speichert und diese Richtung für die Orientierung der Brücke nutzt
		// --> Bedienung zu kompliziert daher neue Herangehensweise: Abfragen der Richtung


	//===========================================================================================
	//2. Richtung der Brücke
	//===========================================================================================
	//Abfragen der Richtung durch cout & Eingabe der Richtung (WASD) durch cin


		//-------------------------------------------------------------------------------------------
		// 2a) Richtungsabfrage für die Brücke
		//-------------------------------------------------------------------------------------------
		//sodass das Menü/Spielfeld noch aufgeräumter wirkt soll bei der Abfrage in welche Richtung die Brücke gebaut werden soll, das Spielfeld komplett neu geladen werden und dann nur ein "Brückenbau Menü" angezeigt werden

		system("cls");//dafür wird Spielfeld zuerst gelöscht
		spielzeichnen();//nun wird Spielfeld erneut gezeichnet

		//"Brückenbau-Menü"
		string randabstand = "\t                   ";// Randabstand für die Zentrierung unter Überschrift
		cout << randabstand << (unsigned char)218;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)191 << endl;

		cout << randabstand << (unsigned char)179 << "          RICHTUNG AUSWAEHLEN           " << (unsigned char)179 << endl;
		cout << randabstand << (unsigned char)179 << "    [W] Hoch              [A] Links     " << (unsigned char)179 << endl;
		cout << randabstand << (unsigned char)179 << "    [S] Runter            [D] Rechts    " << (unsigned char)179 << endl;

		cout << randabstand << (unsigned char)192;
		for (int i = 0; i < 40; i++) cout << (unsigned char)196;
		cout << (unsigned char)217 << endl;

		cout << randabstand << " Richtung waehlen: ";

		
		char Bruecke_Richtung = lese_einzelnes_Zeichen(); //für die Eingabe der Richtung wird die Funktion aus menue.h genommen wodurch nur das erste Zeichen zurückgegeben wird
		//--> Falscheingabe/Doppeleingaben werden dadurch abgefangen

		//um Eingabe der Richtung in einen Vektor umzuwandeln nutzung zweier Hilfsvariablen & switch case
		int x_Hilfsvariable = 0;
		int y_Hilfsvariable = 0;

		//!!Hinweis:!!
		//Koordinatensystem ist gedreht, daher ist der Nullpunkt oben links in der Ecke, daher wird genau entgegen der Richtung der Tasteingabe verschoben

		switch (Bruecke_Richtung) { //durch switch case werden die Hilfsvariablen "befüllt"
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

		default: //bei Falscheingaben (nicht WASD) --> Methode soll direkt beendet werden, so muss Spieler keine Bruecke setzen falls er doch nicht mehr will 
			//dennoch Ausgabe des Fehler Menü sodass Spieler weiß was er falsch gemacht hat

			// "Fehler-Kasten"
			string randabstand = "\t                   ";

			cout << randabstand << (unsigned char)218;
			for (int i = 0; i < 40; i++) cout << (unsigned char)196;
			cout << (unsigned char)191 << endl; // Oben-Rechts

			
			cout << randabstand << (unsigned char)179 << "          UNGUELTIGE EINGABE!           " << (unsigned char)179 << endl;
			cout << randabstand << (unsigned char)179 << "    Nur [W], [A], [S], [D] erlaubt!     " << (unsigned char)179 << endl;

			cout << randabstand << (unsigned char)192;
			for (int i = 0; i < 40; i++) cout << (unsigned char)196;
			cout << (unsigned char)217 << endl;

			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

			return;//Abbruch der Methode Bruecke bauen
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

		// da Insel auf der Cursor steht bereits bekannt ist, kann der nächste Punkt überprüft werden daher wird Einheitsvektor direkt addiert
		int X_Such = x_Koordinate_now + x_Hilfsvariable;
		int Y_Such = y_Koordinate_now + y_Hilfsvariable;


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

			if ((Spieler_Loesung[Y_Such][X_Such] >= '1') && (Spieler_Loesung[Y_Such][X_Such] <= '9')) {
				// wenn eine Zahl im Array Platz steht --> Insel
				ziel_gefunden = true; // Ziel (Insel) wurde gefunden daher kann in Abhängigkeit dieser boolschen Variable eine Brücke gebaut werden
				break; //(Such-)Schleife wird abgebrochen da ziel gefunden ist
			}


			//=====================Fall B: Hindernisse in Form anderer Brücken=====================

			else {
				//durch Eingabe der Bruecken-Richtung gibt es zwei Fälle welche durch eine If-Bedingung überprüft wird

				if ((Bruecke_Richtung == 'W') || (Bruecke_Richtung == 'w') || (Bruecke_Richtung == 'S') || (Bruecke_Richtung == 's')) {
					// Brücke wird vertikal gebaut --> daher darf keine horizontale Brücke " in die Quere kommen"
					if ((Spieler_Loesung[Y_Such][X_Such] == Horizontal_Einfach)||(Spieler_Loesung[Y_Such][X_Such] == Horizontal_Doppelt)) {
						break; //wenn dem so ist, wird Schleife beendet
					}
				}
				else {
					//Brücke wird horizontal gebaut --> daher darf keine vertikale Brücke " in die Quere kommen"
					if ((Spieler_Loesung[Y_Such][X_Such] == Vertikal_Einfach)|| (Spieler_Loesung[Y_Such][X_Such]== Vertikal_Doppelt)) {
						break; //wenn dem so ist, wird Schleife beendet
					}
				}
			}
			//"Sucher" Startkoordinaten müssen eine Koordinate weiterspringen, sodass nächstes Feld gecheckt werden kann
			X_Such = X_Such + x_Hilfsvariable;
			Y_Such = Y_Such + y_Hilfsvariable;
		}//schlussendlich sind die x/y_Such die Ziel Koordinaten der gesuchten Insel (werden so lange aufaddiert bis Ziel erreicht ist oder Hindernis kommt)

	//===========================================================================================
	//4. Bau der Bruecken
	//===========================================================================================
	//wenn Ziel gefunden wurde soll Brücke zwischen der Start Insel und der Ziel Insel gebaut werden

		//ziel gefunden welches auf true gestellt wurde wenn Insel (Ziel) gefunden wurde, wird überprüft
		//wenn ziel gefunden ist kann Bruecke gebaut werden
		if (ziel_gefunden == true) {

			anzahl_Zuege++; //beim Bauen/Löschen einer Brücke wird ein weiterer Zug genutzt --> Erhöhung des Attributs anzahl_Zuege	


			//-------------------------------------------------------------------------------------------
			// 4a) Startpunkt für Bau
			//-------------------------------------------------------------------------------------------
			//Startpunkt sind die x/y Koordinaten des cursor welche durch die Getter bereitgestellt wurden + einmal die Richtung
			// --> dadurch wird nicht schon auf Start Insel eine Brücke gezogen und damit die Insel überschrieben sondern erst ein Feld weiter 

			int X_Bau = x_Koordinate_now + x_Hilfsvariable;
			int Y_Bau = y_Koordinate_now + y_Hilfsvariable;

			//-------------------------------------------------------------------------------------------
			// 4b) Bau-Schleife
			//-------------------------------------------------------------------------------------------
			//Schleife läuft solange bis die Bau Koordinaten identisch mit der Insel sind, Schleife wird daher davor aufhören sodass Ziel Insel nicht überschrieben wird
			//Endpunkte sind X/Y_Such Koordinaten


			//sodass bei der späteren Log_DAtei einfacher ein String erzeugt werden kann welcher dann eingefügt werden kann
			//Nutzung einer boolschen_Variablen welche bei der jeweiligen Brückenwahl auf true umschaltet und später geprüft werden kann

			bool vertikale_einfache_Bruecke = false;
			bool vertikale_doppelte_Bruecke = false;
			bool horizontale_einfache_Bruecke = false;
			bool horizontale_doppelte_Bruecke = false;
			bool Bruecke_entfernt = false;


			while ((X_Bau != X_Such) || (Y_Bau != Y_Such)) {

				//Fehlermeldung/Hinweistext --> deswegen If-Bedingung mit Pufferüberlauf
				//Pufferüberlauf muss verhindert werden (X/Y Such dürfen nicht über die Array Grenzen hinaus laufen)
				if ((X_Bau < 0) || (X_Bau >= ARRAY_MAX_GROESSE) || (Y_Bau < 0) || (Y_Bau >= ARRAY_MAX_GROESSE)) {
					break;
				} // falls die Koordinaten über die Grenzen hinaus laufen wird die (Such) Schleife sofort beendet


				//=====================Fall A: Vertikale Richtung=====================

				if ((Bruecke_Richtung == 'W') || (Bruecke_Richtung == 'w') || (Bruecke_Richtung == 'S') || (Bruecke_Richtung == 's')) {
					//wenn Bruecke_Richtung vertikal werden vertikale Brücken gesetzt
					//Nutzung eines "Kreislaufs": Feld leer --> eine Linie --> zwei Linien --> Feld leer

					
					//wenn kein Zeichen in dem Array Feld ist, zeichne einfache Linie
					if (Spieler_Loesung[Y_Bau][X_Bau] == ' ') {
						Spieler_Loesung[Y_Bau][X_Bau] = Vertikal_Einfach;//Bauen

						vertikale_einfache_Bruecke = true; //spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
					//ist bereits einfache Linie gezogen, überschreibe den Inhalt mit einer Doppellinie
					else if ((unsigned char)Spieler_Loesung[Y_Bau][X_Bau] == Vertikal_Einfach) {
						Spieler_Loesung[Y_Bau][X_Bau] = Vertikal_Doppelt;

						vertikale_doppelte_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
					//ist bereits Doppellinie gezogen, lösche den Inhalt durch Überschreibung mit Leerzeichen
					else if ((unsigned char)Spieler_Loesung[Y_Bau][X_Bau] == Vertikal_Doppelt) {
						Spieler_Loesung[Y_Bau][X_Bau] = ' ';//lösche Inhalt und ersetze durch Leerzeichen

						Bruecke_entfernt = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
				}

				//=====================Fall B: Horizontale Richtung=====================

				else {
					//wenn Breucken_Richtung horizontal werden horizontale Bruecken gesetzt

					//wenn kein Zeichen in dem Array Feld ist, zeichne einfache Linie
					if (Spieler_Loesung[Y_Bau][X_Bau] == ' ') {
						Spieler_Loesung[Y_Bau][X_Bau] = Horizontal_Einfach;//Bauen

						horizontale_einfache_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
					//ist bereits einfache Linie gezogen, überschreibe den Inhalt mit einer Doppellinie
					else if ((unsigned char)Spieler_Loesung[Y_Bau][X_Bau] == Horizontal_Einfach) {
						Spieler_Loesung[Y_Bau][X_Bau] = Horizontal_Doppelt;

						horizontale_doppelte_Bruecke = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
					//ist bereits Doppellinie gezogen, lösche den Inhalt durch Überschreibung mit Leerzeichen
					else if ((unsigned char)Spieler_Loesung[Y_Bau][X_Bau] == Horizontal_Doppelt) {
						Spieler_Loesung[Y_Bau][X_Bau] = ' ';//lösche Inhalt und ersetze durch Leerzeichen

						Bruecke_entfernt = true;//spätere Abfrage welche Bruecke gesetzt wurde für log datei um string zu erzeugen
					}
				}
				//"Bau"-Koordinaten müssen eine Koordinate weiterspringen, sodass im nächsten Feld gebaut werden kann
				X_Bau = X_Bau + x_Hilfsvariable;
				Y_Bau = Y_Bau + y_Hilfsvariable;
			}

			//===========================================================================================
			//5. Inhalt für Log Datei erstellen und integrieren
			//===========================================================================================
			//da es zu aufwändig wäre die Koordinaten welche integer sind in string durch bspw. switch case umzuwandeln wird die Aktion des Spielers direkt in die Log Datei geschrieben


			//-------------------------------------------------------------------------------------------
			// 5a) Start- & Zielkoordinaten zwischenspeichern
			//-------------------------------------------------------------------------------------------
			//die einzelnen Start- & Zielkoordinaten werden hier nochmal zwischengespeichert, sodass eine bessere Übersichtlichkeit gewährleistet ist

			//Startkoordinaten --> (Start-Insel)
			int Start_Insel_X_Log = x_Koordinate_now;
			int Start_Insel_Y_Log = y_Koordinate_now;

			//Zielkoordinaten --> (Ziel-Insel)
			int Ziel_Insel_X_Log = X_Bau;
			int Ziel_Insel_Y_Log = Y_Bau;


			//-------------------------------------------------------------------------------------------
			// 5b) Log-Datei wird erweitert 
			//-------------------------------------------------------------------------------------------
			//durch boolsche Variablen, welche angeben welche Linienart gewählt wurde, wird ein String angefertigt und dieser mit weiteren Elementen in die Log DAtei geschrieben


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
			Spielverlauf_aus << anzahl_Zuege << ".Zug: " << welche_Bruecke << "(" << Start_Insel_X_Log << "|" << Start_Insel_Y_Log << ")" " und der Insel (" << Ziel_Insel_X_Log << "|" << Ziel_Insel_Y_Log << ").\n";
			// Log Datei schließen
			Spielverlauf_aus.close();
		}
	}
}

void Master_Spielregeln::wandle_Fertige_Loesung_um() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Methode soll durch die Spielgenerator Methode ein komplett gelöstes Haschi Game in dem Array Fertige Lösung erzeugen
	//zusätzlich soll das Spielfeld für den Spieler & Computer erstellt werden indem lediglich die Inseln vom Array Fertige Lösung übernommen werden


	//===========================================================================================
	//1. Erstellung des Games im Array Fertige Lösung
	//===========================================================================================
	//dafür wird der Methode vom Spielgenerator die einzelnen Attribute übergeben

	Haschi_Game_Generator.generiere_Spiel(Fertige_Loesung, gewaehltes_Format, schwierigkeit);
	//--> komplettes Spiel mit Inseln und Bruecken ist in Fertiger Lösung gespeichert


	//===========================================================================================
	//2. Übertragung der Inseln
	//===========================================================================================
	// in fertiger Lösung steht nun das komplette Game davon müssen nun die Inseln übertragen werden


	//durch zwei for Schleifen wird jede einzelne Stelle des Fertige Lösung Arrays durchgegangen
	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {

			//es muss an einer Insel genau eine Brücke angreifen und maximal 8 Brücken können angreifen --> Prüfraum: zwischen 1 und 8
			//wenn das Zeichen zwischen 1 und 8 liegt wird das Zeichen in das Spielfeld übertragen
			if ((Fertige_Loesung[i][j] >= '1') && (Fertige_Loesung[i][j] <= '8')) {
				Start_Spielfeld[i][j] = Fertige_Loesung[i][j];
			}
			else { // wenn Zeichen nicht zwischen 1 und 8 liegt wird Zeichen nicht genommen und ein Leerzeichen eingefügt
				Start_Spielfeld[i][j] = ' ';
			}
		}
	}
}

bool Master_Spielregeln::pruefe_ob_gewonnen(char ziel_Array[ARRAY_MAX_GROESSE][ARRAY_MAX_GROESSE]) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//die Methode ist verantwortlich dass die Arrays Fertige_Lösung und das übergebene Array auf Gleichheit untersucht werden
	//falls beide identisch wird true zurückgegeben sonst false


	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			//beide Schleifen durchlaufen jede Position des Arrays aber nur in gewähltem Format da der Restliche Müll (die Leerzeichen welche durch die Konstruktoren festgelegt sind sowieso identisch) irrelevant ist

			// wenn ein ungleicher Inhalt enthalten ist werden die Schleifen direkt beendet
			if (ziel_Array[i][j] != Fertige_Loesung[i][j]) {
				return false;
			}
		}
	}
	// Schleifen sind komplett durchgelaufen daher sind die Arrays identisch --> damit hat der Spieler/Computer gewonnen
	return true;
}

void Master_Spielregeln::schreibe_Log_Datei(string Aktion) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist verantwortlich dafür, dass ein string welcher zuvor erstellt wurde und übergeben wurde in die Log-DAtei geschrieben wird

	//durch den Append Modus wird die Datei nicht gelöscht sondern überschrieben
	ofstream Spielverlauf_aus;
	Spielverlauf_aus.open("Spielverlauf", ios::app);

	if (!Spielverlauf_aus) {
		cout << "Datei konnte nicht geöffnet werden!\n";
		return;
	}
	Spielverlauf_aus << Aktion << endl;

	Spielverlauf_aus.close();
}

bool Master_Spielregeln::hat_Computer_gewonnen() {
	//Methoden funktionieren wie getter --> diese melden der Spielverwaltung zurück ob der jeweilige Spieler/Computer gewonnen hat
	return pruefe_ob_gewonnen(Computer_Loesung);
}

bool Master_Spielregeln::hat_Spieler_gewonnen() {
	//Methoden funktionieren wie getter --> diese melden der Spielverwaltung zurück ob der jeweilige Spieler/Computer gewonnen hat
	return pruefe_ob_gewonnen(Spieler_Loesung);
}

void Master_Spielregeln::vorbereiten_Computer_Durchlauf() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür verantwortlich dass das Array Start Spielfeld mit nur Inseln in das Computer Array kopiert wird
	//--> dadurch hat Computer und Spieler eigene Arrays wodurch diese getrennt genutzt werden können
	//zusätzlich wird der Computer.Löser initialisiert (Anzahl der Inseln und deren Koordinaten werden in die jeweiligen Register Arrays gespeichert
	 
	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			Computer_Loesung[i][j] = Start_Spielfeld[i][j];
		}
	}
	Computer_Loeser.initialisiere_Loeser(Computer_Loesung);
	anzahl_Zuege_Computer = 0;
}

void Master_Spielregeln::vorbereiten_Spieler_Durchlauf() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode kopiert das Start Spielfeld Array in welchem nur die Insel gespeichert sind in das Spieler Loesung Array

	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			Spieler_Loesung[i][j] = Start_Spielfeld[i][j];
		}
	}
}

void Master_Spielregeln::starte_Computer_Durchlauf() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist dafür verantwortlich dass der Computer Durchlauf gestartet werden kann

	//Aufrufen der internen Methode um den Computer Durchlauf vorzubereiten
	vorbereiten_Computer_Durchlauf();

	//Spielfeld wird einmal leer ohne Brücken gezeigt
	spielzeichnen_Computer();

	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde


	//Schleife soll so lange laufen bis der Computer das Spiel gelöst hat
	while (pruefe_ob_gewonnen(Computer_Loesung) == false) {

		//dabei muss immer geprüft werden ob der Computer noch weitere Züge machen kann oder nicht
		if (Computer_Loeser.baue_EINE_Bruecke(Computer_Loesung) == true) {

			anzahl_Zuege_Computer++; //wenn Methode baue eine Bruecke true zurückgemeldet hat --> Computer hat einen zug gemacht --> anzahl der Züge muss erhöht werden

			//zusätzlich muss das Spielfeld gezeichnet werden
			spielzeichnen_Computer();


			//unter Spielfeld wird kleiner Kasten ausgegeben um Nutzer zu signalisieren das Computer einen Zug gemacht hat
			//--> dieser Kasten wird aber nur ausgegeben wenn das Spiel nicht schon gewonnen war --> beim Siegeszug soll die Nachricht nicht ausgegeben werden
			if (hat_Computer_gewonnen() == false) {
				string einzug = "\t                   ";

				cout << endl;

				//Obere Begrenzung
				cout << endl << endl;
				cout << einzug << (unsigned char)218;
				for (int i = 0; i < 40; i++) cout << (unsigned char)196;
				cout << (unsigned char)191 << endl;

				//Inhalt
				cout << einzug << (unsigned char)179 << "      Computer hat Zug ausgefuehrt      " << (unsigned char)179 << endl;

				// Untere Begrenzung
				cout << einzug << (unsigned char)192;
				for (int i = 0; i < 40; i++) cout << (unsigned char)196;
				cout << (unsigned char)217 << endl;

				cout << endl << einzug << "[Enter] Naechster Zug...";

				warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
			}
			//wenn Computer gewonnen hat, wird if Bedingung übersprungen und Schleife endet danach
		}
		else {//wenn der Computer keine weiteren Züge mehr machen kann

			spielzeichnen_Computer();

			//unter Spielfeld wird kleiner Kasten ausgegeben um Nutzer zu signalisieren das Computer keine weiteren Züge mehr machen kann
			string einzug = "\t                   ";

			cout << endl;

			//Obere Begrenzung
			cout << endl << endl;
			cout << einzug << (unsigned char)218;
			for (int i = 0; i < 40; i++) cout << (unsigned char)196;
			cout << (unsigned char)191 << endl;

			//Inhalt
			cout << einzug << (unsigned char)179 << "    Computer findet keine Zuege mehr    " << (unsigned char)179 << endl;
			// Untere Begrenzung
			cout << einzug << (unsigned char)192;
			for (int i = 0; i < 40; i++) cout << (unsigned char)196;
			cout << (unsigned char)217 << endl;

			cout << endl << einzug << "[Enter] Naechster Zug...";

			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde


			// ===========================================================================================
			// Log-Datei muss angepasst werden wenn Computer keine weiteren Züge mehr findet
			// ===========================================================================================
			string Trennstreifen = "_________________________________________________________________\n";
			string aufgegeben = Trennstreifen + "Der Computer hat das Duell vorzeitig abgebrochen\n" + Trennstreifen;

			schreibe_Log_Datei(aufgegeben);


			break;//wenn compiler hier ankommt hat der "Algorhytmus keine Züge mehr gefunden --> Schleife muss abgebrochen werden
		}
	}
}

void Master_Spielregeln::zeichne_Ueberschrift_Spielfeld() {
	string randabstand = "\t"; // Randabstand für die Zentrierung

	cout << endl << endl;
	cout << randabstand << " #   #   ###    ####  #   #  ### " << randabstand << " #   #   ###    ####  ##### ##### ####  " << endl;
	cout << randabstand << " #   #  #   #  #      #   #   #  " << randabstand << " ## ##  #   #  #        #   #     #   # " << endl;
	cout << randabstand << " #####  #####   ###   #####   #  " << randabstand << " # # #  #####   ###     #   ####  ####  " << endl;
	cout << randabstand << " #   #  #   #      #  #   #   #  " << randabstand << " #   #  #   #      #    #   #     #  #  " << endl;
	cout << randabstand << " #   #  #   #  ####   #   #  ### " << randabstand << " #   #  #   #  ####     #   ##### #   # " << endl;
	cout << endl << endl;
}

void Master_Spielregeln::zeichne_Anzahl_Spielzuege_Spieler() {
	string randabstand = "\t               "; // Randabstand für die Zentrierung unter Überschrift

	//obere Begrenzung
	cout << randabstand << (unsigned char)218;
	for (int i = 0; i < 50; i++) cout << (unsigned char)196;
	cout << (unsigned char)191 << endl;

	// Inhalt der Leiste
	//da der Name nicht immer gleich lang ist wird setw(25) genutzt --> wenn der name nur 5 Zeichen lang ist wird der Rest durch die Funktion setw() mit Leerzeichen, nämlich 25 - 5 = 20 Leerzeichen aufgefüllt
	//Name kann nicht länger als 25 Zeichen sein da er davor in der Funktion erfrage_Name überprüft und im Zweifelsfall angepasst wurde
	cout << randabstand << (unsigned char)179 << " SPIELER: " << left << setw(25) << spielername << " |  ZUEGE: " << right << setw(3) << anzahl_Zuege << " " << (unsigned char)179 << endl;



	// Untere Begrenzung
	cout << randabstand << (unsigned char)192;
	for (int i = 0; i < 50; i++) cout << (unsigned char)196;
	cout << (unsigned char)217;

}

void Master_Spielregeln::zeichne_Anzahl_Spielzuege_Computer() {

	string randabstand = "\t               "; // Randabstand für die Zentrierung

	// Obere Begrenzung 
	cout << randabstand << (unsigned char)218;
	for (int i = 0; i < 50; i++) cout << (unsigned char)196;
	cout << (unsigned char)191 << endl;

	// Inhalt 

	cout << randabstand << (unsigned char)179 << " MODUS:   " << left << setw(25) << "COMPUTER-SOLVER" << " |  ZUEGE: " << right << setw(3) << anzahl_Zuege_Computer << " " << (unsigned char)179 << endl;

	// Untere Begrenzung
	cout << randabstand << (unsigned char)192;
	for (int i = 0; i < 50; i++) cout << (unsigned char)196;
	cout << (unsigned char)217 << endl;
}

void Master_Spielregeln::zeichne_Vergleich_Statistik() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode sorgt dafür dass der  Spieler am Ende seines Duells eine Auswertung erhält wer gewonnen hat (Computer oder Spieler)

	bool mensch_Erfolg = hat_Spieler_gewonnen();
	bool computer_Erfolg = hat_Computer_gewonnen();

	//für Log DAtei sind passende Strings vorbereitet
	string Trennstreifen = "_________________________________________________________________\n";
	string Abgrenzung = "=================================================================\n";


	system("cls");//bildschirm muss zuerst gelöscht werden

	string abstand = "      ";
	string randabstand = "\t                   ";

	cout << endl << endl << endl;
	// Obere Begrenzung
	cout << randabstand << (unsigned char)201;
	for (int i = 0; i < 40; i++) cout << (unsigned char)205;
	cout << (unsigned char)187 << endl;

	//Inhalt
	cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
	cout << randabstand << (unsigned char)186 << "            DUELL - Ergebnis            " << (unsigned char)186 << endl;
	cout << randabstand << (unsigned char)186 << "          Computer vs. Spieler          " << (unsigned char)186 << endl;
	cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
	cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;


	//der Spieler hat gewonnen && Computer hat aufgegeben
	if ((mensch_Erfolg == true) && (computer_Erfolg == false)) {
		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "             !!KI gab auf!!             " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << spielername << "       " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       Zuege gesamt: " << left << setw(3) << anzahl_Zuege << "                " << (unsigned char)186 << endl;

		//LOG-DATEI
		//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

		ofstream Spielverlauf_aus;
		Spielverlauf_aus.open("Spielverlauf", ios::app);

		if (!Spielverlauf_aus) {
			cout << "Datei konnte nicht geöffnet werden!\n";
			return;
		}

		Spielverlauf_aus << Trennstreifen << "Der Spieler " << spielername << " hat das Spiel gewonnen da die KI aufgab!\n" << Abgrenzung;

		//Log schließen
		Spielverlauf_aus.close();

	}
	//der Computer hat gewonnen && Spieler hat aufgegeben
	else if ((mensch_Erfolg == false) && (computer_Erfolg == true)) {
		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "         !!COMPUTER GEWONNEN!!          " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << "COMPUTER" << "       " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       Zuege gesamt: " << left << setw(3) << anzahl_Zuege_Computer << "                " << (unsigned char)186 << endl;

		//LOG-DATEI
		//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

		ofstream Spielverlauf_aus;
		Spielverlauf_aus.open("Spielverlauf", ios::app);

		if (!Spielverlauf_aus) {
			cout << "Datei konnte nicht geöffnet werden!\n";
			return;
		}

		Spielverlauf_aus << Trennstreifen << "Der Computer hat das Spiel gewonnen da der Spieler aufgab!\n" << Abgrenzung;

		//Log schließen
		Spielverlauf_aus.close();

	}
	//beide haben gewonnen --> Vergleich Zahl der Züge
	else if ((mensch_Erfolg == true) && (computer_Erfolg == true)) {
		//Computer hatte weniger Züge --> Sieg
		if (anzahl_Zuege > anzahl_Zuege_Computer) {
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "           !!BEIDE GELOEST!!            " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       KI BRAUCHTE WENIGER ZUEGE        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << "COMPUTER" << "       " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       Zuege gesamt: " << left << setw(3) << anzahl_Zuege_Computer << "                " << (unsigned char)186 << endl;

			//LOG-DATEI
			//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

			ofstream Spielverlauf_aus;
			Spielverlauf_aus.open("Spielverlauf", ios::app);

			if (!Spielverlauf_aus) {
				cout << "Datei konnte nicht geöffnet werden!\n";
				return;
			}

			Spielverlauf_aus << Trennstreifen << "Der Computer und der Spieler " << spielername << "konnten das Spiel erfolgreich loesen\n!!Der Computer hat aufgrund weniger Spielzuege ( " << anzahl_Zuege_Computer << " gewonnen!!\n" << Abgrenzung;

			//Log schließen
			Spielverlauf_aus.close();
		}
		//Spieler hatte weniger Züge --> Sieg
		else if (anzahl_Zuege_Computer > anzahl_Zuege) {
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "           !!BEIDE GELOEST!!            " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "      DU BRAUCHTEST WENIGER ZUEGE       " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << spielername << "       " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       Zuege gesamt: " << left << setw(3) << anzahl_Zuege << "                " << (unsigned char)186 << endl;


			//LOG-DATEI
			//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

			ofstream Spielverlauf_aus;
			Spielverlauf_aus.open("Spielverlauf", ios::app);

			if (!Spielverlauf_aus) {
				cout << "Datei konnte nicht geöffnet werden!\n";
				return;
			}

			Spielverlauf_aus << Trennstreifen << "Der Computer und der Spieler " << spielername << "konnten das Spiel erfolgreich loesen\n!!Der Spieler ( " << anzahl_Zuege << ") hat aufgrund weniger Spielzüge gewonnen!!\n" << Abgrenzung;

			//Log schließen
			Spielverlauf_aus.close();
		}
		//beide hat gleich viel Züge
		else {
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "           !!BEIDE GELOEST!!            " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "   BEIDE BRAUCHTEN GLEICH VIELE ZUEGE   " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << "UNENTSCHIEDEN" << "       " << (unsigned char)186 << endl;
			cout << randabstand << (unsigned char)186 << "       Zuege gesamt: " << left << setw(3) << anzahl_Zuege << "                " << (unsigned char)186 << endl;


			//LOG-DATEI
			//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

			ofstream Spielverlauf_aus;
			Spielverlauf_aus.open("Spielverlauf", ios::app);

			if (!Spielverlauf_aus) {
				cout << "Datei konnte nicht geöffnet werden!\n";
				return;
			}

			Spielverlauf_aus << Trennstreifen << "Der Computer und der Spieler " << spielername << "konnten das Spiel erfolgreich lösen\n!!Der Spieler und der Computer haben gleich viele Zuege (" << anzahl_Zuege << ") gebraucht--> Unentschieden\n" << Abgrenzung;

			//Log schließen
			Spielverlauf_aus.close();

		}
	}
	//keiner hat gewonnen
	else {

		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "        !!KEINER HAT GELOEST!!          " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "      BEIDE HABEN AUFGEGEBEN...         " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "                                        " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       SIEGER: " << left << setw(18) << "NIEMAND" << "       " << (unsigned char)186 << endl;
		cout << randabstand << (unsigned char)186 << "       Zuege gesamt: ---                " << (unsigned char)186 << endl;

		//LOG-DATEI
			//es wird direkt in Log DAtei geschrieben um Anzahl der Zuege (int) nicht umwandeln zu müssen (string)

		ofstream Spielverlauf_aus;
		Spielverlauf_aus.open("Spielverlauf", ios::app);

		if (!Spielverlauf_aus) {
			cout << "Datei konnte nicht geöffnet werden!\n";
			return;
		}

		Spielverlauf_aus << Trennstreifen << "Der Computer und der Spieler konnten beide das Spiel nicht lösen\n" << Abgrenzung;

		//Log schließen
		Spielverlauf_aus.close();

	}

	// Untere Begrenzung
	cout << randabstand << (unsigned char)200;
	for (int i = 0; i < 40; i++) cout << (unsigned char)205;
	cout << (unsigned char)188 << endl;
}

//====================================================================================
// nachfolgende Methode im normalen Spielbetrieb in Spiel Verwaltung auskommentiert
//====================================================================================
void Master_Spielregeln::zeige_Loesung() {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//diese Methode ist im normalen Spielbetrieb auskommentiert
	//zum testen ist die Methode sehr relevant 
	//diese zeigt die Fertige Lösung mit allen Brücken und Inseln an
	//so müssen komplizierte Haschi Spiele nicht langwierig gespielt werden sondern es kann direkt auf die korrekte Funktionsweise geschlossen werden

	system("cls");
	cout << "Achtung Lösung\n";

	for (int i = 0; i < gewaehltes_Format; i++) {
		for (int j = 0; j < gewaehltes_Format; j++) {
			// Wir geben das Zeichen aus, gefolgt von einem Leerzeichen für die Optik
			cout << Fertige_Loesung[i][j] << " ";
		}
		cout << endl;
	}
	cout << "\nDruecken Sie eine Taste, um das Spiel zu starten (Loesung verschwindet)..." << endl;
}