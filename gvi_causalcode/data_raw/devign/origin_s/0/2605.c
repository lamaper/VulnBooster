static int xenfb_send_position(struct XenInput *xenfb,

			       int abs_x, int abs_y, int z)

{

    union xenkbd_in_event event;



    memset(&event, 0, XENKBD_IN_EVENT_SIZE);

    event.type = XENKBD_TYPE_POS;

    event.pos.abs_x = abs_x;

    event.pos.abs_y = abs_y;


    event.pos.abs_z = z;



    event.pos.rel_z = z;




    return xenfb_kbd_event(xenfb, &event);

}
