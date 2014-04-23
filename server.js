var server = require('http').createServer(handler);
var io = require('socket.io').listen(server);
var fs = require('fs')	
var game = require('./game');
var static = require('node-static');
var file = new static.Server('./');
server.listen(24131);
io.set('log level', 1);

function handler (req, res) {
	req.addListener('end', function() {
		file.serve(req,res);
	}).resume();
}
var p_id = 0;
var p_ids = {
	0 : 'free',
	1 : 'free',
	2 : 'free',
	3 : 'free'
}
var player_names = new Array();
var players = new Array();
var clients = [];
io.sockets.on('connection', function (socket) {
	p_id = 0;
	for(i = 0; i < 4; i++) {
		if(p_ids[i] == 'free') {
			p_ids[i] = 'taken';
			p_id = i;
			break;
		}	
	}
	socket.on('name', function(data) {
		player_names[data.id] = data.name;	
		for(i = 0; i < player_names.length; i++) {
			io.sockets.emit('player name', {id : i, name : player_names[i]});
		}
		
	});
	console.log("player " + p_id + " connected");
	console.log("socket ID: " + socket.id);
	clients[p_id] = {"socket" : socket.id};
	players[p_id] = p_id;
	io.sockets.socket(clients[p_id].socket).emit('player connected', { playerID: p_id, num_players : players.length });	
	socket.broadcast.emit('player joined', {num_players : players.length, other_playerID : p_id});
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
				p_ids[i] = 'free';
				console.log("player " + i + " disconnected");
				game.destroy_body(i);
				io.sockets.emit('player disconnected', {id_to_destroy : i});
			}
		}
		players.pop();
	});
});




