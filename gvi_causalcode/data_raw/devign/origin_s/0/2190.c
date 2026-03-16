static int decode_opc(MoxieCPU *cpu, DisasContext *ctx)

{

    CPUMoxieState *env = &cpu->env;



     

    int opcode;

     

    int length = 2;



    if (unlikely(qemu_loglevel_mask(CPU_LOG_TB_OP | CPU_LOG_TB_OP_OPT))) {

        tcg_gen_debug_insn_start(ctx->pc);

    }



     

    opcode = ctx->opcode;



     

    if (opcode & (1 << 15)) {

        if (opcode & (1 << 14)) {

             

            int inst = (opcode >> 10 & 0xf);


    do {                                                                     \

        int l1 = gen_new_label();                                            \

        tcg_gen_brcond_i32(cond, cc_a, cc_b, l1);                            \

        gen_goto_tb(env, ctx, 1, ctx->pc+2);                                 \

        gen_set_label(l1);                                                   \

        gen_goto_tb(env, ctx, 0, extract_branch_offset(opcode) + ctx->pc+2); \

        ctx->bstate = BS_BRANCH;                                             \

    } while (0)



            switch (inst) {

            case 0x00:  

                BRANCH(TCG_COND_EQ);

                break;

            case 0x01:  

                BRANCH(TCG_COND_NE);

                break;

            case 0x02:  

                BRANCH(TCG_COND_LT);

                break;

            case 0x03:  

                BRANCH(TCG_COND_GT);

                break;

            case 0x04:  

                BRANCH(TCG_COND_LTU);

                break;

            case 0x05:  

                BRANCH(TCG_COND_GTU);

                break;

            case 0x06:  

                BRANCH(TCG_COND_GE);

                break;

            case 0x07:  

                BRANCH(TCG_COND_LE);

                break;

            case 0x08:  

                BRANCH(TCG_COND_GEU);

                break;

            case 0x09:  

                BRANCH(TCG_COND_LEU);

                break;

            default:

                {

                    TCGv temp = tcg_temp_new_i32();

                    tcg_gen_movi_i32(cpu_pc, ctx->pc);

                    tcg_gen_movi_i32(temp, MOXIE_EX_BAD);

                    gen_helper_raise_exception(cpu_env, temp);

                    tcg_temp_free_i32(temp);

                }

                break;

            }

        } else {

             

            int inst = (opcode >> 12 & 0x3);

            switch (inst) {

            case 0x00:  

                {

                    int a = (opcode >> 8) & 0xf;

                    unsigned int v = (opcode & 0xff);

                    tcg_gen_addi_i32(REG(a), REG(a), v);

                }

                break;

            case 0x01:  

                {

                    int a = (opcode >> 8) & 0xf;

                    unsigned int v = (opcode & 0xff);

                    tcg_gen_subi_i32(REG(a), REG(a), v);

                }

                break;

            case 0x02:  

                {

                    int a = (opcode >> 8) & 0xf;

                    unsigned v = (opcode & 0xff);

                    tcg_gen_ld_i32(REG(a), cpu_env,

                                   offsetof(CPUMoxieState, sregs[v]));

                }

                break;

            case 0x03:  

                {

                    int a = (opcode >> 8) & 0xf;

                    unsigned v = (opcode & 0xff);

                    tcg_gen_st_i32(REG(a), cpu_env,

                                   offsetof(CPUMoxieState, sregs[v]));

                }

                break;

            default:

                {

                    TCGv temp = tcg_temp_new_i32();

                    tcg_gen_movi_i32(cpu_pc, ctx->pc);

                    tcg_gen_movi_i32(temp, MOXIE_EX_BAD);

                    gen_helper_raise_exception(cpu_env, temp);

                    tcg_temp_free_i32(temp);

                }

                break;

            }

        }

    } else {

         

        int inst = opcode >> 8;

        switch (inst) {

        case 0x00:  

            break;

        case 0x01:  

            {

                int reg = (opcode >> 4) & 0xf;

                int val = cpu_ldl_code(env, ctx->pc+2);

                tcg_gen_movi_i32(REG(reg), val);

                length = 6;

            }

            break;

        case 0x02:  

            {

                int dest  = (opcode >> 4) & 0xf;

                int src = opcode & 0xf;

                tcg_gen_mov_i32(REG(dest), REG(src));

            }

            break;

        case 0x03:  

            {

                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();



                tcg_gen_movi_i32(t1, ctx->pc + 6);



                 

                tcg_gen_subi_i32(t2, REG(1), 8);

                tcg_gen_mov_i32(REG(1), t2);

                tcg_gen_qemu_st32(t1, REG(1), ctx->memidx);



                 

                tcg_gen_subi_i32(t2, REG(1), 4);

                tcg_gen_mov_i32(REG(1), t2);

                tcg_gen_qemu_st32(REG(0), REG(1), ctx->memidx);



                 

                tcg_gen_mov_i32(REG(0), REG(1));



                gen_goto_tb(env, ctx, 0, cpu_ldl_code(env, ctx->pc+2));



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                ctx->bstate = BS_BRANCH;

                length = 6;

            }

            break;

        case 0x04:  

            {

                TCGv t1 = tcg_temp_new_i32();



                 

                tcg_gen_mov_i32(REG(1), REG(0));



                 

                tcg_gen_qemu_ld32u(REG(0), REG(1), ctx->memidx);

                tcg_gen_addi_i32(t1, REG(1), 4);

                tcg_gen_mov_i32(REG(1), t1);





                 

                tcg_gen_qemu_ld32u(cpu_pc, REG(1), ctx->memidx);

                tcg_gen_addi_i32(t1, REG(1), 8);

                tcg_gen_mov_i32(REG(1), t1);



                tcg_temp_free_i32(t1);



                 

                tcg_gen_exit_tb(0);



                ctx->bstate = BS_BRANCH;

            }

            break;

        case 0x05:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_add_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x06:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                tcg_gen_subi_i32(t1, REG(a), 4);

                tcg_gen_mov_i32(REG(a), t1);

                tcg_gen_qemu_st32(REG(b), REG(a), ctx->memidx);

                tcg_temp_free_i32(t1);

            }

            break;

        case 0x07:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;

                TCGv t1 = tcg_temp_new_i32();



                tcg_gen_qemu_ld32u(REG(b), REG(a), ctx->memidx);

                tcg_gen_addi_i32(t1, REG(a), 4);

                tcg_gen_mov_i32(REG(a), t1);

                tcg_temp_free_i32(t1);

            }

            break;

        case 0x08:  

            {

                int reg = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld32u(REG(reg), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x09:  

            {

                int val = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st32(REG(val), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x0a:  

            {

                int src  = opcode & 0xf;

                int dest = (opcode >> 4) & 0xf;



                tcg_gen_qemu_ld32u(REG(dest), REG(src), ctx->memidx);

            }

            break;

        case 0x0b:  

            {

                int dest = (opcode >> 4) & 0xf;

                int val  = opcode & 0xf;



                tcg_gen_qemu_st32(REG(val), REG(dest), ctx->memidx);

            }

            break;

        case 0x0c:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld32u(t2, t1, ctx->memidx);

                tcg_gen_mov_i32(REG(a), t2);



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        case 0x0d:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st32(REG(b), t1, ctx->memidx);



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        case 0x0e:  

            {

                int a  = (opcode >> 4) & 0xf;

                int b  = opcode & 0xf;



                tcg_gen_mov_i32(cc_a, REG(a));

                tcg_gen_mov_i32(cc_b, REG(b));

            }

            break;

        case 0x19:  

            {

                int fnreg = (opcode >> 4) & 0xf;



                 

                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();



                tcg_gen_movi_i32(t1, ctx->pc+2);



                 

                tcg_gen_subi_i32(t2, REG(1), 8);

                tcg_gen_mov_i32(REG(1), t2);

                tcg_gen_qemu_st32(t1, REG(1), ctx->memidx);



                 

                tcg_gen_subi_i32(t2, REG(1), 4);

                tcg_gen_mov_i32(REG(1), t2);

                tcg_gen_qemu_st32(REG(0), REG(1), ctx->memidx);



                 

                tcg_gen_mov_i32(REG(0), REG(1));

                tcg_gen_mov_i32(cpu_pc, REG(fnreg));

                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);

                tcg_gen_exit_tb(0);

                ctx->bstate = BS_BRANCH;

            }

            break;

        case 0x1a:  

            {

                tcg_gen_movi_i32(cpu_pc, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_exit_tb(0);

                ctx->bstate = BS_BRANCH;

                length = 6;

            }

            break;

        case 0x1b:  

            {

                int reg = (opcode >> 4) & 0xf;

                int val = cpu_ldl_code(env, ctx->pc+2);

                tcg_gen_movi_i32(REG(reg), val);

                length = 6;

            }

            break;

        case 0x1c:  

            {

                int src  = opcode & 0xf;

                int dest = (opcode >> 4) & 0xf;



                tcg_gen_qemu_ld8u(REG(dest), REG(src), ctx->memidx);

            }

            break;

        case 0x1d:  

            {

                int reg = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld8u(REG(reg), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x1e:  

            {

                int dest = (opcode >> 4) & 0xf;

                int val  = opcode & 0xf;



                tcg_gen_qemu_st8(REG(val), REG(dest), ctx->memidx);

            }

            break;

        case 0x1f:  

            {

                int val = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st8(REG(val), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x20:  

            {

                int reg = (opcode >> 4) & 0xf;

                int val = cpu_ldl_code(env, ctx->pc+2);

                tcg_gen_movi_i32(REG(reg), val);

                length = 6;

            }

            break;

        case 0x21:  

            {

                int src  = opcode & 0xf;

                int dest = (opcode >> 4) & 0xf;



                tcg_gen_qemu_ld16u(REG(dest), REG(src), ctx->memidx);

            }

            break;

        case 0x22:  

            {

                int reg = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld16u(REG(reg), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x23:  

            {

                int dest = (opcode >> 4) & 0xf;

                int val  = opcode & 0xf;



                tcg_gen_qemu_st16(REG(val), REG(dest), ctx->memidx);

            }

            break;

        case 0x24:  

            {

                int val = (opcode >> 4) & 0xf;



                TCGv ptr = tcg_temp_new_i32();

                tcg_gen_movi_i32(ptr, cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st16(REG(val), ptr, ctx->memidx);

                tcg_temp_free_i32(ptr);



                length = 6;

            }

            break;

        case 0x25:  

            {

                int reg = (opcode >> 4) & 0xf;

                tcg_gen_mov_i32(cpu_pc, REG(reg));

                tcg_gen_exit_tb(0);

                ctx->bstate = BS_BRANCH;

            }

            break;

        case 0x26:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_and_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x27:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv sv = tcg_temp_new_i32();

                tcg_gen_andi_i32(sv, REG(b), 0x1f);

                tcg_gen_shr_i32(REG(a), REG(a), sv);

                tcg_temp_free_i32(sv);

            }

            break;

        case 0x28:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv sv = tcg_temp_new_i32();

                tcg_gen_andi_i32(sv, REG(b), 0x1f);

                tcg_gen_shl_i32(REG(a), REG(a), sv);

                tcg_temp_free_i32(sv);

            }

            break;

        case 0x29:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_sub_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x2a:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_neg_i32(REG(a), REG(b));

            }

            break;

        case 0x2b:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_or_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x2c:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_not_i32(REG(a), REG(b));

            }

            break;

        case 0x2d:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv sv = tcg_temp_new_i32();

                tcg_gen_andi_i32(sv, REG(b), 0x1f);

                tcg_gen_sar_i32(REG(a), REG(a), sv);

                tcg_temp_free_i32(sv);

            }

            break;

        case 0x2e:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_xor_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x2f:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                tcg_gen_mul_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x30:  

            {

                int val = cpu_ldl_code(env, ctx->pc+2);



                TCGv temp = tcg_temp_new_i32();

                tcg_gen_movi_i32(temp, val);

                tcg_gen_st_i32(temp, cpu_env,

                               offsetof(CPUMoxieState, sregs[3]));

                tcg_gen_movi_i32(cpu_pc, ctx->pc);

                tcg_gen_movi_i32(temp, MOXIE_EX_SWI);

                gen_helper_raise_exception(cpu_env, temp);

                tcg_temp_free_i32(temp);



                length = 6;

            }

            break;

        case 0x31:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;

                tcg_gen_movi_i32(cpu_pc, ctx->pc);

                gen_helper_div(REG(a), cpu_env, REG(a), REG(b));

            }

            break;

        case 0x32:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;

                tcg_gen_movi_i32(cpu_pc, ctx->pc);

                gen_helper_udiv(REG(a), cpu_env, REG(a), REG(b));

            }

            break;

        case 0x33:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;

                tcg_gen_rem_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x34:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;

                tcg_gen_remu_i32(REG(a), REG(a), REG(b));

            }

            break;

        case 0x35:  

            {

                TCGv temp = tcg_temp_new_i32();

                tcg_gen_movi_i32(cpu_pc, ctx->pc);

                tcg_gen_movi_i32(temp, MOXIE_EX_BREAK);

                gen_helper_raise_exception(cpu_env, temp);

                tcg_temp_free_i32(temp);

            }

            break;

        case 0x36:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld8u(t2, t1, ctx->memidx);

                tcg_gen_mov_i32(REG(a), t2);



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        case 0x37:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st8(REG(b), t1, ctx->memidx);



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        case 0x38:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(b), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_ld16u(t2, t1, ctx->memidx);

                tcg_gen_mov_i32(REG(a), t2);



                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        case 0x39:  

            {

                int a = (opcode >> 4) & 0xf;

                int b = opcode & 0xf;



                TCGv t1 = tcg_temp_new_i32();

                TCGv t2 = tcg_temp_new_i32();

                tcg_gen_addi_i32(t1, REG(a), cpu_ldl_code(env, ctx->pc+2));

                tcg_gen_qemu_st16(REG(b), t1, ctx->memidx);

                tcg_temp_free_i32(t1);

                tcg_temp_free_i32(t2);



                length = 6;

            }

            break;

        default:

            {

                TCGv temp = tcg_temp_new_i32();

                tcg_gen_movi_i32(cpu_pc, ctx->pc);

                tcg_gen_movi_i32(temp, MOXIE_EX_BAD);

                gen_helper_raise_exception(cpu_env, temp);

                tcg_temp_free_i32(temp);

             }

            break;

        }

    }



    return length;

}
