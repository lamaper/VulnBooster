static void systick_reset ( nvic_state * s ) {
 s -> systick . control = 0 ;
 s -> systick . reload = 0 ;
 s -> systick . tick = 0 ;
 qemu_del_timer ( s -> systick . timer ) ;
 }