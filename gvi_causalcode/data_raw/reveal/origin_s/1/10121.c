static void addFile ( const char * filename , const char * name , const char * source , UBool sourceTOC , UBool verbose ) {
 char * s ;
 uint32_t length ;
 char * fullPath = NULL ;
 if ( fileCount == fileMax ) {
 fileMax += CHUNK_FILE_COUNT ;
 files = uprv_realloc ( files , fileMax * sizeof ( files [ 0 ] ) ) ;
 if ( files == NULL ) {
 fprintf ( stderr , "pkgdata/gencmn: Could not allocate %u bytes for %d files\n" , ( unsigned int ) ( fileMax * sizeof ( files [ 0 ] ) ) , fileCount ) ;
 exit ( U_MEMORY_ALLOCATION_ERROR ) ;
 }
 }
 if ( ! sourceTOC ) {
 FileStream * file ;
 if ( uprv_pathIsAbsolute ( filename ) ) {
 fprintf ( stderr , "gencmn: Error: absolute path encountered. Old style paths are not supported. Use relative paths such as 'fur.res' or 'translit%cfur.res'.\n\tBad path: '%s'\n" , U_FILE_SEP_CHAR , filename ) ;
 exit ( U_ILLEGAL_ARGUMENT_ERROR ) ;
 }
 fullPath = pathToFullPath ( filename , source ) ;
 length = ( uint32_t ) ( uprv_strlen ( filename ) + 1 + uprv_strlen ( name ) + 1 ) ;
 s = allocString ( length ) ;
 uprv_strcpy ( s , name ) ;
 uprv_strcat ( s , U_TREE_ENTRY_SEP_STRING ) ;
 uprv_strcat ( s , filename ) ;
 fixDirToTreePath ( s ) ;
 files [ fileCount ] . basename = s ;
 files [ fileCount ] . basenameLength = length ;
 files [ fileCount ] . pathname = fullPath ;
 basenameTotal += length ;
 file = T_FileStream_open ( fullPath , "rb" ) ;
 if ( file == NULL ) {
 fprintf ( stderr , "gencmn: unable to open listed file %s\n" , fullPath ) ;
 exit ( U_FILE_ACCESS_ERROR ) ;
 }
 length = T_FileStream_size ( file ) ;
 if ( T_FileStream_error ( file ) || length <= 20 ) {
 fprintf ( stderr , "gencmn: unable to get length of listed file %s\n" , fullPath ) ;
 exit ( U_FILE_ACCESS_ERROR ) ;
 }
 T_FileStream_close ( file ) ;
 if ( maxSize && length > maxSize ) {
 if ( verbose ) {
 printf ( "%s ignored (size %ld > %ld)\n" , fullPath , ( long ) length , ( long ) maxSize ) ;
 }
 return ;
 }
 files [ fileCount ] . fileSize = length ;
 }
 else {
 char * t ;
 length = ( uint32_t ) ( uprv_strlen ( filename ) + 1 + uprv_strlen ( name ) + 1 ) ;
 s = allocString ( length ) ;
 uprv_strcpy ( s , name ) ;
 uprv_strcat ( s , U_TREE_ENTRY_SEP_STRING ) ;
 uprv_strcat ( s , filename ) ;
 fixDirToTreePath ( s ) ;
 files [ fileCount ] . basename = s ;
 t = files [ fileCount ] . pathname = allocString ( length ) ;
 while ( -- length > 0 ) {
 if ( * s == '.' || * s == '-' || * s == '/' ) {
 * t = '_' ;
 }
 else {
 * t = * s ;
 }
 ++ s ;
 ++ t ;
 }
 * t = 0 ;
 }
 ++ fileCount ;
 }