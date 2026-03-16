static guint16 lbmpdm_fetch_uint16_encoded ( tvbuff_t * tvb , int offset , int encoding ) {
 guint16 value = 0 ;
 if ( encoding == ENC_BIG_ENDIAN ) {
 value = tvb_get_ntohs ( tvb , offset ) ;
 }
 else {
 value = tvb_get_letohs ( tvb , offset ) ;
 }
 return ( value ) ;
 }