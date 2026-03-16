static const char * ultag_getExtensionKey ( const ULanguageTag * langtag , int32_t idx ) {
 const char * key = NULL ;
 ExtensionListEntry * cur = langtag -> extensions ;
 int32_t i = 0 ;
 while ( cur ) {
 if ( i == idx ) {
 key = cur -> key ;
 break ;
 }
 cur = cur -> next ;
 i ++ ;
 }
 return key ;
 }