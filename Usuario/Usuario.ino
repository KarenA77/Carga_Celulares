#include <LiquidCrystal.h>
#include <EEPROM.h>

//AQUI ESTAN LOS PINES
#define RS 8
#define E 9
#define D4 10
#define D5 11
#define D6 12
#define D7 13


//DECLARACION DE LETRAS DE TECLADO

#define LETRA_A 10
#define LETRA_B 11
#define LETRA_C 12
#define LETRA_D 13
#define LETRA_E 14
#define LETRA_F 15
#define NO_TECLA -1

#define PINC_TECLADO 18
#define PINF_TECLADO 14


#define ACEPTAR 7
#define CANCELAR 6

//DEFINICION DE MENUS
#define MENU_PRINCIPAL 16
#define MENU 0
#define INICIO_SESION 1
#define REGISTRO 2
#define CUENTA 3
#define MENU_USER 4


//AQUI ES DONDE SE DECIDE QUE MENU APARECE AL INICIO
int estadoPrograma = MENU_PRINCIPAL;


#define INICIALIZAR_TECLADO(VAR) int VAR = -1
#define TECLADO \
  tecla = teclaPresionada(); \
  switch (tecla)
#define HACER_nVECES(N) for (int i = 0; i < N; i++)
#define LOOP while (1)

#define VACIO "                "

//CONFIGURACION DEL TECLADO
//EN PROTEUS SERIAN LOS SIMBOLOS DE MAS MENOS MULTIPLICAR DIVIDIR ESTAS LETRAS
int teclas[4][4] = { { 7, 8, 9, LETRA_C },
                     { 4, 5, 6, LETRA_D },
                     { 1, 2, 3, LETRA_E },
                     { LETRA_A, 0, LETRA_B, LETRA_F } };

struct Usuario {
  char Nombre[11];
  char Contra[11];
  char Telefono[7];
};
// Nombres del grupo repiticiones en pantalla y elementos por iteración
String nombres[5] = { "Julio", "Maria ", "Karen", "Cris.", "Derek" };
String carne[5] = { "202010312", "201800565", "201900603", "202010905", "202010825" };
int repeticiones = 2;
int elementosPorIteracion = 2;
int indice = 0;
String nameStr;
String passStr;
String numbStr;


//FUNCION BORRAR REGISTROS MEMORIA EEPROM
void Eliminar() {
  for (int i = 0; i < EEPROM.length(); i++) {
    EEPROM.write(i, 0);
  }
}

LiquidCrystal pantalla(RS, E, D4, D5, D6, D7);
INICIALIZAR_TECLADO(tecla);

int teclaPresionada() {
  for (int i = PINF_TECLADO; i < PINF_TECLADO + 4; i++) {
    digitalWrite(i, HIGH);
    for (int j = PINC_TECLADO; j < PINC_TECLADO + 4; j++)
      if (digitalRead(j) == HIGH) {
        digitalWrite(i, LOW);
        return teclas[i - PINF_TECLADO][j - PINC_TECLADO];
      }
    digitalWrite(i, LOW);
  }
  return NO_TECLA;
}

void setup() {
  Serial.begin(9600);
  Serial1.begin(9200);
  pantalla.begin(16, 2);
  HACER_nVECES(4)
    pinMode(PINC_TECLADO + i, INPUT);
  HACER_nVECES(4)
    pinMode(PINF_TECLADO + i, OUTPUT);
}

int seleccion = 0;
char nombre[11] = "";
char contra[11] = "";
char telefono[7] = "";
int indiceNombre = 0;
int indiceContra = 0;
int indiceTelefono = 0;
int direccionEEPROM = 1;

int cuentaActual = 0;


