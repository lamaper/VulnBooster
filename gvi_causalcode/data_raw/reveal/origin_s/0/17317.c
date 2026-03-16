static void dissect_zcl_part_multiack ( tvbuff_t * tvb , proto_tree * tree , guint * offset ) {
 guint tvb_len = tvb_reported_length ( tvb ) ;
 guint i = 0 ;
 guint8 options ;
 guint16 first_frame_id ;
 guint16 nack_id ;
 static const int * ack_opts [ ] = {
 & hf_zbee_zcl_part_ack_opt_nack_id_len , & hf_zbee_zcl_part_ack_opt_res , NULL }
 ;
 options = tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_bitmask ( tree , tvb , * offset , hf_zbee_zcl_part_ack_opt , ett_zbee_zcl_part_ack_opts , ack_opts , ENC_NA ) ;
 * offset += 1 ;
 if ( ( options & ZBEE_ZCL_PART_ACK_OPT_NACK_LEN ) == 0 ) {
 first_frame_id = ( guint16 ) tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_first_frame_id , tvb , * offset , 1 , ( first_frame_id & 0xFF ) ) ;
 * offset += 1 ;
 }
 else {
 first_frame_id = tvb_get_letohs ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_first_frame_id , tvb , * offset , 2 , first_frame_id ) ;
 * offset += 2 ;
 }
 while ( * offset < tvb_len && i < ZBEE_ZCL_PART_NUM_NACK_ID_ETT ) {
 if ( ( options & ZBEE_ZCL_PART_ACK_OPT_NACK_LEN ) == 0 ) {
 nack_id = ( guint16 ) tvb_get_guint8 ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_nack_id , tvb , * offset , 1 , ( nack_id & 0xFF ) ) ;
 * offset += 1 ;
 }
 else {
 nack_id = tvb_get_letohs ( tvb , * offset ) ;
 proto_tree_add_item ( tree , hf_zbee_zcl_part_nack_id , tvb , * offset , 2 , nack_id ) ;
 * offset += 2 ;
 }
 i ++ ;
 }
 }