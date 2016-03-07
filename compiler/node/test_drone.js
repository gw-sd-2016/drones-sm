var arDrone = require('ar-drone');
var client = arDrone.createClient();
var net = require('net');

var server = net.createServer(function(socket) {
		console.log("Connection from " + socket.remoteAddress);
		socket.on('data', function (data) {
			console.log(socket.remoteAddress + "> " + data);
			client.takeoff();
			client
			.after(5000, function() {
				this.clockwise(0.5);
				})
			.after(3000, function() {
				this.animate('flipLeft', 15);
				})
			.after(1000, function() {
				this.stop();
				this.land();
				});

			});
		socket.write('Echo server\r\n');
		console.log("Hello connection received");
		socket.pipe(socket);
});

server.listen(1337, '127.0.0.1');
/*
client.takeoff();

client
.after(5000, function() {
		this.clockwise(0.5);
		})
.after(3000, function() {
		this.animate('flipLeft', 15);
		})
.after(1000, function() {
		this.stop();
		this.land();
		});
*/