void secuenciaInicial() {
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

bool estadoXD = true;



//AQUI ESTAN TODOS LOS MENUS
void loop() {
  switch (estadoPrograma) {
    case MENU_PRINCIPAL:
      {
        if (estadoXD == true) {
          secuenciaInicial();
          delay(500);
          estadoXD = false;
        }

        pantalla.setCursor(0, 0);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 0);
        pantalla.print(seleccion == 0 ? "> " : "  ");
        pantalla.print("Ingreso APP");
        pantalla.setCursor(0, 1);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 1);
        pantalla.print(seleccion == 1 ? "> " : "  ");
        pantalla.print("Ingreso KEYPAD");
        TECLADO {
          case 8:
            {
              if (seleccion >= 1)
                seleccion--;
              break;
            }
          case 2:
            {
              if (seleccion < 1)
                seleccion++;
              break;
            }
          case 5:
            {
              switch (seleccion) {
                case 0:
                  {
                    pantalla.print("Conectando...");
                    while (Serial1.available()) {
                      delay(10);
                      //char c = Serial1.read();
                      nameStr = Serial1.readStringUntil(' ');
                      passStr = Serial1.readStringUntil(' ');
                      numbStr = Serial1.readStringUntil(' ');
                      //pantalla.println(nameStr);
                     // Serial.println(passStr);
                      //Serial.println(numbStr);
                      /*const char* myString = nameStr.c_str();
                      ;
                      strcpy(name, myString);
                      const char* myString2 = passStr.c_str();
                      ;
                      strcpy(pass, myString2);
                      const char* myString3 = numbStr.c_str();
                      ;
                      strcpy(numb, myString3);
                      //apodo += c;
                      uint8_t numeroDeRegistros = 0;
                      struct Usuario usr;
                      EEPROM.get(0, numeroDeRegistros);
                      direccionEEPROM = 1;
                      HACER_nVECES(numeroDeRegistros) {
                        EEPROM.get(direccionEEPROM, usr);
                        direccionEEPROM += sizeof(struct Usuario);
                      }
                      memcpy(usr.Nombre, name, 11);
                      memcpy(usr.Contra, pass, 11);
                      memcpy(usr.Telefono, numb, 7);
                      EEPROM.put(direccionEEPROM, usr);
                      numeroDeRegistros++;
                      EEPROM.write(0, numeroDeRegistros);
                      estadoPrograma = MENU;
                      seleccion = 0;
                      memset(name, 0, 11);
                      memset(pass, 0, 11);
                      memset(numb, 0, 7);
                      indiceNombre = 0;
                      indiceContra = 0;
                      indiceTelefono = 0;*/
                    }
                    break;
                  }
                case 1:
                  {
                    estadoPrograma = MENU;
                    break;
                  }
              }
              delay(120);
              seleccion = 0;
              break;
            }
        }
        break;
      }
    case MENU:
      {
        pantalla.setCursor(0, 0);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 0);
        pantalla.print(seleccion == 0 ? "> " : "  ");
        pantalla.print("Iniciar sesion");
        pantalla.setCursor(0, 1);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 1);
        pantalla.print(seleccion == 1 ? "> " : "  ");
        pantalla.print("Registrar");
        TECLADO {
          case 8:
            {
              if (seleccion >= 1)
                seleccion--;
              break;
            }
          case 2:
            {
              if (seleccion < 1)
                seleccion++;
              break;
            }
          case 5:
            {
              switch (seleccion) {
                case 0:
                  {
                    estadoPrograma = INICIO_SESION;
                    break;
                  }
                case 1:
                  {
                    estadoPrograma = REGISTRO;
                    break;
                  }
              }
              delay(120);
              seleccion = 0;
              break;
            }
        }
        break;
      }

    case MENU_USER:
      {
        pantalla.setCursor(0, 0);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 0);
        pantalla.print(seleccion == 0 ? "> " : "  ");
        pantalla.print("Ingresar Celular");
        pantalla.setCursor(0, 1);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 1);
        pantalla.print(seleccion == 1 ? "> " : "  ");
        pantalla.print("Eliminar User");

        TECLADO {
          case 8:
            {
              if (seleccion >= 1)
                seleccion--;
              break;
            }
          case 2:
            {
              if (seleccion < 1)
                seleccion++;
              break;
            }
          case 5:
            {
              switch (seleccion) {
                case 0:
                  {
                    //AQUI SE CONECTA A LA APP

                    break;
                  }
                case 1:
                  {
                    Eliminar();
                    pantalla.clear();
                    delay(400);
                    estadoPrograma = MENU;
                    break;
                  }
              }
              delay(120);
              seleccion = 0;
              break;
            }
        }
        break;
      }

    case INICIO_SESION:
      {
        pantalla.clear();
        pantalla.print("NOM: ");
        pantalla.setCursor(5, 0);
        LOOP {
          if (digitalRead(ACEPTAR) == HIGH) {
            delay(260);
            break;
          }
          if (digitalRead(CANCELAR) == HIGH) {
            memset(nombre, 0, 11);
            indiceNombre = 0;
            pantalla.setCursor(5, 0);
            HACER_nVECES(11)
              pantalla.write(" ");
            pantalla.setCursor(5, 0);
          }
          TECLADO {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = tecla + 48;
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_A:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'A';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_B:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'B';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_C:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'C';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_D:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'D';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_E:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'E';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(260);
                break;
              }
            case LETRA_F:
              {
                if (indiceNombre == 10)
                  break;
                nombre[indiceNombre++] = 'F';
                pantalla.write(nombre[indiceNombre - 1]);
                delay(200);
                break;
              }
          }
        }
        pantalla.setCursor(0, 1);
        pantalla.print(VACIO);
        pantalla.setCursor(0, 1);
        pantalla.print("CNT: ");
        pantalla.setCursor(5, 1);
        LOOP {
          if (digitalRead(ACEPTAR) == HIGH) {
            delay(260);
            break;
          }
          if (digitalRead(CANCELAR) == HIGH) {
            memset(contra, 0, 11);
            indiceContra = 0;
            pantalla.setCursor(5, 1);
            HACER_nVECES(11)
              pantalla.write(" ");
            pantalla.setCursor(5, 1);
          }
          TECLADO {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = tecla + 48;
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_A:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'A';
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_B:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'B';
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_C:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'C';
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_D:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'D';
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_E:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'E';
                pantalla.write("*");
                delay(260);
                break;
              }
            case LETRA_F:
              {
                if (indiceContra == 10)
                  break;
                contra[indiceContra++] = 'F';
                pantalla.write("*");
                delay(200);
                break;
              }
          }
        }
        bool encontro = false;
        uint8_t numeroDeRegistros = 0;
        struct Usuario usr;
        EEPROM.get(0, numeroDeRegistros);
        direccionEEPROM = 1;
        HACER_nVECES(numeroDeRegistros) {
          EEPROM.get(direccionEEPROM, usr);
          if (memcmp(usr.Nombre, nombre, 11) == 0 && memcmp(usr.Contra, contra, 11) == 0) {
            encontro = true;
            break;
          }
          direccionEEPROM += sizeof(struct Usuario);
        }
        if (encontro) {
          pantalla.clear();
          pantalla.write("Bienvenido");
          pantalla.write(" ");
          pantalla.write(nombre);
          delay(1000);
          estadoPrograma = MENU_USER;


        } else {
          pantalla.clear();
          pantalla.write("Datos incorrectos.");
          memset(nombre, 0, 11);
          memset(contra, 0, 11);
          indiceNombre = 0;
          indiceContra = 0;
          delay(500);
        }
        break;
      }
    case REGISTRO:
      {
        Serial.println("rEGISTRADO");
        if (seleccion <= 1) {
          pantalla.setCursor(0, 0);
          pantalla.print(VACIO);
          pantalla.setCursor(0, 0);
          pantalla.print(seleccion == 0 ? "> " : "  ");
          pantalla.print("Ingresar datos");
          pantalla.setCursor(0, 1);
          pantalla.print(VACIO);
          pantalla.setCursor(0, 1);
          pantalla.print(seleccion == 1 ? "> " : "  ");
          pantalla.print("Registrar");
        } else if (seleccion > 1 && seleccion <= 3) {
          pantalla.setCursor(0, 0);
          pantalla.print(VACIO);
          pantalla.setCursor(0, 0);
          pantalla.print(seleccion == 2 ? "> " : "  ");
          pantalla.print("Cancelar");
          pantalla.setCursor(0, 1);
          pantalla.print(VACIO);
        }
        TECLADO {
          case 8:
            {
              if (seleccion >= 1)
                seleccion--;
              delay(120);
              break;
            }
          case 2:
            {
              if (seleccion < 2)
                seleccion++;
              if (seleccion > 2)
                seleccion = 2;
              delay(120);
              break;
            }
          case 5:
            {
              delay(200);
              switch (seleccion) {
                case 0:
                  {
                    if (indiceNombre != 0 && indiceContra != 0) {
                      pantalla.clear();
                      pantalla.print("Ya se han inser-");
                      pantalla.setCursor(0, 1);
                      pantalla.print("tado datos.     ");
                      delay(1000);
                      pantalla.clear();
                      pantalla.print("Presione ACEPTAR");
                      pantalla.setCursor(0, 1);
                      pantalla.print("para volver.    ");
                      LOOP {
                        if (digitalRead(ACEPTAR) == HIGH)
                          break;
                        delay(120);
                      }
                      break;
                    }
                    pantalla.clear();
                    pantalla.print("NOM: ");
                    pantalla.setCursor(5, 0);
                    LOOP {
                      if (digitalRead(ACEPTAR) == HIGH) {
                        delay(260);
                        break;
                      }
                      if (digitalRead(CANCELAR) == HIGH) {
                        memset(nombre, 0, 11);
                        indiceNombre = 0;
                        pantalla.setCursor(5, 0);
                        HACER_nVECES(11)
                          pantalla.write(" ");
                        pantalla.setCursor(5, 0);
                      }
                      TECLADO {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                          {
                            if (indiceNombre == 10)
                              break;
                            nombre[indiceNombre++] = tecla + 48;
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_A:
                          {
                            if (indiceNombre == 10)
                              break;
                            nombre[indiceNombre++] = 'A';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_B:
                          {
                            if (indiceNombre == 12)
                              break;
                            nombre[indiceNombre++] = 'B';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_C:
                          {
                            if (indiceNombre == 12)
                              break;
                            nombre[indiceNombre++] = 'C';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_D:
                          {
                            if (indiceNombre == 12)
                              break;
                            nombre[indiceNombre++] = 'D';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_E:
                          {
                            if (indiceNombre == 12)
                              break;
                            nombre[indiceNombre++] = 'E';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_F:
                          {
                            if (indiceNombre == 12)
                              break;
                            nombre[indiceNombre++] = 'F';
                            pantalla.write(nombre[indiceNombre - 1]);
                            delay(200);
                            break;
                          }
                      }
                    }
                    pantalla.setCursor(0, 1);
                    pantalla.print(VACIO);
                    pantalla.setCursor(0, 1);
                    pantalla.print("CNT: ");
                    pantalla.setCursor(5, 1);
                    LOOP {
                      if (digitalRead(ACEPTAR) == HIGH) {
                        delay(260);
                        break;
                      }
                      if (digitalRead(CANCELAR) == HIGH) {
                        memset(contra, 0, 11);
                        indiceContra = 0;
                        pantalla.setCursor(5, 1);
                        HACER_nVECES(11)
                          pantalla.write(" ");
                        pantalla.setCursor(5, 1);
                      }
                      TECLADO {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = tecla + 48;
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_A:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'A';
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_B:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'B';
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_C:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'C';
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_D:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'D';
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_E:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'E';
                            pantalla.write("*");
                            delay(260);
                            break;
                          }
                        case LETRA_F:
                          {
                            if (indiceContra == 12)
                              break;
                            contra[indiceContra++] = 'F';
                            pantalla.write("*");
                            delay(200);
                            break;
                          }
                      }
                    }
                    pantalla.setCursor(0, 2);
                    pantalla.print(VACIO);
                    pantalla.setCursor(0, 2);
                    pantalla.print("TEL: ");
                    pantalla.setCursor(5, 2);
                    LOOP {
                      if (digitalRead(ACEPTAR) == HIGH) {
                        delay(260);
                        break;
                      }
                      if (digitalRead(CANCELAR) == HIGH) {
                        memset(telefono, 0, 7);
                        indiceTelefono = 0;
                        pantalla.setCursor(5, 2);
                        HACER_nVECES(7)
                          pantalla.write(" ");
                        pantalla.setCursor(5, 2);
                      }
                      TECLADO {
                        case 0:
                        case 1:
                        case 2:
                        case 3:
                        case 4:
                        case 5:
                        case 6:
                        case 7:
                        case 8:
                        case 9:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = tecla + 48;
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_A:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'A';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_B:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'B';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_C:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'C';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_D:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'D';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_E:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'E';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(260);
                            break;
                          }
                        case LETRA_F:
                          {
                            if (indiceTelefono == 12)
                              break;
                            telefono[indiceTelefono++] = 'F';
                            pantalla.write(telefono[indiceTelefono - 1]);
                            delay(200);
                            break;
                          }
                      }
                    }
                    break;
                  }
                case 1:
                  {
                    if (indiceNombre == 0 || indiceContra == 0) {
                      pantalla.clear();
                      pantalla.print("Uno de los  cam-");
                      pantalla.setCursor(0, 1);
                      pantalla.print("pos esta vacio. ");
                      delay(1000);
                      pantalla.clear();
                      pantalla.print("Presione ACEPTAR");
                      pantalla.setCursor(0, 1);
                      pantalla.print("para volver.    ");
                      memset(nombre, 0, 11);
                      memset(contra, 0, 11);
                      memset(telefono, 0, 7);
                      indiceNombre = 0;
                      indiceContra = 0;
                      indiceTelefono = 0;
                      LOOP {
                        if (digitalRead(ACEPTAR) == HIGH)
                          break;
                        delay(120);
                      }
                      break;
                    }
                    uint8_t numeroDeRegistros = 0;
                    struct Usuario usr;
                    EEPROM.get(0, numeroDeRegistros);
                    direccionEEPROM = 1;
                    HACER_nVECES(numeroDeRegistros) {
                      EEPROM.get(direccionEEPROM, usr);
                      direccionEEPROM += sizeof(struct Usuario);
                    }
                    memcpy(usr.Nombre, nombre, 11);
                    memcpy(usr.Contra, contra, 11);
                    memcpy(usr.Telefono, telefono, 7);
                    EEPROM.put(direccionEEPROM, usr);
                    numeroDeRegistros++;
                    EEPROM.write(0, numeroDeRegistros);
                    estadoPrograma = MENU;
                    seleccion = 0;
                    memset(nombre, 0, 11);
                    memset(contra, 0, 11);
                    memset(telefono, 0, 7);
                    indiceNombre = 0;
                    indiceContra = 0;
                    indiceTelefono = 0;
                    break;
                  }
                case 2:
                  {
                    estadoPrograma = MENU;
                    seleccion = 0;
                    memset(nombre, 0, 11);
                    memset(contra, 0, 11);
                    memset(telefono, 0, 7);
                    indiceNombre = 0;
                    indiceContra = 0;
                    indiceTelefono = 0;
                    break;
                  }
              }
              delay(120);
              break;
            }
        }
        break;
      } /*
        case CUENTA: {
            int presionando = 0;
            Serial.write('?');
            while (Serial.available()) {
                presionando = Serial.read();
            }
            if (presionando)
                cuentaActual++;
            break;
        }*/
  }
  delay(70);
}
