#include <stdbool.h>

typedef struct Resolution
{
    int width;
    int height;
    bool fullscreen;

} Resolution;

typedef struct Images
{
    int count;
    char **images;

} Images;

typedef struct Offsets {
    int health;

} Offsets;

typedef struct Settings
{
    Resolution resolution;
    Images images;
    Offsets offsets;

} Settings;

Settings *CreateSettings();