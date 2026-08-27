; Routine:  CHECK_COLLISIONS
; Purpose:  Checks for wall collisions and self-collisions.
; Outputs:  Sets game_over = 1 if a collision occurs.

CHECK_COLLISIONS PROC NEAR
    PUSH    AX
    PUSH    CX
    PUSH    SI

    ; Check Wall Collisions (head position vs boundaries)
    MOV     AL, snake_x[0]
    CMP     AL, BOARD_MIN_X
    JLE     CC_Trigger_Over
    CMP     AL, BOARD_MAX_X
    JGE     CC_Trigger_Over

    MOV     AL, snake_y[0]
    CMP     AL, BOARD_MIN_Y
    JLE     CC_Trigger_Over
    CMP     AL, BOARD_MAX_Y
    JGE     CC_Trigger_Over

    ; Check Self-Collision
    ; Loop from SI = 1 to (snake_length - 1)
    MOV     CL, snake_length
    XOR     CH, CH
    CMP     CX, 1
    JLE     CC_Done       ;can't collide with body if length <= 1

    MOV     SI, 1         ;start comparing at body segment 1
CC_Self_Loop:
    CMP     SI, CX
    JGE     CC_Done           ;loop finished without collision

    MOV     AL, snake_x[0]
    CMP     AL, snake_x[SI]
    JNE     CC_Next_Segment

    MOV     AL, snake_y[0]
    CMP     AL, snake_y[SI]
    JE      CC_Trigger_Over  ;x,y matchibg Head hit body

CC_Next_Segment:
    INC     SI
    JMP     CC_Self_Loop

CC_Trigger_Over:
    MOV     game_over, 1   ;game over

CC_Done:
    POP     SI
    POP     CX
    POP     AX
    RET
CHECK_COLLISIONS ENDP