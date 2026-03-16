gboolean lbmpdm_verify_payload ( tvbuff_t * tvb , int offset , int * encoding , int * length ) {
 guint8 next_header ;
 guint32 len = 0 ;
 if ( ! tvb_bytes_exist ( tvb , offset , L_LBMPDM_MSG_HDR_T ) ) {
 return ( FALSE ) ;
 }
 if ( ! check_lbmpdm_encoding ( tvb , offset , encoding ) ) {
 return ( FALSE ) ;
 }
 next_header = tvb_get_guint8 ( tvb , offset + O_LBMPDM_MSG_HDR_T_NEXT_HDR ) ;
 switch ( next_header ) {
 case PDM_HDR_TYPE_DATA : case PDM_HDR_TYPE_OFSTTBLE : case PDM_HDR_TYPE_DEFN : case PDM_HDR_TYPE_EOM : break ;
 default : return ( FALSE ) ;
 break ;
 }
 len = lbmpdm_fetch_uint32_encoded ( tvb , offset + O_LBMPDM_MSG_HDR_T_LEN , * encoding ) ;
 if ( len > G_MAXINT ) {
 return ( FALSE ) ;
 }
 * length = ( int ) len ;
 return ( TRUE ) ;
 }