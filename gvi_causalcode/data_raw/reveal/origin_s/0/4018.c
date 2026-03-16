static FILE * checkdupstoredtable ( SplineFont * sf , uint32 tag , int * len , struct alltabs * all , int me ) {
 int i ;
 struct ttf_table * tab = SFFindTable ( sf , tag ) , * test ;
 if ( tab == NULL ) {
 * len = 0 ;
 return ( NULL ) ;
 }
 for ( i = 0 ;
 i < me ;
 ++ i ) {
 test = SFFindTable ( all [ i ] . sf , tag ) ;
 if ( test != NULL && test -> len == tab -> len && memcmp ( test -> data , tab -> data , tab -> len ) == 0 ) {
 * len = i ;
 return ( ( FILE * ) ( intpt ) - 1 ) ;
 }
 }
 return ( dumpstoredtable ( sf , tag , len ) ) ;
 }