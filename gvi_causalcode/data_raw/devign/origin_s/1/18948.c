static void pflash_write (pflash_t *pfl, target_ulong offset, uint32_t value,

                          int width)

{

    target_ulong boff;

    uint8_t *p;

    uint8_t cmd;



     

    if (pfl->wcycle == 0)

        offset -= (target_ulong)(long)pfl->storage;

    else

        offset -= pfl->base;

        

    cmd = value;

    DPRINTF("%s: offset " TARGET_FMT_lx " %08x %d\n", __func__,

            offset, value, width);

    if (pfl->cmd != 0xA0 && cmd == 0xF0) {

        DPRINTF("%s: flash reset asked (%02x %02x)\n",

                __func__, pfl->cmd, cmd);

        goto reset_flash;

    }

     

    cpu_register_physical_memory(pfl->base, pfl->total_len, pfl->fl_mem);

    boff = offset & (pfl->sector_len - 1);

    if (pfl->width == 2)

        boff = boff >> 1;

    else if (pfl->width == 4)

        boff = boff >> 2;

    switch (pfl->wcycle) {

    case 0:

         

    check_unlock0:

        if (boff == 0x55 && cmd == 0x98) {

        enter_CFI_mode:

             

            pfl->wcycle = 7;

            pfl->cmd = 0x98;

            return;

        }

        if (boff != 0x555 || cmd != 0xAA) {

            DPRINTF("%s: unlock0 failed " TARGET_FMT_lx " %02x %04x\n",

                    __func__, boff, cmd, 0x555);

            goto reset_flash;

        }

        DPRINTF("%s: unlock sequence started\n", __func__);

        break;

    case 1:

         

    check_unlock1:

        if (boff != 0x2AA || cmd != 0x55) {

            DPRINTF("%s: unlock1 failed " TARGET_FMT_lx " %02x\n", __func__,

                    boff, cmd);

            goto reset_flash;

        }

        DPRINTF("%s: unlock sequence done\n", __func__);

        break;

    case 2:

         

        if (!pfl->bypass && boff != 0x555) {

            DPRINTF("%s: command failed " TARGET_FMT_lx " %02x\n", __func__,

                    boff, cmd);

            goto reset_flash;

        }

        switch (cmd) {

        case 0x20:

            pfl->bypass = 1;

            goto do_bypass;

        case 0x80:

        case 0x90:

        case 0xA0:

            pfl->cmd = cmd;

            DPRINTF("%s: starting command %02x\n", __func__, cmd);

            break;

        default:

            DPRINTF("%s: unknown command %02x\n", __func__, cmd);

            goto reset_flash;

        }

        break;

    case 3:

        switch (pfl->cmd) {

        case 0x80:

             

            goto check_unlock0;

        case 0xA0:

            DPRINTF("%s: write data offset " TARGET_FMT_lx " %08x %d\n",

                    __func__, offset, value, width);

            p = pfl->storage;

            switch (width) {

            case 1:

                p[offset] &= value;

                pflash_update(pfl, offset, 1);

                break;

            case 2:


                p[offset] &= value >> 8;

                p[offset + 1] &= value;


                p[offset] &= value;

                p[offset + 1] &= value >> 8;


                pflash_update(pfl, offset, 2);

                break;

            case 4:


                p[offset] &= value >> 24;

                p[offset + 1] &= value >> 16;

                p[offset + 2] &= value >> 8;

                p[offset + 3] &= value;


                p[offset] &= value;

                p[offset + 1] &= value >> 8;

                p[offset + 2] &= value >> 16;

                p[offset + 3] &= value >> 24;


                pflash_update(pfl, offset, 4);

                break;

            }

            pfl->status = 0x00 | ~(value & 0x80);

             

            if (pfl->bypass)

                goto do_bypass;

            goto reset_flash;

        case 0x90:

            if (pfl->bypass && cmd == 0x00) {

                 

                goto reset_flash;

            }

             

            if (boff == 0x55 && cmd == 0x98)

                goto enter_CFI_mode;

             

        default:

            DPRINTF("%s: invalid write for command %02x\n",

                    __func__, pfl->cmd);

            goto reset_flash;

        }

    case 4:

        switch (pfl->cmd) {

        case 0xA0:

             

             

            return;

        case 0x80:

            goto check_unlock1;

        default:

             

            DPRINTF("%s: invalid command state %02x (wc 4)\n",

                    __func__, pfl->cmd);

            goto reset_flash;

        }

        break;

    case 5:

        switch (cmd) {

        case 0x10:

            if (boff != 0x555) {

                DPRINTF("%s: chip erase: invalid address " TARGET_FMT_lx "\n",

                        __func__, offset);

                goto reset_flash;

            }

             

            DPRINTF("%s: start chip erase\n", __func__);

            memset(pfl->storage, 0xFF, pfl->total_len);

            pfl->status = 0x00;

            pflash_update(pfl, 0, pfl->total_len);

             

            qemu_mod_timer(pfl->timer, 

                           qemu_get_clock(vm_clock) + (ticks_per_sec * 5));

            break;

        case 0x30:

             

            p = pfl->storage;

            offset &= ~(pfl->sector_len - 1);

            DPRINTF("%s: start sector erase at " TARGET_FMT_lx "\n", __func__,

                    offset);

            memset(p + offset, 0xFF, pfl->sector_len);

            pflash_update(pfl, offset, pfl->sector_len);

            pfl->status = 0x00;

             

            qemu_mod_timer(pfl->timer, 

                           qemu_get_clock(vm_clock) + (ticks_per_sec / 2));

            break;

        default:

            DPRINTF("%s: invalid command %02x (wc 5)\n", __func__, cmd);

            goto reset_flash;

        }

        pfl->cmd = cmd;

        break;

    case 6:

        switch (pfl->cmd) {

        case 0x10:

             

            return;

        case 0x30:

             

            return;

        default:

             

            DPRINTF("%s: invalid command state %02x (wc 6)\n",

                    __func__, pfl->cmd);

            goto reset_flash;

        }

        break;

    case 7:  

        DPRINTF("%s: invalid write in CFI query mode\n", __func__);

        goto reset_flash;

    default:

         

        DPRINTF("%s: invalid write state (wc 7)\n",  __func__);

        goto reset_flash;

    }

    pfl->wcycle++;



    return;



     

 reset_flash:

    if (pfl->wcycle != 0) {

        cpu_register_physical_memory(pfl->base, pfl->total_len,

                                     pfl->off | IO_MEM_ROMD | pfl->fl_mem);

    }

    pfl->bypass = 0;

    pfl->wcycle = 0;

    pfl->cmd = 0;

    return;



 do_bypass:

    pfl->wcycle = 2;

    pfl->cmd = 0;

    return;

}
