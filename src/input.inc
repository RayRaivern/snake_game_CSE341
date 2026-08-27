
; Polls key buffer without blocking. Supports WASD & Arrow Keys.
; Prevents 180-degree instant self-collisions.
; Inputs:   Reads active key buffer via INT 16h
; Outputs:  Modifies 'snake_dir' and 'current_key' in data.inc

POLL_KEYBOARD PROC NEAR
	PUSH	AX	; Preserve modified registers
	PUSH	BX

	; Step 1: Check keyboard status (Non-Blocking)
	MOV	AH, 01h
	INT	16h
	JZ	PK_Done	; ZF=1 -> Buffer empty, keep moving

	; Step 2: Key available -> Remove key from buffer
	MOV	AH, 00h
	INT	16h	; AL = ASCII, AH = Scan Code

	MOV	current_key, AL	; Save raw character to data.inc

	; Step 3: Check WASD & Arrow Keys
	CMP	AL, 'w'
	JE	PK_Set_Up
	CMP	AL, 'W'
	JE	PK_Set_Up
	CMP	AH, 48h	; Up Arrow scan code
	JE	PK_Set_Up

	CMP	AL, 'd'
	JE	PK_Set_Right
	CMP	AL, 'D'
	JE	PK_Set_Right
	CMP	AH, 4Dh	; Right Arrow scan code
	JE	PK_Set_Right

	CMP	AL, 's'
	JE	PK_Set_Down
	CMP	AL, 'S'
	JE	PK_Set_Down
	CMP	AH, 50h	; Down Arrow scan code
	JE	PK_Set_Down

	CMP	AL, 'a'
	JE	PK_Set_Left
	CMP	AL, 'A'
	JE	PK_Set_Left
	CMP	AH, 4Bh	; Left Arrow scan code
	JE	PK_Set_Left

	JMP	PK_Done	; Ignore non-movement keys


; 0=UP, 1=RIGHT, 2=DOWN, 3=LEFT)
; Prevent 180-degree turns (e.g., changing to DOWN when already moving UP)

PK_Set_Up:
	CMP	snake_dir, 2	; Cannot set UP if moving DOWN
	JE	PK_Done
	MOV	snake_dir, 0
	JMP	PK_Done

PK_Set_Right:
	CMP	snake_dir, 3	; Cannot set RIGHT if moving LEFT
	JE	PK_Done
	MOV	snake_dir, 1
	JMP	PK_Done

PK_Set_Down:
	CMP snake_dir, 0	; Cannot set DOWN if moving UP
	JE	PK_Done
	MOV	snake_dir, 2
	JMP	PK_Done

PK_Set_Left:
	CMP	snake_dir, 1	; Cannot set LEFT if moving RIGHT
	JE	PK_Done
	MOV	snake_dir, 3

PK_Done:
	POP	BX	; Restore registers
	POP	AX
	RET
POLL_KEYBOARD	ENDP