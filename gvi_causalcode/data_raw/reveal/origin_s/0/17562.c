int kvm_arch_init ( MachineState * ms , KVMState * s ) {
 uint64_t identity_base = 0xfffbc000 ;
 uint64_t shadow_mem ;
 int ret ;
 struct utsname utsname ;




 if ( ret < 0 ) {
 return ret ;
 }
 uname ( & utsname ) ;
 lm_capable_kernel = strcmp ( utsname . machine , "x86_64" ) == 0 ;
 if ( kvm_check_extension ( s , KVM_CAP_SET_IDENTITY_MAP_ADDR ) ) {
 identity_base = 0xfeffc000 ;
 ret = kvm_vm_ioctl ( s , KVM_SET_IDENTITY_MAP_ADDR , & identity_base ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 }
 ret = kvm_vm_ioctl ( s , KVM_SET_TSS_ADDR , identity_base + 0x1000 ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 ret = e820_add_entry ( identity_base , 0x4000 , E820_RESERVED ) ;
 if ( ret < 0 ) {
 fprintf ( stderr , "e820_add_entry() table is full\n" ) ;
 return ret ;
 }
 qemu_register_reset ( kvm_unpoison_all , NULL ) ;
 shadow_mem = machine_kvm_shadow_mem ( ms ) ;
 if ( shadow_mem != - 1 ) {
 shadow_mem /= 4096 ;
 ret = kvm_vm_ioctl ( s , KVM_SET_NR_MMU_PAGES , shadow_mem ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 }
 if ( kvm_check_extension ( s , KVM_CAP_X86_SMM ) && object_dynamic_cast ( OBJECT ( ms ) , TYPE_PC_MACHINE ) && pc_machine_is_smm_enabled ( PC_MACHINE ( ms ) ) ) {
 smram_machine_done . notify = register_smram_listener ;
 qemu_add_machine_init_done_notifier ( & smram_machine_done ) ;
 }
 return 0 ;
 }