var server = require('http').createServer(handler);
var io = require('socket.io').listen(server);
var fs = require('fs')	
var game = require('./game');
server.listen(24130);




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
		game.init(players, data.width, data.height);
	});
	
	
	socket.on('mouse data', function (data) {
		console.log(data);
		var posX, posY, ang;
		//var pos_data = game.update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
		posX = pos_data.positionX;
		posY = pos_data.positionY;
		ang = pos_data.angle;
		/* console.log(posX);
		console.log(posY);
		console.log(ang); */
		//socket.emit('pos data', pos_data);
	});
	
	socket.on('disconnect', function () {
		io.sockets.emit('user disconnected');
		p_id--;
		players.pop();
	});
	
});




