
// =========================================================
// PROJEKT:      PROJEKT HASCHI
// DATEI:        Cursor.cpp
// BESCHREIBUNG: Implementierung der Cursor-Steuerung
//               Umwandlung von WASD-Eingaben in Vektoren
//               inklusive dynamischer Grenzprüfung
// ---------------------------------------------------------
// ENTWICKLER:   Linus Schiel (Software-Architektur & Implementierung)
// KONZEPT:      Linus Schiel, Emil Kern
// VERSION:      v1.0.0 (Final)
// =========================================================


#include "Cursor.h"
using namespace std;


Cursor::Cursor() {
	//Standardkonstruktor
	x_Koordinate_Spielfeld = 2;
	y_Koordinate_Spielfeld = 2;
	gewaehltes_Format = 23;
}

Cursor::Cursor(int Startpunkt_x_Koordinate, int Startpunkt_Y_Koordinate, int Gewaehltes_Format) {
	//parametrisierter Konstruktor
	x_Koordinate_Spielfeld = Startpunkt_x_Koordinate;
	y_Koordinate_Spielfeld = Startpunkt_Y_Koordinate;
	gewaehltes_Format = Gewaehltes_Format;
}

int Cursor::get_X_Koordinate_Spielfeld() {
	return x_Koordinate_Spielfeld; //return der X_Koordinate falls die X_Koordinate allein benötigt wird
}

int Cursor::get_Y_Koordinate_Spielfeld() {
	return y_Koordinate_Spielfeld;//return der Y_Koordinate falls die Y_Koordinate allein benötigt wird
}

void Cursor::bewege_Cursor(char eingabe) {
	//===========================================================================================
	//Aufgabe dieser Methode
	//===========================================================================================
	//der Methode kann ein Zeichen (eingabe) übergeben werden, dieses Zeichen wird auf die richtige Eingabe überprüft dann in eine Verschiebung/Vektor umgewandelt 
	//diese Verschiebung wird auf Überschreitung der Spielfeldgrenzen überprüft --> wenn passend Verschiebung wird durchgeführt und Attribute (x/y) werden verändert




	//===========================================================================================
	// 1. Temporäre Speicherung der X/Y Koordinate (Attribute der Klasse Cursor)
	//===========================================================================================
	//x/y werden temporär gespeichert das eine spätere Addition/Prüfung möglich ist ohne direkt das Attribut zu verändern

	int x_temporaer_gespeichert = x_Koordinate_Spielfeld; //temporäre Speicherung der x/y_Koordinate 
	int y_temporaer_gespeichert = y_Koordinate_Spielfeld;
	int Dynamische_Obergrenze = gewaehltes_Format - 2;//Randstreifenbegrenzung wird abgezogen
	// da die Obergrenze durch die jeweilige Formatgröße festgelegt ist muss diese sich an die Formatgröße anzupassen --> dynamisch sein


	//===========================================================================================
	// 2. Umwandlung der Eingabe in Vektor
	//===========================================================================================
	//Vektoren sind für die Verschiebung von x/y zuständig, indem diese auf die Koordinaten addiert werden

	//!!Hinweis:!!
	//um das Spielfeld entzerrter darstellen zu können wird das doppelte Array angezeigt --> um dennoch nur 10 mögliche Positionen zu ermöglichen wird der
	//Cursor um 2 Positionen verschoben

	//!!Hinweis:!!
	//Koordinatensystem ist gedreht, daher ist der Nullpunkt oben links in der Ecke, daher wird bei y genau entgegen der Richtung der Tasteingabe verschoben

	switch (eingabe) {//bei passender Ziffer werden temporäre Koordinaten verschoben
	case('w'):
	case('W'):
		y_temporaer_gespeichert = y_temporaer_gespeichert - 2; //temporäre Koordinaten Verschiebung um 2 Koordinaten
		break;

	case('s'):
	case('S'):
		y_temporaer_gespeichert = y_temporaer_gespeichert + 2;
		break;

	case('a'):
	case('A'):
		x_temporaer_gespeichert = x_temporaer_gespeichert - 2;
		break;

	case('d'):
	case('D'):
		x_temporaer_gespeichert = x_temporaer_gespeichert + 2;
		break;

	default:
		return;//bei falscher Eingabe soll Methode direkt beendet werden
	}


	//===========================================================================================
	// 3. Prüfung der Verschiebung --> diese muss im Feld liegen
	//===========================================================================================
	//untere Grenze ist immer die Koordinate 2,2 und die Koordinate der Obergrenze (rechte untere Ecke) wird durch dynamische Obergrenze festgelegt

	if (((x_temporaer_gespeichert >= 2) && (x_temporaer_gespeichert < Dynamische_Obergrenze))&& ((y_temporaer_gespeichert >= 2) && (y_temporaer_gespeichert < Dynamische_Obergrenze))) {


		//===========================================================================================
		// 4. Speicherung der Koordinate
		//===========================================================================================
		//wenn Koordinate im Spielfeld liegt wird das Attribut x/y Koordinate durch die temporäre X/Y Koordinate aktualisiert

		x_Koordinate_Spielfeld = x_temporaer_gespeichert;
		y_Koordinate_Spielfeld = y_temporaer_gespeichert;
	}
}