function init() {
	canvas = document.createElement("canvas");
	canvas.width = 500;
	canvas.height = 250;
	document.body.appendChild(canvas);
	var stage = new createjs.Stage(canvas);
	var circle = new createjs.Shape();
	circle.graphics.beginFill("blue").drawCircle(0, 0, 50);
	circle.x = 100;
	circle.y = 100;
	stage.addChild(circle);
	stage.update();

}

Ticker.setFPS(30);
Ticker.addListener(tick);
function tick(e) {
	stage.update();
}

