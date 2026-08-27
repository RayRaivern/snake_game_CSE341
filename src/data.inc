
; Game Constants

MAX_SNAKE_LEN   EQU 100             ; Maximum array size for body segments
BOARD_MIN_X     EQU 5               ; Left boundary X column
BOARD_MAX_X     EQU 74              ; Right boundary X column
BOARD_MIN_Y     EQU 3               ; Top boundary Y row
BOARD_MAX_Y     EQU 22              ; Bottom boundary Y row

; Game Variables

current_key     DB 0                ; Stores ASCII code of active key press ('w','a','s','d')

; Index 0 = Head, Index [length-1] = Tail
snake_x         DB MAX_SNAKE_LEN DUP(0)  ; X coordinate array (0-79)
snake_y         DB MAX_SNAKE_LEN DUP(0)  ; Y coordinate array (0-24)

snake_length    DB 4                ; Current active segment count
snake_dir       DB 1                ; 0 = UP, 1 = RIGHT, 2 = DOWN, 3 = LEFT
game_over       DB 0                ; Status flag: 0 = Running, 1 = Collision Triggered


food_x          DB 0                ; Active food X position on board
food_y          DB 0                ; Active food Y position on board
rand_seed       DW 0                ; Seed for random coordinate generator

score           DW 0                ; Current player score (16-bit word)
score_str       DB '00000$'         ; ASCII string buffer for printing (INT 21h, AH=09h)