static int xmlHashGrow ( xmlHashTablePtr table , int size ) {
 unsigned long key ;
 int oldsize , i ;
 xmlHashEntryPtr iter , next ;
 struct _xmlHashEntry * oldtable ;


 if ( size < 8 ) return ( - 1 ) ;
 if ( size > 8 * 2048 ) return ( - 1 ) ;
 oldsize = table -> size ;
 oldtable = table -> table ;
 if ( oldtable == NULL ) return ( - 1 ) ;
 table -> table = xmlMalloc ( size * sizeof ( xmlHashEntry ) ) ;
 if ( table -> table == NULL ) {
 table -> table = oldtable ;
 return ( - 1 ) ;
 }
 memset ( table -> table , 0 , size * sizeof ( xmlHashEntry ) ) ;
 table -> size = size ;
 for ( i = 0 ;
 i < oldsize ;
 i ++ ) {
 if ( oldtable [ i ] . valid == 0 ) continue ;
 key = xmlHashComputeKey ( table , oldtable [ i ] . name , oldtable [ i ] . name2 , oldtable [ i ] . name3 ) ;
 memcpy ( & ( table -> table [ key ] ) , & ( oldtable [ i ] ) , sizeof ( xmlHashEntry ) ) ;
 table -> table [ key ] . next = NULL ;
 }
 for ( i = 0 ;
 i < oldsize ;
 i ++ ) {
 iter = oldtable [ i ] . next ;
 while ( iter ) {
 next = iter -> next ;
 key = xmlHashComputeKey ( table , iter -> name , iter -> name2 , iter -> name3 ) ;
 if ( table -> table [ key ] . valid == 0 ) {
 memcpy ( & ( table -> table [ key ] ) , iter , sizeof ( xmlHashEntry ) ) ;
 table -> table [ key ] . next = NULL ;
 xmlFree ( iter ) ;
 }
 else {
 iter -> next = table -> table [ key ] . next ;
 table -> table [ key ] . next = iter ;
 }


 }
 }
 xmlFree ( oldtable ) ;


 }