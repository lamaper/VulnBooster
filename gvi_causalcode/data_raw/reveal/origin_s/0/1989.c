static int kvm_get_sregs ( X86CPU * cpu ) {
 CPUX86State * env = & cpu -> env ;
 struct kvm_sregs sregs ;
 int bit , i , ret ;
 ret = kvm_vcpu_ioctl ( CPU ( cpu ) , KVM_GET_SREGS , & sregs ) ;
 if ( ret < 0 ) {
 return ret ;
 }
 env -> interrupt_injected = - 1 ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( sregs . interrupt_bitmap ) ;
 i ++ ) {
 if ( sregs . interrupt_bitmap [ i ] ) {
 bit = ctz64 ( sregs . interrupt_bitmap [ i ] ) ;
 env -> interrupt_injected = i * 64 + bit ;
 break ;
 }
 }
 get_seg ( & env -> segs [ R_CS ] , & sregs . cs ) ;
 get_seg ( & env -> segs [ R_DS ] , & sregs . ds ) ;
 get_seg ( & env -> segs [ R_ES ] , & sregs . es ) ;
 get_seg ( & env -> segs [ R_FS ] , & sregs . fs ) ;
 get_seg ( & env -> segs [ R_GS ] , & sregs . gs ) ;
 get_seg ( & env -> segs [ R_SS ] , & sregs . ss ) ;
 get_seg ( & env -> tr , & sregs . tr ) ;
 get_seg ( & env -> ldt , & sregs . ldt ) ;
 env -> idt . limit = sregs . idt . limit ;
 env -> idt . base = sregs . idt . base ;
 env -> gdt . limit = sregs . gdt . limit ;
 env -> gdt . base = sregs . gdt . base ;
 env -> cr [ 0 ] = sregs . cr0 ;
 env -> cr [ 2 ] = sregs . cr2 ;
 env -> cr [ 3 ] = sregs . cr3 ;
 env -> cr [ 4 ] = sregs . cr4 ;
 env -> efer = sregs . efer ;
 x86_update_hflags ( env ) ;
 return 0 ;
 }