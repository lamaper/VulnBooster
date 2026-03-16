int vp9_hex_search ( const MACROBLOCK * x , MV * ref_mv , int search_param , int sad_per_bit , int do_init_search , int * sad_list , const vp9_variance_fn_ptr_t * vfp , int use_mvcost , const MV * center_mv , MV * best_mv ) {
 static const int hex_num_candidates [ MAX_PATTERN_SCALES ] = {
 8 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 }
 ;
 static const MV hex_candidates [ MAX_PATTERN_SCALES ] [ MAX_PATTERN_CANDIDATES ] = {
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
 - 1 , - 2 }
 , {
 1 , - 2 }
 , {
 2 , 0 }
 , {
 1 , 2 }
 , {
 - 1 , 2 }
 , {
 - 2 , 0 }
 }
 , {
 {
 - 2 , - 4 }
 , {
 2 , - 4 }
 , {
 4 , 0 }
 , {
 2 , 4 }
 , {
 - 2 , 4 }
 , {
 - 4 , 0 }
 }
 , {
 {
 - 4 , - 8 }
 , {
 4 , - 8 }
 , {
 8 , 0 }
 , {
 4 , 8 }
 , {
 - 4 , 8 }
 , {
 - 8 , 0 }
 }
 , {
 {
 - 8 , - 16 }
 , {
 8 , - 16 }
 , {
 16 , 0 }
 , {
 8 , 16 }
 , {
 - 8 , 16 }
 , {
 - 16 , 0 }
 }
 , {
 {
 - 16 , - 32 }
 , {
 16 , - 32 }
 , {
 32 , 0 }
 , {
 16 , 32 }
 , {
 - 16 , 32 }
 , {
 - 32 , 0 }
 }
 , {
 {
 - 32 , - 64 }
 , {
 32 , - 64 }
 , {
 64 , 0 }
 , {
 32 , 64 }
 , {
 - 32 , 64 }
 , {
 - 64 , 0 }
 }
 , {
 {
 - 64 , - 128 }
 , {
 64 , - 128 }
 , {
 128 , 0 }
 , {
 64 , 128 }
 , {
 - 64 , 128 }
 , {
 - 128 , 0 }
 }
 , {
 {
 - 128 , - 256 }
 , {
 128 , - 256 }
 , {
 256 , 0 }
 , {
 128 , 256 }
 , {
 - 128 , 256 }
 , {
 - 256 , 0 }
 }
 , {
 {
 - 256 , - 512 }
 , {
 256 , - 512 }
 , {
 512 , 0 }
 , {
 256 , 512 }
 , {
 - 256 , 512 }
 , {
 - 512 , 0 }
 }
 , {
 {
 - 512 , - 1024 }
 , {
 512 , - 1024 }
 , {
 1024 , 0 }
 , {
 512 , 1024 }
 , {
 - 512 , 1024 }
 , {
 - 1024 , 0 }
 }
 , }
 ;
 return vp9_pattern_search ( x , ref_mv , search_param , sad_per_bit , do_init_search , sad_list , vfp , use_mvcost , center_mv , best_mv , hex_num_candidates , hex_candidates ) ;
 }