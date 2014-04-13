var Box2D = require('./Box2d.js');
var lives = {
	p1: 3,
	p2: 3,
	p3: 3,
	p4: 3
};

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
var bodyDef = new b2BodyDef;
var myFixture = new b2FixtureDef;
var world = new b2World(new b2Vec2(0, 0), false);
function createWall(x, y, w, h) {
	bodyDef.type = b2Body.b2_staticBody;
	bodyDef.position.x = x + w/2;
	bodyDef.position.y = y + h/2;
	myFixture.shape = new Box2D.Collision.Shapes.b2PolygonShape;
	myFixture.shape.SetAsBox(w/2, h/2);
	world.CreateBody(bodyDef).CreateFixture(myFixture);	
}

	
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
bodyDef.userData = 'BOX';
	

myFixture.shape = new b2CircleShape(3);
myFixture.density = 1;
myFixture.friction = 0.5;
myFixture.restitution = 0.5;
var myHorn = new b2FixtureDef;
myHorn.shape = new b2PolygonShape;
myHorn.shape.SetAsArray([
	new b2Vec2(5*0.866 ,0),
	new b2Vec2(0, 3*1.5),
	new b2Vec2(0, 3*-1.5),
]);
myHorn.density = 1;
myHorn.friction = 0.5;
myHorn.restitution = 0.5;


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



	
		



var listener = new Box2D.Dynamics.b2ContactListener;
world.SetContactListener(listener);
listener.BeginContact = function(contact) {
	var temp_body = contact.GetFixtureA().GetBody();
	for(i = 0; i < myBodies.length; i++) {
		if(temp_body == myBodies[i]) {
			lives["p"+(i+1)]--;
			console.log(lives["p"+(i+1)]);
		}
	}
	console.log(temp_body.GetLinearVelocity().Length());
	console.log("you hit something!");
	console.log("impact velocity = " + temp_body.GetLinearVelocity().Length());
	if(temp_body.GetLinearVelocity().Length() > 10) {
		console.log("hit wall too hard!");
		console.log("setting damping to: " + Math.log(temp_body.GetLinearVelocity().Length()));
		isStunned = true;
		temp_body.SetLinearDamping(
			Math.log(temp_body.GetLinearVelocity().Length())
		);
	}
	console.log("isStunned = " + isStunned);			
} 
var canMove = false;
var isStunned = false;

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
	//console.log("1 - 2: " + (angle1 - angle2));
	//myBodies[playerID].SetAngularVelocity(Math.PI/2);
	if(angle1 >= Math.PI) {				
		if(angle2 >= Math.PI) {
			if(angle1 <= angle2) {
			//console.log("1");
				myBodies[playerID].SetAngularVelocity(-turning_speed)
			}else if(angle1 > angle2) {
			//console.log("2");
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}
			//console.log("angle 2 is greater than angle 1");
			canMove = false;				
		} else if(angle2 < Math.PI) {
			if(angle1 <= (angle2 + Math.PI)) {
			//console.log("1");
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 + Math.PI)) {
			//console.log("2");
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			//console.log("angle 2 is greater than angle 1");
			canMove = false;
		}
		
	}else if(angle1 < Math.PI) {
		if(angle2 >= Math.PI) {
			if(angle1 <= (angle2 - Math.PI)) {
			//console.log("1");
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}else if(angle1 > (angle2 - Math.PI)) {
			//console.log("2");
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}
			//console.log("angle 2 is greater than angle 1");
			canMove = false;				
		} else if(angle2 < Math.PI) {
			if(angle1 <= angle2) {
			//console.log("1");
				myBodies[playerID].SetAngularVelocity(-turning_speed);
			}else if(angle1 > angle2) {
			//console.log("2");
				myBodies[playerID].SetAngularVelocity(turning_speed);
			}
			//console.log("angle 2 is greater than angle 1");
			canMove = false;
		}
	}
	//console.log(Math.abs(angle2 - angle1));
	if((Math.abs(angle2 - angle1) <= 0.1) || (Math.abs(angle2 - angle1) >= 6.1)) {
		//console.log(canMove);
		myBodies[playerID].SetAngularVelocity(0);
		canMove = true;
	} else {
		//console.log(canMove);
	}
	//console.log("a1: " + angle1);	
	//console.log("a2: " + angle2);
	
}
var destroy_body = function(playerID) {
	world.DestroyBody(myBodies[playerID]);
}
		
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
		//console.log("moving");
		myBodies[playerID].ApplyImpulse(new b2Vec2((mouseX - myBodies[playerID].GetPosition().x), (mouseY - myBodies[playerID].GetPosition().y)), myBodies[playerID].GetPosition());
		
		rotate_to_mouse(playerID, mouseX, mouseY);
	} else if(isMouseDown && canMove == false) {
		//console.log("rotating");
		rotate_to_mouse(playerID, mouseX, mouseY);
	}
	var angle = myBodies[playerID].GetAngle();
	var positionX = myBodies[playerID].GetPosition().x;
	var positionY = myBodies[playerID].GetPosition().y;
		
	//console.log(ret);
	
	world.Step(1/60, 8, 3);
	
	
	world.ClearForces();
	return {positionX : positionX, positionY : positionY, angle : angle, playerID : playerID, lives : lives["p"+(playerID+1)]}	
}

module.exports.add_player = add_player;
module.exports.update = update;
module.exports.destroy_body = destroy_body;