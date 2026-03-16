static int get_sync_range ( int width ) {
 if ( width < 640 ) return 1 ;
 else if ( width <= 1280 ) return 2 ;
 else if ( width <= 4096 ) return 4 ;
 else return 8 ;
 }