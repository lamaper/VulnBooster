static void tcg_out_qemu_st (TCGContext *s, const TCGArg *args, int opc)

{

    int addr_reg, r0, r1, data_reg, data_reg2, bswap, rbase;


    int mem_index, r2, addr_reg2;

    uint8_t *label_ptr;




    data_reg = *args++;

    if (opc == 3)

        data_reg2 = *args++;

    else

        data_reg2 = 0;

    addr_reg = *args++;



    addr_reg2 = *args++;


    addr_reg2 = 0;


    mem_index = *args;

    r0 = 3;

    r1 = 4;

    r2 = 0;

    rbase = 0;



    tcg_out_tlb_check (

        s, r0, r1, r2, addr_reg, addr_reg2, opc & 3,

        offsetof (CPUArchState, tlb_table[mem_index][0].addr_write),

        offsetof (CPUTLBEntry, addend) - offsetof (CPUTLBEntry, addr_write),

        &label_ptr

        );


    r0 = addr_reg;

    r1 = 3;

    rbase = GUEST_BASE ? TCG_GUEST_BASE_REG : 0;



    bswap = 0;


    bswap = 1;


    switch (opc) {

    case 0:

        tcg_out32 (s, STBX | SAB (data_reg, rbase, r0));

        break;

    case 1:

        if (bswap)

            tcg_out32 (s, STHBRX | SAB (data_reg, rbase, r0));

        else

            tcg_out32 (s, STHX | SAB (data_reg, rbase, r0));

        break;

    case 2:

        if (bswap)

            tcg_out32 (s, STWBRX | SAB (data_reg, rbase, r0));

        else

            tcg_out32 (s, STWX | SAB (data_reg, rbase, r0));

        break;

    case 3:

        if (bswap) {

            tcg_out32 (s, ADDI | RT (r1) | RA (r0) | 4);

            tcg_out32 (s, STWBRX | SAB (data_reg,  rbase, r0));

            tcg_out32 (s, STWBRX | SAB (data_reg2, rbase, r1));

        }

        else {


            tcg_out32 (s, STWX | SAB (data_reg2, rbase, r0));

            tcg_out32 (s, ADDI | RT (r1) | RA (r0) | 4);

            tcg_out32 (s, STWX | SAB (data_reg,  rbase, r1));


            tcg_out32 (s, STW | RS (data_reg2) | RA (r0));

            tcg_out32 (s, STW | RS (data_reg) | RA (r0) | 4);


        }

        break;

    }


    add_qemu_ldst_label (s,

                         0,

                         opc,

                         data_reg,

                         data_reg2,

                         addr_reg,

                         addr_reg2,

                         mem_index,

                         s->code_ptr,

                         label_ptr);


}
