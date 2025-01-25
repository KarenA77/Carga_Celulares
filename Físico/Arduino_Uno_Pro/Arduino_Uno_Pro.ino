// include the library code:
#include <LiquidCrystal.h>
#include <LedControl.h>

// LCD Pines 
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// LED PINES
int LED = 6;

// HC-SR04 Pines
int TRIG = 10;
int ECHO = 9;
int DURACION, DISTANCIA;

int TRIG1 = 8;
int ECHO1 = 7;
int DURACION1, DISTANCIA1;


// Photoelectric Sensor Pines
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(1000);

  // HC-SR04 PinMode
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);
  pinMode(TRIG1, OUTPUT); 
  pinMode(ECHO1, INPUT);
  Serial.begin(9600);  		// inicializacion de comunicacion serial a 9600 bps

  // LED PinMode
  pinMode(LED, OUTPUT); 
  
}

void loop() {
  
  //-----------------BOX ONE --------------------------------
  //-------------- CODE FOR HC-SR04-------------------------
  digitalWrite(TRIG, HIGH); 		// generacion del pulso a enviar
  delay(1);				// al pin conectado al trigger
  digitalWrite(TRIG, LOW);		// del sensor

  
  DURACION = pulseIn(ECHO, HIGH);	// con funcion pulseIn se espera un pulso
  DISTANCIA = DURACION / 58.2;		// distancia medida en centimetros
  Serial.print("Distancia del Objeto 1: ");
  Serial.println(DISTANCIA);		// envio de valor de distancia por monitor serial
  Serial.println(" cm");
  delay(100);

  //Code for Fotoresistence
  // read the input on analog pin A0 - Box1
  int sensorValue1 = analogRead(A0);
  // print out the value you read:
  Serial.println("1: ");
  Serial.println(sensorValue1);
  delay(100);  // delay in between reads for stability

  // Puerta Abierta Sin Ojeto
  if(DISTANCIA >= 10 && sensorValue1 <= 499){
    digitalWrite(LED, HIGH); //Indicates if the door is Open

    // CODE FOR LCD
    lcd.setCursor(0, 0); // Move the LCD to the left
    lcd.print("No object found on 1");
    }
  // Puerta abierta Con Objeto Esperado


  if(DISTANCIA <=10 && 940 <=sensorValue1 <= 989){
    digitalWrite(LED, HIGH); //Indicates if the door is Open
    //digitalWrite(LED, LOW);

    // CODE FOR LCD
    // Move the LCD to the left
    lcd.setCursor(0, 0);
    lcd.print("Object found on 1");
  }

  // Puerta Cerrada con Objeto
     //** Poner led para la puerta y solo marcar objeto en el LCDs
  if(DISTANCIA <=10 && sensorValue1 >= 1020 ){
    digitalWrite(LED, LOW); //Indicates if the door is Close

    // CODE FOR LCD
    lcd.setCursor(0, 0);
    lcd.print("Object Inside on 1");  // Move the LCD to the left
  }


  // Puerta Cerrada sin objeto
  if(DISTANCIA >=10 && (sensorValue1 >= 995 && sensorValue1 <= 1019)){
    digitalWrite(LED, LOW); //Indicates if the door is Close

    // CODE FOR LCD
    lcd.setCursor(0, 0);
    lcd.print("No Object found on 1"); // Move the LCD to the left
  }






  //-----------------BOX TWO --------------------------------

  digitalWrite(TRIG1, HIGH); 		// generacion del pulso a enviar
  delay(1);				// al pin conectado al trigger
  digitalWrite(TRIG1, LOW);		// del sensor

  
  DURACION1 = pulseIn(ECHO1, HIGH);	// con funcion pulseIn se espera un pulso
  DISTANCIA1 = DURACION1 / 58.2;		// distancia medida en centimetros
  Serial.print("Distancia del Objeto 2: ");
  Serial.println(DISTANCIA1);		// envio de valor de distancia por monitor serial
  Serial.println(" cm");
  delay(100);
   // read the input on analog pin 1 - Box 2:
  int sensorValue2 = analogRead(A1);
  // print out the value you read:
  Serial.println("2: ");
  Serial.println(sensorValue2);
  delay(500);  // delay in between reads for stability

  // Puerta Abierta Sin Ojeto
  if(DISTANCIA1 >= 10 && sensorValue2 <= 499){
    digitalWrite(LED, HIGH); //Indicates if the door is Open

    // CODE FOR LCD
    lcd.setCursor(0, 1);
    lcd.write("No object found on 2"); // Move the LCD to the left 
    }


  // Puerta abierta Con Objeto Esperado
  if(DISTANCIA1 <=10 && 940 <=sensorValue2 <= 989){
    digitalWrite(LED, HIGH); //Indicates if the door is Open

    // CODE FOR LCD
    lcd.setCursor(0, 1);
    lcd.write("Object found on 2"); // Move the LCD to the left
  }


  // Puerta Cerrada con Objeto
     //** Poner led para la puerta y solo marcar objeto en el LCDs
  if(DISTANCIA1 <=10 && sensorValue2 >= 1020 ){
    digitalWrite(LED, LOW); //Indicates if the door is Close

    // CODE FOR LCD
    lcd.setCursor(0, 1);
    lcd.print("Object Inside on 2");  // Move the LCD to the left
  }


  // Puerta Cerrada sin objeto
  if(DISTANCIA1 >=10 && (sensorValue2 >= 995 && sensorValue2 <= 1019)){
    digitalWrite(LED, LOW); //Indicates if the door is Close

    // CODE FOR LCD
    lcd.setCursor(0, 1);  // Move the LCD to the left
    lcd.print("No Object found on 2");
  }

   //---------------------------------------------------


  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(200);
  } 
  
  // Turn off the display:
  lcd.noDisplay();
  delay(100);
  // Turn on the display:
  lcd.display();
  delay(100);


}
