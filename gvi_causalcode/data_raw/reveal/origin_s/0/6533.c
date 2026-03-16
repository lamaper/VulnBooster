static int vvalue_tvb_lpwstr_len ( tvbuff_t * tvb , int offset , int length , void * val ) {
 struct data_str * str = ( struct data_str * ) val ;
 const gchar * ptr ;
 int len ;
 if ( length == 0 ) {
 ptr = tvb_get_stringz_enc ( wmem_packet_scope ( ) , tvb , offset , & len , ENC_UTF_16 | ENC_LITTLE_ENDIAN ) ;
 }
 else {
 ptr = tvb_get_string_enc ( wmem_packet_scope ( ) , tvb , offset , length , ENC_UTF_16 | ENC_LITTLE_ENDIAN ) ;
 len = length ;
 }
 str -> str = ptr ;
 return len ;
 }