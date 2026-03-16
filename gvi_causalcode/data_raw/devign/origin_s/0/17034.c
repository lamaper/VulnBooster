long disas_insn(DisasContext *s, uint8_t *pc_start)

{

    int b, prefixes, aflag, dflag;

    int shift, ot;

    int modrm, reg, rm, mod, reg_addr, op, opreg, offset_addr, val;

    unsigned int next_eip;



    s->pc = pc_start;

    prefixes = 0;

    aflag = s->code32;

    dflag = s->code32;

     

 next_byte:

    b = ldub(s->pc);

    s->pc++;

     

    switch (b) {

    case 0xf3:

        prefixes |= PREFIX_REPZ;

        goto next_byte;

    case 0xf2:

        prefixes |= PREFIX_REPNZ;

        goto next_byte;

    case 0xf0:

        prefixes |= PREFIX_LOCK;

        goto next_byte;

    case 0x2e:

        prefixes |= PREFIX_CS;

        goto next_byte;

    case 0x36:

        prefixes |= PREFIX_SS;

        goto next_byte;

    case 0x3e:

        prefixes |= PREFIX_DS;

        goto next_byte;

    case 0x26:

        prefixes |= PREFIX_ES;

        goto next_byte;

    case 0x64:

        prefixes |= PREFIX_FS;

        goto next_byte;

    case 0x65:

        prefixes |= PREFIX_GS;

        goto next_byte;

    case 0x66:

        prefixes |= PREFIX_DATA;

        goto next_byte;

    case 0x67:

        prefixes |= PREFIX_ADR;

        goto next_byte;

    case 0x9b:

        prefixes |= PREFIX_FWAIT;

        goto next_byte;

    }



    if (prefixes & PREFIX_DATA)

        dflag ^= 1;

    if (prefixes & PREFIX_ADR)

        aflag ^= 1;



    s->prefix = prefixes;

    s->aflag = aflag;

    s->dflag = dflag;



     

    if (prefixes & PREFIX_LOCK)

        gen_op_lock();



     

 reswitch:

    switch(b) {

    case 0x0f:

         

         

        b = ldub(s->pc++) | 0x100;

        goto reswitch;

        

         

         

    case 0x00 ... 0x05:

    case 0x08 ... 0x0d:

    case 0x10 ... 0x15:

    case 0x18 ... 0x1d:

    case 0x20 ... 0x25:

    case 0x28 ... 0x2d:

    case 0x30 ... 0x35:

    case 0x38 ... 0x3d:

        {

            int op, f, val;

            op = (b >> 3) & 7;

            f = (b >> 1) & 3;



            if ((b & 1) == 0)

                ot = OT_BYTE;

            else

                ot = dflag ? OT_LONG : OT_WORD;

            

            switch(f) {

            case 0:  

                modrm = ldub(s->pc++);

                reg = ((modrm >> 3) & 7) + OR_EAX;

                mod = (modrm >> 6) & 3;

                rm = modrm & 7;

                if (mod != 3) {

                    gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                    gen_op_ld_T0_A0[ot]();

                    opreg = OR_TMP0;

                } else {

                    opreg = OR_EAX + rm;

                }

                gen_op(s, op, ot, opreg, reg);

                if (mod != 3 && op != 7) {

                    gen_op_st_T0_A0[ot]();

                }

                break;

            case 1:  

                modrm = ldub(s->pc++);

                mod = (modrm >> 6) & 3;

                reg = ((modrm >> 3) & 7) + OR_EAX;

                rm = modrm & 7;

                if (mod != 3) {

                    gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                    gen_op_ld_T1_A0[ot]();

                    opreg = OR_TMP1;

                } else {

                    opreg = OR_EAX + rm;

                }

                gen_op(s, op, ot, reg, opreg);

                break;

            case 2:  

                val = insn_get(s, ot);

                gen_opi(s, op, ot, OR_EAX, val);

                break;

            }

        }

        break;



    case 0x80:  

    case 0x81:

    case 0x83:

        {

            int val;



            if ((b & 1) == 0)

                ot = OT_BYTE;

            else

                ot = dflag ? OT_LONG : OT_WORD;

            

            modrm = ldub(s->pc++);

            mod = (modrm >> 6) & 3;

            rm = modrm & 7;

            op = (modrm >> 3) & 7;

            

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_op_ld_T0_A0[ot]();

                opreg = OR_TMP0;

            } else {

                opreg = rm + OR_EAX;

            }



            switch(b) {

            default:

            case 0x80:

            case 0x81:

                val = insn_get(s, ot);

                break;

            case 0x83:

                val = (int8_t)insn_get(s, OT_BYTE);

                break;

            }



            gen_opi(s, op, ot, opreg, val);

            if (op != 7 && mod != 3) {

                gen_op_st_T0_A0[ot]();

            }

        }

        break;



         

         

    case 0x40 ... 0x47:  

        ot = dflag ? OT_LONG : OT_WORD;

        gen_inc(s, ot, OR_EAX + (b & 7), 1);

        break;

    case 0x48 ... 0x4f:  

        ot = dflag ? OT_LONG : OT_WORD;

        gen_inc(s, ot, OR_EAX + (b & 7), -1);

        break;

    case 0xf6:  

    case 0xf7:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;



        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        op = (modrm >> 3) & 7;

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_ld_T0_A0[ot]();

        } else {

            gen_op_mov_TN_reg[ot][0][rm]();

        }



        switch(op) {

        case 0:  

            val = insn_get(s, ot);

            gen_op_movl_T1_im(val);

            gen_op_testl_T0_T1_cc();

            s->cc_op = CC_OP_LOGICB + ot;

            break;

        case 2:  

            gen_op_notl_T0();

            if (mod != 3) {

                gen_op_st_T0_A0[ot]();

            } else {

                gen_op_mov_reg_T0[ot][rm]();

            }

            break;

        case 3:  

            gen_op_negl_T0_cc();

            if (mod != 3) {

                gen_op_st_T0_A0[ot]();

            } else {

                gen_op_mov_reg_T0[ot][rm]();

            }

            s->cc_op = CC_OP_SUBB + ot;

            break;

        case 4:  

            switch(ot) {

            case OT_BYTE:

                gen_op_mulb_AL_T0();

                break;

            case OT_WORD:

                gen_op_mulw_AX_T0();

                break;

            default:

            case OT_LONG:

                gen_op_mull_EAX_T0();

                break;

            }

            s->cc_op = CC_OP_MUL;

            break;

        case 5:  

            switch(ot) {

            case OT_BYTE:

                gen_op_imulb_AL_T0();

                break;

            case OT_WORD:

                gen_op_imulw_AX_T0();

                break;

            default:

            case OT_LONG:

                gen_op_imull_EAX_T0();

                break;

            }

            s->cc_op = CC_OP_MUL;

            break;

        case 6:  

            switch(ot) {

            case OT_BYTE:

                gen_op_divb_AL_T0();

                break;

            case OT_WORD:

                gen_op_divw_AX_T0();

                break;

            default:

            case OT_LONG:

                gen_op_divl_EAX_T0();

                break;

            }

            break;

        case 7:  

            switch(ot) {

            case OT_BYTE:

                gen_op_idivb_AL_T0();

                break;

            case OT_WORD:

                gen_op_idivw_AX_T0();

                break;

            default:

            case OT_LONG:

                gen_op_idivl_EAX_T0();

                break;

            }

            break;

        default:

            goto illegal_op;

        }

        break;



    case 0xfe:  

    case 0xff:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;



        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        op = (modrm >> 3) & 7;

        if (op >= 2 && b == 0xfe) {

            goto illegal_op;

        }

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            if (op != 3 && op != 5)

                gen_op_ld_T0_A0[ot]();

        } else {

            gen_op_mov_TN_reg[ot][0][rm]();

        }



        switch(op) {

        case 0:  

            gen_inc(s, ot, OR_TMP0, 1);

            if (mod != 3)

                gen_op_st_T0_A0[ot]();

            else

                gen_op_mov_reg_T0[ot][rm]();

            break;

        case 1:  

            gen_inc(s, ot, OR_TMP0, -1);

            if (mod != 3)

                gen_op_st_T0_A0[ot]();

            else

                gen_op_mov_reg_T0[ot][rm]();

            break;

        case 2:  

             

            if (s->dflag == 0)

                gen_op_andl_T0_ffff();

            gen_op_jmp_T0();

            next_eip = s->pc - s->cs_base;

            gen_op_movl_T0_im(next_eip);

            gen_push_T0(s);

            s->is_jmp = 1;

            break;

        case 3:  

             

            gen_op_movl_T0_seg(R_CS);

            gen_push_T0(s);

            next_eip = s->pc - s->cs_base;

            gen_op_movl_T0_im(next_eip);

            gen_push_T0(s);



            gen_op_ld_T1_A0[ot]();

            gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));

            gen_op_lduw_T0_A0();

            gen_movl_seg_T0(s, R_CS);

            gen_op_movl_T0_T1();

            gen_op_jmp_T0();

            s->is_jmp = 1;

            break;

        case 4:  

            if (s->dflag == 0)

                gen_op_andl_T0_ffff();

            gen_op_jmp_T0();

            s->is_jmp = 1;

            break;

        case 5:  

            gen_op_ld_T1_A0[ot]();

            gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));

            gen_op_lduw_T0_A0();

            gen_movl_seg_T0(s, R_CS);

            gen_op_movl_T0_T1();

            gen_op_jmp_T0();

            s->is_jmp = 1;

            break;

        case 6:  

            gen_push_T0(s);

            break;

        default:

            goto illegal_op;

        }

        break;



    case 0x84:  

    case 0x85: 

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;



        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        reg = (modrm >> 3) & 7;

        

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

        gen_op_mov_TN_reg[ot][1][reg + OR_EAX]();

        gen_op_testl_T0_T1_cc();

        s->cc_op = CC_OP_LOGICB + ot;

        break;

        

    case 0xa8:  

    case 0xa9:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        val = insn_get(s, ot);



        gen_op_mov_TN_reg[ot][0][OR_EAX]();

        gen_op_movl_T1_im(val);

        gen_op_testl_T0_T1_cc();

        s->cc_op = CC_OP_LOGICB + ot;

        break;

        

    case 0x98:  

        if (dflag)

            gen_op_movswl_EAX_AX();

        else

            gen_op_movsbw_AX_AL();

        break;

    case 0x99:  

        if (dflag)

            gen_op_movslq_EDX_EAX();

        else

            gen_op_movswl_DX_AX();

        break;

    case 0x1af:  

    case 0x69:  

    case 0x6b:

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = ((modrm >> 3) & 7) + OR_EAX;

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

        if (b == 0x69) {

            val = insn_get(s, ot);

            gen_op_movl_T1_im(val);

        } else if (b == 0x6b) {

            val = insn_get(s, OT_BYTE);

            gen_op_movl_T1_im(val);

        } else {

            gen_op_mov_TN_reg[ot][1][reg]();

        }



        if (ot == OT_LONG) {

            gen_op_imull_T0_T1();

        } else {

            gen_op_imulw_T0_T1();

        }

        gen_op_mov_reg_T0[ot][reg]();

        s->cc_op = CC_OP_MUL;

        break;

    case 0x1c0:

    case 0x1c1:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        if (mod == 3) {

            rm = modrm & 7;

            gen_op_mov_TN_reg[ot][0][reg]();

            gen_op_mov_TN_reg[ot][1][rm]();

            gen_op_addl_T0_T1_cc();

            gen_op_mov_reg_T0[ot][rm]();

            gen_op_mov_reg_T1[ot][reg]();

        } else {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_mov_TN_reg[ot][0][reg]();

            gen_op_ld_T1_A0[ot]();

            gen_op_addl_T0_T1_cc();

            gen_op_st_T0_A0[ot]();

            gen_op_mov_reg_T1[ot][reg]();

        }

        s->cc_op = CC_OP_ADDB + ot;

        break;

    case 0x1b0:

    case 0x1b1:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        gen_op_mov_TN_reg[ot][1][reg]();

        if (mod == 3) {

            rm = modrm & 7;

            gen_op_mov_TN_reg[ot][0][rm]();

            gen_op_cmpxchg_T0_T1_EAX_cc[ot]();

            gen_op_mov_reg_T0[ot][rm]();

        } else {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_ld_T0_A0[ot]();

            gen_op_cmpxchg_T0_T1_EAX_cc[ot]();

            gen_op_st_T0_A0[ot]();

        }

        s->cc_op = CC_OP_SUBB + ot;

        break;

        

         

         

    case 0x50 ... 0x57:  

        gen_op_mov_TN_reg[OT_LONG][0][b & 7]();

        gen_push_T0(s);

        break;

    case 0x58 ... 0x5f:  

        ot = dflag ? OT_LONG : OT_WORD;

        gen_pop_T0(s);

        gen_op_mov_reg_T0[ot][b & 7]();

        gen_pop_update(s);

        break;

    case 0x60:  

        gen_pusha(s);

        break;

    case 0x61:  

        gen_popa(s);

        break;

    case 0x68:  

    case 0x6a:

        ot = dflag ? OT_LONG : OT_WORD;

        if (b == 0x68)

            val = insn_get(s, ot);

        else

            val = (int8_t)insn_get(s, OT_BYTE);

        gen_op_movl_T0_im(val);

        gen_push_T0(s);

        break;

    case 0x8f:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        gen_pop_T0(s);

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 1);

        gen_pop_update(s);

        break;

    case 0xc8:  

        {

            int level;

            val = lduw(s->pc);

            s->pc += 2;

            level = ldub(s->pc++);

            gen_enter(s, val, level);

        }

        break;

    case 0xc9:  

         

        if (s->ss32) {

            gen_op_mov_TN_reg[OT_LONG][0][R_EBP]();

            gen_op_mov_reg_T0[OT_LONG][R_ESP]();

        } else {

            gen_op_mov_TN_reg[OT_WORD][0][R_EBP]();

            gen_op_mov_reg_T0[OT_WORD][R_ESP]();

        }

        gen_pop_T0(s);

        ot = dflag ? OT_LONG : OT_WORD;

        gen_op_mov_reg_T0[ot][R_EBP]();

        gen_pop_update(s);

        break;

    case 0x06:  

    case 0x0e:  

    case 0x16:  

    case 0x1e:  

        gen_op_movl_T0_seg(b >> 3);

        gen_push_T0(s);

        break;

    case 0x1a0:  

    case 0x1a8:  

        gen_op_movl_T0_seg(((b >> 3) & 7) + R_FS);

        gen_push_T0(s);

        break;

    case 0x07:  

    case 0x17:  

    case 0x1f:  

        gen_pop_T0(s);

        gen_movl_seg_T0(s, b >> 3);

        gen_pop_update(s);

        break;

    case 0x1a1:  

    case 0x1a9:  

        gen_pop_T0(s);

        gen_movl_seg_T0(s, ((b >> 3) & 7) + R_FS);

        gen_pop_update(s);

        break;



         

         

    case 0x88:

    case 0x89:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        

         

        gen_ldst_modrm(s, modrm, ot, OR_EAX + reg, 1);

        break;

    case 0xc6:

    case 0xc7:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        if (mod != 3)

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

        val = insn_get(s, ot);

        gen_op_movl_T0_im(val);

        if (mod != 3)

            gen_op_st_T0_A0[ot]();

        else

            gen_op_mov_reg_T0[ot][modrm & 7]();

        break;

    case 0x8a:

    case 0x8b:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

        gen_op_mov_reg_T0[ot][reg]();

        break;

    case 0x8e:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

        if (reg >= 6 || reg == R_CS)

            goto illegal_op;

        gen_movl_seg_T0(s, reg);

        break;

    case 0x8c:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        if (reg >= 6)

            goto illegal_op;

        gen_op_movl_T0_seg(reg);

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 1);

        break;



    case 0x1b6:  

    case 0x1b7:  

    case 0x1be:  

    case 0x1bf:  

        {

            int d_ot;

             

            d_ot = dflag + OT_WORD;

             

            ot = (b & 1) + OT_BYTE;

            modrm = ldub(s->pc++);

            reg = ((modrm >> 3) & 7) + OR_EAX;

            mod = (modrm >> 6) & 3;

            rm = modrm & 7;

            

            if (mod == 3) {

                gen_op_mov_TN_reg[ot][0][rm]();

                switch(ot | (b & 8)) {

                case OT_BYTE:

                    gen_op_movzbl_T0_T0();

                    break;

                case OT_BYTE | 8:

                    gen_op_movsbl_T0_T0();

                    break;

                case OT_WORD:

                    gen_op_movzwl_T0_T0();

                    break;

                default:

                case OT_WORD | 8:

                    gen_op_movswl_T0_T0();

                    break;

                }

                gen_op_mov_reg_T0[d_ot][reg]();

            } else {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                if (b & 8) {

                    gen_op_lds_T0_A0[ot]();

                } else {

                    gen_op_ldu_T0_A0[ot]();

                }

                gen_op_mov_reg_T0[d_ot][reg]();

            }

        }

        break;



    case 0x8d:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

         

        s->prefix &= ~(PREFIX_CS | PREFIX_SS | PREFIX_DS | 

                       PREFIX_ES | PREFIX_FS | PREFIX_GS);

        val = s->addseg;

        s->addseg = 0;

        gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

        s->addseg = val;

        gen_op_mov_reg_A0[ot - OT_WORD][reg]();

        break;

        

    case 0xa0:  

    case 0xa1:

    case 0xa2:  

    case 0xa3:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (s->aflag)

            offset_addr = insn_get(s, OT_LONG);

        else

            offset_addr = insn_get(s, OT_WORD);

        gen_op_movl_A0_im(offset_addr);

         

         

        {

            int override, must_add_seg;

            override = R_DS;

            must_add_seg = s->addseg;

            if (s->prefix & (PREFIX_CS | PREFIX_SS | PREFIX_DS | 

                             PREFIX_ES | PREFIX_FS | PREFIX_GS)) {

                if (s->prefix & PREFIX_ES)

                    override = R_ES;

                else if (s->prefix & PREFIX_CS)

                    override = R_CS;

                else if (s->prefix & PREFIX_SS)

                    override = R_SS;

                else if (s->prefix & PREFIX_DS)

                    override = R_DS;

                else if (s->prefix & PREFIX_FS)

                    override = R_FS;

                else

                    override = R_GS;

                must_add_seg = 1;

            }

            if (must_add_seg) {

                gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));

            }

        }

        if ((b & 2) == 0) {

            gen_op_ld_T0_A0[ot]();

            gen_op_mov_reg_T0[ot][R_EAX]();

        } else {

            gen_op_mov_TN_reg[ot][0][R_EAX]();

            gen_op_st_T0_A0[ot]();

        }

        break;

    case 0xd7:  

         

        gen_op_movl_A0_reg[R_EBX]();

        gen_op_addl_A0_AL();

        if (s->aflag == 0)

            gen_op_andl_A0_ffff();

         

        {

            int override, must_add_seg;

            override = R_DS;

            must_add_seg = s->addseg;

            if (s->prefix & (PREFIX_CS | PREFIX_SS | PREFIX_DS | 

                             PREFIX_ES | PREFIX_FS | PREFIX_GS)) {

                if (s->prefix & PREFIX_ES)

                    override = R_ES;

                else if (s->prefix & PREFIX_CS)

                    override = R_CS;

                else if (s->prefix & PREFIX_SS)

                    override = R_SS;

                else if (s->prefix & PREFIX_DS)

                    override = R_DS;

                else if (s->prefix & PREFIX_FS)

                    override = R_FS;

                else

                    override = R_GS;

                must_add_seg = 1;

            }

            if (must_add_seg) {

                gen_op_addl_A0_seg(offsetof(CPUX86State,seg_cache[override].base));

            }

        }

        gen_op_ldub_T0_A0();

        gen_op_mov_reg_T0[OT_BYTE][R_EAX]();

        break;

    case 0xb0 ... 0xb7:  

        val = insn_get(s, OT_BYTE);

        gen_op_movl_T0_im(val);

        gen_op_mov_reg_T0[OT_BYTE][b & 7]();

        break;

    case 0xb8 ... 0xbf:  

        ot = dflag ? OT_LONG : OT_WORD;

        val = insn_get(s, ot);

        reg = OR_EAX + (b & 7);

        gen_op_movl_T0_im(val);

        gen_op_mov_reg_T0[ot][reg]();

        break;



    case 0x91 ... 0x97:  

        ot = dflag ? OT_LONG : OT_WORD;

        reg = b & 7;

        rm = R_EAX;

        goto do_xchg_reg;

    case 0x86:

    case 0x87:  

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        if (mod == 3) {

            rm = modrm & 7;

        do_xchg_reg:

            gen_op_mov_TN_reg[ot][0][reg]();

            gen_op_mov_TN_reg[ot][1][rm]();

            gen_op_mov_reg_T0[ot][rm]();

            gen_op_mov_reg_T1[ot][reg]();

        } else {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_mov_TN_reg[ot][0][reg]();

             

            if (!(prefixes & PREFIX_LOCK))

                gen_op_lock();

            gen_op_ld_T1_A0[ot]();

            gen_op_st_T0_A0[ot]();

            if (!(prefixes & PREFIX_LOCK))

                gen_op_unlock();

            gen_op_mov_reg_T1[ot][reg]();

        }

        break;

    case 0xc4:  

        op = R_ES;

        goto do_lxx;

    case 0xc5:  

        op = R_DS;

        goto do_lxx;

    case 0x1b2:  

        op = R_SS;

        goto do_lxx;

    case 0x1b4:  

        op = R_FS;

        goto do_lxx;

    case 0x1b5:  

        op = R_GS;

    do_lxx:

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        if (mod == 3)

            goto illegal_op;

        gen_op_ld_T1_A0[ot]();

        gen_op_addl_A0_im(1 << (ot - OT_WORD + 1));

         

        gen_op_lduw_T0_A0();

        gen_movl_seg_T0(s, op);

         

        gen_op_mov_reg_T1[ot][reg]();

        break;

        

         

         

    case 0xc0:

    case 0xc1:

         

        shift = 2;

    grp2:

        {

            if ((b & 1) == 0)

                ot = OT_BYTE;

            else

                ot = dflag ? OT_LONG : OT_WORD;

            

            modrm = ldub(s->pc++);

            mod = (modrm >> 6) & 3;

            rm = modrm & 7;

            op = (modrm >> 3) & 7;

            

            if (mod != 3) {

                gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

                gen_op_ld_T0_A0[ot]();

                opreg = OR_TMP0;

            } else {

                opreg = rm + OR_EAX;

            }



             

            if (shift == 0) {

                gen_shift(s, op, ot, opreg, OR_ECX);

            } else {

                if (shift == 2) {

                    shift = ldub(s->pc++);

                }

                gen_shifti(s, op, ot, opreg, shift);

            }



            if (mod != 3) {

                gen_op_st_T0_A0[ot]();

            }

        }

        break;

    case 0xd0:

    case 0xd1:

         

        shift = 1;

        goto grp2;

    case 0xd2:

    case 0xd3:

         

        shift = 0;

        goto grp2;



    case 0x1a4:  

        op = 0;

        shift = 1;

        goto do_shiftd;

    case 0x1a5:  

        op = 0;

        shift = 0;

        goto do_shiftd;

    case 0x1ac:  

        op = 1;

        shift = 1;

        goto do_shiftd;

    case 0x1ad:  

        op = 1;

        shift = 0;

    do_shiftd:

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        reg = (modrm >> 3) & 7;

        

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_ld_T0_A0[ot]();

        } else {

            gen_op_mov_TN_reg[ot][0][rm]();

        }

        gen_op_mov_TN_reg[ot][1][reg]();

        

        if (shift) {

            val = ldub(s->pc++);

            val &= 0x1f;

            if (val) {

                gen_op_shiftd_T0_T1_im_cc[ot - OT_WORD][op](val);

                if (op == 0 && ot != OT_WORD)

                    s->cc_op = CC_OP_SHLB + ot;

                else

                    s->cc_op = CC_OP_SARB + ot;

            }

        } else {

            if (s->cc_op != CC_OP_DYNAMIC)

                gen_op_set_cc_op(s->cc_op);

            gen_op_shiftd_T0_T1_ECX_cc[ot - OT_WORD][op]();

            s->cc_op = CC_OP_DYNAMIC;  

        }

        if (mod != 3) {

            gen_op_st_T0_A0[ot]();

        } else {

            gen_op_mov_reg_T0[ot][rm]();

        }

        break;



         

         

    case 0xd8 ... 0xdf: 

        modrm = ldub(s->pc++);

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        op = ((b & 7) << 3) | ((modrm >> 3) & 7);

        

        if (mod != 3) {

             

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            switch(op) {

            case 0x00 ... 0x07:  

            case 0x10 ... 0x17:  

            case 0x20 ... 0x27:  

            case 0x30 ... 0x37:  

                {

                    int op1;

                    op1 = op & 7;



                    switch(op >> 4) {

                    case 0:

                        gen_op_flds_FT0_A0();

                        break;

                    case 1:

                        gen_op_fildl_FT0_A0();

                        break;

                    case 2:

                        gen_op_fldl_FT0_A0();

                        break;

                    case 3:

                    default:

                        gen_op_fild_FT0_A0();

                        break;

                    }

                    

                    gen_op_fp_arith_ST0_FT0[op1]();

                    if (op1 == 3) {

                         

                        gen_op_fpop();

                    }

                }

                break;

            case 0x08:  

            case 0x0a:  

            case 0x0b:  

            case 0x18:  

            case 0x1a:  

            case 0x1b:  

            case 0x28:  

            case 0x2a:  

            case 0x2b:  

            case 0x38:  

            case 0x3a:  

            case 0x3b:  

                

                switch(op & 7) {

                case 0:

                    gen_op_fpush();

                    switch(op >> 4) {

                    case 0:

                        gen_op_flds_ST0_A0();

                        break;

                    case 1:

                        gen_op_fildl_ST0_A0();

                        break;

                    case 2:

                        gen_op_fldl_ST0_A0();

                        break;

                    case 3:

                    default:

                        gen_op_fild_ST0_A0();

                        break;

                    }

                    break;

                default:

                    switch(op >> 4) {

                    case 0:

                        gen_op_fsts_ST0_A0();

                        break;

                    case 1:

                        gen_op_fistl_ST0_A0();

                        break;

                    case 2:

                        gen_op_fstl_ST0_A0();

                        break;

                    case 3:

                    default:

                        gen_op_fist_ST0_A0();

                        break;

                    }

                    if ((op & 7) == 3)

                        gen_op_fpop();

                    break;

                }

                break;

            case 0x0d:  

                gen_op_fldcw_A0();

                break;

            case 0x0f:  

                gen_op_fnstcw_A0();

                break;

            case 0x1d:  

                gen_op_fpush();

                gen_op_fldt_ST0_A0();

                break;

            case 0x1f:  

                gen_op_fstt_ST0_A0();

                gen_op_fpop();

                break;

            case 0x2f:  

                gen_op_fnstsw_A0();

                break;

            case 0x3c:  

                gen_op_fpush();

                gen_op_fbld_ST0_A0();

                break;

            case 0x3e:  

                gen_op_fbst_ST0_A0();

                gen_op_fpop();

                break;

            case 0x3d:  

                gen_op_fpush();

                gen_op_fildll_ST0_A0();

                break;

            case 0x3f:  

                gen_op_fistll_ST0_A0();

                gen_op_fpop();

                break;

            default:

                goto illegal_op;

            }

        } else {

             

            opreg = rm;



            switch(op) {

            case 0x08:  

                gen_op_fpush();

                gen_op_fmov_ST0_STN((opreg + 1) & 7);

                break;

            case 0x09:  

                gen_op_fxchg_ST0_STN(opreg);

                break;

            case 0x0a:  

                switch(rm) {

                case 0:  

                    break;

                default:

                    goto illegal_op;

                }

                break;

            case 0x0c:  

                switch(rm) {

                case 0:  

                    gen_op_fchs_ST0();

                    break;

                case 1:  

                    gen_op_fabs_ST0();

                    break;

                case 4:  

                    gen_op_fldz_FT0();

                    gen_op_fcom_ST0_FT0();

                    break;

                case 5:  

                    gen_op_fxam_ST0();

                    break;

                default:

                    goto illegal_op;

                }

                break;

            case 0x0d:  

                {

                    switch(rm) {

                    case 0:

                        gen_op_fpush();

                        gen_op_fld1_ST0();

                        break;

                    case 1:

                        gen_op_fpush();

                        gen_op_fldl2t_ST0();

                        break;

                    case 2:

                        gen_op_fpush();

                        gen_op_fldl2e_ST0();

                        break;

                    case 3:

                        gen_op_fpush();

                        gen_op_fldpi_ST0();

                        break;

                    case 4:

                        gen_op_fpush();

                        gen_op_fldlg2_ST0();

                        break;

                    case 5:

                        gen_op_fpush();

                        gen_op_fldln2_ST0();

                        break;

                    case 6:

                        gen_op_fpush();

                        gen_op_fldz_ST0();

                        break;

                    default:

                        goto illegal_op;

                    }

                }

                break;

            case 0x0e:  

                switch(rm) {

                case 0:  

                    gen_op_f2xm1();

                    break;

                case 1:  

                    gen_op_fyl2x();

                    break;

                case 2:  

                    gen_op_fptan();

                    break;

                case 3:  

                    gen_op_fpatan();

                    break;

                case 4:  

                    gen_op_fxtract();

                    break;

                case 5:  

                    gen_op_fprem1();

                    break;

                case 6:  

                    gen_op_fdecstp();

                    break;

                default:

                case 7:  

                    gen_op_fincstp();

                    break;

                }

                break;

            case 0x0f:  

                switch(rm) {

                case 0:  

                    gen_op_fprem();

                    break;

                case 1:  

                    gen_op_fyl2xp1();

                    break;

                case 2:  

                    gen_op_fsqrt();

                    break;

                case 3:  

                    gen_op_fsincos();

                    break;

                case 5:  

                    gen_op_fscale();

                    break;

                case 4:  

                    gen_op_frndint();

                    break;

                case 6:  

                    gen_op_fsin();

                    break;

                default:

                case 7:  

                    gen_op_fcos();

                    break;

                }

                break;

            case 0x00: case 0x01: case 0x04 ... 0x07:  

            case 0x20: case 0x21: case 0x24 ... 0x27:  

            case 0x30: case 0x31: case 0x34 ... 0x37:  

                {

                    int op1;

                    

                    op1 = op & 7;

                    if (op >= 0x20) {

                        gen_op_fp_arith_STN_ST0[op1](opreg);

                        if (op >= 0x30)

                            gen_op_fpop();

                    } else {

                        gen_op_fmov_FT0_STN(opreg);

                        gen_op_fp_arith_ST0_FT0[op1]();

                    }

                }

                break;

            case 0x02:  

                gen_op_fmov_FT0_STN(opreg);

                gen_op_fcom_ST0_FT0();

                break;

            case 0x03:  

                gen_op_fmov_FT0_STN(opreg);

                gen_op_fcom_ST0_FT0();

                gen_op_fpop();

                break;

            case 0x15:  

                switch(rm) {

                case 1:  

                    gen_op_fmov_FT0_STN(1);

                    gen_op_fucom_ST0_FT0();

                    gen_op_fpop();

                    gen_op_fpop();

                    break;

                default:

                    goto illegal_op;

                }

                break;

            case 0x1c:

                switch(rm) {

                case 2:  

                    gen_op_fclex();

                    break;

                case 3:  

                    gen_op_fninit();

                    break;

                default:

                    goto illegal_op;

                }

                break;

            case 0x2a:  

                gen_op_fmov_STN_ST0(opreg);

                break;

            case 0x2b:  

                gen_op_fmov_STN_ST0(opreg);

                gen_op_fpop();

                break;

            case 0x2c:  

                gen_op_fmov_FT0_STN(opreg);

                gen_op_fucom_ST0_FT0();

                break;

            case 0x2d:  

                gen_op_fmov_FT0_STN(opreg);

                gen_op_fucom_ST0_FT0();

                gen_op_fpop();

                break;

            case 0x33:  

                switch(rm) {

                case 1:  

                    gen_op_fmov_FT0_STN(1);

                    gen_op_fcom_ST0_FT0();

                    gen_op_fpop();

                    gen_op_fpop();

                    break;

                default:

                    goto illegal_op;

                }

                break;

            case 0x3c:  

                switch(rm) {

                case 0:

                    gen_op_fnstsw_EAX();

                    break;

                default:

                    goto illegal_op;

                }

                break;

            default:

                goto illegal_op;

            }

        }

        break;

         

         

    case 0xa4:  

    case 0xa5:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {

            gen_op_movs[3 + ot]();

        } else {

            gen_op_movs[ot]();

        }

        break;

        

    case 0xaa:  

    case 0xab:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {

            gen_op_stos[3 + ot]();

        } else {

            gen_op_stos[ot]();

        }

        break;

    case 0xac:  

    case 0xad:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {

            gen_op_lods[3 + ot]();

        } else {

            gen_op_lods[ot]();

        }

        break;

    case 0xae:  

    case 0xaf:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPNZ) {

            if (s->cc_op != CC_OP_DYNAMIC)

                gen_op_set_cc_op(s->cc_op);

            gen_op_scas[6 + ot]();

            s->cc_op = CC_OP_DYNAMIC;  

        } else if (prefixes & PREFIX_REPZ) {

            if (s->cc_op != CC_OP_DYNAMIC)

                gen_op_set_cc_op(s->cc_op);

            gen_op_scas[3 + ot]();

            s->cc_op = CC_OP_DYNAMIC;  

        } else {

            gen_op_scas[ot]();

            s->cc_op = CC_OP_SUBB + ot;

        }

        break;



    case 0xa6:  

    case 0xa7:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPNZ) {

            if (s->cc_op != CC_OP_DYNAMIC)

                gen_op_set_cc_op(s->cc_op);

            gen_op_cmps[6 + ot]();

            s->cc_op = CC_OP_DYNAMIC;  

        } else if (prefixes & PREFIX_REPZ) {

            if (s->cc_op != CC_OP_DYNAMIC)

                gen_op_set_cc_op(s->cc_op);

            gen_op_cmps[3 + ot]();

            s->cc_op = CC_OP_DYNAMIC;  

        } else {

            gen_op_cmps[ot]();

            s->cc_op = CC_OP_SUBB + ot;

        }

        break;

        

         

         

    case 0x6c:  

    case 0x6d:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {

            gen_op_ins[3 + ot]();

        } else {

            gen_op_ins[ot]();

        }

        break;

    case 0x6e:  

    case 0x6f:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        if (prefixes & PREFIX_REPZ) {

            gen_op_outs[3 + ot]();

        } else {

            gen_op_outs[ot]();

        }

        break;

    case 0xe4:

    case 0xe5:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        val = ldub(s->pc++);

        gen_op_movl_T0_im(val);

        gen_op_in[ot]();

        gen_op_mov_reg_T1[ot][R_EAX]();

        break;

    case 0xe6:

    case 0xe7:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        val = ldub(s->pc++);

        gen_op_movl_T0_im(val);

        gen_op_mov_TN_reg[ot][1][R_EAX]();

        gen_op_out[ot]();

        break;

    case 0xec:

    case 0xed:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        gen_op_mov_TN_reg[OT_WORD][0][R_EDX]();

        gen_op_in[ot]();

        gen_op_mov_reg_T1[ot][R_EAX]();

        break;

    case 0xee:

    case 0xef:

        if ((b & 1) == 0)

            ot = OT_BYTE;

        else

            ot = dflag ? OT_LONG : OT_WORD;

        gen_op_mov_TN_reg[OT_WORD][0][R_EDX]();

        gen_op_mov_TN_reg[ot][1][R_EAX]();

        gen_op_out[ot]();

        break;



         

         

    case 0xc2:  

        val = ldsw(s->pc);

        s->pc += 2;

        gen_pop_T0(s);

        if (s->ss32)

            gen_op_addl_ESP_im(val + (2 << s->dflag));

        else

            gen_op_addw_ESP_im(val + (2 << s->dflag));

        if (s->dflag == 0)

            gen_op_andl_T0_ffff();

        gen_op_jmp_T0();

        s->is_jmp = 1;

        break;

    case 0xc3:  

        gen_pop_T0(s);

        gen_pop_update(s);

        if (s->dflag == 0)

            gen_op_andl_T0_ffff();

        gen_op_jmp_T0();

        s->is_jmp = 1;

        break;

    case 0xca:  

        val = ldsw(s->pc);

        s->pc += 2;

         

        gen_pop_T0(s);

        if (s->dflag == 0)

            gen_op_andl_T0_ffff();

        gen_op_jmp_T0();

        gen_pop_update(s);

         

        gen_pop_T0(s);

        gen_movl_seg_T0(s, R_CS);

        gen_pop_update(s);

         

        if (s->ss32)

            gen_op_addl_ESP_im(val + (2 << s->dflag));

        else

            gen_op_addw_ESP_im(val + (2 << s->dflag));

        s->is_jmp = 1;

        break;

    case 0xcb:  

         

        gen_pop_T0(s);

        if (s->dflag == 0)

            gen_op_andl_T0_ffff();

        gen_op_jmp_T0();

        gen_pop_update(s);

         

        gen_pop_T0(s);

        gen_movl_seg_T0(s, R_CS);

        gen_pop_update(s);

        s->is_jmp = 1;

        break;

    case 0xe8:  

        {

            unsigned int next_eip;

            ot = dflag ? OT_LONG : OT_WORD;

            val = insn_get(s, ot);

            next_eip = s->pc - s->cs_base;

            val += next_eip;

            if (s->dflag == 0)

                val &= 0xffff;

            gen_op_movl_T0_im(next_eip);

            gen_push_T0(s);

            gen_op_jmp_im(val);

            s->is_jmp = 1;

        }

        break;

    case 0x9a:  

        {

            unsigned int selector, offset;



            ot = dflag ? OT_LONG : OT_WORD;

            offset = insn_get(s, ot);

            selector = insn_get(s, OT_WORD);

            

             

            gen_op_movl_T0_seg(R_CS);

            gen_push_T0(s);

            next_eip = s->pc - s->cs_base;

            gen_op_movl_T0_im(next_eip);

            gen_push_T0(s);



             

            gen_op_movl_T0_im(selector);

            gen_movl_seg_T0(s, R_CS);

            gen_op_jmp_im((unsigned long)offset);

            s->is_jmp = 1;

        }

        break;

    case 0xe9:  

        ot = dflag ? OT_LONG : OT_WORD;

        val = insn_get(s, ot);

        val += s->pc - s->cs_base;

        if (s->dflag == 0)

            val = val & 0xffff;

        gen_op_jmp_im(val);

        s->is_jmp = 1;

        break;

    case 0xea:  

        {

            unsigned int selector, offset;



            ot = dflag ? OT_LONG : OT_WORD;

            offset = insn_get(s, ot);

            selector = insn_get(s, OT_WORD);

            

             

            gen_op_movl_T0_im(selector);

            gen_movl_seg_T0(s, R_CS);

            gen_op_jmp_im((unsigned long)offset);

            s->is_jmp = 1;

        }

        break;

    case 0xeb:  

        val = (int8_t)insn_get(s, OT_BYTE);

        val += s->pc - s->cs_base;

        if (s->dflag == 0)

            val = val & 0xffff;

        gen_op_jmp_im(val);

        s->is_jmp = 1;

        break;

    case 0x70 ... 0x7f:  

        val = (int8_t)insn_get(s, OT_BYTE);

        goto do_jcc;

    case 0x180 ... 0x18f:  

        if (dflag) {

            val = insn_get(s, OT_LONG);

        } else {

            val = (int16_t)insn_get(s, OT_WORD); 

        }

    do_jcc:

        next_eip = s->pc - s->cs_base;

        val += next_eip;

        if (s->dflag == 0)

            val &= 0xffff;

        gen_jcc(s, b, val, next_eip);

        s->is_jmp = 1;

        break;



    case 0x190 ... 0x19f:  

        modrm = ldub(s->pc++);

        gen_setcc(s, b);

        gen_ldst_modrm(s, modrm, OT_BYTE, OR_TMP0, 1);

        break;

    case 0x140 ... 0x14f:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        gen_setcc(s, b);

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_ld_T1_A0[ot]();

        } else {

            rm = modrm & 7;

            gen_op_mov_TN_reg[ot][1][rm]();

        }

        gen_op_cmov_reg_T1_T0[ot - OT_WORD][reg]();

        break;

        

         

         

    case 0x9c:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_movl_T0_eflags();

        gen_push_T0(s);

        break;

    case 0x9d:  

        gen_pop_T0(s);

        gen_op_movl_eflags_T0();

        gen_pop_update(s);

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0x9e:  

        gen_op_mov_TN_reg[OT_BYTE][0][R_AH]();

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_movb_eflags_T0();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0x9f:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_movl_T0_eflags();

        gen_op_mov_reg_T0[OT_BYTE][R_AH]();

        break;

    case 0xf5:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_cmc();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0xf8:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_clc();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0xf9:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_stc();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0xfc:  

        gen_op_cld();

        break;

    case 0xfd:  

        gen_op_std();

        break;



         

         

    case 0x1ba:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        op = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

            gen_op_ld_T0_A0[ot]();

        } else {

            gen_op_mov_TN_reg[ot][0][rm]();

        }

         

        val = ldub(s->pc++);

        gen_op_movl_T1_im(val);

        if (op < 4)

            goto illegal_op;

        op -= 4;

        gen_op_btx_T0_T1_cc[ot - OT_WORD][op]();

        s->cc_op = CC_OP_SARB + ot;

        if (op != 0) {

            if (mod != 3)

                gen_op_st_T0_A0[ot]();

            else

                gen_op_mov_reg_T0[ot][rm]();

        }

        break;

    case 0x1a3:  

        op = 0;

        goto do_btx;

    case 0x1ab:  

        op = 1;

        goto do_btx;

    case 0x1b3:  

        op = 2;

        goto do_btx;

    case 0x1bb:  

        op = 3;

    do_btx:

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        mod = (modrm >> 6) & 3;

        rm = modrm & 7;

        gen_op_mov_TN_reg[OT_LONG][1][reg]();

        if (mod != 3) {

            gen_lea_modrm(s, modrm, &reg_addr, &offset_addr);

             

            if (ot == OT_WORD)

                gen_op_add_bitw_A0_T1();

            else

                gen_op_add_bitl_A0_T1();

            gen_op_ld_T0_A0[ot]();

        } else {

            gen_op_mov_TN_reg[ot][0][rm]();

        }

        gen_op_btx_T0_T1_cc[ot - OT_WORD][op]();

        s->cc_op = CC_OP_SARB + ot;

        if (op != 0) {

            if (mod != 3)

                gen_op_st_T0_A0[ot]();

            else

                gen_op_mov_reg_T0[ot][rm]();

        }

        break;

    case 0x1bc:  

    case 0x1bd:  

        ot = dflag ? OT_LONG : OT_WORD;

        modrm = ldub(s->pc++);

        reg = (modrm >> 3) & 7;

        gen_ldst_modrm(s, modrm, ot, OR_TMP0, 0);

        gen_op_bsx_T0_cc[ot - OT_WORD][b & 1]();

         

        gen_op_mov_reg_T0[ot][reg]();

        s->cc_op = CC_OP_LOGICB + ot;

        break;

         

         

    case 0x27:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_daa();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0x2f:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_das();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0x37:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_aaa();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0x3f:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_aas();

        s->cc_op = CC_OP_EFLAGS;

        break;

    case 0xd4:  

        val = ldub(s->pc++);

        gen_op_aam(val);

        s->cc_op = CC_OP_LOGICB;

        break;

    case 0xd5:  

        val = ldub(s->pc++);

        gen_op_aad(val);

        s->cc_op = CC_OP_LOGICB;

        break;

         

         

    case 0x90:  

        break;

    case 0xcc:  

        gen_op_int3((long)pc_start);

        s->is_jmp = 1;

        break;

    case 0xcd:  

        val = ldub(s->pc++);

         

        gen_op_int_im((long)pc_start);

        s->is_jmp = 1;

        break;

    case 0xce:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_into((long)pc_start, (long)s->pc);

        s->is_jmp = 1;

        break;

    case 0x1c8 ... 0x1cf:  

        reg = b & 7;

        gen_op_mov_TN_reg[OT_LONG][0][reg]();

        gen_op_bswapl_T0();

        gen_op_mov_reg_T0[OT_LONG][reg]();

        break;

    case 0xd6:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

        gen_op_salc();

        break;

    case 0xe0:  

    case 0xe1:  

        if (s->cc_op != CC_OP_DYNAMIC)

            gen_op_set_cc_op(s->cc_op);

         

    case 0xe2:  

    case 0xe3:  

        val = (int8_t)insn_get(s, OT_BYTE);

        next_eip = s->pc - s->cs_base;

        val += next_eip;

        if (s->dflag == 0)

            val &= 0xffff;

        gen_op_loop[s->aflag][b & 3](val, next_eip);

        s->is_jmp = 1;

        break;

    case 0x131:  

        gen_op_rdtsc();

        break;


    case 0x1a2:  

        gen_insn0(OP_ASM);

        break;


    default:

        goto illegal_op;

    }

     

    if (s->prefix & PREFIX_LOCK)

        gen_op_unlock();

    return (long)s->pc;

 illegal_op:

     

    return -1;

}
