static gpgme_error_t gpgsm_set_locale ( void * engine , int category , const char * value ) {
 engine_gpgsm_t gpgsm = engine ;
 gpgme_error_t err ;
 char * optstr ;
 char * catstr ;
 if ( 0 ) ;

 catstr = "lc-ctype" ;
 if ( ! value && gpgsm -> lc_ctype_set ) return gpg_error ( GPG_ERR_INV_VALUE ) ;
 if ( value ) gpgsm -> lc_ctype_set = 1 ;
 }

 catstr = "lc-messages" ;
 if ( ! value && gpgsm -> lc_messages_set ) return gpg_error ( GPG_ERR_INV_VALUE ) ;
 if ( value ) gpgsm -> lc_messages_set = 1 ;
 }

 if ( ! value ) return 0 ;
 if ( asprintf ( & optstr , "OPTION %s=%s" , catstr , value ) < 0 ) err = gpg_error_from_syserror ( ) ;
 else {
 err = assuan_transact ( gpgsm -> assuan_ctx , optstr , NULL , NULL , NULL , NULL , NULL , NULL ) ;
 free ( optstr ) ;
 }
 return err ;
 }