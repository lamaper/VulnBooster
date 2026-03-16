gpg_error_t keydb_add_resource ( const char * url , unsigned int flags ) {
 static int any_registered ;
 const char * resname = url ;
 char * filename = NULL ;
 int create ;
 int read_only = ! ! ( flags & KEYDB_RESOURCE_FLAG_READONLY ) ;
 int is_default = ! ! ( flags & KEYDB_RESOURCE_FLAG_DEFAULT ) ;
 int rc = 0 ;
 KeydbResourceType rt = KEYDB_RESOURCE_TYPE_NONE ;
 void * token ;
 create = ( ! read_only && ! any_registered ) ;
 if ( strlen ( resname ) > 11 && ! strncmp ( resname , "gnupg-ring:" , 11 ) ) {
 rt = KEYDB_RESOURCE_TYPE_KEYRING ;
 resname += 11 ;
 }
 else if ( strlen ( resname ) > 10 && ! strncmp ( resname , "gnupg-kbx:" , 10 ) ) {
 rt = KEYDB_RESOURCE_TYPE_KEYBOX ;
 resname += 10 ;
 }

 log_error ( "invalid key resource URL '%s'\n" , url ) ;
 rc = gpg_error ( GPG_ERR_GENERAL ) ;
 goto leave ;
 }

 if ( strchr ( resname , DIRSEP_C ) ) filename = make_filename ( resname , NULL ) ;
 else filename = make_filename ( opt . homedir , resname , NULL ) ;
 }
 else filename = xstrdup ( resname ) ;
 if ( rt == KEYDB_RESOURCE_TYPE_NONE ) {
 int found , openpgp_flag ;
 int pass = 0 ;
 size_t filenamelen ;
 check_again : filenamelen = strlen ( filename ) ;
 rt = rt_from_file ( filename , & found , & openpgp_flag ) ;
 if ( found ) {
 if ( ! pass && is_default && rt == KEYDB_RESOURCE_TYPE_KEYRING && filenamelen > 4 && ! strcmp ( filename + filenamelen - 4 , ".gpg" ) ) {
 strcpy ( filename + filenamelen - 4 , ".kbx" ) ;
 if ( ( rt_from_file ( filename , & found , & openpgp_flag ) == KEYDB_RESOURCE_TYPE_KEYBOX ) && found && openpgp_flag ) rt = KEYDB_RESOURCE_TYPE_KEYBOX ;
 else strcpy ( filename + filenamelen - 4 , ".gpg" ) ;
 }
 }
 else if ( ! pass && is_default && create && filenamelen > 4 && ! strcmp ( filename + filenamelen - 4 , ".gpg" ) ) {
 strcpy ( filename + filenamelen - 4 , ".kbx" ) ;
 pass ++ ;
 goto check_again ;
 }
 else rt = KEYDB_RESOURCE_TYPE_KEYBOX ;
 }
 switch ( rt ) {
 case KEYDB_RESOURCE_TYPE_NONE : log_error ( "unknown type of key resource '%s'\n" , url ) ;
 rc = gpg_error ( GPG_ERR_GENERAL ) ;
 goto leave ;
 case KEYDB_RESOURCE_TYPE_KEYRING : rc = maybe_create_keyring_or_box ( filename , 0 , create ) ;
 if ( rc ) goto leave ;
 if ( keyring_register_filename ( filename , read_only , & token ) ) {
 if ( used_resources >= MAX_KEYDB_RESOURCES ) rc = gpg_error ( GPG_ERR_RESOURCE_LIMIT ) ;
 else {
 if ( ( flags & KEYDB_RESOURCE_FLAG_PRIMARY ) ) primary_keyring = token ;
 all_resources [ used_resources ] . type = rt ;
 all_resources [ used_resources ] . u . kr = NULL ;
 all_resources [ used_resources ] . token = token ;
 used_resources ++ ;
 }
 }
 else {
 if ( ( flags & KEYDB_RESOURCE_FLAG_PRIMARY ) ) primary_keyring = token ;
 }
 break ;
 case KEYDB_RESOURCE_TYPE_KEYBOX : {
 rc = maybe_create_keyring_or_box ( filename , 1 , create ) ;
 if ( rc ) goto leave ;
 token = keybox_register_file ( filename , 0 ) ;
 if ( token ) {
 if ( used_resources >= MAX_KEYDB_RESOURCES ) rc = gpg_error ( GPG_ERR_RESOURCE_LIMIT ) ;
 else {
 all_resources [ used_resources ] . type = rt ;
 all_resources [ used_resources ] . u . kb = NULL ;
 all_resources [ used_resources ] . token = token ;
 used_resources ++ ;
 }
 }
 else {
 }
 }
 break ;
 default : log_error ( "resource type of '%s' not supported\n" , url ) ;
 rc = gpg_error ( GPG_ERR_GENERAL ) ;
 goto leave ;
 }
 leave : if ( rc ) log_error ( _ ( "keyblock resource '%s': %s\n" ) , filename , gpg_strerror ( rc ) ) ;
 else any_registered = 1 ;
 xfree ( filename ) ;
 return rc ;
 }