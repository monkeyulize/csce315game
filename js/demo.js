var stage, 
	canvas, 
	hero, 
	img = new Image();

	
if ('ontouchstart' in document.documentElement) {
	canvas.addEventListener('touchstart', function(e) {
		handleKeyDown();
	}, false);
} else {
	document.onkeydown = handleKeyDown;
	document.onmousedown = handleKeyDown;
}

	
function init() {
	canvas = document.createElement("canvas");

	//canvas {
	//	padding-left: 0;
	//	padding-right: 0;
	//	margin-left: auto;
	//	margin-right: auto;
	//	display: block;
	//	width: 800px;
	//}
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

	canvas.width = getWidth();
	canvas.height = getHeight();
	document.body.appendChild(canvas);
	
	stage = new createjs.Stage(canvas);

	img.onload = onImageLoaded;
	img.src = 'assets/test.png';
}


function onImageLoaded(e) {
	hero = new Hero(img);
	stage.addChild(hero);
	hero.reset();
	
	createjs.Ticker.setFPS(30);
	createjs.Ticker.addEventListener("tick", tick);
}

function tick() {
	hero.tick();
	stage.update();
}


function handleKeyDown(e) {
	hero.reset();
}

init();

