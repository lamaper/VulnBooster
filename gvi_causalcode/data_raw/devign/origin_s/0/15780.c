static bool vregs_needed(void *opaque)

{


    if (kvm_enabled()) {

        return kvm_check_extension(kvm_state, KVM_CAP_S390_VECTOR_REGISTERS);

    }


    return 0;

}
