extern int main ( int argc , char * argv [ ] ) {
 UBool verbose = TRUE ;
 char writeCode ;
 U_MAIN_INIT_ARGS ( argc , argv ) ;
 options [ kOptDestDir ] . value = "." ;
 argc = u_parseArgs ( argc , argv , UPRV_LENGTHOF ( options ) , options ) ;
 if ( argc < 0 ) {
 fprintf ( stderr , "error in command line argument \"%s\"\n" , argv [ - argc ] ) ;
 }
 if ( argc < 0 || options [ kOptHelpH ] . doesOccur || options [ kOptHelpQuestionMark ] . doesOccur ) {
 fprintf ( stderr , "usage: %s [-options] filename1 filename2 ...\n" "\tread each binary input file and \n" "\tcreate a .c file with a byte array that contains the input file's data\n" "options:\n" "\t-h or -? or --help this usage text\n" "\t-d or --destdir destination directory, followed by the path\n" "\t-n or --name symbol prefix, followed by the prefix\n" "\t-e or --entrypoint entry point name, followed by the name (_dat will be appended)\n" "\t-r or --revision Specify a version\n" , argv [ 0 ] ) ;


 printAssemblyHeadersToStdErr ( ) ;
 }
 else {
 const char * message , * filename ;
 if ( options [ kOptAssembly ] . doesOccur ) {
 message = "generating assembly code for %s\n" ;
 writeCode = CALL_WRITEASSEMBLY ;
 if ( ! checkAssemblyHeaderName ( options [ kOptAssembly ] . value ) ) {
 fprintf ( stderr , "Assembly type \"%s\" is unknown.\n" , options [ kOptAssembly ] . value ) ;
 return - 1 ;
 }
 }

 message = "generating object code for %s\n" ;
 writeCode = CALL_WRITEOBJECT ;
 }

 message = "generating C code for %s\n" ;
 writeCode = CALL_WRITECCODE ;
 }
 while ( -- argc ) {
 filename = getLongPathname ( argv [ argc ] ) ;
 if ( verbose ) {
 fprintf ( stdout , message , filename ) ;
 }
 switch ( writeCode ) {
 case CALL_WRITECCODE : writeCCode ( filename , options [ kOptDestDir ] . value , options [ kOptName ] . doesOccur ? options [ kOptName ] . value : NULL , options [ kOptFilename ] . doesOccur ? options [ kOptFilename ] . value : NULL , NULL ) ;
 break ;
 case CALL_WRITEASSEMBLY : writeAssemblyCode ( filename , options [ kOptDestDir ] . value , options [ kOptEntryPoint ] . doesOccur ? options [ kOptEntryPoint ] . value : NULL , options [ kOptFilename ] . doesOccur ? options [ kOptFilename ] . value : NULL , NULL ) ;
 break ;

 break ;

 }
 }
 }
 return 0 ;
 }