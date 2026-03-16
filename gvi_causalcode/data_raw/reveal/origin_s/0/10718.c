static int get_result_width ( MYSQL_RES * result ) {
 unsigned int len = 0 ;
 MYSQL_FIELD * field ;
 MYSQL_FIELD_OFFSET offset ;

 DBUG_ASSERT ( offset == 0 ) ;


 ( void ) mysql_field_seek ( result , offset ) ;
 return len + 1 ;
 }