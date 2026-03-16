static ExitStatus translate_one(DisasContext *ctx, uint32_t insn)

{

    uint32_t palcode;

    int32_t disp21, disp16;


    int32_t disp12;


    uint16_t fn11;

    uint8_t opc, ra, rb, rc, fpfn, fn7, islit, real_islit;

    uint8_t lit;

    ExitStatus ret;



     

    opc = insn >> 26;

    ra = (insn >> 21) & 0x1F;

    rb = (insn >> 16) & 0x1F;

    rc = insn & 0x1F;

    real_islit = islit = (insn >> 12) & 1;

    if (rb == 31 && !islit) {

        islit = 1;

        lit = 0;

    } else

        lit = (insn >> 13) & 0xFF;

    palcode = insn & 0x03FFFFFF;

    disp21 = ((int32_t)((insn & 0x001FFFFF) << 11)) >> 11;

    disp16 = (int16_t)(insn & 0x0000FFFF);


    disp12 = (int32_t)((insn & 0x00000FFF) << 20) >> 20;


    fn11 = (insn >> 5) & 0x000007FF;

    fpfn = fn11 & 0x3F;

    fn7 = (insn >> 5) & 0x0000007F;

    LOG_DISAS("opc %02x ra %2d rb %2d rc %2d disp16 %6d\n",

              opc, ra, rb, rc, disp16);



    ret = NO_EXIT;

    switch (opc) {

    case 0x00:

         

        ret = gen_call_pal(ctx, palcode);

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

    case 0x08:

         

        if (likely(ra != 31)) {

            if (rb != 31) {

                tcg_gen_addi_i64(cpu_ir[ra], cpu_ir[rb], disp16);

            } else {

                tcg_gen_movi_i64(cpu_ir[ra], disp16);

            }

        }

        break;

    case 0x09:

         

        if (likely(ra != 31)) {

            if (rb != 31) {

                tcg_gen_addi_i64(cpu_ir[ra], cpu_ir[rb], disp16 << 16);

            } else {

                tcg_gen_movi_i64(cpu_ir[ra], disp16 << 16);

            }

        }

        break;

    case 0x0A:

         

        if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {

            gen_load_mem(ctx, &tcg_gen_qemu_ld8u, ra, rb, disp16, 0, 0);

            break;

        }

        goto invalid_opc;

    case 0x0B:

         

        gen_load_mem(ctx, &tcg_gen_qemu_ld64, ra, rb, disp16, 0, 1);

        break;

    case 0x0C:

         

        if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {

            gen_load_mem(ctx, &tcg_gen_qemu_ld16u, ra, rb, disp16, 0, 0);

            break;

        }

        goto invalid_opc;

    case 0x0D:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st16, ra, rb, disp16, 0, 0);

        break;

    case 0x0E:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st8, ra, rb, disp16, 0, 0);

        break;

    case 0x0F:

         

        gen_store_mem(ctx, &tcg_gen_qemu_st64, ra, rb, disp16, 0, 1);

        break;

    case 0x10:

        switch (fn7) {

        case 0x00:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_addi_i64(cpu_ir[rc], cpu_ir[ra], lit);

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                    } else {

                        tcg_gen_add_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x02:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);

                    if (islit) {

                        tcg_gen_addi_i64(tmp, tmp, lit);

                    } else {

                        tcg_gen_add_i64(tmp, tmp, cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], tmp);

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x09:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_subi_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_sub_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                    }

                }

            }

            break;

        case 0x0B:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);

                    if (islit) {

                        tcg_gen_subi_i64(tmp, tmp, lit);

                    } else {

                        tcg_gen_sub_i64(tmp, tmp, cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], tmp);

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                    }

                }

            }

            break;

        case 0x0F:

             

            gen_cmpbge(ra, rb, rc, islit, lit);

            break;

        case 0x12:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);

                    if (islit) {

                        tcg_gen_addi_i64(tmp, tmp, lit);

                    } else {

                        tcg_gen_add_i64(tmp, tmp, cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], tmp);

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x1B:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);

                    if (islit) {

                        tcg_gen_subi_i64(tmp, tmp, lit);

                    } else {

                       tcg_gen_sub_i64(tmp, tmp, cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], tmp);

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                        tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                    }

                }

            }

            break;

        case 0x1D:

             

            gen_cmp(TCG_COND_LTU, ra, rb, rc, islit, lit);

            break;

        case 0x20:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_addi_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_add_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x22:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);

                    if (islit) {

                        tcg_gen_addi_i64(cpu_ir[rc], tmp, lit);

                    } else {

                        tcg_gen_add_i64(cpu_ir[rc], tmp, cpu_ir[rb]);

                    }

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x29:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_subi_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_sub_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x2B:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 2);

                    if (islit) {

                        tcg_gen_subi_i64(cpu_ir[rc], tmp, lit);

                    } else {

                        tcg_gen_sub_i64(cpu_ir[rc], tmp, cpu_ir[rb]);

                    }

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x2D:

             

            gen_cmp(TCG_COND_EQ, ra, rb, rc, islit, lit);

            break;

        case 0x32:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);

                    if (islit) {

                        tcg_gen_addi_i64(cpu_ir[rc], tmp, lit);

                    } else {

                        tcg_gen_add_i64(cpu_ir[rc], tmp, cpu_ir[rb]);

                    }

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x3B:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv tmp = tcg_temp_new();

                    tcg_gen_shli_i64(tmp, cpu_ir[ra], 3);

                    if (islit) {

                        tcg_gen_subi_i64(cpu_ir[rc], tmp, lit);

                    } else {

                        tcg_gen_sub_i64(cpu_ir[rc], tmp, cpu_ir[rb]);

                    }

                    tcg_temp_free(tmp);

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], -lit);

                    } else {

                        tcg_gen_neg_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x3D:

             

            gen_cmp(TCG_COND_LEU, ra, rb, rc, islit, lit);

            break;

        case 0x40:

             

            gen_addlv(ra, rb, rc, islit, lit);

            break;

        case 0x49:

             

            gen_sublv(ra, rb, rc, islit, lit);

            break;

        case 0x4D:

             

            gen_cmp(TCG_COND_LT, ra, rb, rc, islit, lit);

            break;

        case 0x60:

             

            gen_addqv(ra, rb, rc, islit, lit);

            break;

        case 0x69:

             

            gen_subqv(ra, rb, rc, islit, lit);

            break;

        case 0x6D:

             

            gen_cmp(TCG_COND_LE, ra, rb, rc, islit, lit);

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x11:

        switch (fn7) {

        case 0x00:

             

            if (likely(rc != 31)) {

                if (ra == 31) {

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

                } else if (islit) {

                    tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[ra], lit);

                } else {

                    tcg_gen_and_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                }

            }

            break;

        case 0x08:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[ra], ~lit);

                    } else {

                        tcg_gen_andc_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

            }

            break;

        case 0x14:

             

            gen_cmov(TCG_COND_NE, ra, rb, rc, islit, lit, 1);

            break;

        case 0x16:

             

            gen_cmov(TCG_COND_EQ, ra, rb, rc, islit, lit, 1);

            break;

        case 0x20:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_ori_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_or_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x24:

             

            gen_cmov(TCG_COND_EQ, ra, rb, rc, islit, lit, 0);

            break;

        case 0x26:

             

            gen_cmov(TCG_COND_NE, ra, rb, rc, islit, lit, 0);

            break;

        case 0x28:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_ori_i64(cpu_ir[rc], cpu_ir[ra], ~lit);

                    } else {

                        tcg_gen_orc_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], ~lit);

                    } else {

                        tcg_gen_not_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x40:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_xori_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_xor_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], lit);

                    } else {

                        tcg_gen_mov_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x44:

             

            gen_cmov(TCG_COND_LT, ra, rb, rc, islit, lit, 0);

            break;

        case 0x46:

             

            gen_cmov(TCG_COND_GE, ra, rb, rc, islit, lit, 0);

            break;

        case 0x48:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_xori_i64(cpu_ir[rc], cpu_ir[ra], ~lit);

                    } else {

                        tcg_gen_eqv_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                } else {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], ~lit);

                    } else {

                        tcg_gen_not_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

            }

            break;

        case 0x61:

             

            if (likely(rc != 31)) {

                uint64_t amask = ctx->tb->flags >> TB_FLAGS_AMASK_SHIFT;



                if (islit) {

                    tcg_gen_movi_i64(cpu_ir[rc], lit & ~amask);

                } else {

                    tcg_gen_andi_i64(cpu_ir[rc], cpu_ir[rb], ~amask);

                }

            }

            break;

        case 0x64:

             

            gen_cmov(TCG_COND_LE, ra, rb, rc, islit, lit, 0);

            break;

        case 0x66:

             

            gen_cmov(TCG_COND_GT, ra, rb, rc, islit, lit, 0);

            break;

        case 0x6C:

             

            if (rc != 31) {

                tcg_gen_movi_i64(cpu_ir[rc], ctx->implver);

            }

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x12:

        switch (fn7) {

        case 0x02:

             

            gen_msk_l(ra, rb, rc, islit, lit, 0x01);

            break;

        case 0x06:

             

            gen_ext_l(ra, rb, rc, islit, lit, 0x01);

            break;

        case 0x0B:

             

            gen_ins_l(ra, rb, rc, islit, lit, 0x01);

            break;

        case 0x12:

             

            gen_msk_l(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x16:

             

            gen_ext_l(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x1B:

             

            gen_ins_l(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x22:

             

            gen_msk_l(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x26:

             

            gen_ext_l(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x2B:

             

            gen_ins_l(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x30:

             

            gen_zap(ra, rb, rc, islit, lit);

            break;

        case 0x31:

             

            gen_zapnot(ra, rb, rc, islit, lit);

            break;

        case 0x32:

             

            gen_msk_l(ra, rb, rc, islit, lit, 0xff);

            break;

        case 0x34:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_shri_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);

                    } else {

                        TCGv shift = tcg_temp_new();

                        tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);

                        tcg_gen_shr_i64(cpu_ir[rc], cpu_ir[ra], shift);

                        tcg_temp_free(shift);

                    }

                } else

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

            }

            break;

        case 0x36:

             

            gen_ext_l(ra, rb, rc, islit, lit, 0xff);

            break;

        case 0x39:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_shli_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);

                    } else {

                        TCGv shift = tcg_temp_new();

                        tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);

                        tcg_gen_shl_i64(cpu_ir[rc], cpu_ir[ra], shift);

                        tcg_temp_free(shift);

                    }

                } else

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

            }

            break;

        case 0x3B:

             

            gen_ins_l(ra, rb, rc, islit, lit, 0xff);

            break;

        case 0x3C:

             

            if (likely(rc != 31)) {

                if (ra != 31) {

                    if (islit) {

                        tcg_gen_sari_i64(cpu_ir[rc], cpu_ir[ra], lit & 0x3f);

                    } else {

                        TCGv shift = tcg_temp_new();

                        tcg_gen_andi_i64(shift, cpu_ir[rb], 0x3f);

                        tcg_gen_sar_i64(cpu_ir[rc], cpu_ir[ra], shift);

                        tcg_temp_free(shift);

                    }

                } else

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

            }

            break;

        case 0x52:

             

            gen_msk_h(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x57:

             

            gen_ins_h(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x5A:

             

            gen_ext_h(ra, rb, rc, islit, lit, 0x03);

            break;

        case 0x62:

             

            gen_msk_h(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x67:

             

            gen_ins_h(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x6A:

             

            gen_ext_h(ra, rb, rc, islit, lit, 0x0f);

            break;

        case 0x72:

             

            gen_msk_h(ra, rb, rc, islit, lit, 0xff);

            break;

        case 0x77:

             

            gen_ins_h(ra, rb, rc, islit, lit, 0xff);

            break;

        case 0x7A:

             

            gen_ext_h(ra, rb, rc, islit, lit, 0xff);

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x13:

        switch (fn7) {

        case 0x00:

             

            if (likely(rc != 31)) {

                if (ra == 31) {

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

                } else {

                    if (islit) {

                        tcg_gen_muli_i64(cpu_ir[rc], cpu_ir[ra], lit);

                    } else {

                        tcg_gen_mul_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                    }

                    tcg_gen_ext32s_i64(cpu_ir[rc], cpu_ir[rc]);

                }

            }

            break;

        case 0x20:

             

            if (likely(rc != 31)) {

                if (ra == 31) {

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

                } else if (islit) {

                    tcg_gen_muli_i64(cpu_ir[rc], cpu_ir[ra], lit);

                } else {

                    tcg_gen_mul_i64(cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                }

            }

            break;

        case 0x30:

             

            {

                TCGv low;

                if (unlikely(rc == 31)){

                    break;

                }

                if (ra == 31) {

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

                    break;

                }

                low = tcg_temp_new();

                if (islit) {

                    tcg_gen_movi_tl(low, lit);

                    tcg_gen_mulu2_i64(low, cpu_ir[rc], cpu_ir[ra], low);

                } else {

                    tcg_gen_mulu2_i64(low, cpu_ir[rc], cpu_ir[ra], cpu_ir[rb]);

                }

                tcg_temp_free(low);

            }

            break;

        case 0x40:

             

            gen_mullv(ra, rb, rc, islit, lit);

            break;

        case 0x60:

             

            gen_mulqv(ra, rb, rc, islit, lit);

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x14:

        switch (fpfn) {  

        case 0x04:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {

                goto invalid_opc;

            }

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv_i32 tmp = tcg_temp_new_i32();

                    tcg_gen_trunc_i64_i32(tmp, cpu_ir[ra]);

                    gen_helper_memory_to_s(cpu_fir[rc], tmp);

                    tcg_temp_free_i32(tmp);

                } else

                    tcg_gen_movi_i64(cpu_fir[rc], 0);

            }

            break;

        case 0x0A:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {

                gen_fsqrtf(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x0B:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {

                gen_fsqrts(ctx, rb, rc, fn11);

                break;

            }

            goto invalid_opc;

        case 0x14:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {

                goto invalid_opc;

            }

            if (likely(rc != 31)) {

                if (ra != 31) {

                    TCGv_i32 tmp = tcg_temp_new_i32();

                    tcg_gen_trunc_i64_i32(tmp, cpu_ir[ra]);

                    gen_helper_memory_to_f(cpu_fir[rc], tmp);

                    tcg_temp_free_i32(tmp);

                } else

                    tcg_gen_movi_i64(cpu_fir[rc], 0);

            }

            break;

        case 0x24:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {

                goto invalid_opc;

            }

            if (likely(rc != 31)) {

                if (ra != 31) {

                    tcg_gen_mov_i64(cpu_fir[rc], cpu_ir[ra]);

                } else {

                    tcg_gen_movi_i64(cpu_fir[rc], 0);

                }

            }

            break;

        case 0x2A:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {

                gen_fsqrtg(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x02B:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_FIX) {

                gen_fsqrtt(ctx, rb, rc, fn11);

                break;

            }

            goto invalid_opc;

        default:

            goto invalid_opc;

        }

        break;

    case 0x15:

         

         

        switch (fpfn) {  

        case 0x00:

             

            gen_faddf(ra, rb, rc);

            break;

        case 0x01:

             

            gen_fsubf(ra, rb, rc);

            break;

        case 0x02:

             

            gen_fmulf(ra, rb, rc);

            break;

        case 0x03:

             

            gen_fdivf(ra, rb, rc);

            break;

        case 0x1E:


            gen_fcvtdg(rb, rc);


            goto invalid_opc;


            break;

        case 0x20:

             

            gen_faddg(ra, rb, rc);

            break;

        case 0x21:

             

            gen_fsubg(ra, rb, rc);

            break;

        case 0x22:

             

            gen_fmulg(ra, rb, rc);

            break;

        case 0x23:

             

            gen_fdivg(ra, rb, rc);

            break;

        case 0x25:

             

            gen_fcmpgeq(ra, rb, rc);

            break;

        case 0x26:

             

            gen_fcmpglt(ra, rb, rc);

            break;

        case 0x27:

             

            gen_fcmpgle(ra, rb, rc);

            break;

        case 0x2C:

             

            gen_fcvtgf(rb, rc);

            break;

        case 0x2D:


            gen_fcvtgd(rb, rc);


            goto invalid_opc;


            break;

        case 0x2F:

             

            gen_fcvtgq(rb, rc);

            break;

        case 0x3C:

             

            gen_fcvtqf(rb, rc);

            break;

        case 0x3E:

             

            gen_fcvtqg(rb, rc);

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x16:

         

        switch (fpfn) {  

        case 0x00:

             

            gen_fadds(ctx, ra, rb, rc, fn11);

            break;

        case 0x01:

             

            gen_fsubs(ctx, ra, rb, rc, fn11);

            break;

        case 0x02:

             

            gen_fmuls(ctx, ra, rb, rc, fn11);

            break;

        case 0x03:

             

            gen_fdivs(ctx, ra, rb, rc, fn11);

            break;

        case 0x20:

             

            gen_faddt(ctx, ra, rb, rc, fn11);

            break;

        case 0x21:

             

            gen_fsubt(ctx, ra, rb, rc, fn11);

            break;

        case 0x22:

             

            gen_fmult(ctx, ra, rb, rc, fn11);

            break;

        case 0x23:

             

            gen_fdivt(ctx, ra, rb, rc, fn11);

            break;

        case 0x24:

             

            gen_fcmptun(ctx, ra, rb, rc, fn11);

            break;

        case 0x25:

             

            gen_fcmpteq(ctx, ra, rb, rc, fn11);

            break;

        case 0x26:

             

            gen_fcmptlt(ctx, ra, rb, rc, fn11);

            break;

        case 0x27:

             

            gen_fcmptle(ctx, ra, rb, rc, fn11);

            break;

        case 0x2C:

            if (fn11 == 0x2AC || fn11 == 0x6AC) {

                 

                gen_fcvtst(ctx, rb, rc, fn11);

            } else {

                 

                gen_fcvtts(ctx, rb, rc, fn11);

            }

            break;

        case 0x2F:

             

            gen_fcvttq(ctx, rb, rc, fn11);

            break;

        case 0x3C:

             

            gen_fcvtqs(ctx, rb, rc, fn11);

            break;

        case 0x3E:

             

            gen_fcvtqt(ctx, rb, rc, fn11);

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x17:

        switch (fn11) {

        case 0x010:

             

            gen_fcvtlq(rb, rc);

            break;

        case 0x020:

            if (likely(rc != 31)) {

                if (ra == rb) {

                     

                    if (ra == 31) {

                        tcg_gen_movi_i64(cpu_fir[rc], 0);

                    } else {

                        tcg_gen_mov_i64(cpu_fir[rc], cpu_fir[ra]);

                    }

                } else {

                     

                    gen_fcpys(ra, rb, rc);

                }

            }

            break;

        case 0x021:

             

            gen_fcpysn(ra, rb, rc);

            break;

        case 0x022:

             

            gen_fcpyse(ra, rb, rc);

            break;

        case 0x024:

             

            if (likely(ra != 31)) {

                gen_helper_store_fpcr(cpu_env, cpu_fir[ra]);

            } else {

                TCGv tmp = tcg_const_i64(0);

                gen_helper_store_fpcr(cpu_env, tmp);

                tcg_temp_free(tmp);

            }

            break;

        case 0x025:

             

            if (likely(ra != 31)) {

                gen_helper_load_fpcr(cpu_fir[ra], cpu_env);

            }

            break;

        case 0x02A:

             

            gen_fcmov(TCG_COND_EQ, ra, rb, rc);

            break;

        case 0x02B:

             

            gen_fcmov(TCG_COND_NE, ra, rb, rc);

            break;

        case 0x02C:

             

            gen_fcmov(TCG_COND_LT, ra, rb, rc);

            break;

        case 0x02D:

             

            gen_fcmov(TCG_COND_GE, ra, rb, rc);

            break;

        case 0x02E:

             

            gen_fcmov(TCG_COND_LE, ra, rb, rc);

            break;

        case 0x02F:

             

            gen_fcmov(TCG_COND_GT, ra, rb, rc);

            break;

        case 0x030:

             

            gen_fcvtql(rb, rc);

            break;

        case 0x130:

             

        case 0x530:

             

             

            gen_fcvtql_v(ctx, rb, rc);

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

             

             

            break;

        case 0x4400:

             

             

            break;

        case 0x8000:

             

             

            break;

        case 0xA000:

             

             

            break;

        case 0xC000:

             

            if (ra != 31) {

                if (use_icount) {

                    gen_io_start();

                    gen_helper_load_pcc(cpu_ir[ra], cpu_env);

                    gen_io_end();

                    ret = EXIT_PC_STALE;

                } else {

                    gen_helper_load_pcc(cpu_ir[ra], cpu_env);

                }

            }

            break;

        case 0xE000:

             

            gen_rx(ra, 0);

            break;

        case 0xE800:

             

            break;

        case 0xF000:

             

            gen_rx(ra, 1);

            break;

        case 0xF800:

             

             

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x19:


        if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {

            return gen_mfpr(ra, insn & 0xffff);

        }


        goto invalid_opc;

    case 0x1A:

         

        if (rb != 31) {

            tcg_gen_andi_i64(cpu_pc, cpu_ir[rb], ~3);

        } else {

            tcg_gen_movi_i64(cpu_pc, 0);

        }

        if (ra != 31) {

            tcg_gen_movi_i64(cpu_ir[ra], ctx->pc);

        }

        ret = EXIT_PC_UPDATED;

        break;

    case 0x1B:


        if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {

            TCGv addr;



            if (ra == 31) {

                break;

            }



            addr = tcg_temp_new();

            if (rb != 31) {

                tcg_gen_addi_i64(addr, cpu_ir[rb], disp12);

            } else {

                tcg_gen_movi_i64(addr, disp12);

            }

            switch ((insn >> 12) & 0xF) {

            case 0x0:

                 

                gen_helper_ldl_phys(cpu_ir[ra], cpu_env, addr);

                break;

            case 0x1:

                 

                gen_helper_ldq_phys(cpu_ir[ra], cpu_env, addr);

                break;

            case 0x2:

                 

                gen_helper_ldl_l_phys(cpu_ir[ra], cpu_env, addr);

                break;

            case 0x3:

                 

                gen_helper_ldq_l_phys(cpu_ir[ra], cpu_env, addr);

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

                 

                tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_KERNEL_IDX, MO_LESL);

                break;

            case 0xB:

                 

                tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_KERNEL_IDX, MO_LEQ);

                break;

            case 0xC:

                 

                goto invalid_opc;

            case 0xD:

                 

                goto invalid_opc;

            case 0xE:

                 

                tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_USER_IDX, MO_LESL);

                break;

            case 0xF:

                 

                tcg_gen_qemu_ld_i64(cpu_ir[ra], addr, MMU_USER_IDX, MO_LEQ);

                break;

            }

            tcg_temp_free(addr);

            break;

        }


        goto invalid_opc;

    case 0x1C:

        switch (fn7) {

        case 0x00:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_BWX) == 0) {

                goto invalid_opc;

            }

            if (likely(rc != 31)) {

                if (islit) {

                    tcg_gen_movi_i64(cpu_ir[rc], (int64_t)((int8_t)lit));

                } else {

                    tcg_gen_ext8s_i64(cpu_ir[rc], cpu_ir[rb]);

                }

            }

            break;

        case 0x01:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_BWX) {

                if (likely(rc != 31)) {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], (int64_t)((int16_t)lit));

                    } else {

                        tcg_gen_ext16s_i64(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

                break;

            }

            goto invalid_opc;

        case 0x30:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {

                if (likely(rc != 31)) {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], ctpop64(lit));

                    } else {

                        gen_helper_ctpop(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

                break;

            }

            goto invalid_opc;

        case 0x31:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_perr(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x32:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {

                if (likely(rc != 31)) {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], clz64(lit));

                    } else {

                        gen_helper_ctlz(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

                break;

            }

            goto invalid_opc;

        case 0x33:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_CIX) {

                if (likely(rc != 31)) {

                    if (islit) {

                        tcg_gen_movi_i64(cpu_ir[rc], ctz64(lit));

                    } else {

                        gen_helper_cttz(cpu_ir[rc], cpu_ir[rb]);

                    }

                }

                break;

            }

            goto invalid_opc;

        case 0x34:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                if (real_islit || ra != 31) {

                    goto invalid_opc;

                }

                gen_unpkbw(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x35:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                if (real_islit || ra != 31) {

                    goto invalid_opc;

                }

                gen_unpkbl(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x36:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                if (real_islit || ra != 31) {

                    goto invalid_opc;

                }

                gen_pkwb(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x37:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                if (real_islit || ra != 31) {

                    goto invalid_opc;

                }

                gen_pklb(rb, rc);

                break;

            }

            goto invalid_opc;

        case 0x38:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_minsb8(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x39:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_minsw4(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3A:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_minub8(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3B:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_minuw4(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3C:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_maxub8(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3D:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_maxuw4(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3E:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_maxsb8(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x3F:

             

            if (ctx->tb->flags & TB_FLAGS_AMASK_MVI) {

                gen_maxsw4(ra, rb, rc, islit, lit);

                break;

            }

            goto invalid_opc;

        case 0x70:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {

                goto invalid_opc;

            }

            if (likely(rc != 31)) {

                if (ra != 31) {

                    tcg_gen_mov_i64(cpu_ir[rc], cpu_fir[ra]);

                } else {

                    tcg_gen_movi_i64(cpu_ir[rc], 0);

                }

            }

            break;

        case 0x78:

             

            if ((ctx->tb->flags & TB_FLAGS_AMASK_FIX) == 0) {

                goto invalid_opc;

            }

            if (rc != 31) {

                TCGv_i32 tmp1 = tcg_temp_new_i32();

                if (ra != 31) {

                    gen_helper_s_to_memory(tmp1, cpu_fir[ra]);

                } else {

                    TCGv tmp2 = tcg_const_i64(0);

                    gen_helper_s_to_memory(tmp1, tmp2);

                    tcg_temp_free(tmp2);

                }

                tcg_gen_ext_i32_i64(cpu_ir[rc], tmp1);

                tcg_temp_free_i32(tmp1);

            }

            break;

        default:

            goto invalid_opc;

        }

        break;

    case 0x1D:


        if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {

            return gen_mtpr(ctx, rb, insn & 0xffff);

        }


        goto invalid_opc;

    case 0x1E:


        if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {

            if (rb == 31) {

                 

                TCGv tmp = tcg_temp_new();

                tcg_gen_ld_i64(tmp, cpu_env, offsetof(CPUAlphaState, exc_addr));

                gen_helper_hw_ret(cpu_env, tmp);

                tcg_temp_free(tmp);

            } else {

                gen_helper_hw_ret(cpu_env, cpu_ir[rb]);

            }

            ret = EXIT_PC_UPDATED;

            break;

        }


        goto invalid_opc;

    case 0x1F:


        if (ctx->tb->flags & TB_FLAGS_PAL_MODE) {

            TCGv addr, val;

            addr = tcg_temp_new();

            if (rb != 31) {

                tcg_gen_addi_i64(addr, cpu_ir[rb], disp12);

            } else {

                tcg_gen_movi_i64(addr, disp12);

            }

            if (ra != 31) {

                val = cpu_ir[ra];

            } else {

                val = tcg_temp_new();

                tcg_gen_movi_i64(val, 0);

            }

            switch ((insn >> 12) & 0xF) {

            case 0x0:

                 

                gen_helper_stl_phys(cpu_env, addr, val);

                break;

            case 0x1:

                 

                gen_helper_stq_phys(cpu_env, addr, val);

                break;

            case 0x2:

                 

                gen_helper_stl_c_phys(val, cpu_env, addr, val);

                break;

            case 0x3:

                 

                gen_helper_stq_c_phys(val, cpu_env, addr, val);

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

            if (ra == 31) {

                tcg_temp_free(val);

            }

            tcg_temp_free(addr);

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

         

        ret = gen_store_conditional(ctx, ra, rb, disp16, 0);

        break;

    case 0x2F:

         

        ret = gen_store_conditional(ctx, ra, rb, disp16, 1);

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
