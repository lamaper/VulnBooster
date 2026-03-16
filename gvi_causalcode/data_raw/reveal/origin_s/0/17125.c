static guint16 de_tp_sub_channel ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint32 curr_offset ;
 guchar oct ;
 const gchar * str ;
 curr_offset = offset ;
 oct = tvb_get_guint8 ( tvb , curr_offset ) & 0x3f ;
 if ( ( oct & 0x38 ) == 0x38 ) str = "I" ;
 else if ( ( oct & 0x38 ) == 0x18 ) str = "F" ;
 else if ( ( oct & 0x38 ) == 0x10 ) str = "E" ;
 else if ( ( oct & 0x38 ) == 0x08 ) str = "D" ;
 else if ( ( oct & 0x3c ) == 0x04 ) str = "C" ;
 else if ( ( oct & 0x3e ) == 0x02 ) str = "B" ;
 else if ( ( oct & 0x3e ) == 0x00 ) str = "A" ;
 else str = "unknown" ;
 proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_test_loop , tvb , curr_offset , 1 , oct , "%s" , str ) ;
 proto_tree_add_item ( tree , hf_gsm_a_dtap_subchannel , tvb , curr_offset , 1 , ENC_NA ) ;
 curr_offset += 1 ;
 return ( curr_offset - offset ) ;
 }