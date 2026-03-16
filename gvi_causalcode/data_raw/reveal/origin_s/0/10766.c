bool isWriteable ( TSMBuffer bufp ) {
 if ( bufp != nullptr ) {
 return ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap -> m_writeable ;
 }
 return false ;
 }