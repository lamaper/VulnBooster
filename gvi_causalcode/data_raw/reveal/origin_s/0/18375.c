static void openpic_save_IRQ_queue ( QEMUFile * f , IRQQueue * q ) {
 unsigned int i ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( q -> queue ) ;
 i ++ ) {
 qemu_put_be32 ( f , ( uint32_t ) q -> queue [ i ] ) ;


 qemu_put_sbe32s ( f , & q -> next ) ;
 qemu_put_sbe32s ( f , & q -> priority ) ;
 }