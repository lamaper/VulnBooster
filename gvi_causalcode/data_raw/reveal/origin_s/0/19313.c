static void repeat ( struct vars * v , struct state * lp , struct state * rp , int m , int n ) {

 const int rn = REDUCE ( n ) ;
 struct state * s ;
 struct state * s2 ;
 switch ( PAIR ( rm , rn ) ) {
 case PAIR ( 0 , 0 ) : delsub ( v -> nfa , lp , rp ) ;
 EMPTYARC ( lp , rp ) ;
 break ;
 case PAIR ( 0 , 1 ) : EMPTYARC ( lp , rp ) ;
 break ;
 case PAIR ( 0 , SOME ) : repeat ( v , lp , rp , 1 , n ) ;
 NOERR ( ) ;
 EMPTYARC ( lp , rp ) ;
 break ;
 case PAIR ( 0 , INF ) : s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 moveins ( v -> nfa , rp , s ) ;
 EMPTYARC ( lp , s ) ;
 EMPTYARC ( s , rp ) ;
 break ;
 case PAIR ( 1 , 1 ) : break ;
 case PAIR ( 1 , SOME ) : s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 dupnfa ( v -> nfa , s , rp , lp , s ) ;
 NOERR ( ) ;
 repeat ( v , lp , s , 1 , n - 1 ) ;
 NOERR ( ) ;
 EMPTYARC ( lp , s ) ;
 break ;
 case PAIR ( 1 , INF ) : s = newstate ( v -> nfa ) ;
 s2 = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 moveins ( v -> nfa , rp , s2 ) ;
 EMPTYARC ( lp , s ) ;
 EMPTYARC ( s2 , rp ) ;
 EMPTYARC ( s2 , s ) ;
 break ;
 case PAIR ( SOME , SOME ) : s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 dupnfa ( v -> nfa , s , rp , lp , s ) ;
 NOERR ( ) ;
 repeat ( v , lp , s , m - 1 , n - 1 ) ;
 break ;
 case PAIR ( SOME , INF ) : s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 dupnfa ( v -> nfa , s , rp , lp , s ) ;
 NOERR ( ) ;
 repeat ( v , lp , s , m - 1 , n ) ;
 break ;
 default : ERR ( REG_ASSERT ) ;
 break ;
 }
 }