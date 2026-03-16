static inline void set_indic_properties ( hb_glyph_info_t & info ) {
 hb_codepoint_t u = info . codepoint ;
 unsigned int type = hb_indic_get_categories ( u ) ;
 indic_category_t cat = ( indic_category_t ) ( type & 0x7Fu ) ;
 indic_position_t pos = ( indic_position_t ) ( type >> 8 ) ;
 if ( unlikely ( hb_in_ranges ( u , 0x0951u , 0x0952u , 0x1CD0u , 0x1CD2u , 0x1CD4u , 0x1CE1u ) || u == 0x1CF4u ) ) cat = OT_A ;
 else if ( unlikely ( hb_in_range ( u , 0x0953u , 0x0954u ) ) ) cat = OT_SM ;
 else if ( unlikely ( hb_in_ranges ( u , 0x0A72u , 0x0A73u , 0x1CF5u , 0x1CF6u ) ) ) cat = OT_C ;
 else if ( unlikely ( hb_in_range ( u , 0x1CE2u , 0x1CE8u ) ) ) cat = OT_A ;
 else if ( unlikely ( u == 0x1CEDu ) ) cat = OT_A ;
 else if ( unlikely ( hb_in_ranges ( u , 0xA8F2u , 0xA8F7u , 0x1CE9u , 0x1CECu , 0x1CEEu , 0x1CF1u ) ) ) {
 cat = OT_Symbol ;
 ASSERT_STATIC ( ( int ) INDIC_SYLLABIC_CATEGORY_AVAGRAHA == OT_Symbol ) ;
 }
 else if ( unlikely ( hb_in_range ( u , 0x17CDu , 0x17D1u ) || u == 0x17CBu || u == 0x17D3u || u == 0x17DDu ) ) {
 cat = OT_M ;
 pos = POS_ABOVE_C ;
 }
 else if ( unlikely ( u == 0x17C6u ) ) cat = OT_N ;
 else if ( unlikely ( u == 0x17D2u ) ) cat = OT_Coeng ;
 else if ( unlikely ( hb_in_range ( u , 0x2010u , 0x2011u ) ) ) cat = OT_PLACEHOLDER ;
 else if ( unlikely ( u == 0x25CCu ) ) cat = OT_DOTTEDCIRCLE ;
 else if ( unlikely ( u == 0xA982u ) ) cat = OT_SM ;
 else if ( unlikely ( u == 0xA9BEu ) ) cat = OT_CM2 ;
 else if ( unlikely ( u == 0xA9BDu ) ) {
 cat = OT_M ;
 pos = POS_POST_C ;
 }
 if ( ( FLAG ( cat ) & CONSONANT_FLAGS ) ) {
 pos = POS_BASE_C ;
 if ( is_ra ( u ) ) cat = OT_Ra ;
 }
 else if ( cat == OT_M ) {
 pos = matra_position ( u , pos ) ;
 }
 else if ( ( FLAG ( cat ) & ( FLAG ( OT_SM ) | FLAG ( OT_VD ) | FLAG ( OT_A ) | FLAG ( OT_Symbol ) ) ) ) {
 pos = POS_SMVD ;
 }
 if ( unlikely ( u == 0x0B01u ) ) pos = POS_BEFORE_SUB ;
 info . indic_category ( ) = cat ;
 info . indic_position ( ) = pos ;
 }