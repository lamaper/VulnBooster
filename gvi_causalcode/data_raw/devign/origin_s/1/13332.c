void helper_st_asi(target_ulong addr, target_ulong val, int asi, int size)

{


    dump_asi("write", addr, asi, size, val);




    asi &= 0xff;



    if ((asi < 0x80 && (env->pstate & PS_PRIV) == 0)

        || ((env->def->features & CPU_FEATURE_HYPV)

            && asi >= 0x30 && asi < 0x80

            && !(env->hpstate & HS_PRIV)))

        raise_exception(TT_PRIV_ACT);



    helper_check_align(addr, size - 1);

     

    switch (asi) {

    case 0x0c:  

    case 0x18:  

    case 0x19:  

    case 0x1c:  

    case 0x1d:  

    case 0x88:  

    case 0x89:  

        switch(size) {

        case 2:

            val = bswap16(val);

            break;

        case 4:

            val = bswap32(val);

            break;

        case 8:

            val = bswap64(val);

            break;

        default:

            break;

        }

    default:

        break;

    }



    switch(asi) {

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

                    stb_hypv(addr, val);

                    break;

                case 2:

                    stw_hypv(addr, val);

                    break;

                case 4:

                    stl_hypv(addr, val);

                    break;

                case 8:

                default:

                    stq_hypv(addr, val);

                    break;

                }

            } else {

                 

                if (asi & 1) {

                    switch(size) {

                    case 1:

                        stb_kernel_secondary(addr, val);

                        break;

                    case 2:

                        stw_kernel_secondary(addr, val);

                        break;

                    case 4:

                        stl_kernel_secondary(addr, val);

                        break;

                    case 8:

                    default:

                        stq_kernel_secondary(addr, val);

                        break;

                    }

                } else {

                    switch(size) {

                    case 1:

                        stb_kernel(addr, val);

                        break;

                    case 2:

                        stw_kernel(addr, val);

                        break;

                    case 4:

                        stl_kernel(addr, val);

                        break;

                    case 8:

                    default:

                        stq_kernel(addr, val);

                        break;

                    }

                }

            }

        } else {

             

            if (asi & 1) {

                switch(size) {

                case 1:

                    stb_user_secondary(addr, val);

                    break;

                case 2:

                    stw_user_secondary(addr, val);

                    break;

                case 4:

                    stl_user_secondary(addr, val);

                    break;

                case 8:

                default:

                    stq_user_secondary(addr, val);

                    break;

                }

            } else {

                switch(size) {

                case 1:

                    stb_user(addr, val);

                    break;

                case 2:

                    stw_user(addr, val);

                    break;

                case 4:

                    stl_user(addr, val);

                    break;

                case 8:

                default:

                    stq_user(addr, val);

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

                stb_phys(addr, val);

                break;

            case 2:

                stw_phys(addr, val);

                break;

            case 4:

                stl_phys(addr, val);

                break;

            case 8:

            default:

                stq_phys(addr, val);

                break;

            }

        }

        return;

    case 0x24:  

    case 0x2c:  

         

        raise_exception(TT_ILL_INSN);

        return;

    case 0x04:  

    case 0x0c:  

    {

        switch(size) {

        case 1:

            stb_nucleus(addr, val);

            break;

        case 2:

            stw_nucleus(addr, val);

            break;

        case 4:

            stl_nucleus(addr, val);

            break;

        default:

        case 8:

            stq_nucleus(addr, val);

            break;

        }

        break;

    }



    case 0x4a:  

         

        return;

    case 0x45:  

        {

            uint64_t oldreg;



            oldreg = env->lsu;

            env->lsu = val & (DMMU_E | IMMU_E);

             

             

            if (oldreg != env->lsu) {

                DPRINTF_MMU("LSU change: 0x%" PRIx64 " -> 0x%" PRIx64 "\n",

                            oldreg, env->lsu);


                dump_mmu(env);


                tlb_flush(env, 1);

            }

            return;

        }

    case 0x50:  

        {

            int reg = (addr >> 3) & 0xf;

            uint64_t oldreg;



            oldreg = env->immuregs[reg];

            switch(reg) {

            case 0:  

                return;

            case 1:  

            case 2:

                return;

            case 3:  

                if ((val & 1) == 0)

                    val = 0;  

                env->immu.sfsr = val;

                break;

            case 4:  

                return;

            case 5:  

                DPRINTF_MMU("immu TSB write: 0x%016" PRIx64 " -> 0x%016"

                            PRIx64 "\n", env->immu.tsb, val);

                env->immu.tsb = val;

                break;

            case 6:  

                env->immu.tag_access = val;

                break;

            case 7:

            case 8:

                return;

            default:

                break;

            }



            if (oldreg != env->immuregs[reg]) {

                DPRINTF_MMU("immu change reg[%d]: 0x%016" PRIx64 " -> 0x%016"

                            PRIx64 "\n", reg, oldreg, env->immuregs[reg]);

            }


            dump_mmu(env);


            return;

        }

    case 0x54:  

        replace_tlb_1bit_lru(env->itlb, env->immu.tag_access, val, "immu", env);

        return;

    case 0x55:  

        {

             



            unsigned int i = (addr >> 3) & 0x3f;



            replace_tlb_entry(&env->itlb[i], env->immu.tag_access, val, env);


            DPRINTF_MMU("immu data access replaced entry [%i]\n", i);

            dump_mmu(env);


            return;

        }

    case 0x57:  

        demap_tlb(env->itlb, addr, "immu", env);

        return;

    case 0x58:  

        {

            int reg = (addr >> 3) & 0xf;

            uint64_t oldreg;



            oldreg = env->dmmuregs[reg];

            switch(reg) {

            case 0:  

            case 4:

                return;

            case 3:  

                if ((val & 1) == 0) {

                    val = 0;  

                    env->dmmu.sfar = 0;

                }

                env->dmmu.sfsr = val;

                break;

            case 1:  

                env->dmmu.mmu_primary_context = val;

                break;

            case 2:  

                env->dmmu.mmu_secondary_context = val;

                break;

            case 5:  

                DPRINTF_MMU("dmmu TSB write: 0x%016" PRIx64 " -> 0x%016"

                            PRIx64 "\n", env->dmmu.tsb, val);

                env->dmmu.tsb = val;

                break;

            case 6:  

                env->dmmu.tag_access = val;

                break;

            case 7:  

            case 8:  

            default:

                env->dmmuregs[reg] = val;

                break;

            }



            if (oldreg != env->dmmuregs[reg]) {

                DPRINTF_MMU("dmmu change reg[%d]: 0x%016" PRIx64 " -> 0x%016"

                            PRIx64 "\n", reg, oldreg, env->dmmuregs[reg]);

            }


            dump_mmu(env);


            return;

        }

    case 0x5c:  

        replace_tlb_1bit_lru(env->dtlb, env->dmmu.tag_access, val, "dmmu", env);

        return;

    case 0x5d:  

        {

            unsigned int i = (addr >> 3) & 0x3f;



            replace_tlb_entry(&env->dtlb[i], env->dmmu.tag_access, val, env);


            DPRINTF_MMU("dmmu data access replaced entry [%i]\n", i);

            dump_mmu(env);


            return;

        }

    case 0x5f:  

        demap_tlb(env->dtlb, addr, "dmmu", env);

        return;

    case 0x49:  

         

        return;

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

        return;

    case 0x51:  

    case 0x52:  

    case 0x56:  

    case 0x59:  

    case 0x5a:  

    case 0x5b:  

    case 0x5e:  

    case 0x48:  

    case 0x7f:  

    case 0x82:  

    case 0x83:  

    case 0x8a:  

    case 0x8b:  

    default:

        do_unassigned_access(addr, 1, 0, 1, size);

        return;

    }

}
