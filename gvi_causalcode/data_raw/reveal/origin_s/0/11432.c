static unsigned int get_prediction_error ( BLOCK_SIZE bsize , const struct buf_2d * src , const struct buf_2d * ref ) {
 unsigned int sse ;
 const vp9_variance_fn_t fn = get_block_variance_fn ( bsize ) ;
 fn ( src -> buf , src -> stride , ref -> buf , ref -> stride , & sse ) ;
 return sse ;
 }