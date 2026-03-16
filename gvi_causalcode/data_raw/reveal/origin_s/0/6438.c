static void getOutFilename ( const char * inFilename , const char * destdir , char * outFilename , char * entryName , const char * newSuffix , const char * optFilename ) {
 const char * basename = findBasename ( inFilename ) , * suffix = uprv_strrchr ( basename , '.' ) ;
 if ( destdir != NULL && * destdir != 0 ) {
 do {
 * outFilename ++ = * destdir ++ ;
 }
 while ( * destdir != 0 ) ;
 if ( * ( outFilename - 1 ) != U_FILE_SEP_CHAR ) {
 * outFilename ++ = U_FILE_SEP_CHAR ;
 }
 inFilename = basename ;
 }
 else {
 while ( inFilename < basename ) {
 * outFilename ++ = * inFilename ++ ;
 }
 }
 if ( suffix == NULL ) {
 uprv_strcpy ( entryName , inFilename ) ;
 if ( optFilename != NULL ) {
 uprv_strcpy ( outFilename , optFilename ) ;
 }
 else {
 uprv_strcpy ( outFilename , inFilename ) ;
 }
 uprv_strcat ( outFilename , newSuffix ) ;
 }
 else {
 char * saveOutFilename = outFilename ;
 while ( inFilename < suffix ) {
 if ( * inFilename == '-' ) {
 * outFilename ++ = * entryName ++ = '_' ;
 inFilename ++ ;
 }
 else {
 * outFilename ++ = * entryName ++ = * inFilename ++ ;
 }
 }
 * outFilename ++ = * entryName ++ = '_' ;
 ++ inFilename ;
 while ( * inFilename != 0 ) {
 * outFilename ++ = * entryName ++ = * inFilename ++ ;
 }
 * entryName = 0 ;
 if ( optFilename != NULL ) {
 uprv_strcpy ( saveOutFilename , optFilename ) ;
 uprv_strcat ( saveOutFilename , newSuffix ) ;
 }
 else {
 uprv_strcpy ( outFilename , newSuffix ) ;
 }
 }
 }