//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrónica Digital 2
//*****************************************************************************

//*****************************************************************************
//Librerias
//*****************************************************************************
#include <LiquidCrystal.h> //libreria para LCD

//*****************************************************************************
//Definicion etiquetas
//*****************************************************************************

//Potenciometros
#define Potenciometro1 15

//LCD
#define d4 14
#define d5 27
#define d6 26
#define d7 25
#define en 12 //Sincronización
#define rs 13 //Selector

//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void emaADC(void);
void valores(void);
void mapeo(void);
void leds(void);
void uart(void);

//*****************************************************************************
//Varibles globales
//*****************************************************************************
int rojo = 0;
int verde = 0;
int azul = 0;

//Variables para filtro Medio Móvil Exponencial
float adcRaw1 = 0.0;     //Valor Crudo potenciómetro 1
double rojoFiltrado = 0; //S(0) = Y(0)
double alpha = 0.09;     // Factor de suavizado
float voltage = 0.0;     //Valor de voltaje filtrado

//LCD
LiquidCrystal LCD(rs, en, d4, d5, d6, d7);
uint8_t centena1, decena1, unidad1; //Led Rojo
uint8_t centena2, decena2, unidad2; //Led Verde
uint8_t centena3, decena3, unidad3; //Led Azul

//UART
byte mensaje = 0;

//*****************************************************************************
//configuracion
//*****************************************************************************
void setup()
{
  Serial2.begin(115200);
  Serial.begin(115200);

  LCD.begin(16, 2);
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  uart();
  emaADC();
  mapeo();
  valores();

  LCD.setCursor(0, 0);
  LCD.print("Rojo");
  LCD.setCursor(0, 1);
  LCD.print(centena1);
  LCD.print(decena1);
  LCD.print(unidad1);

  LCD.setCursor(5, 0);
  LCD.print("Verde");
  LCD.setCursor(5, 1);
  LCD.print(centena2);
  LCD.print(decena2);
  LCD.print(unidad2);

  LCD.setCursor(11, 0);
  LCD.print("Azul");
  LCD.setCursor(11, 1);
  LCD.print(centena3);
  LCD.print(decena3);
  LCD.print(unidad3);
}

//****************************************************************
// Filtro media Móvil exponencial EMA
//****************************************************************
void emaADC(void)
{
  adcRaw1 = analogRead(Potenciometro1);                              //toma valor que está midiendo el potenciometro
  rojoFiltrado = (alpha * adcRaw1) + ((1.0 - alpha) * rojoFiltrado); //filtra ese valor
}

//****************************************************************
// Función para mapear valores leido a 8 bits
//****************************************************************
void mapeo(void)
{
  rojo = map(rojoFiltrado, 0, 4095, 0, 255);
}

//****************************************************************
// Función para tomar valores y dividirlos para LCD
//****************************************************************
void valores(void)
{
  //Primer potenciómetro
  int temp1 = rojo;
  centena1 = temp1 / 100.0;
  temp1 = temp1 - centena1 * 100.0;
  decena1 = temp1 / 10.0;
  temp1 = temp1 - decena1 * 10.0;
  unidad1 = temp1;

  //Segundo potenciómetro
  int temp2 = verde;
  centena2 = temp2 / 100.0;
  temp2 = temp2 - centena2 * 100.0;
  decena2 = temp2 / 10.0;
  temp2 = temp2 - decena2 * 10.0;
  unidad2 = temp2;

  //Contador
  int temp3 = azul;
  centena3 = temp3 / 100.0;
  temp3 = temp3 - centena3 * 100.0;
  decena3 = temp3 / 10.0;
  temp3 = temp3 - decena3 * 10.0;
  unidad3 = temp3;
}

//****************************************************************
// Lectura de computadora
//****************************************************************
void uart(void)
{
  while (Serial2.available() > 0)
  {
    verde = Serial2.read(); //Lee de UART2
    Serial2.write(rojo); //Escribe en UART2
    azul = Serial.read(); //Escribe en UART 0
  }
}
