int # ifdef GLOB_ATTRIBUTE GLOB_ATTRIBUTE # endif glob ( pattern , flags , errfunc , pglob ) const char * pattern ;
 int flags ;
 int ( * errfunc ) ( const char * , int ) ;
 glob_t * pglob ;
 {
 const char * filename ;
 char * dirname = NULL ;
 size_t dirlen ;
 int status ;
 size_t oldcount ;
 int meta ;
 int dirname_modified ;
 int malloc_dirname = 0 ;
 glob_t dirs ;
 int retval = 0 ;


 __set_errno ( EINVAL ) ;
 return - 1 ;
 }
 if ( ! ( flags & GLOB_DOOFFS ) ) pglob -> gl_offs = 0 ;
 if ( flags & GLOB_BRACE ) {
 const char * begin ;
 if ( flags & GLOB_NOESCAPE ) begin = strchr ( pattern , '{
' ) ;
 else {
 begin = pattern ;
 while ( 1 ) {
 if ( * begin == '\0' ) {
 begin = NULL ;
 break ;
 }
 if ( * begin == '\\' && begin [ 1 ] != '\0' ) ++ begin ;
 else if ( * begin == '{
' ) break ;
 ++ begin ;
 }
 }
 if ( begin != NULL ) {
 size_t firstc ;
 char * alt_start ;
 const char * p ;
 const char * next ;
 const char * rest ;
 size_t rest_len ;
 char * onealt ;
 size_t pattern_len = strlen ( pattern ) - 1 ;

 if ( alloca_onealt ) onealt = alloca_account ( pattern_len , alloca_used ) ;
 else # endif {
 onealt = ( char * ) malloc ( pattern_len ) ;
 if ( onealt == NULL ) {
 if ( ! ( flags & GLOB_APPEND ) ) {
 pglob -> gl_pathc = 0 ;
 pglob -> gl_pathv = NULL ;
 }
 return GLOB_NOSPACE ;
 }
 }
 alt_start = mempcpy ( onealt , pattern , begin - pattern ) ;
 next = next_brace_sub ( begin + 1 , flags ) ;
 if ( next == NULL ) {
 illegal_brace : # ifdef _LIBC if ( __builtin_expect ( ! alloca_onealt , 0 ) ) # endif free ( onealt ) ;
 return glob ( pattern , flags & ~ GLOB_BRACE , errfunc , pglob ) ;
 }
 rest = next ;
 while ( * rest != '}
' ) {
 rest = next_brace_sub ( rest + 1 , flags ) ;
 if ( rest == NULL ) goto illegal_brace ;
 }
 rest_len = strlen ( ++ rest ) + 1 ;
 if ( ! ( flags & GLOB_APPEND ) ) {
 pglob -> gl_pathc = 0 ;
 pglob -> gl_pathv = NULL ;
 }
 firstc = pglob -> gl_pathc ;
 p = begin + 1 ;
 while ( 1 ) {
 int result ;
 mempcpy ( mempcpy ( alt_start , p , next - p ) , rest , rest_len ) ;
 result = glob ( onealt , ( ( flags & ~ ( GLOB_NOCHECK | GLOB_NOMAGIC ) ) | GLOB_APPEND ) , errfunc , pglob ) ;
 if ( result && result != GLOB_NOMATCH ) {

 if ( ! ( flags & GLOB_APPEND ) ) {
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 }
 return result ;
 }
 if ( * next == '}
' ) break ;
 p = next + 1 ;
 next = next_brace_sub ( p , flags ) ;
 assert ( next != NULL ) ;
 }

 if ( pglob -> gl_pathc != firstc ) return 0 ;
 else if ( ! ( flags & ( GLOB_NOCHECK | GLOB_NOMAGIC ) ) ) return GLOB_NOMATCH ;
 }
 }
 if ( ! ( flags & GLOB_APPEND ) ) {
 pglob -> gl_pathc = 0 ;
 if ( ! ( flags & GLOB_DOOFFS ) ) pglob -> gl_pathv = NULL ;
 else {
 size_t i ;
 pglob -> gl_pathv = ( char * * ) malloc ( ( pglob -> gl_offs + 1 ) * sizeof ( char * ) ) ;
 if ( pglob -> gl_pathv == NULL ) return GLOB_NOSPACE ;
 for ( i = 0 ;
 i <= pglob -> gl_offs ;
 ++ i ) pglob -> gl_pathv [ i ] = NULL ;
 }
 }
 oldcount = pglob -> gl_pathc + pglob -> gl_offs ;
 filename = strrchr ( pattern , '/' ) ;


 if ( filename == NULL ) {
 if ( ( flags & ( GLOB_TILDE | GLOB_TILDE_CHECK ) ) && pattern [ 0 ] == '~' ) {
 dirname = ( char * ) pattern ;
 dirlen = strlen ( pattern ) ;
 filename = NULL ;
 }
 else {
 if ( __builtin_expect ( pattern [ 0 ] == '\0' , 0 ) ) {
 dirs . gl_pathv = NULL ;
 goto no_matches ;
 }
 filename = pattern ;



 }
 }
 else if ( filename == pattern || ( filename == pattern + 1 && pattern [ 0 ] == '\\' && ( flags & GLOB_NOESCAPE ) == 0 ) ) {
 dirname = ( char * ) "/" ;
 dirlen = 1 ;
 ++ filename ;
 }
 else {
 char * newp ;
 dirlen = filename - pattern ;

 char * drive_spec ;
 ++ dirlen ;
 drive_spec = ( char * ) __alloca ( dirlen + 1 ) ;
 * ( ( char * ) mempcpy ( drive_spec , pattern , dirlen ) ) = '\0' ;
 if ( __glob_pattern_p ( drive_spec , ! ( flags & GLOB_NOESCAPE ) ) ) return GLOB_NOMATCH ;
 }

 else # endif {
 newp = malloc ( dirlen + 1 ) ;
 if ( newp == NULL ) return GLOB_NOSPACE ;
 malloc_dirname = 1 ;
 }
 * ( ( char * ) mempcpy ( newp , pattern , dirlen ) ) = '\0' ;
 dirname = newp ;
 ++ filename ;
 if ( filename [ 0 ] == '\0' # if defined __MSDOS__ || defined WINDOWS32 && dirname [ dirlen - 1 ] != ':' && ( dirlen < 3 || dirname [ dirlen - 2 ] != ':' || dirname [ dirlen - 1 ] != '/' ) # endif && dirlen > 1 ) {
 int orig_flags = flags ;
 if ( ! ( flags & GLOB_NOESCAPE ) && dirname [ dirlen - 1 ] == '\\' ) {
 char * p = ( char * ) & dirname [ dirlen - 1 ] ;
 while ( p > dirname && p [ - 1 ] == '\\' ) -- p ;
 if ( ( & dirname [ dirlen ] - p ) & 1 ) {
 * ( char * ) & dirname [ -- dirlen ] = '\0' ;
 flags &= ~ ( GLOB_NOCHECK | GLOB_NOMAGIC ) ;
 }
 }
 int val = glob ( dirname , flags | GLOB_MARK , errfunc , pglob ) ;
 if ( val == 0 ) pglob -> gl_flags = ( ( pglob -> gl_flags & ~ GLOB_MARK ) | ( flags & GLOB_MARK ) ) ;
 else if ( val == GLOB_NOMATCH && flags != orig_flags ) {
 dirs . gl_pathv = NULL ;
 flags = orig_flags ;
 oldcount = pglob -> gl_pathc + pglob -> gl_offs ;
 goto no_matches ;
 }
 retval = val ;
 goto out ;
 }
 }

 if ( dirname [ 1 ] == '\0' || dirname [ 1 ] == '/' || ( ! ( flags & GLOB_NOESCAPE ) && dirname [ 1 ] == '\\' && ( dirname [ 2 ] == '\0' || dirname [ 2 ] == '/' ) ) ) {
 char * home_dir = getenv ( "HOME" ) ;
 int malloc_home_dir = 0 ;



 int success ;
 char * name ;
 size_t buflen = GET_LOGIN_NAME_MAX ( ) + 1 ;
 if ( buflen == 0 ) buflen = 20 ;
 name = alloca_account ( buflen , alloca_used ) ;
 success = getlogin_r ( name , buflen ) == 0 ;
 if ( success ) {
 struct passwd * p ;

 char * pwtmpbuf ;
 struct passwd pwbuf ;
 int malloc_pwtmpbuf = 0 ;
 int save = errno ;


 else {
 pwtmpbuf = malloc ( pwbuflen ) ;
 if ( pwtmpbuf == NULL ) {
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 malloc_pwtmpbuf = 1 ;
 }
 while ( getpwnam_r ( name , & pwbuf , pwtmpbuf , pwbuflen , & p ) != 0 ) {
 if ( errno != ERANGE ) {
 p = NULL ;
 break ;
 }
 if ( ! malloc_pwtmpbuf && __libc_use_alloca ( alloca_used + 2 * pwbuflen ) ) pwtmpbuf = extend_alloca_account ( pwtmpbuf , pwbuflen , 2 * pwbuflen , alloca_used ) ;
 else {
 char * newp = realloc ( malloc_pwtmpbuf ? pwtmpbuf : NULL , 2 * pwbuflen ) ;
 if ( newp == NULL ) {
 if ( __builtin_expect ( malloc_pwtmpbuf , 0 ) ) free ( pwtmpbuf ) ;
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 pwtmpbuf = newp ;
 pwbuflen = 2 * pwbuflen ;
 malloc_pwtmpbuf = 1 ;
 }
 __set_errno ( save ) ;
 }


 if ( ! malloc_pwtmpbuf ) home_dir = p -> pw_dir ;
 else {
 size_t home_dir_len = strlen ( p -> pw_dir ) + 1 ;
 if ( __libc_use_alloca ( alloca_used + home_dir_len ) ) home_dir = alloca_account ( home_dir_len , alloca_used ) ;
 else {
 home_dir = malloc ( home_dir_len ) ;
 if ( home_dir == NULL ) {
 free ( pwtmpbuf ) ;
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 malloc_home_dir = 1 ;
 }
 memcpy ( home_dir , p -> pw_dir , home_dir_len ) ;
 free ( pwtmpbuf ) ;
 }
 }
 }
 }
 if ( home_dir == NULL || home_dir [ 0 ] == '\0' ) {
 if ( flags & GLOB_TILDE_CHECK ) {
 if ( __builtin_expect ( malloc_home_dir , 0 ) ) free ( home_dir ) ;
 retval = GLOB_NOMATCH ;
 goto out ;
 }
 else home_dir = ( char * ) "~" ;
 }

 if ( __builtin_expect ( malloc_dirname , 0 ) ) free ( dirname ) ;
 dirname = home_dir ;
 dirlen = strlen ( dirname ) ;
 malloc_dirname = malloc_home_dir ;
 }
 else {
 char * newp ;
 size_t home_len = strlen ( home_dir ) ;
 int use_alloca = __libc_use_alloca ( alloca_used + home_len + dirlen ) ;
 if ( use_alloca ) newp = alloca_account ( home_len + dirlen , alloca_used ) ;
 else {
 newp = malloc ( home_len + dirlen ) ;
 if ( newp == NULL ) {
 if ( __builtin_expect ( malloc_home_dir , 0 ) ) free ( home_dir ) ;
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 }
 mempcpy ( mempcpy ( newp , home_dir , home_len ) , & dirname [ 1 ] , dirlen ) ;
 if ( __builtin_expect ( malloc_dirname , 0 ) ) free ( dirname ) ;
 dirname = newp ;
 dirlen += home_len - 1 ;
 malloc_dirname = ! use_alloca ;
 }
 dirname_modified = 1 ;
 }

 char * end_name = strchr ( dirname , '/' ) ;
 char * user_name ;
 int malloc_user_name = 0 ;
 const char * home_dir ;
 char * unescape = NULL ;
 if ( ! ( flags & GLOB_NOESCAPE ) ) {
 if ( end_name == NULL ) {
 unescape = strchr ( dirname , '\\' ) ;
 if ( unescape ) end_name = strchr ( unescape , '\0' ) ;
 }
 else unescape = memchr ( dirname , '\\' , end_name - dirname ) ;
 }
 if ( end_name == NULL ) user_name = dirname + 1 ;
 else {
 char * newp ;
 if ( __libc_use_alloca ( alloca_used + ( end_name - dirname ) ) ) newp = alloca_account ( end_name - dirname , alloca_used ) ;
 else {
 newp = malloc ( end_name - dirname ) ;
 if ( newp == NULL ) {
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 malloc_user_name = 1 ;
 }
 if ( unescape != NULL ) {
 char * p = mempcpy ( newp , dirname + 1 , unescape - dirname - 1 ) ;
 char * q = unescape ;
 while ( * q != '\0' ) {
 if ( * q == '\\' ) {
 if ( q [ 1 ] == '\0' ) {
 if ( filename == NULL ) * p ++ = '\\' ;
 break ;
 }
 ++ q ;
 }
 * p ++ = * q ++ ;
 }
 * p = '\0' ;
 }
 else * ( ( char * ) mempcpy ( newp , dirname + 1 , end_name - dirname ) ) = '\0' ;
 user_name = newp ;
 }
 {
 struct passwd * p ;

 char * pwtmpbuf ;
 int malloc_pwtmpbuf = 0 ;
 struct passwd pwbuf ;
 int save = errno ;


 else {
 pwtmpbuf = malloc ( buflen ) ;
 if ( pwtmpbuf == NULL ) {
 nomem_getpw : if ( __builtin_expect ( malloc_user_name , 0 ) ) free ( user_name ) ;
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 malloc_pwtmpbuf = 1 ;
 }
 while ( getpwnam_r ( user_name , & pwbuf , pwtmpbuf , buflen , & p ) != 0 ) {
 if ( errno != ERANGE ) {
 p = NULL ;
 break ;
 }
 if ( ! malloc_pwtmpbuf && __libc_use_alloca ( alloca_used + 2 * buflen ) ) pwtmpbuf = extend_alloca_account ( pwtmpbuf , buflen , 2 * buflen , alloca_used ) ;
 else {
 char * newp = realloc ( malloc_pwtmpbuf ? pwtmpbuf : NULL , 2 * buflen ) ;
 if ( newp == NULL ) {
 if ( __builtin_expect ( malloc_pwtmpbuf , 0 ) ) free ( pwtmpbuf ) ;
 goto nomem_getpw ;
 }
 pwtmpbuf = newp ;
 malloc_pwtmpbuf = 1 ;
 }
 __set_errno ( save ) ;
 }


 if ( p != NULL ) {
 size_t home_len = strlen ( p -> pw_dir ) ;
 size_t rest_len = end_name == NULL ? 0 : strlen ( end_name ) ;
 if ( __builtin_expect ( malloc_dirname , 0 ) ) free ( dirname ) ;
 malloc_dirname = 0 ;
 if ( __libc_use_alloca ( alloca_used + home_len + rest_len + 1 ) ) dirname = alloca_account ( home_len + rest_len + 1 , alloca_used ) ;
 else {
 dirname = malloc ( home_len + rest_len + 1 ) ;
 if ( dirname == NULL ) {
 if ( __builtin_expect ( malloc_pwtmpbuf , 0 ) ) free ( pwtmpbuf ) ;
 retval = GLOB_NOSPACE ;
 goto out ;
 }
 malloc_dirname = 1 ;
 }
 * ( ( char * ) mempcpy ( mempcpy ( dirname , p -> pw_dir , home_len ) , end_name , rest_len ) ) = '\0' ;
 dirlen = home_len + rest_len ;
 dirname_modified = 1 ;
 if ( __builtin_expect ( malloc_pwtmpbuf , 0 ) ) free ( pwtmpbuf ) ;
 }
 else {
 if ( __builtin_expect ( malloc_pwtmpbuf , 0 ) ) free ( pwtmpbuf ) ;
 if ( flags & GLOB_TILDE_CHECK ) return GLOB_NOMATCH ;
 }
 }
 }


 struct stat st ;
 struct_stat64 st64 ;
 if ( ( flags & GLOB_NOCHECK ) || ( ( ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ) ? ( ( * pglob -> gl_stat ) ( dirname , & st ) == 0 && S_ISDIR ( st . st_mode ) ) : ( __stat64 ( dirname , & st64 ) == 0 && S_ISDIR ( st64 . st_mode ) ) ) ) ) {
 int newcount = pglob -> gl_pathc + pglob -> gl_offs ;
 char * * new_gl_pathv ;
 new_gl_pathv = ( char * * ) realloc ( pglob -> gl_pathv , ( newcount + 1 + 1 ) * sizeof ( char * ) ) ;
 if ( new_gl_pathv == NULL ) {
 nospace : free ( pglob -> gl_pathv ) ;
 pglob -> gl_pathv = NULL ;
 pglob -> gl_pathc = 0 ;
 return GLOB_NOSPACE ;
 }
 pglob -> gl_pathv = new_gl_pathv ;
 if ( flags & GLOB_MARK ) {
 char * p ;
 pglob -> gl_pathv [ newcount ] = malloc ( dirlen + 2 ) ;
 if ( pglob -> gl_pathv [ newcount ] == NULL ) goto nospace ;
 p = mempcpy ( pglob -> gl_pathv [ newcount ] , dirname , dirlen ) ;
 p [ 0 ] = '/' ;
 p [ 1 ] = '\0' ;
 }
 else {
 pglob -> gl_pathv [ newcount ] = strdup ( dirname ) ;
 if ( pglob -> gl_pathv [ newcount ] == NULL ) goto nospace ;
 }
 pglob -> gl_pathv [ ++ newcount ] = NULL ;
 ++ pglob -> gl_pathc ;
 pglob -> gl_flags = flags ;
 return 0 ;
 }
 return GLOB_NOMATCH ;
 }
 meta = __glob_pattern_type ( dirname , ! ( flags & GLOB_NOESCAPE ) ) ;
 if ( meta & 5 ) {
 size_t i ;
 if ( ! ( flags & GLOB_NOESCAPE ) && dirlen > 0 && dirname [ dirlen - 1 ] == '\\' ) {
 char * p = ( char * ) & dirname [ dirlen - 1 ] ;
 while ( p > dirname && p [ - 1 ] == '\\' ) -- p ;
 if ( ( & dirname [ dirlen ] - p ) & 1 ) * ( char * ) & dirname [ -- dirlen ] = '\0' ;
 }
 if ( __builtin_expect ( ( flags & GLOB_ALTDIRFUNC ) != 0 , 0 ) ) {
 dirs . gl_opendir = pglob -> gl_opendir ;
 dirs . gl_readdir = pglob -> gl_readdir ;
 dirs . gl_closedir = pglob -> gl_closedir ;
 dirs . gl_stat = pglob -> gl_stat ;
 dirs . gl_lstat = pglob -> gl_lstat ;
 }
 status = glob ( dirname , ( ( flags & ( GLOB_ERR | GLOB_NOESCAPE | GLOB_ALTDIRFUNC ) ) | GLOB_NOSORT | GLOB_ONLYDIR ) , errfunc , & dirs ) ;
 if ( status != 0 ) {
 if ( ( flags & GLOB_NOCHECK ) == 0 || status != GLOB_NOMATCH ) return status ;
 goto no_matches ;
 }
 for ( i = 0 ;
 i < dirs . gl_pathc ;
 ++ i ) {
 int old_pathc ;

 extern int interrupt_state ;
 if ( interrupt_state ) {
 globfree ( & dirs ) ;
 return GLOB_ABORTED ;
 }
 }

 status = glob_in_dir ( filename , dirs . gl_pathv [ i ] , ( ( flags | GLOB_APPEND ) & ~ ( GLOB_NOCHECK | GLOB_NOMAGIC ) ) , errfunc , pglob , alloca_used ) ;
 if ( status == GLOB_NOMATCH ) continue ;
 if ( status != 0 ) {
 globfree ( & dirs ) ;
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 return status ;
 }
 if ( prefix_array ( dirs . gl_pathv [ i ] , & pglob -> gl_pathv [ old_pathc + pglob -> gl_offs ] , pglob -> gl_pathc - old_pathc ) ) {
 globfree ( & dirs ) ;
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 return GLOB_NOSPACE ;
 }
 }
 flags |= GLOB_MAGCHAR ;
 if ( pglob -> gl_pathc + pglob -> gl_offs == oldcount ) {
 no_matches : if ( flags & GLOB_NOCHECK ) {
 int newcount = pglob -> gl_pathc + pglob -> gl_offs ;
 char * * new_gl_pathv ;
 new_gl_pathv = ( char * * ) realloc ( pglob -> gl_pathv , ( newcount + 2 ) * sizeof ( char * ) ) ;
 if ( new_gl_pathv == NULL ) {
 globfree ( & dirs ) ;
 return GLOB_NOSPACE ;
 }
 pglob -> gl_pathv = new_gl_pathv ;
 pglob -> gl_pathv [ newcount ] = __strdup ( pattern ) ;
 if ( pglob -> gl_pathv [ newcount ] == NULL ) {
 globfree ( & dirs ) ;
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 return GLOB_NOSPACE ;
 }
 ++ pglob -> gl_pathc ;
 ++ newcount ;
 pglob -> gl_pathv [ newcount ] = NULL ;
 pglob -> gl_flags = flags ;
 }
 else {
 globfree ( & dirs ) ;
 return GLOB_NOMATCH ;
 }
 }
 globfree ( & dirs ) ;
 }
 else {
 int old_pathc = pglob -> gl_pathc ;
 int orig_flags = flags ;
 if ( meta & 2 ) {
 char * p = strchr ( dirname , '\\' ) , * q ;
 q = p ;
 do {
 if ( * p == '\\' ) {
 * q = * ++ p ;
 -- dirlen ;
 }
 else * q = * p ;
 ++ q ;
 }
 while ( * p ++ != '\0' ) ;
 dirname_modified = 1 ;
 }
 if ( dirname_modified ) flags &= ~ ( GLOB_NOCHECK | GLOB_NOMAGIC ) ;
 status = glob_in_dir ( filename , dirname , flags , errfunc , pglob , alloca_used ) ;
 if ( status != 0 ) {
 if ( status == GLOB_NOMATCH && flags != orig_flags && pglob -> gl_pathc + pglob -> gl_offs == oldcount ) {
 dirs . gl_pathv = NULL ;
 flags = orig_flags ;
 goto no_matches ;
 }
 return status ;
 }
 if ( dirlen > 0 ) {
 if ( prefix_array ( dirname , & pglob -> gl_pathv [ old_pathc + pglob -> gl_offs ] , pglob -> gl_pathc - old_pathc ) ) {
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 return GLOB_NOSPACE ;
 }
 }
 }
 if ( flags & GLOB_MARK ) {
 size_t i ;
 struct stat st ;
 struct_stat64 st64 ;
 for ( i = oldcount ;
 i < pglob -> gl_pathc + pglob -> gl_offs ;
 ++ i ) if ( ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ? ( ( * pglob -> gl_stat ) ( pglob -> gl_pathv [ i ] , & st ) == 0 && S_ISDIR ( st . st_mode ) ) : ( __stat64 ( pglob -> gl_pathv [ i ] , & st64 ) == 0 && S_ISDIR ( st64 . st_mode ) ) ) ) {
 size_t len = strlen ( pglob -> gl_pathv [ i ] ) + 2 ;
 char * new = realloc ( pglob -> gl_pathv [ i ] , len ) ;
 if ( new == NULL ) {
 globfree ( pglob ) ;
 pglob -> gl_pathc = 0 ;
 return GLOB_NOSPACE ;
 }
 strcpy ( & new [ len - 2 ] , "/" ) ;
 pglob -> gl_pathv [ i ] = new ;
 }
 }
 if ( ! ( flags & GLOB_NOSORT ) ) {
 qsort ( & pglob -> gl_pathv [ oldcount ] , pglob -> gl_pathc + pglob -> gl_offs - oldcount , sizeof ( char * ) , collated_compare ) ;
 }
 out : if ( __builtin_expect ( malloc_dirname , 0 ) ) free ( dirname ) ;
 return retval ;
 }