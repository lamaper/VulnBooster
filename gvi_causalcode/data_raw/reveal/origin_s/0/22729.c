static void InterpretPS ( FILE * ps , char * psstr , EntityChar * ec , RetStack * rs ) {
 IO wrapper ;
 memset ( & wrapper , 0 , sizeof ( wrapper ) ) ;
 wrapper . advance_width = UNDEFINED_WIDTH ;
 pushio ( & wrapper , ps , psstr , 0 ) ;
 _InterpretPS ( & wrapper , ec , rs ) ;
 }