static int get_physical_address (CPUMIPSState *env, hwaddr *physical,

                                int *prot, target_ulong real_address,

                                int rw, int access_type)

{

     

    int user_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_UM;

    int supervisor_mode = (env->hflags & MIPS_HFLAG_MODE) == MIPS_HFLAG_SM;

    int kernel_mode = !user_mode && !supervisor_mode;


    int UX = (env->CP0_Status & (1 << CP0St_UX)) != 0;

    int SX = (env->CP0_Status & (1 << CP0St_SX)) != 0;

    int KX = (env->CP0_Status & (1 << CP0St_KX)) != 0;


    int ret = TLBRET_MATCH;

     

    target_ulong address = real_address;










    if (kvm_enabled()) {

         

        if (real_address >= KVM_KSEG0_BASE) {

            if (real_address < KVM_KSEG2_BASE) {

                 

                address += KSEG0_BASE - KVM_KSEG0_BASE;

            } else if (real_address <= USEG_LIMIT) {

                 

                address += KSEG2_BASE - KVM_KSEG2_BASE;

            }

        }

    }



    if (address <= USEG_LIMIT) {

         

        if (env->CP0_Status & (1 << CP0St_ERL)) {

            *physical = address & 0xFFFFFFFF;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        }


    } else if (address < 0x4000000000000000ULL) {

         

        if (UX && address <= (0x3FFFFFFFFFFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < 0x8000000000000000ULL) {

         

        if ((supervisor_mode || kernel_mode) &&

            SX && address <= (0x7FFFFFFFFFFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < 0xC000000000000000ULL) {

         

        if (kernel_mode && KX &&

            (address & 0x07FFFFFFFFFFFFFFULL) <= env->PAMask) {

            *physical = address & env->PAMask;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < 0xFFFFFFFF80000000ULL) {

         

        if (kernel_mode && KX &&

            address <= (0xFFFFFFFF7FFFFFFFULL & env->SEGMask)) {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }


    } else if (address < (int32_t)KSEG1_BASE) {

         

        if (kernel_mode) {

            *physical = address - (int32_t)KSEG0_BASE;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < (int32_t)KSEG2_BASE) {

         

        if (kernel_mode) {

            *physical = address - (int32_t)KSEG1_BASE;

            *prot = PAGE_READ | PAGE_WRITE;

        } else {

            ret = TLBRET_BADADDR;

        }

    } else if (address < (int32_t)KSEG3_BASE) {

         

        if (supervisor_mode || kernel_mode) {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    } else {

         

         

        if (kernel_mode) {

            ret = env->tlb->map_address(env, physical, prot, real_address, rw, access_type);

        } else {

            ret = TLBRET_BADADDR;

        }

    }

    return ret;

}
