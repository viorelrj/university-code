const canvasX = 1280
const canvasY = 720
const ELLIPSE_SIZE = 30

const vertices = {}
const adjency = {}

let distances = {}

let edgeStart
let draggedVertex
let vertexCounter
let hasDragged = false
let vertexInstances = 0

// MinCum - Minimum cummulative (median)
let minCumRow = Infinity
let minCumRowIndex

// (Center)
let minRow = Infinity
let minRowIndex

let pCenters = []
let pMedians = []


// Functionality

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
        const start = vertices[startIndex]
        for (let startIndex in adjency) {
            for (const endIndex in adjency[startIndex]) {
                const end = vertices[endIndex]
                if (collidePointLine(mouseX, mouseY, start.x, start.y, end.x, end.y, 0.5)) {
                    return { startIndex: startIndex, endIndex: endIndex }
                }
            }
        }
    }
    return null
}



// Drawing library specific functions

function setup() {
    const canvas = createCanvas(canvasX, canvasY);
    canvas.mouseReleased(handleMouseReleased)
    canvas.mousePressed(handleMousePressed)
    vertexCounter = 0
}

function draw() {
    clear()
    drawEdges()
    drawVertices()
}


// GUI drawing specific functions

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

function drawVertices() {
    textAlign(CENTER, CENTER)
    textSize(11);

    // Green - selected start point
    // Blue - is a graph median - has shortest routes to every edge
    // Red - is a graph center - has the minimum of greatest distance
    // Pink - both center and median

    for (let i in vertices) {

        fill(255)
        ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
        fill(0)
        text(i, vertices[i].x, vertices[i].y)

        //If is a pMedian
        if (pMedians.includes(int(i))) {
            fill(0, 80, 255)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(255)
            text(i, vertices[i].x, vertices[i].y)
            fill(0)
        }
        //If is a pCenter
        if (pCenters.includes(int(i))) {
            fill(255, 80, 0)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(0)
            text(i, vertices[i].x, vertices[i].y)
        }
        //If is both pMedian and pCenter
        if (pMedians.includes(int(i)) && pCenters.includes(int(i))) {
            fill(255, 80, 255)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(0)
            text(i, vertices[i].x, vertices[i].y)
        }
        //is a Center
        if (minRowIndex === int(i)) {
            fill(255, 0, 0)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(0)
            text(i, vertices[i].x, vertices[i].y)
        }
        //is a Median
        if (minCumRowIndex === int(i)) {
            fill(0, 0, 255)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(255)
            text(i, vertices[i].x, vertices[i].y)
        }
        if (vertices[i].isStartpoint) {
            fill(0, 255, 0)
            ellipse(vertices[i].x, vertices[i].y, ELLIPSE_SIZE)
            fill(0)
            text(i, vertices[i].x, vertices[i].y)
        }
    }
}

// GUI logic

