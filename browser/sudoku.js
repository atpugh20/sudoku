const cvs = document.getElementById("cvs");
const ctx = cvs.getContext('2d');
const cW = 600; const cH = 600;
const FPS = 30;

function setup() {
	console.log("Setup");
	cvs.style.width = `${cW}px`;
	cvs.style.height = `${cH}px`;
}

function clear_canvas() {
	ctx.clearRect(0, 0, cW, cH);
	ctx.fillStyle = "black";
	ctx.fillRect(0, 0, cW, cH);
}

function draw() {	
	console.log("Draw");
	clear_canvas(ctx);
}

function main() {
	setup();
	//setInterval(draw, FPS / 1000);
}

window.onload = main();
