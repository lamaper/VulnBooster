void do_interrupt (CPUState *env)

{


    env->exception_index |= 0x100;


    uint32_t msr;

    int excp = env->exception_index;



    msr = _load_msr(env);


    if ((excp == EXCP_PROGRAM || excp == EXCP_DSI) && msr_pr == 1) 

    {

        if (loglevel > 0) {

            fprintf(logfile, "Raise exception at 0x%08x => 0x%08x (%02x)\n",

                    env->nip, excp << 8, env->error_code);

    }

	if (loglevel > 0)

	    cpu_ppc_dump_state(env, logfile, 0);

    }


     

    switch (excp) {

    case EXCP_OFCALL:


        env->gpr[3] = OF_client_entry((void *)env->gpr[3]);


        return;

    case EXCP_RTASCALL:


        printf("RTAS call !\n");

        env->gpr[3] = RTAS_entry((void *)env->gpr[3]);

        printf("RTAS call done\n");


        return;

    case EXCP_NONE:


        printf("%s: escape EXCP_NONE\n", __func__);


        return;

    case EXCP_RESET:

        if (msr_ip)

            excp += 0xFFC00;

        goto store_next;

    case EXCP_MACHINE_CHECK:

        if (msr_me == 0) {

            cpu_abort(env, "Machine check exception while not allowed\n");

        }

        msr_me = 0;

        break;

    case EXCP_DSI:

         

         

	msr &= ~0xFFFF0000;

	env->spr[DSISR] = 0;

	if (env->error_code &  EXCP_DSI_TRANSLATE)

	    env->spr[DSISR] |= 0x40000000;

	else if (env->error_code & EXCP_DSI_PROT)

	    env->spr[DSISR] |= 0x08000000;

	else if (env->error_code & EXCP_DSI_NOTSUP) {

	    env->spr[DSISR] |= 0x80000000;

	    if (env->error_code & EXCP_DSI_DIRECT)

		env->spr[DSISR] |= 0x04000000;

	}

	if (env->error_code & EXCP_DSI_STORE)

	    env->spr[DSISR] |= 0x02000000;

	if ((env->error_code & 0xF) == EXCP_DSI_DABR)

	    env->spr[DSISR] |= 0x00400000;

	if (env->error_code & EXCP_DSI_ECXW)

	    env->spr[DSISR] |= 0x00100000;


	if (loglevel) {

	    fprintf(logfile, "DSI exception: DSISR=0x%08x, DAR=0x%08x\n",

		    env->spr[DSISR], env->spr[DAR]);

	} else {

	    printf("DSI exception: DSISR=0x%08x, DAR=0x%08x nip=0x%08x\n",

		   env->spr[DSISR], env->spr[DAR], env->nip);

	}


        goto store_next;

    case EXCP_ISI:

         

	msr &= ~0xFFFF0000;

        if (env->error_code == EXCP_ISI_TRANSLATE)

            msr |= 0x40000000;

        else if (env->error_code == EXCP_ISI_NOEXEC ||

		 env->error_code == EXCP_ISI_GUARD ||

		 env->error_code == EXCP_ISI_DIRECT)

            msr |= 0x10000000;

        else

            msr |= 0x08000000;


	if (loglevel) {

	    fprintf(logfile, "ISI exception: msr=0x%08x, nip=0x%08x\n",

		    msr, env->nip);

	} else {

	    printf("ISI exception: msr=0x%08x, nip=0x%08x tbl:0x%08x\n",

		   msr, env->nip, env->spr[V_TBL]);

	}


        goto store_next;

    case EXCP_EXTERNAL:

        if (msr_ee == 0) {


            if (loglevel > 0) {

                fprintf(logfile, "Skipping hardware interrupt\n");

    }


             

            do_raise_exception(EXCP_EXTERNAL);

            return;

            }

        goto store_next;

    case EXCP_ALIGN:

         

         

        env->spr[DSISR] |=

            (ldl_code((void *)(env->nip - 4)) & 0x03FF0000) >> 16;

         

        goto store_current;

    case EXCP_PROGRAM:

        msr &= ~0xFFFF0000;

        switch (env->error_code & ~0xF) {

        case EXCP_FP:

            if (msr_fe0 == 0 && msr_fe1 == 0) {


                printf("Ignore floating point exception\n");


                return;

        }

            msr |= 0x00100000;

             

            env->fpscr[7] |= 0x8;

             

            if ((((env->fpscr[7] & 0x3) << 3) | (env->fpscr[6] >> 1)) &

                ((env->fpscr[1] << 1) | (env->fpscr[0] >> 3)))

                env->fpscr[7] |= 0x4;

        break;

        case EXCP_INVAL:

             

            msr |= 0x00080000;

        break;

        case EXCP_PRIV:

            msr |= 0x00040000;

        break;

        case EXCP_TRAP:

            msr |= 0x00020000;

            break;

        default:

             

        break;

    }

        msr |= 0x00010000;

        goto store_current;

    case EXCP_NO_FP:

        goto store_current;

    case EXCP_DECR:

        if (msr_ee == 0) {

             

            do_raise_exception(EXCP_DECR);

            return;

        }

        goto store_next;

    case EXCP_SYSCALL:


	if (msr_pr) {

	    if (loglevel) {

		fprintf(logfile, "syscall %d 0x%08x 0x%08x 0x%08x 0x%08x\n",

			env->gpr[0], env->gpr[3], env->gpr[4],

			env->gpr[5], env->gpr[6]);

	    } else {

		printf("syscall %d from 0x%08x 0x%08x 0x%08x 0x%08x 0x%08x\n",

		       env->gpr[0], env->nip, env->gpr[3], env->gpr[4],

		       env->gpr[5], env->gpr[6]);

	    }

	}


        goto store_next;

    case EXCP_TRACE:

        goto store_next;

    case EXCP_FP_ASSIST:

        goto store_next;

    case EXCP_MTMSR:

         

        return;

    case EXCP_BRANCH:

         

        return;

    case EXCP_RFI:

         

	tb_flush(env);


	if (msr_pr == 1)

	    printf("Return from exception => 0x%08x\n", (uint32_t)env->nip);


        return;

    store_current:

         

        env->spr[SRR0] = (uint32_t)env->nip - 4;

        break;

    store_next:

         

        env->spr[SRR0] = (uint32_t)env->nip;

        break;

    }

    env->spr[SRR1] = msr;

     

    msr_pow = 0;

    msr_ee = 0;

    msr_pr = 0;

    msr_fp = 0;

    msr_fe0 = 0;

    msr_se = 0;

    msr_be = 0;

    msr_fe1 = 0;

    msr_ir = 0;

    msr_dr = 0;

    msr_ri = 0;

    msr_le = msr_ile;

     

    env->nip = excp << 8;

    env->exception_index = EXCP_NONE;

     

    tlb_flush(env, 1);


    tmp_T0 = 0;


    T0 = 0;



    env->exception_index = -1;

}
