static void display_update ( DisplayChangeListener * dcl , int x , int y , int w , int h ) {
 SimpleSpiceDisplay * ssd = container_of ( dcl , SimpleSpiceDisplay , dcl ) ;
 qemu_spice_display_update ( ssd , x , y , w , h ) ;
 }