static int vvalue_tvb_get1 ( tvbuff_t * tvb , int offset , void * val ) {
 guint8 * ui1 = ( guint8 * ) val ;
 * ui1 = tvb_get_guint8 ( tvb , offset ) ;
 return 1 ;
 }