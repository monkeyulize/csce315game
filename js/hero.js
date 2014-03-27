(function (window) {
	function Hero(image) {
		this.initialize(image);
	}	
	Hero.prototype = new createjs.Bitmap();
	
	Hero.prototype.Bitmap_initialize = Hero.prototype.initialize;
	
	Hero.prototype.initialize = function (image) {
		this.Bitmap_initialize(image);
		this.name = 'Hero';
		this.snapToPixel = true;
	}
	
	Hero.prototype.tick = function() {
		this.y += 1;
	}
	
	Hero.prototype.reset = function() {
		this.y = 0;
	}
	
	window.Hero = Hero;
})(window);