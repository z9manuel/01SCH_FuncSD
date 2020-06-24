/*
 Name:		_01SCH_FuncSD.ino
 Created:	6/23/2020 8:04:30 PM
 Author:	mrodriguez
*/

#include "FS.h"
#include "SD.h"
#include <SPI.h>

#define SD_CS 5						// Define CS pin para modulo SD
File schFile;

void setup() {
	Serial.begin(115200);
	bool resultado = 0;
	for (int i = 1; i < 76; i++) {
		String cadena;
		cadena = "Esta es la cadena " + String(i);
		SD_escribirLog(cadena);
		delay(10);
	}
	SD_leerLog();
	SD_borrarLog() ? Serial.println("Log borrado.") : Serial.println("Log no borrado");
}


void loop() {
}


bool SD_leerLog() {
	SD.begin(SD_CS);
	if (!SD.begin(SD_CS)) {
		Serial.println("Error modulo SD!");
		return 0;
	}
	uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE) {
		Serial.println("Error tarjeta SD!");
		return 0;
	}
	if (!SD.begin(SD_CS)) {
		Serial.println("ERROR - Falla en tarjeta SD!");
		return 0;
	}
	File dataLog = SD.open("/log.txt", FILE_READ);
	if (dataLog) {
		int renglon = 0;
		String confLine;
		dataLog.position();
		while (dataLog.available() && renglon<51) {
			confLine = dataLog.readStringUntil('\n');
			Serial.println(confLine);
			renglon=renglon+1;
		}
		Serial.println(String(renglon) + " renglones.");
		while (dataLog.available()) {
			confLine = dataLog.readString();
			Serial.println(confLine);
		}
		dataLog.close();
		return 1;
	}
}

bool SD_escribirLog(String cadena) {
	SD.begin(SD_CS);
	if (!SD.begin(SD_CS)) {
		Serial.println("Error modulo SD!");
		return 0;
	}
	uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE) {
		Serial.println("Error tarjeta SD!");
		return 0;
	}
	if (!SD.begin(SD_CS)) {
		Serial.println("ERROR - Falla en tarjeta SD!");
		return 0;
	}
	File dataLog = SD.open("/log.txt", FILE_APPEND);
	if (dataLog) {
		dataLog.println(cadena);
		dataLog.close();
		Serial.println(cadena);
		return 1;
	}
}

bool SD_borrarLog() {
	SD.begin(SD_CS);
	if (!SD.begin(SD_CS)) {
		Serial.println("Error modulo SD!");
		return 0;
	}
	uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE) {
		Serial.println("Error tarjeta SD!");
		return 0;
	}
	if (!SD.begin(SD_CS)) {
		Serial.println("ERROR - Falla en tarjeta SD!");
		return 0;
	}
	if (SD.remove("/log.txt")) {
		Serial.println("Registro borrado.");
		schFile.close();
		return 1;
	}
}