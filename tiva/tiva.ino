//*****************************************************************************
// Universidad del Valle de Guatemala
// BE3015: Electrónica Digital 2
// Sofía Salguero - 192236
// Código para Tiva C
//*****************************************************************************

//*****************************************************************************
//Definicion etiquetas
//*****************************************************************************
#define Potenciometro2 A11 //Potenciómetro2

//*****************************************************************************
//Varibles globales
//*****************************************************************************
int brillo = 0;        //Valor que toma el potenciómetro
int brilloAzul = 0;   //brillo del led Azul
int brilloVerde = 0; //brillo del led Verde
int brilloRojo = 0; //brillo del led Rojo

//*****************************************************************************
//Prototipos de funcion
//*****************************************************************************
void ledAzul(void); //Manejar brillo de led Azul
void botones(void); // Manejar brillo led Verde con botones

//*****************************************************************************
//configuracion
//*****************************************************************************
void setup()
{
  //Comunicación Serial
  Serial.begin(115200);
  Serial1.begin(115200);
  Serial2.begin(115200);

  //Definición de Leds
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(GREEN_LED, LOW);

  //Definición de botones
  pinMode(PUSH1, INPUT_PULLUP);
  pinMode(PUSH2, INPUT_PULLUP);
}

//*****************************************************************************
//loop principal
//*****************************************************************************
void loop()
{
  //Se manejan los leds verde y azul
  botones();
  ledAzul();
  //Se recibe el dato del led rojo para manejar el led rojo
  brilloRojo = Serial2.read(); //Lee en UART2
  analogWrite(RED_LED, brilloRojo);

  Serial2.write(brilloVerde); //Escribe en UART2
  delay(10);
  //Se muestran valores en monitor serial
  Serial.println("*****Valores para leds*****");
  Serial.print("Rojo: ");
  Serial.print(brilloRojo);
  Serial.print('\n');
  delay(10);
  Serial.print("Verde: ");
  Serial.print(brilloVerde);
  Serial.print('\n');
  delay(10);
  Serial.print("Azul: ");
  Serial.print(brilloAzul);
  Serial.print('\n');
  delay(10);
}

//*****************************************************************************
// Lectura potenciometro para led azul
//*****************************************************************************
void ledAzul(void)
{
  brillo = analogRead(Potenciometro2); //Lee el valor del potenciómetro
  brilloAzul = map(brillo, 0, 4095, 0, 255); //Mapea de 12 a 8 bits
  analogWrite(BLUE_LED, brilloAzul);      //Escribe la cantidad del potenciometro en el brillo
}

//*****************************************************************************
// Botones para controlar led verde
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
