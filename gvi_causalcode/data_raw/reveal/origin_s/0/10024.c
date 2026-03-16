static UHashTok _uhash_setElement ( UHashtable * hash , UHashElement * e , int32_t hashcode , UHashTok key , UHashTok value , int8_t hint ) {
 UHashTok oldValue = e -> value ;
 if ( hash -> keyDeleter != NULL && e -> key . pointer != NULL && e -> key . pointer != key . pointer ) {
 ( * hash -> keyDeleter ) ( e -> key . pointer ) ;
 }
 if ( hash -> valueDeleter != NULL ) {
 if ( oldValue . pointer != NULL && oldValue . pointer != value . pointer ) {
 ( * hash -> valueDeleter ) ( oldValue . pointer ) ;
 }
 oldValue . pointer = NULL ;
 }
 if ( hint & HINT_KEY_POINTER ) {
 e -> key . pointer = key . pointer ;
 }
 else {
 e -> key = key ;
 }
 if ( hint & HINT_VALUE_POINTER ) {
 e -> value . pointer = value . pointer ;
 }
 else {
 e -> value = value ;
 }
 e -> hashcode = hashcode ;
 return oldValue ;
 }