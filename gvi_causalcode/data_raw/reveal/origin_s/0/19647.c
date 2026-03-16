void TSMimeFieldValueSet ( TSMBuffer bufp , TSMLoc field_obj , int idx , const char * value , int length ) {
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field_obj ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 if ( length == - 1 ) {
 length = strlen ( value ) ;
 }
 if ( idx >= 0 ) {
 mime_field_value_set_comma_val ( heap , handle -> mh , handle -> field_ptr , idx , value , length ) ;
 }
 else {
 mime_field_value_set ( heap , handle -> mh , handle -> field_ptr , value , length , true ) ;
 }
 }