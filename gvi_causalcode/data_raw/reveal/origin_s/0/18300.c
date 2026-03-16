static int vvalue_tvb_get8 ( tvbuff_t * tvb , int offset , void * val ) {
 guint64 * ui8 = ( guint64 * ) val ;
 * ui8 = tvb_get_letoh64 ( tvb , offset ) ;
 return 8 ;
 }