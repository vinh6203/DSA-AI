from classify import *
import math

##
## CSP portion of lab 4.
##
from csp import BinaryConstraint, CSP, CSPState, Variable,\
    basic_constraint_checker, solve_csp_problem

# Implement basic forward checking on the CSPState see csp.py
def forward_checking(state, verbose=False):
    # Before running Forward checking we must ensure
    # that constraints are okay for this state.
    basic = basic_constraint_checker(state, verbose)
    if not basic:
        return False

    # Add your forward checking logic here.


    # state: CSPState
    # constraint: BinaryConstraint
    # current_variable, neighbor_variable: Variable
    # look for other method in csp.py
    current_variable = state.get_current_variable()
    if current_variable is not None:
        
        neighbor_constraints = state.get_constraints_by_name(current_variable.get_name())
        for constraint in neighbor_constraints:
            # current_variable have binary constraint with neighbor_variable
            neighbor_variable = state.get_variable_by_name(constraint.get_variable_j_name())

            for neighbor_value in neighbor_variable.get_domain():

                if not constraint.check(state,value_i=current_variable.get_assigned_value(), value_j=neighbor_value):
                    neighbor_variable.reduce_domain(neighbor_value)
                
                if neighbor_variable.domain_size() == 0:
                    return False
    
    return True

    raise NotImplementedError

# Now Implement forward checking + (constraint) propagation through
# singleton domains.
def forward_checking_prop_singleton(state, verbose=False):
    # Run forward checking first.
    fc_checker = forward_checking(state, verbose)
    if not fc_checker:
        return False

    # Add your propagate singleton logic here.


    # state: CSPState
    # constraint: BinaryConstraint
    # current_variable, neighbor_variable: Variable
    # look for other method in csp.py
    queue = [variable for variable in state.get_all_variables() 
                        if not variable.is_assigned() and variable.domain_size() == 1]
    visited = set()
    
    while queue: # ~ while len(queue) != 0:
        current_variable = queue.pop()
        visited.add(current_variable)

        neighbor_constraints = state.get_constraints_by_name(current_variable.get_name())
        for constraint in neighbor_constraints:
            # current_variable have binary constraint with neighbor_variable
            neighbor_variable = state.get_variable_by_name(constraint.get_variable_j_name())

            for neighbor_value in neighbor_variable.get_domain():

                if not constraint.check(state,value_i=current_variable.get_domain()[0], value_j=neighbor_value):
                    neighbor_variable.reduce_domain(neighbor_value)
                
                if neighbor_variable.domain_size() == 0:
                    return False
            
            queue.extend([variable for variable in state.get_all_variables() 
                            if variable not in visited and \
                            not variable.is_assigned() and \
                            variable.domain_size() == 1])
    return True
    raise NotImplementedError

## The code here are for the tester
## Do not change.
from moose_csp import moose_csp_problem
from map_coloring_csp import map_coloring_csp_problem

def csp_solver_tree(problem, checker):
    problem_func = globals()[problem]
    checker_func = globals()[checker]
    answer, search_tree = problem_func().solve(checker_func)
    return search_tree.tree_to_string(search_tree)

##
## CODE for the learning portion of lab 4.
##

### Data sets for the lab
## You will be classifying data from these sets.
senate_people = read_congress_data('S110.ord')
senate_votes = read_vote_data('S110desc.csv')

house_people = read_congress_data('H110.ord')
house_votes = read_vote_data('H110desc.csv')

last_senate_people = read_congress_data('S109.ord')
last_senate_votes = read_vote_data('S109desc.csv')


### Part 1: Nearest Neighbors
## An example of evaluating a nearest-neighbors classifier.
senate_group1, senate_group2 = crosscheck_groups(senate_people)
#evaluate(nearest_neighbors(hamming_distance, 1), senate_group1, senate_group2, verbose=1)

## Write the euclidean_distance function.
## This function should take two lists of integers and
## find the Euclidean distance between them.
## See 'hamming_distance()' in classify.py for an example that
## computes Hamming distances.

def euclidean_distance(list1, list2):

    assert isinstance(list1, list)
    assert isinstance(list2, list)

    if len(list1) == len(list2):
       return math.sqrt(sum([(l1 - l2)**2 for l1, l2 in zip(list1, list2)]))
    
    # if 2 list have different length
    distance = 0
    i, j = 0, 0
    while i < len(list1) and j < len(list2):
        distance += (list1[i] - list2[j])**2
        i += 1
        j += 1
    while i < len(list1):
        distance += list1[i]**2
        i += 1
    while j < len(list2):
        distance += list2[j]**2
        j += 1
    return math.sqrt(distance)

    # this is not the right solution!
    return hamming_distance(list1, list2)

