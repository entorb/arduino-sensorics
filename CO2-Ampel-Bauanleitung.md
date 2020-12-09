# Teaser: Endprodukt 
(Foto noch ohne OLED Display für Anzeige des Zeitverlaufs als Bar-Chart)
![ASGS-V1.jpg](https://github.com/entorb/arduino-sensorics/blob/main/photos/ASGS-V1.jpg)

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

Alle Preise bei Mengenrabatt durch Bestellung von je 5 Stück.

## Bauplan
Da ich ungerne löte, bevorzuge ich es den ESP32 auf ein Breadboard zu stecken und die anderen Komponenten nur einseitig an ein Kabel mit Stecker zu löten. Dazu schneide ich die oben verlinkten Kabel in der Mitte durch um 10cm Kabel mit Stecker auf einer Seite zu bekommen. Als Breadboard empfehle ich das oben verlinkte zu verwenden und dies in der Mitte längs und auf Länge des ESP32 durchzusägen um die die Pins nicht durch den ESP32 zu verdecken. 

## Verkabelung

| ESP32     | MH-Z19        |
| --------- | ------        |
| 5V        | UIn (weiß)    |
| GND       | GND (schwarz) |
| G16 (RX)  | TX  (grau)    |
| G17 (TX)  | RX  (lila)    |

|ESP32   | 4 digit display
|-----   | ---
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
* [Meine Library](https://github.com/entorb/arduino-sensorics/tree/main/libraries/TM) manuell [hinzufügen](https://www.arduino.cc/en/guide/libraries#toc5)
* [Meinen Arduino Code](https://github.com/entorb/arduino-sensorics/tree/main/0_arduino_code) herunterladen
* Dort in der [device_setup.h](https://github.com/entorb/arduino-sensorics/blob/main/0_arduino_code/device_setup.h) die verwendeten Komponenten und gewünschte Messfrequenz auswählen
* kompilieren & Daumen drücken
