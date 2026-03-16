int cpu_exec(CPUState *env1)

{





    uint32_t *saved_regwptr;



    int ret, interrupt_request;

    long (*gen_func)(void);

    TranslationBlock *tb;

    uint8_t *tc_ptr;



    if (cpu_halted(env1) == EXCP_HALTED)

        return EXCP_HALTED;



    cpu_single_env = env1;



    env = env1;

    SAVE_GLOBALS();



    env_to_regs();


     

    CC_SRC = env->eflags & (CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);

    DF = 1 - (2 * ((env->eflags >> 10) & 1));

    CC_OP = CC_OP_EFLAGS;

    env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);



    saved_regwptr = REGWPTR;



    env->cc_op = CC_OP_FLAGS;

    env->cc_dest = env->sr & 0xf;

    env->cc_x = (env->sr >> 4) & 1;










    env->exception_index = -1;



     

    for(;;) {

        if (setjmp(env->jmp_env) == 0) {

            env->current_tb = NULL;

             

            if (env->exception_index >= 0) {

                if (env->exception_index >= EXCP_INTERRUPT) {

                     

                    ret = env->exception_index;

                    break;

                } else if (env->user_mode_only) {


                    do_interrupt_user(env->exception_index,

                                      env->exception_is_int,

                                      env->error_code,

                                      env->exception_next_eip);


                    ret = env->exception_index;

                    break;

                } else {


                     

                    do_interrupt(env->exception_index,

                                 env->exception_is_int,

                                 env->error_code,

                                 env->exception_next_eip, 0);

                     

                    env->old_exception = -1;


                    do_interrupt(env);


                    do_interrupt(env);


                    do_interrupt(env->exception_index);


                    do_interrupt(env);


		    do_interrupt(env);


                    do_interrupt(env);


                    do_interrupt(env);


                    do_interrupt(0);


                }

                env->exception_index = -1;

            }


            if (kqemu_is_ok(env) && env->interrupt_request == 0) {

                int ret;

                env->eflags = env->eflags | cc_table[CC_OP].compute_all() | (DF & DF_MASK);

                ret = kqemu_cpu_exec(env);

                 

                CC_SRC = env->eflags & (CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);

                DF = 1 - (2 * ((env->eflags >> 10) & 1));

                CC_OP = CC_OP_EFLAGS;

                env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);

                if (ret == 1) {

                     

                    longjmp(env->jmp_env, 1);

                } else if (ret == 2) {

                     

                } else {

                    if (env->interrupt_request != 0) {

                         

                    } else {

                         

                        longjmp(env->jmp_env, 1);

                    }

                }

            }




            T0 = 0;  

            for(;;) {

                SAVE_GLOBALS();

                interrupt_request = env->interrupt_request;

                if (__builtin_expect(interrupt_request, 0)


			&& env->hflags & HF_GIF_MASK


				) {

                    if (interrupt_request & CPU_INTERRUPT_DEBUG) {

                        env->interrupt_request &= ~CPU_INTERRUPT_DEBUG;

                        env->exception_index = EXCP_DEBUG;

                        cpu_loop_exit();

                    }


    defined(TARGET_PPC) || defined(TARGET_ALPHA) || defined(TARGET_CRIS)

                    if (interrupt_request & CPU_INTERRUPT_HALT) {

                        env->interrupt_request &= ~CPU_INTERRUPT_HALT;

                        env->halted = 1;

                        env->exception_index = EXCP_HLT;

                        cpu_loop_exit();

                    }



                    if ((interrupt_request & CPU_INTERRUPT_SMI) &&

                        !(env->hflags & HF_SMM_MASK)) {

                        svm_check_intercept(SVM_EXIT_SMI);

                        env->interrupt_request &= ~CPU_INTERRUPT_SMI;

                        do_smm_enter();

                        BREAK_CHAIN;

                    } else if ((interrupt_request & CPU_INTERRUPT_NMI) &&

                        !(env->hflags & HF_NMI_MASK)) {

                        env->interrupt_request &= ~CPU_INTERRUPT_NMI;

                        env->hflags |= HF_NMI_MASK;

                        do_interrupt(EXCP02_NMI, 0, 0, 0, 1);

                        BREAK_CHAIN;

                    } else if ((interrupt_request & CPU_INTERRUPT_HARD) &&

                        (env->eflags & IF_MASK || env->hflags & HF_HIF_MASK) &&

                        !(env->hflags & HF_INHIBIT_IRQ_MASK)) {

                        int intno;

                        svm_check_intercept(SVM_EXIT_INTR);

                        env->interrupt_request &= ~(CPU_INTERRUPT_HARD | CPU_INTERRUPT_VIRQ);

                        intno = cpu_get_pic_interrupt(env);

                        if (loglevel & CPU_LOG_TB_IN_ASM) {

                            fprintf(logfile, "Servicing hardware INT=0x%02x\n", intno);

                        }

                        do_interrupt(intno, 0, 0, 0, 1);

                         

                        BREAK_CHAIN;


                    } else if ((interrupt_request & CPU_INTERRUPT_VIRQ) &&

                        (env->eflags & IF_MASK) && !(env->hflags & HF_INHIBIT_IRQ_MASK)) {

                         int intno;

                          

                         env->interrupt_request &= ~CPU_INTERRUPT_VIRQ;

                         svm_check_intercept(SVM_EXIT_VINTR);

                         intno = ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.int_vector));

                         if (loglevel & CPU_LOG_TB_IN_ASM)

                             fprintf(logfile, "Servicing virtual hardware INT=0x%02x\n", intno);

	                 do_interrupt(intno, 0, 0, -1, 1);

                         stl_phys(env->vm_vmcb + offsetof(struct vmcb, control.int_ctl),

                                  ldl_phys(env->vm_vmcb + offsetof(struct vmcb, control.int_ctl)) & ~V_IRQ_MASK);

                        BREAK_CHAIN;


                    }



                    if ((interrupt_request & CPU_INTERRUPT_RESET)) {

                        cpu_ppc_reset(env);

                    }


                    if (interrupt_request & CPU_INTERRUPT_HARD) {

                        ppc_hw_interrupt(env);

                        if (env->pending_interrupts == 0)

                            env->interrupt_request &= ~CPU_INTERRUPT_HARD;

                        BREAK_CHAIN;

                    }


                    if ((interrupt_request & CPU_INTERRUPT_HARD) &&

                        (env->CP0_Status & env->CP0_Cause & CP0Ca_IP_mask) &&

                        (env->CP0_Status & (1 << CP0St_IE)) &&

                        !(env->CP0_Status & (1 << CP0St_EXL)) &&

                        !(env->CP0_Status & (1 << CP0St_ERL)) &&

                        !(env->hflags & MIPS_HFLAG_DM)) {

                         

                        env->exception_index = EXCP_EXT_INTERRUPT;

                        env->error_code = 0;

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }


                    if ((interrupt_request & CPU_INTERRUPT_HARD) &&

			(env->psret != 0)) {

			int pil = env->interrupt_index & 15;

			int type = env->interrupt_index & 0xf0;



			if (((type == TT_EXTINT) &&

			     (pil == 15 || pil > env->psrpil)) ||

			    type != TT_EXTINT) {

			    env->interrupt_request &= ~CPU_INTERRUPT_HARD;

			    do_interrupt(env->interrupt_index);

			    env->interrupt_index = 0;


                            cpu_check_irqs(env);


                        BREAK_CHAIN;

			}

		    } else if (interrupt_request & CPU_INTERRUPT_TIMER) {

			 

			env->interrupt_request &= ~CPU_INTERRUPT_TIMER;

		    }


                    if (interrupt_request & CPU_INTERRUPT_FIQ

                        && !(env->uncached_cpsr & CPSR_F)) {

                        env->exception_index = EXCP_FIQ;

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }

                     

                    if (interrupt_request & CPU_INTERRUPT_HARD

                        && ((IS_M(env) && env->regs[15] < 0xfffffff0)

                            || !(env->uncached_cpsr & CPSR_I))) {

                        env->exception_index = EXCP_IRQ;

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }


                    if (interrupt_request & CPU_INTERRUPT_HARD) {

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }


                    if (interrupt_request & CPU_INTERRUPT_HARD) {

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }


                    if (interrupt_request & CPU_INTERRUPT_HARD) {

                        do_interrupt(env);

                        BREAK_CHAIN;

                    }


                    if (interrupt_request & CPU_INTERRUPT_HARD

                        && ((env->sr & SR_I) >> SR_I_SHIFT)

                            < env->pending_level) {

                         

                        env->exception_index = env->pending_vector;

                        do_interrupt(1);

                        BREAK_CHAIN;

                    }


                    

                    if (env->interrupt_request & CPU_INTERRUPT_EXITTB) {

                        env->interrupt_request &= ~CPU_INTERRUPT_EXITTB;

                         

                        BREAK_CHAIN;

                    }

                    if (interrupt_request & CPU_INTERRUPT_EXIT) {

                        env->interrupt_request &= ~CPU_INTERRUPT_EXIT;

                        env->exception_index = EXCP_INTERRUPT;

                        cpu_loop_exit();

                    }

                }


                if ((loglevel & CPU_LOG_TB_CPU)) {

                     

                    regs_to_env();


                    env->eflags = env->eflags | cc_table[CC_OP].compute_all() | (DF & DF_MASK);

                    cpu_dump_state(env, logfile, fprintf, X86_DUMP_CCOP);

                    env->eflags &= ~(DF_MASK | CC_O | CC_S | CC_Z | CC_A | CC_P | CC_C);


                    cpu_dump_state(env, logfile, fprintf, 0);


		    REGWPTR = env->regbase + (env->cwp * 16);

		    env->regwptr = REGWPTR;

                    cpu_dump_state(env, logfile, fprintf, 0);


                    cpu_dump_state(env, logfile, fprintf, 0);


                    cpu_m68k_flush_flags(env, env->cc_op);

                    env->cc_op = CC_OP_FLAGS;

                    env->sr = (env->sr & 0xffe0)

                              | env->cc_dest | (env->cc_x << 4);

                    cpu_dump_state(env, logfile, fprintf, 0);


                    cpu_dump_state(env, logfile, fprintf, 0);


		    cpu_dump_state(env, logfile, fprintf, 0);


                    cpu_dump_state(env, logfile, fprintf, 0);


                    cpu_dump_state(env, logfile, fprintf, 0);




                }


                tb = tb_find_fast();


                if ((loglevel & CPU_LOG_EXEC)) {

                    fprintf(logfile, "Trace 0x%08lx [" TARGET_FMT_lx "] %s\n",

                            (long)tb->tc_ptr, tb->pc,

                            lookup_symbol(tb->pc));

                }


                RESTORE_GLOBALS();

                 

                {

                    if (T0 != 0 &&


                        (env->kqemu_enabled != 2) &&


                        tb->page_addr[1] == -1) {

                    spin_lock(&tb_lock);

                    tb_add_jump((TranslationBlock *)(long)(T0 & ~3), T0 & 3, tb);

                    spin_unlock(&tb_lock);

                }

                }

                tc_ptr = tb->tc_ptr;

                env->current_tb = tb;

                 

                gen_func = (void *)tc_ptr;


                __asm__ __volatile__("call	%0\n\t"

                                     "mov	%%o7,%%i0"

                                     :  

                                     : "r" (gen_func)

                                     : "i0", "i1", "i2", "i3", "i4", "i5",

                                       "o0", "o1", "o2", "o3", "o4", "o5",

                                       "l0", "l1", "l2", "l3", "l4", "l5",

                                       "l6", "l7");


                asm volatile ("ble  0(%%sr4,%1)\n"

                              "copy %%r31,%%r18\n"

                              "copy %%r28,%0\n"

                              : "=r" (T0)

                              : "r" (gen_func)

                              : "r1", "r2", "r3", "r4", "r5", "r6", "r7",

                                "r8", "r9", "r10", "r11", "r12", "r13",

                                "r18", "r19", "r20", "r21", "r22", "r23",

                                "r24", "r25", "r26", "r27", "r28", "r29",

                                "r30", "r31");


                asm volatile ("mov pc, %0\n\t"

                              ".global exec_loop\n\t"

                              "exec_loop:\n\t"

                              :  

                              : "r" (gen_func)

                              : "r1", "r2", "r3", "r8", "r9", "r10", "r12", "r14");


		struct fptr {

			void *ip;

			void *gp;

		} fp;



		fp.ip = tc_ptr;

		fp.gp = code_gen_buffer + 2 * (1 << 20);

		(*(void (*)(void)) &fp)();


                T0 = gen_func();


                env->current_tb = NULL;


                if (env->hflags & HF_SOFTMMU_MASK) {

                    env->hflags &= ~HF_SOFTMMU_MASK;

                     

                    T0 = 0;

                }




                if (kqemu_is_ok(env) &&

                    (cpu_get_time_fast() - env->last_io_time) >= MIN_CYCLE_BEFORE_SWITCH) {

                    cpu_loop_exit();

                }


            }  

        } else {

            env_to_regs();

        }

    }  


     

    env->eflags = env->eflags | cc_table[CC_OP].compute_all() | (DF & DF_MASK);




    REGWPTR = saved_regwptr;




    cpu_m68k_flush_flags(env, env->cc_op);

    env->cc_op = CC_OP_FLAGS;

    env->sr = (env->sr & 0xffe0)

              | env->cc_dest | (env->cc_x << 4);










     

    RESTORE_GLOBALS();




     

    cpu_single_env = NULL;

    return ret;

}
