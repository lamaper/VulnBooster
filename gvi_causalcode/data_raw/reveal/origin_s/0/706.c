static void malta_fpga_led_init ( CharDriverState * chr ) {
 qemu_chr_fe_printf ( chr , "\e[HMalta LEDBAR\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+--------+\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+ +\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+--------+\r\n" ) ;
 qemu_chr_fe_printf ( chr , "\n" ) ;
 qemu_chr_fe_printf ( chr , "Malta ASCII\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+--------+\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+ +\r\n" ) ;
 qemu_chr_fe_printf ( chr , "+--------+\r\n" ) ;
 }