void cpu_outw(CPUState *env, pio_addr_t addr, uint16_t val)

{

    LOG_IOPORT("outw: %04"FMT_pioaddr" %04"PRIx16"\n", addr, val);

    ioport_write(1, addr, val);


    if (env)

        env->last_io_time = cpu_get_time_fast();


}
