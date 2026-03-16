static inline bool alloc_array_check_size ( ulong num_elements , ulong elt_size , ulong * lsize ) {
 int64_t s = ( int64_t ) num_elements * elt_size ;
 if ( s > max_uint ) {
 return false ;
 }
 * lsize = ( ulong ) s ;
 return true ;
 }