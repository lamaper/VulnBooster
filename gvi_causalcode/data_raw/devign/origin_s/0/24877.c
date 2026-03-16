static void gen_spr_power8_book4(CPUPPCState *env)

{


    spr_register_kvm(env, SPR_ACOP, "ACOP",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     KVM_REG_PPC_ACOP, 0);

    spr_register_kvm(env, SPR_BOOKS_PID, "PID",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     KVM_REG_PPC_PID, 0);

    spr_register_kvm(env, SPR_WORT, "WORT",

                     SPR_NOACCESS, SPR_NOACCESS,

                     &spr_read_generic, &spr_write_generic,

                     KVM_REG_PPC_WORT, 0);


}
