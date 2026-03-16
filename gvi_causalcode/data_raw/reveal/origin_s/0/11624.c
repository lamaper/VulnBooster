static void dissect_rsvp_label ( proto_tree * ti , proto_tree * rsvp_object_tree , tvbuff_t * tvb , int offset , int obj_length , int rsvp_class , int type ) {
 int offset2 = offset + 4 ;
 int mylen , i ;
 const char * name ;
 name = ( rsvp_class == RSVP_CLASS_SUGGESTED_LABEL ? "SUGGESTED LABEL" : ( rsvp_class == RSVP_CLASS_UPSTREAM_LABEL ? "UPSTREAM LABEL" : ( rsvp_class == RSVP_CLASS_RECOVERY_LABEL ? "RECOVERY LABEL" : "LABEL" ) ) ) ;
 mylen = obj_length - 4 ;
 switch ( type ) {
 case 1 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "1 (Packet Label)" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_label , tvb , offset2 , 4 , ENC_BIG_ENDIAN ) ;
 proto_item_set_text ( ti , "%s: %u" , name , tvb_get_ntohl ( tvb , offset2 ) ) ;
 break ;
 case 2 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "2 (Generalized Label)" ) ;
 if ( rsvp_generalized_label_option == 1 ) {
 proto_item_set_text ( ti , "%s: Generalized: " , name ) ;
 for ( i = 0 ;
 i < mylen ;
 i += 4 ) {
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_generalized_label , tvb , offset2 + i , 4 , ENC_BIG_ENDIAN ) ;
 if ( i < 16 ) {
 proto_item_append_text ( ti , "0x%x%s" , tvb_get_ntohl ( tvb , offset2 + i ) , i + 4 < mylen ? ", " : "" ) ;
 }
 else if ( i == 16 ) {
 proto_item_append_text ( ti , "..." ) ;
 }
 }
 }
 else if ( rsvp_generalized_label_option == 2 ) {
 dissect_glabel_sdh ( ti , rsvp_object_tree , tvb , offset2 ) ;
 }
 else if ( rsvp_generalized_label_option == 4 ) {
 dissect_glabel_g709 ( ti , rsvp_object_tree , tvb , offset2 ) ;
 }
 else if ( rsvp_generalized_label_option == 3 ) {
 dissect_glabel_lambda ( ti , rsvp_object_tree , tvb , offset2 ) ;
 }
 else if ( rsvp_generalized_label_option == 5 ) {
 dissect_glabel_evpl ( ti , rsvp_object_tree , tvb , offset2 ) ;
 }
 break ;
 case 4 : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "4 (Generalized Channel_set)" ) ;
 proto_item_append_text ( ti , ": Generalized Channel_set" ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_data , tvb , offset2 , mylen , ENC_NA ) ;
 break ;
 default : proto_tree_add_uint_format_value ( rsvp_object_tree , hf_rsvp_ctype , tvb , offset + 3 , 1 , type , "Unknown (%u)" , type ) ;
 proto_tree_add_item ( rsvp_object_tree , hf_rsvp_label_data , tvb , offset2 , mylen , ENC_NA ) ;
 break ;
 }
 }