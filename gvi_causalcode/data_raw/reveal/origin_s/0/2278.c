int vp9_square_search ( const MACROBLOCK * x , MV * ref_mv , int search_param , int sad_per_bit , int do_init_search , int * sad_list , const vp9_variance_fn_ptr_t * vfp , int use_mvcost , const MV * center_mv , MV * best_mv ) {
 static const int square_num_candidates [ MAX_PATTERN_SCALES ] = {
 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , 8 , }
 ;
 static const MV square_candidates [ MAX_PATTERN_SCALES ] [ MAX_PATTERN_CANDIDATES ] = {
 {
 {
 - 1 , - 1 }
 , {
 0 , - 1 }
 , {
 1 , - 1 }
 , {
 1 , 0 }
 , {
 1 , 1 }
 , {
 0 , 1 }
 , {
 - 1 , 1 }
 , {
 - 1 , 0 }
 }
 , {
 {
 - 2 , - 2 }
 , {
 0 , - 2 }
 , {
 2 , - 2 }
 , {
 2 , 0 }
 , {
 2 , 2 }
 , {
 0 , 2 }
 , {
 - 2 , 2 }
 , {
 - 2 , 0 }
 }
 , {
 {
 - 4 , - 4 }
 , {
 0 , - 4 }
 , {
 4 , - 4 }
 , {
 4 , 0 }
 , {
 4 , 4 }
 , {
 0 , 4 }
 , {
 - 4 , 4 }
 , {
 - 4 , 0 }
 }
 , {
 {
 - 8 , - 8 }
 , {
 0 , - 8 }
 , {
 8 , - 8 }
 , {
 8 , 0 }
 , {
 8 , 8 }
 , {
 0 , 8 }
 , {
 - 8 , 8 }
 , {
 - 8 , 0 }
 }
 , {
 {
 - 16 , - 16 }
 , {
 0 , - 16 }
 , {
 16 , - 16 }
 , {
 16 , 0 }
 , {
 16 , 16 }
 , {
 0 , 16 }
 , {
 - 16 , 16 }
 , {
 - 16 , 0 }
 }
 , {
 {
 - 32 , - 32 }
 , {
 0 , - 32 }
 , {
 32 , - 32 }
 , {
 32 , 0 }
 , {
 32 , 32 }
 , {
 0 , 32 }
 , {
 - 32 , 32 }
 , {
 - 32 , 0 }
 }
 , {
 {
 - 64 , - 64 }
 , {
 0 , - 64 }
 , {
 64 , - 64 }
 , {
 64 , 0 }
 , {
 64 , 64 }
 , {
 0 , 64 }
 , {
 - 64 , 64 }
 , {
 - 64 , 0 }
 }
 , {
 {
 - 128 , - 128 }
 , {
 0 , - 128 }
 , {
 128 , - 128 }
 , {
 128 , 0 }
 , {
 128 , 128 }
 , {
 0 , 128 }
 , {
 - 128 , 128 }
 , {
 - 128 , 0 }
 }
 , {
 {
 - 256 , - 256 }
 , {
 0 , - 256 }
 , {
 256 , - 256 }
 , {
 256 , 0 }
 , {
 256 , 256 }
 , {
 0 , 256 }
 , {
 - 256 , 256 }
 , {
 - 256 , 0 }
 }
 , {
 {
 - 512 , - 512 }
 , {
 0 , - 512 }
 , {
 512 , - 512 }
 , {
 512 , 0 }
 , {
 512 , 512 }
 , {
 0 , 512 }
 , {
 - 512 , 512 }
 , {
 - 512 , 0 }
 }
 , {
 {
 - 1024 , - 1024 }
 , {
 0 , - 1024 }
 , {
 1024 , - 1024 }
 , {
 1024 , 0 }
 , {
 1024 , 1024 }
 , {
 0 , 1024 }
 , {
 - 1024 , 1024 }
 , {
 - 1024 , 0 }
 }
 , }
 ;
 return vp9_pattern_search ( x , ref_mv , search_param , sad_per_bit , do_init_search , sad_list , vfp , use_mvcost , center_mv , best_mv , square_num_candidates , square_candidates ) ;
 }