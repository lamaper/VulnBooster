static void vvalue_strbuf_append_vector ( wmem_strbuf_t * strbuf , struct vt_vector val , struct vtype_data * type ) {
 const int elsize = ( type -> size == - 1 ) ? ( int ) sizeof ( struct data_blob ) : type -> size ;
 unsigned i ;
 guint8 * data = val . u . vt_ui1 ;
 wmem_strbuf_append_c ( strbuf , '[' ) ;
 for ( i = 0 ;
 i < val . len ;
 i ++ ) {
 if ( i > 0 ) {
 wmem_strbuf_append_c ( strbuf , ',' ) ;
 }
 type -> strbuf_append ( strbuf , data ) ;
 data += elsize ;
 }
 wmem_strbuf_append_c ( strbuf , ']' ) ;
 }