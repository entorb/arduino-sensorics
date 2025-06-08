# Motivation
## Teaser: Endprodukt 
![ASGS-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ASGS-V1.jpg)

## Motivation
In Zeiten der SARS-CoV-2 / Coronavirus-Pandemie (siehe auch meine [Corona-Datenauswertungen](https://entorb.net/COVID-19-coronavirus/)) ist häufiges Lüften wichtig um die Übertragung über [Aerosole](https://de.wikipedia.org/wiki/Aerosol) zu unterbinden. Dies gilt insbesondere für Schulen, Kindergärten und Kinderkrippen/KiTas. Ein guter Indikator dafür, dass es Zeit um Lüften ist, ist die [CO2 Konzentration](https://de.wikipedia.org/wiki/Kohlenstoffdioxid) in der Luft, wobei ein Wert von 400[ppm](https://de.wikipedia.org/wiki/Parts_per_million) die Baseline und ein Wert von 1000ppm ein guter Grund zum Lüften ist. Um einen kleinen Beitrag zu leisten, habe ich eine CO2 Ampel entworfen und unserer Schule und KiTa gespendet. Nachbauten ausdrücklich erwünscht.

## Funktionalität
* CO2 Konzentration wird periodisch (zB alle 15s) gemessen
* Angezeigt via 
  1. als Zahl in ppm
  2. über eine LED, die von Grün über Blau nach Rot die Farbe (und die Helligkeit) wechselt
  3. V2: als Zeitverlauf über ein Balkendiagramm mit 2h in die Vergangenheit
* optional: via WiFi, InfluxDB und Grafana exportiert und visualisiert

Ich freue mich über Nachbauten, Feedback und Verbesserungsvorschläge, zB über dieses [Kontaktformular](https://entorb.net/contact.php?origin=CO2-Ampel).

Genug der Einleitung, kommen wir nun zur Bauanleitung.

# Hardware
## Einkaufszettel
Komponente |  Preis 
---------- | ------
[Microcontroller ESP32](https://www.az-delivery.de/products/esp32-developmentboard)      | 6 €
[CO2 Sensor MH-Z19B](https://www.ebay.de/sch/i.html?_from=R40&_nkw=MH-Z19B&_sacat=0&rt=nc&LH_PrefLoc=3)    | 15-25 €
[4 digit display](https://www.az-delivery.de/products/4-digit-display)    | 1,60 €
[LED RGB](https://www.az-delivery.de/products/led-rgb-modul)    | 1,20 €
optional [OLED (128x64) display](https://www.az-delivery.de/products/0-96zolldisplay) | 3,60 €   
[Kabel mit Stecker](https://www.az-delivery.de/products/40-stk-jumper-wire-male-to-male-20-zentimeter) | 0,50 €
optional Hälfte von [Breadboard](https://www.az-delivery.de/products/breadboard) | 1 €
SUMME | ca 15 € + MH-Z19B = 30-40€

Alle Preise bei Mengenrabatt durch Bestellung von je 5 Stück. Ich habe durch einen Mengenrabatt einen kleinen Vorrat an CO2 Sensoren erworben und biete gerne an diese weiterzugeben. 

## Bauplan
Da ich ungerne löte, bevorzuge ich es den ESP32 auf ein Breadboard zu stecken und die anderen Komponenten nur einseitig an ein Kabel mit Stecker zu löten. Dazu schneide ich die oben verlinkten Kabel in der Mitte durch um 10cm Kabel mit Stecker auf einer Seite zu bekommen. Als Breadboard empfehle ich das oben verlinkte zu verwenden und dies in der Mitte längs und auf Länge des ESP32 durchzusägen um die die Pins nicht durch den ESP32 zu verdecken. 

## Verkabelung

| ESP32     | MH-Z19        |
|---------- | ----
| 5V        | UIn (weiß)    |
| GND       | GND (schwarz) |
| G16 (RX)  | TX  (grau)    |
| G17 (TX)  | RX  (lila)    |

|ESP32   | 4 digit display
|------- | ----
|3.3V    | VCC (lila / weiß)
|GND     | GND (blau / schwarz)
|G32     | CLK (weiß / lila)
|G33     | DIO (grau / grau)

|ESP32  | RGB LED KY-016
|------ | ----
|GND    | GND
| 5     | R
|18	    | G
|19	    | B

|ESP32  | OLED 0.96" 128x64px
|------ | ----
|GND 	  | GND
|3.3V   | VCC
|G22 	  | SCK
|G21 	  | SDA

## Gehäuse
* 2D Zeichnungsentwurf siehe [hier](https://github.com/entorb/arduino-sensorics/tree/main/cad/CO2-Ampel)
* TODO: upload 3D Zeichnung von B.T.
* 8mm Stärke passt gut zur Dicke des 4-digit-Displays und MH-Z19B CO2 Sensors (für dessen Sensor unten etwas aussparen)

# Software
* [Arduino IDE](https://www.arduino.cc/en/software) installieren
* [ESP32 für Adruino IDE](https://entorb.net/wickie/Arduino#Adding_ESP32_to_Arduino_IDE) installieren, wichtig dabei der Hinweis, dass die URL der JSON in dem Artikel nicht mehr aktuell ist, sondern [diese hier](https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json), [Quelle](https://github.com/espressif/arduino-esp32/issues/3443#issuecomment-549113517)
* optional Visual Studio Code als Editor [einrichten](https://entorb.net/wickie/Arduino#Visual_Studio_Code) 
* folgende Libs installieren
  * MH-Z19 by Jonathan Dempsey
  * Adafruit BME280 Library
  * BH1750 by Christopher Laws
  * InfluxDbClient by Influx Data
  * U8g2 by oliver
  * TM1637 by Avishay Orpaz
  * ESP32 AnalogWrite by ERROPiX
* [Meine Library](https://github.com/entorb/arduino-sensorics/tree/main/libraries/TM) manuell [hinzufügen](https://www.arduino.cc/en/guide/libraries#toc5)
* [Meinen Arduino Code](https://github.com/entorb/arduino-sensorics/tree/main/0_arduino_code) herunterladen
* Dort in der [device_setup.h](https://github.com/entorb/arduino-sensorics/blob/main/0_arduino_code/device_setup.h) die verwendeten Komponenten und gewünschte Messfrequenz auswählen
* kompilieren & Daumen drücken

## Software as a Service
Wer gerne bastelt und lötet, aber keine Erfahrung mit der Arduino Programmierung hat und auch keine Lust hat in das Gebiet abzutauchen, dem biete ich gerne an die Software auf seinen Microcontroller EPS32 einzuspielen.

# Danke
* für die Unterstützung beim Coding an Ingmar und Gerhard
* für das 3D-Zeichnen und Zuschneiden des Gehäuses für unsere Schule an Bastian

# Bilder
V1.2: Massenproduktion mit 2h-Zeitverlauf als Bar-Chart via OLED Display
![4xCO2-in-Holz.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/4xCO2-in-Holz.jpg)

V1 für unsere Schule
![ASGS-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ASGS-V1.jpg)

V0.5 Prototyp für unseren Kindergarten
![KiTa-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/KiTa-V1.jpg)

V0.2 Experimentieren mit verschiedenen Anzeigen
![Display-Test.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/Display-Test.jpg)

V0.1 Anzeige via Grafana und InfluxDB
![Grafana-CO2.png](https://github.com/entorb/arduino-sensorics/blob/main/photos/Grafana-CO2.png)

# Ähnliche Projekte
* [UN-Hack-Bar: CO2 Ampeln für alle](https://www.un-hack-bar.de/2020/10/25/co2-ampeln-fuer-alle/)
* [UN-Hack-Bar: Repository](https://git.unhb.de/smash/co2ampel)
* [Heise: CO2-Ampel: Bauanleitung](https://www.heise.de/select/make/2020/5/2022015381334973804)
* [Heise: CO2-Ampel: Erfahrungsbericht aus der Schule](https://www.heise.de/news/CO2-Ampel-Erfahrungsbericht-aus-der-Schule-4932471.html)
