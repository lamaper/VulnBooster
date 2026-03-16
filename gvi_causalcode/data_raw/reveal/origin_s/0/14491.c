static tvbuff_t * add_to_tree ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , mac_is_sdu * sdu , guint offset , guint16 maclength , guint8 type ) {
 tvbuff_t * new_tvb = NULL ;
 if ( sdu -> frame_num == pinfo -> num ) {
 mac_is_fragment * f = sdu -> fragments ;
 guint counter = 0 ;
 new_tvb = tvb_new_child_real_data ( tvb , sdu -> data , sdu -> length , sdu -> length ) ;
 add_new_data_source ( pinfo , new_tvb , "Reassembled MAC-is SDU" ) ;
 proto_tree_add_expert ( tree , pinfo , & ei_mac_macis_sdu_reassembled , new_tvb , 0 , - 1 ) ;
 while ( f ) {
 proto_tree_add_uint_format_value ( tree , hf_mac_is_fraglink , new_tvb , counter , f -> length , f -> frame_num , "%u, payload: %u-%u (%u bytes) (TSN: %u)" , f -> frame_num , counter , counter + f -> length - 1 , f -> length , f -> tsn ) ;
 counter += f -> length ;
 f = f -> next ;
 }
 return new_tvb ;
 }
 else {
 new_tvb = tvb_new_subset ( tvb , offset , maclength , - 1 ) ;
 switch ( type ) {
 case MAC_IS_HEAD : proto_tree_add_expert ( tree , pinfo , & ei_mac_macis_sdu_first , new_tvb , 0 , - 1 ) ;
 break ;
 case MAC_IS_MIDDLE : proto_tree_add_expert ( tree , pinfo , & ei_mac_macis_sdu_middle , new_tvb , 0 , - 1 ) ;
 break ;
 case MAC_IS_TAIL : proto_tree_add_expert ( tree , pinfo , & ei_mac_macis_sdu_last , new_tvb , 0 , - 1 ) ;
 break ;
 }
 proto_tree_add_uint ( tree , hf_mac_is_reasmin , new_tvb , 0 , 0 , sdu -> frame_num ) ;
 return NULL ;
 }
 }