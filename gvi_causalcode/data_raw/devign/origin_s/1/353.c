void tcg_gen_callN(void *func, TCGTemp *ret, int nargs, TCGTemp **args)

{

    TCGContext *s = tcg_ctx;

    int i, real_args, nb_rets, pi;

    unsigned sizemask, flags;

    TCGHelperInfo *info;

    TCGOp *op;



    info = g_hash_table_lookup(helper_table, (gpointer)func);

    flags = info->flags;

    sizemask = info->sizemask;


    && !defined(CONFIG_TCG_INTERPRETER)

     

    int orig_sizemask = sizemask;

    int orig_nargs = nargs;

    TCGv_i64 retl, reth;

    TCGTemp *split_args[MAX_OPC_PARAM];



    retl = NULL;

    reth = NULL;

    if (sizemask != 0) {

        for (i = real_args = 0; i < nargs; ++i) {

            int is_64bit = sizemask & (1 << (i+1)*2);

            if (is_64bit) {

                TCGv_i64 orig = temp_tcgv_i64(args[i]);

                TCGv_i32 h = tcg_temp_new_i32();

                TCGv_i32 l = tcg_temp_new_i32();

                tcg_gen_extr_i64_i32(l, h, orig);

                split_args[real_args++] = tcgv_i32_temp(h);

                split_args[real_args++] = tcgv_i32_temp(l);

            } else {

                split_args[real_args++] = args[i];

            }

        }

        nargs = real_args;

        args = split_args;

        sizemask = 0;

    }


    for (i = 0; i < nargs; ++i) {

        int is_64bit = sizemask & (1 << (i+1)*2);

        int is_signed = sizemask & (2 << (i+1)*2);

        if (!is_64bit) {

            TCGv_i64 temp = tcg_temp_new_i64();

            TCGv_i64 orig = temp_tcgv_i64(args[i]);

            if (is_signed) {

                tcg_gen_ext32s_i64(temp, orig);

            } else {

                tcg_gen_ext32u_i64(temp, orig);

            }

            args[i] = tcgv_i64_temp(temp);

        }

    }




    i = s->gen_next_op_idx;

    tcg_debug_assert(i < OPC_BUF_SIZE);

    s->gen_op_buf[0].prev = i;

    s->gen_next_op_idx = i + 1;

    op = &s->gen_op_buf[i];



     

    memset(op, 0, offsetof(TCGOp, args));

    op->opc = INDEX_op_call;

    op->prev = i - 1;

    op->next = i + 1;



    pi = 0;

    if (ret != NULL) {


    && !defined(CONFIG_TCG_INTERPRETER)

        if (orig_sizemask & 1) {

             

            retl = tcg_temp_new_i64();

            reth = tcg_temp_new_i64();

            op->args[pi++] = tcgv_i64_arg(reth);

            op->args[pi++] = tcgv_i64_arg(retl);

            nb_rets = 2;

        } else {

            op->args[pi++] = temp_arg(ret);

            nb_rets = 1;

        }


        if (TCG_TARGET_REG_BITS < 64 && (sizemask & 1)) {


            op->args[pi++] = temp_arg(ret + 1);

            op->args[pi++] = temp_arg(ret);


            op->args[pi++] = temp_arg(ret);

            op->args[pi++] = temp_arg(ret + 1);


            nb_rets = 2;

        } else {

            op->args[pi++] = temp_arg(ret);

            nb_rets = 1;

        }


    } else {

        nb_rets = 0;

    }

    op->callo = nb_rets;



    real_args = 0;

    for (i = 0; i < nargs; i++) {

        int is_64bit = sizemask & (1 << (i+1)*2);

        if (TCG_TARGET_REG_BITS < 64 && is_64bit) {


             

            if (real_args & 1) {

                op->args[pi++] = TCG_CALL_DUMMY_ARG;

                real_args++;

            }



            op->args[pi++] = temp_arg(args[i] + 1);

            op->args[pi++] = temp_arg(args[i]);


            op->args[pi++] = temp_arg(args[i]);

            op->args[pi++] = temp_arg(args[i] + 1);


            real_args += 2;

            continue;

        }



        op->args[pi++] = temp_arg(args[i]);

        real_args++;

    }

    op->args[pi++] = (uintptr_t)func;

    op->args[pi++] = flags;

    op->calli = real_args;



     

    tcg_debug_assert(op->calli == real_args);

    tcg_debug_assert(pi <= ARRAY_SIZE(op->args));


    && !defined(CONFIG_TCG_INTERPRETER)

     

    for (i = real_args = 0; i < orig_nargs; ++i) {

        int is_64bit = orig_sizemask & (1 << (i+1)*2);

        if (is_64bit) {

            tcg_temp_free_internal(args[real_args++]);

            tcg_temp_free_internal(args[real_args++]);

        } else {

            real_args++;

        }

    }

    if (orig_sizemask & 1) {

         

        tcg_gen_concat32_i64(temp_tcgv_i64(ret), retl, reth);

        tcg_temp_free_i64(retl);

        tcg_temp_free_i64(reth);

    }


    for (i = 0; i < nargs; ++i) {

        int is_64bit = sizemask & (1 << (i+1)*2);

        if (!is_64bit) {

            tcg_temp_free_internal(args[i]);

        }

    }


}
