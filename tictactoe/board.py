from util import *
from copy import deepcopy # Not referenced copy

class tic_tac_toe_board(object):
    
    def __init__(self) -> None:
        # Board constructor
        self.board = list([0]*board_width for _ in range(board_height))
        self.current_player_turn = current_turn_util

    def get_cell(self, row, col):
        # Get the id# of the player owning the token in the specified cell.
        # Return 0 if it is unclaimed.
        return self.board[row][col]

    def get_other_player_id(self, player_id):
        # player_id is either 1 or -1
        return -player_id

    def get_current_player_turn(self):
        # player turn is their id
        return self.current_player_turn

    def update_board(self, row, col, player_id) -> None:
        # Update board if a player make move in (row, col)
        if player_id not in [player_x_id, player_o_id] or row*col < 0 or row > board_height or col > board_width:
            raise IndexError("Move out of range or player_id is not allowed, player_id: %i (1 or -1)" % player_id)

        self.board[row][col] = player_id

    def generate_board(self, row, col, player_id):
        # Generate board used in alpha-beta algorithm
        if player_id not in [player_x_id, player_o_id] or row*col < 0 or row > board_height or col > board_width:
            raise IndexError("Move out of range or player_id is not allowed, player_id: %i (1 or -1)" % player_id)      
        temp_board = temporary_board(self.board)
        temp_board.get_next_board(row, col, player_id)
        return temp_board

    def get_next_move(self, player_id):
        # generate all legal moves and board if choose that move
        for row in range(board_height):
            for col in range(board_width):
                if self.get_cell(row, col) == 0:
                    yield ((row, col), self.generate_board(row, col, player_id))

    def _contig_vector_cells(self, row, col, direction):  # This function is copied from MIT 6.034 lab3
        # Starting in the specified cell and going a step of direction = (row_step, col_step),
        # count how many consecutive cells are owned by the same player as the starting cell.
        retVal = []
        player_id = self.get_cell(row, col)

        while 0 <= row < board_height and 0 <= col < board_width and player_id == self.get_cell(row, col):
            retVal.append((row, col))
            row += direction[0]
            col += direction[1]

        return retVal[1:]

    def _chain_sets_from_cell(self, row, col):  # This function is copied from MIT 6.034 lab3
        # Return the max-length chain containing this cell
        return [ tuple(x) for x in [
                reverse(self._contig_vector_cells(row, col, (1,1))) + [(row, col)] + self._contig_vector_cells(row, col, (-1,-1)),
                 reverse(self._contig_vector_cells(row, col, (1,0))) + [(row, col)] + self._contig_vector_cells(row, col, (-1,0)),
                reverse(self._contig_vector_cells(row, col, (0,1))) + [(row, col)] + self._contig_vector_cells(row, col, (0,-1)),
                reverse(self._contig_vector_cells(row, col, (-1,1))) + [(row, col)] + self._contig_vector_cells(row, col, (1,-1)) 
                 ] ]

    def get_chains(self, player_id):  # This function is copied from MIT 6.034 lab3
        # Get all consecutive chain of player_id
        retVal = set()
        for row in range(board_height):
            for col in range(board_width):
                if self.get_cell(row, col) == player_id:
                    retVal.update( self._chain_sets_from_cell(row, col) )              
        return retVal

    def _is_game_over(self):
        # Check if a game is over

        for chain in self.get_chains(player_x_id):
            if len(chain) == win_condition:
                return player_x_id
        for chain in self.get_chains(player_o_id):
            if len(chain) == win_condition:
                return player_o_id
        return False


    def print_board(self) -> None:
        # Print board function
        
        for row in self.board:
            for num in row:
                if num == player_x_id:
                    print(player_x_icon, end=" ")
                elif num == player_o_id:
                    print(player_o_icon, end=" ")
                else:
                    print("-", end=" ")
            print("")
        print("")
    

# This class is created to store temporary board used in alpha-beta algorithm
class temporary_board(tic_tac_toe_board):
    def __init__(self, board: tic_tac_toe_board) -> None:
        self.board = deepcopy(board)       # self.board = [row[:] for row in board] is also work!
        self.current_player_turn = current_turn_util
    def get_next_board(self, row, col, player_id):
        if player_id not in [player_x_id, player_o_id] or row*col < 0 or row > board_height or col > board_width:
            raise IndexError("Move out of range or player_id is not allowed, player_id: %i (1 or -1)" % player_id)
        self.board[row][col] = player_id
        return self.board
