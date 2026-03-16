static guint64 lbmpdm_fetch_uint64_encoded ( tvbuff_t * tvb , int offset , int encoding ) {
 guint64 value = 0 ;
 if ( encoding == ENC_BIG_ENDIAN ) {
 value = tvb_get_ntoh64 ( tvb , offset ) ;
 }
 else {
 value = tvb_get_letoh64 ( tvb , offset ) ;
 }
 return ( value ) ;
 }