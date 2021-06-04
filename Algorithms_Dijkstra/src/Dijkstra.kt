/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 6/2/2021 18:31
 */

/**
 * Data class to hold the values of the graph. A secondary constructor was added
 * to make passing the values easier from the main method
 *
 * @vertices - The set of values we name the vertices
 * @edges - The nodes that map to a set of neighbors
 * @weights - The distance between each vertex
 */
data class Graph(
    val vertices: Set<String>,
    val edges: Map<String, Set<String>>,
    val weight: Map<Pair<String, String>, Int>
)

/**
 * This method that will create a Graph by converting a  map that contains our vertices and their corresponding
 * weights. We will break down the values in the map to the corresponding data variables in the Graph
 *
 * @wts - map that contains the pair of vertices and their corresponding weight
 * @returns - a Graph
 */
fun graphCreator(wts: Map<Pair<String,String>,Int>): Graph {

    val vertices = getVerticesValues(wts.keys.toList())


    val weights = mutableMapOf<Pair<String,String>,Int>()
    wts.forEach{
        weights.put(it.key, it.value)
        var inverse = Pair(it.key.second, it.key.first)
        weights.put(inverse, it.value)
    }

    val edges = weights.keys
        .groupBy { it.first }
        .mapValues { dedupeEdgeValues(it.value) {
                arg ->
            arg != it.key }
        }
        .withDefault { emptySet() }
    return Graph(vertices, edges, weights)
}


/**
 * This method extracting the unique values from the vertices (pair of vertices) and return them in a set
 */
fun getVerticesValues(list: List<Pair<String, String>>): Set<String> {
    return list
        .map { (a, b) -> listOf(a, b) }
        .flatten()
        .toSet()
}

/**
 * This method will dedupe the values of the list so we only have a single value for the edges. The predicate
 * (condition) will filter the values that only match our requirements.
 */
fun dedupeEdgeValues(list: List<Pair<String, String>>, condition: (String) -> Boolean): Set<String> {
    return list
        .map { (a, b) -> listOf(a, b) }
        .flatten()
        .filter(condition)
        .toSet()
}

class Dijkstra(val graph: Graph) {

    /**
     * This method will build the shortest path from a starting edge to a given final edge
     *
     * @return the Map of the short path - the question mark means nullable object
     */
    fun dijkstraPath(start: String): Map<String, String?> {
        // variable for the subset of vertices we know the true distance of
        val subset: MutableSet<String> = mutableSetOf()

        // create a variable that will map the vertices set to a max value, then
        // convert to a mutable map so we can edit it
        val delta = graph.vertices.associateWith { Int.MAX_VALUE }.toMutableMap()

        // initialize max value for the starting point to 0. You're already there
        delta[start] = 0

        // create a variable of mutable map with a generic argument and a nullable argument. This
        // will map the vertices set to a null value, then  convert to a mutable map so we can edit it
        // This tracks the last node with the shortest path
        val prev: MutableMap<String, String?> = graph.vertices.associateWith { null }.toMutableMap()

        while (subset != graph.vertices) {
            val value: String = delta
                // traverse every element in delta and only return values where we don't know
                // the distance for where all neighbor edges haven't been checked
                .filter { !subset.contains(it.key) }
                // return the smallest value or else null
                .minByOrNull { it.value }!!
                //return the smallest weighted path
                .key

            // Extract the Set values from the edges variable, then subtract the subset values from the
            // pulled edges set. Then for each value, we compare neighboring edges to determine the shortest
            // path
            graph.edges.getValue(value).minus(subset).forEach { neighbor ->
                val newPath = delta.getValue(value) + graph.weight.getValue(Pair(value, neighbor))
                if (newPath < delta.getValue(neighbor)) {
                    delta[neighbor] = newPath
                    prev[neighbor] = value
                }
            }
            subset.add(value)
        }
        return prev.toMap()
    }

    /**
     * This method will return the shortest path which based on the returned shortest values from
     * dijkstra (prev.toMap())
     *
     * @return a list of the shortest path
     */
    fun shortestPath(prevPath: Map<String, String?>, begin: String, end: String): MutableList<String>? {
        val shortestPath: MutableList<String> = mutableListOf()
        var last = prevPath[end]

        if (last == null) {
            shortestPath.add(begin)
            return shortestPath.asReversed()
        }
        shortestPath.add(end)
        while (last != null) {
            val nextEnd = prevPath[last]
            shortestPath.add(last)
            last = nextEnd
        }
        return shortestPath.asReversed()
    }
}

