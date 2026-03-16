static int vvalue_tvb_get2 ( tvbuff_t * tvb , int offset , void * val ) {
 guint16 * ui2 = ( guint16 * ) val ;
 * ui2 = tvb_get_letohs ( tvb , offset ) ;
 return 2 ;
 }