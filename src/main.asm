.MODEL SMALL
.STACK 100h

.DATA
    INCLUDE "data.inc"

.CODE
    INCLUDE "config.inc"
    INCLUDE "graphics.inc"
    INCLUDE "input.inc"
    INCLUDE "movement.inc"
    INCLUDE "collision.inc"
    INCLUDE "food.inc"
    INCLUDE "score.inc"

MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    ; Set starting position for snake(total length=7)
    MOV snake_length, 7         

    MOV snake_x[0], 40
    MOV snake_y[0], 12
    MOV snake_x[1], 39
    MOV snake_y[1], 12
    MOV snake_x[2], 38
    MOV snake_y[2], 12
    MOV snake_x[3], 37
    MOV snake_y[3], 12
    MOV snake_x[4], 36
    MOV snake_y[4], 12
    MOV snake_x[5], 35
    MOV snake_y[5], 12
    MOV snake_x[6], 34
    MOV snake_y[6], 12

    ; starting position of food
    MOV food_x, 30
    MOV food_y, 10

    ; Call graphics setup routines
    CALL INIT_GRAPHICS
    CALL DRAW_BOARD
    CALL DRAW_FOOD
    CALL DRAW_SCORE

; Game loop starts
GAME_LOOP:
    ; directional change
    CALL POLL_KEYBOARD

    ; Move Snake 
    CALL UPDATE_SNAKE_POSITION

    ;check if ate food
    CALL CHECK_FOOD
    
    ; a wall or self collision
    CALL CHECK_COLLISIONS
    CMP  game_over, 1
    JE   GAME_OVER_STATE

    ; Clear old tail 
    CALL ERASE_CELL

    ; Redraw Snake at new position
    CALL DRAW_SNAKE

    ; Game speed delay
    MOV CX, 0000h
    MOV DX, 2000h
    MOV AH, 86h
    INT 15h

    JMP GAME_LOOP

GAME_OVER_STATE:
    ; Freeze game on collision
    MOV AH, 4Ch
    INT 21h

MAIN ENDP
END MAIN