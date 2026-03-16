static int dissect_diameter ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 if ( check_diameter ( tvb ) != IS_DIAMETER ) return 0 ;
 return dissect_diameter_common ( tvb , pinfo , tree , data ) ;
 }