static void dissect_fpdu_crc ( tvbuff_t * tvb , proto_tree * tree , mpa_state_t * state , guint32 offset , guint32 length ) {
 guint32 crc = 0 ;
 guint32 sent_crc = 0 ;
 if ( state -> crc ) {
 crc = ~ crc32c_tvb_offset_calculate ( tvb , 0 , length , CRC32C_PRELOAD ) ;
 sent_crc = tvb_get_ntohl ( tvb , offset ) ;
 if ( crc == sent_crc ) {
 proto_tree_add_uint_format_value ( tree , hf_mpa_crc_check , tvb , offset , MPA_CRC_LEN , sent_crc , "0x%08x (Good CRC32)" , sent_crc ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_mpa_crc_check , tvb , offset , MPA_CRC_LEN , sent_crc , "0x%08x (Bad CRC32, should be 0x%08x)" , sent_crc , crc ) ;
 }
 }
 else {
 proto_tree_add_item ( tree , hf_mpa_crc , tvb , offset , MPA_CRC_LEN , ENC_BIG_ENDIAN ) ;
 }
 }