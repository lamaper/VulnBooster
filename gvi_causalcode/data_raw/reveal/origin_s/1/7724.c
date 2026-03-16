static int glob_in_dir ( const char * pattern , const char * directory , int flags , int ( * errfunc ) ( const char * , int ) , glob_t * pglob ) {
 size_t dirlen = strlen ( directory ) ;
 void * stream = NULL ;
 struct globnames {
 struct globnames * next ;
 size_t count ;
 char * name [ 64 ] ;
 }
 ;

 struct globnames * names = & init_names ;
 struct globnames * names_alloca = & init_names ;
 size_t nfound = 0 ;
 size_t allocasize = sizeof ( init_names ) ;
 size_t cur = 0 ;
 int meta ;
 int save ;
 init_names . next = NULL ;
 init_names . count = INITIAL_COUNT ;
 meta = __glob_pattern_type ( pattern , ! ( flags & GLOB_NOESCAPE ) ) ;
 if ( meta == 0 && ( flags & ( GLOB_NOCHECK | GLOB_NOMAGIC ) ) ) {
 flags |= GLOB_NOCHECK ;
 }
 else if ( meta == 0 ) {
 struct stat st ;
 struct_stat64 st64 ;
 size_t patlen = strlen ( pattern ) ;
 char * fullname = ( char * ) __alloca ( dirlen + 1 + patlen + 1 ) ;
 mempcpy ( mempcpy ( mempcpy ( fullname , directory , dirlen ) , "/" , 1 ) , pattern , patlen + 1 ) ;
 if ( ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ? ( * pglob -> gl_stat ) ( fullname , & st ) : __stat64 ( fullname , & st64 ) ) == 0 ) flags |= GLOB_NOCHECK ;
 }
 else {
 stream = ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ? ( * pglob -> gl_opendir ) ( directory ) : opendir ( directory ) ) ;
 if ( stream == NULL ) {
 if ( errno != ENOTDIR && ( ( errfunc != NULL && ( * errfunc ) ( directory , errno ) ) || ( flags & GLOB_ERR ) ) ) return GLOB_ABORTED ;
 }
 else {


 flags |= GLOB_MAGCHAR ;
 while ( 1 ) {
 const char * name ;
 size_t len ;

 union {
 struct dirent64 d64 ;
 char room [ offsetof ( struct dirent64 , d_name [ 0 ] ) + NAME_MAX + 1 ] ;
 }
 d64buf ;
 if ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ) {
 struct dirent * d32 = ( * pglob -> gl_readdir ) ( stream ) ;
 if ( d32 != NULL ) {
 CONVERT_DIRENT_DIRENT64 ( & d64buf . d64 , d32 ) ;
 d = & d64buf . d64 ;
 }
 else d = NULL ;
 }
 else d = __readdir64 ( stream ) ;


 if ( ! REAL_DIR_ENTRY ( d ) ) continue ;
 if ( ( flags & GLOB_ONLYDIR ) && ! DIRENT_MIGHT_BE_DIR ( d ) ) continue ;
 name = d -> d_name ;
 if ( fnmatch ( pattern , name , fnm_flags ) == 0 ) {
 if ( ! DIRENT_MIGHT_BE_SYMLINK ( d ) || link_exists_p ( dfd , directory , dirlen , name , pglob , flags ) ) {
 if ( cur == names -> count ) {
 struct globnames * newnames ;
 size_t count = names -> count * 2 ;
 size_t size = ( sizeof ( struct globnames ) + ( ( count - INITIAL_COUNT ) * sizeof ( char * ) ) ) ;
 allocasize += size ;
 if ( __libc_use_alloca ( allocasize ) ) newnames = names_alloca = __alloca ( size ) ;
 else if ( ( newnames = malloc ( size ) ) == NULL ) goto memory_error ;
 newnames -> count = count ;
 newnames -> next = names ;
 names = newnames ;
 cur = 0 ;
 }
 len = NAMLEN ( d ) ;
 names -> name [ cur ] = ( char * ) malloc ( len + 1 ) ;
 if ( names -> name [ cur ] == NULL ) goto memory_error ;
 * ( ( char * ) mempcpy ( names -> name [ cur ++ ] , name , len ) ) = '\0' ;
 ++ nfound ;
 }
 }
 }
 }
 }
 if ( nfound == 0 && ( flags & GLOB_NOCHECK ) ) {
 size_t len = strlen ( pattern ) ;
 nfound = 1 ;
 names -> name [ cur ] = ( char * ) malloc ( len + 1 ) ;
 if ( names -> name [ cur ] == NULL ) goto memory_error ;
 * ( ( char * ) mempcpy ( names -> name [ cur ++ ] , pattern , len ) ) = '\0' ;
 }
 int result = GLOB_NOMATCH ;
 if ( nfound != 0 ) {
 result = 0 ;
 char * * new_gl_pathv ;
 new_gl_pathv = ( char * * ) realloc ( pglob -> gl_pathv , ( pglob -> gl_pathc + pglob -> gl_offs + nfound + 1 ) * sizeof ( char * ) ) ;
 if ( new_gl_pathv == NULL ) {
 memory_error : while ( 1 ) {
 struct globnames * old = names ;
 for ( size_t i = 0 ;
 i < cur ;
 ++ i ) free ( names -> name [ i ] ) ;
 names = names -> next ;
 if ( names == NULL ) {
 assert ( old == & init_names ) ;
 break ;
 }
 cur = names -> count ;
 if ( old == names_alloca ) names_alloca = names ;
 else free ( old ) ;
 }
 result = GLOB_NOSPACE ;
 }
 else {
 while ( 1 ) {
 struct globnames * old = names ;
 for ( size_t i = 0 ;
 i < cur ;
 ++ i ) new_gl_pathv [ pglob -> gl_offs + pglob -> gl_pathc ++ ] = names -> name [ i ] ;
 names = names -> next ;
 if ( names == NULL ) {
 assert ( old == & init_names ) ;
 break ;
 }
 cur = names -> count ;
 if ( old == names_alloca ) names_alloca = names ;
 else free ( old ) ;
 }
 pglob -> gl_pathv = new_gl_pathv ;
 pglob -> gl_pathv [ pglob -> gl_offs + pglob -> gl_pathc ] = NULL ;
 pglob -> gl_flags = flags ;
 }
 }
 if ( stream != NULL ) {
 save = errno ;
 if ( __builtin_expect ( flags & GLOB_ALTDIRFUNC , 0 ) ) ( * pglob -> gl_closedir ) ( stream ) ;
 else closedir ( stream ) ;
 __set_errno ( save ) ;
 }
 return result ;
 }