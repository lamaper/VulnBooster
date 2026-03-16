rfbBool rfbSendDirContent ( rfbClientPtr cl , int length , char * buffer ) {
 char retfilename [ MAX_PATH ] ;
 char path [ MAX_PATH ] ;
 struct stat statbuf ;
 RFB_FIND_DATA win32filename ;
 int nOptLen = 0 , retval = 0 ;

 HANDLE findHandle ;
 int pathLen , basePathLength ;
 char * basePath ;

 struct dirent * direntp = NULL ;

 if ( ! rfbFilenameTranslate2UNIX ( cl , buffer , path , sizeof ( path ) ) ) return FALSE ;
 if ( DB ) rfbLog ( "rfbProcessFileTransfer() rfbDirContentRequest: rfbRDirContent: \"%s\"->\"%s\"\n" , buffer , path ) ;

 basePath = malloc ( pathLen + 3 ) ;
 memcpy ( basePath , path , pathLen ) ;
 basePathLength = pathLen ;
 basePath [ basePathLength ] = '\\' ;
 basePath [ basePathLength + 1 ] = '*' ;
 basePath [ basePathLength + 2 ] = '\0' ;
 memset ( & winFindData , 0 , sizeof ( winFindData ) ) ;
 findHandle = FindFirstFileA ( path , & winFindData ) ;
 free ( basePath ) ;
 if ( findHandle == INVALID_HANDLE_VALUE ) # else dirp = opendir ( path ) ;
 if ( dirp == NULL ) # endif return rfbSendFileTransferMessage ( cl , rfbDirPacket , rfbADirectory , 0 , 0 , NULL ) ;
 if ( rfbSendFileTransferMessage ( cl , rfbDirPacket , rfbADirectory , 0 , length , buffer ) == FALSE ) return FALSE ;

 direntp != NULL ;
 direntp = readdir ( dirp ) ) # endif {



 if ( retval == 0 ) {
 memset ( ( char * ) & win32filename , 0 , sizeof ( win32filename ) ) ;

 win32filename . ftCreationTime . dwLowDateTime = winFindData . ftCreationTime . dwLowDateTime ;
 win32filename . ftCreationTime . dwHighDateTime = winFindData . ftCreationTime . dwHighDateTime ;
 win32filename . ftLastAccessTime . dwLowDateTime = winFindData . ftLastAccessTime . dwLowDateTime ;
 win32filename . ftLastAccessTime . dwHighDateTime = winFindData . ftLastAccessTime . dwHighDateTime ;
 win32filename . ftLastWriteTime . dwLowDateTime = winFindData . ftLastWriteTime . dwLowDateTime ;
 win32filename . ftLastWriteTime . dwHighDateTime = winFindData . ftLastWriteTime . dwHighDateTime ;
 win32filename . nFileSizeLow = winFindData . nFileSizeLow ;
 win32filename . nFileSizeHigh = winFindData . nFileSizeHigh ;
 win32filename . dwReserved0 = winFindData . dwReserved0 ;
 win32filename . dwReserved1 = winFindData . dwReserved1 ;
 strcpy ( ( char * ) win32filename . cFileName , winFindData . cFileName ) ;
 strcpy ( ( char * ) win32filename . cAlternateFileName , winFindData . cAlternateFileName ) ;

 if ( S_ISDIR ( statbuf . st_mode ) ) win32filename . dwFileAttributes = Swap32IfBE ( RFB_FILE_ATTRIBUTE_DIRECTORY ) ;
 win32filename . ftCreationTime . dwLowDateTime = Swap32IfBE ( statbuf . st_ctime ) ;
 win32filename . ftCreationTime . dwHighDateTime = 0 ;
 win32filename . ftLastAccessTime . dwLowDateTime = Swap32IfBE ( statbuf . st_atime ) ;
 win32filename . ftLastAccessTime . dwHighDateTime = 0 ;
 win32filename . ftLastWriteTime . dwLowDateTime = Swap32IfBE ( statbuf . st_mtime ) ;
 win32filename . ftLastWriteTime . dwHighDateTime = 0 ;
 win32filename . nFileSizeLow = Swap32IfBE ( statbuf . st_size ) ;
 win32filename . nFileSizeHigh = 0 ;
 win32filename . dwReserved0 = 0 ;
 win32filename . dwReserved1 = 0 ;
 strcpy ( ( char * ) win32filename . cFileName , direntp -> d_name ) ;

 nOptLen = sizeof ( RFB_FIND_DATA ) - MAX_PATH - 14 + strlen ( ( char * ) win32filename . cFileName ) ;
 if ( rfbSendFileTransferMessage ( cl , rfbDirPacket , rfbADirectory , 0 , nOptLen , ( char * ) & win32filename ) == FALSE ) {



 }
 }
 }

 FindClose ( findHandle ) ;
 findHandle = INVALID_HANDLE_VALUE ;
 }


 FindClose ( findHandle ) ;
 }


 }