static int32_t scsi_send_command(SCSIDevice *d, uint32_t tag,

                                 uint8_t *buf, int lun)

{

    SCSIDeviceState *s = d->state;

    uint64_t nb_sectors;

    uint32_t lba;

    uint32_t len;

    int cmdlen;

    int is_write;

    uint8_t command;

    uint8_t *outbuf;

    SCSIRequest *r;



    command = buf[0];

    r = scsi_find_request(s, tag);

    if (r) {

        BADF("Tag 0x%x already in use\n", tag);

        scsi_cancel_io(d, tag);

    }

     

    r = scsi_new_request(s, tag);

    outbuf = r->dma_buf;

    is_write = 0;

    DPRINTF("Command: lun=%d tag=0x%x data=0x%02x", lun, tag, buf[0]);

    switch (command >> 5) {

    case 0:

        lba = buf[3] | (buf[2] << 8) | ((buf[1] & 0x1f) << 16);

        len = buf[4];

        cmdlen = 6;

        break;

    case 1:

    case 2:

        lba = buf[5] | (buf[4] << 8) | (buf[3] << 16) | (buf[2] << 24);

        len = buf[8] | (buf[7] << 8);

        cmdlen = 10;

        break;

    case 4:

        lba = buf[5] | (buf[4] << 8) | (buf[3] << 16) | (buf[2] << 24);

        len = buf[13] | (buf[12] << 8) | (buf[11] << 16) | (buf[10] << 24);

        cmdlen = 16;

        break;

    case 5:

        lba = buf[5] | (buf[4] << 8) | (buf[3] << 16) | (buf[2] << 24);

        len = buf[9] | (buf[8] << 8) | (buf[7] << 16) | (buf[6] << 24);

        cmdlen = 12;

        break;

    default:

        BADF("Unsupported command length, command %x\n", command);

        goto fail;

    }


    {

        int i;

        for (i = 1; i < cmdlen; i++) {

            printf(" 0x%02x", buf[i]);

        }

        printf("\n");

    }


    if (lun || buf[1] >> 5) {

         

        DPRINTF("Unimplemented LUN %d\n", lun ? lun : buf[1] >> 5);

        if (command != 0x03 && command != 0x12)  

            goto fail;

    }

    switch (command) {

    case 0x0:

	DPRINTF("Test Unit Ready\n");

	break;

    case 0x03:

        DPRINTF("Request Sense (len %d)\n", len);

        if (len < 4)

            goto fail;

        memset(outbuf, 0, 4);

        outbuf[0] = 0xf0;

        outbuf[1] = 0;

        outbuf[2] = s->sense;

        r->buf_len = 4;

        break;

    case 0x12:

        DPRINTF("Inquiry (len %d)\n", len);

        if (buf[1] & 0x2) {

             

            BADF("optional INQUIRY command support request not implemented\n");

            goto fail;

        }

        else if (buf[1] & 0x1) {

             

            uint8_t page_code = buf[2];

            if (len < 4) {

                BADF("Error: Inquiry (EVPD[%02X]) buffer size %d is "

                     "less than 4\n", page_code, len);

                goto fail;

            }



            switch (page_code) {

                case 0x00:

                    {

                         

                        DPRINTF("Inquiry EVPD[Supported pages] "

                                "buffer size %d\n", len);



                        r->buf_len = 0;



                        if (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM) {

                            outbuf[r->buf_len++] = 5;

                        } else {

                            outbuf[r->buf_len++] = 0;

                        }



                        outbuf[r->buf_len++] = 0x00;  

                        outbuf[r->buf_len++] = 0x00;

                        outbuf[r->buf_len++] = 3;     

                        outbuf[r->buf_len++] = 0x00;  

                        outbuf[r->buf_len++] = 0x80;  

                        outbuf[r->buf_len++] = 0x83;  

                    }

                    break;

                case 0x80:

                    {

                         

                        if (len < 4) {

                            BADF("Error: EVPD[Serial number] Inquiry buffer "

                                 "size %d too small, %d needed\n", len, 4);

                            goto fail;

                        }



                        DPRINTF("Inquiry EVPD[Serial number] buffer size %d\n", len);



                        r->buf_len = 0;



                         

                        if (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM) {

                            outbuf[r->buf_len++] = 5;

                        } else {

                            outbuf[r->buf_len++] = 0;

                        }



                        outbuf[r->buf_len++] = 0x80;  

                        outbuf[r->buf_len++] = 0x00;

                        outbuf[r->buf_len++] = 0x01;  



                        outbuf[r->buf_len++] = '0';   

                    }



                    break;

                case 0x83:

                    {

                         

                        int max_len = 255 - 8;

                        int id_len = strlen(bdrv_get_device_name(s->bdrv));

                        if (id_len > max_len)

                            id_len = max_len;



                        DPRINTF("Inquiry EVPD[Device identification] "

                                "buffer size %d\n", len);

                        r->buf_len = 0;

                        if (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM) {

                            outbuf[r->buf_len++] = 5;

                        } else {

                            outbuf[r->buf_len++] = 0;

                        }



                        outbuf[r->buf_len++] = 0x83;  

                        outbuf[r->buf_len++] = 0x00;

                        outbuf[r->buf_len++] = 3 + id_len;



                        outbuf[r->buf_len++] = 0x2;  

                        outbuf[r->buf_len++] = 0;    

                        outbuf[r->buf_len++] = 0;    

                        outbuf[r->buf_len++] = id_len;  



                        memcpy(&outbuf[r->buf_len],

                               bdrv_get_device_name(s->bdrv), id_len);

                        r->buf_len += id_len;

                    }

                    break;

                default:

                    BADF("Error: unsupported Inquiry (EVPD[%02X]) "

                         "buffer size %d\n", page_code, len);

                    goto fail;

            }

             

            break;

        }

        else {

             

            if (buf[2] != 0) {

                BADF("Error: Inquiry (STANDARD) page or code "

                     "is non-zero [%02X]\n", buf[2]);

                goto fail;

            }



             

            if (len < 5) {

                BADF("Error: Inquiry (STANDARD) buffer size %d "

                     "is less than 5\n", len);

                goto fail;

            }



            if (len < 36) {

                BADF("Error: Inquiry (STANDARD) buffer size %d "

                     "is less than 36 (TODO: only 5 required)\n", len);

            }

        }

	memset(outbuf, 0, 36);



        if (lun || buf[1] >> 5) {

            outbuf[0] = 0x7f;	 

	} else if (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM) {

	    outbuf[0] = 5;

            outbuf[1] = 0x80;

	    memcpy(&outbuf[16], "QEMU CD-ROM    ", 16);

	} else {

	    outbuf[0] = 0;

	    memcpy(&outbuf[16], "QEMU HARDDISK  ", 16);

	}

	memcpy(&outbuf[8], "QEMU   ", 8);

        memcpy(&outbuf[32], QEMU_VERSION, 4);

         

	outbuf[2] = 3;

	outbuf[3] = 2;  

	outbuf[4] = 31;

         

        outbuf[7] = 0x10 | (s->tcq ? 0x02 : 0);

	r->buf_len = 36;

	break;

    case 0x16:

        DPRINTF("Reserve(6)\n");

        if (buf[1] & 1)

            goto fail;

        break;

    case 0x17:

        DPRINTF("Release(6)\n");

        if (buf[1] & 1)

            goto fail;

        break;

    case 0x1a:

    case 0x5a:

        {

            uint8_t *p;

            int page;



            page = buf[2] & 0x3f;

            DPRINTF("Mode Sense (page %d, len %d)\n", page, len);

            p = outbuf;

            memset(p, 0, 4);

            outbuf[1] = 0;  

            outbuf[3] = 0;  

            if (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM) {

                outbuf[2] = 0x80;  

            }

            p += 4;

            if (page == 4) {

                int cylinders, heads, secs;



                 

                p[0] = 4;

                p[1] = 0x16;

                 

                bdrv_get_geometry_hint(s->bdrv, &cylinders, &heads, &secs);

                p[2] = (cylinders >> 16) & 0xff;

                p[3] = (cylinders >> 8) & 0xff;

                p[4] = cylinders & 0xff;

                p[5] = heads & 0xff;

                 

                p[6] = (cylinders >> 16) & 0xff;

                p[7] = (cylinders >> 8) & 0xff;

                p[8] = cylinders & 0xff;

                 

                p[9] = (cylinders >> 16) & 0xff;

                p[10] = (cylinders >> 8) & 0xff;

                p[11] = cylinders & 0xff;

                 

                p[12] = 0;

                p[13] = 200;

                 

                p[14] = 0xff;

                p[15] =  0xff;

                p[16] = 0xff;

                 

                p[20] = (5400 >> 8) & 0xff;

                p[21] = 5400 & 0xff;

                p += 0x16;

            } else if (page == 5) {

                int cylinders, heads, secs;



                 

                p[0] = 5;

                p[1] = 0x1e;

                 

                p[2] = 5000 >> 8;

                p[3] = 5000 & 0xff;

                 

                bdrv_get_geometry_hint(s->bdrv, &cylinders, &heads, &secs);

                p[4] = heads & 0xff;

                p[5] = secs & 0xff;

                p[6] = s->cluster_size * 2;

                p[8] = (cylinders >> 8) & 0xff;

                p[9] = cylinders & 0xff;

                 

                p[10] = (cylinders >> 8) & 0xff;

                p[11] = cylinders & 0xff;

                 

                p[12] = (cylinders >> 8) & 0xff;

                p[13] = cylinders & 0xff;

                 

                p[14] = 0;

                p[15] = 1;

                 

                p[16] = 1;

                 

                p[17] = 0;

                p[18] = 1;

                 

                p[19] = 1;

                 

                p[20] = 1;

                 

                p[28] = (5400 >> 8) & 0xff;

                p[29] = 5400 & 0xff;

                p += 0x1e;

            } else if ((page == 8 || page == 0x3f)) {

                 

                memset(p,0,20);

                p[0] = 8;

                p[1] = 0x12;

                p[2] = 4;  

                p += 20;

            }

            if ((page == 0x3f || page == 0x2a)

                    && (bdrv_get_type_hint(s->bdrv) == BDRV_TYPE_CDROM)) {

                 

                p[0] = 0x2a;

                p[1] = 0x14;

                p[2] = 3;  

                p[3] = 0;  

                p[4] = 0x7f;  

                p[5] = 0xff;  

                p[6] = 0x2d | (bdrv_is_locked(s->bdrv)? 2 : 0);

                 

                p[7] = 0;  

                p[8] = (50 * 176) >> 8;  

                p[9] = (50 * 176) & 0xff;

                p[10] = 0 >> 8;  

                p[11] = 0 & 0xff;

                p[12] = 2048 >> 8;  

                p[13] = 2048 & 0xff;

                p[14] = (16 * 176) >> 8;  

                p[15] = (16 * 176) & 0xff;

                p[18] = (16 * 176) >> 8;  

                p[19] = (16 * 176) & 0xff;

                p[20] = (16 * 176) >> 8;  

                p[21] = (16 * 176) & 0xff;

                p += 22;

            }

            r->buf_len = p - outbuf;

            outbuf[0] = r->buf_len - 4;

            if (r->buf_len > len)

                r->buf_len = len;

        }

        break;

    case 0x1b:

        DPRINTF("Start Stop Unit\n");

	break;

    case 0x1e:

        DPRINTF("Prevent Allow Medium Removal (prevent = %d)\n", buf[4] & 3);

        bdrv_set_locked(s->bdrv, buf[4] & 1);

	break;

    case 0x25:

	DPRINTF("Read Capacity\n");

         

	memset(outbuf, 0, 8);

	bdrv_get_geometry(s->bdrv, &nb_sectors);

         

        if (nb_sectors) {

            nb_sectors--;

            outbuf[0] = (nb_sectors >> 24) & 0xff;

            outbuf[1] = (nb_sectors >> 16) & 0xff;

            outbuf[2] = (nb_sectors >> 8) & 0xff;

            outbuf[3] = nb_sectors & 0xff;

            outbuf[4] = 0;

            outbuf[5] = 0;

            outbuf[6] = s->cluster_size * 2;

            outbuf[7] = 0;

            r->buf_len = 8;

        } else {

            scsi_command_complete(r, STATUS_CHECK_CONDITION, SENSE_NOT_READY);

            return 0;

        }

	break;

    case 0x08:

    case 0x28:

        DPRINTF("Read (sector %d, count %d)\n", lba, len);

        r->sector = lba * s->cluster_size;

        r->sector_count = len * s->cluster_size;

        break;

    case 0x0a:

    case 0x2a:

        DPRINTF("Write (sector %d, count %d)\n", lba, len);

        r->sector = lba * s->cluster_size;

        r->sector_count = len * s->cluster_size;

        is_write = 1;

        break;

    case 0x35:

        DPRINTF("Synchronise cache (sector %d, count %d)\n", lba, len);

        bdrv_flush(s->bdrv);

        break;

    case 0x43:

        {

            int start_track, format, msf, toclen;



            msf = buf[1] & 2;

            format = buf[2] & 0xf;

            start_track = buf[6];

            bdrv_get_geometry(s->bdrv, &nb_sectors);

            DPRINTF("Read TOC (track %d format %d msf %d)\n", start_track, format, msf >> 1);

            switch(format) {

            case 0:

                toclen = cdrom_read_toc(nb_sectors, outbuf, msf, start_track);

                break;

            case 1:

                 

                toclen = 12;

                memset(outbuf, 0, 12);

                outbuf[1] = 0x0a;

                outbuf[2] = 0x01;

                outbuf[3] = 0x01;

                break;

            case 2:

                toclen = cdrom_read_toc_raw(nb_sectors, outbuf, msf, start_track);

                break;

            default:

                goto error_cmd;

            }

            if (toclen > 0) {

                if (len > toclen)

                  len = toclen;

                r->buf_len = len;

                break;

            }

        error_cmd:

            DPRINTF("Read TOC error\n");

            goto fail;

        }

    case 0x46:

        DPRINTF("Get Configuration (rt %d, maxlen %d)\n", buf[1] & 3, len);

        memset(outbuf, 0, 8);

         

        outbuf[7] = 8;  

        r->buf_len = 8;

        break;

    case 0x56:

        DPRINTF("Reserve(10)\n");

        if (buf[1] & 3)

            goto fail;

        break;

    case 0x57:

        DPRINTF("Release(10)\n");

        if (buf[1] & 3)

            goto fail;

        break;

    case 0xa0:

        DPRINTF("Report LUNs (len %d)\n", len);

        if (len < 16)

            goto fail;

        memset(outbuf, 0, 16);

        outbuf[3] = 8;

        r->buf_len = 16;

        break;

    case 0x2f:

        DPRINTF("Verify (sector %d, count %d)\n", lba, len);

        break;

    default:

	DPRINTF("Unknown SCSI command (%2.2x)\n", buf[0]);

    fail:

        scsi_command_complete(r, STATUS_CHECK_CONDITION, SENSE_ILLEGAL_REQUEST);

	return 0;

    }

    if (r->sector_count == 0 && r->buf_len == 0) {

        scsi_command_complete(r, STATUS_GOOD, SENSE_NO_SENSE);

    }

    len = r->sector_count * 512 + r->buf_len;

    if (is_write) {

        return -len;

    } else {

        if (!r->sector_count)

            r->sector_count = -1;

        return len;

    }

}
