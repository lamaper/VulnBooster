static uint32_t mipid_txrx(void *opaque, uint32_t cmd, int len)

{

    struct mipid_s *s = (struct mipid_s *) opaque;

    uint8_t ret;



    if (len > 9) {

        hw_error("%s: FIXME: bad SPI word width %i\n", __FUNCTION__, len);

    }



    if (s->p >= ARRAY_SIZE(s->resp)) {

        ret = 0;

    } else {

        ret = s->resp[s->p++];

    }

    if (s->pm-- > 0) {

        s->param[s->pm] = cmd;

    } else {

        s->cmd = cmd;

    }



    switch (s->cmd) {

    case 0x00:	 

        break;



    case 0x01:	 

        mipid_reset(s);

        break;



    case 0x02:	 

        s->booster = 0;

        break;

    case 0x03:	 

        s->booster = 1;

        break;



    case 0x04:	 

        s->p = 0;

        s->resp[0] = (s->id >> 16) & 0xff;

        s->resp[1] = (s->id >>  8) & 0xff;

        s->resp[2] = (s->id >>  0) & 0xff;

        break;



    case 0x06:	 

    case 0x07:	 

         

    case 0x08:	 

        s->p = 0;

         

        s->resp[0] = 0x01;

        break;



    case 0x09:	 

        s->p = 0;

        s->resp[0] = s->booster << 7;

        s->resp[1] = (5 << 4) | (s->partial << 2) |

                (s->sleep << 1) | s->normal;

        s->resp[2] = (s->vscr << 7) | (s->invert << 5) |

                (s->onoff << 2) | (s->te << 1) | (s->gamma >> 2);

        s->resp[3] = s->gamma << 6;

        break;



    case 0x0a:	 

        s->p = 0;

        s->resp[0] = (s->onoff << 2) | (s->normal << 3) | (s->sleep << 4) |

                (s->partial << 5) | (s->sleep << 6) | (s->booster << 7);

        break;

    case 0x0b:	 

        s->p = 0;

        s->resp[0] = 0;

        break;

    case 0x0c:	 

        s->p = 0;

        s->resp[0] = 5;	 

        break;

    case 0x0d:	 

        s->p = 0;

        s->resp[0] = (s->invert << 5) | (s->vscr << 7) | s->gamma;

        break;

    case 0x0e:	 

        s->p = 0;

        s->resp[0] = s->te << 7;

        break;

    case 0x0f:	 

        s->p = 0;

        s->resp[0] = s->selfcheck;

        break;



    case 0x10:	 

        s->sleep = 1;

        break;

    case 0x11:	 

        s->sleep = 0;

        s->selfcheck ^= 1 << 6;	 

        break;



    case 0x12:	 

        s->partial = 1;

        s->normal = 0;

        s->vscr = 0;

        break;

    case 0x13:	 

        s->partial = 0;

        s->normal = 1;

        s->vscr = 0;

        break;



    case 0x20:	 

        s->invert = 0;

        break;

    case 0x21:	 

        s->invert = 1;

        break;



    case 0x22:	 

    case 0x23:	 

        goto bad_cmd;



    case 0x25:	 

        if (s->pm < 0) {

            s->pm = 1;

        }

        goto bad_cmd;



    case 0x26:	 

        if (!s->pm) {

            s->gamma = ctz32(s->param[0] & 0xf);

            if (s->gamma == 32) {

                s->gamma = -1;  

            }

        } else if (s->pm < 0) {

            s->pm = 1;

        }

        break;



    case 0x28:	 

        s->onoff = 0;

        break;

    case 0x29:	 

        s->onoff = 1;

        break;



    case 0x2a:	 

    case 0x2b:	 

    case 0x2c:	 

    case 0x2d:	 

    case 0x2e:	 

    case 0x30:	 

    case 0x33:	 

        goto bad_cmd;



    case 0x34:	 

        s->te = 0;

        break;

    case 0x35:	 

        if (!s->pm) {

            s->te = 1;

        } else if (s->pm < 0) {

            s->pm = 1;

        }

        break;



    case 0x36:	 

        goto bad_cmd;



    case 0x37:	 

        s->partial = 0;

        s->normal = 0;

        s->vscr = 1;

        break;



    case 0x38:	 

    case 0x39:	 

    case 0x3a:	 

        goto bad_cmd;



    case 0xb0:	 

    case 0xb1:	 

        if (s->pm < 0) {

            s->pm = 2;

        }

        break;



    case 0xb4:	 

        break;



    case 0xb5:	 

    case 0xb6:	 

    case 0xb7:	 

    case 0xb8:	 

    case 0xba:	 

    case 0xbb:	 

        goto bad_cmd;



    case 0xbd:	 

        s->p = 0;

        s->resp[0] = 0;

        s->resp[1] = 1;

        break;



    case 0xc2:	 

        if (s->pm < 0) {

            s->pm = 2;

        }

        break;



    case 0xc6:	 

    case 0xc7:	 

    case 0xd0:	 

    case 0xd1:	 

    case 0xd4:	 

    case 0xd5:	 

        goto bad_cmd;



    case 0xda:	 

        s->p = 0;

        s->resp[0] = (s->id >> 16) & 0xff;

        break;

    case 0xdb:	 

        s->p = 0;

        s->resp[0] = (s->id >>  8) & 0xff;

        break;

    case 0xdc:	 

        s->p = 0;

        s->resp[0] = (s->id >>  0) & 0xff;

        break;



    default:

    bad_cmd:

        qemu_log_mask(LOG_GUEST_ERROR,

                      "%s: unknown command %02x\n", __func__, s->cmd);

        break;

    }



    return ret;

}
