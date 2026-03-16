static inline int fp_reg_offset(int regno, TCGMemOp size)

{

    int offs = offsetof(CPUARMState, vfp.regs[regno * 2]);


    offs += (8 - (1 << size));


    return offs;

}
