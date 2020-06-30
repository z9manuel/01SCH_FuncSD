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
	//SD_borrarLog() ? Serial.println("Log borrado.") : Serial.println("Log no borrado");
}


void loop() {
}


bool SD_leerLog() {
	if (SD_validar()) {
		File dataLog = SD.open("/log.txt", FILE_READ);
		if (dataLog) {
			bool enviado = 0;
			String linea;
			dataLog.position();
			while (dataLog.available()) {
				linea = dataLog.readStringUntil('\n');
				enviado = enviar_a_API(linea);
				if (enviado == false) {
					return false;
				}
			}
			dataLog.close();
			if (SD_borrarLog()) {
				return 1;
			}
		}
	}
	return false;
}

bool SD_escribirLog(String cadena) {
	if (SD_validar()) {
		SD.begin(SD_CS);
		File dataLog = SD.open("/log.txt", FILE_APPEND);
		if (dataLog) {
			dataLog.println(cadena);
			dataLog.close();
			Serial.println(cadena);
			return 1;
		}
	}
	return false;
}

bool SD_borrarLog() {
	if (SD_validar()) {
		SD.begin(SD_CS);
		if (SD.remove("/log.txt")) {
			Serial.println("Registro borrado.");
			schFile.close();
			return 1;
		}
	}
	return false;
}

bool SD_validar() {
	SD.begin(SD_CS);
	if (!SD.begin(SD_CS)) {
		Serial.println("Error modulo SD!");
		return false;
	}
	uint8_t cardType = SD.cardType();
	if (cardType == CARD_NONE) {
		Serial.println("Error tarjeta SD!");
		return false;
	}
	if (!SD.begin(SD_CS)) {
		Serial.println("ERROR - Falla en tarjeta SD!");
		return false;
	}
	return 1;
}

bool  enviar_a_API(String dato) {
	Serial.println (dato);
	return 1;
}