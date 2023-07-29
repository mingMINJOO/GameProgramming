#include "Game.h"
#include "GameHome.h"

Home::Home() {
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096);
    btn_sound = Mix_LoadWAV("../../Resources/Button_Sound.wav");

    //homeBgm
    home_bgm = Mix_LoadMUS("../../Resources/introBgm.mp3");;
    Mix_VolumeMusic(100); // 배경 음악 소리 볼륨

    Mix_FadeInMusic(home_bgm, -1, 2); // 소리 서서히 커지게


    // BackGround
    SDL_Surface* bg_surface = IMG_Load("../../Resources/bg_home.png");
    g_bg_texture = SDL_CreateTextureFromSurface(g_renderer, bg_surface);
    SDL_FreeSurface(bg_surface);

    g_bg_source_rect.x = 0;
    g_bg_source_rect.y = 0;
    g_bg_source_rect.w = 800;
    g_bg_source_rect.h = 600;

    g_bg_destination_rect.x = 0;
    g_bg_destination_rect.y = 0;
    g_bg_destination_rect.w = 800;
    g_bg_destination_rect.h = 600;

    // Mode1 Button
    {
        SDL_Surface* temp_surface = IMG_Load("../../Resources/Home_Mode1.png");
        texture_m1 = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
        SDL_FreeSurface(temp_surface);



        SDL_QueryTexture(texture_m1, NULL, NULL, &source_rectangle_m1.w, &source_rectangle_m1.h);
        destination_rectangle_m1.x = 35;
        destination_rectangle_m1.y = 90;
        source_rectangle_m1.x = 0;
        source_rectangle_m1.y = 0;

        destination_rectangle_m1.w = 220;
        destination_rectangle_m1.h = 420;
    }

    // Mode2 Button
    {
        SDL_Surface* temp_surface = IMG_Load("../../Resources/Home_Mode2.png");
        texture_m2 = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
        SDL_FreeSurface(temp_surface);

        SDL_QueryTexture(texture_m2, NULL, NULL, &source_rectangle_m2.w, &source_rectangle_m2.h);
        destination_rectangle_m2.x = 290;
        destination_rectangle_m2.y = 90;
        source_rectangle_m2.x = 0;
        source_rectangle_m2.y = 0;

        destination_rectangle_m2.w = 220;
        destination_rectangle_m2.h = 420;
    }

    // Mode3 Button
    {
        SDL_Surface* temp_surface = IMG_Load("../../Resources/Home_Mode3.png");
        texture_m3 = SDL_CreateTextureFromSurface(g_renderer, temp_surface);
        SDL_FreeSurface(temp_surface);

        SDL_QueryTexture(texture_m3, NULL, NULL, &source_rectangle_m3.w, &source_rectangle_m3.h);
        destination_rectangle_m3.x = 545;
        destination_rectangle_m3.y = 90;
        source_rectangle_m3.x = 0;
        source_rectangle_m3.y = 0;

        destination_rectangle_m3.w = 220;
        destination_rectangle_m3.h = 420;
    }
}

Home::~Home() {
    SDL_DestroyTexture(g_bg_texture);
    SDL_DestroyTexture(texture_m1);
    SDL_DestroyTexture(texture_m2);
    SDL_DestroyTexture(texture_m3);
    Mix_FreeMusic(home_bgm);
}

void Home::Update()
{

}

void Home::Render() {
    if (!Mix_PlayingMusic()) {
        Mix_VolumeMusic(100);
        Mix_PlayMusic(home_bgm, -1); // 무한반복
    }


    // Background
    SDL_RenderCopy(g_renderer, g_bg_texture, &g_bg_source_rect, &g_bg_destination_rect);

    // Mode1 Button
    SDL_RenderCopy(g_renderer, texture_m1, &source_rectangle_m1, &destination_rectangle_m1);

    // Mode2 Button
    SDL_RenderCopy(g_renderer, texture_m2, &source_rectangle_m2, &destination_rectangle_m2);

    // Mode3 Button
    SDL_RenderCopy(g_renderer, texture_m3, &source_rectangle_m3, &destination_rectangle_m3);


    SDL_RenderPresent(g_renderer);
}

void Home::HandleEvents() {

    SDL_Event event;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            g_flag_running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:

            // If the mouse left button is pressed. 
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;
                // Mix_FadeOutMusic(1000);
                Mix_HaltMusic();
                if (mouseX >= destination_rectangle_m1.x && mouseX < destination_rectangle_m1.x + destination_rectangle_m1.w
                    && mouseY >= destination_rectangle_m1.y && mouseY < destination_rectangle_m1.y + destination_rectangle_m1.h) {
                    //wav은 여기서 플레이
                    Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
                    Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기

                    g_current_game_phase = PHASE_MODE1;

                }
                if (mouseX >= destination_rectangle_m2.x && mouseX < destination_rectangle_m2.x + destination_rectangle_m2.w
                    && mouseY >= destination_rectangle_m2.y && mouseY < destination_rectangle_m2.y + destination_rectangle_m2.h) {

                    Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
                    Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기


                    g_current_game_phase = PHASE_MODE2;
                }
                if (mouseX >= destination_rectangle_m3.x && mouseX < destination_rectangle_m3.x + destination_rectangle_m3.w
                    && mouseY >= destination_rectangle_m3.y && mouseY < destination_rectangle_m3.y + destination_rectangle_m3.h) {
                    Mix_VolumeChunk(btn_sound, MIX_MAX_VOLUME);
                    Mix_PlayChannel(3, btn_sound, 0); //무한반복 안하기


                    g_current_game_phase = PHASE_MODE3;
                }

            }
            break;

        default:
            break;
        }
    }

}