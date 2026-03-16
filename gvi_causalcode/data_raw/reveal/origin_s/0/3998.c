static Selectivity regex_selectivity_sub ( const char * patt , int pattlen , bool case_insensitive ) {
 Selectivity sel = 1.0 ;
 int paren_depth = 0 ;
 int paren_pos = 0 ;
 int pos ;
 for ( pos = 0 ;
 pos < pattlen ;
 pos ++ ) {
 if ( patt [ pos ] == '(' ) {
 if ( paren_depth == 0 ) paren_pos = pos ;
 paren_depth ++ ;
 }
 else if ( patt [ pos ] == ')' && paren_depth > 0 ) {
 paren_depth -- ;
 if ( paren_depth == 0 ) sel *= regex_selectivity_sub ( patt + ( paren_pos + 1 ) , pos - ( paren_pos + 1 ) , case_insensitive ) ;
 }
 else if ( patt [ pos ] == '|' && paren_depth == 0 ) {
 sel += regex_selectivity_sub ( patt + ( pos + 1 ) , pattlen - ( pos + 1 ) , case_insensitive ) ;
 break ;
 }
 else if ( patt [ pos ] == '[' ) {
 bool negclass = false ;
 if ( patt [ ++ pos ] == '^' ) {
 negclass = true ;
 pos ++ ;
 }
 if ( patt [ pos ] == ']' ) pos ++ ;
 while ( pos < pattlen && patt [ pos ] != ']' ) pos ++ ;
 if ( paren_depth == 0 ) sel *= ( negclass ? ( 1.0 - CHAR_RANGE_SEL ) : CHAR_RANGE_SEL ) ;
 }
 else if ( patt [ pos ] == '.' ) {
 if ( paren_depth == 0 ) sel *= ANY_CHAR_SEL ;
 }
 else if ( patt [ pos ] == '*' || patt [ pos ] == '?' || patt [ pos ] == '+' ) {
 if ( paren_depth == 0 ) sel *= PARTIAL_WILDCARD_SEL ;
 }
 else if ( patt [ pos ] == '{
' ) {
 while ( pos < pattlen && patt [ pos ] != '}
' ) pos ++ ;
 if ( paren_depth == 0 ) sel *= PARTIAL_WILDCARD_SEL ;
 }
 else if ( patt [ pos ] == '\\' ) {
 pos ++ ;
 if ( pos >= pattlen ) break ;
 if ( paren_depth == 0 ) sel *= FIXED_CHAR_SEL ;
 }
 else {
 if ( paren_depth == 0 ) sel *= FIXED_CHAR_SEL ;
 }
 }
 if ( sel > 1.0 ) sel = 1.0 ;
 return sel ;
 }