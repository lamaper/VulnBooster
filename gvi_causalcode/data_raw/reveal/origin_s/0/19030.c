static guint32 get_first_marker_offset ( mpa_state_t * state , struct tcpinfo * tcpinfo , guint8 endpoint ) {
 guint32 offset = 0 ;
 if ( tcpinfo -> seq > state -> minfo [ endpoint ] . seq ) {
 offset = ( tcpinfo -> seq - state -> minfo [ endpoint ] . seq ) % MPA_MARKER_INTERVAL ;
 }
 if ( tcpinfo -> seq < state -> minfo [ endpoint ] . seq ) {
 offset = state -> minfo [ endpoint ] . seq + ( TCP_MAX_SEQ - tcpinfo -> seq ) % MPA_MARKER_INTERVAL ;
 }
 return ( MPA_MARKER_INTERVAL - offset ) % MPA_MARKER_INTERVAL ;
 }