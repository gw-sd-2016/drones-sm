var arDrone = require('ar-drone');
var client = arDrone.createClient();
var net = require('net');

var server = net.createServer(function(socket) {
		console.log("Connection from " + socket.remoteAddress);
		socket.on('data', function (data) {
			console.log(socket.remoteAddress + "> " + data);
			//client
			/*.after(5000, function() {
			  this.clockwise(0.5);
			  })
			  .after(3000, function() {
			  this.animate('flipLeft', 15);
			  })5*/
			if(String(data) === "stop"){
			client.after(3000, function() {
				client.stop();
				console.log("Stop");
				});
			}
			if(String(data) === "up"){
			client.after(3000, function() {
				client.up(.5);
				console.log("Up: .5");
				});
			}
			if(String(data) === "down"){
				client.after(3000, function() {
						client.down(.5);
						console.log("Down: .5");
						});
			}

			if(String(data) === "left"){
				client.after(3000, function() {
						client.left(.5);
						console.log("Left: .5");
						});
			}
			if(String(data) === "right"){
				client.after(3000, function() {
						client.right(.5);
						console.log("Right: .5");
						});
			}
			if(String(data) === "forward"){
				client.after(3000, function() {
						client.front(.5);
						console.log("forward: .5");
						});
			}
			if(String(data) === "back"){
				client.after(3000, function() {
						client.back(.5);
						console.log("back: .5");
						});
			}
			if(String(data) === "s&l"){
				client.after(3000, function() {
						this.stop();
						this.land();
						console.log("Stop and land");
						});
			}
			if(String(data) === "flipleft"){
				client.after(3000, function() {
						this.animate('flipLeft', 15);
						console.log("Flip Left");
						});
			}

			if(String(data) === "clockwise"){
				client.after(3000, function() {
						this.clockwise(0.5);
						console.log("Clockwise");
						});
			}

			if(String(data) === "counterclockwise"){
				client.after(3000, function() {
						this.counterClockwise(0.5);
						console.log("Counter Clockwise");
						});
			}
			if(String(data) === "takeoff"){
				client.takeoff();
				console.log("Takeoff");
			}

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
   .after(1000, function() {
   this.stop();
   this.land();
   });
 */
