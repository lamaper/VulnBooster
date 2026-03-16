void get_type_io_data ( Oid typid , IOFuncSelector which_func , int16 * typlen , bool * typbyval , char * typalign , char * typdelim , Oid * typioparam , Oid * func ) {
 HeapTuple typeTuple ;
 Form_pg_type typeStruct ;
 if ( IsBootstrapProcessingMode ( ) ) {
 Oid typinput ;
 Oid typoutput ;
 boot_get_type_io_data ( typid , typlen , typbyval , typalign , typdelim , typioparam , & typinput , & typoutput ) ;
 switch ( which_func ) {
 case IOFunc_input : * func = typinput ;
 break ;
 case IOFunc_output : * func = typoutput ;
 break ;
 default : elog ( ERROR , "binary I/O not supported during bootstrap" ) ;
 break ;
 }
 return ;
 }
 typeTuple = SearchSysCache1 ( TYPEOID , ObjectIdGetDatum ( typid ) ) ;
 if ( ! HeapTupleIsValid ( typeTuple ) ) elog ( ERROR , "cache lookup failed for type %u" , typid ) ;
 typeStruct = ( Form_pg_type ) GETSTRUCT ( typeTuple ) ;
 * typlen = typeStruct -> typlen ;
 * typbyval = typeStruct -> typbyval ;
 * typalign = typeStruct -> typalign ;
 * typdelim = typeStruct -> typdelim ;
 * typioparam = getTypeIOParam ( typeTuple ) ;
 switch ( which_func ) {
 case IOFunc_input : * func = typeStruct -> typinput ;
 break ;
 case IOFunc_output : * func = typeStruct -> typoutput ;
 break ;
 case IOFunc_receive : * func = typeStruct -> typreceive ;
 break ;
 case IOFunc_send : * func = typeStruct -> typsend ;
 break ;
 }
 ReleaseSysCache ( typeTuple ) ;
 }