static int32_t ultag_getVariantsSize ( const ULanguageTag * langtag ) {
 int32_t size = 0 ;
 VariantListEntry * cur = langtag -> variants ;
 while ( TRUE ) {
 if ( cur == NULL ) {
 break ;
 }
 size ++ ;
 cur = cur -> next ;
 }
 return size ;
 }