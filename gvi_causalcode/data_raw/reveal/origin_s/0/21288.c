static void dissect_q931_protocol_discriminator ( tvbuff_t * tvb , int offset , proto_tree * tree ) {
 unsigned int discriminator = tvb_get_guint8 ( tvb , offset ) ;
 if ( discriminator == NLPID_DMS ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "Maintenance messages" ) ;
 }
 else if ( discriminator == NLPID_Q_931 ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "Q.931" ) ;
 }
 else if ( discriminator == NLPID_Q_2931 ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "Q.2931" ) ;
 }
 else if ( ( discriminator >= 16 && discriminator < 63 ) || ( ( discriminator >= 80 ) && ( discriminator < 254 ) ) ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "Network layer or layer 3 protocol (0x%02X)" , discriminator ) ;
 }
 else if ( discriminator >= 64 && discriminator <= 79 ) {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "National use (0x%02X)" , discriminator ) ;
 }
 else {
 proto_tree_add_uint_format_value ( tree , hf_q931_discriminator , tvb , offset , 1 , discriminator , "Reserved (0x%02X)" , discriminator ) ;
 }
 }