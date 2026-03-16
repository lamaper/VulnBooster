tvbuff_t * tvb_new_composite ( void ) {
 tvbuff_t * tvb = tvb_new ( & tvb_composite_ops ) ;
 struct tvb_composite * composite_tvb = ( struct tvb_composite * ) tvb ;
 tvb_comp_t * composite = & composite_tvb -> composite ;
 composite -> tvbs = NULL ;
 composite -> start_offsets = NULL ;
 composite -> end_offsets = NULL ;
 return tvb ;
 }