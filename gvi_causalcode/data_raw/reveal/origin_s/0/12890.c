void init_re ( void ) {
 const char * ps_re_str = "^(" "[[:space:]]*REPLACE[[:space:]]|" "[[:space:]]*INSERT[[:space:]]|" "[[:space:]]*UPDATE[[:space:]]|" "[[:space:]]*DELETE[[:space:]]|" "[[:space:]]*SELECT[[:space:]]|" "[[:space:]]*CREATE[[:space:]]+TABLE[[:space:]]|" "[[:space:]]*DO[[:space:]]|" "[[:space:]]*SET[[:space:]]+OPTION[[:space:]]|" "[[:space:]]*DELETE[[:space:]]+MULTI[[:space:]]|" "[[:space:]]*UPDATE[[:space:]]+MULTI[[:space:]]|" "[[:space:]]*INSERT[[:space:]]+SELECT[[:space:]])" ;
 const char * sp_re_str = ps_re_str ;
 const char * view_re_str = "^(" "[[:space:]]*SELECT[[:space:]])" ;
 init_re_comp ( & ps_re , ps_re_str ) ;
 init_re_comp ( & sp_re , sp_re_str ) ;
 init_re_comp ( & view_re , view_re_str ) ;
 }