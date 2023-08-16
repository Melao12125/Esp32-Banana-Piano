// Branch utilizando BleKeyboard para emulação de teclas BlueTooth enquanto conecta-se com WiFi
// Escolha um dos arquivos BleKeyboard ZIP na pasta 'downloads' do repositório e o importe para seu sketch.

// Aviso: Se utilzando a versão otimizada do BleKeyboard importe para o sketch a biblioteca NimBle-Arduino!
// Não precisa incluir a biblioteca NiBle-Arduino no codigo, só basta estar presente dentro do sketch.

#include <BleKeyboard.h>
#include <WiFi.h>

//================Configurações de Pinagem/Wifi/Bluetooth=====================
const char* ssid = "NomeDaRede";
const char* password = "SenhaDaRede";
String teclas[7] = {"q", "w", "e", "r", "t", "y", "u"};
bool teclaPressionada[7] = {false, false, false, false, false, false, false};
const int pinosBananas[7] = {4, 13, 12, 15, 14, 27, 33};
BleKeyboard bleKeyboard("TecladoBanana", "Math e Thigas", 100);

//=======================Setup==============================
void setup() {
  for (int i = 0; i < 8; i++) {
    touchAttachInterrupt(pinosBananas[i], teclaTocada, 40);
    pinMode(pinosBananas[i], INPUT);
  }
  pinMode(2, OUTPUT);

  Serial.begin(115200);
  connectToWiFi();
  bleKeyboard.begin();

//=========================Loop=========================
void loop() {
  if (bleKeyboard.isConnected()) {
    Serial.println("Teclado Conectado");
  } else {
    Serial.println("Teclado Desconectado");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado ao WiFi");
  } else {
    Serial.println("Desconectado do WiFi");
  }
  delay(250);
}

//======================Funções========================
void teclaTocada() {
  for (int i = 0; i < 8; i++) {
    if (touchRead(pinosBananas[i]) < 22) {
      if (!teclaPressionada[i]) {
        teclaPressionada[i] = true;
        bleKeyboard.press(teclas[i][0]);
        digitalWrite(2, HIGH);
      }
    } else {
      if (teclaPressionada[i]) {
        teclaPressionada[i] = false;
        bleKeyboard.release(teclas[i][0]);
        digitalWrite(2, LOW);
      }
    }
  }
}

void connectToWiFi() {
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando...");
  }

  Serial.println("Conectado ao WiFi");
}
