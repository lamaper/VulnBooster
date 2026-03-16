static void display_switch ( DisplayChangeListener * dcl , struct DisplaySurface * surface ) {
 SimpleSpiceDisplay * ssd = container_of ( dcl , SimpleSpiceDisplay , dcl ) ;
 qemu_spice_display_switch ( ssd , surface ) ;
 }