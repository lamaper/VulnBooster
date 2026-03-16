static gboolean dissect_iwarp_mpa ( tvbuff_t * tvb , packet_info * pinfo , proto_tree * tree , void * data ) {
 tvbuff_t * next_tvb = NULL ;
 conversation_t * conversation = NULL ;
 mpa_state_t * state = NULL ;
 struct tcpinfo * tcpinfo ;
 guint8 endpoint = 3 ;
 guint16 ulpdu_length = 0 ;
 if ( data == NULL ) return FALSE ;
 tcpinfo = ( struct tcpinfo * ) data ;
 if ( tvb_captured_length ( tvb ) >= MPA_SMALLEST_FPDU_LEN && is_mpa_fpdu ( pinfo ) ) {
 conversation = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , pinfo -> srcport , pinfo -> destport , 0 ) ;
 state = get_mpa_state ( conversation ) ;
 if ( pinfo -> srcport == state -> minfo [ MPA_INITIATOR ] . port ) {
 endpoint = MPA_INITIATOR ;
 }
 else if ( pinfo -> srcport == state -> minfo [ MPA_RESPONDER ] . port ) {
 endpoint = MPA_RESPONDER ;
 }
 else {
 REPORT_DISSECTOR_BUG ( "endpoint cannot be determined" ) ;
 }
 if ( ( state -> ini_exp_m_res || state -> res_exp_m_ini ) && endpoint <= MPA_RESPONDER ) {
 if ( ! state -> minfo [ endpoint ] . valid ) {
 state -> minfo [ endpoint ] . seq = tcpinfo -> seq ;
 state -> minfo [ endpoint ] . valid = TRUE ;
 }
 }
 ulpdu_length = dissect_mpa_fpdu ( tvb , pinfo , tree , state , tcpinfo , endpoint ) ;
 if ( ! ulpdu_length ) return FALSE ;
 if ( endpoint <= MPA_RESPONDER && state -> minfo [ endpoint ] . valid && number_of_markers ( state , tcpinfo , endpoint ) > 0 ) {
 next_tvb = tvb_new_subset_length ( remove_markers ( tvb , pinfo , get_first_marker_offset ( state , tcpinfo , endpoint ) , number_of_markers ( state , tcpinfo , endpoint ) , fpdu_total_length ( tcpinfo ) ) , MPA_ULPDU_LENGTH_LEN , ulpdu_length ) ;
 }
 else {
 next_tvb = tvb_new_subset_length ( tvb , MPA_ULPDU_LENGTH_LEN , ulpdu_length ) ;
 }
 if ( ddp_rdmap_handle ) {
 call_dissector ( ddp_rdmap_handle , next_tvb , pinfo , tree ) ;
 }
 else {
 REPORT_DISSECTOR_BUG ( "ddp_handle was null" ) ;
 }
 return TRUE ;
 }
 if ( tvb_captured_length ( tvb ) >= MPA_REQ_REP_FRAME_HEADER_LEN ) {
 if ( is_mpa_req ( tvb , pinfo ) ) return dissect_mpa_req_rep ( tvb , pinfo , tree , MPA_REQUEST_FRAME ) ;
 else if ( is_mpa_rep ( tvb , pinfo ) ) return dissect_mpa_req_rep ( tvb , pinfo , tree , MPA_REPLY_FRAME ) ;
 }
 return FALSE ;
 }