function addVertex() {
    vertices[vertexCounter] = { x: mouseX, y: mouseY, isStartpoint: false }
    adjency[vertexCounter] = {}
    for (const key in adjency) {
        adjency[vertexCounter][key] = null
        adjency[key][vertexCounter] = null
    }
    // addjency[vertexCounter]
    if (edgeStart !== null && edgeStart !== undefined) {
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
    if (hoverLine !== null) {
        adjency[hoverLine.startIndex][hoverLine.endIndex] = null
        adjency[hoverLine.endIndex][hoverLine.startIndex] = null
    }
}

function handleMouseReleased() {
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

function handleMousePressed() {
    const hover = getHover()
    draggedVertex = hover
}

function mouseDragged() {
    if (draggedVertex !== null) {
        vertices[draggedVertex] = { x: mouseX, y: mouseY }
        // edgeStart = null
        // hasDragged = true
    }
}

function keyPressed() {
    const hover = getHover()

    // Debugging
    if (key === 'd') {
        console.log({ vertices: vertices, adjency: adjency, distances: distances })
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

    // find P centers
    if (key === 'c') {
        const p = int(window.prompt('How many centers?'))
        pCenter(p)
    }

    // find P medians
    if (key === 'm') {
        const p = int(window.prompt('How many medians?'))
        pMedian(p)
    }

    // If pressed spacebar
    if (keyCode === 32) {
        getCenterAndMedian()
    }
}



// Graph logic
function warshall() {
    distances = JSON.parse(JSON.stringify(adjency))

    for (let i in distances) {
        for (let k in distances) {
            if (i == k) {
                distances[i][k] = 0
            } else {
                distances[i][k] = (distances[i][k] == null) ? Infinity : distances[i][k]
            }
        }
    }

    for (let k in distances) {
        for (let i in distances) {
            for (let j in distances) {
                if (distances[i][k] + distances[k][j] < distances[i][j]) {
                    distances[i][j] = distances[i][k] + distances[k][j]
                }
            }
        }
    }
}

function getCenterAndMedian() {
    minCumRow = Infinity
    minCumRowIndex = null
    minRow = Infinity
    minRowIndex

    warshall()

    const rows = {}
    const cols = {}

    const maxRows = {}

    // Building the rows and cols lengths
    for (const rowIndex in distances) {
        for (const element in distances[rowIndex]) {
            if (rows[rowIndex] === undefined) rows[rowIndex] = 0
            if (cols[element] === undefined) cols[element] = 0
            rows[rowIndex] += distances[rowIndex][element]
            cols[element] += distances[element][rowIndex]

            if (distances[rowIndex][element] > maxRows[rowIndex] || maxRows[rowIndex] === undefined) {
                maxRows[rowIndex] = distances[rowIndex][element]
            }
        }
    }


    // Searching for minimum
    for (const key in rows) {
        if (rows[key] < minCumRow) {
            minCumRow = rows[key]
            minCumRowIndex = int(key)
        }

        if (maxRows[key] < minRow) {
            minRow = maxRows[key]
            minRowIndex = int(key)
        }
        // if (cols[key] < minCol) {
        // 	minCol = cols[key]
        // 	minColIndex = int(key)
        // }
    }
}

function pCenter(p) {
    pCenters = []
    warshall()

    // solution should be an array
    function checkSolution(solution) {
        let minDistances = []
        for (let colIndex in distances) {
            let col = []
            if (!solution.includes(colIndex)) {
                col = solution.map(sol => distances[sol][colIndex])
            }
            minDistances.push(Math.min(...col))
        }

        return Math.max(...minDistances)
    }


    // Get initial set of solutions
    let unchecked = Object.keys(vertices).map(x => int(x))

    // Populate initial solution
    while (pCenters.length < p) {
        pCenters.push(unchecked.pop())
    }

    // Try the element in solution set
    for (let variant of unchecked) {
        for (let index in pCenters) {
            let possibleSolution = JSON.parse(JSON.stringify(pCenters))
            possibleSolution[index] = variant
            if (checkSolution(possibleSolution) < checkSolution(pCenters)) {
                pCenters = possibleSolution
            }
        }
    }
}

function pMedian(p) {
    pMedians = []

    warshall()
    // solution should be an array
    function checkSolution(solution) {
        let cumulatives = []
        for (let sol of solution) {
            let currSum = 0
            for (let col in distances) {
                currSum += distances[sol][col]
            }
            cumulatives.push(currSum)
        }

        return Math.min(...cumulatives)
    }


    // Get initial set of solutions
    let unchecked = Object.keys(vertices).map(x => int(x))

    // Populate initial solution
    while (pMedians.length < p) {
        pMedians.push(unchecked.pop())
    }

    // Try the element in solution set
    for (let variant of unchecked) {
        for (let index in pMedians) {
            let possibleSolution = JSON.parse(JSON.stringify(pMedians))
            possibleSolution[index] = variant
            if (checkSolution(possibleSolution) < checkSolution(pMedians)) {
                pMedians = possibleSolution
            }
        }
    }
}