// Copyright (c) 2021 Raphael Champeimont

// Code designed for Arduino Leonardo

#include "ArduinoFDC.h"

const int NUM_TRACKS = 80;
const int NUM_HEADS = 2;
const int NUM_SECTORS_PER_TRACK = 18;

byte buf[516];

const unsigned int BUFSIZE = 512;
const unsigned int SEND_BATCH_SIZE = 64; // must be a divisor of BUFSIZE

const int DATA_ASKED_PIN = A5;
const int DEBUG_PIN = A4;

// Special optimized read order for speed
const byte SECTOR_READ_ORDER[18] = {1, 3, 5, 7, 9, 11, 13, 15, 17, 2, 4, 6, 8, 10, 12, 14, 16, 18};

unsigned int globalSectorCounter = 0;

void setup() {
  Serial.begin(115200); // used to send debug messages to computer
  Serial1.begin(1E6, SERIAL_8E1); // used to transmit data to other Arduino
  //Serial1.begin(9600, SERIAL_8E1); // used to transmit data to other Arduino

  // Start floppy drive
  ArduinoFDC.begin();
  ArduinoFDC.motorOn();

  pinMode(DEBUG_PIN, OUTPUT);
}

void niceExit() {
  Serial.println("Exiting");
  ArduinoFDC.motorOff();
  delay(1000);
  exit(0);
}

void transmit() {
  // Send the data to "sound player" Arduino
  for (int i = 0; i < BUFSIZE; i += SEND_BATCH_SIZE) {
    // Wait for receiver to be ready to get data
    while (digitalRead(DATA_ASKED_PIN) == LOW);
    // Send batch
    Serial1.write(buf + 1 + i, SEND_BATCH_SIZE);
  }
}

void loop() {
  byte head, track, sector;

  for (track = 0; track < NUM_TRACKS; track++) {
    Serial.print("Track ");
    Serial.println(track);
    for (head = 0; head < NUM_HEADS; head++) {
      for (byte i = 0; i < NUM_SECTORS_PER_TRACK; i++) {
        sector = SECTOR_READ_ORDER[i];

        byte status = ArduinoFDC.readSector(track, head, sector, buf);

        if (status != 0) {
          if (status == S_NOTREADY) {
            Serial.println("Floppy removed. Restarting.");
            return;
          } else {
            Serial.println("Read error");
          }
        } else {
          transmit();
        }
      }
    }
  }
}
