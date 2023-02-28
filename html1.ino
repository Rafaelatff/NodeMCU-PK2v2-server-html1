#include <ESP8266WiFi.h>

// Wifi configuration
const char ssid[] = "CYBERDYNE";
const char senha[] = "put your pass here";

// Server configuration
WiFiServer server_name(80); // IP:door -> IP:80

//const byte LED_Green = D4;
const byte greenLED = 2;  // both can be used, 2 (gpio) or D4 (board)
const byte yellowLED = D7;
const byte redLED = D3;
const byte tecla = D0;
#define LDR A0

boolean statusGreenLED = LOW;
boolean statusYellowLED = LOW;
boolean statusRedLED = LOW;

void thingsConfig();
void networkConfig();

void setup() {
  // put your setup code here, to run once:

  // PK2v2 and other things function configuration
  thingsConfig();

  // Configura serial para monitorar conexão via terminal
  Serial.begin(74880);
  delay(100);

  // Network configuration
  networkConfig();

  // Server configuration
  server_name.begin();
  Serial.println("Servidor inicializado");
}

void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server_name.available();
  if(!client) return;

  while(!client.available()) delay(1);

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>"); //Says that we will be using HTML5
  client.println("<html>");
  client.println("<head>");
  client.println("<title>PK2v2</title>"); 
  client.println("<meta http-equiv='refresh' content='2'>");
  //Check how to send UTF-8 by using an ASCII channel
  //client.println("<meta charset=/"UTF-8/"/>"); //Use UTF-8 instead of ASCII -> to use BR char
  client.println("</head>");
  client.println("<body>");
  //client.println("<meta http-equiv='refresh' content='2'>");
  client.println("<h1>PK2v2 content:</h1>");

  // Read input button
  if(digitalRead(tecla) == LOW){
   client.println("<p>Button pressed</p>");
  } else{
    client.println("<p>Button released</p>"); 
  }

  // change LED status
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  if(req.indexOf("greenLEDon") != -1){
    digitalWrite(greenLED,HIGH);
    statusGreenLED = HIGH;
  } else if(req.indexOf("greenLEDoff")!=-1){
    digitalWrite(greenLED,LOW);
    statusGreenLED = LOW;
  } else if(req.indexOf("yellowLEDon") != -1){
    digitalWrite(yellowLED,HIGH);
    statusYellowLED = HIGH;
  } else if(req.indexOf("yellowLEDoff")!=-1){
    digitalWrite(yellowLED,LOW);
    statusYellowLED = LOW;
  } else if(req.indexOf("redLEDon") != -1){
    digitalWrite(redLED,HIGH);
    statusRedLED = HIGH;
  } else if(req.indexOf("redLEDoff")!=-1){
    digitalWrite(redLED,LOW);
    statusRedLED = LOW;
  }
  if(!statusGreenLED) client.println("<p>Green LED: <a href=\"greenLEDon\"><button>Turn green LED ON</button></a></p>");
  else client.println("<p>greenLED <a href=\"greenLEDoff\"><button>Turn green LED OFF</button></a></p>");
  if(!statusYellowLED) client.println("<p>Yellow LED: <a href=\"yellowLEDon\"><button>Turn yellow LED ON</button></a></p>");
  else client.println("<p>yellowLED <a href=\"yellowLEDoff\"><button>Turn yellow LED OFF</button></a></p>");
  if(!statusRedLED) client.println("<p>Red LED: <a href=\"redLEDon\"><button>Turn red LED ON</button></a></p>");
  else client.println("<p>redLED <a href=\"redLEDoff\"><button>Turn red LED OFF</button></a></p>");

  client.println("</body>");
  client.println("</html>");
}
void thingsConfig(){
  // Digital output configuration
  pinMode(greenLED,OUTPUT);
  pinMode(yellowLED,OUTPUT);
  pinMode(redLED,OUTPUT);

  // Digital input configuration
  pinMode(tecla,INPUT); // 10k pull-up
}

void networkConfig(){
  Serial.print("\r\n"); // new line and carriage return
  Serial.print("Conectando a rede ");
  Serial.println(ssid);

  WiFi.begin(ssid, senha);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" ");
  Serial.println("WiFi Conectado");
  Serial.println("Endereço de IP:");
  Serial.println(WiFi.localIP());
}
