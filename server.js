//define aspects of server such as what files to keep track of, what files needing to store, and what js files to 
//use, in this case http protocol, store files, use socket.io, and use game.js, and listen on port 24133
var server = require('http').createServer(handler).listen(24133);
var io = require('socket.io').listen(server);
var fs = require('fs')	
var game = require('./game');
io.set('log level', 1);

io.sockets.on('connection', function(socket) {
	game.initGame(io, socket);
});

function handler (req, res) {
	//handle request of client_index
	if(req.url == "/") {
		fs.readFile(__dirname + '/client_index.html',
		function (err, data) {
			if (err) {
				res.writeHead(500);
				return res.end('Error loading client_index.html');
			}
		
			res.writeHead(200);
			res.end(data);
		});
		}
		//reply to request of box2d
		else if(req.url == "/Box2d.js") {
			fs.readFile(__dirname + '/Box2d.js',
			function (err, data) {
				if (err) {
					res.writeHead(500);
					return res.end('Error loading Box2d.js');
				}
			
				res.writeHead(200);
				res.end(data);
			});
		}
	
}
//store a local player id, and keep track of players and clients
/* var p_id = 0;
var players = new Array();
var clients = []; */

//see when a player has connected and store information, while adding information to global game
/* io.sockets.on('connection', function (socket) {
	console.log("player " + p_id + " connected");
	console.log("socket ID: " + socket.id);
	clients[p_id] = {"socket" : socket.id};
	players[p_id] = p_id;
	io.sockets.socket(clients[p_id].socket).emit('player connected', { playerID: p_id, num_players : players.length });	
	//let clients know a new player has joined
	socket.broadcast.emit('player joined', {num_players : players.length, other_playerID : p_id});
	p_id++;
	
	socket.on('wh', function(data) {
		//add a player to the servers game 
		game.add_player(players.length, 800, 600);
		
	});
	
	
	
	//emits and updates the players mice and mice locations 
	socket.on('mouse data', function (data) {
		var pos_data = game.update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
		io.sockets.emit('pos data', pos_data);
	});
	
	//sees when a player has disconnected and let other clients know they have disconnected for deletion
	socket.on('disconnect', function () {
		//send disconnect message to every client, and delete disconnect on every local game
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
 */



