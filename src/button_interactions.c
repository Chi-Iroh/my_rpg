/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** button_interactions.c
*/

#include "../include/my_rpg.h"
#include "../lib/my_graphics/my_graphics.h"

static void handle_button_click
(list_button_t* all_btn, sfMouseButtonEvent *event)
{
    static const sfColor color = {
        .r = 220,
        .g = 220,
        .b = 200,
        .a = 255
    };

    if (all_btn->btn->is_clicked(all_btn->btn, event)) {
        set_color_in_draw(all_btn->btn->rect, color);
    }
}

void button_pressed(window_t* wd, list_button_t* all_btn,
    sfMouseButtonEvent evt)
{
    while (all_btn != NULL) {
        if (all_btn->btn->layer_on->show && all_btn->btn->rect->show) {
            handle_button_click(all_btn, &evt);
        } else {
            all_btn->btn->state = NONE;
        }
        all_btn = all_btn->next;
    }
}

void sliding_button_moved(list_button_t* all_btn, sfMouseMoveEvent evt)
{
    while (all_btn != NULL) {
        if (all_btn->btn->s_btn && IS_PRESSED(all_btn->btn)) {
            move_sliding_button_btn(evt, all_btn->btn->s_btn);
        }
        all_btn = all_btn->next;
    }
}