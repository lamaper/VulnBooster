static int get_physical_address (CPUState *env, target_ulong *physical,

                                int *prot, target_ulong address,

                                int rw, int access_type)

{

     

    int user_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_UM;

    int supervisor_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_SM;

    int kernel_mode = !user_mode && !supervisor_mode;


    int UX = (env->CP0_Status & (1 << CP0St_UX)) != 0;

    int SX = (env->CP0_Status & (1 << CP0St_SX)) != 0;

    int KX = (env->CP0_Status & (1 << CP0St_KX)) != 0;


    int ret = TLBRET_MATCH;


    if (logfile) {

        fprintf(logfile, "user mode %d h %08x\n",

                user_mode, env->hflags);

    }




    if (address <= (int32_t)0x7FFFFFFFUL) {

         

        if (env->CP0_Status & (1 << CP0St_ERL)) {

            *physical = address & 0xFFFFFFFF;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

        }


    } else if (address < 0x4000000000000000ULL) {

         

	if (UX && address < (0x3FFFFFFFFFFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

	} else {

	    ret = TLBRET_BADADDR;

        }

    } else if (address < 0x8000000000000000ULL) {

         

	if ((supervisor_mode || kernel_mode) &&

	    SX && address < (0x7FFFFFFFFFFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

	} else {

	    ret = TLBRET_BADADDR;

        }

    } else if (address < 0xC000000000000000ULL) {

         

         

        if (kernel_mode && KX &&

            (address & 0x07FFFFFFFFFFFFFFULL) < 0x0000000FFFFFFFFFULL) {

            *physical = address & 0x0000000FFFFFFFFFULL;

            *prot = PAGE_READ | PAGE_WRITE;

	} else {

	    ret = TLBRET_BADADDR;

	}

    } else if (address < 0xFFFFFFFF80000000ULL) {

         

	if (kernel_mode && KX &&

	    address < (0xFFFFFFFF7FFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

	} else {

	    ret = TLBRET_BADADDR;

	}


    } else if (address < (int32_t)0xA0000000UL) {

         

        if (kernel_mode) {

            *physical = address - (int32_t)0x80000000UL;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < (int32_t)0xC0000000UL) {

         

        if (kernel_mode) {

            *physical = address - (int32_t)0xA0000000UL;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < (int32_t)0xE0000000UL) {

         

        if (supervisor_mode || kernel_mode) {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    } else {

         

         

        if (kernel_mode) {

            ret = env->tlb->map_address(env, physical, prot, address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    }


    if (logfile) {

        fprintf(logfile, TARGET_FMT_lx " %d %d => " TARGET_FMT_lx " %d (%d)\n",

		address, rw, access_type, *physical, *prot, ret);

    }




    return ret;

}
