static int wm8750_event(I2CSlave *i2c, enum i2c_event event)

{

    WM8750State *s = WM8750(i2c);



    switch (event) {

    case I2C_START_SEND:

        s->i2c_len = 0;

        break;

    case I2C_FINISH:


        if (s->i2c_len < 2)

            printf("%s: message too short (%i bytes)\n",

                            __FUNCTION__, s->i2c_len);


        break;

    default:

        break;

    }



    return 0;

}
