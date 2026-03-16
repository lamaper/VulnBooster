static void gen_compute_compact_branch(DisasContext *ctx, uint32_t opc,

                                       int rs, int rt, int32_t offset)

{

    int bcond_compute = 0;

    TCGv t0 = tcg_temp_new();

    TCGv t1 = tcg_temp_new();



    if (ctx->hflags & MIPS_HFLAG_BMASK) {


        LOG_DISAS("Branch in delay / forbidden slot at PC 0x" TARGET_FMT_lx

                  "\n", ctx->pc);


        generate_exception(ctx, EXCP_RI);

        goto out;

    }



     

    switch (opc) {

     

    case OPC_BOVC:  

    case OPC_BNVC:  

        gen_load_gpr(t0, rs);

        gen_load_gpr(t1, rt);

        bcond_compute = 1;

        ctx->btarget = addr_add(ctx, ctx->pc + 4, offset);

        if (rs <= rt && rs == 0) {

             

            tcg_gen_movi_tl(cpu_gpr[31], ctx->pc + 4);

        }

        break;

    case OPC_BLEZC:  

    case OPC_BGTZC:  

        gen_load_gpr(t0, rs);

        gen_load_gpr(t1, rt);

        bcond_compute = 1;

        ctx->btarget = addr_add(ctx, ctx->pc + 4, offset);

        break;

    case OPC_BLEZALC:  

    case OPC_BGTZALC:  

        if (rs == 0 || rs == rt) {

             

             

            tcg_gen_movi_tl(cpu_gpr[31], ctx->pc + 4);

        }

        gen_load_gpr(t0, rs);

        gen_load_gpr(t1, rt);

        bcond_compute = 1;

        ctx->btarget = addr_add(ctx, ctx->pc + 4, offset);

        break;

    case OPC_BC:

    case OPC_BALC:

        ctx->btarget = addr_add(ctx, ctx->pc + 4, offset);

        break;

    case OPC_BEQZC:

    case OPC_BNEZC:

        if (rs != 0) {

             

            gen_load_gpr(t0, rs);

            bcond_compute = 1;

            ctx->btarget = addr_add(ctx, ctx->pc + 4, offset);

        } else {

             

            TCGv tbase = tcg_temp_new();

            TCGv toffset = tcg_temp_new();



            gen_load_gpr(tbase, rt);

            tcg_gen_movi_tl(toffset, offset);

            gen_op_addr_add(ctx, btarget, tbase, toffset);

            tcg_temp_free(tbase);

            tcg_temp_free(toffset);

        }

        break;

    default:

        MIPS_INVAL("Compact branch/jump");

        generate_exception(ctx, EXCP_RI);

        goto out;

    }



    if (bcond_compute == 0) {

         

        switch (opc) {

        case OPC_JIALC:

            tcg_gen_movi_tl(cpu_gpr[31], ctx->pc + 4);

             

        case OPC_JIC:

            ctx->hflags |= MIPS_HFLAG_BR;

            break;

        case OPC_BALC:

            tcg_gen_movi_tl(cpu_gpr[31], ctx->pc + 4);

             

        case OPC_BC:

            ctx->hflags |= MIPS_HFLAG_B;

            break;

        default:

            MIPS_INVAL("Compact branch/jump");

            generate_exception(ctx, EXCP_RI);

            goto out;

        }



         

        gen_branch(ctx, 4);

    } else {

         

        int fs = gen_new_label();

        save_cpu_state(ctx, 0);



        switch (opc) {

        case OPC_BLEZALC:  

            if (rs == 0 && rt != 0) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_LE), t1, 0, fs);

            } else if (rs != 0 && rt != 0 && rs == rt) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_GE), t1, 0, fs);

            } else {

                 

                tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_GEU), t0, t1, fs);

            }

            break;

        case OPC_BGTZALC:  

            if (rs == 0 && rt != 0) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_GT), t1, 0, fs);

            } else if (rs != 0 && rt != 0 && rs == rt) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_LT), t1, 0, fs);

            } else {

                 

                tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_LTU), t0, t1, fs);

            }

            break;

        case OPC_BLEZC:  

            if (rs == 0 && rt != 0) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_LE), t1, 0, fs);

            } else if (rs != 0 && rt != 0 && rs == rt) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_GE), t1, 0, fs);

            } else {

                 

                tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_GE), t0, t1, fs);

            }

            break;

        case OPC_BGTZC:  

            if (rs == 0 && rt != 0) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_GT), t1, 0, fs);

            } else if (rs != 0 && rt != 0 && rs == rt) {

                 

                tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_LT), t1, 0, fs);

            } else {

                 

                tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_LT), t0, t1, fs);

            }

            break;

        case OPC_BOVC:  

        case OPC_BNVC:  

            if (rs >= rt) {

                 

                TCGv t2 = tcg_temp_new();

                TCGv t3 = tcg_temp_new();

                TCGv t4 = tcg_temp_new();

                TCGv input_overflow = tcg_temp_new();



                gen_load_gpr(t0, rs);

                gen_load_gpr(t1, rt);

                tcg_gen_ext32s_tl(t2, t0);

                tcg_gen_setcond_tl(TCG_COND_NE, input_overflow, t2, t0);

                tcg_gen_ext32s_tl(t3, t1);

                tcg_gen_setcond_tl(TCG_COND_NE, t4, t3, t1);

                tcg_gen_or_tl(input_overflow, input_overflow, t4);



                tcg_gen_add_tl(t4, t2, t3);

                tcg_gen_ext32s_tl(t4, t4);

                tcg_gen_xor_tl(t2, t2, t3);

                tcg_gen_xor_tl(t3, t4, t3);

                tcg_gen_andc_tl(t2, t3, t2);

                tcg_gen_setcondi_tl(TCG_COND_LT, t4, t2, 0);

                tcg_gen_or_tl(t4, t4, input_overflow);

                if (opc == OPC_BOVC) {

                     

                    tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_NE), t4, 0, fs);

                } else {

                     

                    tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_EQ), t4, 0, fs);

                }

                tcg_temp_free(input_overflow);

                tcg_temp_free(t4);

                tcg_temp_free(t3);

                tcg_temp_free(t2);

            } else if (rs < rt && rs == 0) {

                 

                if (opc == OPC_BEQZALC) {

                     

                    tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_EQ), t1, 0, fs);

                } else {

                     

                    tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_NE), t1, 0, fs);

                }

            } else {

                 

                if (opc == OPC_BEQC) {

                     

                    tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_EQ), t0, t1, fs);

                } else {

                     

                    tcg_gen_brcond_tl(tcg_invert_cond(TCG_COND_NE), t0, t1, fs);

                }

            }

            break;

        case OPC_BEQZC:

            tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_EQ), t0, 0, fs);

            break;

        case OPC_BNEZC:

            tcg_gen_brcondi_tl(tcg_invert_cond(TCG_COND_NE), t0, 0, fs);

            break;

        default:

            MIPS_INVAL("Compact conditional branch/jump");

            generate_exception(ctx, EXCP_RI);

            goto out;

        }



         

        gen_goto_tb(ctx, 1, ctx->btarget);

        gen_set_label(fs);



        ctx->hflags |= MIPS_HFLAG_FBNSLOT;

        MIPS_DEBUG("Compact conditional branch");

    }



out:

    tcg_temp_free(t0);

    tcg_temp_free(t1);

}
