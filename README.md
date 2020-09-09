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
To easy import the examples you must have the right "_Platform folder_" installed. Check under `Arduino/Preferences/Arduino/Platform and Boards/arduino/Arduino AVR Boards` if version `1.8.3` is available and checked.
If it is not available, you have to check `Update local json files` in `Arduino/Preferences/Arduino/Third party index url's` and then restart sloeber and check the `1.8.3` entry.<br/>
If `File/Import/General/Existing Projects into Workspace` does not work, just can create a new Arduino project and choose `default cpp file`. Then copy the content of the lesson to the new cpp file.<br/>

After importing the project, you must check if the right `Port` is selected. On my computer it is COM6. After this you may check if the `Processor` -especially the right bootloader- is selected. After import, the `ATmega328P` is selected. It is the new version with the faster and smaller bootloader. If the upload does not work with this setting, just select the other one `ATmega328P (Old Bootloader)`. If this does not work either, check your port number with the Windows device manager (or the Arduino IDE, it shows the available port numbers) and check your USB cable.<br/>
![Selection of right Nano module](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Sloeber_Nano_choices.jpg)

# Kursaufbau
Der Arduino Kurs besteht aus **8-10 Schülern** der 8. und 9. Klassen. Er dauert eine **Doppelstunde** / 1,5 Zeitstunden pro Woche. 
Je 2 Schüler teilen sich einen Rechner / Laptop, wobei sicher auch andere Gruppengrößen denkbar sind.

## Inhalt der ersten Stunden
### 1. Stunde
Vorstellung, Vorkenntnisse und Erwartungen.<br/>
Zum Einsteig wird dann das das Doodle [50 Jahre "Kids Coding"](https://www.google.com/logos/2017/logo17/logo17.html?hl=de) gespielt. Dazu muss man allerdings online sein :-(.<br/> 
Hier werden die Konzepte **Anweisung** und **Wiederholungen/Schleifen** benutzt.<br/> 
Danach werden die Kinder in 2 Gruppen aufgeteilt. 
Jede Gruppe schreibt auf Notizzetteln auf, was der **menschliche Roboter** aus der anderen Gruppe machen muss, um vom Klassenraum ins Lehrerzimmer zu kommen. Schleifen und Umwege sind erlaubt!<br/> 
Oft ist dann die Doppelstunde auch schon rum.

### 2. Stunde
Jetzt bekommt der erste menschliche Roboter seine Anweisungen/Notizzettel und darf das Programm abbarbeiten. Danach ist die andere Gruppe dran.<br/> 
Zur Vertiefung kann man noch gemeinsam ein **Flussdiagramm** z.B. fürs Kuchenbacken entwickeln. Hier kommt am Ende die Abfrage, ob der Kuchen OK ist, oder ob man noch 5 Minuten warten soll und dann nochmal nachsieht.<br/>
Das ist ein neues Konzept, nämlich die **Bedingung/Entscheidung** (für eine Schleife).<br/> 
Danach wird mit Scratch ein Spiel gebaut.<br/> 
#### Aufgabe:
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
http://compute-it.toxicode.fr/?hour-of-code und danach http://silentteacher.toxicode.fr/ Beide sind der Hit.
Um das Konzept einer Variablen zu vertiefen, gibt es die **n-Eck Aufgabe** in Scratch.<br/> 
#### Aufgabe:
-  Mit Scratch 40 3-Ecke zeichnen, die Farbe, Größe und Position ist jedes Mal zufällig.
-  Wenn eine Taste gedrückt wird, z.B. die Leertaste, dann wird alles gelöscht und es werden 40 n+1-Ecke gezeichnet. Also erstmal 4-Ecke, dann 5-Ecke usw.

Tipp: Die Werte, die zum Malen eines N-Ecks benötigt werden, kann man aus der Eckenzahl berechnen.<br/> 
Bei dieser Aufgabe müssen Variablen in Formeln/Berechnungen verwendet werden. Das ist eine wichtige Anwendung von Variablen!

### 5. Stunde
Der Aufbau eines Breadboards wird erklärt, die Boards werden ausgeteilt und mit der ersten Aufgabe **1\_1_Ampel** angefangen.<br/> 
Das Beispiel kann man erst einmal auf den Arduino laden und dann beobachten was es macht.<br/>
Für die Lösung der Aufgabe ist es gut, eine Ampel live sehen zu können oder ein Video davon zu zeigen. 
Die meisten Kinder kennen die Gelb Phasen nicht richtig.<br/>
Je nachdem kann man die Kinder auch vorher die Boards zusammenstecken lassen, das ist sicher nett, ich hatte dazu leider keine Geduld.

# Inhalt der Aufgaben
## 1_1_Ampel
Die 3 LED's so ansteuern, dass sie wie eine Verkehrsampel leuchten.
- Ausgabe digitaler Werte auf einem Arduino Pin.
- Warten mit delay().

## 1_2_ButtonInputToLedAndSerial
Den Zustand der beiden Buttons einlesen und und auf dem Serial Monitor ausgeben.
- Einlesen digitaler Werte.
- if / else Anweisung, logisches invertieren.
- Statische Variable.

## 1_2_ButtonInputToTone
Den Zustand der beiden Buttons einlesen und je nach gedrückten Buttons verschiedene Töne ausgeben.
- Ausgabe eines Tons.
- Verknüpfung von Bedingungen.

## 1_3_AnalogValueToTone
Einen Spannungswert, der durch ein Potentiometer oder einen lichtempfindlichen Widerstand (LDR) erzeugt wird, einlesen und in eine Tonhöhe verwandeln.
- Potentiometer, LDR/Lichtwiderstand.
- Einlesen analoger Werte.
- map() Funktion.
- Verwendung von Variablen in der Loopdefinition.

## 1_4_AnalogValueToPlotter
Werte im Arduino Plotter ansehen und das Maximum und Minimum berechnen.
- Potentiometer, LDR/Lichtwiderstand.
- Einlesen analoger Werte.
- Arduino Plotter.
- Minimum / Maximum finden.

## 1_5_USToPentatonic
Ultraschall Entfernungswert einlesen und je nach Entfernung verschiedene Töne aus einer pentatonischen Reihe abspielen.
- Datenblatt eines Abstandsmessers lesen und ihn richtig ansteuern.
- Ultraschall Abstandssensor einlesen.
- Laufzeit des Schalls in Abstand umrechnen.
- Werte aus Array holen.

## 1_6_Melody
Eine Melodie ausgeben.
- Arrays und Loops über Arrays.
- sizeof() Funktion.

## 3_PlayChristmasMelodyUS
Bei richtigem Abstand ein zufälliges Weichnachtslied spielen.
- Ultraschall Abstandssensor einlesen.
- Eine Library benutzen um Weichnachstlieder abzuspielen.


# Universal breadboard layout for all lessons
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Nano_Lessons_Breadboard_Steckplatine.png)
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Nano_Lessons_Breadboard_Schaltplan.png)
![Universal breadboard front](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Front.jpg)
![Universal breadboard top](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Top.jpg)
![Universal breadboard back](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_Back.jpg)
![Universal breadboard connection schema](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_connections.jpg)
![Universal breadboard top and bottom view](https://github.com/ArminJo/Arduino-Lessons-for-School/blob/master/Media/Breadboard_top_bottom.jpg)

### If you are interested in an English translation, please send me a mail.

