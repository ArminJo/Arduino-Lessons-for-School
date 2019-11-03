# Arduino lessons for school
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Hit Counter](https://hitcounter.pythonanywhere.com/count/tag.svg?url=https%3A%2F%2Fgithub.com%2FArminJo%2FArduino-Lessons-for-School)](https://github.com/brentvollebregt/hit-counter)

These lessons are for my course at a Gymnasium in Cologne. The course is addressed at eighth or ninth grade pupils.<br/> 
I use the [Sloeber IDE](http://eclipse.baeyens.it/) here, since it is as easy as the Arduino IDE but a lot more powerful and flexible.
All examples will also run with the Arduino IDE, just copy the program file content to a new sketch.<br/> 
Each lesson consists of the `.cpp file` the pupils work with, a `.task file` with the original content of the task, and a `Solution.cpp` file where the complete solution is contained.<br/>
All lessons work on a universal breadboard layout, and can easily be adapted by just changing the `Breadboard.h` file of the examples.

# Sloeber installation directory and Platform folder
My sloeber is installed at `E:\Elektro\sloeber`, so it will work out of the box if you use the same location. If you have no E: drive you can use the command subst E: "C:<Path to sloeber root directory>"<br/>
My workspace directory is `E:\WORKSPACE_SLOEBER`, but any other location will do.
To easy import the examples you must have the right "_Platform folder_" installed. Check under `Arduino/Preferences/Arduino/Platform and Boards/arduino/Arduino AVR Boards` if version `1.8.1` is available and checked.
If it is not available, you have to check `Update local json files` in `Arduino/Preferences/Arduino/Third party index url's` and then restart sloeber and check the `1.8.1` entry.<br/>
If `File/Import/General/Existing Projects into Workspace` does not work, just can create a new Arduino project and choose `default cpp file`. Then copy the content of the lesson to the new cpp file.


# Kursaufbau
Der Arduino Kurs besteht aus **8-10 Schülern** der 8. und 9. Klassen. Er dauert eine **Doppelstunde** / 1,5 Zeitstunden pro Woche. 
Je 2 Schüler teilen sich einen Rechner / Laptop, wobei sicher auch andere Gruppengrößen denkbar sind.

## Inhalt der ersten Stunden
### 1. Stunde
Vorstellung, Vorkenntnisse und Erwartungen.<br/>
Zum Einsteig das Doodle [50 Jahre "Kids Coding"](https://www.google.com/doodles/celebrating-50-years-of-kids-coding?doodle=32615474). Dazu muss man allerdings online sein :-(.<br/> 
Hier werden die Konzepte Anweisung und Wiederholungen/Schleifen benutzt.<br/> 
Danach werden die Kinder in 2 Gruppen aufgeteilt. 
Jede Gruppe schreibt auf Notizzetteln auf, was der menschliche Roboter aus der anderen Gruppe machen muss, um vom Klassenraum ins Lehrerzimmer zu kommen. Schleifen und Umwege sind erlaubt!<br/> 
Oft ist dann die Doppelstunde auch schon rum.

### 2. Stunde
Jetzt bekommt der erste menschliche Roboter seine Anweisungen/Notizzettel und darf das Programm abbarbeiten. Danach ist die andere Gruppe dran.<br/> 
Zur Vertiefung kann man noch gemeinsam ein Flussdiagramm z.B. fürs Kuchenbacken entwickeln. Hier kommt am Ende die Abfrage, ob der Kuchen OK ist, oder ob man noch 5 Minuten warten soll und dann nochmal nachsieht. Das ist ein neues Konzept, nämlich die Bedingung/Entscheidung.<br/> 
Danach wird mit Scratch ein Spiel gebaut.<br/> 
**Aufgabe**
-	Wir holen 2 Figuren und 1 Objekt (z.B. Bananen oder Diamant).
-	Eine Figur bewegt sich in 20er Schritten mit den Pfeiltasten, die andere mit den wasd Tasten.
-	Die Figuren fangen am Rand an.
-	Das Objekt wird zufällig positioniert.
-	Wir machen 2 Variablen, z.B. Player1 und Player2, die beim Start auf 0 gesetzt werden.
-	Wenn das Objekt einen Player berührt wird die entsprechende Variable hochgezählt und das Objekt an einen neuen zufälligen Platz verschoben.
-	Zusatzaufgabe: wenn das Objekt nach dem verschieben direkt wieder einen Player berührt, dann wird es wieder zufällig verschoben.
-	Wenn eine Variable 10 erreicht, wird ein Sound abgespielt und das Spiel beendet.
-	Zusatzaufgabe: Wenn ein Player am Bildschirmrand ankommt soll er am entgegengesetzten Bildschirmrand erscheinen. Dazu muss man die existierenden Variablen x-Position etc. verwenden.
-	Zusatzaufgabe: Benutze nicht feste Schrittweiten, sondern Variablen SchrittweitePlayer1 + 2, die am Anfang auf 10 gesetzt wird. Die kann bei jedem Punkt verändert werden (z.B. +10).

### 3. Stunde
Weiter mit dem Programmieren des Scratch Spiels.

### 4. Stunde
Um das Konzept einer Variablen zu vertiefen, gibt es die N-Eck Aufgabe in Scratch.<br/> 
**Aufgabe**
-  Mit Scratch 40 3-Ecke zeichnen, die Farbe, Größe und Position ist jedes Mal zufällig.
-  Wenn eine Taste gedrückt wird, z.B. die Leertaste, dann wird alles gelöscht und es werden 40 n+1-Ecke gezeichnet. Also erstmal 4-Ecke, dann 5-Ecke usw.

Tipp: Die Werte, die zum Malen eines N-Ecks benötigt werden, kann man aus der Eckenzahl berechnen.<br/> 
Bei dieser Aufgabe müssen Variablen in Formeln/Berechnungen verwendet werden. Das ist eine wichtige Anwendung von Variablen!

### 5. Stunde
Der Aufbau eines Breadboards wird erklärt die Boards werden ausgeteilt und mit der ersten Aufgabe **1\_1_Ampel** angefangen.<br/> 
Das Beispiel kann man erst einmal auf den Arduino laden und dann beobachten was es macht.<br/> 
Je nachdem kann man die Kinder auch vorher die Boards zusammenstecken lassen, das ist sicher nett, ich hatte dazu leider keine Geduld.


# Universal breadboard layout for all lessons
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Nano_Lessons_Breadboard_Steckplatine.png)
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Nano_Lessons_Breadboard_Schaltplan.png)
![Universal breadboard front](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Front.jpg)
![Universal breadboard top](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Top.jpg)
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Back.jpg)
![Universal breadboard connection schema](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_connections.jpg)
![Universal breadboard top and bottom view](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_top_bottom.jpg)

