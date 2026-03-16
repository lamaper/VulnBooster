static guint32 lbmpdm_fetch_uint32_encoded ( tvbuff_t * tvb , int offset , int encoding ) {
 guint32 value = 0 ;
 if ( encoding == ENC_BIG_ENDIAN ) {
 value = tvb_get_ntohl ( tvb , offset ) ;
 }
 else {
 value = tvb_get_letohl ( tvb , offset ) ;
 }
 return ( value ) ;
 }