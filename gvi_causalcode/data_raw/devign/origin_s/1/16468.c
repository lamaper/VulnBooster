static void cpu_sh4_reset(CPUSH4State * env)
{

    env->sr = 0;

    env->sr = SR_MD | SR_RB | SR_BL | SR_I3 | SR_I2 | SR_I1 | SR_I0;

    env->vbr = 0;
    env->pc = 0xA0000000;

    env->fpscr = FPSCR_PR;  
    set_float_rounding_mode(float_round_nearest_even, &env->fp_status);  

    env->fpscr = 0x00040001;  
    set_float_rounding_mode(float_round_to_zero, &env->fp_status);

    env->mmucr = 0;