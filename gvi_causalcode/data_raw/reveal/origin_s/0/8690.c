static void * _getBuffer ( UEnumeration * en , int32_t capacity ) {
 if ( en -> baseContext != NULL ) {
 if ( ( ( _UEnumBuffer * ) en -> baseContext ) -> len < capacity ) {
 capacity += PAD ;
 en -> baseContext = uprv_realloc ( en -> baseContext , sizeof ( int32_t ) + capacity ) ;
 if ( en -> baseContext == NULL ) {
 return NULL ;
 }
 ( ( _UEnumBuffer * ) en -> baseContext ) -> len = capacity ;
 }
 }
 else {
 capacity += PAD ;
 en -> baseContext = uprv_malloc ( sizeof ( int32_t ) + capacity ) ;
 if ( en -> baseContext == NULL ) {
 return NULL ;
 }
 ( ( _UEnumBuffer * ) en -> baseContext ) -> len = capacity ;
 }
 return ( void * ) & ( ( _UEnumBuffer * ) en -> baseContext ) -> data ;
 }