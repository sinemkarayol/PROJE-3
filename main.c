#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/sysctl.c"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "driverlib/adc.h"

void setinitsettings();


int main(void)
{
    setinitsettings();
    uint32_t temp;
   while(1)
   {
       ADCProcessorTrigger(ADC0_BASE,1); //yazýlýmla tetikliyorum
       //adc örnekleri almaya baþladým
       //    ADCIntStatus(ADC0_BASE, 1, true)=1 gelmiþ olursa adc çevrim iþlemini bitirmiþ olur
       while(!ADCIntStatus(ADC0_BASE, 1, false)){} //bekleme iþlmei yapmak istediðim için while kullanýyoruz //burada bekliyoruz kesmesiz bir örnek
       //buraya gelmiþse  sequence 1 den 4 kanaldan bilgi gelmiþ olur
       uint32_t gelendata[4];
       ADCSequenceDataGet(ADC0_BASE, 1, gelendata);
       uint32_t ortalamadeger=(gelendata[0]+gelendata[1]+gelendata[2]+gelendata[3])/4;
       temp =(1475-((2475*ortalamadeger)/4096))/10;
   }


}

void setinitsettings()
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); //adc hayat=1
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); //sequence ayarý: adc0 ý kullan ve sequence 1 i seç
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS); //0 nolu step  //pe3-->CH0   hepsi için sýcaklýk sensörü seçildi
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS); //1 nolu step   //ilk baþta adc_ctl_ch0 ,1,2,3 yazmýþtýk ama hoca pot olmadýðý için dahili sýcaklýk sensörü olan ts den devam ediyor
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS); //2 nolu step  //4 defa sýcaklýk sensörü yazdýk ama bunlarýn hepsinin deðeri farklý. birinci deðer alýyor , sonrakine yazýyor vs ve bunlar sýrasýyla yapýlýyor
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS |ADC_CTL_IE|ADC_CTL_END ); //3 nolu step  //step iþlemini sonlandýrmak için bu son iki paremetreyi yazdýk

    ADCSequenceEnable(ADC0_BASE, 1); //adc ayarlama bitti
    //daha adc çalýþmaya baþlamadý çünkü henüz main de adcye çalýþ demedik
}