#Once you have implemented euclidean_distance, you can check the results:
#evaluate(nearest_neighbors(euclidean_distance, 1), senate_group1, senate_group2, verbose=True)

## By changing the parameters you used, you can get a classifier factory that
## deals better with independents. Make a classifier that makes at most 3
## errors on the Senate.

my_classifier = nearest_neighbors(euclidean_distance, k=5)
#evaluate(my_classifier, senate_group1, senate_group2, verbose=1)

### Part 2: ID Trees
#print CongressIDTree(senate_people, senate_votes, homogeneous_disorder)

## Now write an information_disorder function to replace homogeneous_disorder,
## which should lead to simpler trees.

def information_disorder(yes, no):
    #yes, no = list of politician either Republican or Democrat that vote yes or no
    #print(isinstance(yes, list), isinstance(no, list))
    info_disorder_score = 0.0
    total_sample_handled_by_test = len(yes) + len(no)

    for table in [yes, no]: #branches in test
        number_of_sample_in_branches = len(table)
        republican, democrat = 0, 0
        for politician in table:
            if politician == 'Republican':
                republican += 1
            else:
                democrat += 1
        #if republican or democrat is 0 then this branch has 0 info_disorder_score (derived from math)
        if republican*democrat != 0:
            a = republican/number_of_sample_in_branches #republican ratio in current branches
            b = democrat/number_of_sample_in_branches #democrat ratio in current branches
            info_disorder_score += (number_of_sample_in_branches/total_sample_handled_by_test)*( - a*(math.log2(a)) - b*(math.log2(b)) )
    
    return info_disorder_score
    return homogeneous_disorder(yes, no)

#print(CongressIDTree(senate_people, senate_votes, information_disorder))
#evaluate(idtree_maker(senate_votes, homogeneous_disorder), senate_group1, senate_group2)

## Now try it on the House of Representatives. However, do it over a data set
## that only includes the most recent n votes, to show that it is possible to
## classify politicians without ludicrous amounts of information.

def limited_house_classifier(house_people, house_votes, n, verbose = False):
    house_limited, house_limited_votes = limit_votes(house_people,
    house_votes, n)
    house_limited_group1, house_limited_group2 = crosscheck_groups(house_limited)

    if verbose:
        print ("ID tree for first group:")
        print (CongressIDTree(house_limited_group1, house_limited_votes,
                             information_disorder))
        print ("")
        print ("ID tree for second group:")
        print (CongressIDTree(house_limited_group2, house_limited_votes,
                             information_disorder))
        print ("")
        
    return evaluate(idtree_maker(house_limited_votes, information_disorder),
                    house_limited_group1, house_limited_group2)

                                   
## Find a value of n that classifies at least 430 representatives correctly.
## Hint: It's not 10.
N_1 = 44
rep_classified = limited_house_classifier(house_people, house_votes, N_1, verbose=False)
#print(rep_classified) #answer is >= 430

## Find a value of n that classifies at least 90 senators correctly.
N_2 = 67
senator_classified = limited_house_classifier(senate_people, senate_votes, N_2)
#print(senator_classified) #answer is >= 90

## Now, find a value of n that classifies at least 95 of last year's senators correctly.
N_3 = 23
old_senator_classified = limited_house_classifier(last_senate_people, last_senate_votes, N_3)
print(old_senator_classified) #answer is >= 95

## The standard survey questions.
HOW_MANY_HOURS_THIS_PSET_TOOK = ""
WHAT_I_FOUND_INTERESTING = ""
WHAT_I_FOUND_BORING = ""


## This function is used by the tester, please don't modify it!
def eval_test(eval_fn, group1, group2, verbose = 0):
    """ Find eval_fn in globals(), then execute evaluate() on it """
    # Only allow known-safe eval_fn's
    if eval_fn in [ 'my_classifier' ]:
        return evaluate(globals()[eval_fn], group1, group2, verbose)
    else:
        raise Exception ("Error: Tester tried to use an invalid evaluation function: '%s'" % eval_fn)

 #[('1', 'Mc'), ('2', 'M'), ('3', 'O'), ('4', 'B'), ('5', 'Y'), ('6', 'P')]
