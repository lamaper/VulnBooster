int kvm_has_sync_mmu(void)

{


    KVMState *s = kvm_state;



    return kvm_check_extension(s, KVM_CAP_SYNC_MMU);


    return 0;


}
