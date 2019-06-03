// Check if an instance of object has no keys
function isEmpty(obj) {
    for (var key in obj) {
        if (obj.hasOwnProperty(key))
            return false;
    }
    return true;
}



class Vertex {
    constructor(x, y, id) {
        this.x = x;
        this.y = y;
        this.size = 30;
        this.id = id;
        this.isMedian = false;
        this.isCenter = false;
    }

    move(x, y) {
        this.x = x;
        this.y = y;
    }

    show() {
        textAlign(CENTER, CENTER);
        textSize(11);

        if (this.isCenter && this.isMedian) {
            fill(255, 0, 255)
        } else if (this.isCenter) {
            fill(255, 0, 0)
        } else if (this.isMedian) {
            fill(0, 0, 255)
        } else {
            fill(255);
        }

        ellipse(this.x, this.y, this.size);
        fill(0);
        text(this.id, this.x, this.y);
    }

    isHovered(x, y) {
        return collidePointEllipse(x, y, this.x, this.y, this.size, this.size)
    }
}
 
class Board {
    constructor () {
        this.adjency = {};
        this.vertices = {};

        this.pCenters = [];
        this.pMedians = [];
        // this.distances = {};

        this.counter = 0;
        this.dragging = false;
        this.vertexClicked = null;
    }







    drawVertices() {
        for (let index in this.vertices) {
            this.vertices[index].show();
        }
    }

    getHoveredVertex(){
        return Object.values(this.vertices).filter(vertex => vertex.isHovered(mouseX, mouseY)).pop();
    }

    addVertex(x, y) {
        // Don't add a vertex, if have dragged a vertex
        if (this.vertexClicked != null) return;
        // Don't add a vertex, if mouse hovers a vertex
        if (this.getHoveredVertex()) return;

        this.vertices[this.counter] = new Vertex(x, y, this.counter);
        this.adjency[this.counter] = {}
        for (const key in this.adjency) {
            this.adjency[this.counter][key] = null
            this.adjency[key][this.counter] = null
        }

        this.counter++;
    }

    dragVertex() {
        if (this.vertexClicked !== null) {
            this.vertices[this.vertexClicked].move(mouseX, mouseY);

            for (const otherVertex in this.adjency[this.vertexClicked]) {

            }
        }

        this.updateEdgeLengths()
    }

    removeVertex() {
        const hoveredIndex = this.getHoveredVertex().id
        delete this.vertices[hoveredIndex];

        delete this.adjency[hoveredIndex];
        for (const key in this.adjency) {
            delete this.adjency[key][hoveredIndex]
        }
    }




    getHoveredEdge() {
        if (!isEmpty(this.adjency)) {
            for (const startIndex in this.adjency) {
                for (const endIndex in this.adjency[startIndex]) {
                    const end = this.vertices[endIndex]
                    const start = this.vertices[startIndex]
                    if (collidePointLine(mouseX, mouseY, start.x, start.y, end.x, end.y, 0.5)) {
                        return { startIndex: startIndex, endIndex: endIndex }
                    }
                }
            }
        }
        return null
    }

    updateEdgeLengths() {
        for (const start in this.adjency) {
            for (const end in this.adjency) {
                const startVertex = this.vertices[start];
                const endVertex = this.vertices[end];

                if (this.adjency[start][end] !== null) {
                    this.adjency[start][end] = sqrt(sq(endVertex.x - startVertex.x) + sq(endVertex.y - startVertex.y))
                }
            }
        }
    }

    drawEdges() {
        if (isEmpty(this.adjency)) return;

        for (const startVertex in this.adjency) {
            for (const endVertex in this.adjency) {
                if (this.adjency[startVertex][endVertex] !== null && endVertex < startVertex) {
                    const start = this.vertices[startVertex]
                    const end = this.vertices[endVertex]
                    line(start.x, start.y, end.x, end.y)

                    // Get what to write as the length of the edge
                    const length = floor(this.adjency[startVertex][endVertex])

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

    addEdge(start, end) {
        if (start === null || end === null) return;
        
        const startVertex = this.vertices[start]
        const endVertex = this.vertices[end];

        this.adjency[start][end] = 1;
        this.adjency[end][start] = 1;

        this.updateEdgeLengths();
    }

    removeEdge(startIndex, endIndex) {
        if (this.adjency[startIndex] && this.adjency[endIndex]){
            this.adjency[startIndex][endIndex] = null
            this.adjency[endIndex][startIndex] = null
        }
    }





    resetCenters() {
        for (let key in this.vertices) {
            this.vertices[key].isCenter = false;
        }
    }

    resetMedians(){
        for (let key in this.vertices) {
            this.vertices[key].isMedian = false;
        }
    }

    warshall() {
        let distances = JSON.parse(JSON.stringify(this.adjency))

        for (let i in distances) {
            for ( let k in distances) {
                if (i == k) {
                    distances[i][k] == 0;
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

        return distances;
    }

    getPMedian() {
        const p = int(window.prompt('How many medians?'))
        if (p > this.vertices.length) return;

        this.resetMedians();

        let pMedians = []

        let distances = this.warshall()
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
        let unchecked = Object.keys(this.vertices).map(x => int(x))

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

        for (let index of pMedians) {
            this.vertices[index].isMedian = true
        }
    }

    getPCenter() {
        const p = int(window.prompt('How many centers?'))
        if (p > this.vertices.length) return;
        
        this.resetCenters();


        let pCenters = []
        let distances = this.warshall()

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
        let unchecked = Object.keys(this.vertices).map(x => int(x))

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

        for (let index of pCenters) {
            this.vertices[index].isCenter = true;
        }
    }

    getCenterAndMedian() {
        this.resetCenters();
        this.resetMedians();

        let minCumRow = Infinity
        let minCumRowIndex = null
        let minRow = Infinity
        let minRowIndex = null


        let distances = this.warshall()

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
        }

        this.vertices[minRowIndex].isCenter = true;
        this.vertices[minCumRowIndex].isMedian = true;
    }
}
