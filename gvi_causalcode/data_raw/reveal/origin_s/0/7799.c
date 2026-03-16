void BrotliStateCleanup ( BrotliState * s ) {
 BrotliStateCleanupAfterMetablock ( s ) ;
 BROTLI_FREE ( s , s -> ringbuffer ) ;
 BROTLI_FREE ( s , s -> block_type_trees ) ;
 }