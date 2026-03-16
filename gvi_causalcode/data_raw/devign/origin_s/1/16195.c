void HELPER(set_cp15)(CPUState *env, uint32_t insn, uint32_t val)

{

    int op1;

    int op2;

    int crm;



    op1 = (insn >> 21) & 7;

    op2 = (insn >> 5) & 7;

    crm = insn & 0xf;

    switch ((insn >> 16) & 0xf) {

    case 0:

         

        if (arm_feature(env, ARM_FEATURE_XSCALE))

            break;

        if (arm_feature(env, ARM_FEATURE_OMAPCP))

            break;

        if (arm_feature(env, ARM_FEATURE_V7)

                && op1 == 2 && crm == 0 && op2 == 0) {

            env->cp15.c0_cssel = val & 0xf;

            break;

        }

        goto bad_reg;

    case 1:  

        if (arm_feature(env, ARM_FEATURE_V7)

                && op1 == 0 && crm == 1 && op2 == 0) {

            env->cp15.c1_scr = val;

            break;

        }

        if (arm_feature(env, ARM_FEATURE_OMAPCP))

            op2 = 0;

        switch (op2) {

        case 0:

            if (!arm_feature(env, ARM_FEATURE_XSCALE) || crm == 0)

                env->cp15.c1_sys = val;

             

             

            tlb_flush(env, 1);

            break;

        case 1:  

            if (arm_feature(env, ARM_FEATURE_XSCALE)) {

                env->cp15.c1_xscaleauxcr = val;

                break;

            }

             

            break;

        case 2:

            if (arm_feature(env, ARM_FEATURE_XSCALE))

                goto bad_reg;

            if (env->cp15.c1_coproc != val) {

                env->cp15.c1_coproc = val;

                 

                tb_flush(env);

            }

            break;

        default:

            goto bad_reg;

        }

        break;

    case 2:  

        if (arm_feature(env, ARM_FEATURE_MPU)) {

            switch (op2) {

            case 0:

                env->cp15.c2_data = val;

                break;

            case 1:

                env->cp15.c2_insn = val;

                break;

            default:

                goto bad_reg;

            }

        } else {

	    switch (op2) {

	    case 0:

		env->cp15.c2_base0 = val;

		break;

	    case 1:

		env->cp15.c2_base1 = val;

		break;

	    case 2:

                val &= 7;

                env->cp15.c2_control = val;

		env->cp15.c2_mask = ~(((uint32_t)0xffffffffu) >> val);

                env->cp15.c2_base_mask = ~((uint32_t)0x3fffu >> val);

		break;

	    default:

		goto bad_reg;

	    }

        }

        break;

    case 3:  

        env->cp15.c3 = val;

        tlb_flush(env, 1);  

        break;

    case 4:  

        goto bad_reg;

    case 5:  

        if (arm_feature(env, ARM_FEATURE_OMAPCP))

            op2 = 0;

        switch (op2) {

        case 0:

            if (arm_feature(env, ARM_FEATURE_MPU))

                val = extended_mpu_ap_bits(val);

            env->cp15.c5_data = val;

            break;

        case 1:

            if (arm_feature(env, ARM_FEATURE_MPU))

                val = extended_mpu_ap_bits(val);

            env->cp15.c5_insn = val;

            break;

        case 2:

            if (!arm_feature(env, ARM_FEATURE_MPU))

                goto bad_reg;

            env->cp15.c5_data = val;

            break;

        case 3:

            if (!arm_feature(env, ARM_FEATURE_MPU))

                goto bad_reg;

            env->cp15.c5_insn = val;

            break;

        default:

            goto bad_reg;

        }

        break;

    case 6:  

        if (arm_feature(env, ARM_FEATURE_MPU)) {

            if (crm >= 8)

                goto bad_reg;

            env->cp15.c6_region[crm] = val;

        } else {

            if (arm_feature(env, ARM_FEATURE_OMAPCP))

                op2 = 0;

            switch (op2) {

            case 0:

                env->cp15.c6_data = val;

                break;

            case 1:  

            case 2:

                env->cp15.c6_insn = val;

                break;

            default:

                goto bad_reg;

            }

        }

        break;

    case 7:  

        env->cp15.c15_i_max = 0x000;

        env->cp15.c15_i_min = 0xff0;

        if (op1 != 0) {

            goto bad_reg;

        }

         

        if (arm_feature(env, ARM_FEATURE_VAPA)) {

            switch (crm) {

            case 4:

                if (arm_feature(env, ARM_FEATURE_V7)) {

                    env->cp15.c7_par = val & 0xfffff6ff;

                } else {

                    env->cp15.c7_par = val & 0xfffff1ff;

                }

                break;

            case 8: {

                uint32_t phys_addr;

                target_ulong page_size;

                int prot;

                int ret, is_user = op2 & 2;

                int access_type = op2 & 1;



                if (op2 & 4) {

                     

                    goto bad_reg;

                }

                ret = get_phys_addr(env, val, access_type, is_user,

                                    &phys_addr, &prot, &page_size);

                if (ret == 0) {

                     

                    if (page_size == (1 << 24)

                        && arm_feature(env, ARM_FEATURE_V7)) {

                        env->cp15.c7_par = (phys_addr & 0xff000000) | 1 << 1;

                    } else {

                        env->cp15.c7_par = phys_addr & 0xfffff000;

                    }

                } else {

                    env->cp15.c7_par = ((ret & (10 << 1)) >> 5) |

                                       ((ret & (12 << 1)) >> 6) |

                                       ((ret & 0xf) << 1) | 1;

                }

                break;

            }

            }

        }

        break;

    case 8:  

        switch (op2) {

        case 0:  

            tlb_flush(env, 0);

            break;

        case 1:  

            tlb_flush_page(env, val & TARGET_PAGE_MASK);

            break;

        case 2:  

            tlb_flush(env, val == 0);

            break;

        case 3:  

             

            tlb_flush(env, 1);

            break;

        default:

            goto bad_reg;

        }

        break;

    case 9:

        if (arm_feature(env, ARM_FEATURE_OMAPCP))

            break;

        if (arm_feature(env, ARM_FEATURE_STRONGARM))

            break;  

        switch (crm) {

        case 0:  

	    switch (op1) {

	    case 0:  

		switch (op2) {

		case 0:

		    env->cp15.c9_data = val;

		    break;

		case 1:

		    env->cp15.c9_insn = val;

		    break;

		default:

		    goto bad_reg;

		}

		break;

	    case 1:  

		 

		break;

	    default:

		goto bad_reg;

	    }

	    break;

        case 1:  

             

            goto bad_reg;

        case 12:  

             

            if (!arm_feature(env, ARM_FEATURE_V7)) {

                goto bad_reg;

            }

            switch (op2) {

            case 0:  

                 

                env->cp15.c9_pmcr &= ~0x39;

                env->cp15.c9_pmcr |= (val & 0x39);

                break;

            case 1:  

                val &= (1 << 31);

                env->cp15.c9_pmcnten |= val;

                break;

            case 2:  

                val &= (1 << 31);

                env->cp15.c9_pmcnten &= ~val;

                break;

            case 3:  

                env->cp15.c9_pmovsr &= ~val;

                break;

            case 4:  

                 

                break;

            case 5:  

                 

                break;

            default:

                goto bad_reg;

            }

            break;

        case 13:  

            if (!arm_feature(env, ARM_FEATURE_V7)) {

                goto bad_reg;

            }

            switch (op2) {

            case 0:  

                break;

            case 1:  

                env->cp15.c9_pmxevtyper = val & 0xff;

                break;

            case 2:  

                 

                break;

            default:

                goto bad_reg;

            }

            break;

        case 14:  

            if (!arm_feature(env, ARM_FEATURE_V7)) {

                goto bad_reg;

            }

            switch (op2) {

            case 0:  

                env->cp15.c9_pmuserenr = val & 1;

                 

                tb_flush(env);

                break;

            case 1:  

                 

                val &= (1 << 31);

                env->cp15.c9_pminten |= val;

                break;

            case 2:  

                val &= (1 << 31);

                env->cp15.c9_pminten &= ~val;

                break;

            }

            break;

        default:

            goto bad_reg;

        }

        break;

    case 10:  

         

        break;

    case 12:  

        goto bad_reg;

    case 13:  

        switch (op2) {

        case 0:

             

            if (env->cp15.c13_fcse != val)

              tlb_flush(env, 1);

            env->cp15.c13_fcse = val;

            break;

        case 1:

             

            if (env->cp15.c13_context != val

                && !arm_feature(env, ARM_FEATURE_MPU))

              tlb_flush(env, 0);

            env->cp15.c13_context = val;

            break;

        default:

            goto bad_reg;

        }

        break;

    case 14:  

        goto bad_reg;

    case 15:  

        if (arm_feature(env, ARM_FEATURE_XSCALE)) {

            if (op2 == 0 && crm == 1) {

                if (env->cp15.c15_cpar != (val & 0x3fff)) {

                     

                    tb_flush(env);

                    env->cp15.c15_cpar = val & 0x3fff;

                }

                break;

            }

            goto bad_reg;

        }

        if (arm_feature(env, ARM_FEATURE_OMAPCP)) {

            switch (crm) {

            case 0:

                break;

            case 1:  

                env->cp15.c15_ticonfig = val & 0xe7;

                env->cp15.c0_cpuid = (val & (1 << 5)) ?  

                        ARM_CPUID_TI915T : ARM_CPUID_TI925T;

                break;

            case 2:  

                env->cp15.c15_i_max = val;

                break;

            case 3:  

                env->cp15.c15_i_min = val;

                break;

            case 4:  

                env->cp15.c15_threadid = val & 0xffff;

                break;

            case 8:  

                cpu_interrupt(env, CPU_INTERRUPT_HALT);

                break;

            default:

                goto bad_reg;

            }

        }

        if (ARM_CPUID(env) == ARM_CPUID_CORTEXA9) {

            switch (crm) {

            case 0:

                if ((op1 == 0) && (op2 == 0)) {

                    env->cp15.c15_power_control = val;

                } else if ((op1 == 0) && (op2 == 1)) {

                    env->cp15.c15_diagnostic = val;

                } else if ((op1 == 0) && (op2 == 2)) {

                    env->cp15.c15_power_diagnostic = val;

                }

            default:

                break;

            }

        }

        break;

    }

    return;

bad_reg:

     

    cpu_abort(env, "Unimplemented cp15 register write (c%d, c%d, {%d, %d})\n",

              (insn >> 16) & 0xf, crm, op1, op2);

}
