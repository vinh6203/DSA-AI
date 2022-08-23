# from tests import *

# Fall 2012 6.034 Lab 2: Search
#
# Your answers for the true and false questions will be in the following form.  
# Your answers will look like one of the two below:
#ANSWER1 = True
#ANSWER1 = False

# 1: True or false - Hill Climbing search is guaranteed to find a solution
#    if there is a solution
ANSWER1 = True

# 2: True or false - Best-first search will give an optimal search result
#    (shortest path length).
#    (If you don't know what we mean by best-first search, refer to
#     http://courses.csail.mit.edu/6.034f/ai3/ch4.pdf (page 13 of the pdf).)
ANSWER2 = False

# 3: True or false - Best-first search and hill climbing make use of
#    heuristic values of nodes.
ANSWER3 = True

# 4: True or false - A* uses an extended-nodes set.
ANSWER4 = True

# 5: True or false - Breadth first search is guaranteed to return a path
#    with the shortest number of nodes.
ANSWER5 = True

# 6: True or false - The regular branch and bound uses heuristic values
#    to speed up the search for an optimal path.
ANSWER6 = False

# Import the Graph data structure from 'search.py'
# Refer to search.py for documentation

# from lab2.tests import bfs_1_testanswer
from search import Graph

## Optional Warm-up: BFS and DFS
# If you implement these, the offline tester will test them.
# If you don't, it won't.
# The online tester will not test them.

def bfs(graph: Graph, start_node, goal_node): # OK!
    # for i in graph.nodes:
    #     print(i)
    #     for j in graph.get_connected_nodes(i):
    #         print(j, end= " ")
    #     print("")
    # return

    q = [start_node]
    visited = set()

    while len(q) != 0:
        current_path = q.pop(0)
        current_node = current_path[len(current_path) - 1]
        visited.add(current_node)
        
        if current_node == goal_node:
            return list(current_path)
        
        for node in graph.get_connected_nodes(current_node):
            if node not in visited:
               q.append(current_path + node)
               visited.add(node)
        
    return False
    raise NotImplementedError

## Once you have completed the breadth-first search,
## this part should be very simple to complete.
def dfs(graph: Graph, start_node, goal_node):

    # for i in graph.nodes:
    #     print(i)
    #     for j in graph.get_connected_nodes(i):
    #         print(j, end= " ")
    #     print("")
    # return
    
    q = [start_node]
    visited = set()

    while len(q) != 0:
        current_path = q.pop()
        current_node = current_path[len(current_path) - 1]
        visited.add(current_node)
        
        if current_node == goal_node:
            return list(current_path)
        
        for node in graph.get_connected_nodes(current_node):
            if node not in visited:
               q.insert(0, current_path + node)
               visited.add(node)

    return False
    raise NotImplementedError


## Now we're going to add some heuristics into the search.  
## Remember that hill-climbing is a modified version of depth-first search.
## Search direction should be towards lower heuristic values to the goal.

def hill_sort(graph: Graph, goalNode, paths):    # helper function sort list of paths by heuristic value of lastest elements
                                                # in each path in list paths
    return sorted(paths, key=lambda path: graph.get_heuristic(path[len(path) - 1], goalNode))


def hill_climbing(graph: Graph, start_node, goal_node): # OK !

    q = [start_node]  # q ~ agenda

    while len(q) != 0:

        current_path = q.pop(0)
        current_node = current_path[len(current_path) - 1]
        new_paths = []

        if current_node == goal_node:
            return list(current_path)

        for node in graph.get_connected_nodes(current_node):
            if node not in current_path:
                new_paths.append(current_path + node)
        
        new_paths = hill_sort(graph, goal_node, new_paths)

        for path in new_paths[::-1]:
            q.insert(0, path)
            
    return False
    raise NotImplementedError

## Now we're going to implement beam search, a variation on BFS
## that caps the amount of memory used to store paths.  Remember,
## we maintain only k candidate paths of length n in our agenda at any time.
## The k top candidates are to be determined using the 
## graph get_heuristic function, with lower values being better values.

