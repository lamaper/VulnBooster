void TSMimeFieldValueInsert ( TSMBuffer bufp , TSMLoc field_obj , const char * value , int length , int idx ) {
 MIMEFieldSDKHandle * handle = ( MIMEFieldSDKHandle * ) field_obj ;
 HdrHeap * heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 if ( length == - 1 ) {
 length = strlen ( value ) ;
 }
 mime_field_value_insert_comma_val ( heap , handle -> mh , handle -> field_ptr , idx , value , length ) ;
 }