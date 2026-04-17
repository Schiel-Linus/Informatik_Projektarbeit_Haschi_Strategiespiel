
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Spiel_Verwaltung.cpp
// BESCHREIBUNG: Implementierung der Spielverwaltung
//               Steuert den Programmablauf, die Navigation 
//               zwischen Menüs und die Spielmodus-Logik
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel & Emil Kern
// VERSION:      v1.0.0 (Final)
// DATUM:        19.01.2026
// =========================================================


#include "Spiel_Verwaltung.h"
using namespace std;


Spiel_Verwaltung::Spiel_Verwaltung() {
	//festlegen von Standardwerten --> diese werden später angepasst
	spielername = "Unbekannt";
	gewaehltes_Format = 23;
	schwierigkeit = 1;
}

void Spiel_Verwaltung::Hauptmenue() {
	//einmalige Begrüßung beim Programmstart
	zeige_Begruessung();
	int auswahl_int;
	char auswahl_char;

	//Nutzung einer do while Schleife sodass Nutzer immer im Menü bleibt
	do {
		//zuerst muss Bildschirm gelöscht werden
		system("cls");

		//dann wird die Funktion zeige_Hauptmenue aus der Header Datei menue aufgerufen
		zeige_Hauptmenue();

		auswahl_char = lese_einzelnes_Zeichen(); //durch diese Funktion können mehrere Zeichen eingegeben werden es wird aber nur das erste Zeichen beachtet
        
        //da Zeichen in char vorliegt aber in int benötigt wird --> Umwandlung von Zeichen in Zahl
        // '1' hat ASCII-Wert 49, '0' hat 48 --> 49 - 48 = 1
		auswahl_int = auswahl_char - '0';

		switch (auswahl_int) {
		case (1)://anzeigen der Regeln
			zeige_Regeln_mit_Menue();
			break;
		case(2)://Testspiel
			starte_Testspiel_();
			break;
		case(3)://Solo Modus
			starte_Solo_Modus();
			break;
		case(4):
			starte_Duell_Modus_();
			break;
		case(5):
			break;//auch wenn Case 5 das Menü beendet wird es in den Cases berücksichtigt
		default:
			cout << "";
		}

	} while (auswahl_int != 5);

	zeichne_Abschluss_Banner();
}

void Spiel_Verwaltung::zeige_Regeln_mit_Menue() {

	int auswahl;
	//zuerst werden Regeln einmal angezeigt
	zeige_Regeln();


	do {
		system("cls");

		//durch ein Untermenü kann passende Kategorie ausgewählt werden
		zeichne_Tutorial_Menue();

		cin >> auswahl;

		switch (auswahl) {
		case (1):
			zeige_Regeln();
			break;
		case(2):
			starte_Testspiel_();
			break;
		case(3):
			break;

		default:
			break;
		}

	} while (auswahl != 3); //bei 3 wird Schleife beendet
}

void Spiel_Verwaltung::zeige_Regeln() {

	string Randabstand = "\t";
	
	zeichne_erste_Regel();
	cout << "\n" << Randabstand << "[Enter] Weiter....";

	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
	

	zeichne_zweite_Regel();
	cout << "\n" << Randabstand << "[Enter] Weiter....";
	
	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

	zeichne_dritte_Regel();
	cout << "\n" << Randabstand << "[Enter] Weiter....";
	
	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

	zeichne_vierte_Regel();
	cout << "\n" << Randabstand << "[Enter] Weiter....";
	
	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

	zeichne_fuenfte_Regel();
	cout << "\n" << Randabstand << "[Enter] Weiter....";
	
	warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
}

void Spiel_Verwaltung::starte_Solo_Modus() {

	//als erstes wird Name benötigt
	spielername = erfrage_Name();

	//dann wird Schwierigkeitsgrad benötigt
	schwierigkeit = erfrage_Schwierigkeit();

	//dann Spielfeldgröße
	gewaehltes_Format = erfrage_Spielfeldgroesse();

	//diese WErte werden genutzt um die Funktion mit parametrisierten Konstruktor aus Master Spielregeln zu starten
	direkter_Spielstart_Spieler();
}

