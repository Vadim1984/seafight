This is a console application which is implement sea fight game user VS PC.

Entities:
1) Board (Model) - implement game board:
  1.  Set ships in random style.
  2.  If player make step check if one of ship was damaged and update ship state.
  3.  Monitoring count of crashed ships.
  4.  Display play board.
2) Ship - implement ship
  1.  Hold ship coordinates and size.
  2.  Hold if ship is crashed or not.
3) View - used for display current game state for user.
  1. Updated after one of players made step, also update model.
4) Controller - used for manage game process.
