#include "../include/colors.h"
#include "../include/game.h"
#include <cstdlib>
#include <csignal>

void bailout() {
	set_mouse_mode(false);
	set_raw_mode(false);
	clearscreen();
}
void interrupt_handler(int x) {
	std::exit(0);
}

int main()
{
	//These two lines prevent us from leaving the terminal in a bad state if we ctrl-c out or exit()
	atexit(bailout); //Callback when we quit, call bailout to clean up the terminal
	signal(SIGINT,interrupt_handler);

	//See how large the terminal is in both dimensions
	const auto [ROWS,COLS] = get_terminal_size();

	set_raw_mode(true); //Enable non-blocking IO & quick_read
    clearscreen();

	set_cursor_mode(true); //Enable drawing the cursor
	set_mouse_mode(false); //Enable mouse events

    // New game
    Game newGame;
    newGame.CreateBoard();
    newGame.Print_Visible_board();

    // Cursor position
    const int cursorXOffset = 2;
    int cursorX = 1, cursorY = 0;
    int tileX = 0, tileY = 0; // This is here to keep track of the tiles since the cursor and tile have different positions.
    movecursor(cursorY, cursorX); // Make sure the cursor starts at the top left
	
	while (true) {
		int c = quick_read();
		if (c == 'q') {
            break;
        } else if (c == ERR) {
            usleep(10'000);
        } else if (c == UP_ARROW) {
            cursorY--;
            movecursor(cursorY, cursorX);
        } else if (c == DOWN_ARROW) {
            cursorY++;
            movecursor(cursorY, cursorX);
        } else if (c == LEFT_ARROW) {
            cursorX -= cursorXOffset;
            movecursor(cursorY, cursorX);
        } else if (c == RIGHT_ARROW) {
            cursorX += cursorXOffset;
            movecursor(cursorY, cursorX);
        } else if (c == 'z') {
            // bomb
        } else if (c == 'x') {
            // mine
        }
	}
}
