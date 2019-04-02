const canvasX = 640
const canvasY = 640
const ELLIPSE_SIZE = 30
const ARROW_LENGTH = 50
const POINT = {
	speed: 8,
	size: 6,
}

let vertices = {}
let adjency = {}
let distances = {}

let edgeStart
let draggedVertex
let vertexCounter
let hasDragged = false

// Check if an instance of object has no keys
function isEmpty(obj) {
	for (var key in obj) {
		if (obj.hasOwnProperty(key))
			return false;
	}
	return true;
}

// Get the index of the hovered vertex
function getHover() {
	for (i in vertices) {
		if (collidePointEllipse(mouseX, mouseY, vertices[i].x, vertices[i].y, ELLIPSE_SIZE, ELLIPSE_SIZE))
			return int(i)
	}
	return null
}

// Get the index of the hovered edge
function getHoverLine() {
	if (!isEmpty(adjency)) {
		for (let startIndex in adjency) {
			const start = vertices[startIndex]
			for (let endVertex of adjency[startIndex]) {
				const endIndex = endVertex.index
				const end = vertices[endIndex]
				if (collidePointLine(mouseX, mouseY, start.x, start.y, end.x, end.y, 0.5)) {
					return {startIndex: startIndex, endIndex: endIndex}
				}
			}
		}
	}
	return null
}

function setup () {
	const canvas = createCanvas(canvasX, canvasY);
	vertexCounter = 0
}

function drawConnections() {
	//If there is nothing to draw, cancel
	if (isEmpty(adjency)) {
		return 
	}

	for ( let startIndex in adjency ) {
		const start = vertices[startIndex]
		for (let connection of adjency[startIndex]) {
			const end = vertices[connection.index]

			const dx = end.x - start.x
			const dy = end.y - start.y
			const slope = dy / dx
			const distance = Math.floor(Math.sqrt(pow(dx, 2) + pow(dy, 2)))

			//Draw the connection line
			fill(0)
			line(start.x, start.y, end.x, end.y)

			//Draw the length of line
			textAlign(CENTER, CENTER)
			textSize(20);
			fill(0)
			translate(start.x + dx / 2, start.y + dy / 2)
			rotate(Math.atan(slope))
			text(distance, 20, 20)
			rotate(-Math.atan(slope))
			translate(-(start.x + dx / 2), -(start.y + dy / 2))
		}
	}
}

// Conection poins are defined as the points that run across
// the edges and indicate the direction of the flow
function drawConnectionPoints() {
	// If there is nothing to draw, return
	if (isEmpty(adjency)) {
		return
	}

	for (let startIndex in adjency) {
		const start = vertices[startIndex]
		for (let connection of adjency[startIndex]) {
			const end = vertices[connection.index]
			const dx = end.x - start.x
			const dy = end.y - start.y

			connection.point.x += dx / Math.hypot(end.x - start.x, end.y, start.y) * POINT.speed
			connection.point.y += dy / Math.hypot(end.x - start.x, end.y, start.y) * POINT.speed

			if (end.x > start.x && connection.point.x > end.x || end.x < start.x && connection.point.x < end.x) {
				connection.point.x = start.x
				connection.point.y = start.y
			}


			fill(255, 116, 116)
			ellipse(connection.point.x, connection.point.y, POINT.size)
		}
	}
}

function drawVertices () {
	textAlign(CENTER, CENTER)
	textSize(11);
	for (let i in vertices) {
		if (vertices[i].isStartpoint) {
			fill(0, 255, 0)
			ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
			fill(0)
			text(i, vertices[i].x, vertices[i].y)
		} else {
			fill(255)
			ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
			fill(0)
			text(i, vertices[i].x, vertices[i].y)
		}
	}
}

function draw () {
	clear()
	drawConnections()
	drawConnectionPoints()
	drawVertices()
}


function mouseReleased () {
	const hover = getHover()
	const hoverLine = getHoverLine()

	//left mouse click
	if (mouseButton === 'left') {
		// If clicked something and there is no memory of clicking other vertex before
		if (hover !== null && edgeStart === null) {
			if (hasDragged === false) {
				edgeStart = hover
				vertices[edgeStart].isStartpoint = true
			}
			hasDragged = false
		}
		// If clicked something and clicked another vertex before
		else if (hover !== null && edgeStart !== null && hover !== edgeStart) {
			// Add a line to adjency Data structure
			if (adjency[edgeStart]) {
				if (!adjency[edgeStart].includes(hover)) {
					adjency[edgeStart].push({ index: int(hover), point: {x: vertices[edgeStart].x, y: vertices[edgeStart].y} })
				}
			} else {

				adjency[edgeStart] = [{ index: int(hover), point: { x: vertices[edgeStart].x, y: vertices[edgeStart].y } }]
			}
			// Reset memory of previously clicked vertex
			vertices[edgeStart].isStartpoint = false
			edgeStart = null
		} 
		else {
			//Add vertex
			vertices[vertexCounter] = { x: mouseX, y: mouseY, isStartpoint: false}
			distances[vertexCounter++] = Infinity
			edgeStart = null;
		}
	}
	// If right click
	else if (mouseButton === 'right') {
		// If clicked a vertex, remove it
		if (edgeStart !== null) {
			vertices[edgeStart].isStartpoint = false
			edgeStart = null
		}
		if (hover !== null) {
			delete adjency[hover]
			delete distances[hover]
			for (let vertex in adjency) {
				adjency[vertex] = adjency[vertex].filter((item) => item.index !== hover)
			}
			delete vertices[hover]
		}
		// If clicked a line, remove it
		if (hoverLine !== null) {
			adjency[hoverLine.startIndex] = adjency[hoverLine.startIndex].filter((item) => item !== hoverLine.endIndex)
		}
	}
	draggedVertex = null
}

function mousePressed () {
	const hover = getHover()
	draggedVertex = hover
}

function mouseDragged () {
	if (draggedVertex !== null) {
		vertices[draggedVertex] = { x: mouseX, y: mouseY }
		// edgeStart = null
		// hasDragged = true
	}
}

function keyPressed () {
	const hover = getHover()

	// Debugging
	if (key === 'd') {
		console.log({ vertices: vertices, adjency: adjency, distances: distances})
	}

	// Reset vertex focus
	if (key === 'r') {
		if (edgeStart !== null) {
			for (vertex in vertices) {
				vertex.isStartpoint = false
			}
			vertices[edgeStart].isStartpoint = false
			edgeStart = null
		}
	}

	// If pressed spacebar
	if (keyCode === 32) {
		function hasUnvisited () {
			for ( const vertex in distances ) {
				if (distances[vertex] === Infinity) {
					return true
				}
			}
			return false
		}

		function checkVertex(prev, curr) {
			if (!hasUnvisited()) {
				return
			}
			if (prev === null) {
				distances[curr] = 0

				for (next of adjency[curr]) {
					checkVertex(curr, next.index)
				}
			} else {
				const distance = Math.floor(Math.sqrt(Math.pow(vertices[curr].x - vertices[prev].x, 2) + Math.pow(vertices[curr].y - vertices[prev].y, 2)))
				if (distances[prev] + distance < distances[curr]) {
					distances[curr] = distances[prev] + distance
				}

				if (adjency[curr]) {
					for (next of adjency[curr]) {
						(curr !== next) ? checkVertex(curr, next) : null
					}
				}

			}
		}

		for (vertex in distances) {
			distances[vertex] = Infinity
		}

		checkVertex(null, hover)
	}
	
}