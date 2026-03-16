static int lbmpdm_get_segment_length ( tvbuff_t * tvb , int offset , int encoding , int * data_length ) {
 guint32 datalen = 0 ;
 int seglen = 0 ;
 datalen = lbmpdm_fetch_uint32_encoded ( tvb , offset + O_LBMPDM_SEG_HDR_T_LEN , encoding ) ;
 seglen = ( ( int ) datalen ) + L_LBMPDM_SEG_HDR_T ;
 * data_length = ( int ) datalen ;
 return ( seglen ) ;
 }