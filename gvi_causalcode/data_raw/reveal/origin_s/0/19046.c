static void desegment_iax ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * iax2_tree , proto_tree * tree , gboolean video , iax_packet_data * iax_packet ) {
 iax_call_data * iax_call = iax_packet -> call_data ;
 iax_call_dirdata * dirdata ;
 gpointer value = NULL ;
 guint32 frag_offset = 0 ;
 fragment_head * fd_head ;
 gboolean must_desegment = FALSE ;
 DISSECTOR_ASSERT ( iax_call ) ;
 pinfo -> can_desegment = 2 ;
 pinfo -> desegment_offset = 0 ;
 pinfo -> desegment_len = 0 ;


 if ( ( ! pinfo -> fd -> flags . visited && ( dirdata -> current_frag_bytes > 0 ) ) || ( ( value = g_hash_table_lookup ( iax_fid_table , GUINT_TO_POINTER ( pinfo -> fd -> num ) ) ) != NULL ) ) {
 guint32 fid ;
 guint32 frag_len = tvb_reported_length ( tvb ) ;
 gboolean complete ;

 c_f_b: %u;
 hash: %u->%u" , pinfo -> fd -> flags . visited ? 1 : 0 , dirdata -> current_frag_bytes , pinfo -> fd -> num , dirdata -> current_frag_id ) ;

 guint32 tot_len ;
 fid = dirdata -> current_frag_id ;
 tot_len = dirdata -> current_frag_minlen ;
 DISSECTOR_ASSERT ( g_hash_table_lookup ( iax_fid_table , GUINT_TO_POINTER ( pinfo -> fd -> num ) ) == NULL ) ;
 g_hash_table_insert ( iax_fid_table , GUINT_TO_POINTER ( pinfo -> fd -> num ) , GUINT_TO_POINTER ( fid ) ) ;
 frag_offset = dirdata -> current_frag_bytes ;
 dirdata -> current_frag_bytes += frag_len ;
 complete = dirdata -> current_frag_bytes > tot_len ;

 frag_offset: %u;
 c_f_b: %u;
 totlen: %u" , pinfo -> fd -> num , fid , frag_offset , dirdata -> current_frag_bytes , tot_len ) ;

 else {
 fid = GPOINTER_TO_UINT ( value ) ;
 dirdata -> current_frag_bytes = 0 ;
 complete = FALSE ;
 }
 fd_head = fragment_add ( & iax_reassembly_table , tvb , 0 , pinfo , fid , NULL , frag_offset , frag_len , ! complete ) ;
 if ( fd_head && ( pinfo -> fd -> num == fd_head -> reassembled_in ) ) {
 gint32 old_len ;
 tvbuff_t * next_tvb = tvb_new_chain ( tvb , fd_head -> tvb_data ) ;
 add_new_data_source ( pinfo , next_tvb , "Reassembled IAX2" ) ;
 process_iax_pdu ( next_tvb , pinfo , tree , video , iax_packet ) ;
 old_len = ( gint32 ) ( tvb_reported_length ( next_tvb ) - frag_len ) ;
 if ( pinfo -> desegment_len && ( pinfo -> desegment_offset < old_len ) ) {
 fragment_set_partial_reassembly ( & iax_reassembly_table , pinfo , fid , NULL ) ;
 if ( pinfo -> desegment_len == DESEGMENT_ONE_MORE_SEGMENT ) {
 dirdata -> current_frag_minlen = fd_head -> datalen + 1 ;
 }
 else {
 dirdata -> current_frag_minlen = fd_head -> datalen + pinfo -> desegment_len ;
 }
 }
 else {
 proto_item * iax_tree_item , * frag_tree_item ;
 show_fragment_tree ( fd_head , & iax2_fragment_items , tree , pinfo , next_tvb , & frag_tree_item ) ;
 iax_tree_item = proto_item_get_parent ( proto_tree_get_parent ( iax2_tree ) ) ;
 if ( frag_tree_item && iax_tree_item ) proto_tree_move_item ( tree , iax_tree_item , frag_tree_item ) ;
 dirdata -> current_frag_minlen = dirdata -> current_frag_id = dirdata -> current_frag_bytes = 0 ;
 if ( pinfo -> desegment_len ) {
 must_desegment = TRUE ;
 pinfo -> desegment_offset -= old_len ;
 }
 fd_head = NULL ;
 }
 }
 }
 else {
 process_iax_pdu ( tvb , pinfo , tree , video , iax_packet ) ;
 if ( pinfo -> desegment_len ) {
 must_desegment = TRUE ;
 }
 fd_head = NULL ;
 }
 if ( must_desegment ) {
 guint32 fid = pinfo -> fd -> num ;
 guint32 deseg_offset = pinfo -> desegment_offset ;
 guint32 frag_len = tvb_reported_length_remaining ( tvb , deseg_offset ) ;
 dirdata -> current_frag_id = fid ;
 dirdata -> current_frag_bytes = frag_len ;
 if ( pinfo -> desegment_len == DESEGMENT_ONE_MORE_SEGMENT ) {
 dirdata -> current_frag_minlen = frag_len + 1 ;
 }
 else {
 dirdata -> current_frag_minlen = frag_len + pinfo -> desegment_len ;
 }
 fd_head = fragment_add ( & iax_reassembly_table , tvb , deseg_offset , pinfo , fid , NULL , 0 , frag_len , TRUE ) ;

 " "Bytes remaining in this segment: %u;
 min required bytes: %u\n" , deseg_offset , frag_len , frag_len + pinfo -> desegment_len ) ;

 if ( fd_head != NULL ) {
 guint32 deseg_offset = pinfo -> desegment_offset ;
 if ( fd_head -> reassembled_in != 0 && ! ( fd_head -> flags & FD_PARTIAL_REASSEMBLY ) ) {
 proto_item * iax_tree_item ;
 iax_tree_item = proto_tree_add_uint ( tree , hf_iax2_reassembled_in , tvb , deseg_offset , tvb_reported_length_remaining ( tvb , deseg_offset ) , fd_head -> reassembled_in ) ;
 PROTO_ITEM_SET_GENERATED ( iax_tree_item ) ;
 }
 else {
 proto_tree_add_item ( tree , hf_iax2_fragment_unfinished , tvb , deseg_offset , - 1 , ENC_NA ) ;
 }
 if ( pinfo -> desegment_offset == 0 ) {
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "IAX2" ) ;
 col_set_str ( pinfo -> cinfo , COL_INFO , "[IAX2 segment of a reassembled PDU]" ) ;
 }
 }
 pinfo -> can_desegment = 0 ;
 pinfo -> desegment_offset = 0 ;
 pinfo -> desegment_len = 0 ;
 }