#include <LCD5110_Basic.h> //Burada Kütüphane Kullanılıyor.
#include "HX711.h" //Burada Kütüphane Kullanılıyor.

LCD5110 myGLCD(8,9,10,11,12); //Burada LCD Ekranın Baglı Olduğu Pinleri Tanımlıyoruz.
extern unsigned char BigNumbers[]; //Burada LCD Ekrandaki Yazılar İçin Kütüphane Kullanıyoruz.

HX711 scale; // Yük Sensörü "scale" Olarak Tanımlanıyor.
int deger; // "deger" İsmi Tanımlanıyor.
int kuvvet = 0  ; // "kuvvet" İsminde Bir Değişken Tanımlanıyor.
int kalibre;
int IN1 = 3; //Direction
int IN2 = 4; //Direction

void setup()
{
  myGLCD.InitLCD(); // LCD Başlatılıyor.
  scale.begin(A1, A0); // "A1" Ve "A0" Pinlerinden Veri Alındığını Arduino'ya Anlatıyor.
  yaz(); // "yaz" Adlı Fonksiyon Tanımlanıyor.
  pinMode(IN1,OUTPUT); // Burada 2. Dijital Pin "Çıkış Pini" Olarak Tanımlanmış.
  pinMode(IN2,OUTPUT); // Burada 4. Dijital Pin "Çıkış Pini" Olarak Tanımlanmış.
  kalibre = (scale.get_units()*-1)/10000; // Değeri Sıfırlamak İçin Matematiksel İşlem Yapılıyor.
  delay(2000);
}

void loop()
{
  deger = (scale.get_units()*-1)/10000; // Değeri Sıfırlamak İçin Matematiksel İşlem Yapılıyor.
  deger = deger - kalibre;
  yaz(); // "yaz" Fonksiyonu Kullanılıyor.
}
void yaz(){ // "yaz" Bu Block İçinde Tanımlanıyor.
    myGLCD.clrScr(); // Burada Ekranı Temizliyor.
    myGLCD.setFont(BigNumbers); // Burada Yazının Tipini Belirliyor.
    myGLCD.printNumF(deger,0, CENTER, 12); // Burada Yazıyı Ortalıyor.
    if(deger - 20 < kuvvet){ // Eğer "kuvvet" "deger"den büyükse; (Aşağıdaki Kodları Çalıştır.)
      digitalWrite(IN1, 0); // Burada Motoru Bir Yöne Döndürmek İçin Gerekli Gücü Gönderiyor.
      digitalWrite(IN2, 1); // Burada Motoru Bir Yöne Döndürmek İçin Gerekli Gücü Gönderiyor.
      delay(500);
      digitalWrite(IN1, 0); // Burada Motoru Durdurmak İçin Gerekli Gücü Gönderiyor.
      digitalWrite(IN2, 0); // Burada Motoru Durdurmak İçin Gerekli Gücü Gönderiyor.
      delay(500);
      }
    if(deger > kuvvet + 20){// Eğer "kuvvet" "deger"den küçükse; (Aşağıdaki Kodları Çalıştır.)
      digitalWrite(IN1, 1); // Burada Motoru Ters Yöne (Yukarıdakine Göre) Döndürmek İçin Gerekli Gücü Gönderiyor.
      digitalWrite(IN2, 0); // Burada Motoru Ters Yöne (Yukarıdakine Göre) Döndürmek İçin Gerekli Gücü Gönderiyor.
      delay(500);
      digitalWrite(IN1, 0); // Burada Motoru Durdurmak İçin Gerekli Gücü Gönderiyor.
      digitalWrite(IN2, 0); // Burada Motoru Durdurmak İçin Gerekli Gücü Gönderiyor.
      delay(500);
      }
  }
