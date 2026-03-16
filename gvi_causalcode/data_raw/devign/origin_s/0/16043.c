static inline void tcg_out_qemu_ld(TCGContext *s, const TCGArg *args, int opc)

{

    int addr_reg, data_reg, data_reg2, bswap;


    int mem_index, s_bits;


    int addr_reg2;


    uint32_t *label_ptr;



    bswap = 1;


    bswap = 0;


    data_reg = *args++;

    if (opc == 3)

        data_reg2 = *args++;

    else

        data_reg2 = 0;  

    addr_reg = *args++;



    addr_reg2 = *args++;


    mem_index = *args;

    s_bits = opc & 3;




    tcg_out_dat_reg(s, COND_AL, ARITH_MOV, TCG_REG_R8,

                    0, addr_reg, SHIFT_IMM_LSR(TARGET_PAGE_BITS));

    tcg_out_dat_imm(s, COND_AL, ARITH_AND,

                    TCG_REG_R0, TCG_REG_R8, CPU_TLB_SIZE - 1);

    tcg_out_dat_reg(s, COND_AL, ARITH_ADD, TCG_REG_R0, TCG_AREG0,

                    TCG_REG_R0, SHIFT_IMM_LSL(CPU_TLB_ENTRY_BITS));

     

    if (mem_index)

        tcg_out_dat_imm(s, COND_AL, ARITH_ADD, TCG_REG_R0, TCG_REG_R0,

                        (mem_index << (TLB_SHIFT & 1)) |

                        ((16 - (TLB_SHIFT >> 1)) << 8));

    tcg_out_ld32_12(s, COND_AL, TCG_REG_R1, TCG_REG_R0,

                    offsetof(CPUState, tlb_table[0][0].addr_read));

    tcg_out_dat_reg(s, COND_AL, ARITH_CMP, 0, TCG_REG_R1,

                    TCG_REG_R8, SHIFT_IMM_LSL(TARGET_PAGE_BITS));

     

    if (s_bits)

        tcg_out_dat_imm(s, COND_EQ, ARITH_TST,

                        0, addr_reg, (1 << s_bits) - 1);


     

    tcg_out_ld32_12(s, COND_EQ, TCG_REG_R1, TCG_REG_R0,

                    offsetof(CPUState, tlb_table[0][0].addr_read) + 4);

    tcg_out_dat_reg(s, COND_EQ, ARITH_CMP, 0,

                    TCG_REG_R1, addr_reg2, SHIFT_IMM_LSL(0));


    tcg_out_ld32_12(s, COND_EQ, TCG_REG_R1, TCG_REG_R0,

                    offsetof(CPUState, tlb_table[0][0].addend));



    switch (opc) {

    case 0:

        tcg_out_ld8_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

        break;

    case 0 | 4:

        tcg_out_ld8s_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

        break;

    case 1:

        tcg_out_ld16u_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

        if (bswap) {

            tcg_out_bswap16(s, COND_EQ, data_reg, data_reg);

        }

        break;

    case 1 | 4:

        if (bswap) {

            tcg_out_ld16u_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

            tcg_out_bswap16s(s, COND_EQ, data_reg, data_reg);

        } else {

            tcg_out_ld16s_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

        }

        break;

    case 2:

    default:

        tcg_out_ld32_r(s, COND_EQ, data_reg, addr_reg, TCG_REG_R1);

        if (bswap) {

            tcg_out_bswap32(s, COND_EQ, data_reg, data_reg);

        }

        break;

    case 3:

        if (bswap) {

            tcg_out_ld32_rwb(s, COND_EQ, data_reg2, TCG_REG_R1, addr_reg);

            tcg_out_ld32_12(s, COND_EQ, data_reg, TCG_REG_R1, 4);

            tcg_out_bswap32(s, COND_EQ, data_reg2, data_reg2);

            tcg_out_bswap32(s, COND_EQ, data_reg, data_reg);

        } else {

            tcg_out_ld32_rwb(s, COND_EQ, data_reg, TCG_REG_R1, addr_reg);

            tcg_out_ld32_12(s, COND_EQ, data_reg2, TCG_REG_R1, 4);

        }

        break;

    }



    label_ptr = (void *) s->code_ptr;

    tcg_out_b(s, COND_EQ, 8);



     

    if (addr_reg != TCG_REG_R0) {

        tcg_out_dat_reg(s, COND_AL, ARITH_MOV,

                        TCG_REG_R0, 0, addr_reg, SHIFT_IMM_LSL(0));

    }


    tcg_out_dat_imm(s, COND_AL, ARITH_MOV, TCG_REG_R1, 0, mem_index);


    if (addr_reg2 != TCG_REG_R1) {

        tcg_out_dat_reg(s, COND_AL, ARITH_MOV,

                        TCG_REG_R1, 0, addr_reg2, SHIFT_IMM_LSL(0));

    }

    tcg_out_dat_imm(s, COND_AL, ARITH_MOV, TCG_REG_R2, 0, mem_index);


    tcg_out_bl(s, COND_AL, (tcg_target_long) qemu_ld_helpers[s_bits] -

                    (tcg_target_long) s->code_ptr);



    switch (opc) {

    case 0 | 4:

        tcg_out_ext8s(s, COND_AL, data_reg, TCG_REG_R0);

        break;

    case 1 | 4:

        tcg_out_ext16s(s, COND_AL, data_reg, TCG_REG_R0);

        break;

    case 0:

    case 1:

    case 2:

    default:

        if (data_reg != TCG_REG_R0) {

            tcg_out_dat_reg(s, COND_AL, ARITH_MOV,

                            data_reg, 0, TCG_REG_R0, SHIFT_IMM_LSL(0));

        }

        break;

    case 3:

        if (data_reg != TCG_REG_R0) {

            tcg_out_dat_reg(s, COND_AL, ARITH_MOV,

                            data_reg, 0, TCG_REG_R0, SHIFT_IMM_LSL(0));

        }

        if (data_reg2 != TCG_REG_R1) {

            tcg_out_dat_reg(s, COND_AL, ARITH_MOV,

                            data_reg2, 0, TCG_REG_R1, SHIFT_IMM_LSL(0));

        }

        break;

    }



    *label_ptr += ((void *) s->code_ptr - (void *) label_ptr - 8) >> 2;


    if (GUEST_BASE) {

        uint32_t offset = GUEST_BASE;

        int i;

        int rot;



        while (offset) {

            i = ctz32(offset) & ~1;

            rot = ((32 - i) << 7) & 0xf00;



            tcg_out_dat_imm(s, COND_AL, ARITH_ADD, TCG_REG_R8, addr_reg,

                            ((offset >> i) & 0xff) | rot);

            addr_reg = TCG_REG_R8;

            offset &= ~(0xff << i);

        }

    }

    switch (opc) {

    case 0:

        tcg_out_ld8_12(s, COND_AL, data_reg, addr_reg, 0);

        break;

    case 0 | 4:

        tcg_out_ld8s_8(s, COND_AL, data_reg, addr_reg, 0);

        break;

    case 1:

        tcg_out_ld16u_8(s, COND_AL, data_reg, addr_reg, 0);

        if (bswap) {

            tcg_out_bswap16(s, COND_AL, data_reg, data_reg);

        }

        break;

    case 1 | 4:

        if (bswap) {

            tcg_out_ld16u_8(s, COND_AL, data_reg, addr_reg, 0);

            tcg_out_bswap16s(s, COND_AL, data_reg, data_reg);

        } else {

            tcg_out_ld16s_8(s, COND_AL, data_reg, addr_reg, 0);

        }

        break;

    case 2:

    default:

        tcg_out_ld32_12(s, COND_AL, data_reg, addr_reg, 0);

        if (bswap) {

            tcg_out_bswap32(s, COND_AL, data_reg, data_reg);

        }

        break;

    case 3:

         

        if (data_reg == addr_reg) {

            tcg_out_ld32_12(s, COND_AL, data_reg2, addr_reg, bswap ? 0 : 4);

            tcg_out_ld32_12(s, COND_AL, data_reg, addr_reg, bswap ? 4 : 0);

        } else {

            tcg_out_ld32_12(s, COND_AL, data_reg, addr_reg, bswap ? 4 : 0);

            tcg_out_ld32_12(s, COND_AL, data_reg2, addr_reg, bswap ? 0 : 4);

        }

        if (bswap) {

            tcg_out_bswap32(s, COND_AL, data_reg, data_reg);

            tcg_out_bswap32(s, COND_AL, data_reg2, data_reg2);

        }

        break;

    }


}
