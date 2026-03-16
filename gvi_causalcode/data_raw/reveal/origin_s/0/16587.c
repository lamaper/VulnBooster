static void resolveBaseDirection ( const UChar * text , uint32_t length , UBiDiLevel * pInLevel , UBiDiLevel * pOutLevel ) {
 switch ( * pInLevel ) {
 case UBIDI_DEFAULT_LTR : case UBIDI_DEFAULT_RTL : {
 UBiDiLevel level = ubidi_getBaseDirection ( text , length ) ;
 * pInLevel = level != UBIDI_NEUTRAL ? level : * pInLevel == UBIDI_DEFAULT_RTL ? RTL : LTR ;
 break ;
 }
 default : * pInLevel &= 1 ;
 break ;
 }
 switch ( * pOutLevel ) {
 case UBIDI_DEFAULT_LTR : case UBIDI_DEFAULT_RTL : * pOutLevel = * pInLevel ;
 break ;
 default : * pOutLevel &= 1 ;
 break ;
 }
 }