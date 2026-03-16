static void systick_reload ( nvic_state * s , int reset ) {
 if ( reset ) s -> systick . tick = qemu_get_clock_ns ( vm_clock ) ;
 s -> systick . tick += ( s -> systick . reload + 1 ) * systick_scale ( s ) ;
 qemu_mod_timer ( s -> systick . timer , s -> systick . tick ) ;
 }