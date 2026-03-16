static size_t readfromfile ( struct Form * form , char * buffer , size_t size ) {
 size_t nread ;
 bool callback = ( form -> data -> type == FORM_CALLBACK ) ? TRUE : FALSE ;
 if ( callback ) {
 if ( form -> fread_func == ZERO_NULL ) return 0 ;
 else nread = form -> fread_func ( buffer , 1 , size , form -> data -> line ) ;
 }
 else {
 if ( ! form -> fp ) {
 form -> fp = fopen_read ( form -> data -> line , "rb" ) ;
 if ( ! form -> fp ) return ( size_t ) - 1 ;
 }
 nread = fread ( buffer , 1 , size , form -> fp ) ;
 }
 if ( ! nread ) {
 if ( form -> fp ) {
 fclose ( form -> fp ) ;
 form -> fp = NULL ;
 }
 form -> data = form -> data -> next ;
 }
 return nread ;
 }