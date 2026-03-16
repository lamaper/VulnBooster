static void pushio ( IO * wrapper , FILE * ps , char * macro , int cnt ) {
 _IO * io = calloc ( 1 , sizeof ( _IO ) ) ;
 io -> prev = wrapper -> top ;
 io -> ps = ps ;
 io -> macro = io -> start = copy ( macro ) ;
 io -> backedup = EOF ;
 if ( cnt == - 1 ) {
 io -> cnt = 1 ;
 io -> isstopped = true ;
 }
 else if ( cnt == 0 ) {
 io -> cnt = 1 ;
 io -> isloop = false ;
 }
 else {
 io -> cnt = cnt ;
 io -> isloop = true ;
 }
 wrapper -> top = io ;
 }