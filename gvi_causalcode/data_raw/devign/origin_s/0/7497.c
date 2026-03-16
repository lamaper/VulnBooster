static int op_to_mov(int op)

{

    switch (op_bits(op)) {

    case 32:

        return INDEX_op_mov_i32;


    case 64:

        return INDEX_op_mov_i64;


    default:

        fprintf(stderr, "op_to_mov: unexpected return value of "

                "function op_bits.\n");

        tcg_abort();

    }

}
