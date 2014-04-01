var server = require('http').createServer(handler);
var io = require('socket.io').listen(server);
var fs = require('fs')	
server.listen(24130);

var players = new Array();


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

io.sockets.on('connection', function (socket) {
	socket.emit('ready', { playerID: p_id });
	players[p_id - 1] = p_id
	p_id++;
	
	
	
	socket.on('mouse data', function (data) {
		console.log(data);
	});
	
});




