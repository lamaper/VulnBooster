static gboolean check_lbmpdm_encoding ( tvbuff_t * tvb , int offset , int * encoding ) {
 guint8 magic_byte_1 ;
 guint8 magic_byte_2 ;
 guint8 magic_byte_3 ;
 guint8 magic_byte_4 ;
 gboolean result = TRUE ;
 magic_byte_1 = tvb_get_guint8 ( tvb , offset ) ;
 magic_byte_2 = tvb_get_guint8 ( tvb , offset + 1 ) ;
 magic_byte_3 = tvb_get_guint8 ( tvb , offset + 2 ) ;
 magic_byte_4 = tvb_get_guint8 ( tvb , offset + 3 ) ;
 if ( ( magic_byte_1 == PDM_MSG_HDR_BE_MAGIC_BYTE_1 ) && ( magic_byte_2 == PDM_MSG_HDR_BE_MAGIC_BYTE_2 ) && ( magic_byte_3 == PDM_MSG_HDR_BE_MAGIC_BYTE_3 ) && ( magic_byte_4 == PDM_MSG_HDR_BE_MAGIC_BYTE_4 ) ) {
 * encoding = ENC_BIG_ENDIAN ;
 }
 else if ( ( magic_byte_1 == PDM_MSG_HDR_LE_MAGIC_BYTE_1 ) && ( magic_byte_2 == PDM_MSG_HDR_LE_MAGIC_BYTE_2 ) && ( magic_byte_3 == PDM_MSG_HDR_LE_MAGIC_BYTE_3 ) && ( magic_byte_4 == PDM_MSG_HDR_LE_MAGIC_BYTE_4 ) ) {
 * encoding = ENC_LITTLE_ENDIAN ;
 }
 else {
 result = FALSE ;
 }
 return ( result ) ;
 }