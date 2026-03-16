static void call_rlc ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , proto_item * ti , guint8 lchid , void * data ) {
 switch ( lchId_type_table [ lchid ] ) {
 case MAC_CONTENT_DCCH : proto_item_append_text ( ti , " (DCCH)" ) ;
 call_dissector_with_data ( rlc_dcch_handle , tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_PS_DTCH : proto_item_append_text ( ti , " (PS DTCH)" ) ;
 call_dissector_with_data ( rlc_ps_dtch_handle , tvb , pinfo , tree , data ) ;
 break ;
 case MAC_CONTENT_CS_DTCH : proto_item_append_text ( ti , " (CS DTCH)" ) ;
 break ;
 default : proto_item_append_text ( ti , " (Unknown EDCH Content)" ) ;
 expert_add_info_format ( pinfo , ti , & ei_mac_unknown_content , "Unknown EDCH Content" ) ;
 break ;
 }
 }