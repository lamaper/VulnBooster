static void disas_sparc_insn(DisasContext * dc)

{

    unsigned int insn, opc, rs1, rs2, rd;



    insn = ldl_code(dc->pc);

    opc = GET_FIELD(insn, 0, 1);



    rd = GET_FIELD(insn, 2, 6);

    switch (opc) {

    case 0:                      

        {

            unsigned int xop = GET_FIELD(insn, 7, 9);

            int32_t target;

            switch (xop) {


            case 0x1:            

                {

                    int cc;



                    target = GET_FIELD_SP(insn, 0, 18);

                    target = sign_extend(target, 18);

                    target <<= 2;

                    cc = GET_FIELD_SP(insn, 20, 21);

                    if (cc == 0)

                        do_branch(dc, target, insn, 0);

                    else if (cc == 2)

                        do_branch(dc, target, insn, 1);

                    else

                        goto illegal_insn;

                    goto jmp_insn;

                }

            case 0x3:            

                {

                    target = GET_FIELD_SP(insn, 0, 13) |

                        (GET_FIELD_SP(insn, 20, 21) << 14);

                    target = sign_extend(target, 16);

                    target <<= 2;

                    rs1 = GET_FIELD(insn, 13, 17);

                    gen_movl_reg_T0(rs1);

                    do_branch_reg(dc, target, insn);

                    goto jmp_insn;

                }

            case 0x5:            

                {

                    int cc = GET_FIELD_SP(insn, 20, 21);

                    if (gen_trap_ifnofpu(dc))

                        goto jmp_insn;

                    target = GET_FIELD_SP(insn, 0, 18);

                    target = sign_extend(target, 19);

                    target <<= 2;

                    do_fbranch(dc, target, insn, cc);

                    goto jmp_insn;

                }


            case 0x7:            

                {

                    goto ncp_insn;

                }


            case 0x2:            

                {

                    target = GET_FIELD(insn, 10, 31);

                    target = sign_extend(target, 22);

                    target <<= 2;

                    do_branch(dc, target, insn, 0);

                    goto jmp_insn;

                }

            case 0x6:            

                {

                    if (gen_trap_ifnofpu(dc))

                        goto jmp_insn;

                    target = GET_FIELD(insn, 10, 31);

                    target = sign_extend(target, 22);

                    target <<= 2;

                    do_fbranch(dc, target, insn, 0);

                    goto jmp_insn;

                }

            case 0x4:            



                if (rd) {  


                    uint32_t value = GET_FIELD(insn, 10, 31);

                    gen_movl_imm_T0(value << 10);

                    gen_movl_T0_reg(rd);


                }


                break;

            case 0x0:            

            default:

                goto illegal_insn;

            }

            break;

        }

        break;

    case 1:

          {

            target_long target = GET_FIELDs(insn, 2, 31) << 2;


            if (dc->pc == (uint32_t)dc->pc) {

                gen_op_movl_T0_im(dc->pc);

            } else {

                gen_op_movq_T0_im64(dc->pc >> 32, dc->pc);

            }


            gen_op_movl_T0_im(dc->pc);


            gen_movl_T0_reg(15);

            target += dc->pc;

            gen_mov_pc_npc(dc);

            dc->npc = target;

        }

        goto jmp_insn;

    case 2:                      

        {

            unsigned int xop = GET_FIELD(insn, 7, 12);

            if (xop == 0x3a) {   

                int cond;



                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {

                    rs2 = GET_FIELD(insn, 25, 31);


                    if (rs2 != 0) {


                        gen_movl_simm_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                } else {

                    rs2 = GET_FIELD(insn, 27, 31);


                    if (rs2 != 0) {


                        gen_movl_reg_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                }

                cond = GET_FIELD(insn, 3, 6);

                if (cond == 0x8) {

                    save_state(dc);

                    gen_op_trap_T0();

                } else if (cond != 0) {


                     

                    int cc = GET_FIELD_SP(insn, 11, 12);

                    flush_T2(dc);

                    save_state(dc);

                    if (cc == 0)

                        gen_cond[0][cond]();

                    else if (cc == 2)

                        gen_cond[1][cond]();

                    else

                        goto illegal_insn;


                    flush_T2(dc);

                    save_state(dc);

                    gen_cond[0][cond]();


                    gen_op_trapcc_T0();

                }

                gen_op_next_insn();

                gen_op_movl_T0_0();

                gen_op_exit_tb();

                dc->is_br = 1;

                goto jmp_insn;

            } else if (xop == 0x28) {

                rs1 = GET_FIELD(insn, 13, 17);

                switch(rs1) {

                case 0:  


                case 0x01 ... 0x0e:  

                case 0x0f:           

                case 0x10 ... 0x1f:  


                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, y));

                    gen_movl_T0_reg(rd);

                    break;


                case 0x2:  

                    gen_op_rdccr();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x3:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, asi));

                    gen_movl_T0_reg(rd);

                    break;

                case 0x4:  

                    gen_op_rdtick();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x5:  

                    if (dc->pc == (uint32_t)dc->pc) {

                        gen_op_movl_T0_im(dc->pc);

                    } else {

                        gen_op_movq_T0_im64(dc->pc >> 32, dc->pc);

                    }

                    gen_movl_T0_reg(rd);

                    break;

                case 0x6:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, fprs));

                    gen_movl_T0_reg(rd);

                    break;

                case 0xf:  

                    break;  

                case 0x13:  

                    if (gen_trap_ifnofpu(dc))

                        goto jmp_insn;

                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, gsr));

                    gen_movl_T0_reg(rd);

                    break;

                case 0x17:  

                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, tick_cmpr));

                    gen_movl_T0_reg(rd);

                    break;

                case 0x18:  

                    gen_op_rdstick();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x19:  

                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, stick_cmpr));

                    gen_movl_T0_reg(rd);

                    break;

                case 0x10:  

                case 0x11:  

                case 0x12:  

                case 0x14:  

                case 0x15:  

                case 0x16:  


                default:

                    goto illegal_insn;

                }


            } else if (xop == 0x29) {  


                if (!supervisor(dc))

                    goto priv_insn;

                gen_op_rdpsr();


                if (!hypervisor(dc))

                    goto priv_insn;

                rs1 = GET_FIELD(insn, 13, 17);

                switch (rs1) {

                case 0:  

                     

                    break;

                case 1:  

                     

                    break;

                case 3:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, hintp));

                    break;

                case 5:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, htba));

                    break;

                case 6:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, hver));

                    break;

                case 31:  

                    gen_op_movl_env_T0(offsetof(CPUSPARCState, hstick_cmpr));

                    break;

                default:

                    goto illegal_insn;

                }


                gen_movl_T0_reg(rd);

                break;

            } else if (xop == 0x2a) {  

                if (!supervisor(dc))

                    goto priv_insn;


                rs1 = GET_FIELD(insn, 13, 17);

                switch (rs1) {

                case 0:  

                    gen_op_rdtpc();

                    break;

                case 1:  

                    gen_op_rdtnpc();

                    break;

                case 2:  

                    gen_op_rdtstate();

                    break;

                case 3:  

                    gen_op_rdtt();

                    break;

                case 4:  

                    gen_op_rdtick();

                    break;

                case 5:  

                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, tbr));

                    break;

                case 6:  

                    gen_op_rdpstate();

                    break;

                case 7:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, tl));

                    break;

                case 8:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, psrpil));

                    break;

                case 9:  

                    gen_op_rdcwp();

                    break;

                case 10:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, cansave));

                    break;

                case 11:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, canrestore));

                    break;

                case 12:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, cleanwin));

                    break;

                case 13:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, otherwin));

                    break;

                case 14:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, wstate));

                    break;

                case 16:  

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, gl));

                    break;

                case 26:  

                    if (!hypervisor(dc))

                        goto priv_insn;

                    gen_op_movl_T0_env(offsetof(CPUSPARCState, ssr));

                    break;

                case 31:  

                    gen_op_movtl_T0_env(offsetof(CPUSPARCState, version));

                    break;

                case 15:  

                default:

                    goto illegal_insn;

                }


                gen_op_movl_T0_env(offsetof(CPUSPARCState, wim));


                gen_movl_T0_reg(rd);

                break;

            } else if (xop == 0x2b) {  


                gen_op_flushw();


                if (!supervisor(dc))

                    goto priv_insn;

                gen_op_movtl_T0_env(offsetof(CPUSPARCState, tbr));

                gen_movl_T0_reg(rd);


                break;


            } else if (xop == 0x34) {    

                if (gen_trap_ifnofpu(dc))

                    goto jmp_insn;

                gen_op_clear_ieee_excp_and_FTT();

                rs1 = GET_FIELD(insn, 13, 17);

                rs2 = GET_FIELD(insn, 27, 31);

                xop = GET_FIELD(insn, 18, 26);

                switch (xop) {

                    case 0x1:  

                        gen_op_load_fpr_FT0(rs2);

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x5:  

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fnegs();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x9:  

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fabss();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x29:  

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fsqrts();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x2a:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fsqrtd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x2b:  

                        goto nfpu_insn;

                    case 0x41:

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fadds();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x42:

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_faddd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x43:  

                        goto nfpu_insn;

                    case 0x45:

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fsubs();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x46:

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fsubd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x47:  

                        goto nfpu_insn;

                    case 0x49:

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fmuls();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x4a:

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fmuld();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x4b:  

                        goto nfpu_insn;

                    case 0x4d:

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fdivs();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x4e:

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fdivd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x4f:  

                        goto nfpu_insn;

                    case 0x69:

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fsmuld();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x6e:  

                        goto nfpu_insn;

                    case 0xc4:

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fitos();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0xc6:

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fdtos();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0xc7:  

                        goto nfpu_insn;

                    case 0xc8:

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fitod();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0xc9:

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fstod();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0xcb:  

                        goto nfpu_insn;

                    case 0xcc:  

                        goto nfpu_insn;

                    case 0xcd:  

                        goto nfpu_insn;

                    case 0xce:  

                        goto nfpu_insn;

                    case 0xd1:

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fstoi();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0xd2:

                        gen_op_load_fpr_DT1(rs2);

                        gen_op_fdtoi();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0xd3:  

                        goto nfpu_insn;


                    case 0x2:  

                        gen_op_load_fpr_DT0(DFPREG(rs2));

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x6:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fnegd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0xa:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fabsd();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x81:  

                        gen_op_load_fpr_FT1(rs2);

                        gen_op_fstox();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x82:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fdtox();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x84:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fxtos();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x88:  

                        gen_op_load_fpr_DT1(DFPREG(rs2));

                        gen_op_fxtod();

                        gen_op_store_DT0_fpr(DFPREG(rd));

                        break;

                    case 0x3:  

                    case 0x7:  

                    case 0xb:  

                    case 0x83:  

                    case 0x8c:  

                        goto nfpu_insn;


                    default:

                        goto illegal_insn;

                }

            } else if (xop == 0x35) {    


                int cond;


                if (gen_trap_ifnofpu(dc))

                    goto jmp_insn;

                gen_op_clear_ieee_excp_and_FTT();

                rs1 = GET_FIELD(insn, 13, 17);

                rs2 = GET_FIELD(insn, 27, 31);

                xop = GET_FIELD(insn, 18, 26);


                if ((xop & 0x11f) == 0x005) {  

                    cond = GET_FIELD_SP(insn, 14, 17);

                    gen_op_load_fpr_FT0(rd);

                    gen_op_load_fpr_FT1(rs2);

                    rs1 = GET_FIELD(insn, 13, 17);

                    gen_movl_reg_T0(rs1);

                    flush_T2(dc);

                    gen_cond_reg(cond);

                    gen_op_fmovs_cc();

                    gen_op_store_FT0_fpr(rd);

                    break;

                } else if ((xop & 0x11f) == 0x006) {  

                    cond = GET_FIELD_SP(insn, 14, 17);

                    gen_op_load_fpr_DT0(rd);

                    gen_op_load_fpr_DT1(rs2);

                    flush_T2(dc);

                    rs1 = GET_FIELD(insn, 13, 17);

                    gen_movl_reg_T0(rs1);

                    gen_cond_reg(cond);

                    gen_op_fmovs_cc();

                    gen_op_store_DT0_fpr(rd);

                    break;

                } else if ((xop & 0x11f) == 0x007) {  

                    goto nfpu_insn;

                }


                switch (xop) {


                    case 0x001:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_fcond[0][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x002:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_fcond[0][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x003:  

                        goto nfpu_insn;

                    case 0x041:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_fcond[1][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x042:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_fcond[1][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x043:  

                        goto nfpu_insn;

                    case 0x081:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_fcond[2][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x082:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_fcond[2][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x083:  

                        goto nfpu_insn;

                    case 0x0c1:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_fcond[3][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x0c2:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_fcond[3][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x0c3:  

                        goto nfpu_insn;

                    case 0x101:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_cond[0][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x102:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_cond[0][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x103:  

                        goto nfpu_insn;

                    case 0x181:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_FT0(rd);

                        gen_op_load_fpr_FT1(rs2);

                        flush_T2(dc);

                        gen_cond[1][cond]();

                        gen_op_fmovs_cc();

                        gen_op_store_FT0_fpr(rd);

                        break;

                    case 0x182:  

                        cond = GET_FIELD_SP(insn, 14, 17);

                        gen_op_load_fpr_DT0(rd);

                        gen_op_load_fpr_DT1(rs2);

                        flush_T2(dc);

                        gen_cond[1][cond]();

                        gen_op_fmovd_cc();

                        gen_op_store_DT0_fpr(rd);

                        break;

                    case 0x183:  

                        goto nfpu_insn;


                    case 0x51:  

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);


                        gen_fcmps[rd & 3]();


                        gen_op_fcmps();


                        break;

                    case 0x52:  

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));


                        gen_fcmpd[rd & 3]();


                        gen_op_fcmpd();


                        break;

                    case 0x53:  

                        goto nfpu_insn;

                    case 0x55:  

                        gen_op_load_fpr_FT0(rs1);

                        gen_op_load_fpr_FT1(rs2);


                        gen_fcmpes[rd & 3]();


                        gen_op_fcmpes();


                        break;

                    case 0x56:  

                        gen_op_load_fpr_DT0(DFPREG(rs1));

                        gen_op_load_fpr_DT1(DFPREG(rs2));


                        gen_fcmped[rd & 3]();


                        gen_op_fcmped();


                        break;

                    case 0x57:  

                        goto nfpu_insn;

                    default:

                        goto illegal_insn;

                }


            } else if (xop == 0x2) {

                 



                rs1 = GET_FIELD(insn, 13, 17);

                if (rs1 == 0) {

                     

                    if (IS_IMM) {        

                        rs2 = GET_FIELDs(insn, 19, 31);

                        gen_movl_simm_T1(rs2);

                    } else {             

                        rs2 = GET_FIELD(insn, 27, 31);

                        gen_movl_reg_T1(rs2);

                    }

                    gen_movl_T1_reg(rd);

                } else {

                    gen_movl_reg_T0(rs1);

                    if (IS_IMM) {        

                         

                        rs2 = GET_FIELDs(insn, 19, 31);

                        if (rs2 != 0) {

                            gen_movl_simm_T1(rs2);

                            gen_op_or_T1_T0();

                        }

                    } else {             

                         

                        rs2 = GET_FIELD(insn, 27, 31);

                        if (rs2 != 0) {

                            gen_movl_reg_T1(rs2);

                            gen_op_or_T1_T0();

                        }

                    }

                    gen_movl_T0_reg(rd);

                }



            } else if (xop == 0x25) {  

                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 20, 31);

                    gen_movl_simm_T1(rs2);

                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);

                    gen_movl_reg_T1(rs2);

                }

                if (insn & (1 << 12))

                    gen_op_sllx();

                else

                    gen_op_sll();

                gen_movl_T0_reg(rd);

            } else if (xop == 0x26) {  

                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 20, 31);

                    gen_movl_simm_T1(rs2);

                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);

                    gen_movl_reg_T1(rs2);

                }

                if (insn & (1 << 12))

                    gen_op_srlx();

                else

                    gen_op_srl();

                gen_movl_T0_reg(rd);

            } else if (xop == 0x27) {  

                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 20, 31);

                    gen_movl_simm_T1(rs2);

                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);

                    gen_movl_reg_T1(rs2);

                }

                if (insn & (1 << 12))

                    gen_op_srax();

                else

                    gen_op_sra();

                gen_movl_T0_reg(rd);


            } else if (xop < 0x36) {

                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 19, 31);

                    gen_movl_simm_T1(rs2);

                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);

                    gen_movl_reg_T1(rs2);

                }

                if (xop < 0x20) {

                    switch (xop & ~0x10) {

                    case 0x0:

                        if (xop & 0x10)

                            gen_op_add_T1_T0_cc();

                        else

                            gen_op_add_T1_T0();

                        break;

                    case 0x1:

                        gen_op_and_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x2:

                        gen_op_or_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x3:

                        gen_op_xor_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x4:

                        if (xop & 0x10)

                            gen_op_sub_T1_T0_cc();

                        else

                            gen_op_sub_T1_T0();

                        break;

                    case 0x5:

                        gen_op_andn_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x6:

                        gen_op_orn_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x7:

                        gen_op_xnor_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0x8:

                        if (xop & 0x10)

                            gen_op_addx_T1_T0_cc();

                        else

                            gen_op_addx_T1_T0();

                        break;


                    case 0x9:  

                        gen_op_mulx_T1_T0();

                        break;


                    case 0xa:

                        gen_op_umul_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0xb:

                        gen_op_smul_T1_T0();

                        if (xop & 0x10)

                            gen_op_logic_T0_cc();

                        break;

                    case 0xc:

                        if (xop & 0x10)

                            gen_op_subx_T1_T0_cc();

                        else

                            gen_op_subx_T1_T0();

                        break;


                    case 0xd:  

                        gen_op_udivx_T1_T0();

                        break;


                    case 0xe:

                        gen_op_udiv_T1_T0();

                        if (xop & 0x10)

                            gen_op_div_cc();

                        break;

                    case 0xf:

                        gen_op_sdiv_T1_T0();

                        if (xop & 0x10)

                            gen_op_div_cc();

                        break;

                    default:

                        goto illegal_insn;

                    }

                    gen_movl_T0_reg(rd);

                } else {

                    switch (xop) {

                    case 0x20:  

                        gen_op_tadd_T1_T0_cc();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x21:  

                        gen_op_tsub_T1_T0_cc();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x22:  

                        save_state(dc);

                        gen_op_tadd_T1_T0_ccTV();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x23:  

                        save_state(dc);

                        gen_op_tsub_T1_T0_ccTV();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x24:  

                        gen_op_mulscc_T1_T0();

                        gen_movl_T0_reg(rd);

                        break;


                    case 0x25:   

                        gen_op_sll();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x26:   

                        gen_op_srl();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x27:   

                        gen_op_sra();

                        gen_movl_T0_reg(rd);

                        break;


                    case 0x30:

                        {

                            switch(rd) {

                            case 0:  

                                gen_op_xor_T1_T0();

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, y));

                                break;


                            case 0x01 ... 0x0f:  

                            case 0x10 ... 0x1f:  

                                break;


                            case 0x2:  

                                gen_op_xor_T1_T0();

                                gen_op_wrccr();

                                break;

                            case 0x3:  

                                gen_op_xor_T1_T0();

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, asi));

                                break;

                            case 0x6:  

                                gen_op_xor_T1_T0();

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, fprs));

                                save_state(dc);

                                gen_op_next_insn();

                                gen_op_movl_T0_0();

                                gen_op_exit_tb();

                                dc->is_br = 1;

                                break;

                            case 0xf:  


                                if (supervisor(dc))

                                    gen_op_sir();


                                break;

                            case 0x13:  

                                if (gen_trap_ifnofpu(dc))

                                    goto jmp_insn;

                                gen_op_xor_T1_T0();

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, gsr));

                                break;

                            case 0x17:  


                                if (!supervisor(dc))

                                    goto illegal_insn;


                                gen_op_xor_T1_T0();

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, tick_cmpr));

                                gen_op_wrtick_cmpr();

                                break;

                            case 0x18:  


                                if (!supervisor(dc))

                                    goto illegal_insn;


                                gen_op_xor_T1_T0();

                                gen_op_wrstick();

                                break;

                            case 0x19:  


                                if (!supervisor(dc))

                                    goto illegal_insn;


                                gen_op_xor_T1_T0();

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, stick_cmpr));

                                gen_op_wrstick_cmpr();

                                break;



                            case 0x10:  

                            case 0x11:  

                            case 0x12:  

                            case 0x14:  

                            case 0x15:  

                            case 0x16:  


                            default:

                                goto illegal_insn;

                            }

                        }

                        break;


                    case 0x31:  

                        {

                            if (!supervisor(dc))

                                goto priv_insn;


                            switch (rd) {

                            case 0:

                                gen_op_saved();

                                break;

                            case 1:

                                gen_op_restored();

                                break;

                            case 2:  

                            case 3:  

                            case 4:  

                            case 5:  

                                 

                            default:

                                goto illegal_insn;

                            }


                            gen_op_xor_T1_T0();

                            gen_op_wrpsr();

                            save_state(dc);

                            gen_op_next_insn();

                            gen_op_movl_T0_0();

                            gen_op_exit_tb();

                            dc->is_br = 1;


                        }

                        break;

                    case 0x32:  

                        {

                            if (!supervisor(dc))

                                goto priv_insn;

                            gen_op_xor_T1_T0();


                            switch (rd) {

                            case 0:  

                                gen_op_wrtpc();

                                break;

                            case 1:  

                                gen_op_wrtnpc();

                                break;

                            case 2:  

                                gen_op_wrtstate();

                                break;

                            case 3:  

                                gen_op_wrtt();

                                break;

                            case 4:  

                                gen_op_wrtick();

                                break;

                            case 5:  

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, tbr));

                                break;

                            case 6:  

                                gen_op_wrpstate();

                                save_state(dc);

                                gen_op_next_insn();

                                gen_op_movl_T0_0();

                                gen_op_exit_tb();

                                dc->is_br = 1;

                                break;

                            case 7:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, tl));

                                break;

                            case 8:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, psrpil));

                                break;

                            case 9:  

                                gen_op_wrcwp();

                                break;

                            case 10:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, cansave));

                                break;

                            case 11:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, canrestore));

                                break;

                            case 12:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, cleanwin));

                                break;

                            case 13:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, otherwin));

                                break;

                            case 14:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, wstate));

                                break;

                            case 16:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, gl));

                                break;

                            case 26:  

                                if (!hypervisor(dc))

                                    goto priv_insn;

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, ssr));

                                break;

                            default:

                                goto illegal_insn;

                            }


                            gen_op_wrwim();


                        }

                        break;

                    case 0x33:  

                        {


                            if (!supervisor(dc))

                                goto priv_insn;

                            gen_op_xor_T1_T0();

                            gen_op_movtl_env_T0(offsetof(CPUSPARCState, tbr));


                            if (!hypervisor(dc))

                                goto priv_insn;

                            gen_op_xor_T1_T0();

                            switch (rd) {

                            case 0:  

                                 

                                save_state(dc);

                                gen_op_next_insn();

                                gen_op_movl_T0_0();

                                gen_op_exit_tb();

                                dc->is_br = 1;

                                break;

                            case 1:  

                                 

                                break;

                            case 3:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, hintp));

                                break;

                            case 5:  

                                gen_op_movl_env_T0(offsetof(CPUSPARCState, htba));

                                break;

                            case 31:  

                                gen_op_movtl_env_T0(offsetof(CPUSPARCState, hstick_cmpr));

                                gen_op_wrhstick_cmpr();

                                break;

                            case 6:  

                            default:

                                goto illegal_insn;

                            }


                        }

                        break;



                    case 0x2c:  

                        {

                            int cc = GET_FIELD_SP(insn, 11, 12);

                            int cond = GET_FIELD_SP(insn, 14, 17);

                            if (IS_IMM) {        

                                rs2 = GET_FIELD_SPs(insn, 0, 10);

                                gen_movl_simm_T1(rs2);

                            }

                            else {

                                rs2 = GET_FIELD_SP(insn, 0, 4);

                                gen_movl_reg_T1(rs2);

                            }

                            gen_movl_reg_T0(rd);

                            flush_T2(dc);

                            if (insn & (1 << 18)) {

                                if (cc == 0)

                                    gen_cond[0][cond]();

                                else if (cc == 2)

                                    gen_cond[1][cond]();

                                else

                                    goto illegal_insn;

                            } else {

                                gen_fcond[cc][cond]();

                            }

                            gen_op_mov_cc();

                            gen_movl_T0_reg(rd);

                            break;

                        }

                    case 0x2d:  

                        gen_op_sdivx_T1_T0();

                        gen_movl_T0_reg(rd);

                        break;

                    case 0x2e:  

                        {

                            if (IS_IMM) {        

                                rs2 = GET_FIELD_SPs(insn, 0, 12);

                                gen_movl_simm_T1(rs2);

                                 

                            }

                            else {

                                rs2 = GET_FIELD_SP(insn, 0, 4);

                                gen_movl_reg_T1(rs2);

                            }

                            gen_op_popc();

                            gen_movl_T0_reg(rd);

                        }

                    case 0x2f:  

                        {

                            int cond = GET_FIELD_SP(insn, 10, 12);

                            rs1 = GET_FIELD(insn, 13, 17);

                            flush_T2(dc);

                            gen_movl_reg_T0(rs1);

                            gen_cond_reg(cond);

                            if (IS_IMM) {        

                                rs2 = GET_FIELD_SPs(insn, 0, 9);

                                gen_movl_simm_T1(rs2);

                            }

                            else {

                                rs2 = GET_FIELD_SP(insn, 0, 4);

                                gen_movl_reg_T1(rs2);

                            }

                            gen_movl_reg_T0(rd);

                            gen_op_mov_cc();

                            gen_movl_T0_reg(rd);

                            break;

                        }


                    default:

                        goto illegal_insn;

                    }

                }

            } else if (xop == 0x36) {  


                int opf = GET_FIELD_SP(insn, 5, 13);

                rs1 = GET_FIELD(insn, 13, 17);

                rs2 = GET_FIELD(insn, 27, 31);

                if (gen_trap_ifnofpu(dc))

                    goto jmp_insn;



                switch (opf) {

                case 0x000:  

                case 0x001:  

                case 0x002:  

                case 0x003:  

                case 0x004:  

                case 0x005:  

                case 0x006:  

                case 0x007:  

                case 0x008:  

                case 0x009:  

                case 0x00a:  

                case 0x00b:  

                     

                    goto illegal_insn;

                case 0x010:  

                    gen_movl_reg_T0(rs1);

                    gen_movl_reg_T1(rs2);

                    gen_op_array8();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x012:  

                    gen_movl_reg_T0(rs1);

                    gen_movl_reg_T1(rs2);

                    gen_op_array16();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x014:  

                    gen_movl_reg_T0(rs1);

                    gen_movl_reg_T1(rs2);

                    gen_op_array32();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x018:  

                    gen_movl_reg_T0(rs1);

                    gen_movl_reg_T1(rs2);

                    gen_op_alignaddr();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x019:  

                case 0x01a:  

                     

                    goto illegal_insn;

                case 0x020:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmple16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x022:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpne16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x024:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmple32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x026:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpne32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x028:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpgt16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x02a:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpeq16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x02c:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpgt32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x02e:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fcmpeq32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x031:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmul8x16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x033:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmul8x16au();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x035:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmul8x16al();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x036:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmul8sux16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x037:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmul8ulx16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x038:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmuld8sux16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x039:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fmuld8ulx16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x03a:  

                case 0x03b:  

                case 0x03d:  

                case 0x03e:  

                     

                    goto illegal_insn;

                case 0x048:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_faligndata();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x04b:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fpmerge();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x04c:  

                     

                    goto illegal_insn;

                case 0x04d:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fexpand();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x050:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fpadd16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x051:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fpadd16s();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x052:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fpadd32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x053:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fpadd32s();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x054:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fpsub16();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x055:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fpsub16s();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x056:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fpadd32();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x057:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fpsub32s();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x060:  

                    gen_op_movl_DT0_0();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x061:  

                    gen_op_movl_FT0_0();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x062:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fnor();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x063:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fnors();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x064:  

                    gen_op_load_fpr_DT1(rs1);

                    gen_op_load_fpr_DT0(rs2);

                    gen_op_fandnot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x065:  

                    gen_op_load_fpr_FT1(rs1);

                    gen_op_load_fpr_FT0(rs2);

                    gen_op_fandnots();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x066:  

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fnot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x067:  

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fnot();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x068:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fandnot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x069:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fandnots();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x06a:  

                    gen_op_load_fpr_DT1(rs1);

                    gen_op_fnot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x06b:  

                    gen_op_load_fpr_FT1(rs1);

                    gen_op_fnot();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x06c:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fxor();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x06d:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fxors();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x06e:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fnand();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x06f:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fnands();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x070:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fand();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x071:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fands();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x072:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fxnor();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x073:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fxnors();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x074:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x075:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x076:  

                    gen_op_load_fpr_DT1(rs1);

                    gen_op_load_fpr_DT0(rs2);

                    gen_op_fornot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x077:  

                    gen_op_load_fpr_FT1(rs1);

                    gen_op_load_fpr_FT0(rs2);

                    gen_op_fornots();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x078:  

                    gen_op_load_fpr_DT0(rs2);

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x079:  

                    gen_op_load_fpr_FT0(rs2);

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x07a:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_fornot();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x07b:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fornots();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x07c:  

                    gen_op_load_fpr_DT0(rs1);

                    gen_op_load_fpr_DT1(rs2);

                    gen_op_for();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x07d:  

                    gen_op_load_fpr_FT0(rs1);

                    gen_op_load_fpr_FT1(rs2);

                    gen_op_fors();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x07e:  

                    gen_op_movl_DT0_1();

                    gen_op_store_DT0_fpr(rd);

                    break;

                case 0x07f:  

                    gen_op_movl_FT0_1();

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x080:  

                case 0x081:  

                     

                    goto illegal_insn;

                default:

                    goto illegal_insn;

                }


                goto ncp_insn;


            } else if (xop == 0x37) {  


                goto illegal_insn;


                goto ncp_insn;



            } else if (xop == 0x39) {  

                rs1 = GET_FIELD(insn, 13, 17);

                save_state(dc);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 19, 31);


                    if (rs2) {


                        gen_movl_simm_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);


                    if (rs2) {


                        gen_movl_reg_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                }

                gen_op_restore();

                gen_mov_pc_npc(dc);

                gen_op_check_align_T0_3();

                gen_op_movl_npc_T0();

                dc->npc = DYNAMIC_PC;

                goto jmp_insn;


            } else {

                rs1 = GET_FIELD(insn, 13, 17);

                gen_movl_reg_T0(rs1);

                if (IS_IMM) {    

                    rs2 = GET_FIELDs(insn, 19, 31);


                    if (rs2) {


                        gen_movl_simm_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                } else {                 

                    rs2 = GET_FIELD(insn, 27, 31);


                    if (rs2) {


                        gen_movl_reg_T1(rs2);

                        gen_op_add_T1_T0();


                    }


                }

                switch (xop) {

                case 0x38:       

                    {

                        if (rd != 0) {


                            if (dc->pc == (uint32_t)dc->pc) {

                                gen_op_movl_T1_im(dc->pc);

                            } else {

                                gen_op_movq_T1_im64(dc->pc >> 32, dc->pc);

                            }


                            gen_op_movl_T1_im(dc->pc);


                            gen_movl_T1_reg(rd);

                        }

                        gen_mov_pc_npc(dc);

                        gen_op_check_align_T0_3();

                        gen_op_movl_npc_T0();

                        dc->npc = DYNAMIC_PC;

                    }

                    goto jmp_insn;


                case 0x39:       

                    {

                        if (!supervisor(dc))

                            goto priv_insn;

                        gen_mov_pc_npc(dc);

                        gen_op_check_align_T0_3();

                        gen_op_movl_npc_T0();

                        dc->npc = DYNAMIC_PC;

                        gen_op_rett();

                    }

                    goto jmp_insn;


                case 0x3b:  

                    gen_op_flush_T0();

                    break;

                case 0x3c:       

                    save_state(dc);

                    gen_op_save();

                    gen_movl_T0_reg(rd);

                    break;

                case 0x3d:       

                    save_state(dc);

                    gen_op_restore();

                    gen_movl_T0_reg(rd);

                    break;


                case 0x3e:       

                    {

                        switch (rd) {

                        case 0:

                            if (!supervisor(dc))

                                goto priv_insn;

                            dc->npc = DYNAMIC_PC;

                            dc->pc = DYNAMIC_PC;

                            gen_op_done();

                            goto jmp_insn;

                        case 1:

                            if (!supervisor(dc))

                                goto priv_insn;

                            dc->npc = DYNAMIC_PC;

                            dc->pc = DYNAMIC_PC;

                            gen_op_retry();

                            goto jmp_insn;

                        default:

                            goto illegal_insn;

                        }

                    }

                    break;


                default:

                    goto illegal_insn;

                }

            }

            break;

        }

        break;

    case 3:                      

        {

            unsigned int xop = GET_FIELD(insn, 7, 12);

            rs1 = GET_FIELD(insn, 13, 17);

            save_state(dc);

            gen_movl_reg_T0(rs1);

            if (xop == 0x3c || xop == 0x3e)

            {

                rs2 = GET_FIELD(insn, 27, 31);

                gen_movl_reg_T1(rs2);

            }

            else if (IS_IMM) {        

                rs2 = GET_FIELDs(insn, 19, 31);


                if (rs2 != 0) {


                    gen_movl_simm_T1(rs2);

                    gen_op_add_T1_T0();


                }


            } else {             

                rs2 = GET_FIELD(insn, 27, 31);


                if (rs2 != 0) {


                    gen_movl_reg_T1(rs2);

                    gen_op_add_T1_T0();


                }


            }

            if (xop < 4 || (xop > 7 && xop < 0x14 && xop != 0x0e) ||

                (xop > 0x17 && xop <= 0x1d ) ||

                (xop > 0x2c && xop <= 0x33) || xop == 0x1f || xop == 0x3d) {

                switch (xop) {

                case 0x0:        


                    gen_op_check_align_T0_3();



                    gen_op_ldst(ld);


                    gen_op_ldst(lduw);


                    break;

                case 0x1:        

                    gen_op_ldst(ldub);

                    break;

                case 0x2:        


                    gen_op_check_align_T0_1();


                    gen_op_ldst(lduh);

                    break;

                case 0x3:        

                    gen_op_check_align_T0_7();

                    if (rd & 1)

                        goto illegal_insn;

                    gen_op_ldst(ldd);

                    gen_movl_T0_reg(rd + 1);

                    break;

                case 0x9:        

                    gen_op_ldst(ldsb);

                    break;

                case 0xa:        


                    gen_op_check_align_T0_1();


                    gen_op_ldst(ldsh);

                    break;

                case 0xd:        

                    gen_op_ldst(ldstub);

                    break;

                case 0x0f:       


                    gen_op_check_align_T0_3();


                    gen_movl_reg_T1(rd);

                    gen_op_ldst(swap);

                    break;


                case 0x10:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_op_check_align_T0_3();


                    gen_ld_asi(insn, 4, 0);

                    break;

                case 0x11:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_ld_asi(insn, 1, 0);

                    break;

                case 0x12:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_op_check_align_T0_1();


                    gen_ld_asi(insn, 2, 0);

                    break;

                case 0x13:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    if (rd & 1)

                        goto illegal_insn;

                    gen_op_check_align_T0_7();

                    gen_ldda_asi(insn);

                    gen_movl_T0_reg(rd + 1);

                    break;

                case 0x19:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_ld_asi(insn, 1, 1);

                    break;

                case 0x1a:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_op_check_align_T0_1();


                    gen_ld_asi(insn, 2, 1);

                    break;

                case 0x1d:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_ldstub_asi(insn);

                    break;

                case 0x1f:       


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_op_check_align_T0_3();


                    gen_movl_reg_T1(rd);

                    gen_swap_asi(insn);

                    break;


                case 0x30:  

                case 0x31:  

                case 0x33:  

                    goto ncp_insn;




                case 0x08:  


                    gen_op_check_align_T0_3();


                    gen_op_ldst(ldsw);

                    break;

                case 0x0b:  

                    gen_op_check_align_T0_7();

                    gen_op_ldst(ldx);

                    break;

                case 0x18:  


                    gen_op_check_align_T0_3();


                    gen_ld_asi(insn, 4, 1);

                    break;

                case 0x1b:  

                    gen_op_check_align_T0_7();

                    gen_ld_asi(insn, 8, 0);

                    break;

                case 0x2d:  

                    goto skip_move;

                case 0x30:  


                    gen_op_check_align_T0_3();


                    gen_ldf_asi(insn, 4);

                    goto skip_move;

                case 0x33:  

                    gen_op_check_align_T0_3();

                    gen_ldf_asi(insn, 8);

                    goto skip_move;

                case 0x3d:  

                    goto skip_move;

                case 0x32:  

                    goto nfpu_insn;


                default:

                    goto illegal_insn;

                }

                gen_movl_T1_reg(rd);


            skip_move: ;


            } else if (xop >= 0x20 && xop < 0x24) {

                if (gen_trap_ifnofpu(dc))

                    goto jmp_insn;

                switch (xop) {

                case 0x20:       


                    gen_op_check_align_T0_3();


                    gen_op_ldst(ldf);

                    gen_op_store_FT0_fpr(rd);

                    break;

                case 0x21:       


                    gen_op_check_align_T0_3();


                    gen_op_ldst(ldf);

                    gen_op_ldfsr();

                    break;

                case 0x22:       

                    goto nfpu_insn;

                case 0x23:       

                    gen_op_check_align_T0_7();

                    gen_op_ldst(lddf);

                    gen_op_store_DT0_fpr(DFPREG(rd));

                    break;

                default:

                    goto illegal_insn;

                }

            } else if (xop < 8 || (xop >= 0x14 && xop < 0x18) || \

                       xop == 0xe || xop == 0x1e) {

                gen_movl_reg_T1(rd);

                switch (xop) {

                case 0x4:


                    gen_op_check_align_T0_3();


                    gen_op_ldst(st);

                    break;

                case 0x5:

                    gen_op_ldst(stb);

                    break;

                case 0x6:


                    gen_op_check_align_T0_1();


                    gen_op_ldst(sth);

                    break;

                case 0x7:

                    if (rd & 1)

                        goto illegal_insn;

                    gen_op_check_align_T0_7();

                    flush_T2(dc);

                    gen_movl_reg_T2(rd + 1);

                    gen_op_ldst(std);

                    break;


                case 0x14:


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;



                    gen_op_check_align_T0_3();


                    gen_st_asi(insn, 4);

                    break;

                case 0x15:


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    gen_st_asi(insn, 1);

                    break;

                case 0x16:


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;



                    gen_op_check_align_T0_1();


                    gen_st_asi(insn, 2);

                    break;

                case 0x17:


                    if (IS_IMM)

                        goto illegal_insn;

                    if (!supervisor(dc))

                        goto priv_insn;


                    if (rd & 1)

                        goto illegal_insn;

                    gen_op_check_align_T0_7();

                    flush_T2(dc);

                    gen_movl_reg_T2(rd + 1);

                    gen_stda_asi(insn);

                    break;



                case 0x0e:  

                    gen_op_check_align_T0_7();

                    gen_op_ldst(stx);

                    break;

                case 0x1e:  

                    gen_op_check_align_T0_7();

                    gen_st_asi(insn, 8);

                    break;


                default:

                    goto illegal_insn;

                }

            } else if (xop > 0x23 && xop < 0x28) {

                if (gen_trap_ifnofpu(dc))

                    goto jmp_insn;

                switch (xop) {

                case 0x24:


                    gen_op_check_align_T0_3();


                    gen_op_load_fpr_FT0(rd);

                    gen_op_ldst(stf);

                    break;

                case 0x25:  


                    gen_op_check_align_T0_3();


                    gen_op_stfsr();

                    gen_op_ldst(stf);

                    break;


                case 0x26:  

                    if (!supervisor(dc))

                        goto priv_insn;

                    if (gen_trap_ifnofpu(dc))

                        goto jmp_insn;

                    goto nfq_insn;


                case 0x27:

                    gen_op_check_align_T0_7();

                    gen_op_load_fpr_DT0(DFPREG(rd));

                    gen_op_ldst(stdf);

                    break;

                default:

                    goto illegal_insn;

                }

            } else if (xop > 0x33 && xop < 0x3f) {

                switch (xop) {


                case 0x34:  


                    gen_op_check_align_T0_3();


                    gen_op_load_fpr_FT0(rd);

                    gen_stf_asi(insn, 4);

                    break;

                case 0x37:  

                    gen_op_check_align_T0_3();

                    gen_op_load_fpr_DT0(DFPREG(rd));

                    gen_stf_asi(insn, 8);

                    break;

                case 0x3c:  


                    gen_op_check_align_T0_3();


                    flush_T2(dc);

                    gen_movl_reg_T2(rd);

                    gen_cas_asi(insn);

                    gen_movl_T1_reg(rd);

                    break;

                case 0x3e:  

                    gen_op_check_align_T0_7();

                    flush_T2(dc);

                    gen_movl_reg_T2(rd);

                    gen_casx_asi(insn);

                    gen_movl_T1_reg(rd);

                    break;

                case 0x36:  

                    goto nfpu_insn;


                case 0x34:  

                case 0x35:  

                case 0x36:  

                case 0x37:  

                    goto ncp_insn;


                default:

                    goto illegal_insn;

                }

            }

            else

                goto illegal_insn;

        }

        break;

    }

     

    if (dc->npc == DYNAMIC_PC) {

        dc->pc = DYNAMIC_PC;

        gen_op_next_insn();

    } else if (dc->npc == JUMP_PC) {

         

        gen_branch2(dc, dc->jump_pc[0], dc->jump_pc[1]);

        dc->is_br = 1;

    } else {

        dc->pc = dc->npc;

        dc->npc = dc->npc + 4;

    }

 jmp_insn:

    return;

 illegal_insn:

    save_state(dc);

    gen_op_exception(TT_ILL_INSN);

    dc->is_br = 1;

    return;


 priv_insn:

    save_state(dc);

    gen_op_exception(TT_PRIV_INSN);

    dc->is_br = 1;

    return;


 nfpu_insn:

    save_state(dc);

    gen_op_fpexception_im(FSR_FTT_UNIMPFPOP);

    dc->is_br = 1;

    return;


 nfq_insn:

    save_state(dc);

    gen_op_fpexception_im(FSR_FTT_SEQ_ERROR);

    dc->is_br = 1;

    return;



 ncp_insn:

    save_state(dc);

    gen_op_exception(TT_NCP_INSN);

    dc->is_br = 1;

    return;


}
