guint16 de_plmn_list ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len , gchar * add_string , int string_len ) {
 guint8 octs [ 3 ] ;
 guint32 curr_offset ;
 gchar mcc [ 4 ] ;
 gchar mnc [ 4 ] ;
 guint8 num_plmn ;
 proto_tree * subtree ;
 curr_offset = offset ;
 num_plmn = 0 ;
 while ( ( len - ( curr_offset - offset ) ) >= 3 ) {
 octs [ 0 ] = tvb_get_guint8 ( tvb , curr_offset ) ;
 octs [ 1 ] = tvb_get_guint8 ( tvb , curr_offset + 1 ) ;
 octs [ 2 ] = tvb_get_guint8 ( tvb , curr_offset + 2 ) ;
 mcc_mnc_aux ( octs , mcc , mnc ) ;
 subtree = proto_tree_add_subtree_format ( tree , tvb , curr_offset , 3 , ett_gsm_a_plmn , NULL , "PLMN[%u]" , num_plmn + 1 ) ;
 proto_tree_add_string ( subtree , hf_gsm_a_mobile_country_code , tvb , curr_offset , 3 , mcc ) ;
 proto_tree_add_string ( subtree , hf_gsm_a_mobile_network_code , tvb , curr_offset , 3 , mnc ) ;
 curr_offset += 3 ;
 num_plmn ++ ;
 }
 if ( add_string ) g_snprintf ( add_string , string_len , " - %u PLMN%s" , num_plmn , plurality ( num_plmn , "" , "s" ) ) ;
 EXTRANEOUS_DATA_CHECK ( len , curr_offset - offset , pinfo , & ei_gsm_a_extraneous_data ) ;
 return ( curr_offset - offset ) ;
 }