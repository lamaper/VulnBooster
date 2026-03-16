void gen_intermediate_code(CPUARMState *env, TranslationBlock *tb)

{

    ARMCPU *cpu = arm_env_get_cpu(env);

    CPUState *cs = CPU(cpu);

    DisasContext dc1, *dc = &dc1;

    target_ulong pc_start;

    target_ulong next_page_start;

    int num_insns;

    int max_insns;

    bool end_of_page;



     



     

    if (ARM_TBFLAG_AARCH64_STATE(tb->flags)) {

        gen_intermediate_code_a64(cpu, tb);

        return;

    }



    pc_start = tb->pc;



    dc->tb = tb;



    dc->is_jmp = DISAS_NEXT;

    dc->pc = pc_start;

    dc->singlestep_enabled = cs->singlestep_enabled;

    dc->condjmp = 0;



    dc->aarch64 = 0;

     

    dc->secure_routed_to_el3 = arm_feature(env, ARM_FEATURE_EL3) &&

                               !arm_el_is_aa64(env, 3);

    dc->thumb = ARM_TBFLAG_THUMB(tb->flags);

    dc->sctlr_b = ARM_TBFLAG_SCTLR_B(tb->flags);

    dc->be_data = ARM_TBFLAG_BE_DATA(tb->flags) ? MO_BE : MO_LE;

    dc->condexec_mask = (ARM_TBFLAG_CONDEXEC(tb->flags) & 0xf) << 1;

    dc->condexec_cond = ARM_TBFLAG_CONDEXEC(tb->flags) >> 4;

    dc->mmu_idx = ARM_TBFLAG_MMUIDX(tb->flags);

    dc->current_el = arm_mmu_idx_to_el(dc->mmu_idx);


    dc->user = (dc->current_el == 0);


    dc->ns = ARM_TBFLAG_NS(tb->flags);

    dc->fp_excp_el = ARM_TBFLAG_FPEXC_EL(tb->flags);

    dc->vfp_enabled = ARM_TBFLAG_VFPEN(tb->flags);

    dc->vec_len = ARM_TBFLAG_VECLEN(tb->flags);

    dc->vec_stride = ARM_TBFLAG_VECSTRIDE(tb->flags);

    dc->c15_cpar = ARM_TBFLAG_XSCALE_CPAR(tb->flags);


    dc->cp_regs = cpu->cp_regs;

    dc->features = env->features;



     

    dc->ss_active = ARM_TBFLAG_SS_ACTIVE(tb->flags);

    dc->pstate_ss = ARM_TBFLAG_PSTATE_SS(tb->flags);

    dc->is_ldex = false;

    dc->ss_same_el = false;  



    cpu_F0s = tcg_temp_new_i32();

    cpu_F1s = tcg_temp_new_i32();

    cpu_F0d = tcg_temp_new_i64();

    cpu_F1d = tcg_temp_new_i64();

    cpu_V0 = cpu_F0d;

    cpu_V1 = cpu_F1d;

     

    cpu_M0 = tcg_temp_new_i64();

    next_page_start = (pc_start & TARGET_PAGE_MASK) + TARGET_PAGE_SIZE;

    num_insns = 0;

    max_insns = tb->cflags & CF_COUNT_MASK;

    if (max_insns == 0) {

        max_insns = CF_COUNT_MASK;

    }

    if (max_insns > TCG_MAX_INSNS) {

        max_insns = TCG_MAX_INSNS;

    }



    gen_tb_start(tb);



    tcg_clear_temp_count();



     



     

    if (dc->condexec_mask || dc->condexec_cond)

      {

        TCGv_i32 tmp = tcg_temp_new_i32();

        tcg_gen_movi_i32(tmp, 0);

        store_cpu_field(tmp, condexec_bits);

      }

    do {

        dc->insn_start_idx = tcg_op_buf_count();

        tcg_gen_insn_start(dc->pc,

                           (dc->condexec_cond << 4) | (dc->condexec_mask >> 1),

                           0);

        num_insns++;


         

        if (dc->pc >= 0xffff0000) {

             

            gen_exception_internal(EXCP_KERNEL_TRAP);

            dc->is_jmp = DISAS_EXC;

            break;

        }


        if (arm_dc_feature(dc, ARM_FEATURE_M)) {

             

            assert(dc->pc < 0xfffffff0);

        }




        if (unlikely(!QTAILQ_EMPTY(&cs->breakpoints))) {

            CPUBreakpoint *bp;

            QTAILQ_FOREACH(bp, &cs->breakpoints, entry) {

                if (bp->pc == dc->pc) {

                    if (bp->flags & BP_CPU) {

                        gen_set_condexec(dc);

                        gen_set_pc_im(dc, dc->pc);

                        gen_helper_check_breakpoints(cpu_env);

                         

                        dc->is_jmp = DISAS_UPDATE;

                    } else {

                        gen_exception_internal_insn(dc, 0, EXCP_DEBUG);

                         

                         

                        dc->pc += 2;

                        goto done_generating;

                    }

                    break;

                }

            }

        }



        if (num_insns == max_insns && (tb->cflags & CF_LAST_IO)) {

            gen_io_start();

        }



        if (dc->ss_active && !dc->pstate_ss) {

             

            assert(num_insns == 1);

            gen_exception(EXCP_UDEF, syn_swstep(dc->ss_same_el, 0, 0),

                          default_exception_el(dc));

            goto done_generating;

        }



        if (dc->thumb) {

            disas_thumb_insn(env, dc);

            if (dc->condexec_mask) {

                dc->condexec_cond = (dc->condexec_cond & 0xe)

                                   | ((dc->condexec_mask >> 4) & 1);

                dc->condexec_mask = (dc->condexec_mask << 1) & 0x1f;

                if (dc->condexec_mask == 0) {

                    dc->condexec_cond = 0;

                }

            }

        } else {

            unsigned int insn = arm_ldl_code(env, dc->pc, dc->sctlr_b);

            dc->pc += 4;

            disas_arm_insn(dc, insn);

        }



        if (dc->condjmp && !dc->is_jmp) {

            gen_set_label(dc->condlabel);

            dc->condjmp = 0;

        }



        if (tcg_check_temp_count()) {

            fprintf(stderr, "TCG temporary leak before "TARGET_FMT_lx"\n",

                    dc->pc);

        }



         



         

        end_of_page = (dc->pc >= next_page_start) ||

            ((dc->pc >= next_page_start - 3) && insn_crosses_page(env, dc));



    } while (!dc->is_jmp && !tcg_op_buf_full() &&

             !is_singlestepping(dc) &&

             !singlestep &&

             !end_of_page &&

             num_insns < max_insns);



    if (tb->cflags & CF_LAST_IO) {

        if (dc->condjmp) {

             

            cpu_abort(cs, "IO on conditional branch instruction");

        }

        gen_io_end();

    }



     

    gen_set_condexec(dc);

    if (unlikely(is_singlestepping(dc))) {

         

        switch (dc->is_jmp) {

        case DISAS_SWI:

            gen_ss_advance(dc);

            gen_exception(EXCP_SWI, syn_aa32_svc(dc->svc_imm, dc->thumb),

                          default_exception_el(dc));

            break;

        case DISAS_HVC:

            gen_ss_advance(dc);

            gen_exception(EXCP_HVC, syn_aa32_hvc(dc->svc_imm), 2);

            break;

        case DISAS_SMC:

            gen_ss_advance(dc);

            gen_exception(EXCP_SMC, syn_aa32_smc(), 3);

            break;

        case DISAS_NEXT:

        case DISAS_UPDATE:

            gen_set_pc_im(dc, dc->pc);

             

        default:

             

            gen_singlestep_exception(dc);

        }

    } else {

         

        switch(dc->is_jmp) {

        case DISAS_NEXT:

            gen_goto_tb(dc, 1, dc->pc);

            break;

        case DISAS_UPDATE:

            gen_set_pc_im(dc, dc->pc);

             

        case DISAS_JUMP:

        default:

             

            tcg_gen_exit_tb(0);

            break;

        case DISAS_TB_JUMP:

             

            break;

        case DISAS_WFI:

            gen_helper_wfi(cpu_env);

             

            tcg_gen_exit_tb(0);

            break;

        case DISAS_WFE:

            gen_helper_wfe(cpu_env);

            break;

        case DISAS_YIELD:

            gen_helper_yield(cpu_env);

            break;

        case DISAS_SWI:

            gen_exception(EXCP_SWI, syn_aa32_svc(dc->svc_imm, dc->thumb),

                          default_exception_el(dc));

            break;

        case DISAS_HVC:

            gen_exception(EXCP_HVC, syn_aa32_hvc(dc->svc_imm), 2);

            break;

        case DISAS_SMC:

            gen_exception(EXCP_SMC, syn_aa32_smc(), 3);

            break;

        }

    }



    if (dc->condjmp) {

         

        gen_set_label(dc->condlabel);

        gen_set_condexec(dc);

        if (unlikely(is_singlestepping(dc))) {

            gen_set_pc_im(dc, dc->pc);

            gen_singlestep_exception(dc);

        } else {

            gen_goto_tb(dc, 1, dc->pc);

        }

    }



done_generating:

    gen_tb_end(tb, num_insns);


    if (qemu_loglevel_mask(CPU_LOG_TB_IN_ASM) &&

        qemu_log_in_addr_range(pc_start)) {

        qemu_log_lock();

        qemu_log("----------------\n");

        qemu_log("IN: %s\n", lookup_symbol(pc_start));

        log_target_disas(cs, pc_start, dc->pc - pc_start,

                         dc->thumb | (dc->sctlr_b << 1));

        qemu_log("\n");

        qemu_log_unlock();

    }


    tb->size = dc->pc - pc_start;

    tb->icount = num_insns;

}