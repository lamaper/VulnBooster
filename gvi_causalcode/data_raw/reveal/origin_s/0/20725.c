static void dissect_rsvp_diffserv ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class _U_ , int type ) {
 int mapnb , count ;
 int * hfindexes [ ] = {
 & hf_rsvp_filter [ RSVPF_DIFFSERV_MAP ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_MAP_EXP ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_DSCP ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_CODE ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_BIT14 ] , & hf_rsvp_filter [ RSVPF_DIFFSERV_PHBID_BIT15 ] }
 ;
 gint * etts [ ] = {
 & TREE ( TT_DIFFSERV_MAP ) , & TREE ( TT_DIFFSERV_MAP_PHBID ) }
 ;
 proto_item_set_text ( ti , "DIFFSERV: " ) ;
 offset += 3 ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset , 1 , type , "1 - E-LSP" ) ;
 proto_tree_add_uint ( rsvp_object_tree , hf_rsvp_filter [ RSVPF_DIFFSERV_MAPNB ] , tvb , offset + 4 , 1 , mapnb = tvb_get_guint8 ( tvb , offset + 4 ) & 15 ) ;
 proto_item_append_text ( ti , "E-LSP, %u MAP%s" , mapnb , ( mapnb == 0 ) ? "" : "s" ) ;
 offset += 5 ;
 for ( count = 0 ;
 count < mapnb ;
 count ++ ) {
 dissect_diffserv_mpls_common ( tvb , rsvp_object_tree , type , offset , hfindexes , etts ) ;
 offset += 4 ;
 }
 break ;
 case 2 : proto_item_append_text ( ti , "L-LSP" ) ;
 proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset , 1 , type , "2 - L-LSP" ) ;
 dissect_diffserv_mpls_common ( tvb , rsvp_object_tree , type , offset + 3 , hfindexes , etts ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_diffserv_data , tvb , offset + 1 , obj_length - 4 , ENC_NA ) ;
 break ;
 }
 }