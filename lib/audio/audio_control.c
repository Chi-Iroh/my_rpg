/*
** EPITECH PROJECT, 2023
** audio_control.c
** File description:
** -> Function for audio pause/play/stop.
*/

#include "audio.h"
#include "audio_play.h"

void (*bgm_functions[3])(sfMusic*) = {
    [AUDIO_PLAY] = sfMusic_play,
    [AUDIO_STOP] = sfMusic_stop,
    [AUDIO_PAUSE] = sfMusic_pause
};

void (*sfx_functions[3])(sfSound*) = {
    [AUDIO_PLAY] = sfSound_play,
    [AUDIO_STOP] = sfSound_stop,
    [AUDIO_PAUSE] = sfSound_pause
};

audio_play_t audio_control(audio_t *audio, audio_control_t action)
{
    audio_play_t changes = AUDIO_CHANGED_NOTHING;

    if (audio->current_bgm) {
        bgm_functions[action](audio->current_bgm);
        audio->bgm_state = (audio_state_t)action;
        changes |= AUDIO_CHANGED_BGM_ONLY;
    }
    if (audio->current_sfx) {
        sfx_functions[action](audio->current_sfx->sound);
        audio->sfx_state = (audio_state_t)action;
        changes |= AUDIO_CHANGED_SFX_ONLY;
    }
    return changes;
}