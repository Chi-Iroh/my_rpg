/*
** EPITECH PROJECT, 2023
** library MY_GRAPHICS
** File description:
** function that initialize a window struct
*/
#include "../include/window.h"

window_t * init_window(void)
{
    window_t * window = malloc(sizeof(window_t));
    window->size = set_2vector(0.f, 0.f);
    window->window = NULL;
    window->view = NULL;
    window->core = NULL;
    window->ui = NULL;
    return window;
}