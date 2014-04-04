var server = require('http').createServer(handler);
var io = require('socket.io').listen(server);
var fs = require('fs')	
var game = require('./game');
server.listen(24130);
io.set('log level', 1);




function handler (req, res) {
  fs.readFile(__dirname + '/client_index.html',
  function (err, data) {
    if (err) {
      res.writeHead(500);
      return res.end('Error loading index.html');
    }

    res.writeHead(200);
    res.end(data);
  });
}
var p_id = 0;
var players = new Array();
var clients = [];
io.sockets.on('connection', function (socket) {
	clients[p_id] = {"socket" : socket.id};
	players[p_id] = p_id;
	io.sockets.socket(clients[p_id].socket).emit('player connected', { playerID: p_id, num_players : players.length });	
	socket.broadcast.emit('player joined', {num_players : players.length, other_playerID : p_id});
	p_id++;
	
	socket.on('wh', function(data) {
		game.add_player(players.length, 800, 600);
	});
	
	
	socket.on('mouse data', function (data) {
		//console.log(data);
		var pos_data = game.update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
		io.sockets.emit('pos data', pos_data);
	});
	
	socket.on('disconnect', function () {
		io.sockets.emit('user disconnected');
		p_id--;
		players.pop();
	});
	
});




