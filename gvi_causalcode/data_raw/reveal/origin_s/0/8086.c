static int data_packets_seen ( const struct ogg * ogg ) {
 int i ;
 for ( i = 0 ;
 i < ogg -> nstreams ;
 i ++ ) if ( ogg -> streams [ i ] . got_data ) return 1 ;
 return 0 ;
 }