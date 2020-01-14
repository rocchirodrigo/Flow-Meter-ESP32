/****************SENSOR DE VAZÃO**************/

var cont = 0; // Contador de bordas (subida)
var Litros = 0; // Variável intermediária
var Total = 0;  // Total de Litros Consumidos
var Vazao;      // Vazão instantânea

setInterval(function() {
  Litros = cont*0.00225;
  Total = Total + Litros;
  Vazao = Litros * 60;
  Litros = 0;
  console.log("Litros = " + Total + "L consumidos");
  console.log("Vazao = " + Vazao + "L/min");
}, 1000);

setWatch(function(D34) {
  cont = cont + 1;
}, D34, {repeat: true, edge: 'rising'});

/****************WIFI************************/

var wifi = require('Wifi');
var ssid = 'AndroidAPD956';
var password = 'n12345678';
var port = 80;

function processRequest (req, res) {
  res.writeHead(200);
  res.end("Litros = " + Total + "L consumidos");
}

wifi.connect(ssid, {password: password}, function() {

    var http = require('http');
    http.createServer(processRequest).listen(port);

  console.log(`Web server running at http://${wifi.getIP().ip}:${port}`)});
