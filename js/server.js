/*
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
*/

var app = require('http').createServer(handler);	//http protocol
var io = require('socket.io').listen(app);			//node.js
var fs = require('fs')								//access to local files
app.listen(24130);									// Listen on port 24130 

// Handles HTTP requests.
function handler(request, response) {
  //reads and processes index.html from current working directory
  fs.readFile(
    __dirname + '/index.html',
    function(err, content) {
      if (err) {
        // If an error happened when loading 'index.html', return a 500 error.
        response.writeHead(500);
        return response.end('Error loading index.html!');
      }
      // If no error happened, return the content of 'index.html'
      response.writeHead(200, {'Content-Type': 'text/html'});
      response.end(content);
    });
}

//listens for connection communciation
io.sockets.on(
  'connection',
  function(client) {
    //reply to the client
    client.emit('welcome', 'Welcome to my chat room!');

    

    //listen for update
    client.on(
      'update',
      function(message) {
        // This function tries to get the user name from the client object, and
        // use that to form a chat message that will be sent to all clients.
        if (message && message.msg) {
          client.get(
            'user_name', 
            function(err, name) {
              if (!err) {
                // io.sockets.emit() will send the message to all clients,
                // including the current client. See socket.io FAQ for more
                // examples.
                io.sockets.emit('chat', { user_name: name, msg: message.msg });
              }
            });
        }
      });

    // Print a message when somebody left.
    client.on(
      'disconnect',
      function() {
        client.get(
          'user_name',
          function(err, name) {
            if (name) {
              io.sockets.emit('notification', name + ' left the room.');
            }
          });
      });
  });