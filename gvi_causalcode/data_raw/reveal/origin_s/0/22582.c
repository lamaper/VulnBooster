int xmlListInsert ( xmlListPtr l , void * data ) {
 xmlLinkPtr lkPlace , lkNew ;
 if ( l == NULL ) return ( 1 ) ;
 lkPlace = xmlListLowerSearch ( l , data ) ;
 lkNew = ( xmlLinkPtr ) xmlMalloc ( sizeof ( xmlLink ) ) ;
 if ( lkNew == NULL ) {
 xmlGenericError ( xmlGenericErrorContext , "Cannot initialize memory for new link" ) ;
 return ( 1 ) ;
 }
 lkNew -> data = data ;
 lkPlace = lkPlace -> prev ;
 lkNew -> next = lkPlace -> next ;
 ( lkPlace -> next ) -> prev = lkNew ;
 lkPlace -> next = lkNew ;
 lkNew -> prev = lkPlace ;
 return 0 ;
 }