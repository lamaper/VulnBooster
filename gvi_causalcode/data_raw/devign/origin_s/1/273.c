static int gdb_handle_packet(GDBState *s, CPUState *env, const char *line_buf)

{

    const char *p;

    int ch, reg_size, type;

    char buf[4096];

    uint8_t mem_buf[4096];

    uint32_t *registers;

    target_ulong addr, len;


    printf("command='%s'\n", line_buf);


    p = line_buf;

    ch = *p++;

    switch(ch) {

    case '?':

         

        snprintf(buf, sizeof(buf), "S%02x", SIGTRAP);

        put_packet(s, buf);

         




    case 'c':

        if (*p != '\0') {

            addr = strtoull(p, (char **)&p, 16);


            env->eip = addr;


            env->nip = addr;


            env->pc = addr;

            env->npc = addr + 4;


            env->regs[15] = addr;


            env->pc = addr;


            env->PC[env->current_tc] = addr;


            env->pc = addr;


        }


	return RS_IDLE;












    case 's':

        if (*p != '\0') {

            addr = strtoull(p, (char **)&p, 16);


            env->eip = addr;


            env->nip = addr;


            env->pc = addr;

            env->npc = addr + 4;


            env->regs[15] = addr;


            env->pc = addr;


            env->PC[env->current_tc] = addr;


            env->pc = addr;


        }

        cpu_single_step(env, sstep_flags);


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


            }

        }


    case 'g':

        reg_size = cpu_gdb_read_registers(env, mem_buf);

        memtohex(buf, mem_buf, reg_size);

        put_packet(s, buf);


    case 'G':

        registers = (void *)mem_buf;

        len = strlen(p) / 2;

        hextomem((uint8_t *)registers, p, len);

        cpu_gdb_write_registers(env, mem_buf, len);



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



    case 'Z':

        type = strtoul(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        addr = strtoull(p, (char **)&p, 16);

        if (*p == ',')

            p++;

        len = strtoull(p, (char **)&p, 16);

        if (type == 0 || type == 1) {

            if (cpu_breakpoint_insert(env, addr) < 0)

                goto breakpoint_error;


        } else if (type == 2) {

            if (cpu_watchpoint_insert(env, addr) < 0)

                goto breakpoint_error;


        } else {

        breakpoint_error:

            put_packet(s, "E22");

        }


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


        } else if (type == 2) {

            cpu_watchpoint_remove(env, addr);


        } else {

            goto breakpoint_error;

        }


    case 'q':

    case 'Q':

         

        if (!strcmp(p,"qemu.sstepbits")) {

             

            sprintf(buf,"ENABLE=%x,NOIRQ=%x,NOTIMER=%x",

                    SSTEP_ENABLE,

                    SSTEP_NOIRQ,

                    SSTEP_NOTIMER);

            put_packet(s, buf);


        } else if (strncmp(p,"qemu.sstep",10) == 0) {

             

            p += 10;

            if (*p != '=') {

                 

                sprintf(buf,"0x%x", sstep_flags);

                put_packet(s, buf);


            }

            p++;

            type = strtoul(p, (char **)&p, 16);

            sstep_flags = type;



        }


        else if (strncmp(p, "Offsets", 7) == 0) {

            TaskState *ts = env->opaque;



            sprintf(buf,

                    "Text=" TARGET_ABI_FMT_lx ";Data=" TARGET_ABI_FMT_lx

                    ";Bss=" TARGET_ABI_FMT_lx,

                    ts->info->code_offset,

                    ts->info->data_offset,

                    ts->info->data_offset);

            put_packet(s, buf);


        }


         

    default:

         

        buf[0] = '\0';

        put_packet(s, buf);


    }

    return RS_IDLE;

}