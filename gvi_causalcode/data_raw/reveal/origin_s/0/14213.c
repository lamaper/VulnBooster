static int vvalue_tvb_blob ( tvbuff_t * tvb , int offset , void * val ) {
 struct data_blob * blob = ( struct data_blob * ) val ;
 guint32 len = tvb_get_letohl ( tvb , offset ) ;
 blob -> size = len ;
 blob -> data = ( guint8 * ) tvb_memdup ( wmem_packet_scope ( ) , tvb , offset + 4 , len ) ;
 return 4 + len ;
 }