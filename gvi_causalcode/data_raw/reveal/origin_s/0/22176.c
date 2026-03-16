hb_set_t * hb_set_get_empty ( void ) {
 static const hb_set_t _hb_set_nil = {
 HB_OBJECT_HEADER_STATIC , true , {
 0 }
 }
 ;
 return const_cast < hb_set_t * > ( & _hb_set_nil ) ;
 }