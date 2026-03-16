int xmlListPushBack ( xmlListPtr l , void * data ) {
 xmlLinkPtr lkPlace , lkNew ;
 if ( l == NULL ) return ( 0 ) ;
 lkPlace = l -> sentinel -> prev ;
 if ( NULL == ( lkNew = ( xmlLinkPtr ) xmlMalloc ( sizeof ( xmlLink ) ) ) ) {
 xmlGenericError ( xmlGenericErrorContext , "Cannot initialize memory for new link" ) ;
 return ( 0 ) ;
 }
 lkNew -> data = data ;
 lkNew -> next = lkPlace -> next ;
 ( lkPlace -> next ) -> prev = lkNew ;
 lkPlace -> next = lkNew ;
 lkNew -> prev = lkPlace ;
 return 1 ;
 }