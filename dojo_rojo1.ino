/* 
Participantes:
  Aguilar Thomás
  Leandro Ayala
  Romina Calani
*/

#include <LiquidCrystal.h>

#define POTENCIOMETROROJO A0
#define inicio A1

#define RS 7
#define E	8
#define D4	9
#define D5	10
#define D6	11
#define D7	12

#define ledRojo 6
#define ledVerde 5
#define ledAmarillo 4
#define ledNaranja 3
#define ledAzul 2 
#define ledBlanco A2

#define PIEZO A3

#define LEN 50

LiquidCrystal myLcd(RS,E,D4,D5,D6,D7);

int estadoSalida;
int salidaLed=0;
int cantGemas=0;

void sonarPiezo(int tiempo);
void apagarTodosLeds();
void sonarPiezo(int tiempo);

void setup()
{
  pinMode(inicio, INPUT_PULLUP);
  //inicializamos el lcd
  myLcd.begin(16,2);
  //-----------------------
  //inicializamos los 6 leds
  for(int i = 2; i < 7; i++)
  {
  	pinMode(i, OUTPUT);
  }
  pinMode(ledBlanco, OUTPUT);
  //-------------------
  Serial.begin(9600);
  randomSeed(analogRead(0));
}

void loop()
{
  //numero random entre 100 y 200
  int randNumber;  
  int lecturaPotenciometro;
  int poderThanos;
  int estadoInicio=digitalRead(inicio);
  char enemigos[][LEN]={{"Gamora"},{"Loki"},{"El coleccionista"},{"Star Lord"},{"Dr strange"},{"Vision"}};
  char gemas[][LEN]={{"Alma"},{"Espacio"},{"Realidad"},{"Poder"},
  {"Tiempo"},{"Mente"}};
  char mensajeGema[LEN];
  char mensajeEnemigo[LEN];
  int flagVictoria=0;
  int reintentos=6; 
  
  if(estadoInicio==HIGH){
    estadoSalida=1;
  }
  
  delay(200);
  
  if(estadoSalida==1 && estadoInicio==LOW){
  
   	salidaLed=!salidaLed;
	
    //ESCRIBAN DESDE ACA
    //digitalWrite(LED, salidaLed); 
    do{
      randNumber = random(100,201);
      lecturaPotenciometro = analogRead(POTENCIOMETROROJO);
  	  poderThanos = map(lecturaPotenciometro,0,1023,90,190);
		
      myLcd.clear();
   	  sprintf(mensajeGema, "Gema: %s ", gemas[cantGemas]);
  	  myLcd.setCursor(0,0);
  	  myLcd.print(mensajeGema);
	  sprintf(mensajeEnemigo, "Enemigo: %s ", enemigos[cantGemas]);
  	  myLcd.setCursor(0,1);
  	  myLcd.print(mensajeEnemigo); 
      delay(2000);
      estadoSalida=0;
      if(cantGemas==6){
      	break;
      }
      
      if(poderThanos>randNumber)
      {    
        flagVictoria=1;
        myLcd.clear();
        cantGemas++;
        sonarPiezo(100);
      }
      else{
        reintentos=reintentos-1;
      }
      
      Serial.println("Poder enemigo: ");
      Serial.println(randNumber);
      Serial.println("Poder Thanos: ");
      Serial.println(poderThanos);  
      
      if(reintentos==0){
      	myLcd.clear();
      	cantGemas=0;
      	apagarTodosLeds();
      	myLcd.print("Perdiste");
      	reintentos = 6;
      	break;        
      }
      else if(cantGemas==6){
       	break; 
      }
 	  
      switch(cantGemas){
       case 1:
        	//amarillo alma
        myLcd.clear();
        digitalWrite(ledAmarillo,HIGH);
        myLcd.setCursor(0,0);        
  	  	myLcd.print("Gano Gema Alma");
        delay(1500);
        break;
        case 2:
        	//azul espacio
        myLcd.clear();
        digitalWrite(ledAzul,HIGH);
        myLcd.setCursor(0,0);
  	  	myLcd.print("Gano Gema");
        myLcd.setCursor(0,1);
        myLcd.print("Espacio");
        delay(1500);
        break;
        case 3:
        	//realidad rojo
        myLcd.clear();
        digitalWrite(ledRojo,HIGH);
        myLcd.setCursor(0,0);
  	  	myLcd.print("Gano Gema");
        myLcd.setCursor(0,1);
  	  	myLcd.print("Realidad");        
        delay(1500);
        break;
        case 4:
        	//poder violeta
        myLcd.clear();
        digitalWrite(ledNaranja,HIGH);
        myLcd.setCursor(0,0);
  	  	myLcd.print("Gano Gema Poder");
        delay(1500);
        break;
        case 5:
        	//tiempo verde
        myLcd.clear();
        digitalWrite(ledVerde,HIGH);
        myLcd.setCursor(0,0);
  	  	myLcd.print("Gano Gema Tiempo");
        delay(1500);
        break;
        case 6:
        	//mente led blanco
        myLcd.clear();
        digitalWrite(ledBlanco,HIGH);
        myLcd.setCursor(0,0);
  	  	myLcd.print("Gano Gema Mente");
        delay(1500);
        break;
        
      }
  	}while(flagVictoria==1);
  }
  
  if(cantGemas==6){
    myLcd.clear();
    encenderTodosLeds();
    encenderTodosLeds();
    encenderTodosLeds();
    myLcd.setCursor(0,0);
    myLcd.print("No me quiero ir");
    myLcd.setCursor(0,1);
    myLcd.print("sr stark");
    delay(2000);
    sonarPiezo(500);
    delay(1000);
    sonarPiezo(500);
    delay(1000);
    sonarPiezo(500);
  }
}

void sonarPiezo(int tiempo)
{
  tone(PIEZO,261.63,tiempo);
  tone(PIEZO,261.63,tiempo);
  tone(PIEZO,261.63,tiempo);
}

void encenderTodosLeds(){
  for(int i=2;i<7;i++){
    digitalWrite(i, HIGH);    
  }
  digitalWrite(ledBlanco,HIGH);
  delay(500);
  for(int i=2;i<7;i++){
    digitalWrite(i, LOW);    
  }
  digitalWrite(ledBlanco,LOW);
  delay(500);
}

void apagarTodosLeds(){
  for(int i=2;i<7;i++){
    digitalWrite(i, LOW);    
  }
  digitalWrite(ledBlanco,LOW);
}