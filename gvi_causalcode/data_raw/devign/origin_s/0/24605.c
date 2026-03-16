HELPER_LD(lbu, ldub, uint8_t)

HELPER_LD(lhu, lduw, uint16_t)

HELPER_LD(lw, ldl, int32_t)

HELPER_LD(ld, ldq, int64_t)




static inline void do_##name(CPUMIPSState *env, target_ulong addr,      \

                             type val, int mem_idx)                     \

{                                                                       \

    cpu_##insn##_data(env, addr, val);                                  \

}



static inline void do_##name(CPUMIPSState *env, target_ulong addr,      \

                             type val, int mem_idx)                     \

{                                                                       \

    switch (mem_idx)                                                    \

    {                                                                   \

    case 0: cpu_##insn##_kernel(env, addr, val); break;                 \

    case 1: cpu_##insn##_super(env, addr, val); break;                  \

    default:                                                            \

    case 2: cpu_##insn##_user(env, addr, val); break;                   \

    }                                                                   \

}


HELPER_ST(sb, stb, uint8_t)

HELPER_ST(sh, stw, uint16_t)

HELPER_ST(sw, stl, uint32_t)

HELPER_ST(sd, stq, uint64_t)




target_ulong helper_clo (target_ulong arg1)

{

    return clo32(arg1);

}
