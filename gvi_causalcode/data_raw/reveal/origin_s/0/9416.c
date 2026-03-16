inline MIMEHdrImpl * _hdr_mloc_to_mime_hdr_impl ( TSMLoc mloc ) {
 return _hdr_obj_to_mime_hdr_impl ( ( HdrHeapObjImpl * ) mloc ) ;
 }