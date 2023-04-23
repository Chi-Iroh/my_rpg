/*
** EPITECH PROJECT, 2022
** Untitled (Workspace)
** File description:
** init_g_src.c
*/

#include <my_rpg.h>
#include <my_graphics.h>

game_t* init_game(window_t* wd, list_button_t** btns, game_src_t* g_src)
{
    game_t* game = malloc(sizeof(game_t));
    bool status = true;

    RETURN_VALUE_IF(!game, NULL);
    status &= (game->pause_menu = init_pause_menu(wd, btns, g_src)) != NULL;
    status &= (game->stat_ui = init_stat_interface(wd->ui, btns)) != NULL;
    status &= (game->layer_fx = wd->fx) != NULL;
    status &= (game->all_weapons = init_all_weapons()) != NULL;
    game->list_bubbles = NULL;
    game->crowd = NULL;
    if (!status) {
        free_menu(g_src->menu);
    }
    return game;
}

game_src_t* init_game_sources(window_t* wd)
{
    game_src_t* g_src = malloc(sizeof(game_src_t));
    list_button_t* btns = NULL;
    g_src->menu = init_menu(wd, &btns);
    g_src->game = init_game(wd, &btns, g_src);
    g_src->game->pause_menu->pause_l->show = false;
    g_src->all_btn = btns;
    audio_init(&g_src->audio, AUDIO_DEFAULT_VOLUME);
    wd->splash->draw->next->show = false;
    wd->splash->draw->next->next->show = false;
    return g_src;
}
