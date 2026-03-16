static void mdb_rtxn_snap ( Operation * op , ww_ctx * ww ) {
 if ( ww -> mcd ) {
 MDB_val key , data ;
 mdb_cursor_get ( ww -> mcd , & key , & data , MDB_GET_CURRENT ) ;
 memcpy ( & ww -> key , key . mv_data , sizeof ( ID ) ) ;
 ww -> data . mv_size = data . mv_size ;
 ww -> data . mv_data = op -> o_tmpalloc ( data . mv_size , op -> o_tmpmemctx ) ;
 memcpy ( ww -> data . mv_data , data . mv_data , data . mv_size ) ;
 }
 mdb_txn_reset ( ww -> txn ) ;
 ww -> flag = 1 ;
 }