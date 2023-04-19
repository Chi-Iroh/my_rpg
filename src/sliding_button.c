/*
** EPITECH PROJECT, 2022
** B-MUL-200-LYN-2-1-mypaint-adrien.audiard
** File description:
** sliding_button.c
*/

#include "../include/my_rpg.h"

button_s_t* append_button_layer(layer_t* layer, button_s_t* btn)
{
    append_draw_layer(layer, btn->name);
    append_draw_layer(layer, btn->rect);
    btn->layer_on = layer;
    return btn;
}

sliding_button_t** append_s_button_layer(layer_t* layer,
    sliding_button_t** s_btn, int nb_s_btn)
{
    for (int i = 0; i < nb_s_btn; i++) {
        s_btn[i]->btn = append_button_layer(layer, s_btn[i]->btn);
        append_draw_layer(layer, s_btn[i]->line);
    }
    return s_btn;
}

float get_value_sliding_button(sliding_button_t* s_btn)
{
    float x_btn = get_position_draw(s_btn->btn->rect).x;
    float x_line = get_position_draw(s_btn->line).x;
    return (x_btn - x_line) / 300 * s_btn->max_value + s_btn->min_value;
}

void move_sliding_button_btn(sfMouseMoveEvent evt, sliding_button_t* s_btn)
{
    sfVector2f old_pos = get_position_draw(s_btn->btn->rect);
    sfVector2f line_pos = get_position_draw(s_btn->line);
    float x = evt.x >= line_pos.x && evt.x <= line_pos.x + 300 ?
        evt.x : evt.x < line_pos.x ? line_pos.x : line_pos.x + 300;
    set_pos_draw(s_btn->btn->rect, set_3vector(x, old_pos.y, 0));
}

sliding_button_t** set_sliding_button(list_button_t** all_btn, int nb_sl,
    sfVector3f pos, float* value)
{
    sliding_button_t** s_btn = malloc(sizeof(sliding_button_t*) * (nb_sl + 1));
    for (int i = 0; i < nb_sl; i++) {
        s_btn[i] = malloc(sizeof(sliding_button_t));
        s_btn[i]->line = create_draw(create_shape(RECT, sfBlack, sfBlack, 0),
            SHAPE, create_data(set_3vector(pos.x, pos.y + i * 70, 0),
            set_2vector(300, 10), 0));
        s_btn[i]->btn = set_button(all_btn, NULL,
            set_3vector(pos.x, pos.y + i * 70, 0), set_2vector(50, 40));
        s_btn[i]->btn->s_btn = s_btn[i];
        set_origin_draw(s_btn[i]->btn->rect, set_2vector(25, 20));
        s_btn[i]->min_value = value[0];
        s_btn[i]->max_value = value[1];
        s_btn[i]->value = &get_value_sliding_button;
    }
    s_btn[nb_sl] = NULL;
    return s_btn;
}
