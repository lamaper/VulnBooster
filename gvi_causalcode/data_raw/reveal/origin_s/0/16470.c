static tvbuff_t * mac_is_add_fragment ( tvbuff_t * tvb _U_ , packet_info * pinfo , proto_tree * tree _U_ , guint8 lchid , guint ueid , int offset , guint8 ss , guint16 tsn , int sdu_no , guint8 no_sdus , guint16 maclength ) {
 mac_is_channel ch ;
 ch . lchid = lchid ;
 ch . ueid = ueid ;
 if ( pinfo -> fd -> flags . visited == FALSE ) {
 body_parts * * body_parts_array = get_body_parts ( & ch ) ;
 if ( no_sdus == 1 && ss == 3 ) {
 guint head_length , tail_length ;
 init_frag ( tvb , body_parts_array [ tsn ] , maclength , offset , pinfo -> num , tsn , MAC_IS_MIDDLE ) ;
 tail_length = find_tail ( body_parts_array , tsn ) ;
 if ( tail_length > 0 ) {
 head_length = find_head ( body_parts_array , & tsn ) ;
 if ( head_length > 0 ) {
 return reassemble ( tvb , body_parts_array , tsn , tail_length + head_length + maclength , & ch , pinfo -> num ) ;
 }
 }
 }
 else if ( sdu_no == 0 && ( ss & 1 ) == 1 ) {
 guint length = maclength ;
 init_frag ( tvb , body_parts_array [ tsn ] , maclength , offset , pinfo -> num , tsn , MAC_IS_TAIL ) ;
 length += find_head ( body_parts_array , & tsn ) ;
 if ( length > maclength ) {
 return reassemble ( tvb , body_parts_array , tsn , length , & ch , pinfo -> num ) ;
 }
 }
 else if ( sdu_no == no_sdus - 1 && ( ss & 2 ) == 2 ) {
 guint length = maclength ;
 init_frag ( tvb , body_parts_array [ tsn ] , maclength , offset , pinfo -> num , tsn , MAC_IS_HEAD ) ;
 length += find_tail ( body_parts_array , tsn ) ;
 if ( length > maclength ) {
 return reassemble ( tvb , body_parts_array , tsn , length , & ch , pinfo -> num ) ;
 }
 }
 else {
 DISSECTOR_ASSERT ( ( sdu_no == 0 ) ? ( ss & 1 ) == 0 : ( ( sdu_no == no_sdus - 1 ) ? ( ss & 2 ) == 0 : TRUE ) ) ;
 return tvb_new_subset ( tvb , offset , maclength , - 1 ) ;
 }
 }
 else {
 tvbuff_t * new_tvb = NULL ;
 if ( no_sdus == 1 && ss == 3 ) {
 mac_is_sdu * sdu = get_sdu ( pinfo -> num , tsn , MAC_IS_MIDDLE , & ch ) ;
 if ( sdu ) {
 return add_to_tree ( tvb , pinfo , tree , sdu , offset , maclength , MAC_IS_MIDDLE ) ;
 }
 }
 else if ( sdu_no == 0 && ( ss & 1 ) == 1 ) {
 mac_is_sdu * sdu = get_sdu ( pinfo -> num , tsn , MAC_IS_TAIL , & ch ) ;
 if ( sdu ) {
 return add_to_tree ( tvb , pinfo , tree , sdu , offset , maclength , MAC_IS_TAIL ) ;
 }
 }
 else if ( sdu_no == no_sdus - 1 && ( ss & 2 ) == 2 ) {
 mac_is_sdu * sdu = get_sdu ( pinfo -> num , tsn , MAC_IS_HEAD , & ch ) ;
 if ( sdu ) {
 return add_to_tree ( tvb , pinfo , tree , sdu , offset , maclength , MAC_IS_HEAD ) ;
 }
 }
 else {
 new_tvb = tvb_new_subset ( tvb , offset , maclength , - 1 ) ;
 proto_tree_add_expert ( tree , pinfo , & ei_mac_macis_sdu_complete , new_tvb , 0 , - 1 ) ;
 proto_tree_add_item ( tree , hf_mac_edch_type2_sdu_data , new_tvb , 0 , - 1 , ENC_NA ) ;
 return new_tvb ;
 }
 }
 return NULL ;
 }