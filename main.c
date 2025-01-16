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
       ADCProcessorTrigger(ADC0_BASE,1); //yaz�l�mla tetikliyorum
       //adc �rnekleri almaya ba�lad�m
       //    ADCIntStatus(ADC0_BASE, 1, true)=1 gelmi� olursa adc �evrim i�lemini bitirmi� olur
       while(!ADCIntStatus(ADC0_BASE, 1, false)){} //bekleme i�lmei yapmak istedi�im i�in while kullan�yoruz //burada bekliyoruz kesmesiz bir �rnek
       //buraya gelmi�se  sequence 1 den 4 kanaldan bilgi gelmi� olur
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
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0); //sequence ayar�: adc0 � kullan ve sequence 1 i se�
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_TS); //0 nolu step  //pe3-->CH0   hepsi i�in s�cakl�k sens�r� se�ildi
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_TS); //1 nolu step   //ilk ba�ta adc_ctl_ch0 ,1,2,3 yazm��t�k ama hoca pot olmad��� i�in dahili s�cakl�k sens�r� olan ts den devam ediyor
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_TS); //2 nolu step  //4 defa s�cakl�k sens�r� yazd�k ama bunlar�n hepsinin de�eri farkl�. birinci de�er al�yor , sonrakine yaz�yor vs ve bunlar s�ras�yla yap�l�yor
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_TS |ADC_CTL_IE|ADC_CTL_END ); //3 nolu step  //step i�lemini sonland�rmak i�in bu son iki paremetreyi yazd�k

    ADCSequenceEnable(ADC0_BASE, 1); //adc ayarlama bitti
    //daha adc �al��maya ba�lamad� ��nk� hen�z main de adcye �al�� demedik
}
