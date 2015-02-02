var WebSocketServer = require("ws").Server,
    express = require("express"),
    http = require("http"),
    app = express(),
    server = http.createServer(app);

// ...

server.listen(8000);


var wss = new WebSocketServer({server: server, path: "/echo"});

wss.on("connection", function(ws){
	console.log("conn");

	ws.on('message', function(message){
		console.log(message);
		ws.send(message);
	});
   // ...
});
