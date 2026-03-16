void BrotliStateCleanupAfterMetablock ( BrotliState * s ) {
 BROTLI_FREE ( s , s -> context_modes ) ;
 BROTLI_FREE ( s , s -> context_map ) ;
 BROTLI_FREE ( s , s -> dist_context_map ) ;
 BrotliHuffmanTreeGroupRelease ( s , & s -> literal_hgroup ) ;
 BrotliHuffmanTreeGroupRelease ( s , & s -> insert_copy_hgroup ) ;
 BrotliHuffmanTreeGroupRelease ( s , & s -> distance_hgroup ) ;
 }