int kvm_arch_get_registers ( CPUState * cs ) {
 X86CPU * cpu = X86_CPU ( cs ) ;
 int ret ;
 assert ( cpu_is_stopped ( cs ) || qemu_cpu_is_self ( cs ) ) ;
 ret = kvm_get_vcpu_events ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_mp_state ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_getput_regs ( cpu , 0 ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_xsave ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_xcrs ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_sregs ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_msrs ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_apic ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = kvm_get_debugregs ( cpu ) ;
 if ( ret < 0 ) {
 goto out ;
 }
 ret = 0 ;
 out : cpu_sync_bndcs_hflags ( & cpu -> env ) ;
 return ret ;
 }