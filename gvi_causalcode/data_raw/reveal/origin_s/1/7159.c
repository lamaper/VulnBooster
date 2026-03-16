static UFILE * finit_owner ( FILE * f , const char * locale , const char * codepage , UBool takeOwnership ) {
 UErrorCode status = U_ZERO_ERROR ;
 UFILE * result ;
 if ( f == NULL ) {
 return 0 ;
 }
 result = ( UFILE * ) uprv_malloc ( sizeof ( UFILE ) ) ;
 if ( result == NULL ) {
 return 0 ;
 }
 uprv_memset ( result , 0 , sizeof ( UFILE ) ) ;
 result -> fFileno = fileno ( f ) ;




 else # endif {
 result -> fFile = f ;
 }
 result -> str . fBuffer = result -> fUCBuffer ;
 result -> str . fPos = result -> fUCBuffer ;
 result -> str . fLimit = result -> fUCBuffer ;

 uprv_free ( result ) ;
 return 0 ;
 }

 result -> fConverter = ucnv_open ( codepage , & status ) ;
 }
 if ( U_SUCCESS ( status ) ) {
 result -> fOwnFile = takeOwnership ;
 }
 else {


 result = NULL ;
 }
 return result ;
 }