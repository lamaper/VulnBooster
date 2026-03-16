static void draw_digit(int digit, uint8_t *dst, unsigned dst_linesize,

                       unsigned segment_width)

{








    struct {

        int x, y, w, h;

    } segments[] = {

        { 1,  0, 5, 1 },  

        { 1,  6, 5, 1 },  

        { 1, 12, 5, 1 },  

        { 0,  1, 1, 5 },  

        { 0,  7, 1, 5 },  

        { 6,  1, 1, 5 },  

        { 6,  7, 1, 5 }   

    };

    static const unsigned char masks[10] = {

          TOP_HBAR         |BOT_HBAR|LEFT_TOP_VBAR|LEFT_BOT_VBAR|RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

                                                                 RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

          TOP_HBAR|MID_HBAR|BOT_HBAR|LEFT_BOT_VBAR                             |RIGHT_TOP_VBAR,

          TOP_HBAR|MID_HBAR|BOT_HBAR                            |RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

                   MID_HBAR         |LEFT_TOP_VBAR              |RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

          TOP_HBAR|BOT_HBAR|MID_HBAR|LEFT_TOP_VBAR                             |RIGHT_BOT_VBAR,

          TOP_HBAR|BOT_HBAR|MID_HBAR|LEFT_TOP_VBAR|LEFT_BOT_VBAR               |RIGHT_BOT_VBAR,

          TOP_HBAR                                              |RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

          TOP_HBAR|BOT_HBAR|MID_HBAR|LEFT_TOP_VBAR|LEFT_BOT_VBAR|RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

          TOP_HBAR|BOT_HBAR|MID_HBAR|LEFT_TOP_VBAR              |RIGHT_TOP_VBAR|RIGHT_BOT_VBAR,

    };

    unsigned mask = masks[digit];

    int i;



    draw_rectangle(0, dst, dst_linesize, segment_width, 0, 0, 8, 13);

    for (i = 0; i < FF_ARRAY_ELEMS(segments); i++)

        if (mask & (1<<i))

            draw_rectangle(255, dst, dst_linesize, segment_width,

                           segments[i].x, segments[i].y, segments[i].w, segments[i].h);

}
