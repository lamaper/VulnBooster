stroke_socket_t * stroke_socket_create ( ) {
 private_stroke_socket_t * this ;
 int max_concurrent ;
 char * uri ;
 INIT ( this , . public = {
 . destroy = _destroy , }
 , . prevent_loglevel_changes = lib -> settings -> get_bool ( lib -> settings , "%s.plugins.stroke.prevent_loglevel_changes" , FALSE , lib -> ns ) , ) ;
 this -> ca = stroke_ca_create ( ) ;
 this -> cred = stroke_cred_create ( this -> ca ) ;
 this -> attribute = stroke_attribute_create ( ) ;
 this -> handler = stroke_handler_create ( ) ;
 this -> config = stroke_config_create ( this -> ca , this -> cred , this -> attribute ) ;
 this -> control = stroke_control_create ( ) ;
 this -> list = stroke_list_create ( this -> attribute ) ;
 this -> counter = stroke_counter_create ( ) ;
 lib -> credmgr -> add_set ( lib -> credmgr , & this -> ca -> set ) ;
 lib -> credmgr -> add_set ( lib -> credmgr , & this -> cred -> set ) ;
 charon -> backends -> add_backend ( charon -> backends , & this -> config -> backend ) ;
 charon -> attributes -> add_provider ( charon -> attributes , & this -> attribute -> provider ) ;
 charon -> attributes -> add_handler ( charon -> attributes , & this -> handler -> handler ) ;
 max_concurrent = lib -> settings -> get_int ( lib -> settings , "%s.plugins.stroke.max_concurrent" , MAX_CONCURRENT_DEFAULT , lib -> ns ) ;
 uri = lib -> settings -> get_str ( lib -> settings , "%s.plugins.stroke.socket" , "unix://" STROKE_SOCKET , lib -> ns ) ;
 this -> service = lib -> streams -> create_service ( lib -> streams , uri , 10 ) ;
 if ( ! this -> service ) {
 DBG1 ( DBG_CFG , "creating stroke socket failed" ) ;
 destroy ( this ) ;
 return NULL ;
 }
 this -> service -> on_accept ( this -> service , ( stream_service_cb_t ) on_accept , this , JOB_PRIO_CRITICAL , max_concurrent ) ;
 return & this -> public ;
 }