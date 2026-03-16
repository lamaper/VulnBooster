static void brackpart ( struct vars * v , struct state * lp , struct state * rp ) {
 celt startc ;
 celt endc ;
 struct cvec * cv ;
 const chr * startp ;
 const chr * endp ;
 chr c [ 1 ] ;
 switch ( v -> nexttype ) {
 case RANGE : ERR ( REG_ERANGE ) ;
 return ;
 break ;
 case PLAIN : c [ 0 ] = v -> nextvalue ;
 NEXT ( ) ;
 if ( ! SEE ( RANGE ) ) {
 onechr ( v , c [ 0 ] , lp , rp ) ;
 return ;
 }
 startc = element ( v , c , c + 1 ) ;
 NOERR ( ) ;
 break ;
 case COLLEL : startp = v -> now ;
 endp = scanplain ( v ) ;
 INSIST ( startp < endp , REG_ECOLLATE ) ;
 NOERR ( ) ;
 startc = element ( v , startp , endp ) ;
 NOERR ( ) ;
 break ;
 case ECLASS : startp = v -> now ;
 endp = scanplain ( v ) ;
 INSIST ( startp < endp , REG_ECOLLATE ) ;
 NOERR ( ) ;
 startc = element ( v , startp , endp ) ;
 NOERR ( ) ;
 cv = eclass ( v , startc , ( v -> cflags & REG_ICASE ) ) ;
 NOERR ( ) ;
 dovec ( v , cv , lp , rp ) ;
 return ;
 break ;
 case CCLASS : startp = v -> now ;
 endp = scanplain ( v ) ;
 INSIST ( startp < endp , REG_ECTYPE ) ;
 NOERR ( ) ;
 cv = cclass ( v , startp , endp , ( v -> cflags & REG_ICASE ) ) ;
 NOERR ( ) ;
 dovec ( v , cv , lp , rp ) ;
 return ;
 break ;
 default : ERR ( REG_ASSERT ) ;
 return ;
 break ;
 }
 if ( SEE ( RANGE ) ) {
 NEXT ( ) ;
 switch ( v -> nexttype ) {
 case PLAIN : case RANGE : c [ 0 ] = v -> nextvalue ;
 NEXT ( ) ;
 endc = element ( v , c , c + 1 ) ;
 NOERR ( ) ;
 break ;
 case COLLEL : startp = v -> now ;
 endp = scanplain ( v ) ;
 INSIST ( startp < endp , REG_ECOLLATE ) ;
 NOERR ( ) ;
 endc = element ( v , startp , endp ) ;
 NOERR ( ) ;
 break ;
 default : ERR ( REG_ERANGE ) ;
 return ;
 break ;
 }
 }
 else endc = startc ;
 if ( startc != endc ) NOTE ( REG_UUNPORT ) ;
 cv = range ( v , startc , endc , ( v -> cflags & REG_ICASE ) ) ;
 NOERR ( ) ;
 dovec ( v , cv , lp , rp ) ;
 }