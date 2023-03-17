int a = 2;
int b = 3;
int c = 4;
int d = 5;
int e = 6;
int f = 7;
int g = 8;
//anodo comun (conectar al vcc 220 ohm)
int segmentos[10][7] = {
  {0,0,0,0,0,0,1}, // 0
  {1,0,0,1,1,1,1}, // 1
  {0,0,1,0,0,1,0}, // 2
  {0,0,0,0,1,1,0}, // 3
  {1,0,0,1,1,0,0}, // 4
  {0,1,0,0,1,0,0}, // 5
  {0,1,0,0,0,0,0}, // 6
  {0,0,0,1,1,1,1}, // 7
  {0,0,0,0,0,0,0}, // 8
  {0,0,0,1,1,0,0}  // 9
};

int segmentoPines[7] = {2,3,4,5,6,7,8}; // Pines conectados a los segmentos del display

void setup() {
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {
  for(int i=0;i<=9;i++){
    mostrarNumero(i);
    delay(1000);
  }
}
// se prende cada uno de los segmentos dependiendo de el numero que se reciba tomando en cuenta la matriz segmentos 
void mostrarNumero(int num){
  for(int j=0;j<7;j++){
    digitalWrite(segmentoPines[j], segmentos[num][j]);
  /*EJEMPLO:
    digitalWrite(a, segmentos[3][0]);
    digitalWrite(b, segmentos[3][1]);
    digitalWrite(c, segmentos[3][2]);
    digitalWrite(d, segmentos[3][3]);
    digitalWrite(e, segmentos[3][4]);
    digitalWrite(f, segmentos[3][5]);
    digitalWrite(g, segmentos[3][6]);
  */
  }
}

