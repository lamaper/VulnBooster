void BrotliHuffmanTreeGroupRelease ( BrotliState * s , HuffmanTreeGroup * group ) {
 BROTLI_FREE ( s , group -> codes ) ;
 group -> htrees = NULL ;
 }