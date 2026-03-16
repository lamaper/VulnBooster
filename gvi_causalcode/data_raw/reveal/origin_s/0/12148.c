hb_blob_t * hb_blob_get_empty ( void ) {
 static const hb_blob_t _hb_blob_nil = {
 HB_OBJECT_HEADER_STATIC , true , NULL , 0 , HB_MEMORY_MODE_READONLY , NULL , NULL }
 ;
 return const_cast < hb_blob_t * > ( & _hb_blob_nil ) ;
 }