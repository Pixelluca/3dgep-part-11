#include "game.h"
#include "surface.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace Tmpl8
{
    void Game::Init() {}
    void Game::Shutdown() {}

    Surface tiles("assets/nc2tiles.png");

    char map[5][30] = {
         "kc kc kc kc kc kc kc kc kc kc",
         "kc fb fb fb kc kc kc kc kc kc",
         "kc fb fb fb fb fb kc kc kc kc",
         "kc lc lc fb fb fb kc kc kc kc",
         "kc kc kc lc lc lc kc kc kc kc"
    };

    Sprite tank(new Surface("assets/ctankbase.tga"), 16);
    int px = 200, py = 128;
    bool CheckPos(int x, int y)
    {
        int tx = x / 32, ty = y / 32;
        return map[ty][tx * 3 + 2] != 'X';
    }

    void DrawTile(int tx, int ty, Surface* screen, int x, int y)
    {
        Pixel* src = tiles.GetBuffer() + 1 + tx * 33 + (1 + ty * 33) * 595;
        Pixel* dst = screen->GetBuffer() + x + y * 800;
        for (int i = 0; i < 32; i++, src += 595, dst += 800)
            for (int j = 0; j < 32; j++)
                dst[j] = src[j];
    }

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        for (int y = 0; y < 5; y++)
            for (int x = 0; x < 10; x++)
            {
                int tx = map[y][x * 3] - 'a';
                int ty = map[y][x * 3 + 1] - 'a';
                DrawTile(tx, ty, screen, x * 32 + 200, y * 32 + 128);
            }
        tank.Draw(screen, px, py);
        int nx = px, ny = py;
        if (GetAsyncKeyState(VK_LEFT)) nx--, tank.SetFrame(12);
        if (GetAsyncKeyState(VK_RIGHT)) nx++, tank.SetFrame(4);
        if (GetAsyncKeyState(VK_UP)) ny--, tank.SetFrame(0);
        if (GetAsyncKeyState(VK_DOWN)) ny++, tank.SetFrame(8);
        if (CheckPos(nx, ny) && CheckPos(nx + 30, ny + 30) &&
            CheckPos(nx + 30, ny) && CheckPos(nx, ny + 30))
            px = nx, py = ny;
    }
};