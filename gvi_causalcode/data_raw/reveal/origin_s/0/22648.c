static void ioescapeloop ( IO * wrapper ) {
 _IO * io = wrapper -> top , * iop ;
 int wasloop ;
 while ( io -> prev != NULL && ! io -> isstopped ) {
 iop = io -> prev ;
 wasloop = io -> isloop ;
 if ( io -> start != NULL ) free ( io -> start ) ;
 io -> start = NULL ;
 free ( io ) ;
 if ( wasloop ) {
 wrapper -> top = iop ;
 return ;
 }
 io = iop ;
 }
 LogError ( _ ( "Use of \"exit\" when not in a loop\n" ) ) ;
 wrapper -> top = io ;
 }