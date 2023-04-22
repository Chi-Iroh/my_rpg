/*
** EPITECH PROJECT, 2023
** library MY_GRAPHICS
** File description:
** function that create a window struct from parameters
*/
#include "../include/window.h"

void window_windowed(window_t * window, const char * title,
                        const sfVideoMode mode, const char * file)
{
    sfContextSettings sett = sfRenderWindow_getSettings(window->window);
    sfRenderWindow_destroy(window->window);
    window->window = sfRenderWindow_create(mode, title, sfDefaultStyle, &sett);
    if (file != NULL) {
        sfImage * icon = sfImage_createFromFile(file);
        sfRenderWindow_setIcon(window->window, sfImage_getSize(icon).x,
                        sfImage_getSize(icon).y, sfImage_getPixelsPtr(icon));
        sfImage_destroy(icon);
    }
    sfRenderWindow_setFramerateLimit(window->window, 120);
}

void window_fullscreen(window_t * window, const char * title,
                        const sfVideoMode mode, const char * file)
{
    sfContextSettings sett = sfRenderWindow_getSettings(window->window);
    sfRenderWindow_destroy(window->window);
    window->window = sfRenderWindow_create(mode, title, sfFullscreen, &sett);
    if (file != NULL) {
        sfImage * icon = sfImage_createFromFile(file);
        sfRenderWindow_setIcon(window->window, sfImage_getSize(icon).x,
                        sfImage_getSize(icon).y, sfImage_getPixelsPtr(icon));
        sfImage_destroy(icon);
    }
    sfRenderWindow_setFramerateLimit(window->window, 120);
}
