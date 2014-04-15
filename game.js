var Box2D = require('./Box2d.js');
//keep global count of each players lives
var lives = {
	p1: 3,
	p2: 3,
	p3: 3,
	p4: 3
};
var p_id = 0;
var players = new Array();
var clients = [];
var io, socket;
module.exports.initGame = function(_io, _socket) {
	io = _io;
	socket = _socket;
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
		add_player(players.length, 800, 600);
		
	});

	//emits and updates the players mice and mice locations 
	socket.on('mouse data', function (data) {
		var pos_data = update(data.playerID, data.isMouseDown, data.mouseX, data.mouseY);
		io.sockets.emit('pos data', pos_data);
	});
	
	//sees when a player has disconnected and let other clients know they have disconnected for deletion
	socket.on('disconnect', function () {
		//send disconnect message to every client, and delete disconnect on every local game
		for(i = 0; i < clients.length; i++) {
			if(clients[i].socket == socket.id) {
				console.log("player " + i + " disconnected");
				destroy_body(i);
				io.sockets.emit('player disconnected', {id_to_destroy : i});
			}
		}
		p_id--;
		players.pop();
	});
}






//declare and define objects and classes needed for box2d
var myBodies = [];
var    b2Vec2 = Box2D.Common.Math.b2Vec2
,	   b2Cross = Box2D.Common.Math.b2Cross
,      b2BodyDef = Box2D.Dynamics.b2BodyDef
,      b2Body = Box2D.Dynamics.b2Body
,      b2FixtureDef = Box2D.Dynamics.b2FixtureDef
,      b2World = Box2D.Dynamics.b2World
,      b2BoxDef = Box2D.Dynamics.b2BoxDef
,      b2PolygonShape = Box2D.Collision.Shapes.b2PolygonShape
,      b2CircleShape = Box2D.Collision.Shapes.b2CircleShape
,	   b2EdgeShape = Box2D.Collision.Shapes.b2EdgeShape
,      b2RevoluteJointDef=Box2D.Dynamics.Joints.b2RevoluteJointDef
,      b2MouseJointDef =  Box2D.Dynamics.Joints.b2MouseJointDef
,      b2DebugDraw = Box2D.Dynamics.b2DebugDraw
,      b2Fixture = Box2D.Dynamics.b2Fixture
,      b2AABB = Box2D.Collision.b2AABB;

//declare the shape class, fixture class, and the world for physics
var bodyDef = new b2BodyDef;
var myFixture = new b2FixtureDef;
var world = new b2World(new b2Vec2(0, 0), false);

//create global copy of a wall
function createWall(x, y, w, h) {
	bodyDef.type = b2Body.b2_staticBody;
	bodyDef.userData = 'WALL';
	bodyDef.position.x = x + w/2;
	bodyDef.position.y = y + h/2;
	myFixture.shape = new Box2D.Collision.Shapes.b2PolygonShape;
	myFixture.shape.SetAsBox(w/2, h/2);
	world.CreateBody(bodyDef).CreateFixture(myFixture);	
}

//create global copy of all 4 walls, and all 4 spawn locations	
var start_positions = new Array();	
	function createArena(x, y, w, h) {
		createWall(x, y, w, 1);	//top wall
		createWall(x, y, 1, h);	//left wall
		createWall(x + w, y, 1, h);	//right wall
		createWall(x, y + h - 1, w, 1);	//bottom wall
	
		start_positions[0] = {x: x + 10, y: y + 10};
		start_positions[1] = {x: x + w - 10, y: y + 10};
		start_positions[2] = {x: x + 10, y: y + h - 10};
		start_positions[3] = {x: x + w - 10, y: y + h - 10};
	}
	var w = 400;
	var l = 300;
	createArena(15, 15, w, l);


bodyDef.type = b2Body.b2_dynamicBody;
bodyDef.position.Set(4, 8);
bodyDef.SetUserData('PLAYER');
	
//define the horn and body subshapes
myFixture.shape = new b2CircleShape(3);
myFixture.density = 1;
myFixture.friction = 0.5;
myFixture.restitution = 0.5;
var myHorn = new b2FixtureDef;
myHorn.SetUserData('HORN');
myHorn.shape = new b2PolygonShape;
myHorn.shape.SetAsArray([
	new b2Vec2(5*0.866 ,0),
	new b2Vec2(0, 3*1.5),
	new b2Vec2(0, 3*-1.5),
]);
myHorn.density = 1;
myHorn.friction = 0.6;
myHorn.restitution = 0.5;

//add a player to the global game 
var add_player = function(num_players, width, height) {
	console.log("num_players: " + num_players);
	myBodies[num_players-1] = world.CreateBody(bodyDef);	
	myBodies[num_players-1].SetPositionAndAngle(
		new b2Vec2(start_positions[num_players-1].x, start_positions[num_players-1].y),0);
	myBodies[num_players-1].SetLinearVelocity(new b2Vec2(0, 0));
	myBodies[num_players-1].SetFixedRotation(false);
	myBodies[num_players-1].SetAngularVelocity(0);
	myBodies[num_players-1].CreateFixture(myFixture);
	myBodies[num_players-1].CreateFixture(myHorn); 
	
	console.log(width);
	console.log(height);
}

