static void s390_cpu_realizefn(DeviceState *dev, Error **errp)

{

    CPUState *cs = CPU(dev);

    S390CPUClass *scc = S390_CPU_GET_CLASS(dev);

    S390CPU *cpu = S390_CPU(dev);

    CPUS390XState *env = &cpu->env;

    Error *err = NULL;



    cpu_exec_init(cs, &err);

    if (err != NULL) {

        error_propagate(errp, err);

        return;

    }


    qemu_register_reset(s390_cpu_machine_reset_cb, cpu);


    env->cpu_num = scc->next_cpu_id++;

    s390_cpu_gdb_init(cs);

    qemu_init_vcpu(cs);


    run_on_cpu(cs, s390_do_cpu_full_reset, cs);


    cpu_reset(cs);




    scc->parent_realize(dev, errp);

}
