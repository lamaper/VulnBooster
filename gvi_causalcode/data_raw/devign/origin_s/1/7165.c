uint64_t helper_ld_asi(target_ulong addr, int asi, int size, int sign)

{

    uint64_t ret = 0;


    target_ulong last_addr = addr;




    asi &= 0xff;



    if ((asi < 0x80 && (env->pstate & PS_PRIV) == 0)

        || ((env->def->features & CPU_FEATURE_HYPV)

            && asi >= 0x30 && asi < 0x80

            && !(env->hpstate & HS_PRIV)))

        raise_exception(TT_PRIV_ACT);



    helper_check_align(addr, size - 1);

    switch (asi) {

    case 0x82:  

    case 0x8a:  

    case 0x83:  

    case 0x8b:  

        {

             

            int access_mmu_idx = ( asi & 1 ) ? MMU_KERNEL_IDX

                                             : MMU_KERNEL_SECONDARY_IDX;



            if (cpu_get_phys_page_nofault(env, addr, access_mmu_idx) == -1ULL) {


                dump_asi("read ", last_addr, asi, size, ret);


                return 0;

            }

        }

         

    case 0x10:  

    case 0x11:  

    case 0x18:  

    case 0x19:  

    case 0x80:  

    case 0x81:  

    case 0x88:  

    case 0x89:  

    case 0xe2:  

    case 0xe3:  

        if ((asi & 0x80) && (env->pstate & PS_PRIV)) {

            if ((env->def->features & CPU_FEATURE_HYPV)

                && env->hpstate & HS_PRIV) {

                switch(size) {

                case 1:

                    ret = ldub_hypv(addr);

                    break;

                case 2:

                    ret = lduw_hypv(addr);

                    break;

                case 4:

                    ret = ldl_hypv(addr);

                    break;

                default:

                case 8:

                    ret = ldq_hypv(addr);

                    break;

                }

            } else {

                 

                if (asi & 1) {

                    switch(size) {

                    case 1:

                        ret = ldub_kernel_secondary(addr);

                        break;

                    case 2:

                        ret = lduw_kernel_secondary(addr);

                        break;

                    case 4:

                        ret = ldl_kernel_secondary(addr);

                        break;

                    default:

                    case 8:

                        ret = ldq_kernel_secondary(addr);

                        break;

                    }

                } else {

                    switch(size) {

                    case 1:

                        ret = ldub_kernel(addr);

                        break;

                    case 2:

                        ret = lduw_kernel(addr);

                        break;

                    case 4:

                        ret = ldl_kernel(addr);

                        break;

                    default:

                    case 8:

                        ret = ldq_kernel(addr);

                        break;

                    }

                }

            }

        } else {

             

            if (asi & 1) {

                switch(size) {

                case 1:

                    ret = ldub_user_secondary(addr);

                    break;

                case 2:

                    ret = lduw_user_secondary(addr);

                    break;

                case 4:

                    ret = ldl_user_secondary(addr);

                    break;

                default:

                case 8:

                    ret = ldq_user_secondary(addr);

                    break;

                }

            } else {

                switch(size) {

                case 1:

                    ret = ldub_user(addr);

                    break;

                case 2:

                    ret = lduw_user(addr);

                    break;

                case 4:

                    ret = ldl_user(addr);

                    break;

                default:

                case 8:

                    ret = ldq_user(addr);

                    break;

                }

            }

        }

        break;

    case 0x14:  

    case 0x15:  

    case 0x1c:  

    case 0x1d:  

        {

            switch(size) {

            case 1:

                ret = ldub_phys(addr);

                break;

            case 2:

                ret = lduw_phys(addr);

                break;

            case 4:

                ret = ldl_phys(addr);

                break;

            default:

            case 8:

                ret = ldq_phys(addr);

                break;

            }

            break;

        }

    case 0x24:  

    case 0x2c:  

         

        raise_exception(TT_ILL_INSN);

        return 0;

    case 0x04:  

    case 0x0c:  

    {

        switch(size) {

        case 1:

            ret = ldub_nucleus(addr);

            break;

        case 2:

            ret = lduw_nucleus(addr);

            break;

        case 4:

            ret = ldl_nucleus(addr);

            break;

        default:

        case 8:

            ret = ldq_nucleus(addr);

            break;

        }

        break;

    }

    case 0x4a:  

         

        break;

    case 0x45:  

        ret = env->lsu;

        break;

    case 0x50:  

        {

            int reg = (addr >> 3) & 0xf;



            if (reg == 0) {

                 

                ret = ultrasparc_tag_target(env->immu.tag_access);

            } else {

                ret = env->immuregs[reg];

            }



            break;

        }

    case 0x51:  

        {

             

             

            ret = ultrasparc_tsb_pointer(env->immu.tsb, env->immu.tag_access,

                                         8*1024);

            break;

        }

    case 0x52:  

        {

             

             

            ret = ultrasparc_tsb_pointer(env->immu.tsb, env->immu.tag_access,

                                         64*1024);

            break;

        }

    case 0x55:  

        {

            int reg = (addr >> 3) & 0x3f;



            ret = env->itlb[reg].tte;

            break;

        }

    case 0x56:  

        {

            int reg = (addr >> 3) & 0x3f;



            ret = env->itlb[reg].tag;

            break;

        }

    case 0x58:  

        {

            int reg = (addr >> 3) & 0xf;



            if (reg == 0) {

                 

                ret = ultrasparc_tag_target(env->dmmu.tag_access);

            } else {

                ret = env->dmmuregs[reg];

            }

            break;

        }

    case 0x59:  

        {

             

             

            ret = ultrasparc_tsb_pointer(env->dmmu.tsb, env->dmmu.tag_access,

                                         8*1024);

            break;

        }

    case 0x5a:  

        {

             

             

            ret = ultrasparc_tsb_pointer(env->dmmu.tsb, env->dmmu.tag_access,

                                         64*1024);

            break;

        }

    case 0x5d:  

        {

            int reg = (addr >> 3) & 0x3f;



            ret = env->dtlb[reg].tte;

            break;

        }

    case 0x5e:  

        {

            int reg = (addr >> 3) & 0x3f;



            ret = env->dtlb[reg].tag;

            break;

        }

    case 0x46:  

    case 0x47:  

    case 0x4b:  

    case 0x4c:  

    case 0x4d:  

    case 0x4e:  

    case 0x66:  

    case 0x67:  

    case 0x6e:  

    case 0x6f:  

    case 0x76:  

    case 0x7e:  

        break;

    case 0x5b:  

    case 0x48:  

    case 0x49:  

    case 0x7f:  

         

        break;

    case 0x54:  

    case 0x57:  

    case 0x5c:  

    case 0x5f:  

    case 0x77:  

    default:

        do_unassigned_access(addr, 0, 0, 1, size);

        ret = 0;

        break;

    }



     

    switch (asi) {

    case 0x0c:  

    case 0x18:  

    case 0x19:  

    case 0x1c:  

    case 0x1d:  

    case 0x88:  

    case 0x89:  

    case 0x8a:  

    case 0x8b:  

        switch(size) {

        case 2:

            ret = bswap16(ret);

            break;

        case 4:

            ret = bswap32(ret);

            break;

        case 8:

            ret = bswap64(ret);

            break;

        default:

            break;

        }

    default:

        break;

    }



     

    if (sign) {

        switch(size) {

        case 1:

            ret = (int8_t) ret;

            break;

        case 2:

            ret = (int16_t) ret;

            break;

        case 4:

            ret = (int32_t) ret;

            break;

        default:

            break;

        }

    }


    dump_asi("read ", last_addr, asi, size, ret);


    return ret;

}
