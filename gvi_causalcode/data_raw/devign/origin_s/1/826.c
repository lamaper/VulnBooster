static void console_putchar(TextConsole *s, int ch)

{

    TextCell *c;

    int y1, i;

    int x, y;



    switch(s->state) {

    case TTY_STATE_NORM:

        switch(ch) {

        case '\r':   

            s->x = 0;

            break;

        case '\n':   

            console_put_lf(s);

            break;

        case '\b':   

            if (s->x > 0)

                s->x--;

            break;

        case '\t':   

            if (s->x + (8 - (s->x % 8)) > s->width) {

                s->x = 0;

                console_put_lf(s);

            } else {

                s->x = s->x + (8 - (s->x % 8));

            }

            break;

        case '\a':   

             

            break;

        case 14:

             

            break;

        case 15:

             

            break;

        case 27:     

            s->state = TTY_STATE_ESC;

            break;

        default:

            if (s->x >= s->width) {

                 

                s->x = 0;

                console_put_lf(s);

            }

            y1 = (s->y_base + s->y) % s->total_height;

            c = &s->cells[y1 * s->width + s->x];

            c->ch = ch;

            c->t_attrib = s->t_attrib;

            update_xy(s, s->x, s->y);

            s->x++;

            break;

        }

        break;

    case TTY_STATE_ESC:  

        if (ch == '[') {

            for(i=0;i<MAX_ESC_PARAMS;i++)

                s->esc_params[i] = 0;

            s->nb_esc_params = 0;

            s->state = TTY_STATE_CSI;

        } else {

            s->state = TTY_STATE_NORM;

        }

        break;

    case TTY_STATE_CSI:  

        if (ch >= '0' && ch <= '9') {

            if (s->nb_esc_params < MAX_ESC_PARAMS) {

                s->esc_params[s->nb_esc_params] =

                    s->esc_params[s->nb_esc_params] * 10 + ch - '0';

            }

        } else {

            s->nb_esc_params++;

            if (ch == ';')

                break;


            fprintf(stderr, "escape sequence CSI%d;%d%c, %d parameters\n",

                    s->esc_params[0], s->esc_params[1], ch, s->nb_esc_params);


            s->state = TTY_STATE_NORM;

            switch(ch) {

            case 'A':

                 

                if (s->esc_params[0] == 0) {

                    s->esc_params[0] = 1;

                }

                s->y -= s->esc_params[0];

                if (s->y < 0) {

                    s->y = 0;

                }

                break;

            case 'B':

                 

                if (s->esc_params[0] == 0) {

                    s->esc_params[0] = 1;

                }

                s->y += s->esc_params[0];

                if (s->y >= s->height) {

                    s->y = s->height - 1;

                }

                break;

            case 'C':

                 

                if (s->esc_params[0] == 0) {

                    s->esc_params[0] = 1;

                }

                s->x += s->esc_params[0];

                if (s->x >= s->width) {

                    s->x = s->width - 1;

                }

                break;

            case 'D':

                 

                if (s->esc_params[0] == 0) {

                    s->esc_params[0] = 1;

                }

                s->x -= s->esc_params[0];

                if (s->x < 0) {

                    s->x = 0;

                }

                break;

            case 'G':

                 

                s->x = s->esc_params[0] - 1;

                if (s->x < 0) {

                    s->x = 0;

                }

                break;

            case 'f':

            case 'H':

                 

                s->x = s->esc_params[1] - 1;

                if (s->x < 0) {

                    s->x = 0;

                }

                s->y = s->esc_params[0] - 1;

                if (s->y < 0) {

                    s->y = 0;

                }

                break;

            case 'J':

                switch (s->esc_params[0]) {

                case 0:

                     

                    for (y = s->y; y < s->height; y++) {

                        for (x = 0; x < s->width; x++) {

                            if (y == s->y && x < s->x) {

                                continue;

                            }

                            console_clear_xy(s, x, y);

                        }

                    }

                    break;

                case 1:

                     

                    for (y = 0; y <= s->y; y++) {

                        for (x = 0; x < s->width; x++) {

                            if (y == s->y && x > s->x) {

                                break;

                            }

                            console_clear_xy(s, x, y);

                        }

                    }

                    break;

                case 2:

                     

                    for (y = 0; y <= s->height; y++) {

                        for (x = 0; x < s->width; x++) {

                            console_clear_xy(s, x, y);

                        }

                    }

                    break;

                }

                break;

            case 'K':

                switch (s->esc_params[0]) {

                case 0:

                     

                    for(x = s->x; x < s->width; x++) {

                        console_clear_xy(s, x, s->y);

                    }

                    break;

                case 1:

                     

                    for (x = 0; x <= s->x; x++) {

                        console_clear_xy(s, x, s->y);

                    }

                    break;

                case 2:

                     

                    for(x = 0; x < s->width; x++) {

                        console_clear_xy(s, x, s->y);

                    }

                    break;

                }

                break;

            case 'm':

                console_handle_escape(s);

                break;

            case 'n':

                 

                 

                break;

            case 's':

                 

                s->x_saved = s->x;

                s->y_saved = s->y;

                break;

            case 'u':

                 

                s->x = s->x_saved;

                s->y = s->y_saved;

                break;

            default:


                fprintf(stderr, "unhandled escape character '%c'\n", ch);


                break;

            }

            break;

        }

    }

}
