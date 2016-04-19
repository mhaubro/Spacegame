#include "UI.h"
#include "Graphics.h"

#include <string.h>

UI::UI(Game* game) : game(game)
{
    
}

void UI::render()
{
    GD.SaveContext();
    
    // prints gameinfo in upper left corner
    GD.ColorRGB(WHITE);
    GD.cmd_text(4,4,16,OPT_SIGNED, "SPACE GAME");
    
    // prints the score in the upper right corner.
    GD.cmd_text(SCREEN_WIDTH-4, 4 , 16, OPT_RIGHTX, "SCORE");
    GD.cmd_number(SCREEN_WIDTH-4, 4 + 12, 16, OPT_RIGHTX + 8, game->score);
    
    // prints the health level in the lower left corner
    GD.ColorRGB(COLOR_HEALTH);
    GD.cmd_text( 4, SCREEN_HEIGHT - 26 , 16, OPT_SIGNED, "Health");
    GD.cmd_number(4, SCREEN_HEIGHT - 16, 16, OPT_SIGNED+4, game->energy);
    GD.Begin(LINES);
    GD.Vertex2f(16 * 4, 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f((((16 * SCREEN_WIDTH)/2)/game->maxHealth)*game->health , 16 * (SCREEN_HEIGHT - 4));
    
    // prints energy level in the lower right corner
    GD.ColorRGB(COLOR_ENERGY);
    GD.cmd_text( SCREEN_WIDTH-4, SCREEN_HEIGHT - 26 , 16, OPT_RIGHTX, "Energy");
    GD.cmd_number(SCREEN_WIDTH-4, SCREEN_HEIGHT - 16, 16, OPT_RIGHTX+4, game->energy);
    GD.Begin(LINES);
    GD.Vertex2f(16 * (SCREEN_WIDTH - 4), 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f((16 * SCREEN_WIDTH) - (((16 * SCREEN_WIDTH)/2)/game->maxEnergy)*game->energy , 16 * (SCREEN_HEIGHT - 4));
    
    GD.RestoreContext();
}