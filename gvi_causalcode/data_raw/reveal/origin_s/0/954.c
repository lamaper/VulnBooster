static int dissect_opcua_message ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data _U_ ) {
 FctParse pfctParse = NULL ;
 enum MessageType msgtype = MSG_INVALID ;
 col_set_str ( pinfo -> cinfo , COL_PROTOCOL , "OpcUa" ) ;
 if ( tvb_memeql ( tvb , 0 , "HEL" , 3 ) == 0 ) {
 msgtype = MSG_HELLO ;
 pfctParse = parseHello ;
 }
 else if ( tvb_memeql ( tvb , 0 , "ACK" , 3 ) == 0 ) {
 msgtype = MSG_ACKNOWLEDGE ;
 pfctParse = parseAcknowledge ;
 }
 else if ( tvb_memeql ( tvb , 0 , "ERR" , 3 ) == 0 ) {
 msgtype = MSG_ERROR ;
 pfctParse = parseError ;
 }
 else if ( tvb_memeql ( tvb , 0 , "MSG" , 3 ) == 0 ) {
 msgtype = MSG_MESSAGE ;
 pfctParse = parseMessage ;
 }
 else if ( tvb_memeql ( tvb , 0 , "OPN" , 3 ) == 0 ) {
 msgtype = MSG_OPENSECURECHANNEL ;
 pfctParse = parseOpenSecureChannel ;
 }
 else if ( tvb_memeql ( tvb , 0 , "CLO" , 3 ) == 0 ) {
 msgtype = MSG_CLOSESECURECHANNEL ;
 pfctParse = parseCloseSecureChannel ;
 }
 else {
 msgtype = MSG_INVALID ;
 }
 col_set_str ( pinfo -> cinfo , COL_INFO , g_szMessageTypes [ msgtype ] ) ;
 if ( pfctParse ) {
 gint offset = 0 ;
 int iServiceId = - 1 ;
 tvbuff_t * next_tvb = tvb ;
 gboolean bParseService = TRUE ;
 gboolean bIsLastFragment = FALSE ;
 proto_item * ti = NULL ;
 proto_tree * transport_tree = NULL ;
 ti = proto_tree_add_item ( tree , proto_opcua , tvb , 0 , - 1 , ENC_NA ) ;
 transport_tree = proto_item_add_subtree ( ti , ett_opcua_transport ) ;
 if ( msgtype == MSG_MESSAGE ) {
 guint8 chunkType = 0 ;
 guint32 opcua_seqid = 0 ;
 guint32 opcua_num = 0 ;
 guint32 opcua_seqnum = 0 ;
 fragment_head * frag_msg = NULL ;
 offset = 3 ;
 chunkType = tvb_get_guint8 ( tvb , offset ) ;
 offset += 1 ;
 offset += 4 ;
 offset += 4 ;
 offset += 4 ;
 opcua_num = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 opcua_seqid = tvb_get_letohl ( tvb , offset ) ;
 offset += 4 ;
 if ( chunkType == 'A' ) {
 fragment_delete ( & opcua_reassembly_table , pinfo , opcua_seqid , NULL ) ;
 col_clear_fence ( pinfo -> cinfo , COL_INFO ) ;
 col_set_str ( pinfo -> cinfo , COL_INFO , "Abort message" ) ;
 offset = 0 ;
 ( * pfctParse ) ( transport_tree , tvb , pinfo , & offset ) ;
 parseAbort ( transport_tree , tvb , pinfo , & offset ) ;
 return tvb_reported_length ( tvb ) ;
 }
 frag_msg = fragment_get ( & opcua_reassembly_table , pinfo , opcua_seqid , NULL ) ;
 if ( frag_msg == NULL ) {
 frag_msg = fragment_get_reassembled_id ( & opcua_reassembly_table , pinfo , opcua_seqid ) ;
 }
 if ( frag_msg != NULL || chunkType != 'F' ) {
 gboolean bSaveFragmented = pinfo -> fragmented ;
 gboolean bMoreFragments = TRUE ;
 tvbuff_t * new_tvb = NULL ;
 pinfo -> fragmented = TRUE ;
 if ( frag_msg == NULL ) {
 opcua_seqnum = 0 ;
 }
 else {
 while ( frag_msg -> next ) {
 frag_msg = frag_msg -> next ;
 }
 opcua_seqnum = frag_msg -> offset + 1 ;
 if ( chunkType == 'F' ) {
 bMoreFragments = FALSE ;
 }
 }
 frag_msg = fragment_add_seq_check ( & opcua_reassembly_table , tvb , offset , pinfo , opcua_seqid , NULL , opcua_seqnum , tvb_captured_length_remaining ( tvb , offset ) , bMoreFragments ) ;
 new_tvb = process_reassembled_data ( tvb , offset , pinfo , "Reassembled Message" , frag_msg , & opcua_frag_items , NULL , transport_tree ) ;
 if ( new_tvb ) {
 bIsLastFragment = TRUE ;
 }
 else {
 col_append_fstr ( pinfo -> cinfo , COL_INFO , " (Message fragment %u)" , opcua_num ) ;
 }
 if ( new_tvb ) {
 next_tvb = new_tvb ;
 }
 else {
 bParseService = FALSE ;
 next_tvb = tvb_new_subset_remaining ( tvb , 0 ) ;
 }
 pinfo -> fragmented = bSaveFragmented ;
 }
 }
 offset = 0 ;
 iServiceId = ( * pfctParse ) ( transport_tree , tvb , pinfo , & offset ) ;
 if ( msgtype == MSG_MESSAGE && bParseService ) {
 if ( bIsLastFragment != FALSE ) {
 offset = 0 ;
 }
 iServiceId = parseService ( transport_tree , next_tvb , pinfo , & offset ) ;
 }
 if ( iServiceId != - 1 ) {
 const gchar * szServiceName = val_to_str ( ( guint32 ) iServiceId , g_requesttypes , "ServiceId %d" ) ;
 if ( bIsLastFragment == FALSE ) {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s: %s" , g_szMessageTypes [ msgtype ] , szServiceName ) ;
 }
 else {
 col_add_fstr ( pinfo -> cinfo , COL_INFO , "%s: %s (Message Reassembled)" , g_szMessageTypes [ msgtype ] , szServiceName ) ;
 }
 }
 }
 return tvb_reported_length ( tvb ) ;
 }