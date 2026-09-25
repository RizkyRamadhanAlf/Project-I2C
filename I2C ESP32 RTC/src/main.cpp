#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS1307 rtc;

void setup() {
    Serial.begin(115200);

    Wire.begin(21, 22);

    lcd.init();
    lcd.backlight();

    // Cek RTC
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
    }

    lcd.setCursor(0, 0);
    lcd.print("RTC DS1307");
    lcd.setCursor(0, 1);
    lcd.print("Ready...");

    delay(1500);
    lcd.clear();

    Serial.println("================================");
    Serial.println("RTC DS1307 READY");
    Serial.println("================================");
    Serial.println("Untuk mengatur waktu, ketik:");
    Serial.println("SETTIME hh:mm:ss");
    Serial.println("Contoh:");
    Serial.println("SETTIME 14:30:00");
    Serial.println("================================");
}

void loop() {

    // ==================================
    // MEMBACA INPUT DARI SERIAL MONITOR
    // ==================================

    if (Serial.available() > 0) {

        String input = Serial.readStringUntil('\n');
        input.trim();

        // Cek apakah diawali dengan SETTIME
        if (input.startsWith("SETTIME ")) {

            // Ambil bagian waktu
            String waktu = input.substring(8);

            // Format harus hh:mm:ss = 8 karakter
            if (waktu.length() == 8 &&
                waktu.charAt(2) == ':' &&
                waktu.charAt(5) == ':') {

                int hour = waktu.substring(0, 2).toInt();
                int minute = waktu.substring(3, 5).toInt();
                int second = waktu.substring(6, 8).toInt();

                // Validasi waktu
                if (hour >= 0 && hour <= 23 &&
                    minute >= 0 && minute <= 59 &&
                    second >= 0 && second <= 59) {

                    // Ambil tanggal yang sedang digunakan RTC
                    DateTime now = rtc.now();

                    // Ubah waktu RTC
                    rtc.adjust(DateTime(
                        now.year(),
                        now.month(),
                        now.day(),
                        hour,
                        minute,
                        second
                    ));

                    Serial.println("Waktu RTC berhasil disesuaikan!");

                    Serial.print("Waktu baru: ");

                    if (hour < 10) Serial.print('0');
                    Serial.print(hour);
                    Serial.print(':');

                    if (minute < 10) Serial.print('0');
                    Serial.print(minute);
                    Serial.print(':');

                    if (second < 10) Serial.print('0');
                    Serial.println(second);

                } else {
                    Serial.println("Waktu tidak valid!");
                    Serial.println("Gunakan jam 00-23, menit 00-59, detik 00-59.");
                }

            } else {
                Serial.println("Format salah!");
                Serial.println("Gunakan: SETTIME hh:mm:ss");
                Serial.println("Contoh: SETTIME 14:30:00");
            }

        } else {
            Serial.println("Perintah tidak dikenal.");
            Serial.println("Gunakan: SETTIME hh:mm:ss");
        }
    }

    // ==================================
    // MEMBACA WAKTU RTC
    // ==================================

    DateTime now = rtc.now();

    // Baris 1: Tanggal
    lcd.setCursor(0, 0);

    lcd.print(now.year());
    lcd.print('/');

    if (now.month() < 10) lcd.print('0');
    lcd.print(now.month());

    lcd.print('/');

    if (now.day() < 10) lcd.print('0');
    lcd.print(now.day());

    // Baris 2: Waktu
    lcd.setCursor(0, 1);

    if (now.hour() < 10) lcd.print('0');
    lcd.print(now.hour());

    lcd.print(':');

    if (now.minute() < 10) lcd.print('0');
    lcd.print(now.minute());

    lcd.print(':');

    if (now.second() < 10) lcd.print('0');
    lcd.print(now.second());

    lcd.print("    ");

    delay(500);
}