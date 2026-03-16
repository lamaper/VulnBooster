void kvm_arch_on_sigbus_vcpu ( CPUState * c , int code , void * addr ) {
 X86CPU * cpu = X86_CPU ( c ) ;
 CPUX86State * env = & cpu -> env ;
 ram_addr_t ram_addr ;
 hwaddr paddr ;
 assert ( code == BUS_MCEERR_AR || code == BUS_MCEERR_AO ) ;
 if ( ( env -> mcg_cap & MCG_SER_P ) && addr ) {
 ram_addr = qemu_ram_addr_from_host ( addr ) ;
 if ( ram_addr != RAM_ADDR_INVALID && kvm_physical_memory_addr_from_host ( c -> kvm_state , addr , & paddr ) ) {
 kvm_hwpoison_page_add ( ram_addr ) ;
 kvm_mce_inject ( cpu , paddr , code ) ;
 return ;
 }
 fprintf ( stderr , "Hardware memory error for memory used by " "QEMU itself instead of guest system!\n" ) ;
 }
 if ( code == BUS_MCEERR_AR ) {
 hardware_memory_error ( ) ;
 }
 }