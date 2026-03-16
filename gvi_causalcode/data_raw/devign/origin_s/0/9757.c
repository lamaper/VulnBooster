uint64_t cpu_get_tsc(CPUX86State *env)

{


    if (env->kqemu_enabled) {

        return cpu_get_real_ticks();

    } else


    {

        return cpu_get_ticks();

    }

}
