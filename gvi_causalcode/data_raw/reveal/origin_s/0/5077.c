static inline bool is_one_of ( const hb_glyph_info_t & info , unsigned int flags ) {
 if ( _hb_glyph_info_ligated ( & info ) ) return false ;
 return ! ! ( FLAG_SAFE ( info . indic_category ( ) ) & flags ) ;
 }