# All Files Features and Functions
1. `main.asm`: Contains code for the main game loop.
2. `config.inc`: Contains shared constants (does not change in execution). 
Ex: board_size, colors, etc.
3. `data.inc`: Shared variables like the main Snake array, Head/Tail positions, Food positions.
4. `graphics.inc` **(Feature-1)**: Board rendering and screen clearing logic.
5. `input.inc` **(Feature-2)**: Keyboard input polling code.
6. `movement.inc` **(Feature-3)**: Updating Snake direction and position.
7. `collision.inc` **(Feature-4)**: Checking Wall or Snake Body collision.
8. `food.inc` **(Feature-5)**: Food generation using random number generator, and food collision check.
9. `score.inc` **(Feature-6)**: Score tracking, and score printing.
