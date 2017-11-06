// SELPIN   10   //Selection Pin (CS)
// DATAOUT  11   //MOSI 
// DATAIN   12   //MISO 
// SPICLOCK 13   //Clock

/*
//AH_MCP320x.h functions
    //free pin mode declaration
AH_MCP320x(int CS_pin, int DOUT_pin, int DIN_pin, int CLK_pin)
    //SPI mode declaration
AH_MCP320x(int CS_pin)
    //read channel ADC value
int readCH(int CHANNEL)
    //read all channels
void readALL(int values[], int n)
    //read saved configuration of all channels
void getCONFIG(int config[],int n)
    //set config of measurement mode: single or differential
void setCONFIG(int CHANNEL, boolean SINGLE)
    //set all channels to diff. mode
void setCONFIG_allDiff(int n)
    //set all channels to single mode
void setCONFIG_allSingle(int n)
    //calculate the input voltage from ADC and VREF
float calcVOLT(float VREF, int ADCvalue)

*/


#include "AH_MCP320x.h"
#include <SPI.h>

int RIGHTARM = 17;
int LEFTARM = 2;
int ADCValue = 0;
float time_in;
float time_out;

//MCP320x ADC Chips Configuration
//int ADCValue = 0;
int ADC_A_Values[8];                //definition of Array for measured values
int ADC_B_Values[8];                //definition of Array for measured values
int ADC_C_Values[8];                //definition of Array for measured values
int ADC_D_Values[8];                //definition of Array for measured values

AH_MCP320x ADC_A_SPI(RIGHTARM);            //D8 as CS, other pins are defined by spi interface (faster mode).
AH_MCP320x ADC_B_SPI(LEFTARM);             //D7 as CS, other pins are defined by spi interface (faster mode).

void setup()
{
  Serial.begin(57600);
}

void loop()
{  
  
  ADC_A_SPI.readALL(ADC_A_Values,8);    //read all 8 channels (SPI mode)
  ADC_B_SPI.readALL(ADC_B_Values,8);    //read all 8 channels (SPI mode)
  
  String spacer = "";    // default ""
  String delim = ",";  // default ","
  
  int value = 0;
  for(int i=0;i<8;i++)   // i<8 at MCP3208 
  {
    value = ADC_A_Values[i]; 
    if(value<10){
      Serial.print(spacer);   
    } 
    if(value<100){
      Serial.print(spacer);   
    } 
    if(value<1000){
      Serial.print(spacer);   
    } 
    Serial.print(value);   
    Serial.print(delim);   
  }
  
  Serial.print(",");   
  
  for(int i=0;i<8;i++)   // i<8 at MCP3208 
  {  
    value = ADC_B_Values[i]; 
    if(value<10){
      Serial.print(spacer);   
    } 
    if(value<100){
      Serial.print(spacer);   
    } 
    if(value<1000){
      Serial.print(spacer);   
    } 
    Serial.print(value);   
    Serial.print(delim);   
  }
  Serial.println("");
  delay (1);
}


