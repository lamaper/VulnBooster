static List * fetch_function_defaults ( HeapTuple func_tuple ) {
 List * defaults ;
 Datum proargdefaults ;
 bool isnull ;
 char * str ;
 proargdefaults = SysCacheGetAttr ( PROCOID , func_tuple , Anum_pg_proc_proargdefaults , & isnull ) ;
 if ( isnull ) elog ( ERROR , "not enough default arguments" ) ;
 str = TextDatumGetCString ( proargdefaults ) ;
 defaults = ( List * ) stringToNode ( str ) ;
 Assert ( IsA ( defaults , List ) ) ;
 pfree ( str ) ;
 return defaults ;
 }