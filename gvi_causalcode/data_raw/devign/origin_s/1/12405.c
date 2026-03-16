void cpu_loop (CPUSPARCState *env)

{

    int trapnr, ret;

    target_siginfo_t info;



    while (1) {

        trapnr = cpu_sparc_exec (env);



        switch (trapnr) {


        case 0x88:

        case 0x90:


        case 0x110:

        case 0x16d:


            ret = do_syscall (env, env->gregs[1],

                              env->regwptr[0], env->regwptr[1],

                              env->regwptr[2], env->regwptr[3],

                              env->regwptr[4], env->regwptr[5]);

            if ((unsigned int)ret >= (unsigned int)(-515)) {


                env->xcc |= PSR_CARRY;


                env->psr |= PSR_CARRY;


                ret = -ret;

            } else {


                env->xcc &= ~PSR_CARRY;


                env->psr &= ~PSR_CARRY;


            }

            env->regwptr[0] = ret;

             

            env->pc = env->npc;

            env->npc = env->npc + 4;

            break;

        case 0x83:  


        case 0x103:


            flush_windows(env);

             

            env->pc = env->npc;

            env->npc = env->npc + 4;

            break;


        case TT_WIN_OVF:  

            save_window(env);

            break;

        case TT_WIN_UNF:  

            restore_window(env);

            break;

        case TT_TFAULT:

        case TT_DFAULT:

            {

                info.si_signo = SIGSEGV;

                info.si_errno = 0;

                 

                info.si_code = TARGET_SEGV_MAPERR;

                info._sifields._sigfault._addr = env->mmuregs[4];

                queue_signal(env, info.si_signo, &info);

            }

            break;


        case TT_SPILL:  

            save_window(env);

            break;

        case TT_FILL:  

            restore_window(env);

            break;

        case TT_TFAULT:

        case TT_DFAULT:

            {

                info.si_signo = SIGSEGV;

                info.si_errno = 0;

                 

                info.si_code = TARGET_SEGV_MAPERR;

                if (trapnr == TT_DFAULT)

                    info._sifields._sigfault._addr = env->dmmuregs[4];

                else

                    info._sifields._sigfault._addr = env->tsptr->tpc;

                queue_signal(env, info.si_signo, &info);

            }

            break;


        case 0x16e:

            flush_windows(env);

            sparc64_get_context(env);

            break;

        case 0x16f:

            flush_windows(env);

            sparc64_set_context(env);

            break;



        case EXCP_INTERRUPT:

             

            break;

        case EXCP_DEBUG:

            {

                int sig;



                sig = gdb_handlesig (env, TARGET_SIGTRAP);

                if (sig)

                  {

                    info.si_signo = sig;

                    info.si_errno = 0;

                    info.si_code = TARGET_TRAP_BRKPT;

                    queue_signal(env, info.si_signo, &info);

                  }

            }

            break;

        default:

            printf ("Unhandled trap: 0x%x\n", trapnr);

            cpu_dump_state(env, stderr, fprintf, 0);

            exit (1);

        }

        process_pending_signals (env);

    }

}
