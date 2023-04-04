/*
** EPITECH PROJECT, 2023
** library MY_GRAPHICS
** File description:
** function that draw a specific layer to window
*/
#include "../include/layer.h"

void draw_single_layer(sfRenderWindow * window, layer_t * layer)
{
    sfColor blank = {0.0, 0.0, 0.0, 0.0};
    sfRenderTexture_clear(layer->texture, blank);
    draw_draws(layer->texture, layer->draw);
    sfSprite_setTexture(layer->sprite,
                        sfRenderTexture_getTexture(layer->texture), sfTrue);
    sfRenderWindow_drawSprite(window, layer->sprite, NULL);
}