void Spiel_Verwaltung::direkter_Spielstart_Spieler() {

	//mit den zuvor erlangten Daten kann Spiel nun erstellt werden --> parametrisierter Konstruktor von Master Spielregeln wird aufgerufen
	Master_Spielregeln meinSpiel(gewaehltes_Format, schwierigkeit, spielername);

	//Hinweis!!: im Spielbetrieb auskommentiert --> zeigt zuvor erzeugte Lösung an
	/*
	meinSpiel.zeige_Loesung();
	system("pause");
	*/

	meinSpiel.spielzeichnen();//Spiel wird einmalig gezeichnet --> Spieler benötigt Spielfeld um nicht blind Zug machen zu müssen
	char eingabe;

	//Spiel-Schleife
	do {

		zeichne_Steuerungs_Kasten();//Hilfe Kasten aus menue.h integrieren

		eingabe = lese_einzelnes_Zeichen();

		meinSpiel.eingabe_verarbeiten(eingabe);

		if (meinSpiel.hat_Spieler_gewonnen() == true) {
			cout << "\t                    [Enter] Weiter....";

			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

			break; //da Spiel gewonnen kann Schleife verlassen werden
		}
	} while (eingabe != 'x'); // Abbruch durch Spieler


	//Log Dateie Ende schreiben
	//wenn der Compiler hier ankommt ist hat der Spieler entweder gewonnen oder das Spiel abgebrochen
	//wenn Spiel gewonnen wird der Text für die Log DAtei direkt in Master Spielregeln geschrieben
	if (meinSpiel.hat_Spieler_gewonnen() == false) {//wenn Spiel nicht gewonnen hat der Spieler das Spiel abgebrochen

		ofstream Spielverlauf_aus;
		Spielverlauf_aus.open("Spielverlauf", ios::app);


		if (!Spielverlauf_aus) {
			cout << "Datei konnte nicht geöffnet werden!\n";
			return;
		}
		string Spielername = spielername;
		int Anzahl_Zuege = meinSpiel.get_anzahl_Zuege();
		Spielverlauf_aus << "_________________________________________________________________\n";
		Spielverlauf_aus << "Spieler: " << Spielername << " hat nach " << Anzahl_Zuege << " Zuegen das Spiel beendet\n";
		Spielverlauf_aus << "_________________________________________________________________\n";
	}
	//Spieler hat Möglichkeit Inhalt der Log DAtei angezeigt zu bekommen
	if (frage_log_anzeigen() == true) {//Spieler möchte den Inhalt der Log DAtei angezeigt bekommen
		//ifstream wird zum lesen der Datei genutzt
		ifstream log_datei_lesen("Spielverlauf");

		

		if (log_datei_lesen) {
			string zeile;
			system("cls");
			cout << "\n\t--- SPIELPROTOKOLL ANFANG ---\n";

			// getline liest Datei Zeile für Zeile bis zum Ende
			while (getline(log_datei_lesen, zeile)) {
				cout <<"\t" << zeile << endl;
			}

			cout << "\t--- SPIELPROTOKOLL ENDE ---\n";
			log_datei_lesen.close();
		}
		else {
			cout << "Fehler: Protokoll konnte nicht geladen werden.\n";
		}

		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

	}
	

	//Spieler hat Möglichkeit ein neues Spiel mit gleichen Parametern (Schwierigkeitsgrad,...) direkt zu starten ohne ins Menü zu müssen
	if (frage_neues_Spiel() == true) {
		//wenn Spieler ein neues Spiel möchte wird nochmals die Funktion aufgerufen
		direkter_Spielstart_Spieler();
	}
}

void Spiel_Verwaltung::starte_Testspiel_() {


	//Spieler kann Attribute jetzt nicht mehr selbst anpassen sondern diese sind schon vor eingestellt

	schwierigkeit = 0;
	gewaehltes_Format = 13;
	spielername = "Lehrling";

	//interne Methode kann direkt gestartet werden
	direkter_Spielstart_Spieler();
}

