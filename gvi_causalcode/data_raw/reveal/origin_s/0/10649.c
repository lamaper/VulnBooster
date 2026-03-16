static int mdb_get_nextid ( MDB_cursor * mci , ID * cursor ) {
 MDB_val key ;
 ID id ;
 int rc ;
 id = * cursor + 1 ;
 key . mv_data = & id ;
 key . mv_size = sizeof ( ID ) ;
 rc = mdb_cursor_get ( mci , & key , NULL , MDB_SET_RANGE ) ;
 if ( rc ) return rc ;
 memcpy ( cursor , key . mv_data , sizeof ( ID ) ) ;
 return 0 ;
 }