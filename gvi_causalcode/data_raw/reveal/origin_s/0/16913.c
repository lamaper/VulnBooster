static void openpic_load_IRQ_queue ( QEMUFile * f , IRQQueue * q ) {
 unsigned int i ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( q -> queue ) ;
 i ++ ) {
 unsigned long val ;
 val = qemu_get_be32 ( f ) ;

 val |= qemu_get_be32 ( f ) ;

 }
 qemu_get_sbe32s ( f , & q -> next ) ;
 qemu_get_sbe32s ( f , & q -> priority ) ;
 }