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
io.sockets.on('connection', function (socket) {
	socket.emit('ready', { playerID: p_id });
	players[p_id] = p_id;
	p_id++;
	
	
	socket.on('wh', function(data) {
		game.init(players, data.width, data.height);
	});
	socket.on('mouse data', function (data) {
		console.log(data);
		game.update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
	});
	
	socket.on('disconnect', function () {
		io.sockets.emit('user disconnected');
		p_id--;
	});
	
});




