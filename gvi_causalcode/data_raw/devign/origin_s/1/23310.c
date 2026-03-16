static always_inline void powerpc_excp (CPUState *env,

                                        int excp_model, int excp)

{

    target_ulong msr, new_msr, vector;

    int srr0, srr1, asrr0, asrr1;


    int lpes0, lpes1, lev;



    lpes0 = (env->spr[SPR_LPCR] >> 1) & 1;

    lpes1 = (env->spr[SPR_LPCR] >> 2) & 1;




    if (loglevel & CPU_LOG_INT) {

        fprintf(logfile, "Raise exception at 0x" ADDRX " => 0x%08x (%02x)\n",

                env->nip, excp, env->error_code);

    }

    msr = env->msr;

    new_msr = msr;

    srr0 = SPR_SRR0;

    srr1 = SPR_SRR1;

    asrr0 = -1;

    asrr1 = -1;

    msr &= ~((target_ulong)0x783F0000);

    switch (excp) {

    case POWERPC_EXCP_NONE:

         

        return;

    case POWERPC_EXCP_CRITICAL:     

        new_msr &= ~((target_ulong)1 << MSR_RI);  

        switch (excp_model) {

        case POWERPC_EXCP_40x:

            srr0 = SPR_40x_SRR2;

            srr1 = SPR_40x_SRR3;

            break;

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_CSRR0;

            srr1 = SPR_BOOKE_CSRR1;

            break;

        case POWERPC_EXCP_G2:

            break;

        default:

            goto excp_invalid;

        }

        goto store_next;

    case POWERPC_EXCP_MCHECK:     

        if (msr_me == 0) {

             

            if (loglevel != 0) {

                fprintf(logfile, "Machine check while not allowed. "

                        "Entering checkstop state\n");

            } else {

                fprintf(stderr, "Machine check while not allowed. "

                        "Entering checkstop state\n");

            }

            env->halted = 1;

            env->interrupt_request |= CPU_INTERRUPT_EXITTB;

        }

        new_msr &= ~((target_ulong)1 << MSR_RI);

        new_msr &= ~((target_ulong)1 << MSR_ME);


        new_msr |= (target_ulong)1 << MSR_HV;


         

        switch (excp_model) {

        case POWERPC_EXCP_40x:

            srr0 = SPR_40x_SRR2;

            srr1 = SPR_40x_SRR3;

            break;

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_MCSRR0;

            srr1 = SPR_BOOKE_MCSRR1;

            asrr0 = SPR_BOOKE_CSRR0;

            asrr1 = SPR_BOOKE_CSRR1;

            break;

        default:

            break;

        }

        goto store_next;

    case POWERPC_EXCP_DSI:        


        if (loglevel != 0) {

            fprintf(logfile, "DSI exception: DSISR=0x" ADDRX" DAR=0x" ADDRX

                    "\n", env->spr[SPR_DSISR], env->spr[SPR_DAR]);

        }


        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;

    case POWERPC_EXCP_ISI:        


        if (loglevel != 0) {

            fprintf(logfile, "ISI exception: msr=0x" ADDRX ", nip=0x" ADDRX

                    "\n", msr, env->nip);

        }


        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        msr |= env->error_code;

        goto store_next;

    case POWERPC_EXCP_EXTERNAL:   

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes0 == 1)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;

    case POWERPC_EXCP_ALIGN:      

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


         

         

        env->spr[SPR_DSISR] |= (ldl_code((env->nip - 4)) & 0x03FF0000) >> 16;

        goto store_current;

    case POWERPC_EXCP_PROGRAM:    

        switch (env->error_code & ~0xF) {

        case POWERPC_EXCP_FP:

            if ((msr_fe0 == 0 && msr_fe1 == 0) || msr_fp == 0) {


                if (loglevel != 0) {

                    fprintf(logfile, "Ignore floating point exception\n");

                }


                env->exception_index = POWERPC_EXCP_NONE;

                env->error_code = 0;

                return;

            }

            new_msr &= ~((target_ulong)1 << MSR_RI);


            if (lpes1 == 0)

                new_msr |= (target_ulong)1 << MSR_HV;


            msr |= 0x00100000;

            if (msr_fe0 == msr_fe1)

                goto store_next;

            msr |= 0x00010000;

            break;

        case POWERPC_EXCP_INVAL:


            if (loglevel != 0) {

                fprintf(logfile, "Invalid instruction at 0x" ADDRX "\n",

                        env->nip);

            }


            new_msr &= ~((target_ulong)1 << MSR_RI);


            if (lpes1 == 0)

                new_msr |= (target_ulong)1 << MSR_HV;


            msr |= 0x00080000;

            break;

        case POWERPC_EXCP_PRIV:

            new_msr &= ~((target_ulong)1 << MSR_RI);


            if (lpes1 == 0)

                new_msr |= (target_ulong)1 << MSR_HV;


            msr |= 0x00040000;

            break;

        case POWERPC_EXCP_TRAP:

            new_msr &= ~((target_ulong)1 << MSR_RI);


            if (lpes1 == 0)

                new_msr |= (target_ulong)1 << MSR_HV;


            msr |= 0x00020000;

            break;

        default:

             

            cpu_abort(env, "Invalid program exception %d. Aborting\n",

                      env->error_code);

            break;

        }

        goto store_current;

    case POWERPC_EXCP_FPU:        

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_current;

    case POWERPC_EXCP_SYSCALL:    

         

         

        if (env->gpr[3] == 0x113724fa && env->gpr[4] == 0x77810f9b &&

            env->osi_call) {

            if (env->osi_call(env) != 0) {

                env->exception_index = POWERPC_EXCP_NONE;

                env->error_code = 0;

                return;

            }

        }

        if (loglevel & CPU_LOG_INT) {

            dump_syscall(env);

        }

        new_msr &= ~((target_ulong)1 << MSR_RI);


        lev = env->error_code;

        if (lev == 1 || (lpes0 == 0 && lpes1 == 0))

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;

    case POWERPC_EXCP_APU:        

        new_msr &= ~((target_ulong)1 << MSR_RI);

        goto store_current;

    case POWERPC_EXCP_DECR:       

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;

    case POWERPC_EXCP_FIT:        


        if (loglevel != 0)

            fprintf(logfile, "FIT exception\n");


        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_next;

    case POWERPC_EXCP_WDT:        


        if (loglevel != 0)

            fprintf(logfile, "WDT exception\n");


        switch (excp_model) {

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_CSRR0;

            srr1 = SPR_BOOKE_CSRR1;

            break;

        default:

            break;

        }

        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_next;

    case POWERPC_EXCP_DTLB:       

        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_next;

    case POWERPC_EXCP_ITLB:       

        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_next;

    case POWERPC_EXCP_DEBUG:      

        switch (excp_model) {

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_DSRR0;

            srr1 = SPR_BOOKE_DSRR1;

            asrr0 = SPR_BOOKE_CSRR0;

            asrr1 = SPR_BOOKE_CSRR1;

            break;

        default:

            break;

        }

         

        cpu_abort(env, "Debug exception is not implemented yet !\n");

        goto store_next;


    case POWERPC_EXCP_SPEU:       

        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_current;

    case POWERPC_EXCP_EFPDI:      

         

        cpu_abort(env, "Embedded floating point data exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_EFPRI:      

         

        cpu_abort(env, "Embedded floating point round exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_EPERFM:     

        new_msr &= ~((target_ulong)1 << MSR_RI);

         

        cpu_abort(env,

                  "Performance counter exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_DOORI:      

         

        cpu_abort(env,

                  "Embedded doorbell interrupt is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_DOORCI:     

        switch (excp_model) {

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_CSRR0;

            srr1 = SPR_BOOKE_CSRR1;

            break;

        default:

            break;

        }

         

        cpu_abort(env, "Embedded doorbell critical interrupt "

                  "is not implemented yet !\n");

        goto store_next;


    case POWERPC_EXCP_RESET:      

        new_msr &= ~((target_ulong)1 << MSR_RI);


        new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;


    case POWERPC_EXCP_DSEG:       

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;

    case POWERPC_EXCP_ISEG:       

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;



    case POWERPC_EXCP_HDECR:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)1 << MSR_HV;

        goto store_next;


    case POWERPC_EXCP_TRACE:      

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_next;


    case POWERPC_EXCP_HDSI:       

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)1 << MSR_HV;

        goto store_next;

    case POWERPC_EXCP_HISI:       

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)1 << MSR_HV;

        goto store_next;

    case POWERPC_EXCP_HDSEG:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)1 << MSR_HV;

        goto store_next;

    case POWERPC_EXCP_HISEG:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)1 << MSR_HV;

        goto store_next;


    case POWERPC_EXCP_VPU:        

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        goto store_current;

    case POWERPC_EXCP_PIT:        


        if (loglevel != 0)

            fprintf(logfile, "PIT exception\n");


        new_msr &= ~((target_ulong)1 << MSR_RI);  

        goto store_next;

    case POWERPC_EXCP_IO:         

         

        cpu_abort(env, "601 IO error exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_RUNM:       

         

        cpu_abort(env, "601 run mode exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_EMUL:       

         

        cpu_abort(env, "602 emulation trap exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_IFTLB:      

        new_msr &= ~((target_ulong)1 << MSR_RI);  


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        switch (excp_model) {

        case POWERPC_EXCP_602:

        case POWERPC_EXCP_603:

        case POWERPC_EXCP_603E:

        case POWERPC_EXCP_G2:

            goto tlb_miss_tgpr;

        case POWERPC_EXCP_7x5:

            goto tlb_miss;

        case POWERPC_EXCP_74xx:

            goto tlb_miss_74xx;

        default:

            cpu_abort(env, "Invalid instruction TLB miss exception\n");

            break;

        }

        break;

    case POWERPC_EXCP_DLTLB:      

        new_msr &= ~((target_ulong)1 << MSR_RI);  


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        switch (excp_model) {

        case POWERPC_EXCP_602:

        case POWERPC_EXCP_603:

        case POWERPC_EXCP_603E:

        case POWERPC_EXCP_G2:

            goto tlb_miss_tgpr;

        case POWERPC_EXCP_7x5:

            goto tlb_miss;

        case POWERPC_EXCP_74xx:

            goto tlb_miss_74xx;

        default:

            cpu_abort(env, "Invalid data load TLB miss exception\n");

            break;

        }

        break;

    case POWERPC_EXCP_DSTLB:      

        new_msr &= ~((target_ulong)1 << MSR_RI);  


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


        switch (excp_model) {

        case POWERPC_EXCP_602:

        case POWERPC_EXCP_603:

        case POWERPC_EXCP_603E:

        case POWERPC_EXCP_G2:

        tlb_miss_tgpr:

             

            if (!(new_msr & ((target_ulong)1 << MSR_TGPR))) {

                new_msr |= (target_ulong)1 << MSR_TGPR;

                hreg_swap_gpr_tgpr(env);

            }

            goto tlb_miss;

        case POWERPC_EXCP_7x5:

        tlb_miss:


            if (loglevel != 0) {

                const unsigned char *es;

                target_ulong *miss, *cmp;

                int en;

                if (excp == POWERPC_EXCP_IFTLB) {

                    es = "I";

                    en = 'I';

                    miss = &env->spr[SPR_IMISS];

                    cmp = &env->spr[SPR_ICMP];

                } else {

                    if (excp == POWERPC_EXCP_DLTLB)

                        es = "DL";

                    else

                        es = "DS";

                    en = 'D';

                    miss = &env->spr[SPR_DMISS];

                    cmp = &env->spr[SPR_DCMP];

                }

                fprintf(logfile, "6xx %sTLB miss: %cM " ADDRX " %cC " ADDRX

                        " H1 " ADDRX " H2 " ADDRX " %08x\n",

                        es, en, *miss, en, *cmp,

                        env->spr[SPR_HASH1], env->spr[SPR_HASH2],

                        env->error_code);

            }


            msr |= env->crf[0] << 28;

            msr |= env->error_code;  

             

            msr |= ((env->last_way + 1) & (env->nb_ways - 1)) << 17;

            break;

        case POWERPC_EXCP_74xx:

        tlb_miss_74xx:


            if (loglevel != 0) {

                const unsigned char *es;

                target_ulong *miss, *cmp;

                int en;

                if (excp == POWERPC_EXCP_IFTLB) {

                    es = "I";

                    en = 'I';

                    miss = &env->spr[SPR_TLBMISS];

                    cmp = &env->spr[SPR_PTEHI];

                } else {

                    if (excp == POWERPC_EXCP_DLTLB)

                        es = "DL";

                    else

                        es = "DS";

                    en = 'D';

                    miss = &env->spr[SPR_TLBMISS];

                    cmp = &env->spr[SPR_PTEHI];

                }

                fprintf(logfile, "74xx %sTLB miss: %cM " ADDRX " %cC " ADDRX

                        " %08x\n",

                        es, en, *miss, en, *cmp, env->error_code);

            }


            msr |= env->error_code;  

            break;

        default:

            cpu_abort(env, "Invalid data store TLB miss exception\n");

            break;

        }

        goto store_next;

    case POWERPC_EXCP_FPA:        

         

        cpu_abort(env, "Floating point assist exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_IABR:       

         

        cpu_abort(env, "IABR exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_SMI:        

         

        cpu_abort(env, "SMI exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_THERM:      

         

        cpu_abort(env, "Thermal management exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_PERFM:      

        new_msr &= ~((target_ulong)1 << MSR_RI);


        if (lpes1 == 0)

            new_msr |= (target_ulong)1 << MSR_HV;


         

        cpu_abort(env,

                  "Performance counter exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_VPUA:       

         

        cpu_abort(env, "VPU assist exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_SOFTP:      

         

        cpu_abort(env,

                  "970 soft-patch exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_MAINT:      

         

        cpu_abort(env,

                  "970 maintenance exception is not implemented yet !\n");

        goto store_next;

    default:

    excp_invalid:

        cpu_abort(env, "Invalid PowerPC exception %d. Aborting\n", excp);

        break;

    store_current:

         

        env->spr[srr0] = env->nip - 4;

        break;

    store_next:

         

        env->spr[srr0] = env->nip;

        break;

    }

     

    env->spr[srr1] = msr;

     

    if (asrr0 != -1)

        env->spr[asrr0] = env->spr[srr0];

    if (asrr1 != -1)

        env->spr[asrr1] = env->spr[srr1];

     

    if (new_msr & ((1 << MSR_IR) | (1 << MSR_DR)))

        tlb_flush(env, 1);

     

    new_msr &= ~((target_ulong)1 << MSR_EE);

    new_msr &= ~((target_ulong)1 << MSR_PR);

    new_msr &= ~((target_ulong)1 << MSR_FP);

    new_msr &= ~((target_ulong)1 << MSR_FE0);

    new_msr &= ~((target_ulong)1 << MSR_SE);

    new_msr &= ~((target_ulong)1 << MSR_BE);

    new_msr &= ~((target_ulong)1 << MSR_FE1);

    new_msr &= ~((target_ulong)1 << MSR_IR);

    new_msr &= ~((target_ulong)1 << MSR_DR);


    new_msr &= ~((target_ulong)1 << MSR_PMM);


    new_msr &= ~((target_ulong)1 << MSR_LE);

    if (msr_ile)

        new_msr |= (target_ulong)1 << MSR_LE;

    else

        new_msr &= ~((target_ulong)1 << MSR_LE);

     

    vector = env->excp_vectors[excp];

    if (vector == (target_ulong)-1) {

        cpu_abort(env, "Raised an exception without defined vector %d\n",

                  excp);

    }

    vector |= env->excp_prefix;


    if (excp_model == POWERPC_EXCP_BOOKE) {

        if (!msr_icm) {

            new_msr &= ~((target_ulong)1 << MSR_CM);

            vector = (uint32_t)vector;

        } else {

            new_msr |= (target_ulong)1 << MSR_CM;

        }

    } else {

        if (!msr_isf) {

            new_msr &= ~((target_ulong)1 << MSR_SF);

            vector = (uint32_t)vector;

        } else {

            new_msr |= (target_ulong)1 << MSR_SF;

        }

    }


     

    env->msr = new_msr;

    env->hflags_nmsr = 0x00000000;

    hreg_compute_hflags(env);

    env->nip = vector;

     

    env->exception_index = POWERPC_EXCP_NONE;

    env->error_code = 0;

}
