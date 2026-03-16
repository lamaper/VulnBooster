void disas(FILE *out, void *code, unsigned long size)

{

    unsigned long pc;

    int count;

    struct disassemble_info disasm_info;

    int (*print_insn)(bfd_vma pc, disassemble_info *info);



    INIT_DISASSEMBLE_INFO(disasm_info, out, fprintf);



    disasm_info.buffer = code;

    disasm_info.buffer_vma = (unsigned long)code;

    disasm_info.buffer_length = size;


    disasm_info.endian = BFD_ENDIAN_BIG;


    disasm_info.endian = BFD_ENDIAN_LITTLE;



    disasm_info.mach = bfd_mach_i386_i386;

    print_insn = print_insn_i386;


    disasm_info.mach = bfd_mach_x86_64;

    print_insn = print_insn_i386;


    print_insn = print_insn_ppc;


    print_insn = print_insn_alpha;


    print_insn = print_insn_sparc;


    disasm_info.mach = bfd_mach_sparc_v9b;



    print_insn = print_insn_arm;


    print_insn = print_insn_big_mips;


    print_insn = print_insn_little_mips;


    print_insn = print_insn_m68k;


    print_insn = print_insn_s390;


    print_insn = print_insn_hppa;


    print_insn = print_insn_ia64;


    fprintf(out, "0x%lx: Asm output not supported on this arch\n",

	    (long) code);

    return;


    for (pc = (unsigned long)code; size > 0; pc += count, size -= count) {

	fprintf(out, "0x%08lx:  ", pc);


         

        fprintf(out, "%08x  ", (int)bfd_getl32((const bfd_byte *)pc));


	count = print_insn(pc, &disasm_info);

	fprintf(out, "\n");

	if (count < 0)

	    break;

    }

}
