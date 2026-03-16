static guint16 de_mm_timer ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 oct ;
 guint16 val ;
 const gchar * str ;
 proto_tree * subtree ;
 proto_item * item = NULL ;
 oct = tvb_get_guint8 ( tvb , offset ) ;
 val = oct & 0x1f ;
 switch ( oct >> 5 ) {
 case 0 : str = "sec" ;
 val *= 2 ;
 break ;
 case 1 : str = "min" ;
 break ;
 case 2 : str = "min" ;
 val *= 6 ;
 break ;
 case 7 : str = "" ;
 item = proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_mm_timer , tvb , offset , 1 , oct , "timer is deactivated" ) ;
 break ;
 default : str = "min" ;
 break ;
 }
 if ( item == NULL ) {
 item = proto_tree_add_uint_format_value ( tree , hf_gsm_a_dtap_mm_timer , tvb , offset , 1 , val , "%u %s" , val , str ) ;
 }
 subtree = proto_item_add_subtree ( item , ett_mm_timer ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_mm_timer_unit , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_dtap_mm_timer_value , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 return ( 1 ) ;
 }