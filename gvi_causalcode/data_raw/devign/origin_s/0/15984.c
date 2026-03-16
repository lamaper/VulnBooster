static void gen_sse(DisasContext *s, int b, target_ulong pc_start, int rex_r)

{

    int b1, op1_offset, op2_offset, is_xmm, val, ot;

    int modrm, mod, rm, reg, reg_addr, offset_addr;

    GenOpFunc2 *sse_op2;

    GenOpFunc3 *sse_op3;



    b &= 0xff;

    if (s->prefix & PREFIX_DATA)

        b1 = 1;

    else if (s->prefix & PREFIX_REPZ)

        b1 = 2;

    else if (s->prefix & PREFIX_REPNZ)

        b1 = 3;

    else

        b1 = 0;

    sse_op2 = sse_op_table1[b][b1];

    if (!sse_op2)

        goto illegal_op;

    if ((b <= 0x5f && b >= 0x10) || b == 0xc6 || b == 0xc2) {

        is_xmm = 1;

    } else {

        if (b1 == 0) {

             

            is_xmm = 0;

        } else {

            is_xmm = 1;

        }

    }

     

    if (s->flags & HF_TS_MASK) {

        gen_exception(s, EXCP07_PREX, pc_start - s->cs_base);

        return;

    }

    if (s->flags & HF_EM_MASK) {

    illegal_op:

        gen_exception(s, EXCP06_ILLOP, pc_start - s->cs_base);

        return;

    }

    if (is_xmm && !(s->flags & HF_OSFXSR_MASK))

        goto illegal_op;

    if (b == 0x77 || b == 0x0e) {

         

        gen_op_emms();

        return;

    }

     

    if (!is_xmm) {

        gen_op_enter_mmx();

    }



    modrm = ldub_code(s->pc++);

    reg = ((modrm >> 3) & 7);

    if (is_xmm)

        reg |= rex_r;

    mod = (modrm >> 6) & 3;

    if (sse_op2 == SSE_SPECIAL) {

        b |= (b1 << 8);

        switch(b) {

        case 0x0e7:  

            if (mod == 3)

                goto illegal_op;

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,fpregs[reg].mmx));

            break;

        case 0x1e7:  

        case 0x02b:  

        case 0x12b:  

        case 0x3f0:  

            if (mod == 3)

                goto illegal_op;

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_sto_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg]));

            break;

        case 0x6e:  


            if (s->dflag == 2) {

                gen_ldst_modrm(s, modrm, OT_QUAD, OR_TMP0, 0);

                gen_op_movq_mm_T0_mmx(offsetof(CPUX86State,fpregs[reg].mmx));

            } else


            {

                gen_ldst_modrm(s, modrm, OT_LONG, OR_TMP0, 0);

                gen_op_movl_mm_T0_mmx(offsetof(CPUX86State,fpregs[reg].mmx));

            }

            break;

        case 0x16e:  


            if (s->dflag == 2) {

                gen_ldst_modrm(s, modrm, OT_QUAD, OR_TMP0, 0);

                gen_op_movq_mm_T0_xmm(offsetof(CPUX86State,xmm_regs[reg]));

            } else


            {

                gen_ldst_modrm(s, modrm, OT_LONG, OR_TMP0, 0);

                gen_op_movl_mm_T0_xmm(offsetof(CPUX86State,xmm_regs[reg]));

            }

            break;

        case 0x6f:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,fpregs[reg].mmx));

            } else {

                rm = (modrm & 7);

                gen_op_movq(offsetof(CPUX86State,fpregs[reg].mmx),

                            offsetof(CPUX86State,fpregs[rm].mmx));

            }

            break;

        case 0x010:  

        case 0x110:  

        case 0x028:  

        case 0x128:  

        case 0x16f:  

        case 0x26f:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldo_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg]));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movo(offsetof(CPUX86State,xmm_regs[reg]),

                            offsetof(CPUX86State,xmm_regs[rm]));

            }

            break;

        case 0x210:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_op_ld_T0_A0(OT_LONG + s->mem_index);

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)));

                gen_op_movl_T0_0();

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(1)));

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(2)));

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(3)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_L(0)));

            }

            break;

        case 0x310:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

                gen_op_movl_T0_0();

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(2)));

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_regs[reg].XMM_L(3)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)));

            }

            break;

        case 0x012:  

        case 0x112:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                 

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_Q(1)));

            }

            break;

        case 0x212:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldo_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg]));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_L(0)));

                gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(2)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_L(2)));

            }

            gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(1)),

                        offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)));

            gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(3)),

                        offsetof(CPUX86State,xmm_regs[reg].XMM_L(2)));

            break;

        case 0x312:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)));

            }

            gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)),

                        offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            break;

        case 0x016:  

        case 0x116:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)));

            } else {

                 

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)));

            }

            break;

        case 0x216:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldo_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg]));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(1)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_L(1)));

                gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(3)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_L(3)));

            }

            gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)),

                        offsetof(CPUX86State,xmm_regs[reg].XMM_L(1)));

            gen_op_movl(offsetof(CPUX86State,xmm_regs[reg].XMM_L(2)),

                        offsetof(CPUX86State,xmm_regs[reg].XMM_L(3)));

            break;

        case 0x7e:  


            if (s->dflag == 2) {

                gen_op_movq_T0_mm_mmx(offsetof(CPUX86State,fpregs[reg].mmx));

                gen_ldst_modrm(s, modrm, OT_QUAD, OR_TMP0, 1);

            } else


            {

                gen_op_movl_T0_mm_mmx(offsetof(CPUX86State,fpregs[reg].mmx));

                gen_ldst_modrm(s, modrm, OT_LONG, OR_TMP0, 1);

            }

            break;

        case 0x17e:  


            if (s->dflag == 2) {

                gen_op_movq_T0_mm_xmm(offsetof(CPUX86State,xmm_regs[reg]));

                gen_ldst_modrm(s, modrm, OT_QUAD, OR_TMP0, 1);

            } else


            {

                gen_op_movl_T0_mm_xmm(offsetof(CPUX86State,xmm_regs[reg]));

                gen_ldst_modrm(s, modrm, OT_LONG, OR_TMP0, 1);

            }

            break;

        case 0x27e:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)));

            }

            gen_op_movq_env_0(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)));

            break;

        case 0x7f:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,fpregs[reg].mmx));

            } else {

                rm = (modrm & 7);

                gen_op_movq(offsetof(CPUX86State,fpregs[rm].mmx),

                            offsetof(CPUX86State,fpregs[reg].mmx));

            }

            break;

        case 0x011:  

        case 0x111:  

        case 0x029:  

        case 0x129:  

        case 0x17f:  

        case 0x27f:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_sto_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg]));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movo(offsetof(CPUX86State,xmm_regs[rm]),

                            offsetof(CPUX86State,xmm_regs[reg]));

            }

            break;

        case 0x211:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_op_movl_T0_env(offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)));

                gen_op_st_T0_A0(OT_LONG + s->mem_index);

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movl(offsetof(CPUX86State,xmm_regs[rm].XMM_L(0)),

                            offsetof(CPUX86State,xmm_regs[reg].XMM_L(0)));

            }

            break;

        case 0x311:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            }

            break;

        case 0x013:  

        case 0x113:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                goto illegal_op;

            }

            break;

        case 0x017:  

        case 0x117:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)));

            } else {

                goto illegal_op;

            }

            break;

        case 0x71:  

        case 0x72:

        case 0x73:

        case 0x171:  

        case 0x172:

        case 0x173:

            val = ldub_code(s->pc++);

            if (is_xmm) {

                gen_op_movl_T0_im(val);

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_t0.XMM_L(0)));

                gen_op_movl_T0_0();

                gen_op_movl_env_T0(offsetof(CPUX86State,xmm_t0.XMM_L(1)));

                op1_offset = offsetof(CPUX86State,xmm_t0);

            } else {

                gen_op_movl_T0_im(val);

                gen_op_movl_env_T0(offsetof(CPUX86State,mmx_t0.MMX_L(0)));

                gen_op_movl_T0_0();

                gen_op_movl_env_T0(offsetof(CPUX86State,mmx_t0.MMX_L(1)));

                op1_offset = offsetof(CPUX86State,mmx_t0);

            }

            sse_op2 = sse_op_table2[((b - 1) & 3) * 8 + (((modrm >> 3)) & 7)][b1];

            if (!sse_op2)

                goto illegal_op;

            if (is_xmm) {

                rm = (modrm & 7) | REX_B(s);

                op2_offset = offsetof(CPUX86State,xmm_regs[rm]);

            } else {

                rm = (modrm & 7);

                op2_offset = offsetof(CPUX86State,fpregs[rm].mmx);

            }

            sse_op2(op2_offset, op1_offset);

            break;

        case 0x050:  

            rm = (modrm & 7) | REX_B(s);

            gen_op_movmskps(offsetof(CPUX86State,xmm_regs[rm]));

            gen_op_mov_reg_T0(OT_LONG, reg);

            break;

        case 0x150:  

            rm = (modrm & 7) | REX_B(s);

            gen_op_movmskpd(offsetof(CPUX86State,xmm_regs[rm]));

            gen_op_mov_reg_T0(OT_LONG, reg);

            break;

        case 0x02a:  

        case 0x12a:  

            gen_op_enter_mmx();

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                op2_offset = offsetof(CPUX86State,mmx_t0);

                gen_ldq_env_A0[s->mem_index >> 2](op2_offset);

            } else {

                rm = (modrm & 7);

                op2_offset = offsetof(CPUX86State,fpregs[rm].mmx);

            }

            op1_offset = offsetof(CPUX86State,xmm_regs[reg]);

            switch(b >> 8) {

            case 0x0:

                gen_op_cvtpi2ps(op1_offset, op2_offset);

                break;

            default:

            case 0x1:

                gen_op_cvtpi2pd(op1_offset, op2_offset);

                break;

            }

            break;

        case 0x22a:  

        case 0x32a:  

            ot = (s->dflag == 2) ? OT_QUAD : OT_LONG;

            gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

            op1_offset = offsetof(CPUX86State,xmm_regs[reg]);

            sse_op_table3[(s->dflag == 2) * 2 + ((b >> 8) - 2)](op1_offset);

            break;

        case 0x02c:  

        case 0x12c:  

        case 0x02d:  

        case 0x12d:  

            gen_op_enter_mmx();

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                op2_offset = offsetof(CPUX86State,xmm_t0);

                gen_ldo_env_A0[s->mem_index >> 2](op2_offset);

            } else {

                rm = (modrm & 7) | REX_B(s);

                op2_offset = offsetof(CPUX86State,xmm_regs[rm]);

            }

            op1_offset = offsetof(CPUX86State,fpregs[reg & 7].mmx);

            switch(b) {

            case 0x02c:

                gen_op_cvttps2pi(op1_offset, op2_offset);

                break;

            case 0x12c:

                gen_op_cvttpd2pi(op1_offset, op2_offset);

                break;

            case 0x02d:

                gen_op_cvtps2pi(op1_offset, op2_offset);

                break;

            case 0x12d:

                gen_op_cvtpd2pi(op1_offset, op2_offset);

                break;

            }

            break;

        case 0x22c:  

        case 0x32c:  

        case 0x22d:  

        case 0x32d:  

            ot = (s->dflag == 2) ? OT_QUAD : OT_LONG;

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                if ((b >> 8) & 1) {

                    gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_t0.XMM_Q(0)));

                } else {

                    gen_op_ld_T0_A0(OT_LONG + s->mem_index);

                    gen_op_movl_env_T0(offsetof(CPUX86State,xmm_t0.XMM_L(0)));

                }

                op2_offset = offsetof(CPUX86State,xmm_t0);

            } else {

                rm = (modrm & 7) | REX_B(s);

                op2_offset = offsetof(CPUX86State,xmm_regs[rm]);

            }

            sse_op_table3[(s->dflag == 2) * 2 + ((b >> 8) - 2) + 4 +

                          (b & 1) * 4](op2_offset);

            gen_op_mov_reg_T0(ot, reg);

            break;

        case 0xc4:  

        case 0x1c4:

            s->rip_offset = 1;

            gen_ldst_modrm(s, modrm, OT_WORD, OR_TMP0, 0);

            val = ldub_code(s->pc++);

            if (b1) {

                val &= 7;

                gen_op_pinsrw_xmm(offsetof(CPUX86State,xmm_regs[reg]), val);

            } else {

                val &= 3;

                gen_op_pinsrw_mmx(offsetof(CPUX86State,fpregs[reg].mmx), val);

            }

            break;

        case 0xc5:  

        case 0x1c5:

            if (mod != 3)

                goto illegal_op;

            val = ldub_code(s->pc++);

            if (b1) {

                val &= 7;

                rm = (modrm & 7) | REX_B(s);

                gen_op_pextrw_xmm(offsetof(CPUX86State,xmm_regs[rm]), val);

            } else {

                val &= 3;

                rm = (modrm & 7);

                gen_op_pextrw_mmx(offsetof(CPUX86State,fpregs[rm].mmx), val);

            }

            reg = ((modrm >> 3) & 7) | rex_r;

            gen_op_mov_reg_T0(OT_LONG, reg);

            break;

        case 0x1d6:  

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_stq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

            } else {

                rm = (modrm & 7) | REX_B(s);

                gen_op_movq(offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)),

                            offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)));

                gen_op_movq_env_0(offsetof(CPUX86State,xmm_regs[rm].XMM_Q(1)));

            }

            break;

        case 0x2d6:  

            gen_op_enter_mmx();

            rm = (modrm & 7);

            gen_op_movq(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(0)),

                        offsetof(CPUX86State,fpregs[rm].mmx));

            gen_op_movq_env_0(offsetof(CPUX86State,xmm_regs[reg].XMM_Q(1)));

            break;

        case 0x3d6:  

            gen_op_enter_mmx();

            rm = (modrm & 7) | REX_B(s);

            gen_op_movq(offsetof(CPUX86State,fpregs[reg & 7].mmx),

                        offsetof(CPUX86State,xmm_regs[rm].XMM_Q(0)));

            break;

        case 0xd7:  

        case 0x1d7:

            if (mod != 3)

                goto illegal_op;

            if (b1) {

                rm = (modrm & 7) | REX_B(s);

                gen_op_pmovmskb_xmm(offsetof(CPUX86State,xmm_regs[rm]));

            } else {

                rm = (modrm & 7);

                gen_op_pmovmskb_mmx(offsetof(CPUX86State,fpregs[rm].mmx));

            }

            reg = ((modrm >> 3) & 7) | rex_r;

            gen_op_mov_reg_T0(OT_LONG, reg);

            break;

        default:

            goto illegal_op;

        }

    } else {

         

        switch(b) {

        case 0xf7:

             

            if (mod != 3)

                goto illegal_op;


            if (s->aflag == 2) {

                gen_op_movq_A0_reg(R_EDI);

            } else


            {

                gen_op_movl_A0_reg(R_EDI);

                if (s->aflag == 0)

                    gen_op_andl_A0_ffff();

            }

            gen_add_A0_ds_seg(s);

            break;

        case 0x70:  

        case 0xc6:  

        case 0xc2:  

            s->rip_offset = 1;

            break;

        default:

            break;

        }

        if (is_xmm) {

            op1_offset = offsetof(CPUX86State,xmm_regs[reg]);

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                op2_offset = offsetof(CPUX86State,xmm_t0);

                if (b1 >= 2 && ((b >= 0x50 && b <= 0x5f && b != 0x5b) ||

                                b == 0xc2)) {

                     

                    if (b1 == 2) {

                         

                        gen_op_ld_T0_A0(OT_LONG + s->mem_index);

                        gen_op_movl_env_T0(offsetof(CPUX86State,xmm_t0.XMM_L(0)));

                    } else {

                         

                        gen_ldq_env_A0[s->mem_index >> 2](offsetof(CPUX86State,xmm_t0.XMM_D(0)));

                    }

                } else {

                    gen_ldo_env_A0[s->mem_index >> 2](op2_offset);

                }

            } else {

                rm = (modrm & 7) | REX_B(s);

                op2_offset = offsetof(CPUX86State,xmm_regs[rm]);

            }

        } else {

            op1_offset = offsetof(CPUX86State,fpregs[reg].mmx);

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                op2_offset = offsetof(CPUX86State,mmx_t0);

                gen_ldq_env_A0[s->mem_index >> 2](op2_offset);

            } else {

                rm = (modrm & 7);

                op2_offset = offsetof(CPUX86State,fpregs[rm].mmx);

            }

        }

        switch(b) {

        case 0x0f:  

            val = ldub_code(s->pc++);

            sse_op2 = sse_op_table5[val];

            if (!sse_op2)

                goto illegal_op;

            sse_op2(op1_offset, op2_offset);

            break;

        case 0x70:  

        case 0xc6:  

            val = ldub_code(s->pc++);

            sse_op3 = (GenOpFunc3 *)sse_op2;

            sse_op3(op1_offset, op2_offset, val);

            break;

        case 0xc2:

             

            val = ldub_code(s->pc++);

            if (val >= 8)

                goto illegal_op;

            sse_op2 = sse_op_table4[val][b1];

            sse_op2(op1_offset, op2_offset);

            break;

        default:

            sse_op2(op1_offset, op2_offset);

            break;

        }

        if (b == 0x2e || b == 0x2f) {

            s->cc_op = CC_OP_EFLAGS;

        }

    }

}
