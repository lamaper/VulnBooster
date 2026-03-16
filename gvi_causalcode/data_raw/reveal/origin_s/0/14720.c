static guint16 de_stream_id ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string , int string_len ) {
 guint32 curr_offset ;
 guint8 oct ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 if ( oct == 0x00 ) {
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_stream_identifier , tvb , curr_offset , 1 , oct , "No Bearer (%u)" , oct ) ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (No Bearer)" ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_gsm_a_dtap_stream_identifier , tvb , curr_offset , 1 , ENC_BIG_ENDIAN ) ;
 if ( add_string ) g_snprintf ( add_string , string_len , " - (%u)" , oct ) ;
 }
 curr_offset ++ ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_dtap_extraneous_data ) ;
 return ( len ) ;
 }