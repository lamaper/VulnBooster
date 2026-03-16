static void categorize ( COOKContext * q , COOKSubpacket * p , int * quant_index_table , int * category , int * category_index ) {
 int exp_idx , bias , tmpbias1 , tmpbias2 , bits_left , num_bits , index , v , i , j ;
 int exp_index2 [ 102 ] = {
 0 }
 ;
 int exp_index1 [ 102 ] = {
 0 }
 ;
 int tmp_categorize_array [ 128 * 2 ] = {
 0 }
 ;
 int tmp_categorize_array1_idx = p -> numvector_size ;
 int tmp_categorize_array2_idx = p -> numvector_size ;
 bits_left = p -> bits_per_subpacket - get_bits_count ( & q -> gb ) ;
 if ( bits_left > q -> samples_per_channel ) bits_left = q -> samples_per_channel + ( ( bits_left - q -> samples_per_channel ) * 5 ) / 8 ;
 bias = - 32 ;
 for ( i = 32 ;
 i > 0 ;
 i = i / 2 ) {
 num_bits = 0 ;
 index = 0 ;
 for ( j = p -> total_subbands ;
 j > 0 ;
 j -- ) {
 exp_idx = av_clip ( ( i - quant_index_table [ index ] + bias ) / 2 , 0 , 7 ) ;
 index ++ ;
 num_bits += expbits_tab [ exp_idx ] ;
 }
 if ( num_bits >= bits_left - 32 ) bias += i ;
 }
 num_bits = 0 ;
 for ( i = 0 ;
 i < p -> total_subbands ;
 i ++ ) {
 exp_idx = av_clip ( ( bias - quant_index_table [ i ] ) / 2 , 0 , 7 ) ;
 num_bits += expbits_tab [ exp_idx ] ;
 exp_index1 [ i ] = exp_idx ;
 exp_index2 [ i ] = exp_idx ;
 }
 tmpbias1 = tmpbias2 = num_bits ;
 for ( j = 1 ;
 j < p -> numvector_size ;
 j ++ ) {
 if ( tmpbias1 + tmpbias2 > 2 * bits_left ) {
 int max = - 999999 ;
 index = - 1 ;
 for ( i = 0 ;
 i < p -> total_subbands ;
 i ++ ) {
 if ( exp_index1 [ i ] < 7 ) {
 v = ( - 2 * exp_index1 [ i ] ) - quant_index_table [ i ] + bias ;
 if ( v >= max ) {
 max = v ;
 index = i ;
 }
 }
 }
 if ( index == - 1 ) break ;
 tmp_categorize_array [ tmp_categorize_array1_idx ++ ] = index ;
 tmpbias1 -= expbits_tab [ exp_index1 [ index ] ] - expbits_tab [ exp_index1 [ index ] + 1 ] ;
 ++ exp_index1 [ index ] ;
 }
 else {
 int min = 999999 ;
 index = - 1 ;
 for ( i = 0 ;
 i < p -> total_subbands ;
 i ++ ) {
 if ( exp_index2 [ i ] > 0 ) {
 v = ( - 2 * exp_index2 [ i ] ) - quant_index_table [ i ] + bias ;
 if ( v < min ) {
 min = v ;
 index = i ;
 }
 }
 }
 if ( index == - 1 ) break ;
 tmp_categorize_array [ -- tmp_categorize_array2_idx ] = index ;
 tmpbias2 -= expbits_tab [ exp_index2 [ index ] ] - expbits_tab [ exp_index2 [ index ] - 1 ] ;
 -- exp_index2 [ index ] ;
 }
 }
 for ( i = 0 ;
 i < p -> total_subbands ;
 i ++ ) category [ i ] = exp_index2 [ i ] ;
 for ( i = 0 ;
 i < p -> numvector_size - 1 ;
 i ++ ) category_index [ i ] = tmp_categorize_array [ tmp_categorize_array2_idx ++ ] ;
 }