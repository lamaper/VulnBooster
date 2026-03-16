static void do_info_cpus(Monitor *mon, QObject **ret_data)

{

    CPUState *env;

    QList *cpu_list;



    cpu_list = qlist_new();



     

    mon_get_cpu();



    for(env = first_cpu; env != NULL; env = env->next_cpu) {

        QDict *cpu;

        QObject *obj;



        cpu_synchronize_state(env);



        obj = qobject_from_jsonf("{ 'CPU': %d, 'current': %i, 'halted': %i }",

                                 env->cpu_index, env == mon->mon_cpu,

                                 env->halted);

        assert(obj != NULL);



        cpu = qobject_to_qdict(obj);


        qdict_put(cpu, "pc", qint_from_int(env->eip + env->segs[R_CS].base));


        qdict_put(cpu, "nip", qint_from_int(env->nip));


        qdict_put(cpu, "pc", qint_from_int(env->pc));

        qdict_put(cpu, "npc", qint_from_int(env->npc));


        qdict_put(cpu, "PC", qint_from_int(env->active_tc.PC));




        qlist_append(cpu_list, cpu);

    }



    *ret_data = QOBJECT(cpu_list);

}
