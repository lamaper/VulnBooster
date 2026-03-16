static int disas_vfp_insn(CPUState * env, DisasContext *s, uint32_t insn)

{

    uint32_t rd, rn, rm, op, i, n, offset, delta_d, delta_m, bank_mask;

    int dp, veclen;

    TCGv addr;

    TCGv tmp;

    TCGv tmp2;



    if (!arm_feature(env, ARM_FEATURE_VFP))

        return 1;



    if (!vfp_enabled(env)) {

         

        if ((insn & 0x0fe00fff) != 0x0ee00a10)

            return 1;

        rn = (insn >> 16) & 0xf;

        if (rn != ARM_VFP_FPSID && rn != ARM_VFP_FPEXC

            && rn != ARM_VFP_MVFR1 && rn != ARM_VFP_MVFR0)

            return 1;

    }

    dp = ((insn & 0xf00) == 0xb00);

    switch ((insn >> 24) & 0xf) {

    case 0xe:

        if (insn & (1 << 4)) {

             

            rd = (insn >> 12) & 0xf;

            if (dp) {

                int size;

                int pass;



                VFP_DREG_N(rn, insn);

                if (insn & 0xf)

                    return 1;

                if (insn & 0x00c00060

                    && !arm_feature(env, ARM_FEATURE_NEON))

                    return 1;



                pass = (insn >> 21) & 1;

                if (insn & (1 << 22)) {

                    size = 0;

                    offset = ((insn >> 5) & 3) * 8;

                } else if (insn & (1 << 5)) {

                    size = 1;

                    offset = (insn & (1 << 6)) ? 16 : 0;

                } else {

                    size = 2;

                    offset = 0;

                }

                if (insn & ARM_CP_RW_BIT) {

                     

                    tmp = neon_load_reg(rn, pass);

                    switch (size) {

                    case 0:

                        if (offset)

                            tcg_gen_shri_i32(tmp, tmp, offset);

                        if (insn & (1 << 23))

                            gen_uxtb(tmp);

                        else

                            gen_sxtb(tmp);

                        break;

                    case 1:

                        if (insn & (1 << 23)) {

                            if (offset) {

                                tcg_gen_shri_i32(tmp, tmp, 16);

                            } else {

                                gen_uxth(tmp);

                            }

                        } else {

                            if (offset) {

                                tcg_gen_sari_i32(tmp, tmp, 16);

                            } else {

                                gen_sxth(tmp);

                            }

                        }

                        break;

                    case 2:

                        break;

                    }

                    store_reg(s, rd, tmp);

                } else {

                     

                    tmp = load_reg(s, rd);

                    if (insn & (1 << 23)) {

                         

                        if (size == 0) {

                            gen_neon_dup_u8(tmp, 0);

                        } else if (size == 1) {

                            gen_neon_dup_low16(tmp);

                        }

                        for (n = 0; n <= pass * 2; n++) {

                            tmp2 = new_tmp();

                            tcg_gen_mov_i32(tmp2, tmp);

                            neon_store_reg(rn, n, tmp2);

                        }

                        neon_store_reg(rn, n, tmp);

                    } else {

                         

                        switch (size) {

                        case 0:

                            tmp2 = neon_load_reg(rn, pass);

                            gen_bfi(tmp, tmp2, tmp, offset, 0xff);

                            dead_tmp(tmp2);

                            break;

                        case 1:

                            tmp2 = neon_load_reg(rn, pass);

                            gen_bfi(tmp, tmp2, tmp, offset, 0xffff);

                            dead_tmp(tmp2);

                            break;

                        case 2:

                            break;

                        }

                        neon_store_reg(rn, pass, tmp);

                    }

                }

            } else {  

                if ((insn & 0x6f) != 0x00)

                    return 1;

                rn = VFP_SREG_N(insn);

                if (insn & ARM_CP_RW_BIT) {

                     

                    if (insn & (1 << 21)) {

                         

                        rn >>= 1;



                        switch (rn) {

                        case ARM_VFP_FPSID:

                             

                            if (IS_USER(s)

                                && arm_feature(env, ARM_FEATURE_VFP3))

                                return 1;

                            tmp = load_cpu_field(vfp.xregs[rn]);

                            break;

                        case ARM_VFP_FPEXC:

                            if (IS_USER(s))

                                return 1;

                            tmp = load_cpu_field(vfp.xregs[rn]);

                            break;

                        case ARM_VFP_FPINST:

                        case ARM_VFP_FPINST2:

                             

                            if (IS_USER(s)

                                || arm_feature(env, ARM_FEATURE_VFP3))

                                return 1;

                            tmp = load_cpu_field(vfp.xregs[rn]);

                            break;

                        case ARM_VFP_FPSCR:

                            if (rd == 15) {

                                tmp = load_cpu_field(vfp.xregs[ARM_VFP_FPSCR]);

                                tcg_gen_andi_i32(tmp, tmp, 0xf0000000);

                            } else {

                                tmp = new_tmp();

                                gen_helper_vfp_get_fpscr(tmp, cpu_env);

                            }

                            break;

                        case ARM_VFP_MVFR0:

                        case ARM_VFP_MVFR1:

                            if (IS_USER(s)

                                || !arm_feature(env, ARM_FEATURE_VFP3))

                                return 1;

                            tmp = load_cpu_field(vfp.xregs[rn]);

                            break;

                        default:

                            return 1;

                        }

                    } else {

                        gen_mov_F0_vreg(0, rn);

                        tmp = gen_vfp_mrs();

                    }

                    if (rd == 15) {

                         

                        gen_set_nzcv(tmp);

                        dead_tmp(tmp);

                    } else {

                        store_reg(s, rd, tmp);

                    }

                } else {

                     

                    tmp = load_reg(s, rd);

                    if (insn & (1 << 21)) {

                        rn >>= 1;

                         

                        switch (rn) {

                        case ARM_VFP_FPSID:

                        case ARM_VFP_MVFR0:

                        case ARM_VFP_MVFR1:

                             

                            break;

                        case ARM_VFP_FPSCR:

                            gen_helper_vfp_set_fpscr(cpu_env, tmp);

                            dead_tmp(tmp);

                            gen_lookup_tb(s);

                            break;

                        case ARM_VFP_FPEXC:

                            if (IS_USER(s))

                                return 1;




                            store_cpu_field(tmp, vfp.xregs[rn]);

                            gen_lookup_tb(s);

                            break;

                        case ARM_VFP_FPINST:

                        case ARM_VFP_FPINST2:

                            store_cpu_field(tmp, vfp.xregs[rn]);

                            break;

                        default:

                            return 1;

                        }

                    } else {

                        gen_vfp_msr(tmp);

                        gen_mov_vreg_F0(0, rn);

                    }

                }

            }

        } else {

             

             

            op = ((insn >> 20) & 8) | ((insn >> 19) & 6) | ((insn >> 6) & 1);

            if (dp) {

                if (op == 15) {

                     

                    rn = ((insn >> 15) & 0x1e) | ((insn >> 7) & 1);

                } else {

                     

                    VFP_DREG_N(rn, insn);

                }



                if (op == 15 && (rn == 15 || rn > 17)) {

                     

                    rd = VFP_SREG_D(insn);

                } else {

                    VFP_DREG_D(rd, insn);

                }



                if (op == 15 && (rn == 16 || rn == 17)) {

                     

                    rm = ((insn << 1) & 0x1e) | ((insn >> 5) & 1);

                } else {

                    VFP_DREG_M(rm, insn);

                }

            } else {

                rn = VFP_SREG_N(insn);

                if (op == 15 && rn == 15) {

                     

                    VFP_DREG_D(rd, insn);

                } else {

                    rd = VFP_SREG_D(insn);

                }

                rm = VFP_SREG_M(insn);

            }



            veclen = env->vfp.vec_len;

            if (op == 15 && rn > 3)

                veclen = 0;



             

            delta_m = 0;

            delta_d = 0;

            bank_mask = 0;



            if (veclen > 0) {

                if (dp)

                    bank_mask = 0xc;

                else

                    bank_mask = 0x18;



                 

                if ((rd & bank_mask) == 0) {

                     

                    veclen = 0;

                } else {

                    if (dp)

                        delta_d = (env->vfp.vec_stride >> 1) + 1;

                    else

                        delta_d = env->vfp.vec_stride + 1;



                    if ((rm & bank_mask) == 0) {

                         

                        delta_m = 0;

                    } else {

                         

                        delta_m = delta_d;

                    }

                }

            }



             

            if (op == 15) {

                switch (rn) {

                case 16:

                case 17:

                     

                    gen_mov_F0_vreg(0, rm);

                    break;

                case 8:

                case 9:

                     

                    gen_mov_F0_vreg(dp, rd);

                    gen_mov_F1_vreg(dp, rm);

                    break;

                case 10:

                case 11:

                     

                    gen_mov_F0_vreg(dp, rd);

                    gen_vfp_F1_ld0(dp);

                    break;

                case 20:

                case 21:

                case 22:

                case 23:

                case 28:

                case 29:

                case 30:

                case 31:

                     

                    gen_mov_F0_vreg(dp, rd);

                    break;

                default:

                     

                    gen_mov_F0_vreg(dp, rm);

                    break;

                }

            } else {

                 

                gen_mov_F0_vreg(dp, rn);

                gen_mov_F1_vreg(dp, rm);

            }



            for (;;) {

                 

                switch (op) {

                case 0:  

                    gen_vfp_mul(dp);

                    gen_mov_F1_vreg(dp, rd);

                    gen_vfp_add(dp);

                    break;

                case 1:  

                    gen_vfp_mul(dp);

                    gen_vfp_neg(dp);

                    gen_mov_F1_vreg(dp, rd);

                    gen_vfp_add(dp);

                    break;

                case 2:  

                    gen_vfp_mul(dp);

                    gen_mov_F1_vreg(dp, rd);

                    gen_vfp_sub(dp);

                    break;

                case 3:  

                    gen_vfp_mul(dp);

                    gen_vfp_neg(dp);

                    gen_mov_F1_vreg(dp, rd);

                    gen_vfp_sub(dp);

                    break;

                case 4:  

                    gen_vfp_mul(dp);

                    break;

                case 5:  

                    gen_vfp_mul(dp);

                    gen_vfp_neg(dp);

                    break;

                case 6:  

                    gen_vfp_add(dp);

                    break;

                case 7:  

                    gen_vfp_sub(dp);

                    break;

                case 8:  

                    gen_vfp_div(dp);

                    break;

                case 14:  

                    if (!arm_feature(env, ARM_FEATURE_VFP3))

                      return 1;



                    n = (insn << 12) & 0x80000000;

                    i = ((insn >> 12) & 0x70) | (insn & 0xf);

                    if (dp) {

                        if (i & 0x40)

                            i |= 0x3f80;

                        else

                            i |= 0x4000;

                        n |= i << 16;

                        tcg_gen_movi_i64(cpu_F0d, ((uint64_t)n) << 32);

                    } else {

                        if (i & 0x40)

                            i |= 0x780;

                        else

                            i |= 0x800;

                        n |= i << 19;

                        tcg_gen_movi_i32(cpu_F0s, n);

                    }

                    break;

                case 15:  

                    switch (rn) {

                    case 0:  

                         

                        break;

                    case 1:  

                        gen_vfp_abs(dp);

                        break;

                    case 2:  

                        gen_vfp_neg(dp);

                        break;

                    case 3:  

                        gen_vfp_sqrt(dp);

                        break;

                    case 8:  

                        gen_vfp_cmp(dp);

                        break;

                    case 9:  

                        gen_vfp_cmpe(dp);

                        break;

                    case 10:  

                        gen_vfp_cmp(dp);

                        break;

                    case 11:  

                        gen_vfp_F1_ld0(dp);

                        gen_vfp_cmpe(dp);

                        break;

                    case 15:  

                        if (dp)

                            gen_helper_vfp_fcvtsd(cpu_F0s, cpu_F0d, cpu_env);

                        else

                            gen_helper_vfp_fcvtds(cpu_F0d, cpu_F0s, cpu_env);

                        break;

                    case 16:  

                        gen_vfp_uito(dp);

                        break;

                    case 17:  

                        gen_vfp_sito(dp);

                        break;

                    case 20:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_shto(dp, 16 - rm);

                        break;

                    case 21:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_slto(dp, 32 - rm);

                        break;

                    case 22:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_uhto(dp, 16 - rm);

                        break;

                    case 23:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_ulto(dp, 32 - rm);

                        break;

                    case 24:  

                        gen_vfp_toui(dp);

                        break;

                    case 25:  

                        gen_vfp_touiz(dp);

                        break;

                    case 26:  

                        gen_vfp_tosi(dp);

                        break;

                    case 27:  

                        gen_vfp_tosiz(dp);

                        break;

                    case 28:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_tosh(dp, 16 - rm);

                        break;

                    case 29:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_tosl(dp, 32 - rm);

                        break;

                    case 30:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_touh(dp, 16 - rm);

                        break;

                    case 31:  

                        if (!arm_feature(env, ARM_FEATURE_VFP3))

                          return 1;

                        gen_vfp_toul(dp, 32 - rm);

                        break;

                    default:  

                        printf ("rn:%d\n", rn);

                        return 1;

                    }

                    break;

                default:  

                    printf ("op:%d\n", op);

                    return 1;

                }



                 

                if (op == 15 && (rn >= 8 && rn <= 11))

                    ;  

                else if (op == 15 && rn > 17)

                     

                    gen_mov_vreg_F0(0, rd);

                else if (op == 15 && rn == 15)

                     

                    gen_mov_vreg_F0(!dp, rd);

                else

                    gen_mov_vreg_F0(dp, rd);



                 

                if (veclen == 0)

                    break;



                if (op == 15 && delta_m == 0) {

                     

                    while (veclen--) {

                        rd = ((rd + delta_d) & (bank_mask - 1))

                             | (rd & bank_mask);

                        gen_mov_vreg_F0(dp, rd);

                    }

                    break;

                }

                 

                veclen--;

                rd = ((rd + delta_d) & (bank_mask - 1))

                     | (rd & bank_mask);



                if (op == 15) {

                     

                    rm = ((rm + delta_m) & (bank_mask - 1))

                         | (rm & bank_mask);

                    gen_mov_F0_vreg(dp, rm);

                } else {

                     

                    rn = ((rn + delta_d) & (bank_mask - 1))

                         | (rn & bank_mask);

                    gen_mov_F0_vreg(dp, rn);

                    if (delta_m) {

                        rm = ((rm + delta_m) & (bank_mask - 1))

                             | (rm & bank_mask);

                        gen_mov_F1_vreg(dp, rm);

                    }

                }

            }

        }

        break;

    case 0xc:

    case 0xd:

        if (dp && (insn & 0x03e00000) == 0x00400000) {

             

            rn = (insn >> 16) & 0xf;

            rd = (insn >> 12) & 0xf;

            if (dp) {

                VFP_DREG_M(rm, insn);

            } else {

                rm = VFP_SREG_M(insn);

            }



            if (insn & ARM_CP_RW_BIT) {

                 

                if (dp) {

                    gen_mov_F0_vreg(0, rm * 2);

                    tmp = gen_vfp_mrs();

                    store_reg(s, rd, tmp);

                    gen_mov_F0_vreg(0, rm * 2 + 1);

                    tmp = gen_vfp_mrs();

                    store_reg(s, rn, tmp);

                } else {

                    gen_mov_F0_vreg(0, rm);

                    tmp = gen_vfp_mrs();

                    store_reg(s, rn, tmp);

                    gen_mov_F0_vreg(0, rm + 1);

                    tmp = gen_vfp_mrs();

                    store_reg(s, rd, tmp);

                }

            } else {

                 

                if (dp) {

                    tmp = load_reg(s, rd);

                    gen_vfp_msr(tmp);

                    gen_mov_vreg_F0(0, rm * 2);

                    tmp = load_reg(s, rn);

                    gen_vfp_msr(tmp);

                    gen_mov_vreg_F0(0, rm * 2 + 1);

                } else {

                    tmp = load_reg(s, rn);

                    gen_vfp_msr(tmp);

                    gen_mov_vreg_F0(0, rm);

                    tmp = load_reg(s, rd);

                    gen_vfp_msr(tmp);

                    gen_mov_vreg_F0(0, rm + 1);

                }

            }

        } else {

             

            rn = (insn >> 16) & 0xf;

            if (dp)

                VFP_DREG_D(rd, insn);

            else

                rd = VFP_SREG_D(insn);

            if (s->thumb && rn == 15) {

                addr = new_tmp();

                tcg_gen_movi_i32(addr, s->pc & ~2);

            } else {

                addr = load_reg(s, rn);

            }

            if ((insn & 0x01200000) == 0x01000000) {

                 

                offset = (insn & 0xff) << 2;

                if ((insn & (1 << 23)) == 0)

                    offset = -offset;

                tcg_gen_addi_i32(addr, addr, offset);

                if (insn & (1 << 20)) {

                    gen_vfp_ld(s, dp, addr);

                    gen_mov_vreg_F0(dp, rd);

                } else {

                    gen_mov_F0_vreg(dp, rd);

                    gen_vfp_st(s, dp, addr);

                }

                dead_tmp(addr);

            } else {

                 

                if (dp)

                    n = (insn >> 1) & 0x7f;

                else

                    n = insn & 0xff;



                if (insn & (1 << 24))  

                    tcg_gen_addi_i32(addr, addr, -((insn & 0xff) << 2));



                if (dp)

                    offset = 8;

                else

                    offset = 4;

                for (i = 0; i < n; i++) {

                    if (insn & ARM_CP_RW_BIT) {

                         

                        gen_vfp_ld(s, dp, addr);

                        gen_mov_vreg_F0(dp, rd + i);

                    } else {

                         

                        gen_mov_F0_vreg(dp, rd + i);

                        gen_vfp_st(s, dp, addr);

                    }

                    tcg_gen_addi_i32(addr, addr, offset);

                }

                if (insn & (1 << 21)) {

                     

                    if (insn & (1 << 24))

                        offset = -offset * n;

                    else if (dp && (insn & 1))

                        offset = 4;

                    else

                        offset = 0;



                    if (offset != 0)

                        tcg_gen_addi_i32(addr, addr, offset);

                    store_reg(s, rn, addr);

                } else {

                    dead_tmp(addr);

                }

            }

        }

        break;

    default:

         

        return 1;

    }

    return 0;

}