# 🎮 Projekt Hashi – Strategie & Logik (Note 1,0)

Dieses Repository enthält die vollständige softwareseitige Umsetzung des japanischen Logikrätsels **Hashi** (Hashiwokakero). Das Projekt wurde im Rahmen der Hausarbeit Informatik (WS 25/26) an der **Hochschule Karlsruhe (HKA)** entwickelt und mit der Bestnote bewertet.

## 🧠 Was ist Hashi?
Hashi ist ein Brückenbau-Rätsel, bei dem logisches Denken und strategische Planung kombiniert werden müssen:
* **Inseln & Brücken:** Inseln enthalten Zahlen (1 bis 8), welche die Anzahl der ausgehenden Brücken definieren.
* **Verbindungen:** Brücken dürfen nur horizontal oder vertikal verlaufen und sich niemals kreuzen.
* **Ziel:** Alle Inseln müssen korrekt verbunden werden, sodass ein zusammenhängendes Netzwerk entsteht.

## 🛠️ Technische Highlights & Architektur
Das Programm wurde in **C++** unter strikter Einhaltung einer modularen Software-Architektur realisiert. Trotz bewusster Einschränkungen (wie dem Verzicht auf `std::vector` gemäß Aufgabenstellung) wurde eine hochgradig robuste Anwendung geschaffen.

* **Umfang:** Über **5.430 Zeilen Quellcode** (LoC).
* **"KI-Komponente" (`Haschi_Loeser`):** Ein Computer-Gegner, der Spielfelder systematisch analysiert und zwingende Züge identifiziert.
* **Spielgenerator:** Algorithmus zur prozeduralen Erstellung garantiert lösbarer Spielfelder in verschiedenen Schwierigkeitsgraden.
* **Robustheit:** Implementierung einer speziellen Eingabeverarbeitung, um Programmabstürze durch Fehleingaben (z.B. Buchstaben statt Zahlen) effektiv abzufangen.

## 📂 Projektstruktur (Industriestandard)
Die Architektur folgt der professionellen Trennung von Deklaration und Implementierung:
* **`include/`**: Enthält alle Header-Dateien (.h). Hier sind die Klassendefinitionen und Schnittstellen hinterlegt.
* **`src/`**: Enthält die Quelldateien (.cpp). Hier befindet sich die gesamte Logik und die mathematische Umsetzung der Spielregeln.
* **`.gitignore`**: Hält das Repository sauber, indem temporäre Log-Files und Kompiler-Daten ausgeschlossen werden.

## 👥 Entwicklerrollen
* **Software-Architektur & Programmierung:** Linus Schiel
* **Konzeption & Dokumentation:** Linus Schiel & Emil Kern

---
*Erstellt im Rahmen der Prüfungsleistung Informatik – Hochschule Karlsruhe (HKA)*
