static const char * ultag_getExtensionValue ( const ULanguageTag * langtag , int32_t idx ) {
 const char * val = NULL ;
 ExtensionListEntry * cur = langtag -> extensions ;
 int32_t i = 0 ;
 while ( cur ) {
 if ( i == idx ) {
 val = cur -> value ;
 break ;
 }
 cur = cur -> next ;
 i ++ ;
 }
 return val ;
 }