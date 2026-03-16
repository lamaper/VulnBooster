static int qemuAgentOnceInit ( void ) {
 if ( ! ( qemuAgentClass = virClassNew ( virClassForObjectLockable ( ) , "qemuAgent" , sizeof ( qemuAgent ) , qemuAgentDispose ) ) ) return - 1 ;
 return 0 ;
 }