def beam_sort(graph: Graph, goalNode, paths):   # helper function sort list of paths by heuristic value of lastest elements
                                                # in each path in list paths
    return sorted(paths, key=lambda path: graph.get_heuristic(path[len(path) - 1], goalNode))

def beam_search(graph: Graph, start_node, goal_node, beam_width): # beam_width = k   ## OK !

    q = [start_node]  # q ~ agenda

    while len(q) != 0:
        current_path = q.pop(0)
        current_node = current_path[len(current_path) - 1]
        new_paths = []

        if current_node == goal_node:
            return list(current_path)
        
        for node in graph.get_connected_nodes(current_node):
            if node not in current_path:
                new_paths.append(current_path + node)
        
        new_paths = beam_sort(graph, goal_node, new_paths)

        for path in new_paths[beam_width - len(q) - 1::-1]:
            q.append(path)

    return False
    raise NotImplementedError

## Now we're going to try optimal search.  The previous searches haven't
## used edge distances in the calculation.

## This function takes in a graph and a path, and returns
## the sum of edge lengths along the path -- the total distance in the path.
def path_length(graph: Graph, path):
    distance = 0
    for i in range(0, len(path) - 1):
        distance += (graph.get_edge(path[i], path[i+1])).length        
    return distance
    raise NotImplementedError

def branch_and_bound_sort(paths):                   # helper function sort list of paths by path length elements
    return sorted(paths, key=lambda path: path[1])  # in each path in list paths  (path = [path, length])

def branch_and_bound(graph: Graph, start_node, goal_node):  # OK!
    
    q = [ [start_node, 0] ]   # q ~ agenda    [path, length]

    while len(q) != 0:
        current_path, current_length = q.pop(0)
        current_node = current_path[len(current_path) - 1]
        new_paths = []

        if current_node == goal_node:
            return list(current_path)

        for neighbor_node in graph.get_connected_nodes(current_node):
            if neighbor_node not in current_path:
                new_paths.append(  [current_path + neighbor_node,
                                    current_length + graph.get_edge(current_node, neighbor_node).length])
        
        for path in new_paths:
            q.append(path)
            
        q = branch_and_bound_sort(q)
    return False
    raise NotImplementedError


def a_star_sort(paths):                             # helper function sort list of paths by (path length + heuristic value)
    return sorted(paths, key=lambda path: path[1])  # of elements in list paths  (path = [path, length + heuristic value])


def a_star(graph: Graph, start_node, goal_node):  # OK !

    q = [ [start_node, 0 + graph.get_heuristic(start_node, goal_node)] ]   # q ~ agenda    [path, length + heuristic value]
    visited = set()

    while len(q) != 0:
        current_path, current_length = q.pop(0)
        current_node = current_path[len(current_path) - 1]
        visited.add(current_node)
        new_paths = []

        if current_node == goal_node:
            return list(current_path)

        for neighbor_node in graph.get_connected_nodes(current_node):
            if neighbor_node not in current_path:
                new_paths.append( [current_path + neighbor_node,
                                   current_length + graph.get_edge(current_node, neighbor_node).length
                                 + graph.get_heuristic(neighbor_node, goal_node) - graph.get_heuristic(current_node, goal_node)] )
                visited.add(neighbor_node)
        
        for path in new_paths:
            q.append(path)
            
        q = a_star_sort(q)
        #print(q)
    return False
    raise NotImplementedError


## It's useful to determine if a graph has a consistent and admissible
## heuristic.  You've seen graphs with heuristics that are
## admissible, but not consistent.  Have you seen any graphs that are
## consistent, but not admissible?

def is_admissible(graph: Graph, goal):  # OK !
    for node in graph.nodes:
        if graph.get_heuristic(node, goal) > path_length(graph, a_star(graph, node, goal)):
            return False
    return True
    raise NotImplementedError

