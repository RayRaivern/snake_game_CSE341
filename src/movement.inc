; Routine:  UPDATE_SNAKE_POSITION
; Purpose:  Shifts snake body array forward and calculates new head position.
; Outputs:  DL = Old Tail X, DH = Old Tail Y (used by ERASE_CELL)

UPDATE_SNAKE_POSITION PROC NEAR
    PUSH    AX
    PUSH    BX
    PUSH    CX
    PUSH    SI

    ;save old tail coordinates (snake_length - 1) into DX
    MOV     CL, snake_length
    XOR     CH, CH
    MOV     SI, CX
    DEC     SI                ;SI = Tail index

    MOV     DL, snake_x[SI]   ;old tail x in DL
    MOV     DH, snake_y[SI]   ;old tail y in DH

    ;shift body segments rightward (from tail back to index 1)
    ; snake[i]=snake[i-1]
USP_Shift_Loop:
    CMP     SI, 0
    JE      USP_Move_Head

    MOV     AL, snake_x[SI-1]
    MOV     snake_x[SI], AL

    MOV     AL, snake_y[SI-1]
    MOV     snake_y[SI], AL

    DEC     SI
    JMP     USP_Shift_Loop

    ;update head position (Index 0) based on snake_dir
USP_Move_Head:
    CMP     snake_dir, 0
    JE      USP_Up
    CMP     snake_dir, 1
    JE      USP_Right
    CMP     snake_dir, 2
    JE      USP_Down
    CMP     snake_dir, 3
    JE      USP_Left
    JMP     USP_Done

USP_Up:
    DEC     snake_y[0]
    JMP     USP_Done

USP_Right:
    INC     snake_x[0]
    JMP     USP_Done

USP_Down:
    INC     snake_y[0]
    JMP     USP_Done

USP_Left:
    DEC     snake_x[0]

USP_Done:
    POP     SI
    POP     CX
    POP     BX
    POP     AX
    RET
UPDATE_SNAKE_POSITION ENDP