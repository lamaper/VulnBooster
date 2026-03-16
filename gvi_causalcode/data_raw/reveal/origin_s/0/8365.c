static gboolean is_mpa_fpdu ( packet_info * pinfo ) {
 conversation_t * conversation = NULL ;
 mpa_state_t * state = NULL ;
 conversation = find_conversation ( pinfo -> num , & pinfo -> src , & pinfo -> dst , pinfo -> ptype , pinfo -> srcport , pinfo -> destport , 0 ) ;
 if ( ! conversation ) {
 return FALSE ;
 }
 state = get_mpa_state ( conversation ) ;
 if ( ! state ) {
 return FALSE ;
 }
 if ( ! state -> full_operation ) {
 return FALSE ;
 }
 if ( pinfo -> num == state -> req_frame_num || pinfo -> num == state -> rep_frame_num ) {
 return FALSE ;
 }
 else {
 return TRUE ;
 }
 }