static void disas_simd_3same_int(DisasContext *s, uint32_t insn)

{

    int is_q = extract32(insn, 30, 1);

    int u = extract32(insn, 29, 1);

    int size = extract32(insn, 22, 2);

    int opcode = extract32(insn, 11, 5);

    int rm = extract32(insn, 16, 5);

    int rn = extract32(insn, 5, 5);

    int rd = extract32(insn, 0, 5);

    int pass;



    switch (opcode) {

    case 0x13:  

        if (u && size != 0) {

            unallocated_encoding(s);

            return;

        }

         

    case 0x0:  

    case 0x2:  

    case 0x4:  

    case 0xc:  

    case 0xd:  

    case 0xe:  

    case 0xf:  

    case 0x12:  

        if (size == 3) {

            unallocated_encoding(s);

            return;

        }

        break;

    case 0x16:  

        if (size == 0 || size == 3) {

            unallocated_encoding(s);

            return;

        }

        break;

    default:

        if (size == 3 && !is_q) {

            unallocated_encoding(s);

            return;

        }

        break;

    }



    if (!fp_access_check(s)) {

        return;

    }



    if (size == 3) {

        for (pass = 0; pass < (is_q ? 2 : 1); pass++) {

            TCGv_i64 tcg_op1 = tcg_temp_new_i64();

            TCGv_i64 tcg_op2 = tcg_temp_new_i64();

            TCGv_i64 tcg_res = tcg_temp_new_i64();



            read_vec_element(s, tcg_op1, rn, pass, MO_64);

            read_vec_element(s, tcg_op2, rm, pass, MO_64);



            handle_3same_64(s, opcode, u, tcg_res, tcg_op1, tcg_op2);



            write_vec_element(s, tcg_res, rd, pass, MO_64);



            tcg_temp_free_i64(tcg_res);

            tcg_temp_free_i64(tcg_op1);

            tcg_temp_free_i64(tcg_op2);

        }

    } else {

        for (pass = 0; pass < (is_q ? 4 : 2); pass++) {

            TCGv_i32 tcg_op1 = tcg_temp_new_i32();

            TCGv_i32 tcg_op2 = tcg_temp_new_i32();

            TCGv_i32 tcg_res = tcg_temp_new_i32();

            NeonGenTwoOpFn *genfn = NULL;

            NeonGenTwoOpEnvFn *genenvfn = NULL;



            read_vec_element_i32(s, tcg_op1, rn, pass, MO_32);

            read_vec_element_i32(s, tcg_op2, rm, pass, MO_32);



            switch (opcode) {

            case 0x0:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_hadd_s8, gen_helper_neon_hadd_u8 },

                    { gen_helper_neon_hadd_s16, gen_helper_neon_hadd_u16 },

                    { gen_helper_neon_hadd_s32, gen_helper_neon_hadd_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x1:  

            {

                static NeonGenTwoOpEnvFn * const fns[3][2] = {

                    { gen_helper_neon_qadd_s8, gen_helper_neon_qadd_u8 },

                    { gen_helper_neon_qadd_s16, gen_helper_neon_qadd_u16 },

                    { gen_helper_neon_qadd_s32, gen_helper_neon_qadd_u32 },

                };

                genenvfn = fns[size][u];

                break;

            }

            case 0x2:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_rhadd_s8, gen_helper_neon_rhadd_u8 },

                    { gen_helper_neon_rhadd_s16, gen_helper_neon_rhadd_u16 },

                    { gen_helper_neon_rhadd_s32, gen_helper_neon_rhadd_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x4:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_hsub_s8, gen_helper_neon_hsub_u8 },

                    { gen_helper_neon_hsub_s16, gen_helper_neon_hsub_u16 },

                    { gen_helper_neon_hsub_s32, gen_helper_neon_hsub_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x5:  

            {

                static NeonGenTwoOpEnvFn * const fns[3][2] = {

                    { gen_helper_neon_qsub_s8, gen_helper_neon_qsub_u8 },

                    { gen_helper_neon_qsub_s16, gen_helper_neon_qsub_u16 },

                    { gen_helper_neon_qsub_s32, gen_helper_neon_qsub_u32 },

                };

                genenvfn = fns[size][u];

                break;

            }

            case 0x6:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_cgt_s8, gen_helper_neon_cgt_u8 },

                    { gen_helper_neon_cgt_s16, gen_helper_neon_cgt_u16 },

                    { gen_helper_neon_cgt_s32, gen_helper_neon_cgt_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x7:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_cge_s8, gen_helper_neon_cge_u8 },

                    { gen_helper_neon_cge_s16, gen_helper_neon_cge_u16 },

                    { gen_helper_neon_cge_s32, gen_helper_neon_cge_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x8:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_shl_s8, gen_helper_neon_shl_u8 },

                    { gen_helper_neon_shl_s16, gen_helper_neon_shl_u16 },

                    { gen_helper_neon_shl_s32, gen_helper_neon_shl_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x9:  

            {

                static NeonGenTwoOpEnvFn * const fns[3][2] = {

                    { gen_helper_neon_qshl_s8, gen_helper_neon_qshl_u8 },

                    { gen_helper_neon_qshl_s16, gen_helper_neon_qshl_u16 },

                    { gen_helper_neon_qshl_s32, gen_helper_neon_qshl_u32 },

                };

                genenvfn = fns[size][u];

                break;

            }

            case 0xa:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_rshl_s8, gen_helper_neon_rshl_u8 },

                    { gen_helper_neon_rshl_s16, gen_helper_neon_rshl_u16 },

                    { gen_helper_neon_rshl_s32, gen_helper_neon_rshl_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0xb:  

            {

                static NeonGenTwoOpEnvFn * const fns[3][2] = {

                    { gen_helper_neon_qrshl_s8, gen_helper_neon_qrshl_u8 },

                    { gen_helper_neon_qrshl_s16, gen_helper_neon_qrshl_u16 },

                    { gen_helper_neon_qrshl_s32, gen_helper_neon_qrshl_u32 },

                };

                genenvfn = fns[size][u];

                break;

            }

            case 0xc:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_max_s8, gen_helper_neon_max_u8 },

                    { gen_helper_neon_max_s16, gen_helper_neon_max_u16 },

                    { gen_max_s32, gen_max_u32 },

                };

                genfn = fns[size][u];

                break;

            }



            case 0xd:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_min_s8, gen_helper_neon_min_u8 },

                    { gen_helper_neon_min_s16, gen_helper_neon_min_u16 },

                    { gen_min_s32, gen_min_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0xe:  

            case 0xf:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_abd_s8, gen_helper_neon_abd_u8 },

                    { gen_helper_neon_abd_s16, gen_helper_neon_abd_u16 },

                    { gen_helper_neon_abd_s32, gen_helper_neon_abd_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x10:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_add_u8, gen_helper_neon_sub_u8 },

                    { gen_helper_neon_add_u16, gen_helper_neon_sub_u16 },

                    { tcg_gen_add_i32, tcg_gen_sub_i32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x11:  

            {

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_tst_u8, gen_helper_neon_ceq_u8 },

                    { gen_helper_neon_tst_u16, gen_helper_neon_ceq_u16 },

                    { gen_helper_neon_tst_u32, gen_helper_neon_ceq_u32 },

                };

                genfn = fns[size][u];

                break;

            }

            case 0x13:  

                if (u) {

                     

                    assert(size == 0);

                    genfn = gen_helper_neon_mul_p8;

                    break;

                }

                 

            case 0x12:  

            {

                static NeonGenTwoOpFn * const fns[3] = {

                    gen_helper_neon_mul_u8,

                    gen_helper_neon_mul_u16,

                    tcg_gen_mul_i32,

                };

                genfn = fns[size];

                break;

            }

            case 0x16:  

            {

                static NeonGenTwoOpEnvFn * const fns[2][2] = {

                    { gen_helper_neon_qdmulh_s16, gen_helper_neon_qrdmulh_s16 },

                    { gen_helper_neon_qdmulh_s32, gen_helper_neon_qrdmulh_s32 },

                };

                assert(size == 1 || size == 2);

                genenvfn = fns[size - 1][u];

                break;

            }

            default:

                g_assert_not_reached();

            }



            if (genenvfn) {

                genenvfn(tcg_res, cpu_env, tcg_op1, tcg_op2);

            } else {

                genfn(tcg_res, tcg_op1, tcg_op2);

            }



            if (opcode == 0xf || opcode == 0x12) {

                 

                static NeonGenTwoOpFn * const fns[3][2] = {

                    { gen_helper_neon_add_u8, gen_helper_neon_sub_u8 },

                    { gen_helper_neon_add_u16, gen_helper_neon_sub_u16 },

                    { tcg_gen_add_i32, tcg_gen_sub_i32 },

                };

                bool is_sub = (opcode == 0x12 && u);  



                genfn = fns[size][is_sub];

                read_vec_element_i32(s, tcg_op1, rd, pass, MO_32);

                genfn(tcg_res, tcg_op1, tcg_res);

            }



            write_vec_element_i32(s, tcg_res, rd, pass, MO_32);



            tcg_temp_free_i32(tcg_res);

            tcg_temp_free_i32(tcg_op1);

            tcg_temp_free_i32(tcg_op2);

        }

    }



    if (!is_q) {

        clear_vec_high(s, rd);

    }

}
