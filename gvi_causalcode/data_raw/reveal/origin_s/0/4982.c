void BrotliHuffmanTreeGroupInit ( BrotliState * s , HuffmanTreeGroup * group , uint32_t alphabet_size , uint32_t ntrees ) {
 const size_t max_table_size = kMaxHuffmanTableSize [ ( alphabet_size + 31 ) >> 5 ] ;
 const size_t code_size = sizeof ( HuffmanCode ) * ntrees * max_table_size ;
 const size_t htree_size = sizeof ( HuffmanCode * ) * ntrees ;
 char * p = ( char * ) BROTLI_ALLOC ( s , code_size + htree_size ) ;
 group -> alphabet_size = ( uint16_t ) alphabet_size ;
 group -> num_htrees = ( uint16_t ) ntrees ;
 group -> codes = ( HuffmanCode * ) p ;
 group -> htrees = ( HuffmanCode * * ) ( p + code_size ) ;
 }