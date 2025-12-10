# SDSU MAPS

Goal:
Create an interactive SDSU campus navigation program that helps new students locate important buildings on campus. Students can either click a building on the map or type its name, and the program will guide them to their destination.


What the Program Does
Accepts building names as typed input or mouse clicks
Converts the name to uppercase and searches using a Hash Table
Uses a Graph shortest path algorithm to compute the fastest walking route
Displays a visual campus map and animated movement to the chosen location
Allows students to change destinations at any time simply by choosing a new building

Data Structures be used in My SDSU MAPS Program

List (vector),  in UI.cpp, Building.h
Stores all buildings and their positions
Used for drawing, iterating through buildings, and walking animation

Queue inside Graph.cpp (used by BFS)
Required for shortest path search between buildings
BFS returns the fastest walking route
Explores graph one “layer” at a time
Uses a Queue (FIFO: First-In, First-Out) to manage visits

Hash Table (unordered_map) in Graph.h + BuildingTree.h
Maps building name, ID (for typed searches)
Maps course code, building
Enables fast lookup when user types “LOVE”

Tree (Binary Search Tree)  in BuildingTree.h/.cpp
Stores building names alphabetically
Used for structured searching & quick comparisons
finds the matching building ID
sends that ID to the Graph for shortest path

Graph (Adjacency List)  in Graph.h/.cpp
Nodes = campus buildings
Edges = walking paths between buildings
BFS generates the shortest route for the ball animation

Bonus
Searching Algorithm = Searching for buildings via Binary Search Tree + Hash lookup for fast access
Sorting Algorithm = Buildings are sorted alphabetically in UI
Other Algorithms = BFS shortest path algorithm
GUI / Visualization = Full SFML GUI with: clickable buildings, animated moving ball, real map, text input, labels, path visualization

![Screen Shot 2025-12-10 at 12.38.05 PM.png](../../Desktop/Screen%20Shot%202025-12-10%20at%2012.38.05%20PM.png)