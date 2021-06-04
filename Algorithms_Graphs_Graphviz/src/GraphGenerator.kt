import java.io.File
import java.lang.Exception

/**
 * Author: Alicia Garcia
 * Version: 1.0
 * Date: 5/26/2021 20:37
 */

/**
 * Main method for generating the graphs from the files entered
 */
fun main() {
    var file: String = "adj4.txt"
    val graphG = GraphGen()

    // Fill a 2D matrix variable with the file values
    var matrix: List<List<String>> = graphG.readFile(file)
    val nodeList = graphG.nodeGenerator(matrix)

    val relationships = graphG.relationGenerator(matrix)
    val finalRelationship = relationships.toMutableList()

    val typeG = graphG.graphType(finalRelationship)

    graphG.printGraph(typeG, finalRelationship, nodeList)
}

/**
 * This is a data class that accepts two values to indicate our fromNode mapping to the toNode
 */
data class Relationship(val fromNode: String, val toNode: String) {
    /**
     * This method returns the inverse Relationship to be used for comparison
     */
    fun inverse(): Relationship {
        return Relationship(toNode, fromNode)
    }
}

/**
 *  This class generates our graph relationships so we can print the correct value and model the graph with graphviz
 */
class GraphGen {

    /**
     *  This will read the file and populate a 2D list to create our matrix
     */
    fun readFile(fileName: String): List<List<String>> {
        //Declaring a constant variable to hold my 2D List
        val matrix: MutableList<List<String>> = mutableListOf()

        File(fileName).forEachLine {
            // split the line for each column in the matrix and fill a variable
            val listStr = it.split("\t")
            // add the values of listStr to our 2D list
            matrix.add(listStr)
        }
        return matrix;
    }

    /**
     * This will create a List of nodes for generating a baseline node set
     */
    fun nodeGenerator(matrix: List<List<String>>): List<String> {
        var row = 0
        var col = 0
        val ascii = 97
        var nodeList: MutableList<String> = mutableListOf()

        matrix.forEachIndexed { i, r ->
            val colVal = i + ascii
            nodeList.add(colVal.toChar().toString())
            row++
            r.forEach {
                col++
            }
        }
        if (row == 0) {
            throw Exception("ERROR: Empty file found! Invalid input!")
        }
        if ( col / row != row ) {
            throw Exception("ERROR: Non-symmetrical matrix found!")
        } else {
            return nodeList
        }
    }

    /**
     *  This will generate a relations between the rows and columns of the matrix, as well as assign ASCII values to
     *  the rows and columns for better representation in the graph. A relationships object is returned
     */
    fun relationGenerator(matrix: List<List<String>>): List<Relationship> {
        val completeRelationships: MutableList<Relationship> = mutableListOf()
        val ascii = 97

        // Double nested for loop to traverse the matrix and populate the valid relationships (1)
        matrix.forEachIndexed { i, row ->
            row.forEachIndexed { j, col ->
                if (col == "1") {
                    val rowVal = i + ascii
                    val colVal = j + ascii
                    val relation = Relationship(rowVal.toChar().toString(), colVal.toChar().toString())
                    completeRelationships.add(relation)
                }
            }
        }
        return completeRelationships
    }

    /**
     *  This will determine the type of graph we will be printing, graph or digraph, then create the final relation
     *  set so we can correctly represent the graph or digraph.
     */
    fun graphType(fullRelation: MutableList<Relationship>): Boolean {
        //Relation map for determine if the graph is directed or not
        val relationSet = mutableSetOf<Relationship>()
        var gType = false
        var duplicates = 0

        fullRelation.forEach { map ->
            // Add the relation to the map if it doesn't exist and create an empty set. Then add the values to the set
            if (relationSet.contains(map) || relationSet.contains(map.inverse())) {
                duplicates++
            } else {
                relationSet.add(map)
            }
        }
        if (duplicates == fullRelation.size / 2) {
            fullRelation.clear()
            fullRelation.addAll(relationSet.toList())
            return true
        } else {
            return gType
        }
    }

    /**
     *  This will print the graph based on the type that is associated with the relation. If the relation is empty, a
     *  base set of Nodes is printed so we can show the "0" value graphs.
     */
    fun printGraph(gType: Boolean, relation: List<Relationship>, baseNodes: List<String>) {
        File("graphFile.dot").printWriter().use { out ->
            val delim: String
            if (!gType) {
                out.println("digraph {")
                delim = "->"
            } else {
                out.println("graph {")
                delim = "--"
            }
            // print the base nodes created
            baseNodes.forEach { node ->
                out.println("${node};")
            }
            // print the relationships from the matrix
            relation.forEach { relate ->
                out.println("${relate.fromNode} $delim ${relate.toNode};")
            }
            out.println("}")
        }
    }
}

