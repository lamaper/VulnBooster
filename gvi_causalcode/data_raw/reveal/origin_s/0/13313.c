static UBool _addVariantToList ( VariantListEntry * * first , VariantListEntry * var ) {
 UBool bAdded = TRUE ;
 if ( * first == NULL ) {
 var -> next = NULL ;
 * first = var ;
 }
 else {
 VariantListEntry * prev , * cur ;
 int32_t cmp ;
 prev = NULL ;
 cur = * first ;
 while ( TRUE ) {
 if ( cur == NULL ) {
 prev -> next = var ;
 var -> next = NULL ;
 break ;
 }
 cmp = uprv_compareInvCharsAsAscii ( var -> variant , cur -> variant ) ;
 if ( cmp == 0 ) {
 bAdded = FALSE ;
 break ;
 }
 prev = cur ;
 cur = cur -> next ;
 }
 }
 return bAdded ;
 }