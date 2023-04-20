/*
** EPITECH PROJECT, 2023
** audio_init_free.c
** File description:
** -> Initializes audio and sound structures.
*/

#include <my_macros.h>
#include "audio.h"
#include "audio_path.h"

const float DONT_CHANGE_VOLUME = -1.f;
const float DEFAULT_BGM_VOLUME = 75.f;
const float DEFAULT_SFX_VOLUME = 100.f;

/*
    audio is always valid (not NULL)
*/
static void init_pointers_and_volume
(audio_t *audio, float bgm_volume, float sfx_volume)
{
    const float bgm_volumes[2] = { DEFAULT_BGM_VOLUME, bgm_volume };
    const float sfx_volumes[2] = { DEFAULT_SFX_VOLUME, sfx_volume };

    *audio = (audio_t) {
        .battle_bgm = NULL,
        .bgm = NULL,
        .boss_bgm = NULL,
        .menu_bgm = NULL,
        .quest_sfx = { .buffer = NULL, .sound = NULL },
        .explosion_sfx = { .buffer = NULL, .sound = NULL },
        .current_bgm = NULL,
        .current_sfx = NULL,
        .bgm_volume = bgm_volumes[is_volume_ok(bgm_volume)],
        .bgm_state = AUDIO_NOT_YET_STARTED,
        .sfx_volume = sfx_volumes[is_volume_ok(sfx_volume)],
        .sfx_state = AUDIO_NOT_YET_STARTED
    };
}

/*
    Any value of volume not in [0;100] won't change the volume.
*/
static bool init_sfx(sound_t *sound, const char *path, float volume)
{
    RETURN_VALUE_IF(!sound || !path, false);
    sound->buffer = sfSoundBuffer_createFromFile(path);
    sound->sound = sfSound_create();
    if (!sound->buffer || !sound->sound) {
        free_sfx(sound);
        return false;
    }
    sfSound_setBuffer(sound->sound, sound->buffer);
    return true;
}

/*
    Any value of volume not in [0;100] won't change the volume.
*/
static bool init_bgm(sfMusic **bgm, const char *path, float bgm_volume)
{
    RETURN_VALUE_IF(!bgm || !path, false);
    *bgm = sfMusic_createFromFile(path);
    RETURN_VALUE_IF(!(*bgm), false);
    return true;
}

/*
    Properly initialized an audio_t structure.
    For both bgm_volume and sfx_volume:
        -> Any value of volume not in [0;100] won't change the volume.
    Frees all that has been initializes if initialization cannot finish.
*/
bool init_audio(audio_t *audio, float bgm_volume, float sfx_volume)
{
    bool status = audio != NULL;

    RETURN_VALUE_IF(!status, false);
    init_pointers_and_volume(audio, bgm_volume, sfx_volume);
    status &= init_bgm(&audio->menu_bgm, MENU_BGM_PATH, bgm_volume);
    status &= init_sfx(&audio->quest_sfx, QUEST_SFX_PATH, sfx_volume);
    if (!status) {
        free_audio(audio);
        return false;
    }
    audio->current_bgm = audio->menu_bgm;
    audio->current_sfx = &audio->quest_sfx;
    update_volume(audio);
    return true;
}