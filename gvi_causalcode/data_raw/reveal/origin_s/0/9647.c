static int vvalue_tvb_lpstr ( tvbuff_t * tvb , int offset , void * val ) {
 struct data_str * str = ( struct data_str * ) val ;
 gint len ;
 str -> len = tvb_get_letohl ( tvb , offset ) ;
 str -> str = tvb_get_stringz_enc ( wmem_packet_scope ( ) , tvb , offset + 4 , & len , ENC_ASCII | ENC_LITTLE_ENDIAN ) ;
 return 4 + len ;
 }