static void gen_mtc0 (DisasContext *ctx, int reg, int sel)

{

    const char *rn = "invalid";



    switch (reg) {

    case 0:

        switch (sel) {

        case 0:

           gen_op_mtc0_index();

            rn = "Index";

            break;

        case 1:

 

            rn = "MVPControl";

 

        case 2:

 

            rn = "MVPConf0";

 

        case 3:

 

            rn = "MVPConf1";

 

        default:

            goto die;

        }

        break;

    case 1:

        switch (sel) {

        case 0:

             

            rn = "Random";

            break;

        case 1:

 

            rn = "VPEControl";

 

        case 2:

 

            rn = "VPEConf0";

 

        case 3:

 

            rn = "VPEConf1";

 

        case 4:

 

            rn = "YQMask";

 

        case 5:

 

            rn = "VPESchedule";

 

        case 6:

 

            rn = "VPEScheFBack";

 

        case 7:

 

            rn = "VPEOpt";

 

        default:

            goto die;

        }

        break;

    case 2:

        switch (sel) {

        case 0:

            gen_op_mtc0_entrylo0();

            rn = "EntryLo0";

            break;

        case 1:

 

            rn = "TCStatus";

 

        case 2:

 

            rn = "TCBind";

 

        case 3:

 

            rn = "TCRestart";

 

        case 4:

 

            rn = "TCHalt";

 

        case 5:

 

            rn = "TCContext";

 

        case 6:

 

            rn = "TCSchedule";

 

        case 7:

 

            rn = "TCScheFBack";

 

        default:

            goto die;

        }

        break;

    case 3:

        switch (sel) {

        case 0:

            gen_op_mtc0_entrylo1();

            rn = "EntryLo1";

            break;

        default:

            goto die;

        }

        break;

    case 4:

        switch (sel) {

        case 0:

            gen_op_mtc0_context();

            rn = "Context";

            break;

        case 1:

 

            rn = "ContextConfig";

 

        default:

            goto die;

        }

        break;

    case 5:

        switch (sel) {

        case 0:

            gen_op_mtc0_pagemask();

            rn = "PageMask";

            break;

        case 1:

            gen_op_mtc0_pagegrain();

            rn = "PageGrain";

            break;

        default:

            goto die;

        }

        break;

    case 6:

        switch (sel) {

        case 0:

            gen_op_mtc0_wired();

            rn = "Wired";

            break;

        case 1:

 

            rn = "SRSConf0";

 

        case 2:

 

            rn = "SRSConf1";

 

        case 3:

 

            rn = "SRSConf2";

 

        case 4:

 

            rn = "SRSConf3";

 

        case 5:

 

            rn = "SRSConf4";

 

        default:

            goto die;

        }

        break;

    case 7:

        switch (sel) {

        case 0:

            gen_op_mtc0_hwrena();

            rn = "HWREna";

            break;

        default:

            goto die;

        }

        break;

    case 8:

         

        rn = "BadVaddr";

        break;

    case 9:

        switch (sel) {

        case 0:

            gen_op_mtc0_count();

            rn = "Count";

            break;

         

        default:

            goto die;

        }

         

        ctx->bstate = BS_STOP;

        break;

    case 10:

        switch (sel) {

        case 0:

            gen_op_mtc0_entryhi();

            rn = "EntryHi";

            break;

        default:

            goto die;

        }

        break;

    case 11:

        switch (sel) {

        case 0:

            gen_op_mtc0_compare();

            rn = "Compare";

            break;

         

        default:

            goto die;

        }

         

        ctx->bstate = BS_STOP;

        break;

    case 12:

        switch (sel) {

        case 0:

            gen_op_mtc0_status();

             

            gen_save_pc(ctx->pc + 4);

            ctx->bstate = BS_EXCP;

            rn = "Status";

            break;

        case 1:

            gen_op_mtc0_intctl();

             

            ctx->bstate = BS_STOP;

            rn = "IntCtl";

            break;

        case 2:

            gen_op_mtc0_srsctl();

             

            ctx->bstate = BS_STOP;

            rn = "SRSCtl";

            break;

        case 3:

            gen_op_mtc0_srsmap();

             

            ctx->bstate = BS_STOP;

            rn = "SRSMap";

            break;

        default:

            goto die;

        }

        break;

    case 13:

        switch (sel) {

        case 0:

            gen_op_mtc0_cause();

            rn = "Cause";

            break;

        default:

            goto die;

        }

         

        ctx->bstate = BS_STOP;

        break;

    case 14:

        switch (sel) {

        case 0:

            gen_op_mtc0_epc();

            rn = "EPC";

            break;

        default:

            goto die;

        }

        break;

    case 15:

        switch (sel) {

        case 0:

             

            rn = "PRid";

            break;

        case 1:

            gen_op_mtc0_ebase();

            rn = "EBase";

            break;

        default:

            goto die;

        }

        break;

    case 16:

        switch (sel) {

        case 0:

            gen_op_mtc0_config0();

            rn = "Config";

             

            ctx->bstate = BS_STOP;

            break;

        case 1:

             

            rn = "Config1";

            break;

        case 2:

            gen_op_mtc0_config2();

            rn = "Config2";

             

            ctx->bstate = BS_STOP;

            break;

        case 3:

             

            rn = "Config3";

            break;

         

         

        case 6:

             

            rn = "Config6";

            break;

        case 7:

             

            rn = "Config7";

            break;

        default:

            rn = "Invalid config selector";

            goto die;

        }

        break;

    case 17:

        switch (sel) {

        case 0:

             

            rn = "LLAddr";

            break;

        default:

            goto die;

        }

        break;

    case 18:

        switch (sel) {

        case 0 ... 7:

            gen_op_mtc0_watchlo(sel);

            rn = "WatchLo";

            break;

        default:

            goto die;

        }

        break;

    case 19:

        switch (sel) {

        case 0 ... 7:

            gen_op_mtc0_watchhi(sel);

            rn = "WatchHi";

            break;

        default:

            goto die;

        }

        break;

    case 20:

        switch (sel) {

        case 0:


            gen_op_mtc0_xcontext();

            rn = "XContext";

            break;


        default:

            goto die;

        }

        break;

    case 21:

        

        switch (sel) {

        case 0:

            gen_op_mtc0_framemask();

            rn = "Framemask";

            break;

        default:

            goto die;

        }

        break;

    case 22:

         

        rn = "Diagnostic";  

        break;

    case 23:

        switch (sel) {

        case 0:

            gen_op_mtc0_debug();  

             

            gen_save_pc(ctx->pc + 4);

            ctx->bstate = BS_EXCP;

            rn = "Debug";

            break;

        case 1:

 

            rn = "TraceControl";

             

            ctx->bstate = BS_STOP;

 

        case 2:

 

            rn = "TraceControl2";

             

            ctx->bstate = BS_STOP;

 

        case 3:

             

            ctx->bstate = BS_STOP;

 

            rn = "UserTraceData";

             

            ctx->bstate = BS_STOP;

 

        case 4:

 

             

            ctx->bstate = BS_STOP;

            rn = "TraceBPC";

 

        default:

            goto die;

        }

        break;

    case 24:

        switch (sel) {

        case 0:

            gen_op_mtc0_depc();  

            rn = "DEPC";

            break;

        default:

            goto die;

        }

        break;

    case 25:

        switch (sel) {

        case 0:

            gen_op_mtc0_performance0();

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

         

        rn = "ECC";

        break;

    case 27:

        switch (sel) {

        case 0 ... 3:

             

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

            gen_op_mtc0_taglo();

            rn = "TagLo";

            break;

        case 1:

        case 3:

        case 5:

        case 7:

            gen_op_mtc0_datalo();

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

            gen_op_mtc0_taghi();

            rn = "TagHi";

            break;

        case 1:

        case 3:

        case 5:

        case 7:

            gen_op_mtc0_datahi();

            rn = "DataHi";

            break;

        default:

            rn = "invalid sel";

            goto die;

        }

       break;

    case 30:

        switch (sel) {

        case 0:

            gen_op_mtc0_errorepc();

            rn = "ErrorEPC";

            break;

        default:

            goto die;

        }

        break;

    case 31:

        switch (sel) {

        case 0:

            gen_op_mtc0_desave();  

            rn = "DESAVE";

            break;

        default:

            goto die;

        }

         

        ctx->bstate = BS_STOP;

        break;

    default:

       goto die;

    }


    if (loglevel & CPU_LOG_TB_IN_ASM) {

        fprintf(logfile, "mtc0 %s (reg %d sel %d)\n",

                rn, reg, sel);

    }


    return;



die:


    if (loglevel & CPU_LOG_TB_IN_ASM) {

        fprintf(logfile, "mtc0 %s (reg %d sel %d)\n",

                rn, reg, sel);

    }


    generate_exception(ctx, EXCP_RI);

}
