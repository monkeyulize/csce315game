var Box2D = require('./Box2d.js');
//keep global count of each players lives
var lives = {
	p1: 3,
	p2: 3,
	p3: 3,
	p4: 3
};
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
var wallDef = new b2BodyDef;
var wallFixture = new b2FixtureDef;
var playerFixture = new b2FixtureDef;
var playerDef = new b2BodyDef;
var hornFixture = new b2FixtureDef;
var world = new b2World(new b2Vec2(0, 0), false);
function createWall(x, y, w, h) {
	wallDef.type = b2Body.b2_staticBody;
	wallDef.position.x = x + w/2;
	wallDef.position.y = y + h/2;
	wallFixture.shape = new Box2D.Collision.Shapes.b2PolygonShape;
	wallFixture.shape.SetAsBox(w/2, h/2);
	wallFixture.userData = "WALL";
	world.CreateBody(wallDef).CreateFixture(wallFixture);	
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
createArena(0, 0, 75.4, 55.4);

var launcherDef = new b2BodyDef;
var launcherFixture = new b2FixtureDef;
var launcherSensor = new b2FixtureDef;
var launcher;
function createLauncher(x, y, w, h) {
	launcherDef.type = b2Body.b2_staticBody;
	launcherDef.position.x = x + w/2;
	launcherDef.position.y = y + h/2;
	launcherFixture.shape = new Box2D.Collision.Shapes.b2PolygonShape;
	launcherFixture.shape.SetAsBox(w/2, h/2);
	launcherFixture.userData = "LAUNCHER";
	launcherSensor.shape = new Box2D.Collision.Shapes.b2PolygonShape;
	launcherSensor.shape.SetAsOrientedBox(w/2.5, h/8, new b2Vec2(0, -h/2));
	launcherSensor.userData = "LAUNCHERSENSOR";
	
	launcher = world.CreateBody(launcherDef);
	launcher.CreateFixture(launcherSensor);
	launcher.CreateFixture(launcherFixture);
}

createLauncher(10, 30, 10, 1);

createLauncher(40, 30, 10, 1);



playerDef.type = b2Body.b2_dynamicBody;
playerDef.position.Set(4, 8);

	

playerFixture.shape = new b2CircleShape(1.5);
playerFixture.density = 1;
playerFixture.friction = 0.5;
playerFixture.restitution = 0.5;
playerFixture.userData = "PLAYER";

hornFixture.userData = "HORN";
hornFixture.shape = new b2PolygonShape;
hornFixture.shape.SetAsArray([
	new b2Vec2(2.5*0.866 ,0),
	new b2Vec2(0, 1*1.5),
	new b2Vec2(0, 1*-1.5),
]);
hornFixture.density = 1;
hornFixture.friction = 0.5;
hornFixture.restitution = 0.5;

//add a player to the global game 
var add_player = function(num_players, width, height) {
	console.log("num_players: " + num_players);
	myBodies[num_players-1] = world.CreateBody(playerDef);		
	myBodies[num_players-1].SetPositionAndAngle(
		new b2Vec2(start_positions[num_players-1].x, start_positions[num_players-1].y),0);
	myBodies[num_players-1].SetLinearVelocity(new b2Vec2(0, 0));
	myBodies[num_players-1].SetFixedRotation(false);
	myBodies[num_players-1].SetAngularVelocity(0);
	myBodies[num_players-1].CreateFixture(playerFixture);
	myBodies[num_players-1].CreateFixture(hornFixture); 
	myBodies[num_players-1].userData = {canMove : true, isStunned : false, launchMode : false};
}
var canMove = false;
var isStunned = false;
var launchMode = false;




//track collisions of dynamic shapes, being those shapes that move
var listener = new Box2D.Dynamics.b2ContactListener;
world.SetContactListener(listener);
listener.BeginContact = function(contact) {
	var body1 = contact.GetFixtureA();
	var body2 = contact.GetFixtureB();
	if(body1.GetUserData() == 'HORN' || body1.GetUserData() == 'PLAYER') {
		if(body2.GetUserData() == 'LAUNCHERSENSOR') {
			for(i = 0; i < myBodies.length; i++) {
				if(body1.GetBody() == myBodies[i]) {
					myBodies[i].userData.launchMode = true;
				}
			}	
		}
	} else if(body2.GetUserData() == 'HORN' || body2.GetUserData() == 'PLAYER') {
		if(body1.GetUserData() == 'LAUNCHERSENSOR') {
			for(i = 0; i < myBodies.length; i++) {
				if(body2.GetBody() == myBodies[i]) {
					myBodies[i].userData.launchMode = true;
				}
			}
		}
	}
	
	
	if(body1.GetUserData() == 'HORN') {
		if(body2.GetUserData() == 'PLAYER') {
			for(i = 0; i < myBodies.length; i++) {
				if(body2.GetBody() == myBodies[i]) {
					lives["p"+(i+1)]--;
				}
			}				
		} else if(body2.GetUserData() == 'WALL') {
			if(body1.GetBody().GetLinearVelocity().Length() > 10) {
				for(i = 0; i < myBodies.length; i++) {
					if(body1.GetBody() == myBodies[i]) {
						myBodies[i].userData.isStunned = true;
					}
				}				
				isStunned = true;
				body1.GetBody().SetLinearDamping(
					Math.log(body1.GetBody().GetLinearVelocity().Length())
				);
			}					
		}
	} else if(body2.GetUserData() == 'HORN') {
		if(body1.GetUserData() == 'PLAYER') {
			for(i = 0; i < myBodies.length; i++) {
				if(body1.GetBody() == myBodies[i]) {
					lives["p"+(i+1)]--;
				}
			}				
		} else if(body1.GetUserData() == 'WALL') {
			if(body2.GetBody().GetLinearVelocity().Length() > 10) {
				for(i = 0; i < myBodies.length; i++) {
					if(body1.GetBody() == myBodies[i]) {
						myBodies[i].userData.isStunned = true;
					}
				}
				isStunned = true;
				body2.GetBody().SetLinearDamping(
					Math.log(body2.GetBody().GetLinearVelocity().Length())
				);
			}					
		}
	} 
}  

//allow rotation to mouse pointer for player to turn, include all logic for angles and turning
function rotate_to_mouse(playerID, mouseX, mouseY) {
	var pos = new b2Vec2(myBodies[playerID].GetPosition().x, myBodies[playerID].GetPosition().y);
	var a1 = mouseY - pos.y;
	var b1 = mouseX - pos.x;
	var angle1_act = Math.atan2(a1, b1);
	var angle1;
	
	var turning_speed = Math.PI;
	
	var angle2 = myBodies[playerID].GetAngle();
	if(angle2 < 0) {
		angle2 += 2*Math.PI;
		myBodies[playerID].SetAngle(angle2);
	}
	if(angle2 > 2*Math.PI) {
		angle2 -= 2*Math.PI;
		myBodies[playerID].SetAngle(angle2);
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
			myBodies[playerID].userData.canMove = false;
		} else if(angle2 < Math.PI) {
			if(angle1 <= (angle2 + Math.PI)) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 + Math.PI)) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			myBodies[playerID].userData.canMove = false;
		}
		
	}else if(angle1 < Math.PI) {
		if(angle2 >= Math.PI) {
			if(angle1 <= (angle2 - Math.PI)) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 - Math.PI)) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			myBodies[playerID].userData.canMove = false;
		} else if(angle2 < Math.PI) {
			if(angle1 <= angle2) {
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}else if(angle1 > angle2) {
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}
			myBodies[playerID].userData.canMove = false;
		}
	}
	if((Math.abs(angle2 - angle1) <= 0.1) || (Math.abs(angle2 - angle1) >= 6.1)) {
		myBodies[playerID].SetAngularVelocity(0);
		myBodies[playerID].userData.canMove = true;
	}
}
//delete player from game, currently used in deleting player from game
var destroy_body = function(playerID) {	
	world.DestroyBody(myBodies[playerID]);
	lives["p"+(playerID+1)] = 3;
}

