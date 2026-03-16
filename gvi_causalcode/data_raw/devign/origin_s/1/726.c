static int decode_gusa(DisasContext *ctx, CPUSH4State *env, int *pmax_insns)

{

    uint16_t insns[5];

    int ld_adr, ld_dst, ld_mop;

    int op_dst, op_src, op_opc;

    int mv_src, mt_dst, st_src, st_mop;

    TCGv op_arg;



    uint32_t pc = ctx->pc;

    uint32_t pc_end = ctx->tb->cs_base;

    int backup = sextract32(ctx->tbflags, GUSA_SHIFT, 8);

    int max_insns = (pc_end - pc) / 2;

    int i;



    if (pc != pc_end + backup || max_insns < 2) {

         

        ctx->envflags &= ~GUSA_MASK;

        return 0;

    }



    if (ctx->tbflags & GUSA_EXCLUSIVE) {

         

        *pmax_insns = max_insns;

        return 0;

    }



     

    if (max_insns > ARRAY_SIZE(insns)) {

        goto fail;

    }



     

    for (i = 0; i < max_insns; ++i) {

        insns[i] = cpu_lduw_code(env, pc + i * 2);

    }



    ld_adr = ld_dst = ld_mop = -1;

    mv_src = -1;

    op_dst = op_src = op_opc = -1;

    mt_dst = -1;

    st_src = st_mop = -1;

    TCGV_UNUSED(op_arg);

    i = 0;


    do { if (i >= max_insns) goto fail; ctx->opcode = insns[i++]; } while (0)



     

    NEXT_INSN;

    switch (ctx->opcode & 0xf00f) {

    case 0x6000:  

        ld_mop = MO_SB;

        break;

    case 0x6001:  

        ld_mop = MO_TESW;

        break;

    case 0x6002:  

        ld_mop = MO_TESL;

        break;

    default:

        goto fail;

    }

    ld_adr = B7_4;

    ld_dst = B11_8;

    if (ld_adr == ld_dst) {

        goto fail;

    }

     

    op_dst = ld_dst;



     

    NEXT_INSN;

    switch (ctx->opcode & 0xf00f) {

    case 0x6003:  

         

        op_dst = B11_8;

        mv_src = B7_4;

        if (op_dst == ld_dst) {

             

            goto fail;

        }

        if (mv_src != ld_dst) {

             

            op_src = ld_dst;

        }

        break;



    default:

         

        --i;

    }



     

    NEXT_INSN;

    switch (ctx->opcode & 0xf00f) {

    case 0x300c:  

        op_opc = INDEX_op_add_i32;

        goto do_reg_op;

    case 0x2009:  

        op_opc = INDEX_op_and_i32;

        goto do_reg_op;

    case 0x200a:  

        op_opc = INDEX_op_xor_i32;

        goto do_reg_op;

    case 0x200b:  

        op_opc = INDEX_op_or_i32;

    do_reg_op:

         

        if (op_dst != B11_8) {

            goto fail;

        }

        if (op_src < 0) {

             

            op_src = B7_4;

        } else if (op_src == B7_4) {

             

            op_src = mv_src;

        } else {

            goto fail;

        }

        op_arg = REG(op_src);

        break;



    case 0x6007:  

        if (ld_dst != B7_4 || mv_src >= 0) {

            goto fail;

        }

        op_dst = B11_8;

        op_opc = INDEX_op_xor_i32;

        op_arg = tcg_const_i32(-1);

        break;



    case 0x7000 ... 0x700f:  

        if (op_dst != B11_8 || mv_src >= 0) {

            goto fail;

        }

        op_opc = INDEX_op_add_i32;

        op_arg = tcg_const_i32(B7_0s);

        break;



    case 0x3000:  

         

        if ((ld_dst == B11_8) + (ld_dst == B7_4) != 1 || mv_src >= 0) {

            goto fail;

        }

        op_opc = INDEX_op_setcond_i32;   

        op_src = (ld_dst == B11_8 ? B7_4 : B11_8);

        op_arg = REG(op_src);



        NEXT_INSN;

        switch (ctx->opcode & 0xff00) {

        case 0x8b00:  

        case 0x8f00:  

            if (pc + (i + 1 + B7_0s) * 2 != pc_end) {

                goto fail;

            }

            if ((ctx->opcode & 0xff00) == 0x8b00) {  

                break;

            }

             

            NEXT_INSN;

            if ((ctx->opcode & 0xf0ff) == 0x0029) {  

                mt_dst = B11_8;

            } else {

                goto fail;

            }

            break;



        default:

            goto fail;

        }

        break;



    case 0x2008:  

         

        if (ld_dst != B11_8 || ld_dst != B7_4 || mv_src >= 0) {

            goto fail;

        }

        op_opc = INDEX_op_setcond_i32;

        op_arg = tcg_const_i32(0);



        NEXT_INSN;

        if ((ctx->opcode & 0xff00) != 0x8900  

            || pc + (i + 1 + B7_0s) * 2 != pc_end) {

            goto fail;

        }

        break;



    default:

         

        --i;

    }



     

     

    if (i != max_insns - 1) {

        goto fail;

    }

    NEXT_INSN;

    switch (ctx->opcode & 0xf00f) {

    case 0x2000:  

        st_mop = MO_UB;

        break;

    case 0x2001:  

        st_mop = MO_UW;

        break;

    case 0x2002:  

        st_mop = MO_UL;

        break;

    default:

        goto fail;

    }

     

    if (ld_adr != B11_8 || st_mop != (ld_mop & MO_SIZE)) {

        goto fail;

    }

    st_src = B7_4;




     

    tcg_gen_insn_start(pc, ctx->envflags);

    switch (op_opc) {

    case -1:

         

        if (st_src == ld_dst || mv_src >= 0) {

            goto fail;

        }

        tcg_gen_atomic_xchg_i32(REG(ld_dst), REG(ld_adr), REG(st_src),

                                ctx->memidx, ld_mop);

        break;



    case INDEX_op_add_i32:

        if (op_dst != st_src) {

            goto fail;

        }

        if (op_dst == ld_dst && st_mop == MO_UL) {

            tcg_gen_atomic_add_fetch_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

        } else {

            tcg_gen_atomic_fetch_add_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

            if (op_dst != ld_dst) {

                 

                tcg_gen_add_i32(REG(op_dst), REG(ld_dst), op_arg);

            }

        }

        break;



    case INDEX_op_and_i32:

        if (op_dst != st_src) {

            goto fail;

        }

        if (op_dst == ld_dst) {

            tcg_gen_atomic_and_fetch_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

        } else {

            tcg_gen_atomic_fetch_and_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

            tcg_gen_and_i32(REG(op_dst), REG(ld_dst), op_arg);

        }

        break;



    case INDEX_op_or_i32:

        if (op_dst != st_src) {

            goto fail;

        }

        if (op_dst == ld_dst) {

            tcg_gen_atomic_or_fetch_i32(REG(ld_dst), REG(ld_adr),

                                        op_arg, ctx->memidx, ld_mop);

        } else {

            tcg_gen_atomic_fetch_or_i32(REG(ld_dst), REG(ld_adr),

                                        op_arg, ctx->memidx, ld_mop);

            tcg_gen_or_i32(REG(op_dst), REG(ld_dst), op_arg);

        }

        break;



    case INDEX_op_xor_i32:

        if (op_dst != st_src) {

            goto fail;

        }

        if (op_dst == ld_dst) {

            tcg_gen_atomic_xor_fetch_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

        } else {

            tcg_gen_atomic_fetch_xor_i32(REG(ld_dst), REG(ld_adr),

                                         op_arg, ctx->memidx, ld_mop);

            tcg_gen_xor_i32(REG(op_dst), REG(ld_dst), op_arg);

        }

        break;



    case INDEX_op_setcond_i32:

        if (st_src == ld_dst) {

            goto fail;

        }

        tcg_gen_atomic_cmpxchg_i32(REG(ld_dst), REG(ld_adr), op_arg,

                                   REG(st_src), ctx->memidx, ld_mop);

        tcg_gen_setcond_i32(TCG_COND_EQ, cpu_sr_t, REG(ld_dst), op_arg);

        if (mt_dst >= 0) {

            tcg_gen_mov_i32(REG(mt_dst), cpu_sr_t);

        }

        break;



    default:

        g_assert_not_reached();

    }



     

    if (op_src < 0) {

        tcg_temp_free_i32(op_arg);

    }



     

    ctx->envflags &= ~GUSA_MASK;

    ctx->pc = pc_end;

    return max_insns;



 fail:

    qemu_log_mask(LOG_UNIMP, "Unrecognized gUSA sequence %08x-%08x\n",

                  pc, pc_end);



     

    tcg_gen_insn_start(pc, ctx->envflags);

    ctx->envflags |= GUSA_EXCLUSIVE;

    gen_save_cpu_state(ctx, false);

    gen_helper_exclusive(cpu_env);

    ctx->bstate = BS_EXCP;



     

    ctx->pc = pc_end;

    return 1;

}
