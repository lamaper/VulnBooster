static int virLogSetDefaultOutputToStderr ( void ) {
 return virAsprintf ( & virLogDefaultOutput , "%d:stderr" , virLogDefaultPriority ) ;
 }