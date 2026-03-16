static inline indic_position_t matra_position ( hb_codepoint_t u , indic_position_t side ) {
 switch ( ( int ) side ) {
 case POS_PRE_C : return MATRA_POS_LEFT ( u ) ;
 case POS_POST_C : return MATRA_POS_RIGHT ( u ) ;
 case POS_ABOVE_C : return MATRA_POS_TOP ( u ) ;
 case POS_BELOW_C : return MATRA_POS_BOTTOM ( u ) ;
 }
 ;
 return side ;
 }