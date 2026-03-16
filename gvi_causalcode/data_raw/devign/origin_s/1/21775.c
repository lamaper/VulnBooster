void cpu_dump_state(CPUState *env, FILE *f, 

                    int (*cpu_fprintf)(FILE *f, const char *fmt, ...),

                    int flags)

{












    int i;



    cpu_fprintf(f, "NIP " REGX " LR " REGX " CTR " REGX "\n",

                env->nip, env->lr, env->ctr);

    cpu_fprintf(f, "MSR " REGX FILL " XER %08x      TB %08x %08x "


                "DECR %08x"


                "\n",

                do_load_msr(env), load_xer(env), cpu_ppc_load_tbu(env),

                cpu_ppc_load_tbl(env)


                , cpu_ppc_load_decr(env)


                );

    for (i = 0; i < 32; i++) {

        if ((i & (RGPL - 1)) == 0)

            cpu_fprintf(f, "GPR%02d", i);

        cpu_fprintf(f, " " REGX, env->gpr[i]);

        if ((i & (RGPL - 1)) == (RGPL - 1))

            cpu_fprintf(f, "\n");

    }

    cpu_fprintf(f, "CR ");

    for (i = 0; i < 8; i++)

        cpu_fprintf(f, "%01x", env->crf[i]);

    cpu_fprintf(f, "  [");

    for (i = 0; i < 8; i++) {

        char a = '-';

        if (env->crf[i] & 0x08)

            a = 'L';

        else if (env->crf[i] & 0x04)

            a = 'G';

        else if (env->crf[i] & 0x02)

            a = 'E';

        cpu_fprintf(f, " %c%c", a, env->crf[i] & 0x01 ? 'O' : ' ');

    }

    cpu_fprintf(f, " ]             " FILL "RES " REGX "\n", env->reserve);

    for (i = 0; i < 32; i++) {

        if ((i & (RFPL - 1)) == 0)

            cpu_fprintf(f, "FPR%02d", i);

        cpu_fprintf(f, " %016" PRIx64, *((uint64_t *)&env->fpr[i]));

        if ((i & (RFPL - 1)) == (RFPL - 1))

            cpu_fprintf(f, "\n");

    }

    cpu_fprintf(f, "SRR0 " REGX " SRR1 " REGX "         " FILL FILL FILL

                "SDR1 " REGX "\n",

                env->spr[SPR_SRR0], env->spr[SPR_SRR1], env->sdr1);





}
