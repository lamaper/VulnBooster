static inline bool is_port_in_range ( int port , HttpConfigPortRange * pr ) {
 while ( pr ) {
 if ( pr -> low == - 1 ) {
 return true ;
 }
 else if ( ( pr -> low <= port ) && ( pr -> high >= port ) ) {
 return true ;
 }
 pr = pr -> next ;
 }
 return false ;
 }