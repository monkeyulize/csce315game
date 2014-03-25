var circle, stage, cont_circle;
function init() {
	canvas = document.createElement("canvas");
	canvas.width = window.innerWidth-15;
	canvas.height = window.innerHeight-100;
	document.body.appendChild(canvas);
	stage = new createjs.Stage(canvas);
	stage.enableDOMEvents(true);
	circle = new createjs.Shape();
	circle.graphics.beginFill("blue").drawCircle(0, 0, 50);
	circle.x = 100;
	circle.y = 100;
	stage.addChild(circle);
	cont_circle = new createjs.Shape();
	cont_circle.graphics.beginFill("red").drawCircle(0, 0, 50);
	cont_circle.x = canvas.width;
	cont_circle.y = canvas.height;
	stage.addChild(cont_circle);
	stage.on("stagemousemove",function(evt) {
			circle.x = evt.stageX;
			circle.y = evt.stageY;
			cont_circle.x = canvas.width - evt.stageX;
			cont_circle.y = canvas.height - evt.stageY;
			stage.update();
	})
	createjs.Ticker.on("tick", tick);

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
		}


