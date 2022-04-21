# Game of Life Kata

Link zur Kata [hier](https://codingdojo.org/kata/GameOfLife/).

Bei der [Game of Life Kata](https://codingdojo.org/kata/GameOfLife/) geht es darum, Conways ["Game of Life"](https://en.wikipedia.org/wiki/Conway's_Game_of_Life) nachzuprogrammieren, einen Startzustand laden zu können und den nächsten Zustand wieder abspeichern zu können. Das **"Game of Life"** ist ein spezifischer [Zellulärer Automat](https://de.wikipedia.org/wiki/Zellul%C3%A4rer_Automat), also kurzgesagt ein 2-Dimensionales (nicht zwingend) Feld aus Zellen, die binär entweder tot (0) oder lebendig (1) sind. Zusätzlich haben zellulärer Automaten eine Regel, die festlegt, welchen Zustand die Zelle im nächsten Schritt haben wird. Diese Regel ist immer abhängig von den **Nachbarn** einer Zelle. 

## Conways Game of Life

Das "Game of Life" hat seinen Namen daher, dass die Regel des Automaten ein Ergebnis liefert, dass stark an die Bewegung und Entwicklung von kleinen mehrzelligen Organismen erinnert. Es gibt sich wiederholende, sich bewegende und konstante Muster. Die Regeln des "Game of Life" sind ganz einfach:

> 1. Eine tote Zelle mit genau drei lebenden Nachbarn wird im nächsten Schritt neu geboren.
> 2. Lebende Zellen mit weniger als zwei lebenden Nachbarn sterben im nächsten Schritt.
> 3. Eine lebende Zelle mit zwei oder drei lebenden Nachbarn bleibt im nächsten Schritt am Leben.
> 4. Lebende Zellen mit mehr als drei lebenden Nachbarn sterben im nächsten Schritt an Überbevölkerung.

Die Nachbarn für eine Zelle sind alle **direkten**, sowie die **diagonalen** Nachbarn.

# Umsetzung

## Schritt 1: Zellen 

Ein guter Punkt um zu starten ist eine Klasse für die Zellen zu schreiben, aus denen der Automat besteht. Diese brauchen mindestens diese Attribute:

- Der aktuelle Zustand
- Die Position der Zelle

An Funktionen braucht die Klasse eigentlich nur eine Funktion `void checknext(int nachbarn)`, die den nächsten Zustand der Zelle bestimmt, wen man ihr die Anzahl der lebendigen Nachbarn gibt.  
*Beachte, dass der Zustand der Zelle erst geändert werden darf, wenn der nächste Zustand für alle Zellen berechnet wurde.*  

## Schritt 2: Automat

Als nächstes kann man schon den Automat schreiben. Dieser braucht natürlich ein Feld aus Zellen, das den aktuellen Zustand darstellt. Zusätzlich braucht er Funktionen, die über das ganze Feld iterieren um den nächsten Schritt vorzubereiten: `void prepareNextStep()` und eine Funktion um die Änderungen auszuführen: `void executeNextStep()`. Außerdem ist die Funktion `int getNeighbors(COORD pos)` nötig, um die Lebendigen Nachbarn einer Zelle zu berechnen.
*Beachte, dass ein Verhalten für den Rand des (endlichen) Feldes festgelegt werden muss.*

## Schritt 3: Dateiformat

Die wichtigsten Teile des Automaten sind jetzt vorhanden. Als nächstes müssen wir uns Gedanken über das Dateiformat machen, mit dem wir einen Zustand einlesen und dann wieder abspeichern wollen. Meine Lösung verwendet kein Format dass das ganze Feld abbildet, sondern nur die Koordinaten der lebenden Zellen speichert. Die 2-D Darstellung wird erst sichtbar, wenn man die Datei einliest. Es sind natürlich viel andere Formate möglich.

## Schritt 4: Parser

Nachdem wir das Format festgelegt habe, müssen wir eigentlich nur noch den Parser schreiben, der die Datei einlesen kann und auch wieder in eine Datei schreiben kann. Diese Funktionen können einfach Teil der Automat Klasse, da diese direkt auf dem Feld arbeiten müssen. In der Lösung sind das `bool loadLayout(std::string filename)` und `void saveLayout(std::string filename)`. In der Lösung gibt es die Möglichkeit zu pausieren, Zellen einzeln zu setzen, eine Anzahl an Schritten weiterzugehen und natürlich zu Speichern und zu Laden.

## Bedienung der Lösung

Beim Starten bekommt man 3 verschiedene Optionen:

1. Zustand aus einer Datei laden.
2. Zufällige Ausgangssituation
3. Die Zellen per Hand setzen

Danach gibt es zwei Eingabe Modi mit den folgenden Optionen:

- Pausiert:
    - T: Pause aufheben
    - Q: Datei speichern
    - O: Datei Laden
    - WASD: Bewegen des Cursors 
    - Space: Zustand der Zelle setzten
    - 1-9: Lässt den Automaten 1-9 Schritte weiter gehen
- Running:
    - T: Pausieren
    - S: Beende das Programm

Es liegen schon ein paar Dateien mit interessanten Formationen in dem Verzeichnis *"start"* zum Beispiel führt zu einem gleichmäßigen Muster, das sich über viele Schritte ausbreitet.











