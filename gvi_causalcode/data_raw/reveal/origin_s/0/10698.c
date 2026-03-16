void exsltRegisterAll ( void ) {
 xsltInitGlobals ( ) ;
 exsltCommonRegister ( ) ;


 exsltSetsRegister ( ) ;
 exsltFuncRegister ( ) ;
 exsltStrRegister ( ) ;
 exsltDateRegister ( ) ;
 exsltSaxonRegister ( ) ;
 exsltDynRegister ( ) ;
 }