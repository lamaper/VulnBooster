static void nb_resync_indicator ( tvbuff_t * tvb , int offset , proto_tree * tree , const char * cmd_str ) {
 guint16 resync_indicator = tvb_get_letohs ( tvb , offset + NB_DATA2 ) ;
 switch ( resync_indicator ) {
 case 0x0000 : proto_tree_add_uint_format_value ( tree , hf_netb_resync_indicator , tvb , offset + NB_DATA2 , 2 , resync_indicator , "No re-sync" ) ;
 break ;
 case 0x0001 : proto_tree_add_uint_format_value ( tree , hf_netb_resync_indicator , tvb , offset + NB_DATA2 , 2 , resync_indicator , "First '%s' following 'Receive Outstanding'" , cmd_str ) ;
 break ;
 default : proto_tree_add_item ( tree , hf_netb_resync_indicator , tvb , offset + NB_DATA2 , 2 , ENC_LITTLE_ENDIAN ) ;
 break ;
 }
 }