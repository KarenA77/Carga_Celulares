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



// Photoelectric Sensor Pines
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  delay(1000);

  /*// Print a message to the LCD.
  //Advertencia No hay ningún objeto en X
  lcd.print("No hay Ningun Objeto en 1");
  lcd.print("No hay Ningun Objeto en 2");

  //Advertencia Objeto Cambiado X
  lcd.print("Objeto Cambiado en 1");
  lcd.print("Objeto Cambiado en 2");

  //Advertencia Menos Iluminación X
  lcd.print("La puerta esta Abierta 1");
  lcd.print("La puerta esta Abierta 2");*/
  

  // HC-SR04 PinMode
  pinMode(TRIG, OUTPUT); 
  pinMode(ECHO, INPUT);
  Serial.begin(9600);  		// inicializacion de comunicacion serial a 9600 bps

  // LED PinMode
  pinMode(LED, OUTPUT); 
  
}

void loop() {
  
  //-------------- CODE FOR HC-SR04-------------------------
  digitalWrite(TRIG, HIGH); 		// generacion del pulso a enviar
  delay(1);				// al pin conectado al trigger
  digitalWrite(TRIG, LOW);		// del sensor

  
  DURACION = pulseIn(ECHO, HIGH);	// con funcion pulseIn se espera un pulso
  DISTANCIA = DURACION / 58.2;		// distancia medida en centimetros
  Serial.print("Distancia del Objeto: ");
  Serial.println(DISTANCIA);		// envio de valor de distancia por monitor serial
  Serial.println(" cm");
  delay(100);


  if(DISTANCIA >= 20){
    digitalWrite(LED, HIGH);
    //delay(DISTANCIA * 10);
    digitalWrite(LED, LOW);

    // CODE FOR LCD
    // Move the LCD to the left
    lcd.setCursor(0, 0);
    lcd.print("No object found on box 1");
    lcd.setCursor(0, 1);
    lcd.write("No object found on box 2");
  }else{
    // CODE FOR LCD
    // Move the LCD to the left
    lcd.setCursor(0, 0);
    lcd.print("Object found on box 1");
    lcd.setCursor(0, 1);
    lcd.write("Object found on box 2");
  }

  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(400);
  } 
  
  // Turn off the display:
  lcd.noDisplay();
  delay(250);
  // Turn on the display:
  lcd.display();
  delay(250);


}
