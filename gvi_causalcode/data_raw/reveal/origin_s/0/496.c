int virLogSetDefaultOutput ( const char * filename , bool godaemon , bool privileged ) {
 if ( ! godaemon ) return virLogSetDefaultOutputToStderr ( ) ;
 if ( access ( "/run/systemd/journal/socket" , W_OK ) >= 0 ) return virLogSetDefaultOutputToJournald ( ) ;
 return virLogSetDefaultOutputToFile ( filename , privileged ) ;
 }