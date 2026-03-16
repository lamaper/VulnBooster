static void parseqatom ( struct vars * v , int stopper , int type , struct state * lp , struct state * rp , struct subre * top ) {
 struct state * s ;
 struct state * s2 ;

 struct subre * atom ;
 struct subre * t ;
 int cap ;
 int latype ;
 int subno ;
 int atomtype ;
 int qprefer ;
 int f ;
 struct subre * * atomp ;
 atom = NULL ;
 assert ( lp -> nouts == 0 ) ;
 assert ( rp -> nins == 0 ) ;
 subno = 0 ;
 atomtype = v -> nexttype ;
 switch ( atomtype ) {
 case '^' : ARCV ( '^' , 1 ) ;
 if ( v -> cflags & REG_NLANCH ) ARCV ( BEHIND , v -> nlcolor ) ;
 NEXT ( ) ;
 return ;
 break ;
 case '$' : ARCV ( '$' , 1 ) ;
 if ( v -> cflags & REG_NLANCH ) ARCV ( AHEAD , v -> nlcolor ) ;
 NEXT ( ) ;
 return ;
 break ;
 case SBEGIN : ARCV ( '^' , 1 ) ;
 ARCV ( '^' , 0 ) ;
 NEXT ( ) ;
 return ;
 break ;
 case SEND : ARCV ( '$' , 1 ) ;
 ARCV ( '$' , 0 ) ;
 NEXT ( ) ;
 return ;
 break ;
 case '<' : wordchrs ( v ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 nonword ( v , BEHIND , lp , s ) ;
 word ( v , AHEAD , s , rp ) ;
 return ;
 break ;
 case '>' : wordchrs ( v ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 word ( v , BEHIND , lp , s ) ;
 nonword ( v , AHEAD , s , rp ) ;
 return ;
 break ;
 case WBDRY : wordchrs ( v ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 nonword ( v , BEHIND , lp , s ) ;
 word ( v , AHEAD , s , rp ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 word ( v , BEHIND , lp , s ) ;
 nonword ( v , AHEAD , s , rp ) ;
 return ;
 break ;
 case NWBDRY : wordchrs ( v ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 word ( v , BEHIND , lp , s ) ;
 word ( v , AHEAD , s , rp ) ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 nonword ( v , BEHIND , lp , s ) ;
 nonword ( v , AHEAD , s , rp ) ;
 return ;
 break ;
 case LACON : latype = v -> nextvalue ;
 NEXT ( ) ;
 s = newstate ( v -> nfa ) ;
 s2 = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 t = parse ( v , ')' , LACON , s , s2 ) ;
 freesubre ( v , t ) ;
 NOERR ( ) ;
 assert ( SEE ( ')' ) ) ;
 NEXT ( ) ;
 processlacon ( v , s , s2 , latype , lp , rp ) ;
 return ;
 break ;
 case '*' : case '+' : case '?' : case '{
' : ERR ( REG_BADRPT ) ;
 return ;
 break ;
 default : ERR ( REG_ASSERT ) ;
 return ;
 break ;
 case ')' : if ( ( v -> cflags & REG_ADVANCED ) != REG_EXTENDED ) {
 ERR ( REG_EPAREN ) ;
 return ;
 }
 NOTE ( REG_UPBOTCH ) ;
 case PLAIN : onechr ( v , v -> nextvalue , lp , rp ) ;
 okcolors ( v -> nfa , v -> cm ) ;
 NOERR ( ) ;
 NEXT ( ) ;
 break ;
 case '[' : if ( v -> nextvalue == 1 ) bracket ( v , lp , rp ) ;
 else cbracket ( v , lp , rp ) ;
 assert ( SEE ( ']' ) || ISERR ( ) ) ;
 NEXT ( ) ;
 break ;
 case '.' : rainbow ( v -> nfa , v -> cm , PLAIN , ( v -> cflags & REG_NLSTOP ) ? v -> nlcolor : COLORLESS , lp , rp ) ;
 NEXT ( ) ;
 break ;
 case '(' : cap = ( type == LACON ) ? 0 : v -> nextvalue ;
 if ( cap ) {
 v -> nsubexp ++ ;
 subno = v -> nsubexp ;
 if ( ( size_t ) subno >= v -> nsubs ) moresubs ( v , subno ) ;
 assert ( ( size_t ) subno < v -> nsubs ) ;
 }
 else atomtype = PLAIN ;
 NEXT ( ) ;
 s = newstate ( v -> nfa ) ;
 s2 = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 EMPTYARC ( lp , s ) ;
 EMPTYARC ( s2 , rp ) ;
 NOERR ( ) ;
 atom = parse ( v , ')' , type , s , s2 ) ;
 assert ( SEE ( ')' ) || ISERR ( ) ) ;
 NEXT ( ) ;
 NOERR ( ) ;
 if ( cap ) {
 v -> subs [ subno ] = atom ;
 t = subre ( v , '(' , atom -> flags | CAP , lp , rp ) ;
 NOERR ( ) ;
 t -> subno = subno ;
 t -> left = atom ;
 atom = t ;
 }
 break ;
 case BACKREF : INSIST ( type != LACON , REG_ESUBREG ) ;
 INSIST ( v -> nextvalue < v -> nsubs , REG_ESUBREG ) ;
 INSIST ( v -> subs [ v -> nextvalue ] != NULL , REG_ESUBREG ) ;
 NOERR ( ) ;
 assert ( v -> nextvalue > 0 ) ;
 atom = subre ( v , 'b' , BACKR , lp , rp ) ;
 NOERR ( ) ;
 subno = v -> nextvalue ;
 atom -> subno = subno ;
 EMPTYARC ( lp , rp ) ;
 NEXT ( ) ;
 break ;
 }
 switch ( v -> nexttype ) {
 case '*' : m = 0 ;
 n = DUPINF ;
 qprefer = ( v -> nextvalue ) ? LONGER : SHORTER ;
 NEXT ( ) ;
 break ;
 case '+' : m = 1 ;
 n = DUPINF ;
 qprefer = ( v -> nextvalue ) ? LONGER : SHORTER ;
 NEXT ( ) ;
 break ;
 case '?' : m = 0 ;
 n = 1 ;
 qprefer = ( v -> nextvalue ) ? LONGER : SHORTER ;
 NEXT ( ) ;
 break ;
 case '{
' : NEXT ( ) ;
 m = scannum ( v ) ;
 if ( EAT ( ',' ) ) {
 if ( SEE ( DIGIT ) ) n = scannum ( v ) ;
 else n = DUPINF ;
 if ( m > n ) {
 ERR ( REG_BADBR ) ;
 return ;
 }
 qprefer = ( v -> nextvalue ) ? LONGER : SHORTER ;
 }
 else {
 n = m ;
 qprefer = 0 ;
 }
 if ( ! SEE ( '}
' ) ) {
 ERR ( REG_BADBR ) ;
 return ;
 }
 NEXT ( ) ;
 break ;
 default : m = n = 1 ;
 qprefer = 0 ;
 break ;
 }
 if ( m == 0 && n == 0 ) {
 if ( atom != NULL ) freesubre ( v , atom ) ;
 if ( atomtype == '(' ) v -> subs [ subno ] = NULL ;
 delsub ( v -> nfa , lp , rp ) ;
 EMPTYARC ( lp , rp ) ;
 return ;
 }
 assert ( ! MESSY ( top -> flags ) ) ;
 f = top -> flags | qprefer | ( ( atom != NULL ) ? atom -> flags : 0 ) ;
 if ( atomtype != '(' && atomtype != BACKREF && ! MESSY ( UP ( f ) ) ) {
 if ( ! ( m == 1 && n == 1 ) ) repeat ( v , lp , rp , m , n ) ;
 if ( atom != NULL ) freesubre ( v , atom ) ;
 top -> flags = f ;
 return ;
 }
 if ( atom == NULL ) {
 atom = subre ( v , '=' , 0 , lp , rp ) ;
 NOERR ( ) ;
 }
 s = newstate ( v -> nfa ) ;
 s2 = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , lp , s ) ;
 moveins ( v -> nfa , rp , s2 ) ;
 NOERR ( ) ;
 atom -> begin = s ;
 atom -> end = s2 ;
 s = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 EMPTYARC ( lp , s ) ;
 NOERR ( ) ;
 t = subre ( v , '.' , COMBINE ( qprefer , atom -> flags ) , lp , rp ) ;
 NOERR ( ) ;
 t -> left = atom ;
 atomp = & t -> left ;
 assert ( top -> op == '=' && top -> left == NULL && top -> right == NULL ) ;
 top -> left = subre ( v , '=' , top -> flags , top -> begin , lp ) ;
 NOERR ( ) ;
 top -> op = '.' ;
 top -> right = t ;
 if ( atomtype == BACKREF ) {
 assert ( atom -> begin -> nouts == 1 ) ;
 delsub ( v -> nfa , atom -> begin , atom -> end ) ;
 assert ( v -> subs [ subno ] != NULL ) ;
 dupnfa ( v -> nfa , v -> subs [ subno ] -> begin , v -> subs [ subno ] -> end , atom -> begin , atom -> end ) ;
 NOERR ( ) ;
 }
 if ( atomtype == BACKREF ) {
 EMPTYARC ( s , atom -> begin ) ;
 repeat ( v , atom -> begin , atom -> end , m , n ) ;
 atom -> min = ( short ) m ;
 atom -> max = ( short ) n ;
 atom -> flags |= COMBINE ( qprefer , atom -> flags ) ;
 s2 = atom -> end ;
 }
 else if ( m == 1 && n == 1 ) {
 EMPTYARC ( s , atom -> begin ) ;
 s2 = atom -> end ;
 }
 else if ( m > 0 && ! ( atom -> flags & BACKR ) ) {
 dupnfa ( v -> nfa , atom -> begin , atom -> end , s , atom -> begin ) ;
 assert ( m >= 1 && m != DUPINF && n >= 1 ) ;
 repeat ( v , s , atom -> begin , m - 1 , ( n == DUPINF ) ? n : n - 1 ) ;
 f = COMBINE ( qprefer , atom -> flags ) ;
 t = subre ( v , '.' , f , s , atom -> end ) ;
 NOERR ( ) ;
 t -> left = subre ( v , '=' , PREF ( f ) , s , atom -> begin ) ;
 NOERR ( ) ;
 t -> right = atom ;
 * atomp = t ;
 s2 = atom -> end ;
 }
 else {
 s2 = newstate ( v -> nfa ) ;
 NOERR ( ) ;
 moveouts ( v -> nfa , atom -> end , s2 ) ;
 NOERR ( ) ;
 dupnfa ( v -> nfa , atom -> begin , atom -> end , s , s2 ) ;
 repeat ( v , s , s2 , m , n ) ;
 f = COMBINE ( qprefer , atom -> flags ) ;
 t = subre ( v , '*' , f , s , s2 ) ;
 NOERR ( ) ;
 t -> min = ( short ) m ;
 t -> max = ( short ) n ;
 t -> left = atom ;
 * atomp = t ;
 }
 t = top -> right ;
 if ( ! ( SEE ( '|' ) || SEE ( stopper ) || SEE ( EOS ) ) ) t -> right = parsebranch ( v , stopper , type , s2 , rp , 1 ) ;
 else {
 EMPTYARC ( s2 , rp ) ;
 t -> right = subre ( v , '=' , 0 , s2 , rp ) ;
 }
 NOERR ( ) ;
 assert ( SEE ( '|' ) || SEE ( stopper ) || SEE ( EOS ) ) ;
 t -> flags |= COMBINE ( t -> flags , t -> right -> flags ) ;
 top -> flags |= COMBINE ( top -> flags , t -> flags ) ;
 }