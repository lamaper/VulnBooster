static sd_rsp_type_t sd_normal_command(SDState *sd,
                                       SDRequest req)
{
    uint32_t rca = 0x0000;
    uint64_t addr = (sd->ocr & (1 << 30)) ? (uint64_t) req.arg << 9 : req.arg;
    if (sd_cmd_type[req.cmd] == sd_ac || sd_cmd_type[req.cmd] == sd_adtc)
        rca = req.arg >> 16;
    DPRINTF("CMD%d 0x%08x state %d\n", req.cmd, req.arg, sd->state);
    switch (req.cmd) {
     
    case 0:	 
        switch (sd->state) {
        case sd_inactive_state:
            return sd->spi ? sd_r1 : sd_r0;
        default:
            sd->state = sd_idle_state;
            sd_reset(sd, sd->bdrv);
            return sd->spi ? sd_r1 : sd_r0;
        }
        break;
    case 1:	 
        if (!sd->spi)
            goto bad_cmd;
        sd->state = sd_transfer_state;
        return sd_r1;
    case 2:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_ready_state:
            sd->state = sd_identification_state;
            return sd_r2_i;
        default:
            break;
        }
        break;
    case 3:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_identification_state:
        case sd_standby_state:
            sd->state = sd_standby_state;
            sd_set_rca(sd);
            return sd_r6;
        default:
            break;
        }
        break;
    case 4:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_standby_state:
            break;
        default:
            break;
        }
        break;
    case 5:  
    case 6:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->mode) {
        case sd_data_transfer_mode:
            sd_function_switch(sd, req.arg);
            sd->state = sd_sendingdata_state;
            sd->data_start = 0;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
    case 7:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_standby_state:
            if (sd->rca != rca)
            sd->state = sd_transfer_state;
            return sd_r1b;
        case sd_transfer_state:
        case sd_sendingdata_state:
            if (sd->rca == rca)
                break;
            sd->state = sd_standby_state;
            return sd_r1b;
        case sd_disconnect_state:
            if (sd->rca != rca)
            sd->state = sd_programming_state;
            return sd_r1b;
        case sd_programming_state:
            if (sd->rca == rca)
                break;
            sd->state = sd_disconnect_state;
            return sd_r1b;
        default:
            break;
        }
        break;
    case 8:	 
         
        switch (sd->state) {
        case sd_idle_state:
            sd->vhs = 0;
             
            if (!(req.arg >> 8) || (req.arg >> ffs(req.arg & ~0xff)))
                return sd->spi ? sd_r7 : sd_r0;
             
            sd->vhs = req.arg;
            return sd_r7;
        default:
            break;
        }
        break;
    case 9:	 
        switch (sd->state) {
        case sd_standby_state:
            if (sd->rca != rca)
            return sd_r2_s;
        case sd_transfer_state:
            if (!sd->spi)
                break;
            sd->state = sd_sendingdata_state;
            memcpy(sd->data, sd->csd, 16);
            sd->data_start = addr;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
    case 10:	 
        switch (sd->state) {
        case sd_standby_state:
            if (sd->rca != rca)
            return sd_r2_i;
        case sd_transfer_state:
            if (!sd->spi)
                break;
            sd->state = sd_sendingdata_state;
            memcpy(sd->data, sd->cid, 16);
            sd->data_start = addr;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
    case 11:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_sendingdata_state;
            sd->data_start = req.arg;
            sd->data_offset = 0;
            if (sd->data_start + sd->blk_len > sd->size)
                sd->card_status |= ADDRESS_ERROR;
        default:
            break;
        }
        break;
    case 12:	 
        switch (sd->state) {
        case sd_sendingdata_state:
            sd->state = sd_transfer_state;
            return sd_r1b;
        case sd_receivingdata_state:
            sd->state = sd_programming_state;
             
            sd->state = sd_transfer_state;
            return sd_r1b;
        default:
            break;
        }
        break;
    case 13:	 
        switch (sd->mode) {
        case sd_data_transfer_mode:
            if (sd->rca != rca)
            return sd_r1;
        default:
            break;
        }
        break;
    case 15:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->mode) {
        case sd_data_transfer_mode:
            if (sd->rca != rca)
            sd->state = sd_inactive_state;
        default:
            break;
        }
        break;
     
    case 16:	 
        switch (sd->state) {
        case sd_transfer_state:
            if (req.arg > (1 << HWBLOCK_SHIFT))
                sd->card_status |= BLOCK_LEN_ERROR;
            else
                sd->blk_len = req.arg;
            return sd_r1;
        default:
            break;
        }
        break;
    case 17:	 
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_sendingdata_state;
            sd->data_start = addr;
            sd->data_offset = 0;
            if (sd->data_start + sd->blk_len > sd->size)
                sd->card_status |= ADDRESS_ERROR;
            return sd_r1;
        default:
            break;
        }
        break;
    case 18:	 
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_sendingdata_state;
            sd->data_start = addr;
            sd->data_offset = 0;
            if (sd->data_start + sd->blk_len > sd->size)
                sd->card_status |= ADDRESS_ERROR;
            return sd_r1;
        default:
            break;
        }
        break;
     
    case 24:	 
        if (sd->spi)
            goto unimplemented_cmd;
        switch (sd->state) {
        case sd_transfer_state:
             
            if (sd->spi)
                break;
            sd->state = sd_receivingdata_state;
            sd->data_start = addr;
            sd->data_offset = 0;
            sd->blk_written = 0;
            if (sd->data_start + sd->blk_len > sd->size)
                sd->card_status |= ADDRESS_ERROR;
            if (sd_wp_addr(sd, sd->data_start))
                sd->card_status |= WP_VIOLATION;
            if (sd->csd[14] & 0x30)
                sd->card_status |= WP_VIOLATION;
            return sd_r1;
        default:
            break;
        }
        break;
    case 25:	 
        if (sd->spi)
            goto unimplemented_cmd;
        switch (sd->state) {
        case sd_transfer_state:
             
            if (sd->spi)
                break;
            sd->state = sd_receivingdata_state;
            sd->data_start = addr;
            sd->data_offset = 0;
            sd->blk_written = 0;
            if (sd->data_start + sd->blk_len > sd->size)
                sd->card_status |= ADDRESS_ERROR;
            if (sd_wp_addr(sd, sd->data_start))
                sd->card_status |= WP_VIOLATION;
            if (sd->csd[14] & 0x30)
                sd->card_status |= WP_VIOLATION;
            return sd_r1;
        default:
            break;
        }
        break;
    case 26:	 
        if (sd->spi)
            goto bad_cmd;
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_receivingdata_state;
            sd->data_start = 0;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
    case 27:	 
        if (sd->spi)
            goto unimplemented_cmd;
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_receivingdata_state;
            sd->data_start = 0;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
     
    case 28:	 
        switch (sd->state) {
        case sd_transfer_state:
            if (addr >= sd->size) {
                sd->card_status = ADDRESS_ERROR;
                return sd_r1b;
            }
            sd->state = sd_programming_state;
            sd->wp_groups[addr >> (HWBLOCK_SHIFT +
                            SECTOR_SHIFT + WPGROUP_SHIFT)] = 1;
             
            sd->state = sd_transfer_state;
            return sd_r1b;
        default:
            break;
        }
        break;
    case 29:	 
        switch (sd->state) {
        case sd_transfer_state:
            if (addr >= sd->size) {
                sd->card_status = ADDRESS_ERROR;
                return sd_r1b;
            }
            sd->state = sd_programming_state;
            sd->wp_groups[addr >> (HWBLOCK_SHIFT +
                            SECTOR_SHIFT + WPGROUP_SHIFT)] = 0;
             
            sd->state = sd_transfer_state;
            return sd_r1b;
        default:
            break;
        }
        break;
    case 30:	 
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_sendingdata_state;
            *(uint32_t *) sd->data = sd_wpbits(sd, req.arg);
            sd->data_start = addr;
            sd->data_offset = 0;
            return sd_r1b;
        default:
            break;
        }
        break;
     
    case 32:	 
        switch (sd->state) {
        case sd_transfer_state:
            sd->erase_start = req.arg;
            return sd_r1;
        default:
            break;
        }
        break;
    case 33:	 
        switch (sd->state) {
        case sd_transfer_state:
            sd->erase_end = req.arg;
            return sd_r1;
        default:
            break;
        }
        break;
    case 38:	 
        switch (sd->state) {
        case sd_transfer_state:
            if (sd->csd[14] & 0x30) {
                sd->card_status |= WP_VIOLATION;
                return sd_r1b;
            }
            sd->state = sd_programming_state;
            sd_erase(sd);
             
            sd->state = sd_transfer_state;
            return sd_r1b;
        default:
            break;
        }
        break;
     
    case 42:	 
        if (sd->spi)
            goto unimplemented_cmd;
        switch (sd->state) {
        case sd_transfer_state:
            sd->state = sd_receivingdata_state;
            sd->data_start = 0;
            sd->data_offset = 0;
            return sd_r1;
        default:
            break;
        }
        break;
     
    case 55:	 
        if (sd->rca != rca)
        sd->card_status |= APP_CMD;
        return sd_r1;
    case 56:	 
        fprintf(stderr, "SD: GEN_CMD 0x%08x\n", req.arg);
        switch (sd->state) {
        case sd_transfer_state:
            sd->data_offset = 0;
            if (req.arg & 1)
                sd->state = sd_sendingdata_state;
            else
                sd->state = sd_receivingdata_state;
            return sd_r1;
        default:
            break;
        }
        break;
    default:
    bad_cmd:
        fprintf(stderr, "SD: Unknown CMD%i\n", req.cmd);
    unimplemented_cmd:
         
        fprintf(stderr, "SD: CMD%i not implemented in SPI mode\n", req.cmd);
    }
    fprintf(stderr, "SD: CMD%i in a wrong state\n", req.cmd);
}