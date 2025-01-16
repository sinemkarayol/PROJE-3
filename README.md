# PROJE-3
ADC Kullanımı (Tiva C TM4C123)

Bu proje, Texas Instruments Tiva C TM4C123 serisi mikrodenetleyiciler ile dahili sıcaklık sensörünü kullanarak ADC (Analog-Digital Converter) işlemini gerçekleştirmektedir. ADC, sıcaklık verisini alıp işleyerek dijital ortama aktarmaktadır.

Özellikler
Dahili sıcaklık sensöründen veri okuma
ADC modülü ile 4 örnek alıp ortalama hesaplama
Yazılımla ADC tetikleme
Kesmesiz (polling) ADC kullanımı

Donanım Gereksinimleri
Tiva C TM4C123GXL LaunchPad
Dahili sıcaklık sensörü (TS) (Ekstra sensör bağlantısı gerektirmez)

Dosya Açıklamaları
main.c: Ana program dosyası, ADC başlatma ve sıcaklık hesaplama işlemlerini içerir.
setinitsettings(): ADC ve sistem saat ayarlarını içeren fonksiyon.

Kullanılan Kütüphaneler
Kod, TivaWare sürücü kütüphanesini kullanmaktadır. TivaWare yüklü olmalıdır.
driverlib/gpio.h
driverlib/sysctl.h
driverlib/adc.h
inc/hw_types.h
inc/hw_memmap.h
inc/hw_gpio.h

Çalışma Mantığı
ADC başlatılır ve konfigüre edilir.
Yazılım aracılığıyla ADC tetiklenir.
ADC dönüşümü tamamlanana kadar beklenir.
4 farklı sıcaklık örneği alınır ve ortalama hesaplanır.
Hesaplanan sıcaklık değeri, Celcius cinsine çevrilir.

Kurulum ve Derleme
TivaWare Kurulumu: TivaWare Download
Code Composer Studio (CCS) veya Keil IDE kullanarak derleyin.
Tiva C TM4C123 LaunchPad'e yükleyin.
Sıcaklık verilerini gözlemleyin.
