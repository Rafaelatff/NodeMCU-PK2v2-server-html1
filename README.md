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

To understand and help us a little bit with of HTML code, we will be using the [OpenGDB](https://www.onlinegdb.com) editor and learning from the [Curso em vídeo](https://www.youtube.com/@CursoemVideo/playlists) that was a recommendation from my brother about the subject.

The first structure that OpenGDB give us for the HTML code is:

```html
<html>
<body>
<h1>Hello World</h1>
</body>
</html>
```
To understand better the code:

* Every HTML code uses marks/tags html: < > 
* Every (or at least almost all) HTML code has an opening <example> and a closure </example>
* Every HTML code is betwen <html> and </html>
* To say the code is in HTML5 we need to add, before <html> is the line <!DOCTYPE html>.
* We can inform the language by adding: <html lang="pt-bt"> (this helps search engines).
* In HTML we have two main areas, the header (<head> </head>) and then the body (<body></body>).
* Portuguese (latin, with acentuation) text must use UTF-8 instead of ASCII.
* In the <head> area add: <meta charset="UTF-8">.
* Above is tag without closure, but optionaly we can add the '/' at the code: <meta charset="UTF-8"/>.
* To add a browser tab name we just add to <head> the following: <title>Tab Name</title>.
* To create titles in the text that will be displayed, we can add text inside the tags <h1> </h1>.
* <h2> </h2> follows the hierarchy, being a subtitle.
* To change the formatting of the text, we use CSS.

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


## Code 2
