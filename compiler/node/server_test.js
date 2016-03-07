var net = require('net');

var server = net.createServer(function(socket) {
		console.log("Connection from " + socket.remoteAddress);
		socket.on('data', function (data) {
			console.log(socket.remoteAddress + "> " + data);
			});
		socket.write('Echo server\r\n');
		console.log("Hello connection received");
		socket.pipe(socket);
		});

server.listen(1337, '127.0.0.1');
