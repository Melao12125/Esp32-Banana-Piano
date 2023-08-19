// Branch Original utilizando apenas BleKeyboard para emulação de teclas BlueTooth
// Escolha um dos arquivos BleKeyboard ZIP na pasta 'downloads' do repositório e o importe para seu sketch.

// Aviso: Se utilzando a versão otimizada do BleKeyboard importe para o sketch a biblioteca NimBle-Arduino!
// Não precisa incluir a biblioteca NiBle-Arduino no codigo, só basta estar presente dentro do sketch.

#include <BleKeyboard.h>

//============== Definindo teclas ======================
String teclasAtuais[7] = {" ", " ", " ", " ", " ", " ", " "};
String teclas1[7] = {"1", "2", "3", "4", "5", "6", "7"};
String teclas2[7] = {"8", "9", "0", "q", "w", "e", "r"};
String teclas3[7] = {"t", "y", "u", "i", "o", "p", "a"};
String teclas4[7] = {"s", "d", "f", "g", "h", "j", "k"};
String teclas5[7] = {"l", "z", "x", "c", "v", "b", "n"};

int setTecla = 1;
int i = 0;
//======================================================

//==============Configurações Iniciais===================
bool teclaPressionada[7] = {false, false, false, false, false, false, false};   
const int pinosBananas[7] = {33, 12, 27, 13, 4, 15, 14}; //4, 13, 12, 15, 14, 27, 33 
const int PINO_RECEPTOR = 34;
BleKeyboard bleKeyboard("TecladoBanana", "Math e Thigas", 100);
//=======================================================

//=================== Setup ===========================
void setup() {
  
  pinMode(PINO_RECEPTOR, INPUT);

  for (int i = 0; i < 7; i++) {
    teclasAtuais[i] = teclas1[i];
  }

  for (int i = 0; i < 8; i++) {
    touchAttachInterrupt(pinosBananas[i], teclaTocada, 40);
    pinMode(pinosBananas[i], INPUT);
  }
  pinMode(2, OUTPUT);
  Serial.begin(115200);
  bleKeyboard.begin();
}
//=======================================================

//================= Loop Principal ======================
void loop() {

  Serial.println("Recebendo sinal: "); 
  Serial.println(digitalRead(PINO_RECEPTOR) == 1);
  if (touchRead(4) < 22) { //  PINO_RECEPTOR) == 1
    Serial.print(" | Set de Teclas atualizado para!" + setTecla);
    if (setTecla > 4) {
      setTecla = 0;
    }
    setTecla++;
  }

  switch (setTecla) {
    case 1:
      for (i = 0; i < 7; i++) {
        teclasAtuais[i] = teclas1[i];
      }
      break;
    case 2:
      for (i = 0; i < 7; i++) {
        teclasAtuais[i] = teclas2[i];
      }
      break;
    case 3:
      for (i = 0; i < 7; i++) {
        teclasAtuais[i] = teclas3[i];
      }
      break;
    case 4:
      for (i = 0; i < 7; i++) {
        teclasAtuais[i] = teclas4[i];
      }
      break;
    case 5:
      for (i = 0; i < 7; i++) {
        teclasAtuais[i] = teclas5[i];
      }
      break;
  }

  //for (int i = 0; i < 7; i++) {
  //  Serial.println(teclasAtuais[i]);
  //}

  if(bleKeyboard.isConnected()) {
    Serial.println("Conectado!");
  } else {
    Serial.println("Desconectado!");
  }

  delay(1500);
}
//=======================================================

//============= Logica das Teclas/Pinos ===================
void teclaTocada() {
  for (int i = 0; i < 7; i++) {
    if (touchRead(pinosBananas[i]) < 22) { // Se a leitura do pino for menor que 22 significa que a tecla está pressionada.
      //Logica para pressionar a tecla .
      if (!teclaPressionada[i]) {
        teclaPressionada[i] = true;
        bleKeyboard.press(teclasAtuais[i][0]); // Pressiona a tecla 
        digitalWrite(2, HIGH);
      }
      //Logica para despressionar tecla e evitar repetição
    } else {
      if (teclaPressionada[i]) { 
        teclaPressionada[i] = false;
        bleKeyboard.release(teclasAtuais[i][0]);
        digitalWrite(2, LOW);
      }
    }
  }
  //=====================================================

}
