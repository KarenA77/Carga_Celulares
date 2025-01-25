// include the library code:
#include <LiquidCrystal.h>
#include <LedControl.h>

// LCD Pines 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LED = 6;

void setup() 
{
  Serial.begin(9600); 
  pinMode(7, OUTPUT); 
  pinMode(6, INPUT);
  pinMode(LED, INPUT);
  pinMode(8, OUTPUT);

  //Configurar el número de columnas y filas de la pantalla LCD:
  lcd.begin(16, 2);
  delay(1000);
}

void loop() 
{
  //Borra la condición Trig Pin
  digitalWrite(7, LOW);
  delayMicroseconds(2);
  
  //Establece el Trig Pin HIGH (ACTIVO) durante 10 microsegundos
  digitalWrite(7, HIGH);
  delayMicroseconds(10);
  digitalWrite(7, LOW);
  
  //Lee el Echo Pin, devuelve el tiempo de viaje de la onda de sonido en microsegundos
  long Duration = pulseIn(6, HIGH);
  
  //Calculando la distancia
  int Distance = Duration * 0.034 / 2; // Velocidad de la onda de sonido dividida por 2 (ida y vuelta)
  
  //Muestra la distancia en el Monitor Serie
  Serial.print("Distancia: ");
  Serial.print(Distance);
  Serial.println(" cm");

  //Condincionar la distancia
  int sensorValue = analogRead(A0);
  Serial.println("Intensidad de la luz: " );
  Serial.println(sensorValue);
  delay(1);
  if((Distance >= 20 && Distance >=25) && sensorValue<=25){
    digitalWrite(LED, HIGH);
    delay(Distance * 10);
    digitalWrite(LED, LOW);
    //Mover el LCD a la izquierda.
    digitalWrite(10, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("No se encontró ningún objeto");
    lcd.setCursor(0, 1);
    lcd.write("No se encontró ningún objeto");
  }else{
    digitalWrite(10, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Se encontró el objeto");
    lcd.setCursor(0, 1);
    lcd.write("Se encontró el objeto");
  }

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    ////Mover el LCD a la izquierda.:
    lcd.scrollDisplayLeft();
    delay(30);
  }
}






