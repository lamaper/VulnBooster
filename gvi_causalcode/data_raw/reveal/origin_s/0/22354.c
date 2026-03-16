static inline void decompose_cluster ( const hb_ot_shape_normalize_context_t * c , unsigned int end , bool might_short_circuit , bool always_short_circuit ) {
 if ( likely ( c -> buffer -> idx + 1 == end ) ) decompose_current_character ( c , might_short_circuit ) ;
 else decompose_multi_char_cluster ( c , end , always_short_circuit ) ;
 }