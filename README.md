# NodeMCU-PK2v2-server-html1
Writting first code lines using NodeMCU as a server and generating some code in &lt;html>.

This is a follow up from the content of [network](https://github.com/Rafaelatff/NodeMCU-PK2v2-network) studies using ESP8266.

## Code 1

The purpose of this code is to connect to the NodeMCU (server) via browser and receive the messagem "Hello World!". The network configuration will be moved inside a new function, since it is already completed.

We will start by declaring the WiFiServer type, with name 'server_name' and send the value '80', that will consist in being the server door.

```c
// Server configuration
WiFiServer server_name(80); // IP:door -> IP:80
```

Then in the 'void setup()' we add the server configuration/setup for our 'server_name'. It uses a class function.

```c
  // Server configuration
  server_name.begin();
  Serial.println("Servidor inicializado");
 ```

To understand and help us a little bit with of HTML code, we will be using the [OpenGDB](https://www.onlinegdb.com) editor and learning from the [Curso em vídeo](https://www.youtube.com/@CursoemVideo/playlists) that was a recommendation from my brother about the subject.

The first structure that OpenGDB give us for the HTML code is:

```html
<html>
<body>
<h1>Hello World</h1>
</body>
</html>
```
To understand better the code and also learn more things:

* Every HTML code uses marks/tags html: < > 
* Every (or at least almost all) HTML code has an opening <example> and a closure </example>
* Every HTML code is betwen <html> and </html>
* To say the code is in HTML5 we need to add, before <html> is the line <!DOCTYPE html>.
* We can inform the language by adding: (this helps search engines)
```html
  <html lang="pt-bt"> 
```
* In HTML we have two main areas, the header:
```html
    <head> </head>
```
* and then the body:
```html
    <body></body>
```
* Portuguese (latin, with acentuation) text must use UTF-8 instead of ASCII.
* In the <head> area add:
```html    
    <meta charset="UTF-8">
```
* Above is tag without closure, but optionaly we can add the '/' at the code:
```html
<meta charset="UTF-8"/>
```
* To add a browser tab name we just add to <head> the following: 
```html  
  <title>Tab Name</title>
```
* To create titles in the text that will be displayed, we can add text inside the tags:
```html
  <h1> </h1>
```
* To follow the title hierarchy, we have the subtitles:
```html  
  <h2> </h2>
```
* To change the formatting of the text, we use CSS3 code inside the HTML5 code.

```html
<head>
<style>
  h1 {
      font-family: Arial;
      font-size: 30pt;
      color: blue;
      text-shadow: 2px 2px 2px black; // deslocamento lateral direita, deslocamento vertical, espalhamento, shadow collor
  }
</style>      
</head>
```
  
Now let's go back to our **C/C++** code. Let's do a simple code. To send the HTML code we will use the same class function that sends message to Serial Monitor terminal. It's C++ so we use and abuse of class functions. Our 'void loop()' will be like:

```c
void loop() {
  // put your main code here, to run repeatedly:
  WiFiClient client = server_name.available();
  if(!client){
    return;
  }

  while(!client.available()){
    delay(1);
  }

  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>"); //Says that we will be using HTML5
  client.println("<html>");
  client.println("<head>");
  //Check how to send UTF-8 by using an ASCII channel
  //client.println("<meta charset=/"UTF-8/"/>"); //Use UTF-8 instead of ASCII -> to use BR char
  client.println("</head>");
  client.println("<body>");
  //client.println("<meta http-equiv='refresh' content='2'>");
  client.println("<h1>Hello World!</h1>");
  client.println("<h2>Olá mundo!</h2>");
  client.println("</body>");
  client.println("</html>");
}
```
  
![IMG_20230225_210815_HDR](https://user-images.githubusercontent.com/58916022/221385737-3f7b7bab-1dcf-4984-9c2d-b3c11baa52d9.jpg)

## Code 2
    
Now, via browser, let's read the status of the button connected to D0. It is easy to do that, in the *body*, just add the lines:
    
```c
  if(digitalRead(tecla) == LOW){
   client.println("<p>Button pressed</p>");
  } else{
    client.println("<p>Button released</p>"); 
  }
```   

Note, the status will be update only when you refresh the browser. Let's add in the *head* two commands marks. One to give a name to the tab:
    
```c
    client.println("<title>PK2v2</title>"); 
```
    
And the mark to refresh the web browser:
    
```c
    client.println("<meta http-equiv='refresh' content='2'>");
```
    
Results:
    
![image](https://user-images.githubusercontent.com/58916022/221423239-e2055585-ea05-4f3d-b888-98d2e0bf132b.png)
    
Tip: To understand better the functions that we will be using, or install new libraries, go to 'Sketch' -> 'Include Library' -> 'Manage Libraries...'.    
![image](https://user-images.githubusercontent.com/58916022/221428657-cb1e5cee-21a5-4fd9-9bdb-f0fa7c049b30.png)

## Code 3
    
Now, let's control the 3 LEDs of PK2v2.

Let's add boolean global variables to hold the status for the LEDs.

```c
boolean statusGreenLED = LOW;
boolean statusYellowLED = LOW;
boolean statusRedLED = LOW;
```
Then, inside the *body* part of the *html* code, we will be adding:
    
```c
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
```

Then, we will get as results:
    
 
  ![WhatsApp Video 2023-02-27 at 21 30 46 (3)](https://user-images.githubusercontent.com/58916022/221722525-c2443ecd-1d62-4ead-b7b1-4250225554fd.gif)
  
    
    

