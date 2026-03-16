static void VGA_init ( void ) {
 printf ( "Init VGA...\n" ) ;

 PPC_io_writeb ( PPC_IO_BASE + 0x3C4 , 0x04 ) ;
 PPC_io_writeb ( PPC_IO_BASE + 0x3C5 , 0x02 ) ;

 }