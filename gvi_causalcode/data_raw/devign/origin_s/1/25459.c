static int gdb_set_avr_reg(CPUState *env, uint8_t *mem_buf, int n)

{

    if (n < 32) {


        env->avr[n].u64[0] = ldq_p(mem_buf);

        env->avr[n].u64[1] = ldq_p(mem_buf+8);


        env->avr[n].u64[1] = ldq_p(mem_buf);

        env->avr[n].u64[0] = ldq_p(mem_buf+8);


        return 16;

    }

    if (n == 33) {

        env->vscr = ldl_p(mem_buf);

        return 4;

    }

    if (n == 34) {

        env->spr[SPR_VRSAVE] = (target_ulong)ldl_p(mem_buf);

        return 4;

    }

    return 0;

}