def is_consistent(graph: Graph, goal):  # OK !
    for node in graph.nodes:
        for neighbor in graph.get_connected_nodes(node):
            abs_diff = abs(graph.get_heuristic(node, goal) - graph.get_heuristic(neighbor, goal))
            if abs_diff > graph.get_edge(node, neighbor).length:
                return False
    return True
    raise NotImplementedError

HOW_MANY_HOURS_THIS_PSET_TOOK = '69'
WHAT_I_FOUND_INTERESTING = '69'
WHAT_I_FOUND_BORING = '69'

SAQG = Graph(edgesdict=[
    {'NAME': 'SA', 'LENGTH': 1, 'NODE1': 'S', 'NODE2': 'A'},
    {'NAME': 'SQ', 'LENGTH': 1, 'NODE1': 'S', 'NODE2': 'Q'},
    {'NAME': 'AG', 'LENGTH': 1, 'NODE1': 'A', 'NODE2': 'G'},
    {'NAME': 'QG', 'LENGTH': 1, 'NODE1': 'Q', 'NODE2': 'G'},
    {'NAME': 'SG', 'LENGTH': 1, 'NODE1': 'S', 'NODE2': 'G'}])
NEWGRAPH1 = Graph(edgesdict=[ 
        { 'NAME': 'e1',  'LENGTH':  6, 'NODE1': 'S', 'NODE2': 'A' },
        { 'NAME': 'e2',  'LENGTH':  4, 'NODE1': 'A', 'NODE2': 'B' },
        { 'NAME': 'e3',  'LENGTH':  7, 'NODE1': 'B', 'NODE2': 'F' },
        { 'NAME': 'e4',  'LENGTH':  6, 'NODE1': 'C', 'NODE2': 'D' },
        { 'NAME': 'e5',  'LENGTH':  3, 'NODE1': 'C', 'NODE2': 'A' },
        { 'NAME': 'e6',  'LENGTH':  7, 'NODE1': 'E', 'NODE2': 'D' },
        { 'NAME': 'e7',  'LENGTH':  6, 'NODE1': 'D', 'NODE2': 'H' },
        { 'NAME': 'e8',  'LENGTH':  2, 'NODE1': 'S', 'NODE2': 'C' },
        { 'NAME': 'e9',  'LENGTH':  2, 'NODE1': 'B', 'NODE2': 'D' },
        { 'NAME': 'e10', 'LENGTH': 25, 'NODE1': 'E', 'NODE2': 'G' },
        { 'NAME': 'e11', 'LENGTH':  5, 'NODE1': 'E', 'NODE2': 'C' } ],
                  heuristic={"G":{'S': 11,
                                  'A': 9,
                                  'B': 6,
                                  'C': 12,
                                  'D': 8,
                                  'E': 15,
                                  'F': 1,
                                  'H': 2},
                             "H":{'S': 11,
                                  'A': 9,
                                  'B': 6,
                                  'D': 12,
                                  'E': 8,
                                  'F': 15,
                                  'G': 14},
                             'A':{'S':5, # admissible
                                  "B":1, # h(d) > h(b)+c(d->b) ...  6 > 1 + 2
                                  "C":3,
                                  "D":6,
                                  "E":8,
                                  "F":11,
                                  "G":33,
                                  "H":12},
                             'C':{"S":2, # consistent
                                  "A":3,
                                  "B":7,
                                  "D":6,
                                  "E":5,
                                  "F":14,
                                  "G":30,
                                  "H":12},
                             "D":{"D":3}, # dumb
                             "E":{} # empty
                             })
