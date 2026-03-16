static void processlacon ( struct vars * v , struct state * begin , struct state * end , int latype , struct state * lp , struct state * rp ) {
 struct state * s1 ;
 int n ;
 s1 = single_color_transition ( begin , end ) ;
 switch ( latype ) {
 case LATYPE_AHEAD_POS : if ( s1 != NULL ) {
 cloneouts ( v -> nfa , s1 , lp , rp , AHEAD ) ;
 return ;
 }
 break ;
 case LATYPE_AHEAD_NEG : if ( s1 != NULL ) {
 colorcomplement ( v -> nfa , v -> cm , AHEAD , s1 , lp , rp ) ;
 newarc ( v -> nfa , '$' , 1 , lp , rp ) ;
 newarc ( v -> nfa , '$' , 0 , lp , rp ) ;
 return ;
 }
 break ;
 case LATYPE_BEHIND_POS : if ( s1 != NULL ) {
 cloneouts ( v -> nfa , s1 , lp , rp , BEHIND ) ;
 return ;
 }
 break ;
 case LATYPE_BEHIND_NEG : if ( s1 != NULL ) {
 colorcomplement ( v -> nfa , v -> cm , BEHIND , s1 , lp , rp ) ;
 newarc ( v -> nfa , '^' , 1 , lp , rp ) ;
 newarc ( v -> nfa , '^' , 0 , lp , rp ) ;
 return ;
 }
 break ;
 default : assert ( NOTREACHED ) ;
 }
 n = newlacon ( v , begin , end , latype ) ;
 newarc ( v -> nfa , LACON , n , lp , rp ) ;
 }