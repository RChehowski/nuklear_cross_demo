
#define NKCD NKC_GLFW

#include "nuklear_cross.h"
#include <stdio.h>

const int WindowW = 600;
const int WindowH = 100;

enum radioOptions {
    EASY,
    HARD
};

struct my_nkc_app {
    struct nkc* nkcHandle;

    /* some user data */
    float value;
    enum radioOptions op;
};

void mainLoop(void* loopArg)
{
    struct my_nkc_app* myapp = (struct my_nkc_app*)loopArg;
    struct nk_context *ctx = nkc_get_ctx(myapp->nkcHandle);

    union nkc_event e = nkc_poll_events(myapp->nkcHandle);

    if((e.type == NKC_EWINDOW) && (e.window.param == NKC_EQUIT) )
    {
        nkc_stop_main_loop(myapp->nkcHandle);
    }

    static const int border_padding = 5;

    static struct nk_rect rect = nk_rect(
        border_padding,
        border_padding,
        WindowW - (2 * border_padding),
        WindowH - (2 * border_padding)
    );

//    struct nk_rect rect1 = nk_window_get_bounds(ctx);
//    printf("%f x %f", rect1.h, rect1.w);


    /* Nuklear GUI code */
    if (nk_begin(ctx, "Show", rect, NK_WINDOW_BORDER))
    {
        nk_layout_row_static(ctx, 20, 0, 1);
//        nk_layout_set_min_row_height(ctx, 0);


        static const float ratio_two[] = {0.85f, 0.15f};
        nk_layout_row(ctx, NK_DYNAMIC, 30, 2, ratio_two);



        static size_t prog = 40;
        nk_progress(ctx, &prog, 100, NK_MODIFIABLE);



        nk_style_button button_style = ctx->style.button;
        button_style.padding = nk_vec2(.0f, .0f);

        if (nk_button_label_styled(ctx, &button_style, "Cancel"))
        {
            printf("Installation Canceled\n");
            nkc_stop_main_loop(myapp->nkcHandle);
        }
    }

    nk_end(ctx);

    nkc_render(myapp->nkcHandle, nk_rgb(40, 40, 40));
}

int main(){
    struct my_nkc_app myapp;
    struct nkc nkcx; /* Allocate memory for Nuklear+ handle */
    myapp.nkcHandle = &nkcx;

    /* init some user data */
    myapp.value = 0.4;
    myapp.op = HARD;

    if (nkc_init(myapp.nkcHandle, "Installing", WindowW, WindowH, NKC_WIN_NORMAL))
    {
        printf("Successfull init. Starting 'infinite' main loop...\n");
        nkc_set_main_loop(myapp.nkcHandle, mainLoop, (void*)&myapp );
    }
    else
    {
        printf("Can't init NKC\n");
    }

    printf("Value after exit = %f\n", myapp.value);
    nkc_shutdown( myapp.nkcHandle );
    return 0;
}