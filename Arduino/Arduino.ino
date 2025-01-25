#include <LiquidCrystal.h>

LiquidCrystal pantalla(14,15,16,17,18,19);

void setup() {
  // put your setup code here, to run once:
  pantalla.begin(16,4);
  pantalla.setCursor(0,0);
  pinMode(13,INPUT);
  pinMode(12,INPUT);
  //pantalla.print("Julio 202010312");
  //pantalla.setCursor(0,1);
  //pantalla.print("Isabel 12121212");
  //pantalla.setCursor(0,0);
  //pantalla.clear();
  //pantalla.print("hola hola");
  
}

String opciones[4] = {"1.Ingreso","2.Retiro","3.Cerrar sesion","4.eliminar"};
String nombres[5] = {"Julio","Maria ","Karen","Cris.","Derek"};
String carne[5] = {"202010312","201800565","201900603","202010995","202010825"};
int repeticiones = 2;
int elementosPorIteracion = 2; 
int indice = 0;
void secuenciaInicial(){
for (int i = 0; i < repeticiones; i++) {
    // Imprimir nombres y carnés de 4 en 4
    for (int j = 0; j < 5; j += elementosPorIteracion) {
      pantalla.clear();  // Limpiar la pantalla antes de imprimir los siguientes nombres
      for (int k = 0; k < elementosPorIteracion; k++) {
        indice = j + k;
        if (indice < 5) {
          pantalla.setCursor(0, k);
          pantalla.print(nombres[indice] + " " + carne[indice]);
        }
      }
      delay(1500);  // Esperar 2 segundos antes de pasar al siguiente grupo de nombres
    indice = 0;
    }
  }
}

void MenuPrincipal(){
  pantalla.setCursor(0,0);
  delay(100);
  pantalla.print("*Menu Principal*");
  pantalla.setCursor(0,1);
  pantalla.print("1.Iniciar Sesion");
  delay(1500);
  pantalla.clear();
  pantalla.setCursor(0,0);
  pantalla.print("*Menu Principal*");
  pantalla.setCursor(0,1);
  pantalla.print("2.Registro");
}


void MenuAdmin(){
  pantalla.setCursor(0,0);
  delay(100);
  pantalla.clear();
  pantalla.print("*Menu Admin*");
  pantalla.setCursor(0,1);
  pantalla.print("1.Logs");
  pantalla.setCursor(0,1);
  delay(1500);
  pantalla.print("2.Estado del si.");
  }


void menuUsuarios(){
  pantalla.setCursor(0,0);
  delay(100);
  for(int i = 0; i < 4; i++){
    pantalla.clear();
    pantalla.setCursor(0,0);
    pantalla.print("*Menu Usuario*");  
    pantalla.setCursor(0,1);
    pantalla.print(opciones[i]);
    delay(700);
    } 
  
  }
  
int  prueba = 1;
void loop() {
  if(digitalRead(13) == HIGH){
    prueba = 3;
    }
  if(digitalRead(12) == HIGH){
    prueba = 4;
    }
  delay(500);
  if(prueba == 1){
      secuenciaInicial();
      delay(500);
      prueba = 2;
    }
   if(prueba == 2){
      MenuPrincipal();
   }
   if(prueba == 3){
    MenuAdmin();
    }
   if(prueba == 4){
    menuUsuarios();
    }
}
