CHECK_FOOD PROC NEAR

	;is snake head on food?
	MOV AL, snake_x[0]
	CMP AL, food_x
	JNE Dont_Eat
	MOV AL, snake_y[0]
	CMP AL, food_y
	JNE Dont_Eat

	ADD score, 1
	CMP snake_length, MAX_SNAKE_LEN
	JGE Skip_Grow
	

	Skip_Grow:
		CALL SPAWN_FOOD
		CALL DRAW_SCORE

	Dont_Eat:
		RET
CHECK_FOOD ENDP


SPAWN_FOOD PROC NEAR
	PUSH AX
	PUSH BX
	PUSH CX
	PUSH DX

	;get bios timer ticks
	MOV AH, 00h
	INT 1Ah
	MOV rand_seed, DX
	
	;generate coordinates
	MOV AX, rand_seed
	MOV BX, 68 ;x=68 positions
	XOR DX, DX
	DIV BX

	MOV AL, DL
	ADD AL, 6 ; x starts from 6
	MOV food_x, AL

	MOV rand_seed, DX ;change random seed
	MOV AX, rand_seed
	ADD AX, 37
	MOV BX, 18  ;y=18 positions
	XOR DX, DX
	DIV BX

	MOV AL, DL
	ADD AL, 4 ; y starts from 4
	MOV food_y, AL

	CALL DRAW_FOOD

	POP AX
	POP BX
	POP CX
	POP DX

	RET

SPAWN_FOOD ENDP






