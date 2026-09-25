#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

// ==========================
// KONFIGURASI
// ==========================

#define PB_JAM 18
#define PB_MENIT 19

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;

// Variabel untuk debounce tombol
bool lastJamState = HIGH;
bool lastMenitState = HIGH;

unsigned long lastDebounceJam = 0;
unsigned long lastDebounceMenit = 0;

const unsigned long debounceDelay = 200;


// ==========================
// SETUP
// ==========================

void setup() {

    Serial.begin(115200);

    // I2C ESP32
    Wire.begin(21, 22);

    // LCD
    lcd.init();
    lcd.backlight();

    // Push button
    pinMode(PB_JAM, INPUT_PULLUP);
    pinMode(PB_MENIT, INPUT_PULLUP);

    // RTC
    if (!rtc.begin()) {

        Serial.println("RTC DS1307 tidak terdeteksi!");

        lcd.setCursor(0, 0);
        lcd.print("RTC not found!");

        while (1) {
            delay(10);
        }
    }

    // Jika RTC belum berjalan
    if (!rtc.isrunning()) {

        Serial.println("RTC tidak berjalan!");

        // Atur waktu awal
        rtc.adjust(DateTime(2026, 9, 24, 19, 0, 0));
    }

    Serial.println("RTC DS1307 Ready");

    lcd.setCursor(0, 0);
    lcd.print("RTC DS1307");
    lcd.setCursor(0, 1);
    lcd.print("Ready...");

    delay(1500);

    lcd.clear();
}


// ==========================
// LOOP
// ==========================

void loop() {

    DateTime now = rtc.now();


    // =================================
    // TOMBOL JAM
    // =================================

    bool jamState = digitalRead(PB_JAM);

    if (jamState == LOW && lastJamState == HIGH) {

        if (millis() - lastDebounceJam > debounceDelay) {

            int jamBaru = now.hour() + 1;

            // Sistem 24 jam
            if (jamBaru >= 24) {
                jamBaru = 0;
            }

            rtc.adjust(DateTime(
                now.year(),
                now.month(),
                now.day(),
                jamBaru,
                now.minute(),
                now.second()
            ));

            Serial.print("Jam ditambah: ");

            if (jamBaru < 10)
                Serial.print("0");

            Serial.println(jamBaru);

            lastDebounceJam = millis();
        }
    }

    lastJamState = jamState;


    // =================================
    // TOMBOL MENIT
    // =================================

    bool menitState = digitalRead(PB_MENIT);

    if (menitState == LOW && lastMenitState == HIGH) {

        if (millis() - lastDebounceMenit > debounceDelay) {

            int menitBaru = now.minute() + 1;

            int jamBaru = now.hour();

            // Jika menit mencapai 60
            if (menitBaru >= 60) {

                menitBaru = 0;

                // Jam ikut bertambah
                jamBaru++;

                // Sistem 24 jam
                if (jamBaru >= 24) {
                    jamBaru = 0;
                }
            }

            rtc.adjust(DateTime(
                now.year(),
                now.month(),
                now.day(),
                jamBaru,
                menitBaru,
                now.second()
            ));

            Serial.print("Menit ditambah: ");

            if (jamBaru < 10)
                Serial.print("0");

            Serial.print(jamBaru);
            Serial.print(":");

            if (menitBaru < 10)
                Serial.print("0");

            Serial.println(menitBaru);

            lastDebounceMenit = millis();
        }
    }

    lastMenitState = menitState;


    // =================================
    // TAMPILKAN WAKTU DI LCD
    // =================================

    now = rtc.now();

    // Baris 1
    lcd.setCursor(0, 0);

    lcd.print(now.year());
    lcd.print("/");

    if (now.month() < 10)
        lcd.print("0");

    lcd.print(now.month());
    lcd.print("/");

    if (now.day() < 10)
        lcd.print("0");

    lcd.print(now.day());


    // Baris 2
    lcd.setCursor(0, 1);

    if (now.hour() < 10)
        lcd.print("0");

    lcd.print(now.hour());

    lcd.print(":");

    if (now.minute() < 10)
        lcd.print("0");

    lcd.print(now.minute());

    lcd.print(":");

    if (now.second() < 10)
        lcd.print("0");

    lcd.print(now.second());

    lcd.print("    ");


    delay(100);
}