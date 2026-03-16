static void remoteDispatchCopyError ( remote_error * rerr , virErrorPtr verr ) {
 rerr -> code = verr -> code ;
 rerr -> domain = verr -> domain ;
 rerr -> message = verr -> message ? malloc ( sizeof ( char * ) ) : NULL ;
 if ( rerr -> message ) * rerr -> message = strdup ( verr -> message ) ;
 rerr -> level = verr -> level ;
 rerr -> str1 = verr -> str1 ? malloc ( sizeof ( char * ) ) : NULL ;
 if ( rerr -> str1 ) * rerr -> str1 = strdup ( verr -> str1 ) ;
 rerr -> str2 = verr -> str2 ? malloc ( sizeof ( char * ) ) : NULL ;
 if ( rerr -> str2 ) * rerr -> str2 = strdup ( verr -> str2 ) ;
 rerr -> str3 = verr -> str3 ? malloc ( sizeof ( char * ) ) : NULL ;
 if ( rerr -> str3 ) * rerr -> str3 = strdup ( verr -> str3 ) ;
 rerr -> int1 = verr -> int1 ;
 rerr -> int2 = verr -> int2 ;
 }