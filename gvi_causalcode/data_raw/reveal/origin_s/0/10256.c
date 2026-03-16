static const char * ultag_getVariant ( const ULanguageTag * langtag , int32_t idx ) {
 const char * var = NULL ;
 VariantListEntry * cur = langtag -> variants ;
 int32_t i = 0 ;
 while ( cur ) {
 if ( i == idx ) {
 var = cur -> variant ;
 break ;
 }
 cur = cur -> next ;
 i ++ ;
 }
 return var ;
 }