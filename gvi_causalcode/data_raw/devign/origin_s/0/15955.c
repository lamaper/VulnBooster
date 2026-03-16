static int gdb_handle_packet(GDBState *s, CPUState *env, const char *line_buf)

{

    const char *p;

    int ch, reg_size, type;

    char buf[MAX_PACKET_LENGTH];

    uint8_t mem_buf[MAX_PACKET_LENGTH];

    uint8_t *registers;

    target_ulong addr, len;


    printf("command='%s'\n", line_buf);


    p = line_buf;

    ch = *p++;

    switch(ch) {

    case '?':

         

        snprintf(buf, sizeof(buf), "S%02x", SIGTRAP);

        put_packet(s, buf);

         

        cpu_breakpoint_remove_all(env);

        cpu_watchpoint_remove_all(env);

        break;

    case 'c':

        if (*p != '\0') {

            addr = strtoull(p, (char **)&p, 16);


            env->eip = addr;


            env->nip = addr;


            env->pc = addr;

            env->npc = addr + 4;


            env->regs[15] = addr;


            env->pc = addr;


            env->active_tc.PC = addr;


            env->pc = addr;


        }

        gdb_continue(s);

	return RS_IDLE;

    case 'C':

        s->signal = strtoul(p, (char **)&p, 16);

        gdb_continue(s);

        return RS_IDLE;

    case 'k':

         

        fprintf(stderr, "\nQEMU: Terminated via GDBstub\n");

        exit(0);

    case 'D':

         

        cpu_breakpoint_remove_all(env);

        cpu_watchpoint_remove_all(env);

        gdb_continue(s);

        put_packet(s, "OK");

        break;

    case 's':

        if (*p != '\0') {

            addr = strtoull(p, (char **)&p, 16);


            env->eip = addr;


            env->nip = addr;


            env->pc = addr;

            env->npc = addr + 4;


            env->regs[15] = addr;


            env->pc = addr;


            env->active_tc.PC = addr;


            env->pc = addr;


        }

        cpu_single_step(env, sstep_flags);

        gdb_continue(s);

	return RS_IDLE;

    case 'F':

        {

            target_ulong ret;

            target_ulong err;



            ret = strtoull(p, (char **)&p, 16);

            if (*p == ',') {

                p++;

                err = strtoull(p, (char **)&p, 16);

            } else {

                err = 0;

            }

            if (*p == ',')

                p++;

            type = *p;

            if (gdb_current_syscall_cb)

                gdb_current_syscall_cb(s->env, ret, err);

            if (type == 'C') {

                put_packet(s, "T02");

            } else {

                gdb_continue(s);

            }

        }

        break;

    case 'g':

        len = 0;

        for (addr = 0; addr < num_g_regs; addr++) {

            reg_size = gdb_read_register(env, mem_buf + len, addr);

            len += reg_size;

        }

        memtohex(buf, mem_buf, len);

        put_packet(s, buf);

        break;

    case 'G':

        registers = mem_buf;

        len = strlen(p) / 2;

        hextomem((uint8_t *)registers, p, len);

        for (addr = 0; addr < num_g_regs && len > 0; addr++) {

            reg_size = gdb_write_register(env, registers, addr);

            len -= reg_size;

            registers += reg_size;

        }

        put_packet(s, "OK");

        break;

    case 'm':

        addr = strtoull(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        len = strtoull(p, NULL, 16);

        if (cpu_memory_rw_debug(env, addr, mem_buf, len, 0) != 0) {

            put_packet (s, "E14");

        } else {

            memtohex(buf, mem_buf, len);

            put_packet(s, buf);

        }

        break;

    case 'M':

        addr = strtoull(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        len = strtoull(p, (char **)&p, 16);

        if (*p == ':')

            p++;

        hextomem(mem_buf, p, len);

        if (cpu_memory_rw_debug(env, addr, mem_buf, len, 1) != 0)

            put_packet(s, "E14");

        else

            put_packet(s, "OK");

        break;

    case 'p':

         

        if (!gdb_has_xml)

            goto unknown_command;

        addr = strtoull(p, (char **)&p, 16);

        reg_size = gdb_read_register(env, mem_buf, addr);

        if (reg_size) {

            memtohex(buf, mem_buf, reg_size);

            put_packet(s, buf);

        } else {

            put_packet(s, "E14");

        }

        break;

    case 'P':

        if (!gdb_has_xml)

            goto unknown_command;

        addr = strtoull(p, (char **)&p, 16);

        if (*p == '=')

            p++;

        reg_size = strlen(p) / 2;

        hextomem(mem_buf, p, reg_size);

        gdb_write_register(env, mem_buf, addr);

        put_packet(s, "OK");

        break;

    case 'Z':

        type = strtoul(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        addr = strtoull(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        len = strtoull(p, (char **)&p, 16);

        switch (type) {

        case 0:

        case 1:

            if (cpu_breakpoint_insert(env, addr) < 0)

                goto breakpoint_error;

            put_packet(s, "OK");

            break;


        case 2:

            type = PAGE_WRITE;

            goto insert_watchpoint;

        case 3:

            type = PAGE_READ;

            goto insert_watchpoint;

        case 4:

            type = PAGE_READ | PAGE_WRITE;

        insert_watchpoint:

            if (cpu_watchpoint_insert(env, addr, type) < 0)

                goto breakpoint_error;

            put_packet(s, "OK");

            break;


        default:

            put_packet(s, "");

            break;

        }

        break;

    breakpoint_error:

        put_packet(s, "E22");

        break;



    case 'z':

        type = strtoul(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        addr = strtoull(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        len = strtoull(p, (char **)&p, 16);

        if (type == 0 || type == 1) {

            cpu_breakpoint_remove(env, addr);

            put_packet(s, "OK");


        } else if (type >= 2 || type <= 4) {

            cpu_watchpoint_remove(env, addr);

            put_packet(s, "OK");


        } else {

            put_packet(s, "");

        }

        break;

    case 'q':

    case 'Q':

         

        if (!strcmp(p,"qemu.sstepbits")) {

             

            snprintf(buf, sizeof(buf), "ENABLE=%x,NOIRQ=%x,NOTIMER=%x",

                     SSTEP_ENABLE,

                     SSTEP_NOIRQ,

                     SSTEP_NOTIMER);

            put_packet(s, buf);

            break;

        } else if (strncmp(p,"qemu.sstep",10) == 0) {

             

            p += 10;

            if (*p != '=') {

                 

                snprintf(buf, sizeof(buf), "0x%x", sstep_flags);

                put_packet(s, buf);

                break;

            }

            p++;

            type = strtoul(p, (char **)&p, 16);

            sstep_flags = type;

            put_packet(s, "OK");

            break;

        }


        else if (strncmp(p, "Offsets", 7) == 0) {

            TaskState *ts = env->opaque;



            snprintf(buf, sizeof(buf),

                     "Text=" TARGET_ABI_FMT_lx ";Data=" TARGET_ABI_FMT_lx

                     ";Bss=" TARGET_ABI_FMT_lx,

                     ts->info->code_offset,

                     ts->info->data_offset,

                     ts->info->data_offset);

            put_packet(s, buf);

            break;

        }


        if (strncmp(p, "Supported", 9) == 0) {

            sprintf(buf, "PacketSize=%x", MAX_PACKET_LENGTH);


            strcat(buf, ";qXfer:features:read+");


            put_packet(s, buf);

            break;

        }


        if (strncmp(p, "Xfer:features:read:", 19) == 0) {

            const char *xml;

            target_ulong total_len;



            gdb_has_xml = 1;

            p += 19;

            xml = get_feature_xml(env, p, &p);

            if (!xml) {

                sprintf(buf, "E00");

                put_packet(s, buf);

                break;

            }



            if (*p == ':')

                p++;

            addr = strtoul(p, (char **)&p, 16);

            if (*p == ',')

                p++;

            len = strtoul(p, (char **)&p, 16);



            total_len = strlen(xml);

            if (addr > total_len) {

                sprintf(buf, "E00");

                put_packet(s, buf);

                break;

            }

            if (len > (MAX_PACKET_LENGTH - 5) / 2)

                len = (MAX_PACKET_LENGTH - 5) / 2;

            if (len < total_len - addr) {

                buf[0] = 'm';

                len = memtox(buf + 1, xml + addr, len);

            } else {

                buf[0] = 'l';

                len = memtox(buf + 1, xml + addr, total_len - addr);

            }

            put_packet_binary(s, buf, len + 1);

            break;

        }


         

        goto unknown_command;



    default:

    unknown_command:

         

        buf[0] = '\0';

        put_packet(s, buf);

        break;

    }

    return RS_IDLE;

}
