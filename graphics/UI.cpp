#include "UI.h"
#include "Graphics.h"
#include "player.h"
#include <string.h>

UI::UI(Game* game) : game(game)
{
    
}

void UI::render()
{
    GD.SaveContext();
    
    GD.ColorA(0x88);
    GD.ColorRGB(GREY);

    GD.Begin(EDGE_STRIP_B);
    GD.Vertex2ii(0,SCREEN_HEIGHT - 30);
    GD.Vertex2ii(56, SCREEN_HEIGHT - 30);
    GD.Vertex2ii(76,SCREEN_HEIGHT-10);
    GD.Vertex2ii(SCREEN_WIDTH/2 - 52,SCREEN_HEIGHT-10);
    GD.Vertex2ii(SCREEN_WIDTH/2 - 32,SCREEN_HEIGHT-30);
    GD.Vertex2ii(SCREEN_WIDTH/2 + 32,SCREEN_HEIGHT-30);
    GD.Vertex2ii(SCREEN_WIDTH/2 + 52,SCREEN_HEIGHT-10);
    GD.Vertex2ii(SCREEN_WIDTH - 76,SCREEN_HEIGHT-10);
    GD.Vertex2ii(SCREEN_WIDTH - 56, SCREEN_HEIGHT - 30);
    GD.Vertex2ii(SCREEN_WIDTH - 0,SCREEN_HEIGHT-30);

    GD.Begin(EDGE_STRIP_A);
    GD.Vertex2ii(0,20);
    GD.Vertex2ii(80,20);
    GD.Vertex2ii(100,0);
    GD.Vertex2ii(SCREEN_WIDTH - 100,0);
    GD.Vertex2ii(SCREEN_WIDTH - 72,28);
    GD.Vertex2ii(SCREEN_WIDTH,28);

    GD.ColorA(0xFF);

    GD.LineWidth(3*16);

    // prints gameinfo in upper left corner
    GD.ColorRGB(WHITE);
    GD.cmd_text(4,4,16,OPT_SIGNED, "SPACE GAME");
    GD.cmd_number(4, 4 + 12, 16, OPT_SIGNED, player.ph.position.x);
    GD.cmd_number(4, 4 + 24, 16, OPT_SIGNED, player.ph.position.y);
    
    // prints the score in the upper right corner.
    GD.cmd_text(SCREEN_WIDTH-4, 4 , 16, OPT_RIGHTX, "SCORE");
    GD.cmd_number(SCREEN_WIDTH-4, 4 + 12, 16, OPT_RIGHTX + 8, game->score);
    
    // prints the health level in the lower left corner
    GD.Begin(LINES);
    GD.ColorRGB(DARK_GREY);
    GD.Vertex2f(16 * 4, 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f(16 * (SCREEN_WIDTH/2-16), 16 * (SCREEN_HEIGHT - 4));
    GD.ColorRGB(COLOR_HEALTH);
    GD.Vertex2f(16 * 4, 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f(((16 * (SCREEN_WIDTH/2-16))/game->maxHealth)*game->health , 16 * (SCREEN_HEIGHT - 4));
    GD.cmd_text( 4, SCREEN_HEIGHT - 26 , 16, OPT_SIGNED, "Health");
    GD.cmd_number(4, SCREEN_HEIGHT - 16, 16, OPT_SIGNED+4, game->health);
    
    // prints energy level in the lower right corner
    GD.Begin(LINES);
    GD.ColorRGB(DARK_GREY);
    GD.Vertex2f(16 * (SCREEN_WIDTH - 4), 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f(16 * (SCREEN_WIDTH/2+16), 16 * (SCREEN_HEIGHT - 4));
    GD.ColorRGB(COLOR_ENERGY);
    GD.Vertex2f(16 * (SCREEN_WIDTH - 4), 16 * (SCREEN_HEIGHT - 4));
    GD.Vertex2f((16 * SCREEN_WIDTH) - (16 * (SCREEN_WIDTH/2-16)/game->maxEnergy)*game->energy , 16 * (SCREEN_HEIGHT - 4));
    GD.cmd_text( SCREEN_WIDTH-4, SCREEN_HEIGHT - 26 , 16, OPT_RIGHTX, "Energy");
    GD.cmd_number(SCREEN_WIDTH-4, SCREEN_HEIGHT - 16, 16, OPT_RIGHTX+4, game->energy);
    
    // prints the height in the lower middle.
    GD.cmd_text(SCREEN_WIDTH/2-4, SCREEN_HEIGHT - 26 , 16, OPT_CENTERX, "Height");
   // GD.cmd_number(SCREEN_WIDTH/2-4, SCREEN_HEIGHT - 16, 16, OPT_CENTERX + 4, player.height);
    GD.cmd_number(SCREEN_WIDTH/2-4, SCREEN_HEIGHT - 16, 16, OPT_CENTERX + 4, player.height);

    GD.RestoreContext();
}
