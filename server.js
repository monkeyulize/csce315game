var server = require('http').createServer(handler);
var io = require('socket.io').listen(server);
var fs = require('fs')	
var game = require('./game');
server.listen(24130);
io.set('log level', 1);

function handler (req, res) {
  
  
  //console.log(req.url);
	if(req.url == "/") {
		fs.readFile(__dirname + '/client_index.html',
		function (err, data) {
			if (err) {
				res.writeHead(500);
				return res.end('Error loading index.html');
			}
		
			res.writeHead(200);
			res.end(data);
		});
		} else if(req.url == "/Box2d.js") {
			fs.readFile(__dirname + '/Box2d.js',
			function (err, data) {
				if (err) {
					res.writeHead(500);
					return res.end('Error loading index.html');
				}
				res.writeHead(200);
				res.end(data);
			});
		}
}
var p_id = 0;
var players = new Array();
var clients = [];
io.sockets.on('connection', function (socket) {
	console.log("player " + p_id + " connected");
	console.log("socket ID: " + socket.id);
	clients[p_id] = {"socket" : socket.id};
	players[p_id] = p_id;
	io.sockets.socket(clients[p_id].socket).emit('player connected', { playerID: p_id, num_players : players.length });	
	socket.broadcast.emit('player joined', {num_players : players.length, other_playerID : p_id});
	p_id++;
	socket.on('wh', function(data) {
		game.add_player(players.length, 800, 600);
	});
	socket.on('mouse data', function (data) {
		var pos_data = game.update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
		if(pos_data.lives <= 0) {
			game.destroy_body(data.playerID);
			io.sockets.emit('player disconnected', {id_to_destroy : data.playerID});
		}
		
		io.sockets.emit('pos data', pos_data);
	});
	socket.on('disconnect', function () {
		for(i = 0; i < clients.length; i++) {
			if(clients[i].socket == socket.id) {
				console.log("player " + i + " disconnected");
				game.destroy_body(i);
				io.sockets.emit('player disconnected', {id_to_destroy : i});
			}
		}
		p_id--;
		players.pop();
	});
});




