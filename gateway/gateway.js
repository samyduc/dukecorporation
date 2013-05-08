// require
var socketio = require('socket.io');
var rabbitmq = require('rabbit.js');

// init
var rabbitcontext = rabbitmq.createContext('amqp://localhost');
var io = socketio.listen(80);

io.sockets.on('connection', function (socket) {

	var pub = context.socket('PUB');
	var sub = context.socket('SUB');

	pub.setEncoding('utf8');
	sub.setEncoding('utf8');

	pub.connect("pub:".concat(socket.id))
	sub.connect("sub:".concat(socket.id))

	connection.on('message', function(msg) {
    	pub.write(msg);
	});

	sub.on('data', function(msg) {
		connection.send(msg);
	});

	connection.on('disconnect', function() {
		sub.write(JSON.stringify({'event': 'disconnect'}))

		pub.destroy();
		sub.destroy();
	});
});


