static UBool _addAttributeToList ( AttributeListEntry * * first , AttributeListEntry * attr ) {
 UBool bAdded = TRUE ;
 if ( * first == NULL ) {
 attr -> next = NULL ;
 * first = attr ;
 }
 else {
 AttributeListEntry * prev , * cur ;
 int32_t cmp ;
 prev = NULL ;
 cur = * first ;
 while ( TRUE ) {
 if ( cur == NULL ) {
 prev -> next = attr ;
 attr -> next = NULL ;
 break ;
 }
 cmp = uprv_compareInvCharsAsAscii ( attr -> attribute , cur -> attribute ) ;
 if ( cmp < 0 ) {
 if ( prev == NULL ) {
 * first = attr ;
 }
 else {
 prev -> next = attr ;
 }
 attr -> next = cur ;
 break ;
 }
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