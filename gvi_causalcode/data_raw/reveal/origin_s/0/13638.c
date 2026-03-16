guint16 de_time_zone ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint32 curr_offset ;
 char sign ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) ;
 sign = ( oct & 0x08 ) ? '-' : '+' ;
 oct = ( oct >> 4 ) + ( oct & 0x07 ) * 10 ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_timezone , tvb , curr_offset , 1 , oct , "GMT %c %d hours %d minutes" , sign , oct / 4 , oct % 4 * 15 ) ;
 curr_offset ++ ;
 return ( curr_offset - offset ) ;
 }