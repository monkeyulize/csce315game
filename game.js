var Box2D = require('./Box2d.js');
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
bodyDef.type = b2Body.b2_dynamicBody;
bodyDef.position.Set(4, 8);
bodyDef.userData = 'BOX';
	
var myFixture = new b2FixtureDef;
myFixture.shape = new b2CircleShape(3);
myFixture.density = 1;
myFixture.friction = 0.5;
myFixture.restitution = 0.5;
	
var init = function(players) {
	for(i = 0; i < players.length; i++) {
		myBodies[i] = world.CreateBody(bodyDef);			
	}
	for(i = 0; i < myBodies.length; i++) {
		myBodies[i].SetPositionAndAngle(new b2Vec2(i*10 + 10,10),0);
		myBodies[i].SetLinearVelocity(new b2Vec2(0, 0));
		myBodies[i].SetFixedRotation(false);
		myBodies[i].SetAngularVelocity(0);
		myBodies[i].CreateFixture(myFixture);
	}
}

	
		

var world = new b2World(new b2Vec2(0, 0), false);

var listener = new Box2D.Dynamics.b2ContactListener;
world.SetContactListener(listener);
listener.BeginContact = function(contact) {
	console.log("you hit something!");
	console.log("impact velocity = " + myBodies[playerID].GetLinearVelocity().Length());
	if(myBodies[playerID].GetLinearVelocity().Length() > 10) {
		console.log("hit wall too hard!");
		console.log("setting damping to: " + Math.log(myBodies[playerID].GetLinearVelocity().Length())/2);
		console.log("My Lives : " + myLives);
		isStunned = true;
		myBodies[playerID].SetLinearDamping(Math.log(myBodies[playerID].GetLinearVelocity().Length())/2);
		myLives= myLives - 1;
	}
	console.log("isStunned = " + isStunned);			
}






var myLives = 3;

/*
//attempting wall_1
var Wall_one = new b2FixtureDef;
Wall_one.density = .5;
Wall_one.friction = 0.4;
Wall_one.restitution = 0.2;
var bodyDef = new b2BodyDef;
bodyDef.type = b2Body.b2_staticBody;
Wall_one.shape = new b2PolygonShape;
Wall_one.shape.SetAsBox(canvas.width/2,4);
bodyDef.position.Set(canvas.width/2, 0);
world.CreateBody(bodyDef).CreateFixture(Wall_one);
bodyDef.position.Set(canvas.width/2, (canvas.height/10));
world.CreateBody(bodyDef).CreateFixture(Wall_one);
Wall_one.shape.SetAsBox(2,canvas.height/2);
bodyDef.position.Set(0, canvas.height/2);
world.CreateBody(bodyDef).CreateFixture(Wall_one);
bodyDef.position.Set(canvas.width/10, canvas.height/2);
world.CreateBody(bodyDef).CreateFixture(Wall_one);
*/

var debugDraw = new b2DebugDraw();
debugDraw.SetSprite(document.getElementById ("canvas").getContext("2d"));
debugDraw.SetDrawScale(10);
debugDraw.SetFillAlpha(0.5); //define transparency
debugDraw.SetLineThickness(1.0); //defines thickness of lines or boundaries
debugDraw.SetFlags(b2DebugDraw.e_shapeBit | b2DebugDraw.e_jointBit);
world.SetDebugDraw(debugDraw);

window.setInterval(update, 1000/60);

var canMove = false;
var isStunned = false;

function rotate_to_mouse(playerID) {
	var pos = new b2Vec2(myBodies[playerID].GetPosition().x, myBodies[playerID].GetPosition().y);
	var a1 = mouseY - pos.y;
	var b1 = mouseX - pos.x;
	//circle.x = pos.x;
	//circle.y = pos.y;
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
	
var update = function(playerID, mouseX, mouseY) {

	if(myBodies[playerID].GetLinearVelocity().Length() < 0.8 && myBodies[playerID].GetLinearDamping() != 0) {
		myBodies[playerID].SetLinearVelocity(new b2Vec2(0, 0));
		console.log("resetting damping to 0");
		myBodies[playerID].SetLinearDamping(0);
		isStunned = false;
		console.log("isStunned = " + canMove);
	}
	
	if(!isMouseDown) {
		myBodies[playerID].SetAngularVelocity(0);
	}		
	if(isMouseDown && canMove == true && isStunned == false) {
		myBodies[playerID].ApplyForce(new b2Vec2((mouseX - myBodies[playerID].GetPosition().x)*10, (mouseY - myBodies[playerID].GetPosition().y)*10), myBodies[playerID].GetPosition());
		
		rotate_to_mouse(playerID);
	} else if(isMouseDown && canMove == false) {
		rotate_to_mouse(playerID);
	}
	
	world.Step(1/60, 10, 10);
	world.DrawDebugData();			
	//stage.update();
	world.ClearForces();
	
}

module.exports.init = init;
module.exports.update = update;