const canvasX = 640
const canvasY = 640
const ELLIPSE_SIZE = 30

const vertices = {}
const adjency = {}
const distances = {}

let edgeStart
let draggedVertex
let vertexCounter
let hasDragged = false
let vertexInstances = 0


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
			for (const endIndex in adjency[startIndex]) {
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
	canvas.mouseReleased(handleMouseReleased)
	canvas.mousePressed(handleMousePressed)
	vertexCounter = 0
}


function drawEdges() {
	//If there is nothing to draw, cancel
	if (isEmpty(adjency)) {
		return 
	}

	for (const startVertex in adjency) {
		for (const endVertex in adjency) {
			if (adjency[startVertex][endVertex] !== null && endVertex < startVertex) {
				const start = vertices[startVertex]
				const end = vertices[endVertex]
				line(start.x, start.y, end.x, end.y)

				// Get what to write as the length of the edge
				const length = adjency[startVertex][endVertex]

				// Get the modification of cansaf required to draw the data correctly
				const xCenter = (start.x + end.x) / 2
				const yCenter = (start.y + end.y) / 2
				const angle = Math.atan((end.y - start.y) / (end.x - start.x)) 


				// Draw the text
				// Move origin point of the canvas to the text position
				translate(xCenter, yCenter)
				// Rotate the canvas by the set angle
				rotate(angle)
				textSize(24)
				text(length, 0, 0)
				// Get the canvas to the original state
				rotate(-angle)
				translate(-xCenter, -yCenter)
			}
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
	drawEdges()
	drawVertices()
}

function addVertex() {
	vertices[vertexCounter] = { x: mouseX, y: mouseY, isStartpoint: false }
	adjency[vertexCounter] = {}
	for (const key in adjency) {
		adjency[vertexCounter][key] = null
		adjency[key][vertexCounter] = null
	}
	// addjency[vertexCounter]
	if (edgeStart !== null && edgeStart !== undefined) {
		console.log(edgeStart)
		vertices[edgeStart].isStartpoint = false
	}
	edgeStart = null;
	vertexCounter++
	vertexInstances++
}

function removeVertex(hover) {

	delete vertices[hover]
	delete adjency[hover]
	for (const key in adjency) {
		delete adjency[key][hover]
	}

	vertexInstances--
}

function addEdge(hover) {
	const length = int(window.prompt('What is the length of the edge?'))
	adjency[edgeStart][hover] = length
	adjency[hover][edgeStart] = length

	if (edgeStart !== null) {
		vertices[edgeStart].isStartpoint = false
	}
	
	edgeStart = null
}

function removeEdge(hoverLine) {
	adjency[hoverLine.startIndex][hoverLine.endIndex] = null
	adjency[hoverLine.endIndex][hoverLine.startIndex] = null
}

function handleMouseReleased () {
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
			addEdge(hover)
		} 
		else {
			addVertex()
		}
	}
	// If right click
	else if (mouseButton === 'right') {
		// If clicked a vertex, remove it
		if (hover !== null) {
			removeVertex(hover)
		}

		if (hoverLine !== null) {
			removeEdge(hoverLine)
		}
	}
	draggedVertex = null
}

function handleMousePressed () {
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

	if (key === 'e') {
		drawEdges()
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
		buildDistancesTable()
		findMinDistance()
	}
}

function buildDistancesTable() {
	// This function Calculates the shortest distances from one point
	function minDistances(start) {
		// This function recursively minimizes the distances to each node
		// Input: prev - index of the previous vertex, curr - index of the current vertex
		function getDistance(prev, curr) {
			visited[curr]++

			if (prev === null) {
				row[curr] = 0
			} else {
				if (adjency[prev][curr] + row[prev] <= row[curr]) {
					row[curr] = adjency[prev][curr] + row[prev]
				}
			}

			if (visited !== {}) {
				for (next in adjency[curr]) {
					if (adjency[curr][next] !== null && visited[next] < vertexInstances) {
						getDistance(curr, next)
					}
				}
			}
		}
		
		// Select a row to calcuate distances from
		const row = Object.assign({}, adjency[start]);
		const visited = Object.assign({}, adjency[start]);

		// Build initial distances with infinity as the initial value
		for (const key in row) {
			row[key] = Infinity
			visited[key] = 0
		}
		row[start] = 0	

		// Recursively minimize the distances
		getDistance(null, start)
		// Save the row into the distances table
		distances[start] = Object.assign({}, row);
	}


	// Build row of distances for every vertex
	for (key in vertices) {
		minDistances(int(key))
	}
}

function findMinDistance() {
	const rows = {}
	for (const rowIndex in distances) {
		for (const element in distances[rowIndex]) {
			if (rows[rowIndex] === undefined) {
				rows[rowIndex] = 0
			}
			rows[rowIndex] += distances[rowIndex][element]
		}
	}
	let minRow = Infinity
	let minRowIndex
	for (const key in rows) {
		if (rows[key] < minRow) {
			minRow = rows[key]
			minRowIndex = int(key)
		}
	}
	console.log(minRow, minRowIndex)
}
