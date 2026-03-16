static void test_bug12337762 ( ) {
 int rc , i = 0 ;
 MYSQL_RES * result ;
 MYSQL_FIELD * field ;
 unsigned int tab_charsetnr [ 3 ] = {
 0 }
 ;
 DBUG_ENTER ( "test_bug12337762" ) ;
 myheader ( "test_bug12337762" ) ;
 rc = mysql_query ( mysql , "drop table if exists charset_tab" ) ;
 rc = mysql_query ( mysql , "create table charset_tab(" "txt1 varchar(32) character set Latin1," "txt2 varchar(32) character set Latin1 collate latin1_bin," "txt3 varchar(32) character set utf8 collate utf8_bin" ")" ) ;
 DIE_UNLESS ( rc == 0 ) ;
 DIE_IF ( mysql_errno ( mysql ) ) ;
 rc = mysql_query ( mysql , "drop view if exists charset_view" ) ;
 rc = mysql_query ( mysql , "create view charset_view as " "select * from charset_tab;
" ) ;
 DIE_UNLESS ( rc == 0 ) ;
 DIE_IF ( mysql_errno ( mysql ) ) ;
 result = mysql_list_fields ( mysql , "charset_tab" , NULL ) ;
 DIE_IF ( mysql_errno ( mysql ) ) ;
 i = 0 ;
 while ( ( field = mysql_fetch_field ( result ) ) ) {
 printf ( "field name %s\n" , field -> name ) ;
 printf ( "field table %s\n" , field -> table ) ;
 printf ( "field type %d\n" , field -> type ) ;