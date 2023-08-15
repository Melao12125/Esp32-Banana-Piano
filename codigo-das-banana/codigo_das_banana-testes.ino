#include <WiFiManager.h>
//#include <BLEDevice.h>
#include <BleKeyboard.h>
//tlvz tirar bledevice e deixar de fundo?

//WiFiManager wifiManager;

//============== Definindo teclas ======================
String teclas[4] = {"q", "w", "e", "r"}; //, , "t", "y", "u"
//String teclas[7] = {1, 2, 3, 4, 5, 6, 7}
//String teclas[7] = {i, o, p, a, s, d, f}
//======================================================

//===========Configurações Iniciais do Teclado===========
bool teclaPressionada[4] = {false, false, false, false}; // false, false, false, false, false   
const int pinosBananas[4] = {33, 32, 12, 15}; //27 -> 14, 33, 32 
BleKeyboard bleKeyboard("TecladoBanana", "Math e Thigas", 100);
bool res;
//======================================================

//=================== Setup ===========================
void setup() {

  wifiManager.autoConnect("TecladoBanana_AP");
  
  for (int i = 0; i < 4; i++) { //4 temp -> 8
    touchAttachInterrupt(pinosBananas[i], teclaTocada, 40); // Seta o modo de todos os pinos sensores como INPUT
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
  delay(2500);
}
//=======================================================

//============= Logica das Teclas/Pinos ===================
void teclaTocada() {
  
  for (int i = 0; i < 4; i++) { //temp    
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