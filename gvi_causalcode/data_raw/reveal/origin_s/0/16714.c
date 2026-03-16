static Datum ExecEvalArray ( ArrayExprState * astate , ExprContext * econtext , bool * isNull , ExprDoneCond * isDone ) {
 ArrayExpr * arrayExpr = ( ArrayExpr * ) astate -> xprstate . expr ;
 ArrayType * result ;
 ListCell * element ;
 Oid element_type = arrayExpr -> element_typeid ;
 int ndims = 0 ;
 int dims [ MAXDIM ] ;
 int lbs [ MAXDIM ] ;
 * isNull = false ;
 if ( isDone ) * isDone = ExprSingleResult ;
 if ( ! arrayExpr -> multidims ) {
 int nelems ;
 Datum * dvalues ;
 bool * dnulls ;
 int i = 0 ;
 ndims = 1 ;
 nelems = list_length ( astate -> elements ) ;
 if ( nelems == 0 ) return PointerGetDatum ( construct_empty_array ( element_type ) ) ;
 dvalues = ( Datum * ) palloc ( nelems * sizeof ( Datum ) ) ;
 dnulls = ( bool * ) palloc ( nelems * sizeof ( bool ) ) ;
 foreach ( element , astate -> elements ) {
 ExprState * e = ( ExprState * ) lfirst ( element ) ;
 dvalues [ i ] = ExecEvalExpr ( e , econtext , & dnulls [ i ] , NULL ) ;
 i ++ ;
 }
 dims [ 0 ] = nelems ;
 lbs [ 0 ] = 1 ;
 result = construct_md_array ( dvalues , dnulls , ndims , dims , lbs , element_type , astate -> elemlength , astate -> elembyval , astate -> elemalign ) ;
 }
 else {
 int nbytes = 0 ;
 int nitems = 0 ;
 int outer_nelems = 0 ;
 int elem_ndims = 0 ;
 int * elem_dims = NULL ;
 int * elem_lbs = NULL ;
 bool firstone = true ;
 bool havenulls = false ;
 bool haveempty = false ;
 char * * subdata ;
 bits8 * * subbitmaps ;
 int * subbytes ;
 int * subnitems ;
 int i ;
 int32 dataoffset ;
 char * dat ;
 int iitem ;
 i = list_length ( astate -> elements ) ;
 subdata = ( char * * ) palloc ( i * sizeof ( char * ) ) ;
 subbitmaps = ( bits8 * * ) palloc ( i * sizeof ( bits8 * ) ) ;
 subbytes = ( int * ) palloc ( i * sizeof ( int ) ) ;
 subnitems = ( int * ) palloc ( i * sizeof ( int ) ) ;
 foreach ( element , astate -> elements ) {
 ExprState * e = ( ExprState * ) lfirst ( element ) ;
 bool eisnull ;
 Datum arraydatum ;
 ArrayType * array ;
 int this_ndims ;
 arraydatum = ExecEvalExpr ( e , econtext , & eisnull , NULL ) ;
 if ( eisnull ) {
 haveempty = true ;
 continue ;
 }
 array = DatumGetArrayTypeP ( arraydatum ) ;
 if ( element_type != ARR_ELEMTYPE ( array ) ) ereport ( ERROR , ( errcode ( ERRCODE_DATATYPE_MISMATCH ) , errmsg ( "cannot merge incompatible arrays" ) , errdetail ( "Array with element type %s cannot be " "included in ARRAY construct with element type %s." , format_type_be ( ARR_ELEMTYPE ( array ) ) , format_type_be ( element_type ) ) ) ) ;
 this_ndims = ARR_NDIM ( array ) ;
 if ( this_ndims <= 0 ) {
 haveempty = true ;
 continue ;
 }
 if ( firstone ) {
 elem_ndims = this_ndims ;
 ndims = elem_ndims + 1 ;
 if ( ndims <= 0 || ndims > MAXDIM ) ereport ( ERROR , ( errcode ( ERRCODE_PROGRAM_LIMIT_EXCEEDED ) , errmsg ( "number of array dimensions (%d) exceeds " \ "the maximum allowed (%d)" , ndims , MAXDIM ) ) ) ;
 elem_dims = ( int * ) palloc ( elem_ndims * sizeof ( int ) ) ;
 memcpy ( elem_dims , ARR_DIMS ( array ) , elem_ndims * sizeof ( int ) ) ;
 elem_lbs = ( int * ) palloc ( elem_ndims * sizeof ( int ) ) ;
 memcpy ( elem_lbs , ARR_LBOUND ( array ) , elem_ndims * sizeof ( int ) ) ;
 firstone = false ;
 }
 else {
 if ( elem_ndims != this_ndims || memcmp ( elem_dims , ARR_DIMS ( array ) , elem_ndims * sizeof ( int ) ) != 0 || memcmp ( elem_lbs , ARR_LBOUND ( array ) , elem_ndims * sizeof ( int ) ) != 0 ) ereport ( ERROR , ( errcode ( ERRCODE_ARRAY_SUBSCRIPT_ERROR ) , errmsg ( "multidimensional arrays must have array " "expressions with matching dimensions" ) ) ) ;
 }
 subdata [ outer_nelems ] = ARR_DATA_PTR ( array ) ;
 subbitmaps [ outer_nelems ] = ARR_NULLBITMAP ( array ) ;
 subbytes [ outer_nelems ] = ARR_SIZE ( array ) - ARR_DATA_OFFSET ( array ) ;
 nbytes += subbytes [ outer_nelems ] ;
 subnitems [ outer_nelems ] = ArrayGetNItems ( this_ndims , ARR_DIMS ( array ) ) ;
 nitems += subnitems [ outer_nelems ] ;
 havenulls |= ARR_HASNULL ( array ) ;
 outer_nelems ++ ;
 }
 if ( haveempty ) {
 if ( ndims == 0 ) return PointerGetDatum ( construct_empty_array ( element_type ) ) ;
 ereport ( ERROR , ( errcode ( ERRCODE_ARRAY_SUBSCRIPT_ERROR ) , errmsg ( "multidimensional arrays must have array " "expressions with matching dimensions" ) ) ) ;
 }
 dims [ 0 ] = outer_nelems ;
 lbs [ 0 ] = 1 ;
 for ( i = 1 ;
 i < ndims ;
 i ++ ) {
 dims [ i ] = elem_dims [ i - 1 ] ;
 lbs [ i ] = elem_lbs [ i - 1 ] ;
 }
 if ( havenulls ) {
 dataoffset = ARR_OVERHEAD_WITHNULLS ( ndims , nitems ) ;
 nbytes += dataoffset ;
 }
 else {
 dataoffset = 0 ;
 nbytes += ARR_OVERHEAD_NONULLS ( ndims ) ;
 }
 result = ( ArrayType * ) palloc ( nbytes ) ;
 SET_VARSIZE ( result , nbytes ) ;
 result -> ndim = ndims ;
 result -> dataoffset = dataoffset ;
 result -> elemtype = element_type ;
 memcpy ( ARR_DIMS ( result ) , dims , ndims * sizeof ( int ) ) ;
 memcpy ( ARR_LBOUND ( result ) , lbs , ndims * sizeof ( int ) ) ;
 dat = ARR_DATA_PTR ( result ) ;
 iitem = 0 ;
 for ( i = 0 ;
 i < outer_nelems ;
 i ++ ) {
 memcpy ( dat , subdata [ i ] , subbytes [ i ] ) ;
 dat += subbytes [ i ] ;
 if ( havenulls ) array_bitmap_copy ( ARR_NULLBITMAP ( result ) , iitem , subbitmaps [ i ] , 0 , subnitems [ i ] ) ;
 iitem += subnitems [ i ] ;
 }
 }
 return PointerGetDatum ( result ) ;
 }