//update the physics including movement, collisions, and setting the state of the game		
var update = function(playerID, isMouseDown, mouseX, mouseY) {
	var SCALE_FACTOR = 3;
	var LAUNCH_SPEED = 700;

	var temp_data = myBodies[playerID].userData;
	if(temp_data.launchMode == true) {
		rotate_to_mouse(playerID, mouseX, mouseY);
		myBodies[playerID].SetLinearVelocity(new b2Vec2(0, 0));
		rotate_to_mouse(playerID, mouseX, mouseY);
		if(undefined != mouseX) {
			lastMouseX = mouseX;
		}
		if(undefined != mouseY) {
			lastMouseY = mouseY;
		}
		if(!isMouseDown) {
			myBodies[playerID].userData.launchMode = false;
			console.log("launched " + playerID);
			var vec = new b2Vec2((lastMouseX - myBodies[playerID].GetPosition().x), (lastMouseY - myBodies[playerID].GetPosition().y));
			var vec_length = Math.sqrt(vec.x*vec.x + vec.y*vec.y);
			vec.x = (vec.x/vec_length) * LAUNCH_SPEED;
			vec.y = (vec.y/vec_length) * LAUNCH_SPEED;
			myBodies[playerID].ApplyImpulse(vec, myBodies[playerID].GetPosition());
			
		}		
	}
	if(myBodies[playerID].GetLinearVelocity().Length() < 0.8 && myBodies[playerID].GetLinearDamping() != 0) {
		myBodies[playerID].SetLinearVelocity(new b2Vec2(0, 0));
		myBodies[playerID].SetLinearDamping(0);
		myBodies[playerID].userData.isStunned = false;
		isStunned = false;
	}
	
	if(!isMouseDown && temp_data.launchMode == false) {
		myBodies[playerID].SetAngularVelocity(0);
	}		
	if(isMouseDown && temp_data.canMove == true && temp_data.isStunned == false && temp_data.launchMode == false) {
		myBodies[playerID].SetLinearDamping(0);
		var vec = new b2Vec2((mouseX - myBodies[playerID].GetPosition().x), (mouseY - myBodies[playerID].GetPosition().y));
		var vec_length = Math.sqrt(vec.x*vec.x + vec.y*vec.y);
		vec.x = (vec.x/vec_length) * SCALE_FACTOR;
		vec.y = (vec.y/vec_length) * SCALE_FACTOR;
		myBodies[playerID].ApplyImpulse(vec, myBodies[playerID].GetPosition());
		rotate_to_mouse(playerID, mouseX, mouseY);
	} else if(isMouseDown && temp_data.canMove == false && temp_data.launchMode == false) {
		myBodies[playerID].SetLinearDamping(1);
		rotate_to_mouse(playerID, mouseX, mouseY);
	}
	var angle = myBodies[playerID].GetAngle();
	var positionX = myBodies[playerID].GetPosition().x;
	var positionY = myBodies[playerID].GetPosition().y;

	world.Step(1/60, 8, 3);
	
	world.ClearForces();
	return {positionX : positionX, positionY : positionY, angle : angle, playerID : playerID, lives : lives["p"+(playerID+1)], state : temp_data}	
}

//export functions for server usage.
module.exports.add_player = add_player;
module.exports.update = update;
module.exports.destroy_body = destroy_body;