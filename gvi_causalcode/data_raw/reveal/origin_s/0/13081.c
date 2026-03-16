static int mono_decode ( COOKContext * q , COOKSubpacket * p , float * mlt_buffer ) {
 int category_index [ 128 ] = {
 0 }
 ;
 int category [ 128 ] = {
 0 }
 ;
 int quant_index_table [ 102 ] ;
 int res ;
 if ( ( res = decode_envelope ( q , p , quant_index_table ) ) < 0 ) return res ;
 q -> num_vectors = get_bits ( & q -> gb , p -> log2_numvector_size ) ;
 categorize ( q , p , quant_index_table , category , category_index ) ;
 expand_category ( q , category , category_index ) ;
 decode_vectors ( q , p , category , quant_index_table , mlt_buffer ) ;
 return 0 ;
 }