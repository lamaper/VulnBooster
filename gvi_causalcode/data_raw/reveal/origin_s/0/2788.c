inline MIMEHdrImpl * _hdr_obj_to_mime_hdr_impl ( HdrHeapObjImpl * obj ) {
 MIMEHdrImpl * impl ;
 if ( obj -> m_type == HDR_HEAP_OBJ_HTTP_HEADER ) {
 impl = ( ( HTTPHdrImpl * ) obj ) -> m_fields_impl ;
 }
 else if ( obj -> m_type == HDR_HEAP_OBJ_MIME_HEADER ) {
 impl = ( MIMEHdrImpl * ) obj ;
 }
 else {
 ink_release_assert ( ! "mloc not a header type" ) ;
 impl = nullptr ;
 }
 return impl ;
 }