// Branch Original utilizando apenas BleKeyboard para emulação de teclas BlueTooth
// Escolha um dos arquivos BleKeyboard ZIP na pasta 'downloads' nesta Branch do repositório e o importe para seu sketch.

// Aviso: Se utilzando a versão otimizada do BleKeyboard importe para o sketch a biblioteca NimBle-Arduino!
// Não precisa incluir a biblioteca NiBle-Arduino no codigo, só basta estar presente dentro do sketch.

#include <BleKeyboard.h>

//============== Definindo teclas ======================
String teclas[7] = {"q", "w", "e", "r", "t", "y", "u"};
//String teclas[7] = {1, 2, 3, 4, 5, 6, 7} 
//String teclas[7] = {i, o, p, a, s, d, f}
//======================================================

//==============Configurações Iniciais===================
bool teclaPressionada[7] = {false, false, false, false, false, false, false};   
const int pinosBananas[7] = {4, 13, 12, 15, 14, 27, 33 };  
BleKeyboard bleKeyboard("TecladoBanana", "Math e Thigas", 100);
//=======================================================

//=================== Setup ===========================
void setup() {
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
  if(bleKeyboard.isConnected()) {
    Serial.println("Conectado!!!");
  } else {
    Serial.println("Desconectado!!!");
  }
  delay(250);
}
//=======================================================

//============= Logica das Teclas/Pinos ===================
void teclaTocada() {
  for (int i = 0; i < 8; i++) {
    if (touchRead(pinosBananas[i]) < 22) { // Se a leitura do pino for menor que 22 significa que a tecla está pressionada.
      //Logica para pressionar a tecla .
      if (!teclaPressionada[i]) {
        teclaPressionada[i] = true;
        bleKeyboard.press(teclas[i][0]); // Pressiona a tecla 
        //Serial.println("Tecla pressionada: " + teclas[i]);
        //setDelay()? blekey
        digitalWrite(2, HIGH);
      }
      //Logica para despressionar tecla e evitar repetição
    } else {
      if (teclaPressionada[i]) { 
        teclaPressionada[i] = false;
        bleKeyboard.release(teclas[i][0]);
        digitalWrite(2, LOW);
      }
    }
  }
  //=====================================================
}
