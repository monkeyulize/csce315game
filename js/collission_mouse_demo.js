var circle, stage, cont_circle;

function init() {
	canvas = document.createElement("canvas");
	canvas.width = window.innerWidth-15;
	canvas.height = window.innerHeight-100;
	document.body.appendChild(canvas);
	stage = new createjs.Stage(canvas);
	stage.enableDOMEvents(true);
	
	back = stage.addChild(new createjs.Shape());
	back.graphics.beginFill("green").drawRect(0,0,window.innerWidth-15,window.innerHeight-100);
			back.x = 0;
			back.y = 0;
	stage.addChild(back);
	
	circle = new createjs.Shape();
	circle.graphics.beginFill("blue").drawCircle(0, 0, 50);
	circle.graphics.beginStroke("black");
		circle.graphics.moveTo(circle.x, circle.y).lineTo(circle.x-50, circle.y).lineTo(circle.x, circle.y+100).lineTo(circle.x+50, circle.y).lineTo(circle.x, circle.y);
		circle.x = canvas.width/4;
		circle.y = canvas.height/2;
		
		
	stage.addChild(circle);
	
	cont_circle = new createjs.Shape();
	cont_circle.graphics.beginFill("red").drawCircle(0, 0, 50);
		cont_circle.x = 3*canvas.width/4;
		cont_circle.y = canvas.height/2;
		
	stage.addChild(cont_circle);
	
	
	stage.on("stagemousemove",function(evt) {
			var mouse_x = evt.stageX;
			var mouse_y = evt.stageY;
			circle.x += (mouse_x-circle.x)/100;
			circle.y += (mouse_y-circle.y)/100;
			if(mouse_x>circle.x)
				circle.rotation = (Math.atan((mouse_y-circle.y)/(mouse_x-circle.x)))*57.2957795-90;
			if(mouse_x<circle.x)
				circle.rotation = -(Math.atan((mouse_y-circle.y)/(circle.x-mouse_x)))*57.2957795+90;	
				
			cont_circle.x += (mouse_x-cont_circle.x)/100;
			cont_circle.y += (mouse_y-cont_circle.y)/100;
			stage.update();
	})
	createjs.Ticker.on("tick", tick);
	var socket = io.connect('http://compute.cse.tamu.edu:11111');
		
}

function tick(event) {
			var pt = circle.localToLocal(0,0,cont_circle);
			var cpt = cont_circle.localToLocal(0,0,circle);
			circle.alpha=.3;
			cont_circle.alpha=.3;
			if (cont_circle.hitTest(pt.x, pt.y)) {
				circle.alpha = 1;
				cont_circle.alpha = 1;
			}
			if (circle.hitTest(cpt.x, cpt.y)) {
				circle.alpha = 1;
				cont_circle.alpha = 1;
			}
			stage.update(event);
			socket.on('coords', function (data) {
			console.log(data);
			socket.emit('i am here');
		});
		}

init();
