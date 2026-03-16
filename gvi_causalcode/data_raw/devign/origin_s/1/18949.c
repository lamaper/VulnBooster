void cpu_loop(CPUPPCState *env)

{

    CPUState *cs = CPU(ppc_env_get_cpu(env));

    target_siginfo_t info;

    int trapnr;

    target_ulong ret;



    for(;;) {

        cpu_exec_start(cs);

        trapnr = cpu_ppc_exec(cs);

        cpu_exec_end(cs);

        switch(trapnr) {

        case POWERPC_EXCP_NONE:

             

            break;

        case POWERPC_EXCP_CRITICAL:  

            cpu_abort(cs, "Critical interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_MCHECK:    

            cpu_abort(cs, "Machine check exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_DSI:       

            EXCP_DUMP(env, "Invalid data memory access: 0x" TARGET_FMT_lx "\n",

                      env->spr[SPR_DAR]);

             

            switch (env->error_code & 0xFF000000) {

            case 0x40000000:

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_MAPERR;

                break;

            case 0x04000000:

                info.si_signo = TARGET_SIGILL;

                info.si_errno = 0;

                info.si_code = TARGET_ILL_ILLADR;

                break;

            case 0x08000000:

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_ACCERR;

                break;

            default:

                 

                EXCP_DUMP(env, "Invalid segfault errno (%02x)\n",

                          env->error_code);

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_MAPERR;

                break;

            }

            info._sifields._sigfault._addr = env->nip;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_ISI:       

            EXCP_DUMP(env, "Invalid instruction fetch: 0x\n" TARGET_FMT_lx

                      "\n", env->spr[SPR_SRR0]);

             

            switch (env->error_code & 0xFF000000) {

            case 0x40000000:

                info.si_signo = TARGET_SIGSEGV;

            info.si_errno = 0;

                info.si_code = TARGET_SEGV_MAPERR;

                break;

            case 0x10000000:

            case 0x08000000:

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_ACCERR;

                break;

            default:

                 

                EXCP_DUMP(env, "Invalid segfault errno (%02x)\n",

                          env->error_code);

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_MAPERR;

                break;

            }

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_EXTERNAL:  

            cpu_abort(cs, "External interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_ALIGN:     

            EXCP_DUMP(env, "Unaligned memory access\n");

             

            info.si_signo = TARGET_SIGBUS;

            info.si_errno = 0;

            info.si_code = TARGET_BUS_ADRALN;

            info._sifields._sigfault._addr = env->nip;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_PROGRAM:   


             

            switch (env->error_code & ~0xF) {

            case POWERPC_EXCP_FP:

                EXCP_DUMP(env, "Floating point program exception\n");

                info.si_signo = TARGET_SIGFPE;

                info.si_errno = 0;

                switch (env->error_code & 0xF) {

                case POWERPC_EXCP_FP_OX:

                    info.si_code = TARGET_FPE_FLTOVF;

                    break;

                case POWERPC_EXCP_FP_UX:

                    info.si_code = TARGET_FPE_FLTUND;

                    break;

                case POWERPC_EXCP_FP_ZX:

                case POWERPC_EXCP_FP_VXZDZ:

                    info.si_code = TARGET_FPE_FLTDIV;

                    break;

                case POWERPC_EXCP_FP_XX:

                    info.si_code = TARGET_FPE_FLTRES;

                    break;

                case POWERPC_EXCP_FP_VXSOFT:

                    info.si_code = TARGET_FPE_FLTINV;

                    break;

                case POWERPC_EXCP_FP_VXSNAN:

                case POWERPC_EXCP_FP_VXISI:

                case POWERPC_EXCP_FP_VXIDI:

                case POWERPC_EXCP_FP_VXIMZ:

                case POWERPC_EXCP_FP_VXVC:

                case POWERPC_EXCP_FP_VXSQRT:

                case POWERPC_EXCP_FP_VXCVI:

                    info.si_code = TARGET_FPE_FLTSUB;

                    break;

                default:

                    EXCP_DUMP(env, "Unknown floating point exception (%02x)\n",

                              env->error_code);

                    break;

                }

                break;

            case POWERPC_EXCP_INVAL:

                EXCP_DUMP(env, "Invalid instruction\n");

                info.si_signo = TARGET_SIGILL;

                info.si_errno = 0;

                switch (env->error_code & 0xF) {

                case POWERPC_EXCP_INVAL_INVAL:

                    info.si_code = TARGET_ILL_ILLOPC;

                    break;

                case POWERPC_EXCP_INVAL_LSWX:

                    info.si_code = TARGET_ILL_ILLOPN;

                    break;

                case POWERPC_EXCP_INVAL_SPR:

                    info.si_code = TARGET_ILL_PRVREG;

                    break;

                case POWERPC_EXCP_INVAL_FP:

                    info.si_code = TARGET_ILL_COPROC;

                    break;

                default:

                    EXCP_DUMP(env, "Unknown invalid operation (%02x)\n",

                              env->error_code & 0xF);

                    info.si_code = TARGET_ILL_ILLADR;

                    break;

                }

                break;

            case POWERPC_EXCP_PRIV:

                EXCP_DUMP(env, "Privilege violation\n");

                info.si_signo = TARGET_SIGILL;

                info.si_errno = 0;

                switch (env->error_code & 0xF) {

                case POWERPC_EXCP_PRIV_OPC:

                    info.si_code = TARGET_ILL_PRVOPC;

                    break;

                case POWERPC_EXCP_PRIV_REG:

                    info.si_code = TARGET_ILL_PRVREG;

                    break;

                default:

                    EXCP_DUMP(env, "Unknown privilege violation (%02x)\n",

                              env->error_code & 0xF);

                    info.si_code = TARGET_ILL_PRVOPC;

                    break;

                }

                break;

            case POWERPC_EXCP_TRAP:

                cpu_abort(cs, "Tried to call a TRAP\n");

                break;

            default:

                 

                cpu_abort(cs, "Unknown program exception (%02x)\n",

                          env->error_code);

                break;

            }

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_FPU:       

            EXCP_DUMP(env, "No floating point allowed\n");

            info.si_signo = TARGET_SIGILL;

            info.si_errno = 0;

            info.si_code = TARGET_ILL_COPROC;

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_SYSCALL:   

            cpu_abort(cs, "Syscall exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_APU:       

            EXCP_DUMP(env, "No APU instruction allowed\n");

            info.si_signo = TARGET_SIGILL;

            info.si_errno = 0;

            info.si_code = TARGET_ILL_COPROC;

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_DECR:      

            cpu_abort(cs, "Decrementer interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_FIT:       

            cpu_abort(cs, "Fix interval timer interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_WDT:       

            cpu_abort(cs, "Watchdog timer interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_DTLB:      

            cpu_abort(cs, "Data TLB exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_ITLB:      

            cpu_abort(cs, "Instruction TLB exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_SPEU:      

            EXCP_DUMP(env, "No SPE/floating-point instruction allowed\n");

            info.si_signo = TARGET_SIGILL;

            info.si_errno = 0;

            info.si_code = TARGET_ILL_COPROC;

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_EFPDI:     

            cpu_abort(cs, "Embedded floating-point data IRQ not handled\n");

            break;

        case POWERPC_EXCP_EFPRI:     

            cpu_abort(cs, "Embedded floating-point round IRQ not handled\n");

            break;

        case POWERPC_EXCP_EPERFM:    

            cpu_abort(cs, "Performance monitor exception not handled\n");

            break;

        case POWERPC_EXCP_DOORI:     

            cpu_abort(cs, "Doorbell interrupt while in user mode. "

                       "Aborting\n");

            break;

        case POWERPC_EXCP_DOORCI:    

            cpu_abort(cs, "Doorbell critical interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_RESET:     

            cpu_abort(cs, "Reset interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_DSEG:      

            cpu_abort(cs, "Data segment exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_ISEG:      

            cpu_abort(cs, "Instruction segment exception "

                      "while in user mode. Aborting\n");

            break;

         

        case POWERPC_EXCP_HDECR:     

            cpu_abort(cs, "Hypervisor decrementer interrupt "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_TRACE:     

             

            break;

         

        case POWERPC_EXCP_HDSI:      

            cpu_abort(cs, "Hypervisor data storage exception "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_HISI:      

            cpu_abort(cs, "Hypervisor instruction storage exception "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_HDSEG:     

            cpu_abort(cs, "Hypervisor data segment exception "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_HISEG:     

            cpu_abort(cs, "Hypervisor instruction segment exception "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_VPU:       

            EXCP_DUMP(env, "No Altivec instructions allowed\n");

            info.si_signo = TARGET_SIGILL;

            info.si_errno = 0;

            info.si_code = TARGET_ILL_COPROC;

            info._sifields._sigfault._addr = env->nip - 4;

            queue_signal(env, info.si_signo, &info);

            break;

        case POWERPC_EXCP_PIT:       

            cpu_abort(cs, "Programmable interval timer interrupt "

                      "while in user mode. Aborting\n");

            break;

        case POWERPC_EXCP_IO:        

            cpu_abort(cs, "IO error exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_RUNM:      

            cpu_abort(cs, "Run mode exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_EMUL:      

            cpu_abort(cs, "Emulation trap exception not handled\n");

            break;

        case POWERPC_EXCP_IFTLB:     

            cpu_abort(cs, "Instruction fetch TLB exception "

                      "while in user-mode. Aborting");

            break;

        case POWERPC_EXCP_DLTLB:     

            cpu_abort(cs, "Data load TLB exception while in user-mode. "

                      "Aborting");

            break;

        case POWERPC_EXCP_DSTLB:     

            cpu_abort(cs, "Data store TLB exception while in user-mode. "

                      "Aborting");

            break;

        case POWERPC_EXCP_FPA:       

            cpu_abort(cs, "Floating-point assist exception not handled\n");

            break;

        case POWERPC_EXCP_IABR:      

            cpu_abort(cs, "Instruction address breakpoint exception "

                      "not handled\n");

            break;

        case POWERPC_EXCP_SMI:       

            cpu_abort(cs, "System management interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_THERM:     

            cpu_abort(cs, "Thermal interrupt interrupt while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_PERFM:    

            cpu_abort(cs, "Performance monitor exception not handled\n");

            break;

        case POWERPC_EXCP_VPUA:      

            cpu_abort(cs, "Vector assist exception not handled\n");

            break;

        case POWERPC_EXCP_SOFTP:     

            cpu_abort(cs, "Soft patch exception not handled\n");

            break;

        case POWERPC_EXCP_MAINT:     

            cpu_abort(cs, "Maintenance exception while in user mode. "

                      "Aborting\n");

            break;

        case POWERPC_EXCP_STOP:      

             

            break;

        case POWERPC_EXCP_BRANCH:    

             

            break;

        case POWERPC_EXCP_SYSCALL_USER:

             

             

            env->crf[0] &= ~0x1;

            ret = do_syscall(env, env->gpr[0], env->gpr[3], env->gpr[4],

                             env->gpr[5], env->gpr[6], env->gpr[7],

                             env->gpr[8], 0, 0);

            if (ret == -TARGET_ERESTARTSYS) {

                env->nip -= 4;

                break;

            }

            if (ret == (target_ulong)(-TARGET_QEMU_ESIGRETURN)) {

                 

                break;

            }

            if (ret > (target_ulong)(-515)) {

                env->crf[0] |= 0x1;

                ret = -ret;

            }

            env->gpr[3] = ret;

            break;

        case POWERPC_EXCP_STCX:

            if (do_store_exclusive(env)) {

                info.si_signo = TARGET_SIGSEGV;

                info.si_errno = 0;

                info.si_code = TARGET_SEGV_MAPERR;

                info._sifields._sigfault._addr = env->nip;

                queue_signal(env, info.si_signo, &info);

            }

            break;

        case EXCP_DEBUG:

            {

                int sig;



                sig = gdb_handlesig(cs, TARGET_SIGTRAP);

                if (sig) {

                    info.si_signo = sig;

                    info.si_errno = 0;

                    info.si_code = TARGET_TRAP_BRKPT;

                    queue_signal(env, info.si_signo, &info);

                  }

            }

            break;

        case EXCP_INTERRUPT:

             

            break;

        default:

            cpu_abort(cs, "Unknown exception 0x%d. Aborting\n", trapnr);

            break;

        }

        process_pending_signals(env);

    }

}