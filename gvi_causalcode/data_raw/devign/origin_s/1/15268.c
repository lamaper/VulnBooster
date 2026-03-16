static DisasJumpType translate_one(DisasContext *ctx, uint32_t insn)

{

    int32_t disp21, disp16, disp12 __attribute__((unused));

    uint16_t fn11;

    uint8_t opc, ra, rb, rc, fpfn, fn7, lit;

    bool islit, real_islit;

    TCGv va, vb, vc, tmp, tmp2;

    TCGv_i32 t32;

    DisasJumpType ret;



     

    opc = extract32(insn, 26, 6);

    ra = extract32(insn, 21, 5);

    rb = extract32(insn, 16, 5);

    rc = extract32(insn, 0, 5);

    real_islit = islit = extract32(insn, 12, 1);

    lit = extract32(insn, 13, 8);



    disp21 = sextract32(insn, 0, 21);

    disp16 = sextract32(insn, 0, 16);

    disp12 = sextract32(insn, 0, 12);



    fn11 = extract32(insn, 5, 11);

    fpfn = extract32(insn, 5, 6);

    fn7 = extract32(insn, 5, 7);



    if (rb == 31 && !islit) {

        islit = true;

        lit = 0;

    }



    ret = DISAS_NEXT;

    switch (opc) {

    case 0x00:

         

        ret = gen_call_pal(ctx, insn & 0x03ffffff);

        break;

    case 0x01:

         

        goto invalid_opc;

    case 0x02:

         

        goto invalid_opc;

    case 0x03:

         

        goto invalid_opc;

    case 0x04:

         

        goto invalid_opc;

    case 0x05:

         

        goto invalid_opc;

    case 0x06:

         

        goto invalid_opc;

    case 0x07:

         

        goto invalid_opc;



    case 0x09:

         

        disp16 = (uint32_t)disp16 << 16;

         

    case 0x08:

         

        va = dest_gpr(ctx, ra);

         

        if (rb == 31) {

            tcg_gen_movi_i64(va, disp16);

        } else {

            tcg_gen_addi_i64(va, load_gpr(ctx, rb), disp16);

        }

        break;



    case 0x0A:

         

        REQUIRE_AMASK(BWX);

        gen_load_mem(ctx, &tcg_gen_qemu_ld8u, ra, rb, disp16, 0, 0);

        break;

    case 0x0B:

         

        gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 0, 1);

        break;

    case 0x0C:

         

        REQUIRE_AMASK(BWX);

        gen_load_mem(ctx, &tcg_gen_qemu_ld16u, ra, rb, disp16, 0, 0);

        break;

    case 0x0D:

         

        REQUIRE_AMASK(BWX);

        gen_store_mem(ctx, &tcg_gen_qemu_st16, ra, rb, disp16, 0, 0);

        break;

    case 0x0E:

         

        REQUIRE_AMASK(BWX);

        gen_store_mem(ctx, &tcg_gen_qemu_st8, ra, rb, disp16, 0, 0);

        break;

    case 0x0F:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 0, 1);

        break;



    case 0x10:

        vc = dest_gpr(ctx, rc);

        vb = load_gpr_lit(ctx, rb, lit, islit);



        if (ra == 31) {

            if (fn7 == 0x00) {

                 

                tcg_gen_ext32s_i64(vc, vb);

                break;

            }

            if (fn7 == 0x29) {

                 

                tcg_gen_neg_i64(vc, vb);

                break;

            }

        }



        va = load_gpr(ctx, ra);

        switch (fn7) {

        case 0x00:

             

            tcg_gen_add_i64(vc, va, vb);

            tcg_gen_ext32s_i64(vc, vc);

            break;

        case 0x02:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 2);

            tcg_gen_add_i64(tmp, tmp, vb);

            tcg_gen_ext32s_i64(vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x09:

             

            tcg_gen_sub_i64(vc, va, vb);

            tcg_gen_ext32s_i64(vc, vc);

            break;

        case 0x0B:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 2);

            tcg_gen_sub_i64(tmp, tmp, vb);

            tcg_gen_ext32s_i64(vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x0F:

             

            if (ra == 31) {

                 

                gen_helper_cmpbe0(vc, vb);

            } else {

                gen_helper_cmpbge(vc, va, vb);

            }

            break;

        case 0x12:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 3);

            tcg_gen_add_i64(tmp, tmp, vb);

            tcg_gen_ext32s_i64(vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x1B:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 3);

            tcg_gen_sub_i64(tmp, tmp, vb);

            tcg_gen_ext32s_i64(vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x1D:

             

            tcg_gen_setcond_i64(TCG_COND_LTU, vc, va, vb);

            break;

        case 0x20:

             

            tcg_gen_add_i64(vc, va, vb);

            break;

        case 0x22:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 2);

            tcg_gen_add_i64(vc, tmp, vb);

            tcg_temp_free(tmp);

            break;

        case 0x29:

             

            tcg_gen_sub_i64(vc, va, vb);

            break;

        case 0x2B:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 2);

            tcg_gen_sub_i64(vc, tmp, vb);

            tcg_temp_free(tmp);

            break;

        case 0x2D:

             

            tcg_gen_setcond_i64(TCG_COND_EQ, vc, va, vb);

            break;

        case 0x32:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 3);

            tcg_gen_add_i64(vc, tmp, vb);

            tcg_temp_free(tmp);

            break;

        case 0x3B:

             

            tmp = tcg_temp_new();

            tcg_gen_shli_i64(tmp, va, 3);

            tcg_gen_sub_i64(vc, tmp, vb);

            tcg_temp_free(tmp);

            break;

        case 0x3D:

             

            tcg_gen_setcond_i64(TCG_COND_LEU, vc, va, vb);

            break;

        case 0x40:

             

            tmp = tcg_temp_new();

            tcg_gen_ext32s_i64(tmp, va);

            tcg_gen_ext32s_i64(vc, vb);

            tcg_gen_add_i64(tmp, tmp, vc);

            tcg_gen_ext32s_i64(vc, tmp);

            gen_helper_check_overflow(cpu_env, vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x49:

             

            tmp = tcg_temp_new();

            tcg_gen_ext32s_i64(tmp, va);

            tcg_gen_ext32s_i64(vc, vb);

            tcg_gen_sub_i64(tmp, tmp, vc);

            tcg_gen_ext32s_i64(vc, tmp);

            gen_helper_check_overflow(cpu_env, vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x4D:

             

            tcg_gen_setcond_i64(TCG_COND_LT, vc, va, vb);

            break;

        case 0x60:

             

            tmp = tcg_temp_new();

            tmp2 = tcg_temp_new();

            tcg_gen_eqv_i64(tmp, va, vb);

            tcg_gen_mov_i64(tmp2, va);

            tcg_gen_add_i64(vc, va, vb);

            tcg_gen_xor_i64(tmp2, tmp2, vc);

            tcg_gen_and_i64(tmp, tmp, tmp2);

            tcg_gen_shri_i64(tmp, tmp, 63);

            tcg_gen_movi_i64(tmp2, 0);

            gen_helper_check_overflow(cpu_env, tmp, tmp2);

            tcg_temp_free(tmp);

            tcg_temp_free(tmp2);

            break;

        case 0x69:

             

            tmp = tcg_temp_new();

            tmp2 = tcg_temp_new();

            tcg_gen_xor_i64(tmp, va, vb);

            tcg_gen_mov_i64(tmp2, va);

            tcg_gen_sub_i64(vc, va, vb);

            tcg_gen_xor_i64(tmp2, tmp2, vc);

            tcg_gen_and_i64(tmp, tmp, tmp2);

            tcg_gen_shri_i64(tmp, tmp, 63);

            tcg_gen_movi_i64(tmp2, 0);

            gen_helper_check_overflow(cpu_env, tmp, tmp2);

            tcg_temp_free(tmp);

            tcg_temp_free(tmp2);

            break;

        case 0x6D:

             

            tcg_gen_setcond_i64(TCG_COND_LE, vc, va, vb);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x11:

        if (fn7 == 0x20) {

            if (rc == 31) {

                 

                break;

            }

            if (ra == 31) {

                 

                vc = dest_gpr(ctx, rc);

                if (islit) {

                    tcg_gen_movi_i64(vc, lit);

                } else {

                    tcg_gen_mov_i64(vc, load_gpr(ctx, rb));

                }

                break;

            }

        }



        vc = dest_gpr(ctx, rc);

        vb = load_gpr_lit(ctx, rb, lit, islit);



        if (fn7 == 0x28 && ra == 31) {

             

            tcg_gen_not_i64(vc, vb);

            break;

        }



        va = load_gpr(ctx, ra);

        switch (fn7) {

        case 0x00:

             

            tcg_gen_and_i64(vc, va, vb);

            break;

        case 0x08:

             

            tcg_gen_andc_i64(vc, va, vb);

            break;

        case 0x14:

             

            tmp = tcg_temp_new();

            tcg_gen_andi_i64(tmp, va, 1);

            tcg_gen_movcond_i64(TCG_COND_NE, vc, tmp, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            tcg_temp_free(tmp);

            break;

        case 0x16:

             

            tmp = tcg_temp_new();

            tcg_gen_andi_i64(tmp, va, 1);

            tcg_gen_movcond_i64(TCG_COND_EQ, vc, tmp, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            tcg_temp_free(tmp);

            break;

        case 0x20:

             

            tcg_gen_or_i64(vc, va, vb);

            break;

        case 0x24:

             

            tcg_gen_movcond_i64(TCG_COND_EQ, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x26:

             

            tcg_gen_movcond_i64(TCG_COND_NE, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x28:

             

            tcg_gen_orc_i64(vc, va, vb);

            break;

        case 0x40:

             

            tcg_gen_xor_i64(vc, va, vb);

            break;

        case 0x44:

             

            tcg_gen_movcond_i64(TCG_COND_LT, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x46:

             

            tcg_gen_movcond_i64(TCG_COND_GE, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x48:

             

            tcg_gen_eqv_i64(vc, va, vb);

            break;

        case 0x61:

             

            REQUIRE_REG_31(ra);

            tcg_gen_andi_i64(vc, vb, ~ctx->amask);

            break;

        case 0x64:

             

            tcg_gen_movcond_i64(TCG_COND_LE, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x66:

             

            tcg_gen_movcond_i64(TCG_COND_GT, vc, va, load_zero(ctx),

                                vb, load_gpr(ctx, rc));

            break;

        case 0x6C:

             

            REQUIRE_REG_31(ra);

            tcg_gen_movi_i64(vc, ctx->implver);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x12:

        vc = dest_gpr(ctx, rc);

        va = load_gpr(ctx, ra);

        switch (fn7) {

        case 0x02:

             

            gen_msk_l(ctx, vc, va, rb, islit, lit, 0x01);

            break;

        case 0x06:

             

            gen_ext_l(ctx, vc, va, rb, islit, lit, 0x01);

            break;

        case 0x0B:

             

            gen_ins_l(ctx, vc, va, rb, islit, lit, 0x01);

            break;

        case 0x12:

             

            gen_msk_l(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x16:

             

            gen_ext_l(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x1B:

             

            gen_ins_l(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x22:

             

            gen_msk_l(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x26:

             

            gen_ext_l(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x2B:

             

            gen_ins_l(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x30:

             

            if (islit) {

                gen_zapnoti(vc, va, ~lit);

            } else {

                gen_helper_zap(vc, va, load_gpr(ctx, rb));

            }

            break;

        case 0x31:

             

            if (islit) {

                gen_zapnoti(vc, va, lit);

            } else {

                gen_helper_zapnot(vc, va, load_gpr(ctx, rb));

            }

            break;

        case 0x32:

             

            gen_msk_l(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        case 0x34:

             

            if (islit) {

                tcg_gen_shri_i64(vc, va, lit & 0x3f);

            } else {

                tmp = tcg_temp_new();

                vb = load_gpr(ctx, rb);

                tcg_gen_andi_i64(tmp, vb, 0x3f);

                tcg_gen_shr_i64(vc, va, tmp);

                tcg_temp_free(tmp);

            }

            break;

        case 0x36:

             

            gen_ext_l(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        case 0x39:

             

            if (islit) {

                tcg_gen_shli_i64(vc, va, lit & 0x3f);

            } else {

                tmp = tcg_temp_new();

                vb = load_gpr(ctx, rb);

                tcg_gen_andi_i64(tmp, vb, 0x3f);

                tcg_gen_shl_i64(vc, va, tmp);

                tcg_temp_free(tmp);

            }

            break;

        case 0x3B:

             

            gen_ins_l(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        case 0x3C:

             

            if (islit) {

                tcg_gen_sari_i64(vc, va, lit & 0x3f);

            } else {

                tmp = tcg_temp_new();

                vb = load_gpr(ctx, rb);

                tcg_gen_andi_i64(tmp, vb, 0x3f);

                tcg_gen_sar_i64(vc, va, tmp);

                tcg_temp_free(tmp);

            }

            break;

        case 0x52:

             

            gen_msk_h(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x57:

             

            gen_ins_h(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x5A:

             

            gen_ext_h(ctx, vc, va, rb, islit, lit, 0x03);

            break;

        case 0x62:

             

            gen_msk_h(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x67:

             

            gen_ins_h(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x6A:

             

            gen_ext_h(ctx, vc, va, rb, islit, lit, 0x0f);

            break;

        case 0x72:

             

            gen_msk_h(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        case 0x77:

             

            gen_ins_h(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        case 0x7A:

             

            gen_ext_h(ctx, vc, va, rb, islit, lit, 0xff);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x13:

        vc = dest_gpr(ctx, rc);

        vb = load_gpr_lit(ctx, rb, lit, islit);

        va = load_gpr(ctx, ra);

        switch (fn7) {

        case 0x00:

             

            tcg_gen_mul_i64(vc, va, vb);

            tcg_gen_ext32s_i64(vc, vc);

            break;

        case 0x20:

             

            tcg_gen_mul_i64(vc, va, vb);

            break;

        case 0x30:

             

            tmp = tcg_temp_new();

            tcg_gen_mulu2_i64(tmp, vc, va, vb);

            tcg_temp_free(tmp);

            break;

        case 0x40:

             

            tmp = tcg_temp_new();

            tcg_gen_ext32s_i64(tmp, va);

            tcg_gen_ext32s_i64(vc, vb);

            tcg_gen_mul_i64(tmp, tmp, vc);

            tcg_gen_ext32s_i64(vc, tmp);

            gen_helper_check_overflow(cpu_env, vc, tmp);

            tcg_temp_free(tmp);

            break;

        case 0x60:

             

            tmp = tcg_temp_new();

            tmp2 = tcg_temp_new();

            tcg_gen_muls2_i64(vc, tmp, va, vb);

            tcg_gen_sari_i64(tmp2, vc, 63);

            gen_helper_check_overflow(cpu_env, tmp, tmp2);

            tcg_temp_free(tmp);

            tcg_temp_free(tmp2);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x14:

        REQUIRE_AMASK(FIX);

        vc = dest_fpr(ctx, rc);

        switch (fpfn) {  

        case 0x04:

             

            REQUIRE_REG_31(rb);

            t32 = tcg_temp_new_i32();

            va = load_gpr(ctx, ra);

            tcg_gen_extrl_i64_i32(t32, va);

            gen_helper_memory_to_s(vc, t32);

            tcg_temp_free_i32(t32);

            break;

        case 0x0A:

             

            REQUIRE_REG_31(ra);

            vb = load_fpr(ctx, rb);

            gen_helper_sqrtf(vc, cpu_env, vb);

            break;

        case 0x0B:

             

            REQUIRE_REG_31(ra);

            gen_sqrts(ctx, rb, rc, fn11);

            break;

        case 0x14:

             

            REQUIRE_REG_31(rb);

            t32 = tcg_temp_new_i32();

            va = load_gpr(ctx, ra);

            tcg_gen_extrl_i64_i32(t32, va);

            gen_helper_memory_to_f(vc, t32);

            tcg_temp_free_i32(t32);

            break;

        case 0x24:

             

            REQUIRE_REG_31(rb);

            va = load_gpr(ctx, ra);

            tcg_gen_mov_i64(vc, va);

            break;

        case 0x2A:

             

            REQUIRE_REG_31(ra);

            vb = load_fpr(ctx, rb);

            gen_helper_sqrtg(vc, cpu_env, vb);

            break;

        case 0x02B:

             

            REQUIRE_REG_31(ra);

            gen_sqrtt(ctx, rb, rc, fn11);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x15:

         

         

        vc = dest_fpr(ctx, rc);

        vb = load_fpr(ctx, rb);

        va = load_fpr(ctx, ra);

        switch (fpfn) {  

        case 0x00:

             

            gen_helper_addf(vc, cpu_env, va, vb);

            break;

        case 0x01:

             

            gen_helper_subf(vc, cpu_env, va, vb);

            break;

        case 0x02:

             

            gen_helper_mulf(vc, cpu_env, va, vb);

            break;

        case 0x03:

             

            gen_helper_divf(vc, cpu_env, va, vb);

            break;

        case 0x1E:

             

            REQUIRE_REG_31(ra);

            goto invalid_opc;

        case 0x20:

             

            gen_helper_addg(vc, cpu_env, va, vb);

            break;

        case 0x21:

             

            gen_helper_subg(vc, cpu_env, va, vb);

            break;

        case 0x22:

             

            gen_helper_mulg(vc, cpu_env, va, vb);

            break;

        case 0x23:

             

            gen_helper_divg(vc, cpu_env, va, vb);

            break;

        case 0x25:

             

            gen_helper_cmpgeq(vc, cpu_env, va, vb);

            break;

        case 0x26:

             

            gen_helper_cmpglt(vc, cpu_env, va, vb);

            break;

        case 0x27:

             

            gen_helper_cmpgle(vc, cpu_env, va, vb);

            break;

        case 0x2C:

             

            REQUIRE_REG_31(ra);

            gen_helper_cvtgf(vc, cpu_env, vb);

            break;

        case 0x2D:

             

            REQUIRE_REG_31(ra);

            goto invalid_opc;

        case 0x2F:

             

            REQUIRE_REG_31(ra);

            gen_helper_cvtgq(vc, cpu_env, vb);

            break;

        case 0x3C:

             

            REQUIRE_REG_31(ra);

            gen_helper_cvtqf(vc, cpu_env, vb);

            break;

        case 0x3E:

             

            REQUIRE_REG_31(ra);

            gen_helper_cvtqg(vc, cpu_env, vb);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x16:

         

        switch (fpfn) {  

        case 0x00:

             

            gen_adds(ctx, ra, rb, rc, fn11);

            break;

        case 0x01:

             

            gen_subs(ctx, ra, rb, rc, fn11);

            break;

        case 0x02:

             

            gen_muls(ctx, ra, rb, rc, fn11);

            break;

        case 0x03:

             

            gen_divs(ctx, ra, rb, rc, fn11);

            break;

        case 0x20:

             

            gen_addt(ctx, ra, rb, rc, fn11);

            break;

        case 0x21:

             

            gen_subt(ctx, ra, rb, rc, fn11);

            break;

        case 0x22:

             

            gen_mult(ctx, ra, rb, rc, fn11);

            break;

        case 0x23:

             

            gen_divt(ctx, ra, rb, rc, fn11);

            break;

        case 0x24:

             

            gen_cmptun(ctx, ra, rb, rc, fn11);

            break;

        case 0x25:

             

            gen_cmpteq(ctx, ra, rb, rc, fn11);

            break;

        case 0x26:

             

            gen_cmptlt(ctx, ra, rb, rc, fn11);

            break;

        case 0x27:

             

            gen_cmptle(ctx, ra, rb, rc, fn11);

            break;

        case 0x2C:

            REQUIRE_REG_31(ra);

            if (fn11 == 0x2AC || fn11 == 0x6AC) {

                 

                gen_cvtst(ctx, rb, rc, fn11);

            } else {

                 

                gen_cvtts(ctx, rb, rc, fn11);

            }

            break;

        case 0x2F:

             

            REQUIRE_REG_31(ra);

            gen_cvttq(ctx, rb, rc, fn11);

            break;

        case 0x3C:

             

            REQUIRE_REG_31(ra);

            gen_cvtqs(ctx, rb, rc, fn11);

            break;

        case 0x3E:

             

            REQUIRE_REG_31(ra);

            gen_cvtqt(ctx, rb, rc, fn11);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x17:

        switch (fn11) {

        case 0x010:

             

            REQUIRE_REG_31(ra);

            vc = dest_fpr(ctx, rc);

            vb = load_fpr(ctx, rb);

            gen_cvtlq(vc, vb);

            break;

        case 0x020:

             

            if (rc == 31) {

                 

            } else {

                vc = dest_fpr(ctx, rc);

                va = load_fpr(ctx, ra);

                if (ra == rb) {

                     

                    tcg_gen_mov_i64(vc, va);

                } else {

                    vb = load_fpr(ctx, rb);

                    gen_cpy_mask(vc, va, vb, 0, 0x8000000000000000ULL);

                }

            }

            break;

        case 0x021:

             

            vc = dest_fpr(ctx, rc);

            vb = load_fpr(ctx, rb);

            va = load_fpr(ctx, ra);

            gen_cpy_mask(vc, va, vb, 1, 0x8000000000000000ULL);

            break;

        case 0x022:

             

            vc = dest_fpr(ctx, rc);

            vb = load_fpr(ctx, rb);

            va = load_fpr(ctx, ra);

            gen_cpy_mask(vc, va, vb, 0, 0xFFF0000000000000ULL);

            break;

        case 0x024:

             

            va = load_fpr(ctx, ra);

            gen_helper_store_fpcr(cpu_env, va);

            if (ctx->tb_rm == QUAL_RM_D) {

                 

                ctx->tb_rm = -1;

            }

            break;

        case 0x025:

             

            va = dest_fpr(ctx, ra);

            gen_helper_load_fpcr(va, cpu_env);

            break;

        case 0x02A:

             

            gen_fcmov(ctx, TCG_COND_EQ, ra, rb, rc);

            break;

        case 0x02B:

             

            gen_fcmov(ctx, TCG_COND_NE, ra, rb, rc);

            break;

        case 0x02C:

             

            gen_fcmov(ctx, TCG_COND_LT, ra, rb, rc);

            break;

        case 0x02D:

             

            gen_fcmov(ctx, TCG_COND_GE, ra, rb, rc);

            break;

        case 0x02E:

             

            gen_fcmov(ctx, TCG_COND_LE, ra, rb, rc);

            break;

        case 0x02F:

             

            gen_fcmov(ctx, TCG_COND_GT, ra, rb, rc);

            break;

        case 0x030:  

        case 0x130:  

        case 0x530:  

            REQUIRE_REG_31(ra);

            vc = dest_fpr(ctx, rc);

            vb = load_fpr(ctx, rb);

            gen_helper_cvtql(vc, cpu_env, vb);

            gen_fp_exc_raise(rc, fn11);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x18:

        switch ((uint16_t)disp16) {

        case 0x0000:

             

             

            break;

        case 0x0400:

             

             

            break;

        case 0x4000:

             

            tcg_gen_mb(TCG_MO_ALL | TCG_BAR_SC);

            break;

        case 0x4400:

             

            tcg_gen_mb(TCG_MO_ST_ST | TCG_BAR_SC);

            break;

        case 0x8000:

             

             

            break;

        case 0xA000:

             

             

            break;

        case 0xC000:

             

            va = dest_gpr(ctx, ra);

            if (ctx->base.tb->cflags & CF_USE_ICOUNT) {

                gen_io_start();

                gen_helper_load_pcc(va, cpu_env);

                gen_io_end();

                ret = DISAS_PC_STALE;

            } else {

                gen_helper_load_pcc(va, cpu_env);

            }

            break;

        case 0xE000:

             

            gen_rx(ctx, ra, 0);

            break;

        case 0xE800:

             

            break;

        case 0xF000:

             

            gen_rx(ctx, ra, 1);

            break;

        case 0xF800:

             

             

            break;

        case 0xFC00:

             

             

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x19:


        REQUIRE_TB_FLAG(ENV_FLAG_PAL_MODE);

        va = dest_gpr(ctx, ra);

        ret = gen_mfpr(ctx, va, insn & 0xffff);

        break;


        goto invalid_opc;




    case 0x1A:

         

        vb = load_gpr(ctx, rb);

        tcg_gen_andi_i64(cpu_pc, vb, ~3);

        if (ra != 31) {

            tcg_gen_movi_i64(ctx->ir[ra], ctx->base.pc_next);

        }

        ret = DISAS_PC_UPDATED;

        break;



    case 0x1B:


        REQUIRE_TB_FLAG(ENV_FLAG_PAL_MODE);

        {

            TCGv addr = tcg_temp_new();

            vb = load_gpr(ctx, rb);

            va = dest_gpr(ctx, ra);



            tcg_gen_addi_i64(addr, vb, disp12);

            switch ((insn >> 12) & 0xF) {

            case 0x0:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_PHYS_IDX, MO_LESL);

                break;

            case 0x1:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_PHYS_IDX, MO_LEQ);

                break;

            case 0x2:

                 

                gen_qemu_ldl_l(va, addr, MMU_PHYS_IDX);

                break;

            case 0x3:

                 

                gen_qemu_ldq_l(va, addr, MMU_PHYS_IDX);

                break;

            case 0x4:

                 

                goto invalid_opc;

            case 0x5:

                 

                goto invalid_opc;

                break;

            case 0x6:

                 

                goto invalid_opc;

            case 0x7:

                 

                goto invalid_opc;

            case 0x8:

                 

                goto invalid_opc;

            case 0x9:

                 

                goto invalid_opc;

            case 0xA:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_KERNEL_IDX, MO_LESL);

                break;

            case 0xB:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_KERNEL_IDX, MO_LEQ);

                break;

            case 0xC:

                 

                goto invalid_opc;

            case 0xD:

                 

                goto invalid_opc;

            case 0xE:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_USER_IDX, MO_LESL);

                break;

            case 0xF:

                 

                tcg_gen_qemu_ld_i64(va, addr, MMU_USER_IDX, MO_LEQ);

                break;

            }

            tcg_temp_free(addr);

            break;

        }


        goto invalid_opc;




    case 0x1C:

        vc = dest_gpr(ctx, rc);

        if (fn7 == 0x70) {

             

            REQUIRE_AMASK(FIX);

            REQUIRE_REG_31(rb);

            va = load_fpr(ctx, ra);

            tcg_gen_mov_i64(vc, va);

            break;

        } else if (fn7 == 0x78) {

             

            REQUIRE_AMASK(FIX);

            REQUIRE_REG_31(rb);

            t32 = tcg_temp_new_i32();

            va = load_fpr(ctx, ra);

            gen_helper_s_to_memory(t32, va);

            tcg_gen_ext_i32_i64(vc, t32);

            tcg_temp_free_i32(t32);

            break;

        }



        vb = load_gpr_lit(ctx, rb, lit, islit);

        switch (fn7) {

        case 0x00:

             

            REQUIRE_AMASK(BWX);

            REQUIRE_REG_31(ra);

            tcg_gen_ext8s_i64(vc, vb);

            break;

        case 0x01:

             

            REQUIRE_AMASK(BWX);

            REQUIRE_REG_31(ra);

            tcg_gen_ext16s_i64(vc, vb);

            break;

        case 0x30:

             

            REQUIRE_AMASK(CIX);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            tcg_gen_ctpop_i64(vc, vb);

            break;

        case 0x31:

             

            REQUIRE_AMASK(MVI);

            REQUIRE_NO_LIT;

            va = load_gpr(ctx, ra);

            gen_helper_perr(vc, va, vb);

            break;

        case 0x32:

             

            REQUIRE_AMASK(CIX);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            tcg_gen_clzi_i64(vc, vb, 64);

            break;

        case 0x33:

             

            REQUIRE_AMASK(CIX);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            tcg_gen_ctzi_i64(vc, vb, 64);

            break;

        case 0x34:

             

            REQUIRE_AMASK(MVI);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            gen_helper_unpkbw(vc, vb);

            break;

        case 0x35:

             

            REQUIRE_AMASK(MVI);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            gen_helper_unpkbl(vc, vb);

            break;

        case 0x36:

             

            REQUIRE_AMASK(MVI);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            gen_helper_pkwb(vc, vb);

            break;

        case 0x37:

             

            REQUIRE_AMASK(MVI);

            REQUIRE_REG_31(ra);

            REQUIRE_NO_LIT;

            gen_helper_pklb(vc, vb);

            break;

        case 0x38:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_minsb8(vc, va, vb);

            break;

        case 0x39:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_minsw4(vc, va, vb);

            break;

        case 0x3A:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_minub8(vc, va, vb);

            break;

        case 0x3B:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_minuw4(vc, va, vb);

            break;

        case 0x3C:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_maxub8(vc, va, vb);

            break;

        case 0x3D:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_maxuw4(vc, va, vb);

            break;

        case 0x3E:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_maxsb8(vc, va, vb);

            break;

        case 0x3F:

             

            REQUIRE_AMASK(MVI);

            va = load_gpr(ctx, ra);

            gen_helper_maxsw4(vc, va, vb);

            break;

        default:

            goto invalid_opc;

        }

        break;



    case 0x1D:


        REQUIRE_TB_FLAG(ENV_FLAG_PAL_MODE);

        vb = load_gpr(ctx, rb);

        ret = gen_mtpr(ctx, vb, insn & 0xffff);

        break;


        goto invalid_opc;




    case 0x1E:


        REQUIRE_TB_FLAG(ENV_FLAG_PAL_MODE);

        if (rb == 31) {

             

            ctx->lit = vb = tcg_temp_new();

            tcg_gen_ld_i64(vb, cpu_env, offsetof(CPUAlphaState, exc_addr));

        } else {

            vb = load_gpr(ctx, rb);

        }

        tcg_gen_movi_i64(cpu_lock_addr, -1);

        tmp = tcg_temp_new();

        tcg_gen_movi_i64(tmp, 0);

        st_flag_byte(tmp, ENV_FLAG_RX_SHIFT);

        tcg_gen_andi_i64(tmp, vb, 1);

        st_flag_byte(tmp, ENV_FLAG_PAL_SHIFT);

        tcg_temp_free(tmp);

        tcg_gen_andi_i64(cpu_pc, vb, ~3);

         

        ret = DISAS_PC_UPDATED_NOCHAIN;

        break;


        goto invalid_opc;




    case 0x1F:


        REQUIRE_TB_FLAG(ENV_FLAG_PAL_MODE);

        {

            switch ((insn >> 12) & 0xF) {

            case 0x0:

                 

                va = load_gpr(ctx, ra);

                vb = load_gpr(ctx, rb);

                tmp = tcg_temp_new();

                tcg_gen_addi_i64(tmp, vb, disp12);

                tcg_gen_qemu_st_i64(va, tmp, MMU_PHYS_IDX, MO_LESL);

                tcg_temp_free(tmp);

                break;

            case 0x1:

                 

                va = load_gpr(ctx, ra);

                vb = load_gpr(ctx, rb);

                tmp = tcg_temp_new();

                tcg_gen_addi_i64(tmp, vb, disp12);

                tcg_gen_qemu_st_i64(va, tmp, MMU_PHYS_IDX, MO_LEQ);

                tcg_temp_free(tmp);

                break;

            case 0x2:

                 

                ret = gen_store_conditional(ctx, ra, rb, disp12,

                                            MMU_PHYS_IDX, MO_LESL);

                break;

            case 0x3:

                 

                ret = gen_store_conditional(ctx, ra, rb, disp12,

                                            MMU_PHYS_IDX, MO_LEQ);

                break;

            case 0x4:

                 

                goto invalid_opc;

            case 0x5:

                 

                goto invalid_opc;

            case 0x6:

                 

                goto invalid_opc;

            case 0x7:

                 

                goto invalid_opc;

            case 0x8:

                 

                goto invalid_opc;

            case 0x9:

                 

                goto invalid_opc;

            case 0xA:

                 

                goto invalid_opc;

            case 0xB:

                 

                goto invalid_opc;

            case 0xC:

                 

                goto invalid_opc;

            case 0xD:

                 

                goto invalid_opc;

            case 0xE:

                 

                goto invalid_opc;

            case 0xF:

                 

                goto invalid_opc;

            }

            break;

        }


        goto invalid_opc;


    case 0x20:

         

        gen_load_mem(ctx, &gen_qemu_ldf, ra, rb, disp16, 1, 0);

        break;

    case 0x21:

         

        gen_load_mem(ctx, &gen_qemu_ldg, ra, rb, disp16, 1, 0);

        break;

    case 0x22:

         

        gen_load_mem(ctx, &gen_qemu_lds, ra, rb, disp16, 1, 0);

        break;

    case 0x23:

         

        gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 1, 0);

        break;

    case 0x24:

         

        gen_store_mem(ctx, &gen_qemu_stf, ra, rb, disp16, 1, 0);

        break;

    case 0x25:

         

        gen_store_mem(ctx, &gen_qemu_stg, ra, rb, disp16, 1, 0);

        break;

    case 0x26:

         

        gen_store_mem(ctx, &gen_qemu_sts, ra, rb, disp16, 1, 0);

        break;

    case 0x27:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 1, 0);

        break;

    case 0x28:

         

        gen_load_mem(ctx, &tcg_gen_qemu_ld32s, ra, rb, disp16, 0, 0);

        break;

    case 0x29:

         

        gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 0, 0);

        break;

    case 0x2A:

         

        gen_load_mem(ctx, &gen_qemu_ldl_l, ra, rb, disp16, 0, 0);

        break;

    case 0x2B:

         

        gen_load_mem(ctx, &gen_qemu_ldq_l, ra, rb, disp16, 0, 0);

        break;

    case 0x2C:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st32, ra, rb, disp16, 0, 0);

        break;

    case 0x2D:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 0, 0);

        break;

    case 0x2E:

         

        ret = gen_store_conditional(ctx, ra, rb, disp16,

                                    ctx->mem_idx, MO_LESL);

        break;

    case 0x2F:

         

        ret = gen_store_conditional(ctx, ra, rb, disp16,

                                    ctx->mem_idx, MO_LEQ);

        break;

    case 0x30:

         

        ret = gen_bdirect(ctx, ra, disp21);

        break;

    case 0x31:  

        ret = gen_fbcond(ctx, TCG_COND_EQ, ra, disp21);

        break;

    case 0x32:  

        ret = gen_fbcond(ctx, TCG_COND_LT, ra, disp21);

        break;

    case 0x33:  

        ret = gen_fbcond(ctx, TCG_COND_LE, ra, disp21);

        break;

    case 0x34:

         

        ret = gen_bdirect(ctx, ra, disp21);

        break;

    case 0x35:  

        ret = gen_fbcond(ctx, TCG_COND_NE, ra, disp21);

        break;

    case 0x36:  

        ret = gen_fbcond(ctx, TCG_COND_GE, ra, disp21);

        break;

    case 0x37:  

        ret = gen_fbcond(ctx, TCG_COND_GT, ra, disp21);

        break;

    case 0x38:

         

        ret = gen_bcond(ctx, TCG_COND_EQ, ra, disp21, 1);

        break;

    case 0x39:

         

        ret = gen_bcond(ctx, TCG_COND_EQ, ra, disp21, 0);

        break;

    case 0x3A:

         

        ret = gen_bcond(ctx, TCG_COND_LT, ra, disp21, 0);

        break;

    case 0x3B:

         

        ret = gen_bcond(ctx, TCG_COND_LE, ra, disp21, 0);

        break;

    case 0x3C:

         

        ret = gen_bcond(ctx, TCG_COND_NE, ra, disp21, 1);

        break;

    case 0x3D:

         

        ret = gen_bcond(ctx, TCG_COND_NE, ra, disp21, 0);

        break;

    case 0x3E:

         

        ret = gen_bcond(ctx, TCG_COND_GE, ra, disp21, 0);

        break;

    case 0x3F:

         

        ret = gen_bcond(ctx, TCG_COND_GT, ra, disp21, 0);

        break;

    invalid_opc:

        ret = gen_invalid(ctx);

        break;

    }



    return ret;

}
