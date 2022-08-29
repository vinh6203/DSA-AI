
# WARNING if change width and height to large (it is recommended to set board_width*board_height <= 25), 
# it can cause program to run for a long time or maybe even crash!
board_width = 5
board_height = 5
turn_limit_util = board_height*board_width
win_condition = 4  # Default is min(board_height, board_width) but change to 2, 3, 4 at wish

# it is important to NOT change player_id (change will cause bad consequences !!!)
player_x_id = 1
player_x_icon = 'X'
player_o_id = -1
player_o_icon = 'O'

current_turn_util = player_x_id
convert_turn_to_icon = dict([[player_x_id, player_x_icon], [player_o_id, player_o_icon]])

# Set Delay on the screen (1 for 1 second)
allowed_delay = True  #set this to True if want delay on screen
delay = 1   # 1 second

# Ultility function
def reverse(lst):
    reversed_lst = list(lst)
    reversed_lst.reverse()
    return reversed_lst
