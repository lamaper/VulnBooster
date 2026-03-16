guint16 dissect_description_of_velocity ( tvbuff_t * tvb , proto_tree * tree , packet_info * pinfo _U_ , guint32 offset , guint len _U_ , gchar * add_string _U_ , int string_len _U_ ) {
 proto_item * velocity_item ;
 guint32 curr_offset ;
 guint8 velocity_type , uncertainty_speed = 0 ;
 curr_offset = offset ;
 velocity_type = tvb_get_guint8 ( tvb , curr_offset ) ;
 proto_tree_add_item ( tree , hf_gsm_a_velocity_type , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 curr_offset ++ ;
 switch ( velocity_type ) {
 case 0 : proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_bearing , tvb , ( curr_offset << 3 ) + 7 , 9 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_horizontal_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset += 2 ;
 break ;
 case 1 : proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_d , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_bearing , tvb , ( curr_offset << 3 ) + 7 , 9 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_horizontal_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_vertical_speed , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset ++ ;
 break ;
 case 2 : proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 3 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_bearing , tvb , ( curr_offset << 3 ) + 7 , 9 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_horizontal_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset += 2 ;
 uncertainty_speed = tvb_get_guint8 ( tvb , curr_offset ) ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_uncertainty_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( uncertainty_speed == 255 ) {
 proto_item_append_text ( velocity_item , " not specified" ) ;
 }
 else {
 proto_item_append_text ( velocity_item , " km/h" ) ;
 }
 offset ++ ;
 break ;
 case 3 : proto_tree_add_bits_item ( tree , hf_gsm_a_spare_bits , tvb , ( curr_offset << 3 ) + 4 , 2 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_item ( tree , hf_gsm_a_d , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_tree_add_bits_item ( tree , hf_gsm_a_bearing , tvb , ( curr_offset << 3 ) + 7 , 9 , ENC_BIG_ENDIAN ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_horizontal_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset += 2 ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_vertical_speed , tvb , offset , 1 , ENC_BIG_ENDIAN ) ;
 proto_item_append_text ( velocity_item , " km/h" ) ;
 curr_offset ++ ;
 uncertainty_speed = tvb_get_guint8 ( tvb , curr_offset ) ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_h_uncertainty_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( uncertainty_speed == 255 ) {
 proto_item_append_text ( velocity_item , " not specified" ) ;
 }
 else {
 proto_item_append_text ( velocity_item , " km/h" ) ;
 }
 offset ++ ;
 uncertainty_speed = tvb_get_guint8 ( tvb , curr_offset ) ;
 velocity_item = proto_tree_add_item ( tree , hf_gsm_a_v_uncertainty_speed , tvb , offset , 2 , ENC_BIG_ENDIAN ) ;
 if ( uncertainty_speed == 255 ) {
 proto_item_append_text ( velocity_item , " not specified" ) ;
 }
 else {
 proto_item_append_text ( velocity_item , " km/h" ) ;
 }
 offset ++ ;
 break ;
 default : break ;
 }
 return ( curr_offset - offset ) ;
 }