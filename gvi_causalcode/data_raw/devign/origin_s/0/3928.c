void cpu_exec_init(CPUState *cpu, Error **errp)

{

    CPUClass *cc = CPU_GET_CLASS(cpu);

    int cpu_index;

    Error *local_err = NULL;


    cpu->as = &address_space_memory;

    cpu->thread_id = qemu_get_thread_id();



    cpu_list_lock();


    cpu_index = cpu->cpu_index = cpu_get_free_index(&local_err);

    if (local_err) {

        error_propagate(errp, local_err);


        cpu_list_unlock();


        return;

    }

    QTAILQ_INSERT_TAIL(&cpus, cpu, node);


    cpu_list_unlock();


    if (qdev_get_vmsd(DEVICE(cpu)) == NULL) {

        vmstate_register(NULL, cpu_index, &vmstate_cpu_common, cpu);

    }


    register_savevm(NULL, "cpu", cpu_index, CPU_SAVE_VERSION,

                    cpu_save, cpu_load, cpu->env_ptr);

    assert(cc->vmsd == NULL);

    assert(qdev_get_vmsd(DEVICE(cpu)) == NULL);


    if (cc->vmsd != NULL) {

        vmstate_register(NULL, cpu_index, cc->vmsd, cpu);

    }

}
