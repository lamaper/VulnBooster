static krb5_error_code kadmin_parse_name ( char * name , krb5_principal * principal ) {
 char * cp , * fullname ;
 krb5_error_code retval ;
 int result ;
 cp = strchr ( name , '@' ) ;
 while ( cp ) {
 if ( cp - name && * ( cp - 1 ) != '\\' ) break ;
 else cp = strchr ( cp + 1 , '@' ) ;
 }
 if ( cp == NULL ) result = asprintf ( & fullname , "%s@%s" , name , def_realm ) ;
 else result = asprintf ( & fullname , "%s" , name ) ;
 if ( result < 0 ) return ENOMEM ;
 retval = krb5_parse_name ( context , fullname , principal ) ;
 free ( fullname ) ;
 return retval ;
 }