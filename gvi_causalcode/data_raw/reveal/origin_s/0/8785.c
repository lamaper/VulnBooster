static void pushfogio ( IO * wrapper , FILE * fog ) {
 _IO * io = calloc ( 1 , sizeof ( _IO ) ) ;
 io -> prev = wrapper -> top ;
 io -> fog = fog ;
 io -> backedup = EOF ;
 io -> cnt = 1 ;
 io -> isloop = false ;
 wrapper -> top = io ;
 }