fun main() {

    //Test a standard map to make sure everything is working. BTW, it wasn't, but I fixed it
    val weights1 = mapOf(
        Pair("A", "B") to 2,
        Pair("A", "D") to 7,
        Pair("B", "C") to 3,
        Pair("C", "D") to 1,
        Pair("D", "E") to 5,
        )
    var start = "C"
    var end = "A"

    println("Test 1:")
    printGraph(weights1)
    runDijkstra(weights1, start, end)
    // Change the starting points to ensure we can determine the shortest path from anywhere. I'm glad I did this,
    // because this identified a HUGE gap in my code, which is why I'm submitting this so late
    start = "B"
    end = "E"
    runDijkstra(weights1, start, end)

    // I wanted to test the path to see if it would take a 0 path (like I wanted), it does! Probably not realistic
    // and if I were to use this for a game and my character just teleported somewhere, that'd be a problem for
    // animation
    val weights2 = mapOf(
        Pair("A", "B") to 0,
        Pair("A", "D") to 1,
        Pair("B", "C") to 0,
        Pair("B", "H") to 1,
        Pair("B", "I") to 0,
        Pair("C", "I") to 1,
        Pair("C", "F") to 0,
        Pair("C", "D") to 1,
        Pair("D", "E") to 0,
        Pair("D", "F") to 1,
        Pair("E", "F") to 0,
        Pair("F", "G") to 1,
        Pair("G", "I") to 0,
        Pair("G", "H") to 1,
    )
    start = "A"
    end = "I"

    println("\nTest 2:")
    printGraph(weights2)
    runDijkstra(weights2,start, end)
    //change the start point again, just to make sure I fixed the bug from test 1
    end = "E"
    start = "C"
    runDijkstra(weights2,start, end)
    end = "F"
    start = "H"
    runDijkstra(weights2,start, end)


    // Let's see the paths if everything is ascending. Did it change things? Not really, but showed how dynamic the
    // program is at finding a short patch
    val weights3 = mapOf(
        Pair("A", "B") to 8,
        Pair("A", "C") to 7,
        Pair("B", "D") to 6,
        Pair("B", "E") to 5,
        Pair("C", "D") to 4,
        Pair("D", "E") to 3,
        Pair("D", "F") to 2,
        Pair("E", "F") to 1,
    )
    start = "A"
    end = "E"

    println("\nTest 3:")
    printGraph(weights3)
    runDijkstra(weights3,start, end)
    end = "D"
    runDijkstra(weights3,start, end)
    //Still checking that start point, because I really want to make sure I fixed it!
    start = "F"
    end = "B"
    runDijkstra(weights3,start, end)
    end = "C"
    runDijkstra(weights3,start, end)

    //Let's add negative numbers! Will the code work? It did, which I'm not sure is the behaviour we want, but, the
    // shortest path is found. Granted, if this were for a game, weird stuff would happen
    val weights4 = mapOf(
        Pair("A", "B") to 16,
        Pair("A", "D") to 11,
        Pair("B", "C") to 2,
        Pair("B", "H") to 21,
        Pair("B", "I") to 10,
        Pair("C", "I") to 7,
        Pair("C", "F") to 8,
        Pair("C", "D") to 2,
        Pair("D", "E") to 5,
        Pair("D", "F") to 9,
        Pair("E", "F") to 12,
        Pair("F", "G") to -1,
        Pair("G", "I") to -3,
        Pair("G", "H") to 6,
    )
    start = "A"
    end = "E"

    println("\nTest 4:")
    printGraph(weights4)
    runDijkstra(weights4,start, end)
    end = "G"
    runDijkstra(weights4,start, end)
    // Gonna check that changing starting point again!
    start = "I"
    end = "D"
    runDijkstra(weights4,start, end)
    end = "C"
    runDijkstra(weights4,start, end)
}

fun runDijkstra(wts: Map<Pair<String,String>,Int>, begin: String, end: String) {
    val graphDij = graphCreator(wts)
    val dijkstra = Dijkstra(graphDij)

    val previousPath = dijkstra.dijkstraPath(begin)
    val shortestPath = dijkstra.shortestPath(previousPath, begin, end)

    println("The shortest path between $begin and $end is $shortestPath")
}

fun printGraph(wts: Map<Pair<String,String>,Int>) {
    println("graph {")
        wts.forEach{
            println("${it.key.first}--${it.key.second} [label = \"${it.value}\"];")
        }
    println("}")
}