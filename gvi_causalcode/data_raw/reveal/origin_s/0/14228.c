static void display_refresh ( DisplayChangeListener * dcl ) {
 SimpleSpiceDisplay * ssd = container_of ( dcl , SimpleSpiceDisplay , dcl ) ;
 qemu_spice_display_refresh ( ssd ) ;
 }