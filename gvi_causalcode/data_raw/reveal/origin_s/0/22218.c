static int32_t ultag_getExtensionsSize ( const ULanguageTag * langtag ) {
 int32_t size = 0 ;
 ExtensionListEntry * cur = langtag -> extensions ;
 while ( TRUE ) {
 if ( cur == NULL ) {
 break ;
 }
 size ++ ;
 cur = cur -> next ;
 }
 return size ;
 }