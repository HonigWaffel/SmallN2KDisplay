# N2K-Display

Veröffentlicht von Paul Lecke und Marco Hintz

### Projekt

Für dieses Projekt wird ein Display von Riverdi verwendet:

https://riverdi.com/de/product/5-inch-lcd-display-stm32u5-rvt50hqsnwn00



Das N2K-Display ist ein 5" Display mit integriertem STM32U5A9NJH6Q und ist mit einer Auflösung von 800 x 480 Pixeln ausgestattet. Das Panel ist ein

TFT-LCD mit einer Helligkeit von 1000cd/m^2 (ohne Touch).

Dieses Display ist mit einem CANFD-Treiber ausgestattet, mit dem die N2K-Nachrichten ausgelesen werden können.



Das Display wird mittels STMCube-IDE programmiert, hierfür wird das von Riverdi eigens entwickelte Projekt verwendet. Dieses Projekt ist in dem GitHub-Projekt:

https://github.com/riverdi

zu finden. Es beinhaltetet die für den verwendeten Controller und das Display benötigten Treiber- und Flashspeichereinstellungen.Für die Erstellung der GUI wird ebenfalls die von Riverdi unterstützt Software TouchGFX von STM verwendet.



Die Software ist in mehreren Modulen aufgebaut. Die wichtigsten sind der CANFD-Treiber zum einlesen und verarbeiten der N2K-Nachrichten.

Weiter wird noch ein GPIO-Treiber verwendet. Dieser wird benötigt um die Eingaben über die Knöpfe zu verarbeiten.

Die Grafik wird mittels der von TouchGFX erstellten Module durchgeführt.



### Programmierung

Für das Einbinden neuer N2K-Nachrichten werden Anpassungen an verschiedenen Stellen benötigt:

In fdcan.c wird ein Task synchron aufgerufen, dieser verarbeitet die Empfangenen Nachrichten. In dem Task fdcan\_vParserTask muss der Code in den SwitchCase eingearbeitet werden, der

die CAN-Nachricht auswertet. Weiter muss das Enum fdcan\_enMSG\_t und die Listen fdcan\_stCanMgs und fdcan\_stN2KData an die neue Nachricht angepasst werden, dazu wird einfach ein

weiterer Eintrag hinzugefügt und mit die notwendigen Parametern aufgefüllt. In die Liste fdcan\_stCanMgs werden die empfangenen Nachrichten anhand ihrer Parameter Group Number (PGN) in die Liste eingetragen. In dem Task fdcan\_vParserTask werden die Daten aus den Nachrichten entnommen, in das benötigte Format gebracht und in die Liste fdcan\_stN2KData geschrieben. Diese Überträgt die Daten an die GUI.



In fdcan.h müssen die Enums fdcan\_enn2kDATA\_t und fdcan\_enSEL\_SCREEN\_t um die neue Nachricht ergänzt. Dadurch werden die Elemente veröffentlicht und alle Module die fdcan.h inkludieren können auf die Elemente zugreifen.



In den GUI-Module müssen Anpassungen in Model.cpp, ModelListener.hpp und MenuView.ccp durchgeführt werden. Zuvor sollte jedoch der Screen der neuen Daten in TouchGFX programmiert

werden. Dazu wird die Datei N2KDisplay.touchgfx mit TouchGFX-Desginer geöffnet und ein neuer Screen erstellt. Dabei muss darauf geachtet werden, das in der Interactions von dem Screen

Menu ein Wechsel auf den neuen Screen eingestellt ist. Ebenfalls muss ein Wechsel von dem neu programmierten Screen auf den Menu Screen in den Interactions des neuen eingestellt werden.

Bei der Schriftart muss darauf geachtet werden, dass alle benötigten Characters enthalten sind. Dies kann überprüft werden, in dem links auf Texts, Typographies und dort die

gewünschte Art ausgewählt wird. In den Wildcard Characters müssen alle benötigten Zeichen eingegeben werden. Bereits vor eingestellte Schrifttypen sind: "Default", "Data\_Lang" und "Data\_Big".

Weiter muss auf dem Menu Screen ein Textfeld mit dem neuen Screen und ein Pfeil dazu erstellt werden. Die Reihenfolge der Textfelder der Screens muss mit dem Enum fdcan\_enSEL\_SCREEN\_t

aus fdcan.h übereinstimmen. 

Für die Daten ist es relevant eine Wildcard anzulegen. Diese in TouchGFX auf dem Textfeld der Daten aktiviert. Wenn man auf das Textfeld drück, findet man unter Translation den Button "Wildcard +". Dabei wird in das Textfeld "<value>" geschrieben, welches gegen die Daten eingetauscht wird. In Wildcard muss danach noch die Buffergröße ausgewählt werden. Diese ist abhängig davon wie viele Zeichen verwendet werden sollen.

Abschließend sollte der neue Pfeil noch auf unsichtbar geschaltet werden und der Code generiert werden.



Die GUI von TouchGFX wird durch das Modul "Model" gesteuert. Dieses ist in dem Ordner "Projektname->TouchGFX->gui->" und "src" führ den Code und "include" für die Veröffentlichungen zu finden. 



In Model.cpp gibt es die Funktion tick() welche zyklisch aufgerufen wird. In dieser Funktion ist eine For-Schleife die alle Daten an die Screens versendet, sobald neue Daten vorhanden sind. In dieser For-Schleife muss der Funktionsaufruf für den neuen Screen eingefügt werden.

Weiter muss in das Header-File ModelListener.hpp die Funktion veröffentlicht werden.



In "Screenname"Presenter.hpp muss diese Funktion in public eingetragen werden.

Die Funktion selber wird in "Screenname"Presenter.cpp aufgebaut. Sie muss die Daten weitergeben, den Darkmode aktivieren können und die Funktion changeScreen aufrufen.



Als letztes wird das View-Modul des Screens programmiert. Dieses schreibt die Daten in den Screen, ändert den Beleuchtungsmodus und wechselt den Screen. 

Die Funktionen die zuvor in "Screenname"Presenter.cpp aufgerufen wurden, müssen in dem Header-File "Screenname"View.hpp veröffentlicht werden. Dazu werden sie in public eingetragen mit dem Einstellung "virtual". Diese Funktionen werden dann in "Screenname"View.cpp realisiert.

Zusätzlich muss die Wildcard noch initialisiert werden. Dazu wird in die Funktion setupScreen der Aufruf "Screennam"Target.setWildcard("Textfiledname"Buffer); geschrieben.



Zur Orientierung können die vorhandenen Module "Screen1", "Speed" und "Depth" verwendet werden.







