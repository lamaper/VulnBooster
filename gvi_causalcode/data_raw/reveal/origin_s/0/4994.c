static void remove_locks ( void ) {
 struct remote_lock * lock = repo -> locks ;
 fprintf ( stderr , "Removing remote locks...\n" ) ;
 while ( lock ) {
 struct remote_lock * next = lock -> next ;
 unlock_remote ( lock ) ;
 lock = next ;
 }
 }