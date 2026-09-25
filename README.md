# Project-I2C

# Praktikum ESP32 – Pengaturan Waktu RTC dengan Serial Monitor dan Push Button

Repository ini berisi hasil praktikum **Internet of Things (IoT)** menggunakan **ESP32** dan modul **RTC (Real-Time Clock)** untuk melakukan pengaturan serta pemantauan waktu secara real-time.

Pada praktikum ini, sistem dibuat dengan dua metode pengaturan waktu, yaitu melalui **komunikasi serial menggunakan Serial Monitor** dan melalui **dua buah push button**. RTC digunakan untuk menyimpan dan menjaga informasi waktu sehingga ESP32 dapat menampilkan waktu secara akurat selama sistem berjalan.

## Tujuan Praktikum

Praktikum ini bertujuan untuk:

1. Memahami penggunaan modul RTC pada ESP32.
2. Memahami komunikasi serial antara ESP32 dengan komputer melalui Serial Monitor.
3. Mengimplementasikan perintah untuk mengatur waktu RTC melalui input teks.
4. Mengimplementasikan push button sebagai input untuk mengubah nilai jam dan menit.
5. Menerapkan sistem waktu **24 jam** pada RTC.
6. Memahami proses pembacaan, pengaturan, dan perubahan waktu pada modul RTC.

## Fitur Program

Program yang dibuat memiliki beberapa fitur utama:

### 1. Pengaturan Waktu melalui Serial Monitor

Pengguna dapat mengatur waktu RTC dengan mengetikkan perintah berikut pada Serial Monitor:

```text
SETTIME hh:mm:ss
```

Contoh:

```text
SETTIME 14:30:00
```

Setelah perintah diterima dan format waktu valid, ESP32 akan melakukan penyesuaian waktu pada RTC sesuai dengan waktu yang diberikan.

### 2. Pengaturan Jam Menggunakan Push Button

Sistem menggunakan satu push button khusus untuk mengatur jam.

Setiap kali **PB Jam** ditekan, nilai jam pada RTC akan bertambah **1 jam**.

Contoh:

```text
14:30:00 → 15:30:00
```

Jika nilai jam mencapai `23`, kemudian tombol ditekan kembali, nilai jam akan kembali ke `00` sesuai dengan sistem waktu 24 jam.

### 3. Pengaturan Menit Menggunakan Push Button

Push button kedua digunakan untuk mengatur menit.

Setiap kali **PB Menit** ditekan, nilai menit pada RTC akan bertambah **1 menit**.

Contoh:

```text
14:30:00 → 14:31:00
```

Jika nilai menit mencapai `59`, kemudian tombol ditekan kembali, nilai menit akan kembali ke `00` dan jam akan bertambah 1.

## Sistem Waktu

Program menggunakan format waktu **24 jam**, yaitu:

```text
00:00:00 – 23:59:59
```

Format waktu yang ditampilkan terdiri dari:

* `hh` = Jam
* `mm` = Menit
* `ss` = Detik

Contoh tampilan:

```text
Time: 14:30:25
```

## Komponen yang Digunakan

Komponen utama yang digunakan dalam praktikum ini antara lain:

* ESP32
* Modul RTC
* 2 Push Button
* LCD I2C (jika digunakan pada rangkaian)
* Kabel jumper
* Breadboard
* Komputer/Laptop untuk Serial Monitor

## Konsep Kerja Sistem

Secara umum, alur kerja sistem adalah sebagai berikut:

1. ESP32 melakukan inisialisasi RTC dan komponen lainnya.
2. ESP32 membaca waktu yang tersimpan pada RTC.
3. Waktu ditampilkan melalui Serial Monitor atau media display yang digunakan.
4. ESP32 membaca input dari Serial Monitor.
5. Jika pengguna memasukkan perintah `SETTIME hh:mm:ss`, sistem akan memvalidasi format tersebut.
6. Jika format valid, waktu RTC akan diperbarui sesuai input.
7. ESP32 juga membaca kondisi kedua push button.
8. Jika PB Jam ditekan, nilai jam ditambah 1.
9. Jika PB Menit ditekan, nilai menit ditambah 1.
10. Sistem terus melakukan pembacaan dan menampilkan waktu secara real-time.

## Dokumentasi Praktikum

Repository ini juga memuat dokumentasi praktikum berupa:

* Gambar rangkaian ESP32 dan RTC.
* Kode program ESP32.
* Penjelasan program.
* Konfigurasi push button.
* Screenshot hasil running simulasi.
* Hasil pengujian pengaturan waktu melalui Serial Monitor.
* Hasil pengujian pengaturan jam dan menit menggunakan push button.
* Laporan praktikum.

## Hasil yang Diharapkan

Setelah program dijalankan, ESP32 dapat membaca dan menampilkan waktu dari RTC. Pengguna dapat melakukan pengaturan waktu melalui dua metode:

**Serial Monitor:**

```text
SETTIME 08:15:30
```

atau menggunakan:

**Push Button:**

```text
PB Jam   → Jam + 1
PB Menit → Menit + 1
```

Dengan demikian, sistem dapat digunakan sebagai implementasi sederhana pengaturan waktu berbasis **ESP32 dan RTC** dengan input melalui komunikasi serial maupun push button.

## Teknologi yang Digunakan

* **ESP32**
* **Arduino IDE / PlatformIO**
* **RTC**
* **I2C**
* **Serial Communication**
* **Push Button**
* **C/C++ Arduino**

## Struktur Repository

> Struktur folder dapat disesuaikan dengan isi repository.

## Kesimpulan

Praktikum ini menghasilkan sebuah sistem pengaturan waktu berbasis ESP32 dan RTC yang dapat dikontrol menggunakan komunikasi serial maupun push button. Pengaturan waktu melalui Serial Monitor dilakukan dengan perintah `SETTIME hh:mm:ss`, sedangkan push button digunakan untuk menambah nilai jam dan menit secara langsung. Sistem menggunakan format waktu 24 jam dan dapat digunakan sebagai dasar untuk pengembangan berbagai aplikasi IoT yang membutuhkan informasi waktu secara real-time.
