static int get_kpcr_number ( CPUX86State * env ) {
 struct kpcr {
 uint8_t fill1 [ 0x1c ] ;
 uint32_t self ;
 uint8_t fill2 [ 0x31 ] ;
 uint8_t number ;
 }
 QEMU_PACKED kpcr ;
 if ( cpu_memory_rw_debug ( env , env -> segs [ R_FS ] . base , ( void * ) & kpcr , sizeof ( kpcr ) , 0 ) < 0 || kpcr . self != env -> segs [ R_FS ] . base ) {
 return - 1 ;
 }
 return kpcr . number ;
 }