void PPC_init_hw ( uint32_t mem_size , uint32_t kernel_addr , uint32_t kernel_size , uint32_t stack_addr , int boot_device , const unsigned char * initrd_file ) {
 CPUPPCState * env = global_env ;
 uint8_t * p ;

 uint32_t tmpi [ 2 ] ;






 printf ( "Start address: 0x%08x\n" , env -> nip ) ;
 }
 msr_ee = 0 ;
 msr_fp = 1 ;
 msr_pr = 0 ;
 msr_me = 1 ;
 msr_fe0 = msr_fe1 = 0 ;
 msr_ip = 0 ;
 msr_ir = msr_dr = 1 ;
 msr_le = msr_ile = 0 ;
 env -> gpr [ 1 ] = stack_addr ;
 env -> gpr [ 2 ] = 0 ;
 env -> gpr [ 8 ] = kernel_addr ;
 env -> decr = 0xFFFFFFFF ;
 p = phys_ram_base + kernel_addr ;

 put_long ( p , 0xdeadc0de ) ;
 p = phys_ram_base + stack_addr ;
 put_long ( p , stack_addr ) ;
 p -= 32 ;
 env -> gpr [ 1 ] -= 32 ;
 env -> gpr [ 3 ] = 0 ;
 if ( initrd_file != NULL ) {
 int size ;
 env -> gpr [ 4 ] = ( kernel_addr + kernel_size + 4095 ) & ~ 4095 ;
 size = load_initrd ( initrd_file , phys_ram_base + env -> gpr [ 4 ] ) ;
 if ( size < 0 ) {
 env -> gpr [ 4 ] = env -> gpr [ 5 ] = 0 ;
 }
 else {
 env -> gpr [ 5 ] = size ;
 boot_device = 'e' ;
 }
 printf ( "Initrd loaded at 0x%08x (%d) (0x%08x 0x%08x)\n" , env -> gpr [ 4 ] , env -> gpr [ 5 ] , kernel_addr , kernel_size ) ;
 }
 else {
 env -> gpr [ 4 ] = env -> gpr [ 5 ] = 0 ;
 }



 fprintf ( logfile , "bootinfos: %p 0x%08x\n" , p , ( int ) ( p - phys_ram_base ) ) ;
 }
 else {
 printf ( "bootinfos: %p 0x%08x\n" , p , ( int ) ( p - phys_ram_base ) ) ;
 }



 env -> gpr [ 7 ] = env -> gpr [ 6 ] + strlen ( p + 0x1000 ) ;
 if ( loglevel > 0 ) {
 fprintf ( logfile , "cmdline: %p 0x%08x [%s]\n" , p + 0x1000 , env -> gpr [ 6 ] , p + 0x1000 ) ;
 }
 else {
 printf ( "cmdline: %p 0x%08x [%s]\n" , p + 0x1000 , env -> gpr [ 6 ] , p + 0x1000 ) ;
 }
 p = set_bootinfo_tag ( p , 0x1010 , 0 , 0 ) ;
 p = set_bootinfo_tag ( p , 0x1012 , env -> gpr [ 7 ] - env -> gpr [ 6 ] , env -> gpr [ 6 ] + phys_ram_base ) ;
 tmp = ( void * ) tmpi ;
 tmp [ 0 ] = ( mem_size >> 24 ) & 0xFF ;
 tmp [ 1 ] = ( mem_size >> 16 ) & 0xFF ;
 tmp [ 2 ] = ( mem_size >> 8 ) & 0xFF ;
 tmp [ 3 ] = mem_size & 0xFF ;
 p = set_bootinfo_tag ( p , 0x1017 , 4 , tmpi ) ;
 tmp [ 0 ] = ( env -> gpr [ 4 ] >> 24 ) & 0xFF ;
 tmp [ 1 ] = ( env -> gpr [ 4 ] >> 16 ) & 0xFF ;
 tmp [ 2 ] = ( env -> gpr [ 4 ] >> 8 ) & 0xFF ;
 tmp [ 3 ] = env -> gpr [ 4 ] & 0xFF ;
 tmp [ 4 ] = ( env -> gpr [ 5 ] >> 24 ) & 0xFF ;
 tmp [ 5 ] = ( env -> gpr [ 5 ] >> 16 ) & 0xFF ;
 tmp [ 6 ] = ( env -> gpr [ 5 ] >> 8 ) & 0xFF ;
 tmp [ 7 ] = env -> gpr [ 5 ] & 0xFF ;
 p = set_bootinfo_tag ( p , 0x1014 , 8 , tmpi ) ;
 env -> gpr [ 4 ] = env -> gpr [ 5 ] = 0 ;
 p = set_bootinfo_tag ( p , 0x1011 , 0 , 0 ) ;

 {



 printf ( "Start address: 0x%08x\n" , env -> nip ) ;
 }
 env -> gpr [ 1 ] = env -> nip + ( 1 << 22 ) ;
 p = phys_ram_base + stack_addr ;
 put_long ( p - 32 , stack_addr ) ;
 env -> gpr [ 1 ] -= 32 ;
 printf ( "Kernel starts at 0x%08x stack 0x%08x\n" , env -> nip , env -> gpr [ 1 ] ) ;
 setup_BAT ( env , 1 , 0x00000000 , 0x00000000 , 0x010000000 , 1 , 1 , 2 ) ;
 setup_BAT ( env , 2 , 0xFFFE0000 , mem_size - 131072 , 131072 , 1 , 0 , 1 ) ;
 {
 char * p ;
 p = ( char * ) phys_ram_base + mem_size - 131072 ;
 * p ++ = 0x18 ;
 * p ++ = 0x00 ;
 * p ++ = 0x00 ;
 * p ++ = 0x02 ;
 * p ++ = 0x4E ;
 * p ++ = 0x80 ;
 * p ++ = 0x00 ;
 * p ++ = 0x20 ;
 }
 env -> gpr [ 5 ] = 0xFFFE0000 ;
 {
 OF_transl_t translations [ 3 ] = {
 {
 0x01000000 , 0x00400000 , kernel_addr , 0x00000002 , }
 , {
 0x00000000 , 0x01000000 , 0x00000000 , 0x00000002 , }
 , {
 0xFFFE0000 , 0x00020000 , mem_size - ( 128 * 1024 ) , 0x00000001 , }
 , }
 ;
 OF_register_translations ( 3 , translations ) ;
 }
 OF_register_bus ( "isa" , "isa" ) ;
 OF_register_serial ( "isa" , "serial" , 4 , 0x3f8 ) ;
 OF_register_stdio ( "serial" , "serial" ) ;
 RTAS_init ( ) ;





