TSUuid TSProcessUuidGet ( void ) {
 Machine * machine = Machine : : instance ( ) ;
 return ( TSUuid ) ( & machine -> uuid ) ;
 }