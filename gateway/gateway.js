// require
var socketio = require('socket.io');
var rabbitmq = require('rabbit.js');

// init
var rabbitcontext = rabbitmq.createContext('amqp://localhost');
var io = socketio.listen(80);

io.sockets.on('connection', function (connection) {

	var pubConnect = rabbitcontext.socket('PUB');
	var pub = rabbitcontext.socket('PUB');
	var sub = rabbitcontext.socket('SUB');

	pubConnect.setEncoding('utf8');
	pub.setEncoding('utf8');
	sub.setEncoding('utf8');

	pubConnect.connect("connection");
	pub.connect("gateway:".concat(connection.id));
	sub.connect("client:".concat(connection.id));

	connection.on('message', function(msg) {
    	pub.write(msg);
	});

	sub.on('data', function(msg) {
		connection.emit('message', msg);
	});

	connection.on('disconnect', function() {
		sub.write(JSON.stringify({'event': 'disconnect'}))

		pubConnect.destroy();
		pub.destroy();
		sub.destroy();
	});

	pubConnect.write(JSON.stringify({'event': 'connection', 'socketId':connection.id}));
});


