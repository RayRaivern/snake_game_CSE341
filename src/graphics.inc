; Uses BIOS INT 10h text mode graphics (80x25 columns/rows).

; Color Constants (BL attribute for INT 10h, AH=09h)
COLOR_BORDER	EQU	01Fh	; Bright White on Blue background
COLOR_SNAKE	EQU	00Ah	; Light Green
COLOR_HEAD	EQU	00Eh	; Yellow
COLOR_FOOD	EQU	00Ch	; Light Red
COLOR_BG	EQU	000h	; Black (Clear)


; Helper Routine: WRITE_CHAR_AT
; Inputs:   DL = X (Column), DH = Y (Row), AL = ASCII Char, BL = Color/Attr

WRITE_CHAR_AT	PROC	NEAR
	PUSH	AX
	PUSH	BX
	PUSH	CX
	PUSH	DX

	; Set cursor position
	MOV	AH, 02h
	MOV	BH, 00h	; Page 0
	INT	10h	; DH=Row, DL=Col

	; Write character with attribute
	MOV	AH, 09h
	MOV	CX, 0001h	; Write 1 character
	INT	10h

	POP	DX
	POP	CX
	POP	BX
	POP	AX
	RET
WRITE_CHAR_AT	ENDP


; Routine:  INIT_GRAPHICS
; Purpose:  Sets 80x25 text mode (03h) and hides cursor

INIT_GRAPHICS	PROC	NEAR
	PUSH	AX
	PUSH	CX

	; Set Video Mode 03h (80x25, 16 colors)
	MOV	AH, 00h
	MOV	AL, 03h
	INT	10h

	; Hide cursor by setting start line > end line
	MOV	AH, 01h
	MOV	CX, 2000h
	INT	10h

	POP	CX
	POP	AX
	RET
INIT_GRAPHICS	ENDP


; Routine:  DRAW_BOARD
; Purpose:  Renders top, bottom, left, and right borders

DRAW_BOARD	PROC	NEAR
	PUSH	AX
	PUSH	BX
	PUSH	DX

	MOV	BL, COLOR_BORDER

	; 1. Draw Top and Bottom Horizontal Borders
	MOV	DL, BOARD_MIN_X
DB_Horiz_Loop:
	MOV	DH, BOARD_MIN_Y	; Top Row
	MOV	AL, '='
	CALL	WRITE_CHAR_AT

	MOV	DH, BOARD_MAX_Y	; Bottom Row
	MOV	AL, '='
	CALL	WRITE_CHAR_AT

	INC	DL
	CMP	DL, BOARD_MAX_X
	JLE	DB_Horiz_Loop

	; 2. Draw Left and Right Vertical Borders
	MOV	DH, BOARD_MIN_Y
DB_Vert_Loop:
	MOV	DL, BOARD_MIN_X	; Left Column
	MOV	AL, '|'
	CALL	WRITE_CHAR_AT

	MOV	DL, BOARD_MAX_X	; Right Column
	MOV	AL, '|'
	CALL	WRITE_CHAR_AT

	INC	DH
	CMP	DH, BOARD_MAX_Y
	JLE	DB_Vert_Loop

	POP	DX
	POP	BX
	POP	AX
	RET
DRAW_BOARD	ENDP


; Routine:  DRAW_SNAKE
; Purpose:  Renders head ('O') and body segments ('o') from parallel arrays

DRAW_SNAKE	PROC	NEAR
	PUSH	AX
	PUSH	BX
	PUSH	CX
	PUSH	DX
	PUSH	SI

	MOV	CL, snake_length
	XOR	CH, CH
	XOR	SI, SI	; SI = 0 (Head)

DS_Loop:
	MOV	DL, snake_x[SI]
	MOV	DH, snake_y[SI]

	CMP	SI, 0
	JNE	DS_Draw_Body

	; Draw Snake Head
	MOV	AL, 'O'
	MOV	BL, COLOR_HEAD
	JMP	DS_Plot

DS_Draw_Body:
	; Draw Body Segment
	MOV	AL, 'o'
	MOV	BL, COLOR_SNAKE

DS_Plot:
	CALL	WRITE_CHAR_AT
	INC	SI
	LOOP	DS_Loop

	POP	SI
	POP	DX
	POP	CX
	POP	BX
	POP	AX
	RET
DRAW_SNAKE	ENDP


; Routine:  ERASE_CELL
; Purpose:  Clears a specific coordinate (e.g., erasing old tail)
; Inputs:   DL = X coordinate, DH = Y coordinate

ERASE_CELL	PROC	NEAR
	PUSH	AX
	PUSH	BX

	MOV	AL, ' '	; Blank character
	MOV	BL, COLOR_BG
	CALL	WRITE_CHAR_AT

	POP	BX
	POP	AX
	RET
ERASE_CELL	ENDP


; Routine:  DRAW_FOOD
; Purpose:  Renders food symbol ('*') at (food_x, food_y)

DRAW_FOOD	PROC	NEAR
	PUSH	AX
	PUSH	BX
	PUSH	DX

	MOV	DL, food_x
	MOV	DH, food_y
	MOV	AL, '*'
	MOV	BL, COLOR_FOOD
	CALL	WRITE_CHAR_AT

	POP	DX
	POP	BX
	POP	AX
	RET
DRAW_FOOD	ENDP