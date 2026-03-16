static TCGArg *tcg_constant_folding(TCGContext *s, uint16_t *tcg_opc_ptr,

                                    TCGArg *args, TCGOpDef *tcg_op_defs)

{

    int i, nb_ops, op_index, nb_temps, nb_globals, nb_call_args;

    TCGOpcode op;

    const TCGOpDef *def;

    TCGArg *gen_args;

    TCGArg tmp;

    TCGCond cond;



     



    nb_temps = s->nb_temps;

    nb_globals = s->nb_globals;

    memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));



    nb_ops = tcg_opc_ptr - gen_opc_buf;

    gen_args = args;

    for (op_index = 0; op_index < nb_ops; op_index++) {

        op = gen_opc_buf[op_index];

        def = &tcg_op_defs[op];

         

        if (!(def->flags & (TCG_OPF_CALL_CLOBBER | TCG_OPF_SIDE_EFFECTS))) {

            assert(op != INDEX_op_call);

            for (i = def->nb_oargs; i < def->nb_oargs + def->nb_iargs; i++) {

                if (temps[args[i]].state == TCG_TEMP_COPY) {

                    args[i] = temps[args[i]].val;

                }

            }

        }



         

        switch (op) {

        CASE_OP_32_64(add):

        CASE_OP_32_64(mul):

        CASE_OP_32_64(and):

        CASE_OP_32_64(or):

        CASE_OP_32_64(xor):

        CASE_OP_32_64(eqv):

        CASE_OP_32_64(nand):

        CASE_OP_32_64(nor):

            if (temps[args[1]].state == TCG_TEMP_CONST) {

                tmp = args[1];

                args[1] = args[2];

                args[2] = tmp;

            }

            break;

        CASE_OP_32_64(brcond):

            if (temps[args[0]].state == TCG_TEMP_CONST

                && temps[args[1]].state != TCG_TEMP_CONST) {

                tmp = args[0];

                args[0] = args[1];

                args[1] = tmp;

                args[2] = tcg_swap_cond(args[2]);

            }

            break;

        CASE_OP_32_64(setcond):

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[2]].state != TCG_TEMP_CONST) {

                tmp = args[1];

                args[1] = args[2];

                args[2] = tmp;

                args[3] = tcg_swap_cond(args[3]);

            }

            break;

        CASE_OP_32_64(movcond):

            cond = args[5];

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[2]].state != TCG_TEMP_CONST) {

                tmp = args[1];

                args[1] = args[2];

                args[2] = tmp;

                cond = tcg_swap_cond(cond);

            }

             

            if (args[0] == args[3]) {

                tmp = args[3];

                args[3] = args[4];

                args[4] = tmp;

                cond = tcg_invert_cond(cond);

            }

            args[5] = cond;

        default:

            break;

        }



         

        switch (op) {

        CASE_OP_32_64(shl):

        CASE_OP_32_64(shr):

        CASE_OP_32_64(sar):

        CASE_OP_32_64(rotl):

        CASE_OP_32_64(rotr):

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[1]].val == 0) {

                gen_opc_buf[op_index] = op_to_movi(op);

                tcg_opt_gen_movi(gen_args, args[0], 0, nb_temps, nb_globals);

                args += 3;

                gen_args += 2;

                continue;

            }

            break;

        default:

            break;

        }



         

        switch (op) {

        CASE_OP_32_64(add):

        CASE_OP_32_64(sub):

        CASE_OP_32_64(shl):

        CASE_OP_32_64(shr):

        CASE_OP_32_64(sar):

        CASE_OP_32_64(rotl):

        CASE_OP_32_64(rotr):

        CASE_OP_32_64(or):

        CASE_OP_32_64(xor):

            if (temps[args[1]].state == TCG_TEMP_CONST) {

                 

                break;

            }

            if (temps[args[2]].state == TCG_TEMP_CONST

                && temps[args[2]].val == 0) {

                if ((temps[args[0]].state == TCG_TEMP_COPY

                    && temps[args[0]].val == args[1])

                    || args[0] == args[1]) {

                    gen_opc_buf[op_index] = INDEX_op_nop;

                } else {

                    gen_opc_buf[op_index] = op_to_mov(op);

                    tcg_opt_gen_mov(gen_args, args[0], args[1],

                                    nb_temps, nb_globals);

                    gen_args += 2;

                }

                args += 3;

                continue;

            }

            break;

        default:

            break;

        }



         

        switch (op) {

        CASE_OP_32_64(and):

        CASE_OP_32_64(mul):

            if ((temps[args[2]].state == TCG_TEMP_CONST

                && temps[args[2]].val == 0)) {

                gen_opc_buf[op_index] = op_to_movi(op);

                tcg_opt_gen_movi(gen_args, args[0], 0, nb_temps, nb_globals);

                args += 3;

                gen_args += 2;

                continue;

            }

            break;

        default:

            break;

        }



         

        switch (op) {

        CASE_OP_32_64(or):

        CASE_OP_32_64(and):

            if (args[1] == args[2]) {

                if (args[1] == args[0]) {

                    gen_opc_buf[op_index] = INDEX_op_nop;

                } else {

                    gen_opc_buf[op_index] = op_to_mov(op);

                    tcg_opt_gen_mov(gen_args, args[0], args[1], nb_temps,

                                    nb_globals);

                    gen_args += 2;

                }

                args += 3;

                continue;

            }

            break;

        default:

            break;

        }



         

        switch (op) {

        CASE_OP_32_64(mov):

            if ((temps[args[1]].state == TCG_TEMP_COPY

                && temps[args[1]].val == args[0])

                || args[0] == args[1]) {

                args += 2;

                gen_opc_buf[op_index] = INDEX_op_nop;

                break;

            }

            if (temps[args[1]].state != TCG_TEMP_CONST) {

                tcg_opt_gen_mov(gen_args, args[0], args[1],

                                nb_temps, nb_globals);

                gen_args += 2;

                args += 2;

                break;

            }

             

            op = op_to_movi(op);

            gen_opc_buf[op_index] = op;

            args[1] = temps[args[1]].val;

             

        CASE_OP_32_64(movi):

            tcg_opt_gen_movi(gen_args, args[0], args[1], nb_temps, nb_globals);

            gen_args += 2;

            args += 2;

            break;

        CASE_OP_32_64(not):

        CASE_OP_32_64(neg):

        CASE_OP_32_64(ext8s):

        CASE_OP_32_64(ext8u):

        CASE_OP_32_64(ext16s):

        CASE_OP_32_64(ext16u):

        case INDEX_op_ext32s_i64:

        case INDEX_op_ext32u_i64:

            if (temps[args[1]].state == TCG_TEMP_CONST) {

                gen_opc_buf[op_index] = op_to_movi(op);

                tmp = do_constant_folding(op, temps[args[1]].val, 0);

                tcg_opt_gen_movi(gen_args, args[0], tmp, nb_temps, nb_globals);

            } else {

                reset_temp(args[0], nb_temps, nb_globals);

                gen_args[0] = args[0];

                gen_args[1] = args[1];

            }

            gen_args += 2;

            args += 2;

            break;

        CASE_OP_32_64(add):

        CASE_OP_32_64(sub):

        CASE_OP_32_64(mul):

        CASE_OP_32_64(or):

        CASE_OP_32_64(and):

        CASE_OP_32_64(xor):

        CASE_OP_32_64(shl):

        CASE_OP_32_64(shr):

        CASE_OP_32_64(sar):

        CASE_OP_32_64(rotl):

        CASE_OP_32_64(rotr):

        CASE_OP_32_64(andc):

        CASE_OP_32_64(orc):

        CASE_OP_32_64(eqv):

        CASE_OP_32_64(nand):

        CASE_OP_32_64(nor):

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[2]].state == TCG_TEMP_CONST) {

                gen_opc_buf[op_index] = op_to_movi(op);

                tmp = do_constant_folding(op, temps[args[1]].val,

                                          temps[args[2]].val);

                tcg_opt_gen_movi(gen_args, args[0], tmp, nb_temps, nb_globals);

                gen_args += 2;

            } else {

                reset_temp(args[0], nb_temps, nb_globals);

                gen_args[0] = args[0];

                gen_args[1] = args[1];

                gen_args[2] = args[2];

                gen_args += 3;

            }

            args += 3;

            break;

        CASE_OP_32_64(setcond):

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[2]].state == TCG_TEMP_CONST) {

                gen_opc_buf[op_index] = op_to_movi(op);

                tmp = do_constant_folding_cond(op, temps[args[1]].val,

                                               temps[args[2]].val, args[3]);

                tcg_opt_gen_movi(gen_args, args[0], tmp, nb_temps, nb_globals);

                gen_args += 2;

            } else {

                reset_temp(args[0], nb_temps, nb_globals);

                gen_args[0] = args[0];

                gen_args[1] = args[1];

                gen_args[2] = args[2];

                gen_args[3] = args[3];

                gen_args += 4;

            }

            args += 4;

            break;

        CASE_OP_32_64(brcond):

            if (temps[args[0]].state == TCG_TEMP_CONST

                && temps[args[1]].state == TCG_TEMP_CONST) {

                if (do_constant_folding_cond(op, temps[args[0]].val,

                                             temps[args[1]].val, args[2])) {

                    memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));

                    gen_opc_buf[op_index] = INDEX_op_br;

                    gen_args[0] = args[3];

                    gen_args += 1;

                } else {

                    gen_opc_buf[op_index] = INDEX_op_nop;

                }

            } else {

                memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));

                reset_temp(args[0], nb_temps, nb_globals);

                gen_args[0] = args[0];

                gen_args[1] = args[1];

                gen_args[2] = args[2];

                gen_args[3] = args[3];

                gen_args += 4;

            }

            args += 4;

            break;

        CASE_OP_32_64(movcond):

            if (temps[args[1]].state == TCG_TEMP_CONST

                && temps[args[2]].state == TCG_TEMP_CONST) {

                tmp = do_constant_folding_cond(op, temps[args[1]].val,

                                               temps[args[2]].val, args[5]);

                if (args[0] == args[4-tmp]

                    || (temps[args[4-tmp]].state == TCG_TEMP_COPY

                        && temps[args[4-tmp]].val == args[0])) {

                    gen_opc_buf[op_index] = INDEX_op_nop;

                } else if (temps[args[4-tmp]].state == TCG_TEMP_CONST) {

                    gen_opc_buf[op_index] = op_to_movi(op);

                    tcg_opt_gen_movi(gen_args, args[0], temps[args[4-tmp]].val,

                                     nb_temps, nb_globals);

                    gen_args += 2;

                } else {

                    gen_opc_buf[op_index] = op_to_mov(op);

                    tcg_opt_gen_mov(gen_args, args[0], args[4-tmp],

                                    nb_temps, nb_globals);

                    gen_args += 2;

                }

            } else {

                reset_temp(args[0], nb_temps, nb_globals);

                gen_args[0] = args[0];

                gen_args[1] = args[1];

                gen_args[2] = args[2];

                gen_args[3] = args[3];

                gen_args[4] = args[4];

                gen_args[5] = args[5];

                gen_args += 6;

            }

            args += 6;

            break;

        case INDEX_op_call:

            nb_call_args = (args[0] >> 16) + (args[0] & 0xffff);

            if (!(args[nb_call_args + 1] & (TCG_CALL_CONST | TCG_CALL_PURE))) {

                for (i = 0; i < nb_globals; i++) {

                    reset_temp(i, nb_temps, nb_globals);

                }

            }

            for (i = 0; i < (args[0] >> 16); i++) {

                reset_temp(args[i + 1], nb_temps, nb_globals);

            }

            i = nb_call_args + 3;

            while (i) {

                *gen_args = *args;

                args++;

                gen_args++;

                i--;

            }

            break;

        default:

             

            if (def->flags & TCG_OPF_BB_END) {

                memset(temps, 0, nb_temps * sizeof(struct tcg_temp_info));

            } else {

                for (i = 0; i < def->nb_oargs; i++) {

                    reset_temp(args[i], nb_temps, nb_globals);

                }

            }

            for (i = 0; i < def->nb_args; i++) {

                gen_args[i] = args[i];

            }

            args += def->nb_args;

            gen_args += def->nb_args;

            break;

        }

    }



    return gen_args;

}
