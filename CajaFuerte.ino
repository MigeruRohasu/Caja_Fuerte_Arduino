#include <Servo.h>

//Reset de cuenta
int reset = 0;

//Variable para centimetros
int cm = 0;

//Asignacion PIn para piezo
int piezo = 10;

//Asignacion PIn para servo motor
int lectura1 = 0;

// Variables de Temperatura
float tempC;
int pinLM35 = 9;

//Asignacion PIn para servo motor
int salida = 10;

//Variable pocicion del servo motor
int pos = 0;

Servo servoMotor;

//Variables para pulsadores
int lectura = 0;
int estadoanterior = 0;

//Contadores de cada pulsador
int con_v = 0;
int con_am = 0;
int con_n = 0;
int con_az = 0;
int con_r = 0;

//Detectores de pulsador de cada color
int boton_v = 6;
int boton_am = 5;
int boton_n = 4;
int boton_az = 3;
int boton_r = 2;

long readUltrasonicDistance(int triggerPin, int echoPin)
{
  // Limpia el pin trigger
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);

  // Manda un pulso HIGH en el pin trigger que dura 10 microsegundos
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  
  // Lee el pin echo, y devuelve el viaje de la onda sonora en microsegundos 
  return pulseIn(echoPin, HIGH);
}

void clave ()
{
  //Espacio donde se ingresa la contraseña
          if(con_v == 2)
          {
              if(con_am == 5)
                {
                    if(con_n == 4)
                    {
                        if(con_az == 2)
                        {
                            if(con_r == 3)
                            {
                                Serial.println("abierto");
                                servoMotor.write(90);
                                delay(5000);    
                            }
                        }
                    }
                }
          }
          else
          {
            Serial.println("cerrado");
            servoMotor.write(0);
            delay(20);
          }
}

void BotonVerde ()
{
  //Lectura del boton verde
          lectura= digitalRead( boton_v);
          if(lectura != estadoanterior)
          {
            if(lectura == HIGH)
            {
              con_v = con_v + 1;
              Serial.println(con_v);
              Serial.println("verde");
            }
          delay(100);
          }
          estadoanterior = lectura;
}

void BotonAmarillo ()
{
  //Lectura del boton amarillo
          lectura= digitalRead( boton_am);
          if(lectura != estadoanterior)
          {
            if(lectura == HIGH)
            {
              con_am = con_am + 1;
              Serial.println(con_am);
              Serial.println("amarillo");
            }
          delay(100);
          }
          estadoanterior = lectura;
}

void BotonNaranja ()
{
  //Lectura del boton naranja
          lectura= digitalRead( boton_n);
          if(lectura != estadoanterior)
          {
            if(lectura == HIGH)
            {
              con_n = con_n + 1;
              Serial.println(con_n);
              Serial.println("naranja");
            }
          delay(100);
          }
          estadoanterior = lectura;
}

void BotonAzul ()
{
  //Lectura del boton azul
          lectura= digitalRead( boton_az);
          if(lectura != estadoanterior)
          {
            if(lectura == HIGH)
            {
              con_az = con_az + 1;
              Serial.println(con_az);
              Serial.println("azul");
            }
          delay(100);
          }
          estadoanterior = lectura;
}

void BotonRojo ()
{
  //Lectura del boton rojo
          lectura= digitalRead( boton_r);
          if(lectura != estadoanterior)
          {
            if(lectura == HIGH)
            {
              con_r = con_r + 1;
              Serial.println(con_r);
              Serial.println("rojo");
            }
          delay(100);
          }
        estadoanterior = lectura;
}

void ResetBotones ()
{
  //resetea todos los contadores cuando llegan a 6
               if(con_v == 6)
               {
                   con_v = 0;
                   con_am = 0;
                   con_n = 0;
                   con_az = 0;
                   con_r = 0;
                   
                   reset = reset + 1;
               }
               if(con_am == 6)
               {
                   con_v = 0;
                   con_am = 0;
                   con_n = 0;
                   con_az = 0;
                   con_r = 0;
                   
                   reset = reset + 1;
               }
               if(con_n == 6)
               {
                   con_v = 0;
                   con_am = 0;
                   con_n = 0;
                   con_az = 0;
                   con_r = 0;
                   
                   reset = reset + 1;
               }
               if(con_az == 6)
               {
                   con_v = 0;
                   con_am = 0;
                   con_n = 0;
                   con_az = 0;
                   con_r = 0;
                   
                   reset = reset + 1;
               }
               if(con_r == 6)
               {
                   con_v = 0;
                   con_am = 0;
                   con_n = 0;
                   con_az = 0;
                   con_r = 0;
                   
                   reset = reset + 1;
               }
}

void PintarValores()
{
  //Muestra el valor de cm en el monitor serial
      Serial.print(cm);
      Serial.println("  cm");
      Serial.print(tempC);
      Serial.println("  temperatura");
}

void ejercicio ()
{
  if (reset <= 3 ){
      // Mide el tiempo de ping en cm
      cm = 0.01723 * readUltrasonicDistance(8,7);
    
      // Mide temperatura 
      tempC = analogRead(pinLM35); 
   
     // Calculamos la temperatura con la fórmula
    tempC = ((analogRead(pinLM35)*(5.0/1024))-0.5)/0.01;
      
      
      PintarValores();
      
      //si el usuario se encuentra a menos de 200cm no entra al if  
      if (cm <= 200){
        
          digitalWrite(piezo, LOW );
        
          delay(200);
        
          clave();
        
          BotonVerde ();
          
          BotonAmarillo ();
          
          BotonNaranja ();
        
          BotonAzul ();
        
          BotonRojo ();
        
          ResetBotones ();
      //en el caso contrario suena la chicharra
      }else{
        digitalWrite(piezo, HIGH);
        delay(200);
        digitalWrite(piezo, LOW);
      }
   }
}

void setup()
{
  servoMotor.attach(10);
  
  pinMode(piezo, OUTPUT);
  
  pinMode(boton_v, INPUT);
  pinMode(boton_am, INPUT);
  pinMode(boton_n, INPUT);
  pinMode(boton_az, INPUT);
  pinMode(boton_r, INPUT);
  
  //pinMode(pinLM35,INPUT);
  
  analogReference(INTERNAL);
  
  //Inicio Pantalla serial
  Serial.begin(9600);
}

void loop()
{
  ejercicio();
}
