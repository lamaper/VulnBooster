static guint composite_offset ( const tvbuff_t * tvb , const guint counter ) {
 const struct tvb_composite * composite_tvb = ( const struct tvb_composite * ) tvb ;
 const tvbuff_t * member = ( const tvbuff_t * ) composite_tvb -> composite . tvbs -> data ;
 return tvb_offset_from_real_beginning_counter ( member , counter ) ;
 }