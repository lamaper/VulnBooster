void xsltFreeAVTList ( void * avt ) {
 xsltAttrVTPtr cur = ( xsltAttrVTPtr ) avt , next ;
 while ( cur != NULL ) {
 next = cur -> next ;
 xsltFreeAttrVT ( cur ) ;
 cur = next ;
 }
 }