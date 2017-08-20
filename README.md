This is a console application which is implement sea fight game user VS PC.

Entities:
1) Board (Model) - implement game board:
  -  Set ships in random style.
  -  If player make step check if one of ship was damaged and update ship state.
  -  Monitoring count of crashed ships.
  -  Display play board.
2) Ship - implement ship
  -  Hold ship coordinates and size.
  -  Hold if ship is crashed or not.
3) View - used for display current game state for user.
  - Updated after one of players made step, also update model.
4) Controller - used for manage game process.
