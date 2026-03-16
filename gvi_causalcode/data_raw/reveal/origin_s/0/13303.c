static bool is_zero_width_char ( hb_font_t * font , hb_codepoint_t unicode ) {
 hb_codepoint_t glyph ;
 return hb_font_get_glyph ( font , unicode , 0 , & glyph ) && hb_font_get_glyph_h_advance ( font , glyph ) == 0 ;
 }