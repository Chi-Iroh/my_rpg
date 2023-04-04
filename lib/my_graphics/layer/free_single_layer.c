/*
** EPITECH PROJECT, 2023
** library MY_GRAPHICS
** File description:
** function that free a layer struct
*/
#include "../include/layer.h"

void free_single_layer(layer_t * layer)
{
    sfRenderTexture_destroy(layer->texture);
    sfSprite_destroy(layer->sprite);
    free(layer);
}
