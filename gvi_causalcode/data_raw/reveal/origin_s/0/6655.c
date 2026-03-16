Pattern_Prefix_Status pattern_fixed_prefix ( Const * patt , Pattern_Type ptype , Oid collation , Const * * prefix , Selectivity * rest_selec ) {
 Pattern_Prefix_Status result ;
 switch ( ptype ) {
 case Pattern_Type_Like : result = like_fixed_prefix ( patt , false , collation , prefix , rest_selec ) ;
 break ;
 case Pattern_Type_Like_IC : result = like_fixed_prefix ( patt , true , collation , prefix , rest_selec ) ;
 break ;
 case Pattern_Type_Regex : result = regex_fixed_prefix ( patt , false , collation , prefix , rest_selec ) ;
 break ;
 case Pattern_Type_Regex_IC : result = regex_fixed_prefix ( patt , true , collation , prefix , rest_selec ) ;
 break ;
 default : elog ( ERROR , "unrecognized ptype: %d" , ( int ) ptype ) ;
 result = Pattern_Prefix_None ;
 break ;
 }
 return result ;
 }