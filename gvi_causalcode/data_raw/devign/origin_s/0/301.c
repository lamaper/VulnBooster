static void tcg_liveness_analysis(TCGContext *s)

{

    uint8_t *dead_temps, *mem_temps;

    int oi, oi_prev, nb_ops;



    nb_ops = s->gen_next_op_idx;

    s->op_dead_args = tcg_malloc(nb_ops * sizeof(uint16_t));

    s->op_sync_args = tcg_malloc(nb_ops * sizeof(uint8_t));

    

    dead_temps = tcg_malloc(s->nb_temps);

    mem_temps = tcg_malloc(s->nb_temps);

    tcg_la_func_end(s, dead_temps, mem_temps);



    for (oi = s->gen_last_op_idx; oi >= 0; oi = oi_prev) {

        int i, nb_iargs, nb_oargs;

        TCGOpcode opc_new, opc_new2;

        bool have_opc_new2;

        uint16_t dead_args;

        uint8_t sync_args;

        TCGArg arg;



        TCGOp * const op = &s->gen_op_buf[oi];

        TCGArg * const args = &s->gen_opparam_buf[op->args];

        TCGOpcode opc = op->opc;

        const TCGOpDef *def = &tcg_op_defs[opc];



        oi_prev = op->prev;



        switch (opc) {

        case INDEX_op_call:

            {

                int call_flags;



                nb_oargs = op->callo;

                nb_iargs = op->calli;

                call_flags = args[nb_oargs + nb_iargs + 1];



                 

                if (call_flags & TCG_CALL_NO_SIDE_EFFECTS) {

                    for (i = 0; i < nb_oargs; i++) {

                        arg = args[i];

                        if (!dead_temps[arg] || mem_temps[arg]) {

                            goto do_not_remove_call;

                        }

                    }

                    goto do_remove;

                } else {

                do_not_remove_call:



                     

                    dead_args = 0;

                    sync_args = 0;

                    for (i = 0; i < nb_oargs; i++) {

                        arg = args[i];

                        if (dead_temps[arg]) {

                            dead_args |= (1 << i);

                        }

                        if (mem_temps[arg]) {

                            sync_args |= (1 << i);

                        }

                        dead_temps[arg] = 1;

                        mem_temps[arg] = 0;

                    }



                    if (!(call_flags & TCG_CALL_NO_READ_GLOBALS)) {

                         

                        memset(mem_temps, 1, s->nb_globals);

                    }

                    if (!(call_flags & (TCG_CALL_NO_WRITE_GLOBALS |

                                        TCG_CALL_NO_READ_GLOBALS))) {

                         

                        memset(dead_temps, 1, s->nb_globals);

                    }



                     

                    for (i = nb_oargs; i < nb_iargs + nb_oargs; i++) {

                        arg = args[i];

                        if (arg != TCG_CALL_DUMMY_ARG) {

                            if (dead_temps[arg]) {

                                dead_args |= (1 << i);

                            }

                            dead_temps[arg] = 0;

                        }

                    }

                    s->op_dead_args[oi] = dead_args;

                    s->op_sync_args[oi] = sync_args;

                }

            }

            break;

        case INDEX_op_debug_insn_start:

            break;

        case INDEX_op_discard:

             

            dead_temps[args[0]] = 1;

            mem_temps[args[0]] = 0;

            break;



        case INDEX_op_add2_i32:

            opc_new = INDEX_op_add_i32;

            goto do_addsub2;

        case INDEX_op_sub2_i32:

            opc_new = INDEX_op_sub_i32;

            goto do_addsub2;

        case INDEX_op_add2_i64:

            opc_new = INDEX_op_add_i64;

            goto do_addsub2;

        case INDEX_op_sub2_i64:

            opc_new = INDEX_op_sub_i64;

        do_addsub2:

            nb_iargs = 4;

            nb_oargs = 2;

             

            if (dead_temps[args[1]] && !mem_temps[args[1]]) {

                if (dead_temps[args[0]] && !mem_temps[args[0]]) {

                    goto do_remove;

                }

                 

                op->opc = opc = opc_new;

                args[1] = args[2];

                args[2] = args[4];

                 

                nb_iargs = 2;

                nb_oargs = 1;

            }

            goto do_not_remove;



        case INDEX_op_mulu2_i32:

            opc_new = INDEX_op_mul_i32;

            opc_new2 = INDEX_op_muluh_i32;

            have_opc_new2 = TCG_TARGET_HAS_muluh_i32;

            goto do_mul2;

        case INDEX_op_muls2_i32:

            opc_new = INDEX_op_mul_i32;

            opc_new2 = INDEX_op_mulsh_i32;

            have_opc_new2 = TCG_TARGET_HAS_mulsh_i32;

            goto do_mul2;

        case INDEX_op_mulu2_i64:

            opc_new = INDEX_op_mul_i64;

            opc_new2 = INDEX_op_muluh_i64;

            have_opc_new2 = TCG_TARGET_HAS_muluh_i64;

            goto do_mul2;

        case INDEX_op_muls2_i64:

            opc_new = INDEX_op_mul_i64;

            opc_new2 = INDEX_op_mulsh_i64;

            have_opc_new2 = TCG_TARGET_HAS_mulsh_i64;

            goto do_mul2;

        do_mul2:

            nb_iargs = 2;

            nb_oargs = 2;

            if (dead_temps[args[1]] && !mem_temps[args[1]]) {

                if (dead_temps[args[0]] && !mem_temps[args[0]]) {

                     

                    goto do_remove;

                }

                 

                op->opc = opc = opc_new;

                args[1] = args[2];

                args[2] = args[3];

            } else if (have_opc_new2 && dead_temps[args[0]]

                       && !mem_temps[args[0]]) {

                 

                op->opc = opc = opc_new2;

                args[0] = args[1];

                args[1] = args[2];

                args[2] = args[3];

            } else {

                goto do_not_remove;

            }

             

            nb_oargs = 1;

            goto do_not_remove;



        default:

             

            nb_iargs = def->nb_iargs;

            nb_oargs = def->nb_oargs;



             

            if (!(def->flags & TCG_OPF_SIDE_EFFECTS) && nb_oargs != 0) {

                for (i = 0; i < nb_oargs; i++) {

                    arg = args[i];

                    if (!dead_temps[arg] || mem_temps[arg]) {

                        goto do_not_remove;

                    }

                }

            do_remove:

                tcg_op_remove(s, op);

            } else {

            do_not_remove:

                 

                dead_args = 0;

                sync_args = 0;

                for (i = 0; i < nb_oargs; i++) {

                    arg = args[i];

                    if (dead_temps[arg]) {

                        dead_args |= (1 << i);

                    }

                    if (mem_temps[arg]) {

                        sync_args |= (1 << i);

                    }

                    dead_temps[arg] = 1;

                    mem_temps[arg] = 0;

                }



                 

                if (def->flags & TCG_OPF_BB_END) {

                    tcg_la_bb_end(s, dead_temps, mem_temps);

                } else if (def->flags & TCG_OPF_SIDE_EFFECTS) {

                     

                    memset(mem_temps, 1, s->nb_globals);

                }



                 

                for (i = nb_oargs; i < nb_oargs + nb_iargs; i++) {

                    arg = args[i];

                    if (dead_temps[arg]) {

                        dead_args |= (1 << i);

                    }

                    dead_temps[arg] = 0;

                }

                s->op_dead_args[oi] = dead_args;

                s->op_sync_args[oi] = sync_args;

            }

            break;

        }

    }

}
