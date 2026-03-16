static Int decUnitCompare ( const Unit * a , Int alength , const Unit * b , Int blength , Int exp ) {
 Unit * acc ;
 Unit accbuff [ SD2U ( DECBUFFER * 2 + 1 ) ] ;
 Unit * allocacc = NULL ;
 Int accunits , need ;
 const Unit * l , * r , * u ;
 Int expunits , exprem , result ;
 if ( exp == 0 ) {
 if ( alength > blength ) return 1 ;
 if ( alength < blength ) return - 1 ;
 l = a + alength - 1 ;
 r = b + alength - 1 ;
 for ( ;
 l >= a ;
 l -- , r -- ) {
 if ( * l > * r ) return 1 ;
 if ( * l < * r ) return - 1 ;
 }
 return 0 ;
 }
 if ( alength > blength + ( Int ) D2U ( exp ) ) return 1 ;
 if ( alength + 1 < blength + ( Int ) D2U ( exp ) ) return - 1 ;
 need = blength + D2U ( exp ) ;
 if ( need < alength ) need = alength ;
 need += 2 ;
 acc = accbuff ;
 if ( need * sizeof ( Unit ) > sizeof ( accbuff ) ) {
 allocacc = ( Unit * ) malloc ( need * sizeof ( Unit ) ) ;
 if ( allocacc == NULL ) return BADINT ;
 acc = allocacc ;
 }
 expunits = exp / DECDPUN ;
 exprem = exp % DECDPUN ;
 accunits = decUnitAddSub ( a , alength , b , blength , expunits , acc , - ( Int ) powers [ exprem ] ) ;
 if ( accunits < 0 ) result = - 1 ;
 else {
 for ( u = acc ;
 u < acc + accunits - 1 && * u == 0 ;
 ) u ++ ;
 result = ( * u == 0 ? 0 : + 1 ) ;
 }
 if ( allocacc != NULL ) free ( allocacc ) ;
 return result ;
 }