int sen_masa = 2;
int boton = 3;
int contador = 4;
int retro_arriba = 5;
int retro_abajo = 6;

int levanta = 8;
int LED_arduino = 9;
int LED_barrera = 10;

int tiempo = 0;

void setup() {
    pinMode(sen_masa, INPUT);
    pinMode(boton, INPUT);
    pinMode(contador, INPUT);
    pinMode(retro_arriba, INPUT);
    pinMode(retro_abajo, INPUT);
  
    pinMode(levanta, OUTPUT);
    pinMode(LED_arduino, OUTPUT);
    pinMode(LED_barrera, OUTPUT);

    Serial.begin(9600);    
    }

void loop() {  

  int estado_masa;
  int estado_boton;
  int estado_contador;
  int estado_retro_arriba;
  int estado_retro_abajo;

    Leer_Valores(&estado_masa, &estado_boton, &estado_contador, &estado_retro_arriba, &estado_retro_abajo);
    Enviar_Serial(estado_masa, estado_boton, estado_contador, estado_retro_arriba, estado_retro_abajo);
    Levantar_Barrera(Recibir_Serial());
    tiempo = Parpadeo_LED(tiempo);
    
}

void Leer_Valores(int *lec_masa, int *lec_boton, int *lec_contador, int *lec_retro_arriba, int *lec_retro_abajo){
  
    *lec_masa         = digitalRead(sen_masa);
    *lec_boton        = digitalRead(boton);
    *lec_contador     = digitalRead(contador);
    *lec_retro_arriba = digitalRead(retro_arriba);
    *lec_retro_abajo  = digitalRead(retro_abajo);
 
}

void Enviar_Serial(int ser_masa, int ser_boton, int ser_contador, int ser_retro_arriba, int ser_retro_abajo){

  Serial.print(ser_masa);
  Serial.print("M, ");
  Serial.print(ser_boton);
  Serial.print("B, ");
  Serial.print(ser_contador);
  Serial.print("R, ");
  Serial.print(ser_retro_arriba);
  Serial.print(", ");
  Serial.println(ser_retro_abajo);
  
}


int Recibir_Serial(){
int estado;    
  if (Serial.available()){
    estado = Serial.read();
  }
  return estado;
}

void Levantar_Barrera(int recibido){

    if (recibido == '1')
    {
        digitalWrite(levanta, HIGH);
        digitalWrite(LED_barrera, HIGH);
        delay(1000);
    }
    else
    {
        digitalWrite(levanta,LOW);
        digitalWrite(LED_barrera, LOW);   
        //delay(1000); 
    }
  
}

int Parpadeo_LED(unsigned long t_segs){

if (t_segs > 25)
    {
      digitalWrite(LED_arduino, HIGH);
      if(t_segs < 50)
      {        
        return t_segs+1;
      }
      else
        return 0;  
    } 
else
    { 
      digitalWrite(LED_arduino, LOW);
      return t_segs+1;
    }
}

