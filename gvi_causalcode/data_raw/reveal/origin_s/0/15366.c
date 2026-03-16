static Node * strip_array_coercion ( Node * node ) {
 for ( ;
 ;
 ) {
 if ( node && IsA ( node , ArrayCoerceExpr ) && ( ( ArrayCoerceExpr * ) node ) -> elemfuncid == InvalidOid ) {
 node = ( Node * ) ( ( ArrayCoerceExpr * ) node ) -> arg ;
 }
 else if ( node && IsA ( node , RelabelType ) ) {
 node = ( Node * ) ( ( RelabelType * ) node ) -> arg ;
 }
 else break ;
 }
 return node ;
 }