void Spiel_Verwaltung::starte_Duell_Modus_() {
	//zuerst werden Parameter für Spielerstellung erfragt
	spielername = erfrage_Name();
	schwierigkeit = erfrage_Schwierigkeit();
	gewaehltes_Format = erfrage_Spielfeldgroesse();


	//sodass Duell nochmal gestartet werden könnte wird do while Schleife genutzt
	char nochmal;

	do {
		Master_Spielregeln meinSpiel(gewaehltes_Format, schwierigkeit, spielername);


		//um auch das Duell in einer Log DAtei mitzuschreiben muss die Log DAtei erstmal angepasst werden, denn beim starten des parametrisierten Konstruktor Master Spielregeln wird sofort eine Log DAtei
		//mit DAten welche zum Solo Spiel passen beschrieben --> um das zu löschen und für das Duell anzupassen wird die log datei überschreiben 

		//basiert auf dem Prinzip des vorgehen mit der log datei im parametrisierten Konstruktor

		// 1. Log Datei wird einmalig überschrieben (gelöscht) 
		ofstream Spielverlauf_aus("Spielverlauf");
		Spielverlauf_aus.close();

		string Abgrenzung = "=================================================================\n";
		string Einleitung = "Neues Duell gestartet\n";
		string Name = spielername + " gegen Computer\n";
		string Trennstreifen = "_________________________________________________________________\n";
		string phase_1 = "\nPhase 1: Spieler\n";

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


		string Ueberschrift = "\n\n" + Abgrenzung + Einleitung + Name + schwierigkeitsgrad + spielfeldgroesse + Trennstreifen + phase_1;

		//um den Text in Log DAtei zu schreiben wird methode aus der Klasse Master Spielregeln verwendet
		meinSpiel.schreibe_Log_Datei(Ueberschrift);



		//Phase 1: Spieler ist an der Reihe
		system("cls");

		zeichne_Phase_Spieler();//Ueberschrift wird gezeichnet
		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
		
		//Hinweis!!: im Spielbetrieb auskommentiert --> zeigt zuvor erzeugte Lösung an
		/*
		meinSpiel.zeige_Loesung();
		system("pause");
		*/

		meinSpiel.spielzeichnen();//Spiel wird einmalig gezeichnet --> Spieler benötigt Spielfeld um nicht blind Zug machen zu müssen
		char eingabe;

		//Spiel-Schleife
		do {

			zeichne_Steuerungs_Kasten();//Hilfe Kasten aus menue.h integrieren
			eingabe = getchar();
			//cin >> eingabe;

			meinSpiel.eingabe_verarbeiten(eingabe);

			if (meinSpiel.hat_Spieler_gewonnen() == true) {
				warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

				break; //da Spiel gewonnen kann Schleife verlassen werden
			}
		} while (eingabe != 'x'); // Abbruch durch Spieler


		//falls Spieler das Spiel vor dem Sieg abgebrochen hat wird das in die Log DAtei geschrieben
		if ((eingabe == 'x') || (eingabe == 'X')) {
			//wenn X gedrückt wurde hat Spieler das Spiel abgegbrochen

			string aufgegeben = Trennstreifen + "Der Spieler hat das Duell vorzeitig abgebrochen\n" + Trennstreifen;
			meinSpiel.schreibe_Log_Datei(aufgegeben);
			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde

		}


		//Phase eins ist abgeschlossen (Spieler hat fertig gespielt/aufgegeben) --> Log DAtei braucht Trennung um Phase 2 reinschreiben zu können
		string phase_2 = "\n" + Trennstreifen + "Phase 2: Computer\n" + Trennstreifen;
		//wieder Nutzung der Methode fürs reinschreiben in Log DAtei
		meinSpiel.schreibe_Log_Datei(phase_2);


		//Phase 2:
		system("cls");

		zeichne_Phase_Computer();
		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
		

		meinSpiel.starte_Computer_Durchlauf();


		meinSpiel.zeichne_Vergleich_Statistik();
		warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde


		//Spieler hat Möglichkeit Inhalt der Log DAtei angezeigt zu bekommen
		if (frage_log_anzeigen() == true) {//Spieler möchte den Inhalt der Log DAtei angezeigt bekommen
			//ifstream wird zum lesen der Datei genutzt
			ifstream log_datei_lesen("Spielverlauf");


			if (log_datei_lesen) {
				string zeile;
				system("cls");
				cout << "\n\t--- SPIELPROTOKOLL ANFANG ---\n";

				// getline liest Datei Zeile für Zeile bis zum Ende
				while (getline(log_datei_lesen, zeile)) {
					cout << "\t" << zeile << endl;
				}

				cout << "\t--- SPIELPROTOKOLL ENDE ---\n";
				log_datei_lesen.close();
			}
			else {
				cout << "Fehler: Protokoll konnte nicht geladen werden.\n";
			}
			warte_auf_Enter();//durch diese Funktion wartet Compiler bis Enter gedrückt wurde
		}
		


		//schleife läuft so lange wie funktion frage nach neuem Spiel true zurückliefert
	} while (frage_neues_Spiel() == true);
}
