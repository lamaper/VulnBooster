METHOD ( stroke_socket_t , destroy , void , private_stroke_socket_t * this ) {
 DESTROY_IF ( this -> service ) ;
 lib -> credmgr -> remove_set ( lib -> credmgr , & this -> ca -> set ) ;
 lib -> credmgr -> remove_set ( lib -> credmgr , & this -> cred -> set ) ;
 charon -> backends -> remove_backend ( charon -> backends , & this -> config -> backend ) ;
 charon -> attributes -> remove_provider ( charon -> attributes , & this -> attribute -> provider ) ;
 charon -> attributes -> remove_handler ( charon -> attributes , & this -> handler -> handler ) ;
 this -> cred -> destroy ( this -> cred ) ;
 this -> ca -> destroy ( this -> ca ) ;
 this -> config -> destroy ( this -> config ) ;
 this -> attribute -> destroy ( this -> attribute ) ;
 this -> handler -> destroy ( this -> handler ) ;
 this -> control -> destroy ( this -> control ) ;
 this -> list -> destroy ( this -> list ) ;
 this -> counter -> destroy ( this -> counter ) ;
 free ( this ) ;
 }