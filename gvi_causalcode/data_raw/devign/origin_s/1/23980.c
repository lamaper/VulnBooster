static inline void powerpc_excp(PowerPCCPU *cpu, int excp_model, int excp)

{

    CPUState *cs = CPU(cpu);

    CPUPPCState *env = &cpu->env;

    target_ulong msr, new_msr, vector;

    int srr0, srr1, asrr0, asrr1;

    int lpes0, lpes1, lev, ail;



    if (0) {

         

        lpes0 = (env->spr[SPR_LPCR] >> 1) & 1;

        lpes1 = (env->spr[SPR_LPCR] >> 2) & 1;

    } else {

         

        lpes0 = 0;

        lpes1 = 1;

    }



    qemu_log_mask(CPU_LOG_INT, "Raise exception at " TARGET_FMT_lx

                  " => %08x (%02x)\n", env->nip, excp, env->error_code);



     

    if (excp_model == POWERPC_EXCP_BOOKE) {

        msr = env->msr;

    } else {

        msr = env->msr & ~0x783f0000ULL;

    }



     

    new_msr = env->msr & ((target_ulong)1 << MSR_ME);



     

    srr0 = SPR_SRR0;

    srr1 = SPR_SRR1;

    asrr0 = -1;

    asrr1 = -1;


    if (excp_model == POWERPC_EXCP_POWER7 ||

        excp_model == POWERPC_EXCP_POWER8) {

        if (excp_model == POWERPC_EXCP_POWER8) {

            ail = (env->spr[SPR_LPCR] & LPCR_AIL) >> LPCR_AIL_SHIFT;

        } else {

            ail = 0;

        }

    } else


    {

        ail = 0;

    }



    switch (excp) {

    case POWERPC_EXCP_NONE:

         

        return;

    case POWERPC_EXCP_CRITICAL:     

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

             

            fprintf(stderr, "Machine check while not allowed. "

                    "Entering checkstop state\n");

            if (qemu_log_separate()) {

                qemu_log("Machine check while not allowed. "

                        "Entering checkstop state\n");

            }

            cs->halted = 1;

            cs->interrupt_request |= CPU_INTERRUPT_EXITTB;

        }

        if (0) {

             

            new_msr |= (target_ulong)MSR_HVB;

        }

        ail = 0;



         

        new_msr &= ~((target_ulong)1 << MSR_ME);



         

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

        LOG_EXCP("DSI exception: DSISR=" TARGET_FMT_lx" DAR=" TARGET_FMT_lx

                 "\n", env->spr[SPR_DSISR], env->spr[SPR_DAR]);

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_ISI:        

        LOG_EXCP("ISI exception: msr=" TARGET_FMT_lx ", nip=" TARGET_FMT_lx

                 "\n", msr, env->nip);

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        msr |= env->error_code;

        goto store_next;

    case POWERPC_EXCP_EXTERNAL:   

        cs = CPU(cpu);



        if (lpes0 == 1) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        if (env->mpic_proxy) {

             

            env->spr[SPR_BOOKE_EPR] = ldl_phys(cs->as, env->mpic_iack);

        }

        goto store_next;

    case POWERPC_EXCP_ALIGN:      

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

         

         

        env->spr[SPR_DSISR] |= (cpu_ldl_code(env, (env->nip - 4))

                                & 0x03FF0000) >> 16;

        goto store_next;

    case POWERPC_EXCP_PROGRAM:    

        switch (env->error_code & ~0xF) {

        case POWERPC_EXCP_FP:

            if ((msr_fe0 == 0 && msr_fe1 == 0) || msr_fp == 0) {

                LOG_EXCP("Ignore floating point exception\n");

                cs->exception_index = POWERPC_EXCP_NONE;

                env->error_code = 0;

                return;

            }

            if (lpes1 == 0) {

                new_msr |= (target_ulong)MSR_HVB;

            }

            msr |= 0x00100000;

            if (msr_fe0 == msr_fe1) {

                goto store_next;

            }

            msr |= 0x00010000;

            break;

        case POWERPC_EXCP_INVAL:

            LOG_EXCP("Invalid instruction at " TARGET_FMT_lx "\n", env->nip);

            if (lpes1 == 0) {

                new_msr |= (target_ulong)MSR_HVB;

            }

            msr |= 0x00080000;

            env->spr[SPR_BOOKE_ESR] = ESR_PIL;

            break;

        case POWERPC_EXCP_PRIV:

            if (lpes1 == 0) {

                new_msr |= (target_ulong)MSR_HVB;

            }

            msr |= 0x00040000;

            env->spr[SPR_BOOKE_ESR] = ESR_PPR;

            break;

        case POWERPC_EXCP_TRAP:

            if (lpes1 == 0) {

                new_msr |= (target_ulong)MSR_HVB;

            }

            msr |= 0x00020000;

            env->spr[SPR_BOOKE_ESR] = ESR_PTR;

            break;

        default:

             

            cpu_abort(cs, "Invalid program exception %d. Aborting\n",

                      env->error_code);

            break;

        }

        goto store_current;

    case POWERPC_EXCP_FPU:        

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_current;

    case POWERPC_EXCP_SYSCALL:    

        dump_syscall(env);

        lev = env->error_code;

        if ((lev == 1) && cpu_ppc_hypercall) {

            cpu_ppc_hypercall(cpu);

            return;

        }

        if (lev == 1 || (lpes0 == 0 && lpes1 == 0)) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_APU:        

        goto store_current;

    case POWERPC_EXCP_DECR:       

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_FIT:        

         

        LOG_EXCP("FIT exception\n");

        goto store_next;

    case POWERPC_EXCP_WDT:        

        LOG_EXCP("WDT exception\n");

        switch (excp_model) {

        case POWERPC_EXCP_BOOKE:

            srr0 = SPR_BOOKE_CSRR0;

            srr1 = SPR_BOOKE_CSRR1;

            break;

        default:

            break;

        }

        goto store_next;

    case POWERPC_EXCP_DTLB:       

        goto store_next;

    case POWERPC_EXCP_ITLB:       

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

         

        cpu_abort(cs, "Debug exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_SPEU:       

        env->spr[SPR_BOOKE_ESR] = ESR_SPV;

        goto store_current;

    case POWERPC_EXCP_EFPDI:      

         

        cpu_abort(cs, "Embedded floating point data exception "

                  "is not implemented yet !\n");

        env->spr[SPR_BOOKE_ESR] = ESR_SPV;

        goto store_next;

    case POWERPC_EXCP_EFPRI:      

         

        cpu_abort(cs, "Embedded floating point round exception "

                  "is not implemented yet !\n");

        env->spr[SPR_BOOKE_ESR] = ESR_SPV;

        goto store_next;

    case POWERPC_EXCP_EPERFM:     

         

        cpu_abort(cs,

                  "Performance counter exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_DOORI:      

        goto store_next;

    case POWERPC_EXCP_DOORCI:     

        srr0 = SPR_BOOKE_CSRR0;

        srr1 = SPR_BOOKE_CSRR1;

        goto store_next;

    case POWERPC_EXCP_RESET:      

        if (msr_pow) {

             

            msr |= 0x10000;

        } else {

            new_msr &= ~((target_ulong)1 << MSR_ME);

        }



        if (0) {

             

            new_msr |= (target_ulong)MSR_HVB;

        }

        ail = 0;

        goto store_next;

    case POWERPC_EXCP_DSEG:       

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_ISEG:       

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_HDECR:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)MSR_HVB;

        new_msr |= env->msr & ((target_ulong)1 << MSR_RI);

        goto store_next;

    case POWERPC_EXCP_TRACE:      

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_next;

    case POWERPC_EXCP_HDSI:       

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)MSR_HVB;

        new_msr |= env->msr & ((target_ulong)1 << MSR_RI);

        goto store_next;

    case POWERPC_EXCP_HISI:       

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)MSR_HVB;

        new_msr |= env->msr & ((target_ulong)1 << MSR_RI);

        goto store_next;

    case POWERPC_EXCP_HDSEG:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)MSR_HVB;

        new_msr |= env->msr & ((target_ulong)1 << MSR_RI);

        goto store_next;

    case POWERPC_EXCP_HISEG:      

        srr0 = SPR_HSRR0;

        srr1 = SPR_HSRR1;

        new_msr |= (target_ulong)MSR_HVB;

        new_msr |= env->msr & ((target_ulong)1 << MSR_RI);

        goto store_next;

    case POWERPC_EXCP_VPU:        

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_current;

    case POWERPC_EXCP_VSXU:        

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_current;

    case POWERPC_EXCP_FU:          

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

        goto store_current;

    case POWERPC_EXCP_PIT:        

        LOG_EXCP("PIT exception\n");

        goto store_next;

    case POWERPC_EXCP_IO:         

         

        cpu_abort(cs, "601 IO error exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_RUNM:       

         

        cpu_abort(cs, "601 run mode exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_EMUL:       

         

        cpu_abort(cs, "602 emulation trap exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_IFTLB:      

        if (lpes1 == 0) {  

            new_msr |= (target_ulong)MSR_HVB;

        }

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

            cpu_abort(cs, "Invalid instruction TLB miss exception\n");

            break;

        }

        break;

    case POWERPC_EXCP_DLTLB:      

        if (lpes1 == 0) {  

            new_msr |= (target_ulong)MSR_HVB;

        }

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

            cpu_abort(cs, "Invalid data load TLB miss exception\n");

            break;

        }

        break;

    case POWERPC_EXCP_DSTLB:      

        if (lpes1 == 0) {  

            new_msr |= (target_ulong)MSR_HVB;

        }

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


            if (qemu_log_enabled()) {

                const char *es;

                target_ulong *miss, *cmp;

                int en;



                if (excp == POWERPC_EXCP_IFTLB) {

                    es = "I";

                    en = 'I';

                    miss = &env->spr[SPR_IMISS];

                    cmp = &env->spr[SPR_ICMP];

                } else {

                    if (excp == POWERPC_EXCP_DLTLB) {

                        es = "DL";

                    } else {

                        es = "DS";

                    }

                    en = 'D';

                    miss = &env->spr[SPR_DMISS];

                    cmp = &env->spr[SPR_DCMP];

                }

                qemu_log("6xx %sTLB miss: %cM " TARGET_FMT_lx " %cC "

                         TARGET_FMT_lx " H1 " TARGET_FMT_lx " H2 "

                         TARGET_FMT_lx " %08x\n", es, en, *miss, en, *cmp,

                         env->spr[SPR_HASH1], env->spr[SPR_HASH2],

                         env->error_code);

            }


            msr |= env->crf[0] << 28;

            msr |= env->error_code;  

             

            msr |= ((env->last_way + 1) & (env->nb_ways - 1)) << 17;

            break;

        case POWERPC_EXCP_74xx:

        tlb_miss_74xx:


            if (qemu_log_enabled()) {

                const char *es;

                target_ulong *miss, *cmp;

                int en;



                if (excp == POWERPC_EXCP_IFTLB) {

                    es = "I";

                    en = 'I';

                    miss = &env->spr[SPR_TLBMISS];

                    cmp = &env->spr[SPR_PTEHI];

                } else {

                    if (excp == POWERPC_EXCP_DLTLB) {

                        es = "DL";

                    } else {

                        es = "DS";

                    }

                    en = 'D';

                    miss = &env->spr[SPR_TLBMISS];

                    cmp = &env->spr[SPR_PTEHI];

                }

                qemu_log("74xx %sTLB miss: %cM " TARGET_FMT_lx " %cC "

                         TARGET_FMT_lx " %08x\n", es, en, *miss, en, *cmp,

                         env->error_code);

            }


            msr |= env->error_code;  

            break;

        default:

            cpu_abort(cs, "Invalid data store TLB miss exception\n");

            break;

        }

        goto store_next;

    case POWERPC_EXCP_FPA:        

         

        cpu_abort(cs, "Floating point assist exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_DABR:       

         

        cpu_abort(cs, "DABR exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_IABR:       

         

        cpu_abort(cs, "IABR exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_SMI:        

         

        cpu_abort(cs, "SMI exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_THERM:      

         

        cpu_abort(cs, "Thermal management exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_PERFM:      

        if (lpes1 == 0) {

            new_msr |= (target_ulong)MSR_HVB;

        }

         

        cpu_abort(cs,

                  "Performance counter exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_VPUA:       

         

        cpu_abort(cs, "VPU assist exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_SOFTP:      

         

        cpu_abort(cs,

                  "970 soft-patch exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_MAINT:      

         

        cpu_abort(cs,

                  "970 maintenance exception is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_MEXTBR:     

         

        cpu_abort(cs, "Maskable external exception "

                  "is not implemented yet !\n");

        goto store_next;

    case POWERPC_EXCP_NMEXTBR:    

         

        cpu_abort(cs, "Non maskable external exception "

                  "is not implemented yet !\n");

        goto store_next;

    default:

    excp_invalid:

        cpu_abort(cs, "Invalid PowerPC exception %d. Aborting\n", excp);

        break;

    store_current:

         

        env->spr[srr0] = env->nip - 4;

        break;

    store_next:

         

        env->spr[srr0] = env->nip;

        break;

    }

     

    env->spr[srr1] = msr;

     

    if (asrr0 != -1) {

        env->spr[asrr0] = env->spr[srr0];

    }

    if (asrr1 != -1) {

        env->spr[asrr1] = env->spr[srr1];

    }



    if (env->spr[SPR_LPCR] & LPCR_AIL) {

        new_msr |= (1 << MSR_IR) | (1 << MSR_DR);

    }


    if (excp_model == POWERPC_EXCP_POWER7 ||

        excp_model == POWERPC_EXCP_POWER8) {

        if (env->spr[SPR_LPCR] & LPCR_ILE) {

            new_msr |= (target_ulong)1 << MSR_LE;

        }

    } else if (msr_ile) {

        new_msr |= (target_ulong)1 << MSR_LE;

    }


    if (msr_ile) {

        new_msr |= (target_ulong)1 << MSR_LE;

    }




     

    vector = env->excp_vectors[excp];

    if (vector == (target_ulong)-1ULL) {

        cpu_abort(cs, "Raised an exception without defined vector %d\n",

                  excp);

    }

    vector |= env->excp_prefix;



     

    if (!((msr >> MSR_IR) & 1) || !((msr >> MSR_DR) & 1)) {

        ail = 0;

    }

     

    if (ail) {

        new_msr |= (1 << MSR_IR) | (1 << MSR_DR);

        switch(ail) {

        case AIL_0001_8000:

            vector |= 0x18000;

            break;

        case AIL_C000_0000_0000_4000:

            vector |= 0xc000000000004000ull;

            break;

        default:

            cpu_abort(cs, "Invalid AIL combination %d\n", ail);

            break;

        }

    }


    if (excp_model == POWERPC_EXCP_BOOKE) {

        if (env->spr[SPR_BOOKE_EPCR] & EPCR_ICM) {

             

            new_msr |= (target_ulong)1 << MSR_CM;

        } else {

            vector = (uint32_t)vector;

        }

    } else {

        if (!msr_isf && !(env->mmu_model & POWERPC_MMU_64)) {

            vector = (uint32_t)vector;

        } else {

            new_msr |= (target_ulong)1 << MSR_SF;

        }

    }


     

    env->msr = new_msr & env->msr_mask;

    hreg_compute_hflags(env);

    env->nip = vector;

     

    cs->exception_index = POWERPC_EXCP_NONE;

    env->error_code = 0;



     

    check_tlb_flush(env);

}
