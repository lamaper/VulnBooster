static UBool _addExtensionToList ( ExtensionListEntry * * first , ExtensionListEntry * ext , UBool localeToBCP ) {
 UBool bAdded = TRUE ;
 if ( * first == NULL ) {
 ext -> next = NULL ;
 * first = ext ;
 }
 else {
 ExtensionListEntry * prev , * cur ;
 int32_t cmp ;
 prev = NULL ;
 cur = * first ;
 while ( TRUE ) {
 if ( cur == NULL ) {
 prev -> next = ext ;
 ext -> next = NULL ;
 break ;
 }
 if ( localeToBCP ) {
 int32_t len , curlen ;
 len = ( int32_t ) uprv_strlen ( ext -> key ) ;
 curlen = ( int32_t ) uprv_strlen ( cur -> key ) ;
 if ( len == 1 && curlen == 1 ) {
 if ( * ( ext -> key ) == * ( cur -> key ) ) {
 cmp = 0 ;
 }
 else if ( * ( ext -> key ) == PRIVATEUSE ) {
 cmp = 1 ;
 }
 else if ( * ( cur -> key ) == PRIVATEUSE ) {
 cmp = - 1 ;
 }
 else {
 cmp = * ( ext -> key ) - * ( cur -> key ) ;
 }
 }
 else if ( len == 1 ) {
 cmp = * ( ext -> key ) - LDMLEXT ;
 }
 else if ( curlen == 1 ) {
 cmp = LDMLEXT - * ( cur -> key ) ;
 }
 else {
 cmp = uprv_compareInvCharsAsAscii ( ext -> key , cur -> key ) ;
 if ( cmp != 0 ) {
 if ( uprv_strcmp ( cur -> key , LOCALE_ATTRIBUTE_KEY ) == 0 ) {
 cmp = 1 ;
 }
 else if ( uprv_strcmp ( ext -> key , LOCALE_ATTRIBUTE_KEY ) == 0 ) {
 cmp = - 1 ;
 }
 }
 }
 }
 else {
 cmp = uprv_compareInvCharsAsAscii ( ext -> key , cur -> key ) ;
 }
 if ( cmp < 0 ) {
 if ( prev == NULL ) {
 * first = ext ;
 }
 else {
 prev -> next = ext ;
 }
 ext -> next = cur ;
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