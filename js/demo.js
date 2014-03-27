function init() {
	canvas = document.createElement("canvas");
	canvas {
		padding-left: 0;
		padding-right: 0;
		margin-left: auto;
		margin-right: auto;
		display: block;
		width: 800px;
	}
	document.body.appendChild(canvas);
	var stage = new createjs.Stage(canvas);
	var circle = new createjs.Shape();
	circle.graphics.beginFill("blue").drawCircle(0, 50, 50);
	circle.x = 100;
	circle.y = 100;
	stage.addChild(circle);
	
	stage.on("stagemousemove", function(evt) {
		circle.x = evt.stageX;
		circle.y = evt.stageY;
		stage.update();
	})
	stage.update();

}
