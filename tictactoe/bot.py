from board import *
from util import *
from cmath import inf
import time

# This is custom
# This also need to be synchronized with win_condition in util.py
def heuristic_function(board: tic_tac_toe_board):
    score = 0
    for chain in board.get_chains(player_x_id):
        length = len(chain)
        if length == 1:
            score += 1
        elif length == 2:
            score += 10
        elif length == 3:
            score += 100
        elif length == 4:
            score += 1000
    
    for chain in board.get_chains(player_o_id):
        length = len(chain)
        if length == 1:
            score -= 1
        elif length == 2:
            score -= 10
        elif length == 3:
            score -= 100
        elif length == 4:
            score -= 1000
    return score


def alpha_beta(board: tic_tac_toe_board, max_player=True, depth=3, alpha=-inf, beta=inf, terminal_function=heuristic_function):
    
    if depth == 0: # reach the leaf
        return [], terminal_function(board)   # move, point
    
    best_action = None, None   #move, point    # move: tuple([row, col])

    if max_player:
        for move, new_board in board.get_next_move(board.get_current_player_turn()):
            child_node_val = alpha_beta(new_board, False, depth - 1, alpha, beta)

            if best_action[1] == None or best_action[1] < child_node_val[1]:
                best_action = (move, child_node_val[1])
                if best_action[1] != None:
                    alpha = max(alpha, best_action[1])
                    if best_action[1] >= beta:
                        return best_action
    else:
        for move, new_board in board.get_next_move(board.get_current_player_turn()):
            child_node_val = alpha_beta(new_board, True, depth - 1, alpha, beta)

            if best_action[1] == None or best_action[1] > child_node_val[1]:
                best_action = (move, child_node_val[1])
                if best_action[1] != None:
                    beta = min(beta, best_action[1])
                    if best_action[1] <= alpha:
                        return best_action
    return best_action


def play_game(turn_limit=turn_limit_util, current_turn=current_turn_util):
    board = tic_tac_toe_board()

    while turn_limit > 0 and not board._is_game_over():

        action = alpha_beta(board)
        move = action[0]
        board.update_board(move[0], move[1], current_turn)
        print("Player", convert_turn_to_icon[current_turn], "chooses", move)
        board.print_board()
        current_turn = -current_turn 

        end_game = board._is_game_over()
        turn_limit -= 1
        if end_game != False:
            if end_game == player_x_id:
                print("Player %s wins" % player_x_icon)
                board.print_board()
                break
            if end_game == player_o_id:
                print("Player %s wins" % player_o_icon)
                board.print_board()
                break
        if turn_limit == 0:
            print("Draw")
            board.print_board()
        if allowed_delay:
            time.sleep(delay)