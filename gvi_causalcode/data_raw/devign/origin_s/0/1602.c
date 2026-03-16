static void gen_mfc0(DisasContext *ctx, TCGv arg, int reg, int sel)

{

    const char *rn = "invalid";



    if (sel != 0)

        check_insn(ctx, ISA_MIPS32);



    switch (reg) {

    case 0:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Index));

            rn = "Index";

            break;

        case 1:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_mvpcontrol(arg, cpu_env);

            rn = "MVPControl";

            break;

        case 2:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_mvpconf0(arg, cpu_env);

            rn = "MVPConf0";

            break;

        case 3:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_mvpconf1(arg, cpu_env);

            rn = "MVPConf1";

            break;

        default:

            goto die;

        }

        break;

    case 1:

        switch (sel) {

        case 0:

            gen_helper_mfc0_random(arg, cpu_env);

            rn = "Random";

            break;

        case 1:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_VPEControl));

            rn = "VPEControl";

            break;

        case 2:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_VPEConf0));

            rn = "VPEConf0";

            break;

        case 3:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_VPEConf1));

            rn = "VPEConf1";

            break;

        case 4:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load64(arg, offsetof(CPUMIPSState, CP0_YQMask));

            rn = "YQMask";

            break;

        case 5:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load64(arg, offsetof(CPUMIPSState, CP0_VPESchedule));

            rn = "VPESchedule";

            break;

        case 6:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load64(arg, offsetof(CPUMIPSState, CP0_VPEScheFBack));

            rn = "VPEScheFBack";

            break;

        case 7:

            check_insn(ctx, ASE_MT);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_VPEOpt));

            rn = "VPEOpt";

            break;

        default:

            goto die;

        }

        break;

    case 2:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_EntryLo0));


            if (ctx->rxi) {

                TCGv tmp = tcg_temp_new();

                tcg_gen_andi_tl(tmp, arg, (3ull << 62));

                tcg_gen_shri_tl(tmp, tmp, 32);

                tcg_gen_or_tl(arg, arg, tmp);

                tcg_temp_free(tmp);

            }


            tcg_gen_ext32s_tl(arg, arg);

            rn = "EntryLo0";

            break;

        case 1:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tcstatus(arg, cpu_env);

            rn = "TCStatus";

            break;

        case 2:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tcbind(arg, cpu_env);

            rn = "TCBind";

            break;

        case 3:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tcrestart(arg, cpu_env);

            rn = "TCRestart";

            break;

        case 4:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tchalt(arg, cpu_env);

            rn = "TCHalt";

            break;

        case 5:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tccontext(arg, cpu_env);

            rn = "TCContext";

            break;

        case 6:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tcschedule(arg, cpu_env);

            rn = "TCSchedule";

            break;

        case 7:

            check_insn(ctx, ASE_MT);

            gen_helper_mfc0_tcschefback(arg, cpu_env);

            rn = "TCScheFBack";

            break;

        default:

            goto die;

        }

        break;

    case 3:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_EntryLo1));


            if (ctx->rxi) {

                TCGv tmp = tcg_temp_new();

                tcg_gen_andi_tl(tmp, arg, (3ull << 62));

                tcg_gen_shri_tl(tmp, tmp, 32);

                tcg_gen_or_tl(arg, arg, tmp);

                tcg_temp_free(tmp);

            }


            tcg_gen_ext32s_tl(arg, arg);

            rn = "EntryLo1";

            break;

        default:

            goto die;

        }

        break;

    case 4:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_Context));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "Context";

            break;

        case 1:

 

            rn = "ContextConfig";

            goto die;

 

        case 2:

            if (ctx->ulri) {

                tcg_gen_ld32s_tl(arg, cpu_env,

                                 offsetof(CPUMIPSState,

                                          active_tc.CP0_UserLocal));

                rn = "UserLocal";

            } else {

                tcg_gen_movi_tl(arg, 0);

            }

            break;

        default:

            goto die;

        }

        break;

    case 5:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_PageMask));

            rn = "PageMask";

            break;

        case 1:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_PageGrain));

            rn = "PageGrain";

            break;

        default:

            goto die;

        }

        break;

    case 6:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Wired));

            rn = "Wired";

            break;

        case 1:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSConf0));

            rn = "SRSConf0";

            break;

        case 2:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSConf1));

            rn = "SRSConf1";

            break;

        case 3:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSConf2));

            rn = "SRSConf2";

            break;

        case 4:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSConf3));

            rn = "SRSConf3";

            break;

        case 5:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSConf4));

            rn = "SRSConf4";

            break;

        default:

            goto die;

        }

        break;

    case 7:

        switch (sel) {

        case 0:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_HWREna));

            rn = "HWREna";

            break;

        default:

            goto die;

        }

        break;

    case 8:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_BadVAddr));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "BadVAddr";

            break;

        case 1:

            if (ctx->bi) {

                gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_BadInstr));

                rn = "BadInstr";

            } else {

                gen_mfc0_unimplemented(ctx, arg);

            }

            break;

        case 2:

            if (ctx->bp) {

                gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_BadInstrP));

                rn = "BadInstrP";

            } else {

                gen_mfc0_unimplemented(ctx, arg);

            }

            break;

        default:

            goto die;

        }

        break;

    case 9:

        switch (sel) {

        case 0:

             

            if (use_icount)

                gen_io_start();

            gen_helper_mfc0_count(arg, cpu_env);

            if (use_icount) {

                gen_io_end();

            }

             

            ctx->bstate = BS_STOP;

            rn = "Count";

            break;

         

        default:

            goto die;

        }

        break;

    case 10:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_EntryHi));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "EntryHi";

            break;

        default:

            goto die;

        }

        break;

    case 11:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Compare));

            rn = "Compare";

            break;

         

        default:

            goto die;

        }

        break;

    case 12:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Status));

            rn = "Status";

            break;

        case 1:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_IntCtl));

            rn = "IntCtl";

            break;

        case 2:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSCtl));

            rn = "SRSCtl";

            break;

        case 3:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_SRSMap));

            rn = "SRSMap";

            break;

        default:

            goto die;

       }

        break;

    case 13:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Cause));

            rn = "Cause";

            break;

        default:

            goto die;

       }

        break;

    case 14:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_EPC));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "EPC";

            break;

        default:

            goto die;

        }

        break;

    case 15:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_PRid));

            rn = "PRid";

            break;

        case 1:

            check_insn(ctx, ISA_MIPS32R2);

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_EBase));

            rn = "EBase";

            break;

        default:

            goto die;

       }

        break;

    case 16:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config0));

            rn = "Config";

            break;

        case 1:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config1));

            rn = "Config1";

            break;

        case 2:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config2));

            rn = "Config2";

            break;

        case 3:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config3));

            rn = "Config3";

            break;

        case 4:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config4));

            rn = "Config4";

            break;

        case 5:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config5));

            rn = "Config5";

            break;

         

        case 6:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config6));

            rn = "Config6";

            break;

        case 7:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Config7));

            rn = "Config7";

            break;

        default:

            goto die;

        }

        break;

    case 17:

        switch (sel) {

        case 0:

            gen_helper_mfc0_lladdr(arg, cpu_env);

            rn = "LLAddr";

            break;

        default:

            goto die;

        }

        break;

    case 18:

        switch (sel) {

        case 0 ... 7:

            gen_helper_1e0i(mfc0_watchlo, arg, sel);

            rn = "WatchLo";

            break;

        default:

            goto die;

        }

        break;

    case 19:

        switch (sel) {

        case 0 ...7:

            gen_helper_1e0i(mfc0_watchhi, arg, sel);

            rn = "WatchHi";

            break;

        default:

            goto die;

        }

        break;

    case 20:

        switch (sel) {

        case 0:


            check_insn(ctx, ISA_MIPS3);

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_XContext));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "XContext";

            break;


        default:

            goto die;

        }

        break;

    case 21:

        

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Framemask));

            rn = "Framemask";

            break;

        default:

            goto die;

        }

        break;

    case 22:

        tcg_gen_movi_tl(arg, 0);  

        rn = "'Diagnostic";  

        break;

    case 23:

        switch (sel) {

        case 0:

            gen_helper_mfc0_debug(arg, cpu_env);  

            rn = "Debug";

            break;

        case 1:

 

            rn = "TraceControl";

 

        case 2:

 

            rn = "TraceControl2";

 

        case 3:

 

            rn = "UserTraceData";

 

        case 4:

 

            rn = "TraceBPC";

 

        default:

            goto die;

        }

        break;

    case 24:

        switch (sel) {

        case 0:

             

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_DEPC));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "DEPC";

            break;

        default:

            goto die;

        }

        break;

    case 25:

        switch (sel) {

        case 0:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_Performance0));

            rn = "Performance0";

            break;

        case 1:

 

            rn = "Performance1";

 

        case 2:

 

            rn = "Performance2";

 

        case 3:

 

            rn = "Performance3";

 

        case 4:

 

            rn = "Performance4";

 

        case 5:

 

            rn = "Performance5";

 

        case 6:

 

            rn = "Performance6";

 

        case 7:

 

            rn = "Performance7";

 

        default:

            goto die;

        }

        break;

    case 26:

        tcg_gen_movi_tl(arg, 0);  

        rn = "ECC";

        break;

    case 27:

        switch (sel) {

        case 0 ... 3:

            tcg_gen_movi_tl(arg, 0);  

            rn = "CacheErr";

            break;

        default:

            goto die;

        }

        break;

    case 28:

        switch (sel) {

        case 0:

        case 2:

        case 4:

        case 6:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_TagLo));

            rn = "TagLo";

            break;

        case 1:

        case 3:

        case 5:

        case 7:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_DataLo));

            rn = "DataLo";

            break;

        default:

            goto die;

        }

        break;

    case 29:

        switch (sel) {

        case 0:

        case 2:

        case 4:

        case 6:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_TagHi));

            rn = "TagHi";

            break;

        case 1:

        case 3:

        case 5:

        case 7:

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_DataHi));

            rn = "DataHi";

            break;

        default:

            goto die;

        }

        break;

    case 30:

        switch (sel) {

        case 0:

            tcg_gen_ld_tl(arg, cpu_env, offsetof(CPUMIPSState, CP0_ErrorEPC));

            tcg_gen_ext32s_tl(arg, arg);

            rn = "ErrorEPC";

            break;

        default:

            goto die;

        }

        break;

    case 31:

        switch (sel) {

        case 0:

             

            gen_mfc0_load32(arg, offsetof(CPUMIPSState, CP0_DESAVE));

            rn = "DESAVE";

            break;

        case 2 ... 7:

            if (ctx->kscrexist & (1 << sel)) {

                tcg_gen_ld_tl(arg, cpu_env,

                              offsetof(CPUMIPSState, CP0_KScratch[sel-2]));

                tcg_gen_ext32s_tl(arg, arg);

                rn = "KScratch";

            } else {

                gen_mfc0_unimplemented(ctx, arg);

            }

            break;

        default:

            goto die;

        }

        break;

    default:

       goto die;

    }

    (void)rn;  

    LOG_DISAS("mfc0 %s (reg %d sel %d)\n", rn, reg, sel);

    return;



die:

    LOG_DISAS("mfc0 %s (reg %d sel %d)\n", rn, reg, sel);

    generate_exception(ctx, EXCP_RI);

}
