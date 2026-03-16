static char * stp_print_bridge_id ( const u_char * p ) {
 static char bridge_id_str [ sizeof ( "pppp.aa:bb:cc:dd:ee:ff" ) ] ;
 snprintf ( bridge_id_str , sizeof ( bridge_id_str ) , "%.2x%.2x.%.2x:%.2x:%.2x:%.2x:%.2x:%.2x" , p [ 0 ] , p [ 1 ] , p [ 2 ] , p [ 3 ] , p [ 4 ] , p [ 5 ] , p [ 6 ] , p [ 7 ] ) ;
 return bridge_id_str ;
 }