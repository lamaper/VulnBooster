static int virLogSetDefaultOutputToJournald ( void ) {
 virLogPriority priority = virLogDefaultPriority ;
 if ( priority == VIR_LOG_DEBUG ) priority = VIR_LOG_INFO ;
 return virAsprintf ( & virLogDefaultOutput , "%d:journald" , priority ) ;
 }