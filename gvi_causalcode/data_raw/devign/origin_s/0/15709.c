static void gdb_set_cpu_pc(GDBState *s, target_ulong pc)

{


    cpu_synchronize_state(s->c_cpu);

    s->c_cpu->eip = pc;


    s->c_cpu->nip = pc;


    s->c_cpu->pc = pc;

    s->c_cpu->npc = pc + 4;


    s->c_cpu->regs[15] = pc;


    s->c_cpu->pc = pc;


    s->c_cpu->active_tc.PC = pc;


    s->c_cpu->sregs[SR_PC] = pc;


    s->c_cpu->pc = pc;


    s->c_cpu->pc = pc;


    cpu_synchronize_state(s->c_cpu);

    s->c_cpu->psw.addr = pc;


}
