var app = require('http').createServer(handler);
var io = require('socket.io').listen(app);
var fs = require('fs')

app.listen(10111);

function handler(request, response) {
  fs.readFile(
	__dirname + '/index.html',
    function(err, content) {
      if (err) {
        response.writeHead(500);
        return response.end('Error loading index.html!');
      }
      response.writeHead(200, {'Content-Type': 'text/html'});
      response.end(content);
    });
}


io.sockets.on( 
	'connection', 
	function(client) {
		client.emit('welcome', 'Welcome to the game server');
		client.on(
		'update',
		function(message) {
		console.log(message);
		});
	});
