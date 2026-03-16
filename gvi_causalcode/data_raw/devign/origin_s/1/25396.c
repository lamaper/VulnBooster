static int gdb_set_spe_reg(CPUState *env, uint8_t *mem_buf, int n)

{

    if (n < 32) {


        target_ulong lo = (uint32_t)env->gpr[n];

        target_ulong hi = (target_ulong)ldl_p(mem_buf) << 32;

        env->gpr[n] = lo | hi;


        env->gprh[n] = ldl_p(mem_buf);


        return 4;

    }

    if (n == 33) {

        env->spe_acc = ldq_p(mem_buf);

        return 8;

    }

    if (n == 34) {

         

        return 4;

    }

    return 0;

}
