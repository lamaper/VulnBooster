static guint32 number_of_markers ( mpa_state_t * state , struct tcpinfo * tcpinfo , guint8 endpoint ) {
 guint32 size ;
 guint32 offset ;
 size = fpdu_total_length ( tcpinfo ) ;
 offset = get_first_marker_offset ( state , tcpinfo , endpoint ) ;
 if ( offset < size ) {
 return ( ( size - offset ) / MPA_MARKER_INTERVAL ) + 1 ;
 }
 else {
 return 0 ;
 }
 }