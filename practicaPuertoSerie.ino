// analogos porque yo no hay pines digitales...
int led1=A0;
int led2=A1;
int digitPins[] = {3, 4, 5, 6}; // pines de los dígitos del display (de derecha a izquierda)
int segmentPins[] = {7, 8, 9, 10, 11, 12, 13}; // pines de los segmentos del display
volatile int i=0;
String ultimoComando;
int segmentos[10][7] = {
  {1, 1, 1, 1, 1, 1, 0}, // 0
  {0, 1, 1, 0, 0, 0, 0}, // 1
  {1, 1, 0, 1, 1, 0, 1}, // 2
  {1, 1, 1, 1, 0, 0, 1}, // 3
  {0, 1, 1, 0, 0, 1, 1}, // 4
  {1, 0, 1, 1, 0, 1, 1}, // 5
  {1, 0, 1, 1, 1, 1, 1}, // 6
  {1, 1, 1, 0, 0, 0, 0}, // 7
  {1, 1, 1, 1, 1, 1, 1}, // 8
  {1, 1, 1, 0, 0, 1, 1}  // 9
};
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1,OUTPUT);  
  pinMode(led2,OUTPUT);  
  //display:
  for (int i = 0; i < 4; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  for (int i = 0; i < 7; i++) {
    pinMode(segmentPins[i], OUTPUT);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  char c= ' ';
  String mensaje="";
  if(Serial.available()){// comprobamos si hay algo esperando
    while(c!='\n'){//mientras el carácter leído no sea un salto de línea
      c=Serial.read();// lee un carácter a través del puerto serial
      if(c!='\n'){// comprueba si el carácter leído no es un salto de línea
        mensaje=mensaje+c;
      }
      delay(25);
    }
    if(comandosLeds(mensaje)==false && comandosDisplay(mensaje)==false){
      Serial.println("El comando: "+mensaje+" no es valido...");
    }
  }
}
bool comandosDisplay(String mensaje){
  
  if(strcmp(mensaje.c_str(), "iniciar") == 0){
    Serial.println("Iniciando cuenta...");
    ultimoComando="iniciar";
    iniciarCuenta();
    return true;
  }else if(strcmp(mensaje.c_str(), "pausa") == 0){
    Serial.println("Pausando cuenta...");
    pausarDisplay();
    return true;
  }else if(strcmp(mensaje.c_str(), "retro") == 0){
    Serial.println("retrocediendo cuenta...");
    ultimoComando="retro";
    retrocederCuenta();
    return true;
  }else if(strcmp(mensaje.c_str(), "reiniciar") == 0){
    Serial.println("reiniciando cuenta...");
    i=0;
    iniciarCuenta();
    return true;
  }else if(strcmp(mensaje.c_str(), "reanudar") == 0){
    // para renudar despues de usar pausa
    Serial.println("reanudando cuenta...");
    Serial.println("ultimo comando: "+ultimoComando);
    // toma en cuenta el ultimo comando y lo vuelve a correr desde donde se quedo i
    comandosDisplay(ultimoComando);
    return true;
  }else{
    return false;
  }
}
void retrocederCuenta(){
  for(;i>=0;i--){
    for(int j=0;j<10;j++){// retardo para que no se muestre tan rapido
      int unidades = i % 10;
      int decenas = (i / 10) % 10;
      int centenas = (i / 100) % 10;
      int unidadesDeMillar = i / 1000;
        mostrarNumero(unidades, 0);
        mostrarNumero(decenas, 1);
        mostrarNumero(centenas, 2);
        mostrarNumero(unidadesDeMillar, 3);
        // detener diclo si se ingreso otro comando
    }
    if(Serial.available()){
      break;
    }
  }
}
void pausarDisplay(){
  //mientras que no se ingrese otro comando
  while(!Serial.available()){
    int unidades = i % 10;
    int decenas = (i / 10) % 10;
    int centenas = (i / 100) % 10;
    int unidadesDeMillar = i / 1000;
    mostrarNumero(unidades, 0);
    mostrarNumero(decenas, 1);
    mostrarNumero(centenas, 2);
    mostrarNumero(unidadesDeMillar, 3);
  }
}
void iniciarCuenta(){
  for (; i < 10000; i++) {
    for(int j=0;j<10;j++){// retardo para que no se muestre tan rapido
      int unidades = i % 10;
      int decenas = (i / 10) % 10;
      int centenas = (i / 100) % 10;
      int unidadesDeMillar = i / 1000;
      mostrarNumero(unidades, 0);
      mostrarNumero(decenas, 1);
      mostrarNumero(centenas, 2);
      mostrarNumero(unidadesDeMillar, 3);
    }
    // detener diclo si se ingreso otro comando
    if(Serial.available()){
      break;
    }
  }
}
void mostrarNumero(int numero, int digito) {
  digitalWrite(digitPins[digito], LOW); // encender el dígito correspondiente
  for (int i = 0; i < 7; i++) {
    digitalWrite(segmentPins[i], segmentos[numero][i]); // encender los segmentos correspondientes
  }
  delay(5);
  digitalWrite(digitPins[digito], HIGH); // apagar el dígito correspondiente
}
bool comandosLeds(String mensaje){
  if (strcmp(mensaje.c_str(), "led1") == 0) {
    encenderLed1();
    return true;
  }
  else if (strcmp(mensaje.c_str(), "led2") == 0) {
    encenderLed2();
    return true;
  }
  else if(strcmp(mensaje.c_str(), "no led1") == 0){
    apagarLed1(); 
    return true;     
  }
  else if(strcmp(mensaje.c_str(), "no led2") == 0){
    apagarLed2();    
    return true;
  }
  else if(strcmp(mensaje.c_str(), "encender-todos") == 0){
    encenderTodos();    
    return true;
  }
  else if (strcmp(mensaje.c_str(), "apagar-todos") == 0) {
    apagarTodos();
    return true;
  }
  else {
    return false;
  }
}
void encenderTodos(){
  Serial.println("Encendiendo todos los leds...");
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
}
void apagarTodos(){
  Serial.println("Apagando LEDS...");
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
}
void apagarLed1(){
  Serial.println("Apagando LED1...");
  digitalWrite(led1,LOW);
}
void apagarLed2(){
  Serial.println("Apagando LED2...");
  digitalWrite(led2,LOW);
}
void encenderLed1(){
  Serial.println("Encendiendo LED1...");
  digitalWrite(led1,HIGH);
}
void encenderLed2(){
  Serial.println("Encendiendo LED2...");
  digitalWrite(led2,HIGH);
}
