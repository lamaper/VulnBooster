static void blizzard_reg_write(void *opaque, uint8_t reg, uint16_t value)

{

    BlizzardState *s = (BlizzardState *) opaque;



    switch (reg) {

    case 0x04:	 

        s->pll = (value & 0x3f) + 1;

        break;

    case 0x06:	 

        s->pll_range = value & 3;

        break;

    case 0x08:	 

        s->pll_ctrl &= 0xf00;

        s->pll_ctrl |= (value << 0) & 0x0ff;

        break;

    case 0x0a:	 

        s->pll_ctrl &= 0x0ff;

        s->pll_ctrl |= (value << 8) & 0xf00;

        break;

    case 0x0c:	 

        s->pll_mode = value & 0x77;

        if ((value & 3) == 0 || (value & 3) == 3)

            fprintf(stderr, "%s: wrong PLL Control bits (%i)\n",

                    __FUNCTION__, value & 3);

        break;



    case 0x0e:	 

        s->clksel = value & 0xff;

        break;



    case 0x10:	 

        s->memenable = value & 1;

        break;

    case 0x14:	 

        break;



    case 0x18:	 

        s->memrefresh &= 0xf00;

        s->memrefresh |= (value << 0) & 0x0ff;

        break;

    case 0x1a:	 

        s->memrefresh &= 0x0ff;

        s->memrefresh |= (value << 8) & 0xf00;

        break;



    case 0x1c:	 

        s->timing[0] = value & 0x7f;

        break;

    case 0x1e:	 

        s->timing[1] = value & 0x17;

        break;

    case 0x20:	 

        s->timing[2] = value & 0x35;

        break;



    case 0x24:	 

        s->priority = value & 1;

        break;



    case 0x28:	 

        s->lcd_config = value & 0xff;

        if (value & (1 << 7))

            fprintf(stderr, "%s: data swap not supported!\n", __FUNCTION__);

        break;



    case 0x2a:	 

        s->x = value << 3;

        break;

    case 0x2c:	 

        s->hndp = value & 0xff;

        break;

    case 0x2e:	 

        s->y &= 0x300;

        s->y |= (value << 0) & 0x0ff;

        break;

    case 0x30:	 

        s->y &= 0x0ff;

        s->y |= (value << 8) & 0x300;

        break;

    case 0x32:	 

        s->vndp = value & 0xff;

        break;

    case 0x34:	 

        s->hsync = value & 0xff;

        break;

    case 0x36:	 

        s->skipx = value & 0xff;

        break;

    case 0x38:	 

        s->vsync = value & 0xbf;

        break;

    case 0x3a:	 

        s->skipy = value & 0xff;

        break;



    case 0x3c:	 

        s->pclk = value & 0x82;

         

        break;



    case 0x3e:	 

        s->hssi_config[0] = value;

        break;

    case 0x40:	 

        s->hssi_config[1] = value;

        if (((value >> 4) & 3) == 3)

            fprintf(stderr, "%s: Illegal active-data-links value\n",

                            __FUNCTION__);

        break;

    case 0x42:	 

        s->hssi_config[2] = value & 0xbd;

        break;



    case 0x44:	 

        s->tv_config = value & 0xfe;

        break;

    case 0x46 ... 0x4c:	 

        s->tv_timing[(reg - 0x46) >> 1] = value;

        break;

    case 0x4e:	 

        s->vbi = value;

        break;

    case 0x50:	 

        s->tv_x = value;

        break;

    case 0x52:	 

        s->tv_y = value & 0x7f;

        break;

    case 0x54:	 

        s->tv_test = value;

        break;

    case 0x56:	 

        s->tv_filter_config = value & 0xbf;

        break;

    case 0x58:	 

        s->tv_filter_idx = value & 0x1f;

        break;

    case 0x5a:	 

        if (s->tv_filter_idx < 0x20)

            s->tv_filter_coeff[s->tv_filter_idx ++] = value;

        break;



    case 0x60:	 

        s->yrc[0] = value & 0xb0;

        break;

    case 0x62:	 

        s->yrc[1] = value & 0x30;

        break;

    case 0x64:	 

        s->u = value & 0xff;

        break;

    case 0x66:	 

        s->v = value & 0xff;

        break;



    case 0x68:	 

        if ((s->mode ^ value) & 3)

            s->invalidate = 1;

        s->mode = value & 0xb7;

        s->enable = value & 1;

        s->blank = (value >> 1) & 1;

        if (value & (1 << 4))

            fprintf(stderr, "%s: Macrovision enable attempt!\n", __FUNCTION__);

        break;



    case 0x6a:	 

        s->effect = value & 0xfb;

        break;



    case 0x6c:	 

        s->ix[0] &= 0x300;

        s->ix[0] |= (value << 0) & 0x0ff;

        break;

    case 0x6e:	 

        s->ix[0] &= 0x0ff;

        s->ix[0] |= (value << 8) & 0x300;

        break;

    case 0x70:	 

        s->iy[0] &= 0x300;

        s->iy[0] |= (value << 0) & 0x0ff;

        break;

    case 0x72:	 

        s->iy[0] &= 0x0ff;

        s->iy[0] |= (value << 8) & 0x300;

        break;

    case 0x74:	 

        s->ix[1] &= 0x300;

        s->ix[1] |= (value << 0) & 0x0ff;

        break;

    case 0x76:	 

        s->ix[1] &= 0x0ff;

        s->ix[1] |= (value << 8) & 0x300;

        break;

    case 0x78:	 

        s->iy[1] &= 0x300;

        s->iy[1] |= (value << 0) & 0x0ff;

        break;

    case 0x7a:	 

        s->iy[1] &= 0x0ff;

        s->iy[1] |= (value << 8) & 0x300;

        break;

    case 0x7c:	 

        s->ox[0] &= 0x300;

        s->ox[0] |= (value << 0) & 0x0ff;

        break;

    case 0x7e:	 

        s->ox[0] &= 0x0ff;

        s->ox[0] |= (value << 8) & 0x300;

        break;

    case 0x80:	 

        s->oy[0] &= 0x300;

        s->oy[0] |= (value << 0) & 0x0ff;

        break;

    case 0x82:	 

        s->oy[0] &= 0x0ff;

        s->oy[0] |= (value << 8) & 0x300;

        break;

    case 0x84:	 

        s->ox[1] &= 0x300;

        s->ox[1] |= (value << 0) & 0x0ff;

        break;

    case 0x86:	 

        s->ox[1] &= 0x0ff;

        s->ox[1] |= (value << 8) & 0x300;

        break;

    case 0x88:	 

        s->oy[1] &= 0x300;

        s->oy[1] |= (value << 0) & 0x0ff;

        break;

    case 0x8a:	 

        s->oy[1] &= 0x0ff;

        s->oy[1] |= (value << 8) & 0x300;

        break;



    case 0x8c:	 

        s->iformat = value & 0xf;

        s->bpp = blizzard_iformat_bpp[s->iformat];

        if (!s->bpp)

            fprintf(stderr, "%s: Illegal or unsupported input format %x\n",

                            __FUNCTION__, s->iformat);

        break;

    case 0x8e:	 

        s->source = value & 7;

         

        if ((!(s->effect & (1 << 3)) && (s->ix[0] != s->ox[0] ||

                                        s->iy[0] != s->oy[0] ||

                                        s->ix[1] != s->ox[1] ||

                                        s->iy[1] != s->oy[1])) ||

                        !((s->ix[1] - s->ix[0]) & (s->iy[1] - s->iy[0]) &

                          (s->ox[1] - s->ox[0]) & (s->oy[1] - s->oy[0]) & 1))

            fprintf(stderr, "%s: Illegal input/output window positions\n",

                            __FUNCTION__);



        blizzard_transfer_setup(s);

        break;



    case 0x90:	 

        if (!s->data.len && !blizzard_transfer_setup(s))

            break;



        *s->data.ptr ++ = value;

        if (-- s->data.len == 0)

            blizzard_window(s);

        break;



    case 0xa8:	 

        s->border_r = value;

        break;

    case 0xaa:	 

        s->border_g = value;

        break;

    case 0xac:	 

        s->border_b = value;

        break;



    case 0xb4:	 

        s->gamma_config = value & 0x87;

        break;

    case 0xb6:	 

        s->gamma_idx = value;

        break;

    case 0xb8:	 

        s->gamma_lut[s->gamma_idx ++] = value;

        break;



    case 0xba:	 

        s->matrix_ena = value & 1;

        break;

    case 0xbc ... 0xde:	 

        s->matrix_coeff[(reg - 0xbc) >> 1] = value & ((reg & 2) ? 0x80 : 0xff);

        break;

    case 0xe0:	 

        s->matrix_r = value;

        break;

    case 0xe2:	 

        s->matrix_g = value;

        break;

    case 0xe4:	 

        s->matrix_b = value;

        break;



    case 0xe6:	 

        s->pm = value & 0x83;

        if (value & s->mode & 1)

            fprintf(stderr, "%s: The display must be disabled before entering "

                            "Standby Mode\n", __FUNCTION__);

        break;

    case 0xe8:	 

        s->status = value & 0x1b;

        break;

    case 0xea:	 

        s->rgbgpio_dir = value & 0x8f;

        break;

    case 0xec:	 

        s->rgbgpio = value & 0xcf;

        break;

    case 0xee:	 

        s->gpio_dir = value;

        break;

    case 0xf0:	 

        s->gpio = value;

        break;

    case 0xf2:	 

        s->gpio_edge[0] = value;

        break;

    case 0xf4:	 

        s->gpio_edge[1] = value;

        break;

    case 0xf6:	 

        s->gpio_irq &= value;

        break;

    case 0xf8:	 

        s->gpio_pdown = value;

        break;



    default:

        fprintf(stderr, "%s: unknown register %02x\n", __FUNCTION__, reg);

        break;

    }

}