//track collisions of dynamic shapes, being those shapes that move
var listener = new Box2D.Dynamics.b2ContactListener;
world.SetContactListener(listener);
listener.BeginContact = function(contact) {
			
			//temp body is collider, temp coli is collidee
			var temp_body = contact.GetFixtureA();
			var temp_coli = contact.GetFixtureB();
			console.log("my type "+temp_body.GetFriction());
			console.log("there type "+temp_coli.GetFriction());
			console.log("you hit something!");
			console.log("impact velocity = " + temp_body.GetBody().GetLinearVelocity().Length());

			//hit other player
			if(temp_coli.GetBody().GetUserData() != 'WALL')
			{
				console.log("hit a " + temp_body.GetBody().GetUserData());
				//find which body was hit
					for(i = 0; i < myBodies.length; i++) {
						if(temp_coli.GetBody() == myBodies[i]) {
							lives["p"+(i+1)]--;
							socket.emit('lose life', {lives: lives["p"+(i+1)]});
							console.log("player " + (i+1) + " " + lives["p"+(i+1)]);
						}
					}
			}

			//hit a wall too hard
			if(temp_body.GetBody().GetLinearVelocity().Length() > 25 && temp_coli.GetBody().GetUserData() == 'WALL') {
				console.log("hit wall too hard!");
				console.log("setting damping to: " + Math.log(temp_body.GetBody().GetLinearVelocity().Length())/2);
				isStunned = true;
				temp_body.GetBody().SetLinearDamping(Math.log(temp_body.GetBody().GetLinearVelocity().Length())/2);
			}
			console.log("isStunned = " + isStunned);	
} 
var canMove = false;
var isStunned = false;
//allow rotation to mouse pointer for player to turn, include all logic for angles and turning
function rotate_to_mouse(playerID, mouseX, mouseY) {
	
	var pos = new b2Vec2(myBodies[playerID].GetPosition().x, myBodies[playerID].GetPosition().y);
	//console.log(pos);
	var a1 = mouseY - pos.y;
	var b1 = mouseX - pos.x;
	var angle1_act = Math.atan2(a1, b1);
	var angle1;
	
	var turning_speed = Math.PI*3;
	
	var angle2 = myBodies[playerID].GetAngle();

	if(angle2 < 0) {
		angle2 += 2*Math.PI;
	}
	if(angle2 > 2*Math.PI) {
		angle2 -= 2*Math.PI;
	}
	
	if (angle1_act < 0) {
		angle1 = 2*Math.PI - (-1 * angle1_act);
	}
	if (angle1_act > 0) {
		angle1 = angle1_act;
	}
	if(angle1 >= Math.PI) {				
		if(angle2 >= Math.PI) {
			if(angle1 <= angle2) {
				myBodies[playerID].SetAngularVelocity(-turning_speed)
			}else if(angle1 > angle2) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}
			canMove = false;				
		} else if(angle2 < Math.PI) {
			if(angle1 <= (angle2 + Math.PI)) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 + Math.PI)) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			canMove = false;
		}
		
	}else if(angle1 < Math.PI) {
		if(angle2 >= Math.PI) {
			if(angle1 <= (angle2 - Math.PI)) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 - Math.PI)) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			canMove = false;				
		} else if(angle2 < Math.PI) {
			if(angle1 <= angle2) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}else if(angle1 > angle2) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}
			canMove = false;
		}
	}
	if((Math.abs(angle2 - angle1) <= 0.1) || (Math.abs(angle2 - angle1) >= 6.1)) {
		myBodies[playerID].SetAngularVelocity(0);
		canMove = true;
	}
}
//delete player from game, currently used in deleting player from game
var destroy_body = function(playerID) {
	world.DestroyBody(myBodies[playerID]);
}

//update the physics including movement, collisions, and setting the state of the game		
var update = function(playerID, isMouseDown, mouseX, mouseY) {
	if(myBodies[playerID].GetLinearVelocity().Length() < 0.8 && myBodies[playerID].GetLinearDamping() != 0) {
		myBodies[playerID].SetLinearVelocity(new b2Vec2(0, 0));
		console.log("resetting damping to 0");
		myBodies[playerID].SetLinearDamping(0);
		isStunned = false;
		console.log("isStunned = " + isStunned);
	}
	
	if(!isMouseDown) {
		myBodies[playerID].SetAngularVelocity(0);
	}		
	if(isMouseDown && canMove == true && isStunned == false ) {
		myBodies[playerID].ApplyImpulse(new b2Vec2((mouseX - myBodies[playerID].GetPosition().x), (mouseY - myBodies[playerID].GetPosition().y)), myBodies[playerID].GetPosition());
		
		rotate_to_mouse(playerID, mouseX, mouseY);
	} else if(isMouseDown && canMove == false) {
		rotate_to_mouse(playerID, mouseX, mouseY);
	}
	var angle = myBodies[playerID].GetAngle();
	var positionX = myBodies[playerID].GetPosition().x;
	var positionY = myBodies[playerID].GetPosition().y;

	world.Step(1/60, 8, 3);
	
	world.ClearForces();
	return {positionX : positionX, positionY : positionY, angle : angle, playerID : playerID, lives : lives["p"+(playerID+1)]}	
}

//export functions for server usage.
module.exports.add_player = add_player;
module.exports.update = update;
module.exports.destroy_body = destroy_body;