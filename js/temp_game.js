function init() {
		canvas.style="background-color:#00CCCC;"
		//canvas.width = window.innerWidth;
		//canvas.height = window.innerHeight;
		canvas.width = 4000;
		canvas.height = 2000;	
		
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
		
		var world = new b2World(new b2Vec2(0, 0), false);

		var listener = new Box2D.Dynamics.b2ContactListener;
		var scheduledForDestruction = Array();
		var deletingNum = 0;
			
		world.SetContactListener(listener);
		listener.BeginContact = function(contact) {
			console.log(contact.GetFixtureA().GetShape().m_type);
			console.log(contact.GetFixtureB().GetShape());
			//console.log(contact.GetFixtureB().GetBody().GetUserData());
			console.log("you hit something!");
			console.log("impact velocity = " + myBody.GetLinearVelocity().Length());
			
			
			if(contact.GetFixtureA().GetShape().m_type == 1 &&  contact.GetFixtureB().GetShape().m_type==0 && contact.GetFixtureA().GetBody().GetUserData() != "WALL" && contact.GetFixtureB().GetBody().GetUserData() != "WALL")
			{
				console.log("hit other player");
				console.log("setting damping to: " + Math.log(myBody.GetLinearVelocity().Length())/2);
				contact.GetFixtureB().GetBody().SetUserData((parseInt(contact.GetFixtureB().GetBody().GetUserData())-1).toString());
				console.log("My Lives : " + contact.GetFixtureA().GetBody().GetUserData());
				console.log("Their Lives : " + contact.GetFixtureB().GetBody().GetUserData());
				isStunned = true;
				myBody.SetLinearDamping(Math.log(myBody.GetLinearVelocity().Length())/2);
				
				//fixture A's deletion upon no lives remaining
				if (parseInt(contact.GetFixtureA().GetBody().GetUserData()) < 1) 
				{
					//add body to array for bodies scheduled to be removed
					scheduledForDestruction.push(contact.GetFixtureA().GetBody());
					deletingNum++;
				}
				
				//fixture B's deletion upon no lives remaining
				if (parseInt(contact.GetFixtureB().GetBody().GetUserData()) < 1) 
				{
					//add bodyB to array for bodies scheduled to be removed
					scheduledForDestruction.push(contact.GetFixtureB().GetBody());
					deletingNum++;
				}
			}
			
			//hit a wall too hard
			if(myBody.GetLinearVelocity().Length() > 25 && contact.GetFixtureB().GetBody().GetUserData() == "WALL") {
				console.log("hit wall too hard!");
				console.log("setting damping to: " + Math.log(myBody.GetLinearVelocity().Length())/2);
				console.log("My Lives : " + contact.GetFixtureA().GetBody().GetUserData());
				console.log("Their Lives : " + contact.GetFixtureB().GetBody().GetUserData());
				isStunned = true;
				myBody.SetLinearDamping(Math.log(myBody.GetLinearVelocity().Length())/2);
			}
			console.log("isStunned = " + isStunned);
			
		}
		
		//interval to check for players deleting
		window.setInterval(destroyPlayer, 1000/90); 
		
		// deleting players function
		function destroyPlayer() 
		{
			//delete bodies
			for(var i = 0; i < deletingNum; i++)
			{
				world.DestroyBody(scheduledForDestruction[i]);
				scheduledForDestruction[i] = null;
			}
			
			//reset variables
			scheduledForRemoval = Array();
			deletingNum = 0;
		}
		
		var bodyDef = new b2BodyDef;
		bodyDef.type = b2Body.b2_dynamicBody;
		bodyDef.position.Set(4, 8);
		bodyDef.userData = '3';
		
		
		var myBody = world.CreateBody(bodyDef);
		
		myBody.SetPositionAndAngle(new b2Vec2(10,10),0);
		myBody.SetLinearVelocity(new b2Vec2(0, 0));
		myBody.SetFixedRotation(false);
		myBody.SetAngularVelocity(0);
		
		
		var myFixture = new b2FixtureDef;
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
		myHorn.isSensor = false;
		
		var myLives = 3;
		
		myBody.CreateFixture(myFixture);
		myBody.CreateFixture(myHorn);
		

		//Crack at pseudoplayer
		bodyDef.userData = '3';
		var yourBody = world.CreateBody(bodyDef);
		
		yourBody.SetPositionAndAngle(new b2Vec2(100,100),0);
		yourBody.SetLinearVelocity(new b2Vec2(-2, -2));
		yourBody.SetFixedRotation(false);
		yourBody.SetAngularVelocity(0);
		
		
		var yourFixture = new b2FixtureDef;
		yourFixture.shape = new b2CircleShape(3);
		yourFixture.density = 1;
		yourFixture.friction = 0.5;
		yourFixture.restitution = 0.5;
		
		yourBody.CreateFixture(yourFixture);
		
		//attempting wall_1
		
		var Wall_one = new b2FixtureDef;
		Wall_one.density = .5;
		Wall_one.friction = 0.4;
		Wall_one.restitution = 0.2;
		var bodyDef = new b2BodyDef;
		bodyDef.userData = 'WALL';
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
		
		var debugDraw = new b2DebugDraw();
		debugDraw.SetSprite(document.getElementById ("canvas").getContext("2d"));
		debugDraw.SetDrawScale(10);
		debugDraw.SetFillAlpha(.95); //define transparency
		debugDraw.SetLineThickness(1.0); //defines thickness of lines or boundaries
		debugDraw.SetFlags(b2DebugDraw.e_shapeBit | b2DebugDraw.e_jointBit);
		world.SetDebugDraw(debugDraw);
		
		window.setInterval(update, 1000/60);
		
		var mouseX, mouseY, mousePVec, isMouseDown, selectedBody, mouseJoint;
		var canvasPosition = getElementPosition(document.getElementById("canvas")); 
		
		document.addEventListener("mousedown", function(e) {
			isMouseDown = true;
			handleMouseMove(e);
			document.addEventListener("mousemove", handleMouseMove, true);
		}, true);
		
		document.addEventListener("mouseup", function() {
			document.removeEventListener("mousemove", handleMouseMove, true);
			isMouseDown = false;
			mouseX = undefined;
			mouseY = undefined;
		}, true);
		
		function handleMouseMove(e) {
			mouseX = (e.clientX - canvasPosition.x) / 10;
			mouseY = (e.clientY - canvasPosition.y) / 10;
		};
		function getElementPosition(element) {
			var elem=element, tagname="", x=0, y=0;
			while((typeof(elem) == "object") && (typeof(elem.tagName) != "undefined")) {
				y += elem.offsetTop;
				x += elem.offsetLeft;
				tagname = elem.tagName.toUpperCase();
				if(tagname == "BODY")
					elem=0;
				if(typeof(elem) == "object") {
					if(typeof(elem.offsetParent) == "object") {
						elem = elem.offsetParent;
					}
				}
			}
			return {x: x, y: y};
		}
		
		var canMove = false;
		var isStunned = false;
		
		function rotate_to_mouse() {
			var pos = new b2Vec2(myBody.GetPosition().x, myBody.GetPosition().y);
			var a1 = mouseY - pos.y;
			var b1 = mouseX - pos.x;
			//circle.x = pos.x;
			//circle.y = pos.y;
			var angle1_act = Math.atan2(a1, b1);
			var angle1;
			
			var turning_speed = Math.PI*3;
			
			var angle2 = myBody.GetAngle();

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
			//myBody.SetAngularVelocity(Math.PI/2);
			if(angle1 >= Math.PI) {				
				if(angle2 >= Math.PI) {
					if(angle1 <= angle2) {
					//console.log("1");
						myBody.SetAngularVelocity(-turning_speed)
					}else if(angle1 > angle2) {
					//console.log("2");
						myBody.SetAngularVelocity(turning_speed);
					}
					//console.log("angle 2 is greater than angle 1");
					canMove = false;				
				} else if(angle2 < Math.PI) {
					if(angle1 <= (angle2 + Math.PI)) {
					//console.log("1");
						myBody.SetAngularVelocity(turning_speed);
					}else if(angle1 > (angle2 + Math.PI)) {
					//console.log("2");
						myBody.SetAngularVelocity(-turning_speed);
					}
					//console.log("angle 2 is greater than angle 1");
					canMove = false;
				}
				

			}else if(angle1 < Math.PI) {
				if(angle2 >= Math.PI) {
					if(angle1 <= (angle2 - Math.PI)) {
					//console.log("1");
						myBody.SetAngularVelocity(turning_speed);
					}else if(angle1 > (angle2 - Math.PI)) {
					//console.log("2");
						myBody.SetAngularVelocity(-turning_speed);
					}
					//console.log("angle 2 is greater than angle 1");
					canMove = false;				
				} else if(angle2 < Math.PI) {
					if(angle1 <= angle2) {
					//console.log("1");
						myBody.SetAngularVelocity(-turning_speed);
					}else if(angle1 > angle2) {
					//console.log("2");
						myBody.SetAngularVelocity(turning_speed);
					}
					//console.log("angle 2 is greater than angle 1");
					canMove = false;
				}
			}
			//console.log(Math.abs(angle2 - angle1));
			if((Math.abs(angle2 - angle1) <= 0.1) || (Math.abs(angle2 - angle1) >= 6.1)) {
				//console.log(canMove);
				myBody.SetAngularVelocity(0);
				canMove = true;
			} else {
				//console.log(canMove);
			}
			//console.log("a1: " + angle1);	
			//console.log("a2: " + angle2);
			
		}

		function update() {
		
			if(myBody.GetLinearVelocity().Length() < 0.8 && myBody.GetLinearDamping() != 0) {
				myBody.SetLinearVelocity(new b2Vec2(0, 0));
				console.log("resetting damping to 0");
				myBody.SetLinearDamping(0);
				isStunned = false;
				console.log("isStunned = " + canMove);
			}
			
			if(!isMouseDown) {
				myBody.SetAngularVelocity(0);
			}		
			if(isMouseDown && canMove == true && isStunned == false) {
				myBody.ApplyForce(new b2Vec2((mouseX - myBody.GetPosition().x)*10, (mouseY - myBody.GetPosition().y)*10), myBody.GetPosition());
				
				rotate_to_mouse();
			} else if(isMouseDown && canMove == false) {
				rotate_to_mouse();
			}
			
			world.Step(1/60, 10, 10);
			world.DrawDebugData();			
			//stage.update();
			world.ClearForces();
			
		}
}
//init();
	