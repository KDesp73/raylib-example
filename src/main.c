#include "raylib.h"
#include "raymath.h"
#include <math.h>

#define CLIB_IMPLEMENTATION
#include "clib.h"

#define POINT_RADIUS 15.f
#define STARTING_OFFSET 100
#define TARGET_FPS 60

#define EUCLEDIAN_DISTANCE(x1, y1, x2, y2) (sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1)))

int mouse_on_point(Vector2 mouse_pos, Vector2 point_pos){
    return EUCLEDIAN_DISTANCE(mouse_pos.x, mouse_pos.y, point_pos.x, point_pos.y) <= POINT_RADIUS;
}

int will_collide(Vector2 point1, Vector2 point2){
    return EUCLEDIAN_DISTANCE(point1.x, point1.y, point2.x, point2.y) < 2 * POINT_RADIUS;
}

typedef enum {
    POINT_RED,
    POINT_BLUE
} PointColor ;

int main(int argc, char** argv){
    clib_shift_args(&argc, &argv);
    INFO("Started...");

    InitWindow(1600, 900, "Raylib Test");
    SetTargetFPS(TARGET_FPS);
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    Color blue = GetColor(0x0088BBFF);
    Color red = GetColor(0xE34234FF);
    Color grey = GetColor(0x808080FF);

    Vector2 center = {
        .x = (float) w/2,
        .y = (float) h/2
    };
    Vector2 blue_coords = {
        .x = center.x - STARTING_OFFSET,
        .y = center.y
    };
    Vector2 red_coords = {
        .x = center.x + STARTING_OFFSET,
        .y = center.y
    };

    Camera2D camera = {
        .zoom = 1.0f
    };

    int holding = -1;

    BeginMode2D(camera);

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
            ClearBackground(GetColor(0x181818FF));

            if(IsKeyPressed(KEY_R)){
                blue_coords.x = center.x - STARTING_OFFSET;
                blue_coords.y = center.y;
                red_coords.x = center.x + STARTING_OFFSET;
                red_coords.y = center.y;
            }

            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(mouse_on_point(mouse_pos, blue_coords)){
                    holding = POINT_BLUE;
                }
                
                if(mouse_on_point(mouse_pos, red_coords)){
                    holding = POINT_RED;
                }
            } else holding = -1;

            if(holding == POINT_BLUE){
                if(!will_collide(mouse_pos, red_coords)){
                    blue_coords = mouse_pos;
                }
            } else if(holding == POINT_RED){
                if(!will_collide(mouse_pos, blue_coords)){
                    red_coords = mouse_pos;
                }
            }

            DrawLineEx(blue_coords, red_coords, 5.0f, grey);
            DrawCircleV(blue_coords, POINT_RADIUS, blue);
            DrawCircleV(red_coords, POINT_RADIUS, red);
            DrawText(TextFormat("BLUE %4.0f %4.0f", blue_coords.x, blue_coords.y), 10, 10, 20, WHITE);
            DrawText(TextFormat("RED %4.0f %4.0f", red_coords.x, red_coords.y), 10, 40, 20, WHITE);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
