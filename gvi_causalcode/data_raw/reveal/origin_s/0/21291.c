static int vvalue_tvb_get4 ( tvbuff_t * tvb , int offset , void * val ) {
 guint32 * ui4 = ( guint32 * ) val ;
 * ui4 = tvb_get_letohl ( tvb , offset ) ;
 return 4 ;
 }