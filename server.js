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
var p_id = 1;
var players = new Array();
io.sockets.on('connection', function (socket) {
	socket.emit('ready', { playerID: p_id });
	players[p_id-1] = p_id;
	p_id++;
	game.init(players);
	
	
	socket.on('mouse data', function (data) {
		console.log(data);
		game.update(data.playerID, data.mouseX, data.mouseY);
	});
	
});




