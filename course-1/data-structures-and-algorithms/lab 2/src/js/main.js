const CANVAS_CONFIG = {
	x: 1280,
	y: 720,
}

class Button {
	constructor(x, y, text, action) {
		this.x = x;
		this.y = y;
		this.text = text;

		this.height = 30;
		this.width = 200;
		this.brds = 4;

		this.click = action;
	}

	show() {
		textAlign(CENTER, CENTER);
		textSize(15);
		fill(255);
		rect(this.x, this.y, this.width, this.height, this.brds);
		fill(0);
		text(this.text, this.x + this.width / 2, this.y + this.height / 2);
	}

	checkHover() {
		return collidePointRect(mouseX, mouseY, this.x, this.y, this.width, this.height);
	}
}

const board = new Board();

function setup() {
	const canvas = createCanvas(CANVAS_CONFIG.x, CANVAS_CONFIG.y);
}

function draw() {
	clear();
	board.drawEdges();
	board.drawVertices();
	showButtons();
}

function mouseReleased() {
	if (board.dragging) {
		board.dragging = false;
		return
	}

	const hoveredVertex = board.getHoveredVertex();

	if (mouseButton === 'left') {
		if (pMedianBTN.checkHover()) {
			pMedianBTN.click();
			return;
		}

		if (pCenterBTN.checkHover()) {
			pCenterBTN.click();
			return;
		}

		if (centerAndMedianBTN.checkHover()) {
			centerAndMedianBTN.click();
			return;
		}

		board.addVertex(mouseX, mouseY);

	} else if (mouseButton == 'right') {
		const hoveredEdge = board.getHoveredEdge();
		const hoveredVertex = board.getHoveredVertex();

		if (hoveredVertex) {
			if (hoveredVertex.id === board.vertexClicked) {
				board.removeVertex();
			} else {
				board.addEdge(hoveredVertex.id, board.vertexClicked);
			}
		}

		if (hoveredEdge) {
			board.removeEdge(hoveredEdge.startIndex, hoveredEdge.endIndex)
		}
	}

	board.vertexClicked = null;
}

function mousePressed() {
	const vertex = board.getHoveredVertex();
	if (vertex) board.vertexClicked = vertex.id;
}

function mouseDragged() {
	if (mouseButton === 'left') {
		board.dragVertex();
	}
}


let pMedianBTN = new Button(20, 30, 'Find P Centers', board.getPCenter.bind(board)); 
let pCenterBTN = new Button(20, 80, 'Find P Medians', board.getPMedian.bind(board));
let centerAndMedianBTN = new Button(20, 130, 'Find Center and Median', board.getCenterAndMedian.bind(board));

function showButtons() {
	pMedianBTN.show()
	pCenterBTN.show()
	centerAndMedianBTN.show()
}