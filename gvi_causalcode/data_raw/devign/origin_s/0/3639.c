static TCGv_i32 gen_get_asi(DisasContext *dc, int insn)

{

    int asi;



    if (IS_IMM) {


        asi = dc->asi;


        gen_exception(dc, TT_ILL_INSN);

        asi = 0;


    } else {

        asi = GET_FIELD(insn, 19, 26);

    }

    return tcg_const_i32(asi);

}
