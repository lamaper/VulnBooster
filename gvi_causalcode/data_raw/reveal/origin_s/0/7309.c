guint16 de_lai ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 guint8 octs [ 3 ] ;
 guint16 value ;
 guint32 curr_offset ;
 proto_tree * subtree ;
 proto_item * item ;
 gchar mcc [ 4 ] ;
 gchar mnc [ 4 ] ;
 curr_offset = offset ;
 subtree = proto_tree_add_subtree ( tree , tvb , curr_offset , 5 , ett_gsm_common_elem [ DE_LAI ] , & item , val_to_str_ext_const ( DE_LAI , & gsm_common_elem_strings_ext , "" ) ) ;
 octs [ 0 ] = tvb_get_guint8 ( tvb , curr_offset ) ;
 octs [ 1 ] = tvb_get_guint8 ( tvb , curr_offset + 1 ) ;
 octs [ 2 ] = tvb_get_guint8 ( tvb , curr_offset + 2 ) ;
 mcc_mnc_aux ( octs , mcc , mnc ) ;
 curr_offset = dissect_e212_mcc_mnc ( tvb , pinfo , subtree , curr_offset , E212_LAI , TRUE ) ;
 value = tvb_get_ntohs ( tvb , curr_offset ) ;
 proto_tree_add_item ( subtree , hf_gsm_a_lac , tvb , curr_offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( item , " - %s/%s/%u" , mcc , mnc , value ) ;
 curr_offset += 2 ;
 return ( curr_offset - offset ) ;
 }