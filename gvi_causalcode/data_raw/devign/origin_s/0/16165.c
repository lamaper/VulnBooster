static void tcg_out_qemu_ld (TCGContext *s, const TCGArg *args, int opc)

{

    int addr_reg, data_reg, data_reg2, r0, r1, rbase, mem_index, s_bits, bswap;


    int r2;

    void *label1_ptr, *label2_ptr;



    int addr_reg2;




    data_reg = *args++;

    if (opc == 3)

        data_reg2 = *args++;

    else

        data_reg2 = 0;

    addr_reg = *args++;


    addr_reg2 = *args++;


    mem_index = *args;

    s_bits = opc & 3;


    r0 = 3;

    r1 = 4;

    r2 = 0;

    rbase = 0;



    tcg_out32 (s, (RLWINM

                   | RA (r0)

                   | RS (addr_reg)

                   | SH (32 - (TARGET_PAGE_BITS - CPU_TLB_ENTRY_BITS))

                   | MB (32 - (CPU_TLB_BITS + CPU_TLB_ENTRY_BITS))

                   | ME (31 - CPU_TLB_ENTRY_BITS)

                   )

        );

    tcg_out32 (s, ADD | RT (r0) | RA (r0) | RB (TCG_AREG0));

    tcg_out32 (s, (LWZU

                   | RT (r1)

                   | RA (r0)

                   | offsetof (CPUState, tlb_table[mem_index][0].addr_read)

                   )

        );

    tcg_out32 (s, (RLWINM

                   | RA (r2)

                   | RS (addr_reg)

                   | SH (0)

                   | MB ((32 - s_bits) & 31)

                   | ME (31 - TARGET_PAGE_BITS)

                   )

        );



    tcg_out32 (s, CMP | BF (7) | RA (r2) | RB (r1));


    tcg_out32 (s, LWZ | RT (r1) | RA (r0) | 4);

    tcg_out32 (s, CMP | BF (6) | RA (addr_reg2) | RB (r1));

    tcg_out32 (s, CRAND | BT (7, CR_EQ) | BA (6, CR_EQ) | BB (7, CR_EQ));




    label1_ptr = s->code_ptr;


    tcg_out32 (s, BC | BI (7, CR_EQ) | BO_COND_TRUE);



    tcg_out_mov (s, 3, addr_reg);

    tcg_out_movi (s, TCG_TYPE_I32, 4, mem_index);


    tcg_out_mov (s, 3, addr_reg2);

    tcg_out_mov (s, 4, addr_reg);

    tcg_out_movi (s, TCG_TYPE_I32, 5, mem_index);




    tcg_out_call (s, (tcg_target_long) qemu_ld_helpers[s_bits], 1);

    switch (opc) {

    case 0|4:

        tcg_out32 (s, EXTSB | RA (data_reg) | RS (3));

        break;

    case 1|4:

        tcg_out32 (s, EXTSH | RA (data_reg) | RS (3));

        break;

    case 0:

    case 1:

    case 2:

        if (data_reg != 3)

            tcg_out_mov (s, data_reg, 3);

        break;

    case 3:

        if (data_reg == 3) {

            if (data_reg2 == 4) {

                tcg_out_mov (s, 0, 4);

                tcg_out_mov (s, 4, 3);

                tcg_out_mov (s, 3, 0);

            }

            else {

                tcg_out_mov (s, data_reg2, 3);

                tcg_out_mov (s, 3, 4);

            }

        }

        else {

            if (data_reg != 4) tcg_out_mov (s, data_reg, 4);

            if (data_reg2 != 3) tcg_out_mov (s, data_reg2, 3);

        }

        break;

    }

    label2_ptr = s->code_ptr;

    tcg_out32 (s, B);


    reloc_pc14 (label1_ptr, (tcg_target_long) s->code_ptr);




     

    tcg_out32 (s, (LWZ

                   | RT (r0)

                   | RA (r0)

                   | (ADDEND_OFFSET + offsetof (CPUTLBEntry, addend)

                      - offsetof (CPUTLBEntry, addr_read))

                   ));

     

    tcg_out32 (s, ADD | RT (r0) | RA (r0) | RB (addr_reg));


    r0 = addr_reg;

    r1 = 3;

    rbase = GUEST_BASE ? TCG_GUEST_BASE_REG : 0;



    bswap = 0;


    bswap = 1;




    switch (opc) {

    default:

    case 0:

        tcg_out32 (s, LBZX | TAB (data_reg, rbase, r0));

        break;

    case 0|4:

        tcg_out32 (s, LBZX | TAB (data_reg, rbase, r0));

        tcg_out32 (s, EXTSB | RA (data_reg) | RS (data_reg));

        break;

    case 1:

        if (bswap)

            tcg_out32 (s, LHBRX | TAB (data_reg, rbase, r0));

        else

            tcg_out32 (s, LHZX | TAB (data_reg, rbase, r0));

        break;

    case 1|4:

        if (bswap) {

            tcg_out32 (s, LHBRX | TAB (data_reg, rbase, r0));

            tcg_out32 (s, EXTSH | RA (data_reg) | RS (data_reg));

        }

        else tcg_out32 (s, LHAX | TAB (data_reg, rbase, r0));

        break;

    case 2:

        if (bswap)

            tcg_out32 (s, LWBRX | TAB (data_reg, rbase, r0));

        else

            tcg_out32 (s, LWZX | TAB (data_reg, rbase, r0));

        break;

    case 3:

        if (bswap) {

            tcg_out32 (s, ADDI | RT (r1) | RA (r0) | 4);

            tcg_out32 (s, LWBRX | TAB (data_reg, rbase, r0));

            tcg_out32 (s, LWBRX | TAB (data_reg2, rbase, r1));

        }

        else {


            tcg_out32 (s, ADDI | RT (r1) | RA (r0) | 4);

            tcg_out32 (s, LWZX | TAB (data_reg2, rbase, r0));

            tcg_out32 (s, LWZX | TAB (data_reg, rbase, r1));


            if (r0 == data_reg2) {

                tcg_out32 (s, LWZ | RT (0) | RA (r0));

                tcg_out32 (s, LWZ | RT (data_reg) | RA (r0) | 4);

                tcg_out_mov (s, data_reg2, 0);

            }

            else {

                tcg_out32 (s, LWZ | RT (data_reg2) | RA (r0));

                tcg_out32 (s, LWZ | RT (data_reg) | RA (r0) | 4);

            }


        }

        break;

    }


    reloc_pc24 (label2_ptr, (tcg_target_long) s->code_ptr);


}
