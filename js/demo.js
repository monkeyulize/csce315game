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