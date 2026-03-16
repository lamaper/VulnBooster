int dissect_ber_choice ( asn1_ctx_t * actx , proto_tree * parent_tree , tvbuff_t * tvb , int offset , const ber_choice_t * choice , gint hf_id , gint ett_id , gint * branch_taken ) {
 gint8 ber_class ;
 gboolean pc , ind , imp_tag = FALSE ;
 gint32 tag ;
 guint32 len ;
 proto_tree * tree = parent_tree ;
 proto_item * item = NULL ;
 int end_offset , start_offset , count ;
 int hoffset = offset ;
 gint length ;
 tvbuff_t * next_tvb ;
 gboolean first_pass ;
 header_field_info * hfinfo ;
 const ber_choice_t * ch ;

 const char * name ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 if ( tvb_reported_length_remaining ( tvb , offset ) > 3 ) {
 printf ( "CHOICE dissect_ber_choice(%s) entered offset:%d len:%d %02x:%02x:%02x\n" , name , offset , tvb_reported_length_remaining ( tvb , offset ) , tvb_get_guint8 ( tvb , offset ) , tvb_get_guint8 ( tvb , offset + 1 ) , tvb_get_guint8 ( tvb , offset + 2 ) ) ;
 }
 else {
 printf ( "CHOICE dissect_ber_choice(%s) entered len:%d\n" , name , tvb_reported_length_remaining ( tvb , offset ) ) ;
 }
 }

 if ( branch_taken ) {
 * branch_taken = - 1 ;
 }
 if ( tvb_reported_length_remaining ( tvb , offset ) == 0 ) {
 item = proto_tree_add_string_format_value ( parent_tree , hf_ber_error , tvb , offset , 0 , "empty_choice" , "Empty choice was found" ) ;
 expert_add_info ( actx -> pinfo , item , & ei_ber_empty_choice ) ;
 return offset ;
 }
 offset = get_ber_identifier ( tvb , offset , & ber_class , & pc , & tag ) ;
 offset = get_ber_length ( tvb , offset , & len , & ind ) ;
 end_offset = offset + len ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 switch ( hfinfo -> type ) {
 case FT_UINT8 : case FT_UINT16 : case FT_UINT24 : case FT_UINT32 : break ;
 default : proto_tree_add_expert_format ( tree , actx -> pinfo , & ei_hf_field_not_integer_type , tvb , offset , len , "dissect_ber_choice(): frame:%u offset:%d Was passed an HF field that was not integer type : %s" , actx -> pinfo -> fd -> num , offset , hfinfo -> abbrev ) ;
 return end_offset ;
 }
 }
 ch = choice ;
 first_pass = TRUE ;
 while ( ch -> func || first_pass ) {
 if ( branch_taken ) {
 ( * branch_taken ) ++ ;
 }
 if ( ! ch -> func ) {
 first_pass = FALSE ;
 ch = choice ;
 if ( branch_taken ) {
 * branch_taken = - 1 ;
 }
 continue ;
 }


 if ( ! ( ch -> flags & BER_FLAGS_NOOWNTAG ) ) {
 hoffset = dissect_ber_identifier ( actx -> pinfo , tree , tvb , start_offset , NULL , NULL , NULL ) ;
 hoffset = dissect_ber_length ( actx -> pinfo , tree , tvb , hoffset , NULL , NULL ) ;
 start_offset = hoffset ;
 if ( ind ) {
 length = len - 2 ;
 }
 else {
 length = len ;
 }
 }
 else {
 length = end_offset - hoffset ;
 }
 if ( hf_id >= 0 ) {
 if ( parent_tree ) {
 item = proto_tree_add_uint ( parent_tree , hf_id , tvb , hoffset , end_offset - hoffset , ch -> value ) ;
 tree = proto_item_add_subtree ( item , ett_id ) ;
 }
 }

 else next_tvb = tvb ;


 const char * name ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 if ( tvb_reported_length_remaining ( next_tvb , 0 ) > 3 ) {
 printf ( "CHOICE dissect_ber_choice(%s) calling subdissector start_offset:%d offset:%d len:%d %02x:%02x:%02x\n" , name , start_offset , offset , tvb_reported_length_remaining ( next_tvb , 0 ) , tvb_get_guint8 ( next_tvb , 0 ) , tvb_get_guint8 ( next_tvb , 1 ) , tvb_get_guint8 ( next_tvb , 2 ) ) ;
 }
 else {
 printf ( "CHOICE dissect_ber_choice(%s) calling subdissector len:%d\n" , name , tvb_reported_length ( next_tvb ) ) ;
 }
 }

 THROW ( ReportedBoundsError ) ;
 }
 imp_tag = FALSE ;
 if ( ( ch -> flags & BER_FLAGS_IMPLTAG ) ) imp_tag = TRUE ;
 count = ch -> func ( imp_tag , next_tvb , 0 , actx , tree , * ch -> p_id ) ;

 const char * name ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 printf ( "CHOICE dissect_ber_choice(%s) subdissector ate %d bytes\n" , name , count ) ;
 }

 ch ++ ;

 const char * name ;
 if ( hf_id >= 0 ) {
 hfinfo = proto_registrar_get_nth ( hf_id ) ;
 name = hfinfo -> name ;
 }
 else {
 name = "unnamed" ;
 }
 printf ( "CHOICE dissect_ber_choice(%s) trying again\n" , name ) ;
 }

 }
 if ( ! ( ch -> flags & BER_FLAGS_NOOWNTAG ) ) {
 if ( ind ) {
 if ( show_internal_ber_fields ) {
 proto_tree_add_item ( tree , hf_ber_choice_eoc , tvb , end_offset - 2 , 2 , ENC_NA ) ;
 }
 }
 }
 return end_offset ;
 }
 ch ++ ;
 }
 if ( branch_taken ) {
 * branch_taken = - 1 ;
 }

 expert_add_info ( actx -> pinfo , item , & ei_ber_choice_not_found ) ;
 return end_offset ;

 }