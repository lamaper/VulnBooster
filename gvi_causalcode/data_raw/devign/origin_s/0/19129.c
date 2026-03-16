static void tcg_out_mov(TCGContext *s, TCGType type, TCGReg ret, TCGReg arg)

{

    uint8_t *old_code_ptr = s->code_ptr;

    assert(ret != arg);


    tcg_out_op_t(s, INDEX_op_mov_i32);


    tcg_out_op_t(s, INDEX_op_mov_i64);


    tcg_out_r(s, ret);

    tcg_out_r(s, arg);

    old_code_ptr[1] = s->code_ptr - old_code_ptr;

}
