static KeydbResourceType rt_from_file ( const char * filename , int * r_found , int * r_openpgp ) {
 u32 magic ;
 unsigned char verbuf [ 4 ] ;
 FILE * fp ;
 KeydbResourceType rt = KEYDB_RESOURCE_TYPE_NONE ;
 * r_found = * r_openpgp = 0 ;
 fp = fopen ( filename , "rb" ) ;
 if ( fp ) {
 * r_found = 1 ;
 if ( fread ( & magic , 4 , 1 , fp ) == 1 ) {
 if ( magic == 0x13579ace || magic == 0xce9a5713 ) ;
 else if ( fread ( & verbuf , 4 , 1 , fp ) == 1 && verbuf [ 0 ] == 1 && fread ( & magic , 4 , 1 , fp ) == 1 && ! memcmp ( & magic , "KBXf" , 4 ) ) {
 if ( ( verbuf [ 3 ] & 0x02 ) ) * r_openpgp = 1 ;
 rt = KEYDB_RESOURCE_TYPE_KEYBOX ;
 }
 else rt = KEYDB_RESOURCE_TYPE_KEYRING ;
 }
 else rt = KEYDB_RESOURCE_TYPE_KEYRING ;
 fclose ( fp ) ;
 }
 return rt ;
 }