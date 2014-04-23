csce315game
===========
----------------------------README-------------------------------------

The game is pretty much divided up into two sections. On the client side, the client_index is used. This client_index file is used to connect and communicate with the server.js file. The client_index maintains a canvas and updates locations of itself and other players while also sending to the server file where its mouse is so that the server file can calculate how to move the piece in that direction as well as the consequences for said action. The server is the site used for communication. We used sockets for our communication and when any information is needed to be sent or received, sockets.on is used. Server.js loads the box2d library which is the major library used to generate the shapes controlled by the players as well as dictate their movement. Game.js is included by the server.js file.

--CLIENT SIDE--

client_index: The client_index file has just a couple of major purposes. It connects to the server and sends a "ready" message using the socket, it sends the current position of the user's piece, sends whether or not the mouse left click is held down, and it sends the x and y coordinants of the user's pointer.

    The socket is initialized at the beginning to a port 
    that has been hardcoded in. The default port is the 
    compute.cse.tamu.edu:24130 port. The next function
    sends a ready message to the server if it has connected.

    Two seperate event listeners work to tell the server
    when the left click of the mouse is held down using a
    variable isMouseDown. If it is held down, another
    function is called named handleMouseMove.

    handleMouseMove calculates the position on the gameboard
    where the user's mouse is. it then logs that position to 
    the console and emits this data to the server so that it
    can calculate how the piece should be moving.

    the function getElementPosition is just used for the 
    maintenance of the canvas in the html doc.
--SERVER SIDE--

game.js: The game.js file is where most of the calculations as far as the movement and pieces is done.

    Initially, all the shapes and objects are declared or
    defined. the body object, fixture object, and world are
    all created. the Function createWall is used to create 
    the walls that go along the outside of the level it will
    used in another function.

    The createArena function is where all the walls are drawn
    and the positions at which each player starts is
    established. 

    The user's pieces characteristics are then defined, giving
    different parts different characteristics. The piece, is 
    divided into two different parts; the horn and the body.
    The horns are the part of the piece that has to make
    contact with the other piece for it to harm them.

    the add_player funciton does just that. Upon connection,
    the function creates another body and sets its individual
    characteristics.

    The beginContact listener listens for a collision of some
    sort. This could either be a player-player collision or
    a player-environment collision. If it's a player-player
    collision it determines which player hurt the other
    player, decrements its lives, and stuns the hitting player
    so that he doesn't immediately rehit the player. If the 
    collision was with a wall, it stuns the player for a few
    moments, leaving him vulnerable from an attack.

    The rotate_to_mouse function manages the direction of the 
    piece. If the mouse position is not straight ahead, (which
    it almost never is) this function works to turn the piece
    at a set speed so that it can now go in that direction. If
    the direction is opposing the movement of its current 
    direction, it slows down the piece and works to send the 
    piece in that direction.

    The destroy_body function is used to destroy bodies when
    they are out of health as well as when they are
    disconnected from the server. 

    the update function, takes the position and speed of a
    piece to manage its movement, speed, and direction. It 
    looks to see if the mouse is being held down, and then
    sets variables accordingly. It also gets the position of
    the user's piece and mouse location. It defines how often
    this function will update and returns all the relevant data
    for the piece.
server.js: The server file is the hub of communication. It holds a connection with the clients and also uses the game.js file to take data and do the appropriate thing with it.

    The function handler loads the client_index file as well
    as the Box2D library. 

    The io.sockets.on('connection', function(socket) { 
    notifies other players when a player is connected and 
    increments the number of players so that another player
    will be added to the gameboard. 

    The disconnect function notifies the clients that a player
    has been disconnected and destroys the body associated with
    that client.    
--RUNNING INSTRUCTIONS--
The code is currently stored on the development branch.
In order to run our program, you must download the submitted code, get on putty and connect to the compute.cse.tamu.edu server. Once you have navigated to the directory containing the files, type in "node server.js". This should start the server. If you are within the computer science's VPN, you should be able to connect to the game by going to http://compute.cse.tamu.edu:24133. This is the default port that we run our server on. This connects using a client html to connect to our game running on the compute server.
