//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrónica Digital 2
//*****************************************************************************

//*****************************************************************************
//Definicion etiquetas
//*****************************************************************************
#define Potenciometro2 A11

//*****************************************************************************
//Varibles globales
//*****************************************************************************
int brillo = 0; //Valor que toma el potenciómetro
int brilloAzul = 0; //brillo del led Azul
int brilloVerde = 0;
int brilloRojo = 0;
//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void ledAzul(void);
void botones(void);

//*****************************************************************************
//configuracion
//*****************************************************************************

void setup()
{
  Serial2.begin(115200);
  Serial.begin(115200);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  botones();
  delay(10);
  ledAzul();
  delay(10);
  Serial2.write(brilloVerde); //Escribe en UART 2
  delay(10);
  brilloRojo = Serial2.read(); //Lee en UART2
  analogWrite(RED_LED, brilloRojo);
  delay(10);
  Serial.println("*****Valores para leds*****");
  Serial.print("Rojo: ");
  Serial.print(brilloRojo);
  Serial.write('\n');
  delay(10);
  Serial.print("Verde: ");
  Serial.print(brilloVerde);
  Serial.write('\n');
  delay(10);
  Serial.print("Azul: ");
  Serial.print(brilloAzul);
  Serial.write('\n');
  delay(10);
}

//*****************************************************************************
// Lectura potenciometro
//*****************************************************************************
void ledAzul(void)
{
  brillo = analogRead(Potenciometro2); //Lee el valor del potenciómetro
  brilloAzul = map(brillo, 0, 4095, 0, 255);
  analogWrite(BLUE_LED, brilloAzul);      //Escribe la cantidad del potenciometro en el brillo
}

//*****************************************************************************
// Botones
//*****************************************************************************
void botones(void)
{
  if (digitalRead(PUSH1) == LOW)
  {
    brilloVerde = brilloVerde + 5;
    if (brilloVerde >= 255)
    {
      brilloVerde = 0;
    }
  }

  if (digitalRead(PUSH2) == LOW)
  {
    brilloVerde = brilloVerde - 5;
    if (brilloVerde <= 0)
    {
      brilloVerde = 255;
    }
  }

  analogWrite(GREEN_LED, brilloVerde);
}
