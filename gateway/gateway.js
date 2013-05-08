// require
var socketio = require('socket.io');
var redis = require("redis");

// init
var io = socketio.listen(80);
pub = redis.createClient();

io.sockets.on('connection', function (socket) {

	sub = redis.createClient();

	var push_key = "world:1";
	var rsp_key = "node:".concat(socket.id);

	socket.on('message', function(msg) {
		console.log(msg);
		msg['id'] = socket.id;
    	pub.publish(push_key, JSON.stringify(msg));
	});

	sub.on("message", function (channel, msg) {
		console.log("Send to client");
		console.log(msg);
        socket.emit('message', msg);
    });

	socket.on('disconnect', function() {
		console.log("Client disconnected")

		sub.unsubscribe();
		sub.end();
	});

	sub.subscribe(rsp_key);
});


