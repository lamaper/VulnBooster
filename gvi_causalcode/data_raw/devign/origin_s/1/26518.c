static void do_v7m_exception_exit(ARMCPU *cpu)

{

    CPUARMState *env = &cpu->env;

    CPUState *cs = CPU(cpu);

    uint32_t excret;

    uint32_t xpsr;

    bool ufault = false;

    bool sfault = false;

    bool return_to_sp_process;

    bool return_to_handler;

    bool rettobase = false;

    bool exc_secure = false;

    bool return_to_secure;



     

    assert(arm_v7m_is_handler_mode(env));



     

    excret = env->regs[15];

    if (env->thumb) {

        excret |= 1;

    }



    qemu_log_mask(CPU_LOG_INT, "Exception return: magic PC %" PRIx32

                  " previous exception %d\n",

                  excret, env->v7m.exception);



    if ((excret & R_V7M_EXCRET_RES1_MASK) != R_V7M_EXCRET_RES1_MASK) {

        qemu_log_mask(LOG_GUEST_ERROR, "M profile: zero high bits in exception "

                      "exit PC value 0x%" PRIx32 " are UNPREDICTABLE\n",

                      excret);

    }



    if (arm_feature(env, ARM_FEATURE_M_SECURITY)) {

         

        if (!env->v7m.secure &&

            ((excret & R_V7M_EXCRET_ES_MASK) ||

             !(excret & R_V7M_EXCRET_DCRS_MASK))) {

            sfault = 1;

             

            excret &= ~R_V7M_EXCRET_ES_MASK;

        }

    }



    if (env->v7m.exception != ARMV7M_EXCP_NMI) {

         

        if (arm_feature(env, ARM_FEATURE_M_SECURITY)) {

            exc_secure = excret & R_V7M_EXCRET_ES_MASK;

            if (armv7m_nvic_raw_execution_priority(env->nvic) >= 0) {

                env->v7m.faultmask[exc_secure] = 0;

            }

        } else {

            env->v7m.faultmask[M_REG_NS] = 0;

        }

    }



    switch (armv7m_nvic_complete_irq(env->nvic, env->v7m.exception,

                                     exc_secure)) {

    case -1:

         

        ufault = true;

        break;

    case 0:

         

        break;

    case 1:

         

        rettobase = true;

        break;

    default:

        g_assert_not_reached();

    }



    return_to_handler = !(excret & R_V7M_EXCRET_MODE_MASK);

    return_to_sp_process = excret & R_V7M_EXCRET_SPSEL_MASK;

    return_to_secure = arm_feature(env, ARM_FEATURE_M_SECURITY) &&

        (excret & R_V7M_EXCRET_S_MASK);



    if (arm_feature(env, ARM_FEATURE_V8)) {

        if (!arm_feature(env, ARM_FEATURE_M_SECURITY)) {

             

            if ((excret & R_V7M_EXCRET_S_MASK) ||

                (excret & R_V7M_EXCRET_ES_MASK) ||

                !(excret & R_V7M_EXCRET_DCRS_MASK)) {

                ufault = true;

            }

        }

        if (excret & R_V7M_EXCRET_RES0_MASK) {

            ufault = true;

        }

    } else {

         

        switch (excret & 0xf) {

        case 1:  

            break;

        case 13:  

        case 9:  

             

            if (!rettobase &&

                !(env->v7m.ccr[env->v7m.secure] &

                  R_V7M_CCR_NONBASETHRDENA_MASK)) {

                ufault = true;

            }

            break;

        default:

            ufault = true;

        }

    }



    if (sfault) {

        env->v7m.sfsr |= R_V7M_SFSR_INVER_MASK;

        armv7m_nvic_set_pending(env->nvic, ARMV7M_EXCP_SECURE, false);

        v7m_exception_taken(cpu, excret);

        qemu_log_mask(CPU_LOG_INT, "...taking SecureFault on existing "

                      "stackframe: failed EXC_RETURN.ES validity check\n");

        return;

    }



    if (ufault) {

         

        env->v7m.cfsr[env->v7m.secure] |= R_V7M_CFSR_INVPC_MASK;

        armv7m_nvic_set_pending(env->nvic, ARMV7M_EXCP_USAGE, env->v7m.secure);

        v7m_exception_taken(cpu, excret);

        qemu_log_mask(CPU_LOG_INT, "...taking UsageFault on existing "

                      "stackframe: failed exception return integrity check\n");

        return;

    }



     

    write_v7m_control_spsel_for_secstate(env, return_to_sp_process, exc_secure);



    switch_v7m_security_state(env, return_to_secure);



    {

         

        uint32_t *frame_sp_p = get_v7m_sp_ptr(env,

                                              return_to_secure,

                                              !return_to_handler,

                                              return_to_sp_process);

        uint32_t frameptr = *frame_sp_p;



        if (!QEMU_IS_ALIGNED(frameptr, 8) &&

            arm_feature(env, ARM_FEATURE_V8)) {

            qemu_log_mask(LOG_GUEST_ERROR,

                          "M profile exception return with non-8-aligned SP "

                          "for destination state is UNPREDICTABLE\n");

        }



         

        if (return_to_secure &&

            ((excret & R_V7M_EXCRET_ES_MASK) == 0 ||

             (excret & R_V7M_EXCRET_DCRS_MASK) == 0)) {

            uint32_t expected_sig = 0xfefa125b;

            uint32_t actual_sig = ldl_phys(cs->as, frameptr);



            if (expected_sig != actual_sig) {

                 

                env->v7m.sfsr |= R_V7M_SFSR_INVIS_MASK;

                armv7m_nvic_set_pending(env->nvic, ARMV7M_EXCP_SECURE, false);

                v7m_exception_taken(cpu, excret);

                qemu_log_mask(CPU_LOG_INT, "...taking SecureFault on existing "

                              "stackframe: failed exception return integrity "

                              "signature check\n");

                return;

            }



            env->regs[4] = ldl_phys(cs->as, frameptr + 0x8);

            env->regs[5] = ldl_phys(cs->as, frameptr + 0xc);

            env->regs[6] = ldl_phys(cs->as, frameptr + 0x10);

            env->regs[7] = ldl_phys(cs->as, frameptr + 0x14);

            env->regs[8] = ldl_phys(cs->as, frameptr + 0x18);

            env->regs[9] = ldl_phys(cs->as, frameptr + 0x1c);

            env->regs[10] = ldl_phys(cs->as, frameptr + 0x20);

            env->regs[11] = ldl_phys(cs->as, frameptr + 0x24);



            frameptr += 0x28;

        }



         

        env->regs[0] = ldl_phys(cs->as, frameptr);

        env->regs[1] = ldl_phys(cs->as, frameptr + 0x4);

        env->regs[2] = ldl_phys(cs->as, frameptr + 0x8);

        env->regs[3] = ldl_phys(cs->as, frameptr + 0xc);

        env->regs[12] = ldl_phys(cs->as, frameptr + 0x10);

        env->regs[14] = ldl_phys(cs->as, frameptr + 0x14);

        env->regs[15] = ldl_phys(cs->as, frameptr + 0x18);



         

        if (env->regs[15] & 1) {

            env->regs[15] &= ~1U;

            if (!arm_feature(env, ARM_FEATURE_V8)) {

                qemu_log_mask(LOG_GUEST_ERROR,

                              "M profile return from interrupt with misaligned "

                              "PC is UNPREDICTABLE on v7M\n");

            }

        }



        xpsr = ldl_phys(cs->as, frameptr + 0x1c);



        if (arm_feature(env, ARM_FEATURE_V8)) {

             

            bool will_be_handler = (xpsr & XPSR_EXCP) != 0;

            if (return_to_handler != will_be_handler) {

                 

                armv7m_nvic_set_pending(env->nvic, ARMV7M_EXCP_USAGE,

                                        env->v7m.secure);

                env->v7m.cfsr[env->v7m.secure] |= R_V7M_CFSR_INVPC_MASK;

                v7m_exception_taken(cpu, excret);

                qemu_log_mask(CPU_LOG_INT, "...taking UsageFault on existing "

                              "stackframe: failed exception return integrity "

                              "check\n");

                return;

            }

        }



         

        frameptr += 0x20;

         

        if (xpsr & XPSR_SPREALIGN) {

            frameptr |= 4;

        }

        *frame_sp_p = frameptr;

    }

     

    xpsr_write(env, xpsr, ~XPSR_SPREALIGN);



     

    if (return_to_handler != arm_v7m_is_handler_mode(env)) {

         

        assert(!arm_feature(env, ARM_FEATURE_V8));

        armv7m_nvic_set_pending(env->nvic, ARMV7M_EXCP_USAGE, false);

        env->v7m.cfsr[env->v7m.secure] |= R_V7M_CFSR_INVPC_MASK;

        v7m_push_stack(cpu);

        v7m_exception_taken(cpu, excret);

        qemu_log_mask(CPU_LOG_INT, "...taking UsageFault on new stackframe: "

                      "failed exception return integrity check\n");

        return;

    }



     

    arm_clear_exclusive(env);

    qemu_log_mask(CPU_LOG_INT, "...successful exception return\n");

}
