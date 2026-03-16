asn1_parser_t * asn1_parser_create ( asn1Object_t const * objects , chunk_t blob ) {
 private_asn1_parser_t * this ;
 INIT ( this , . public = {
 . iterate = _iterate , . get_level = _get_level , . set_top_level = _set_top_level , . set_flags = _set_flags , . success = _success , . destroy = _destroy , }
 , . objects = objects , . blobs [ 0 ] = blob , . line = - 1 , . success = TRUE , ) ;
 return & this -> public ;
 }