static TCGArg do_constant_folding(int op, TCGArg x, TCGArg y)

{

    TCGArg res = do_constant_folding_2(op, x, y);


    if (op_bits(op) == 32) {

        res &= 0xffffffff;

    }


    return res;

}
