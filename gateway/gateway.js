// require
var socketio = require('socket.io');
var rabbitmq = require('rabbit.js');

// init
var rabbitcontext = rabbitmq.createContext('amqp://localhost');
var io = socketio.listen(80);

io.sockets.on('connection', function (socket) {
	socket.emit('news', { hello: 'world' });
	socket.on('my other event', function (data) {
		console.log(data);
	});
});


