static int ioescapestopped ( IO * wrapper , struct psstack * stack , int sp , const size_t bsize ) {
 _IO * io = wrapper -> top , * iop ;
 int wasstopped ;
 while ( io -> prev != NULL ) {
 iop = io -> prev ;
 wasstopped = io -> isstopped ;
 if ( io -> start != NULL ) free ( io -> start ) ;
 io -> start = NULL ;
 free ( io ) ;
 if ( wasstopped ) {
 wrapper -> top = iop ;
 if ( sp < ( int ) bsize ) {
 stack [ sp ] . type = ps_bool ;
 stack [ sp ++ ] . u . tf = true ;
 }
 return ( sp ) ;
 }
 io = iop ;
 }
 LogError ( _ ( "Use of \"stop\" when not in a stopped\n" ) ) ;
 wrapper -> top = io ;
 return ( sp ) ;
 }