NEWGRAPH2 = Graph(edgesdict=
                  [ { 'NAME': 'e1', 'LENGTH': 2, 'NODE1': 'D', 'NODE2': 'F' },
                    { 'NAME': 'e2', 'LENGTH': 4, 'NODE1': 'C', 'NODE2': 'E' },
                    { 'NAME': 'e3', 'LENGTH': 2, 'NODE1': 'S', 'NODE2': 'B' },
                    { 'NAME': 'e4', 'LENGTH': 5, 'NODE1': 'S', 'NODE2': 'C' },
                    { 'NAME': 'e5', 'LENGTH': 4, 'NODE1': 'S', 'NODE2': 'A' },
                    { 'NAME': 'e6', 'LENGTH': 8, 'NODE1': 'F', 'NODE2': 'G' },
                    { 'NAME': 'e7', 'LENGTH': 5, 'NODE1': 'D', 'NODE2': 'C' },
                    { 'NAME': 'e8', 'LENGTH': 6, 'NODE1': 'D', 'NODE2': 'H' } ],
                  heuristic={"G":{'S': 9,
                                  'A': 1,
                                  'B': 2,
                                  'C': 3,
                                  'D': 6,
                                  'E': 5,
                                  'F': 15,
                                  'H': 10}})
NEWGRAPH3 = Graph(nodes=["S"])
NEWGRAPH4 = Graph(nodes=["S","A", "B", "C", "D", "E", "F", "H", "J", "K",
            "L", "T" ],
                 edgesdict = [{ 'NAME': 'eSA', 'LENGTH': 2, 'NODE1': 'S', 'NODE2': 'A' },
              { 'NAME': 'eSB', 'LENGTH': 10, 'NODE1': 'S', 'NODE2':'B' },
              { 'NAME': 'eBC', 'LENGTH': 5, 'NODE1': 'B', 'NODE2':'C' },
              { 'NAME': 'eBF', 'LENGTH': 2, 'NODE1': 'B', 'NODE2':'F' },
              { 'NAME': 'eCE', 'LENGTH': 5, 'NODE1': 'C', 'NODE2':'E' },
              { 'NAME': 'eCJ', 'LENGTH': 12, 'NODE1': 'C', 'NODE2':'J' },
              { 'NAME': 'eFH', 'LENGTH': 8, 'NODE1': 'F', 'NODE2':'H' },
              { 'NAME': 'eHD', 'LENGTH': 3, 'NODE1': 'H', 'NODE2':'D' },
              { 'NAME': 'eHK', 'LENGTH': 5, 'NODE1': 'H', 'NODE2':'K' },
              { 'NAME': 'eKJ', 'LENGTH': 1, 'NODE1': 'K', 'NODE2':'J' },
              { 'NAME': 'eJL', 'LENGTH': 4, 'NODE1': 'J', 'NODE2':'L' },
              { 'NAME': 'eKT', 'LENGTH': 7, 'NODE1': 'K', 'NODE2':'T' },
              { 'NAME': 'eLT', 'LENGTH': 5, 'NODE1': 'L', 'NODE2':'T' },
              ],
                 heuristic={"T":{'S': 10,
                                 'A': 6,
                                 'B': 5,
                                 'C': 2,
                                 'D': 5,
                                 'E': 1,
                                 'F': 100,
                                 'H': 2,
                                 'J': 3,
                                 'K': 100,
                                 'L': 4,
                                 'T': 0,}})
AGRAPH = Graph(nodes = ['S', 'A', 'B', 'C', 'G'],
               edgesdict = [{'NAME': 'eSA', 'LENGTH': 3, 'NODE1': 'S', 'NODE2': 'A'},
                            {'NAME': 'eSB', 'LENGTH': 1, 'NODE1': 'S', 'NODE2': 'B'},
                            {'NAME': 'eAB', 'LENGTH': 1, 'NODE1': 'A', 'NODE2': 'B'},
                            {'NAME': 'eAC', 'LENGTH': 1, 'NODE1': 'A', 'NODE2': 'C'},
                            {'NAME': 'eCG', 'LENGTH': 10, 'NODE1': 'C', 'NODE2': 'G'}],
               heuristic = {'G':{'S': 12,
                                 'A': 9,
                                 'B': 12,
                                 'C': 8,
                                 'G': 0}})
