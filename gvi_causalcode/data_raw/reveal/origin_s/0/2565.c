TSConfig TSConfigGet ( unsigned int id ) {
 return reinterpret_cast < TSConfig > ( configProcessor . get ( id ) ) ;
 }