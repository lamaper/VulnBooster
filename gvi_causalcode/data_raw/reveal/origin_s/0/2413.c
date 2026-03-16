static void qdev_print_props ( Monitor * mon , DeviceState * dev , Property * props , const char * prefix , int indent ) {
 char buf [ 64 ] ;
 if ( ! props ) return ;
 while ( props -> name ) {
 if ( props -> info -> print ) {
 props -> info -> print ( dev , props , buf , sizeof ( buf ) ) ;
 qdev_printf ( "%s-prop: %s = %s\n" , prefix , props -> name , buf ) ;
 }
 props ++ ;
 }
 }