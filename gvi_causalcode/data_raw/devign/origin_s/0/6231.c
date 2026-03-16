void curses_display_init(DisplayState *ds, int full_screen)

{


    if (!isatty(1)) {

        fprintf(stderr, "We need a terminal output\n");

        exit(1);

    }




    curses_setup();

    curses_keyboard_setup();

    atexit(curses_atexit);


    signal(SIGINT, SIG_DFL);

    signal(SIGQUIT, SIG_DFL);


     

    signal(SIGWINCH, curses_winch_handler);





    ds->data = (void *) screen;

    ds->linesize = 0;

    ds->depth = 0;

    ds->width = 640;

    ds->height = 400;

    ds->dpy_update = curses_update;

    ds->dpy_resize = curses_resize;

    ds->dpy_refresh = curses_refresh;

    ds->dpy_text_cursor = curses_cursor_position;



    invalidate = 1;



     

    curses_resize(ds, 80, 25);

}
