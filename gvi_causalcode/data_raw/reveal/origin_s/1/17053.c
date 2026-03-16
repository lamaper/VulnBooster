xmlListPtr xmlListCreate ( xmlListDeallocator deallocator , xmlListDataCompare compare ) {
 xmlListPtr l ;
 if ( NULL == ( l = ( xmlListPtr ) xmlMalloc ( sizeof ( xmlList ) ) ) ) {
 xmlGenericError ( xmlGenericErrorContext , "Cannot initialize memory for list" ) ;
 return ( NULL ) ;
 }
 memset ( l , 0 , sizeof ( xmlList ) ) ;
 if ( NULL == ( l -> sentinel = ( xmlLinkPtr ) xmlMalloc ( sizeof ( xmlLink ) ) ) ) {
 xmlGenericError ( xmlGenericErrorContext , "Cannot initialize memory for sentinel" ) ;
 xmlFree ( l ) ;
 return ( NULL ) ;
 }
 l -> sentinel -> next = l -> sentinel ;
 l -> sentinel -> prev = l -> sentinel ;
 l -> sentinel -> data = NULL ;
 if ( deallocator != NULL ) l -> linkDeallocator = deallocator ;
 if ( compare != NULL ) l -> linkCompare = compare ;
 else l -> linkCompare = xmlLinkCompare ;
 return l ;
 }