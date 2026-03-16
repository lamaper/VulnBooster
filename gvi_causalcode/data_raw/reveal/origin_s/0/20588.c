void do_block ( enum block_cmd cmd , struct st_command * command ) {
 char * p = command -> first_argument ;
 const char * expr_start , * expr_end ;
 VAR v ;
 const char * cmd_name = ( cmd == cmd_while ? "while" : "if" ) ;
 my_bool not_expr = FALSE ;
 DBUG_ENTER ( "do_block" ) ;
 DBUG_PRINT ( "enter" , ( "%s" , cmd_name ) ) ;
 if ( cur_block == block_stack_end ) die ( "Nesting too deeply" ) ;
 cur_block -> line = parser . current_line ++ ;
 if ( ! cur_block -> ok ) {
 cur_block ++ ;
 cur_block -> cmd = cmd ;
 cur_block -> ok = FALSE ;
 cur_block -> delim [ 0 ] = '\0' ;
 DBUG_VOID_RETURN ;
 }
 expr_start = strchr ( p , '(' ) ;
 if ( ! expr_start ++ ) die ( "missing '(' in %s" , cmd_name ) ;
 while ( my_isspace ( charset_info , * expr_start ) ) expr_start ++ ;
 if ( * expr_start == '!' ) {
 not_expr = TRUE ;
 expr_start ++ ;
 while ( * expr_start && my_isspace ( charset_info , * expr_start ) ) expr_start ++ ;
 }
 expr_end = strrchr ( expr_start , ')' ) ;
 if ( ! expr_end ) die ( "missing ')' in %s" , cmd_name ) ;
 p = ( char * ) expr_end + 1 ;
 while ( * p && my_isspace ( charset_info , * p ) ) p ++ ;
 if ( * p && * p != '{
' ) die ( "Missing '{
' after %s. Found \"%s\"" , cmd_name , p ) ;
 var_init ( & v , 0 , 0 , 0 , 0 ) ;
 if ( * expr_start == '$' ) {
 const char * curr_ptr = expr_end ;
 eval_expr ( & v , expr_start , & curr_ptr , true ) ;
 while ( my_isspace ( charset_info , * ++ curr_ptr ) ) {
 }
 if ( curr_ptr == expr_end ) goto NO_COMPARE ;
 enum block_op operand = find_operand ( curr_ptr ) ;
 if ( operand == ILLEG_OP ) die ( "Found junk '%.*s' after $variable in condition" , ( int ) ( expr_end - curr_ptr ) , curr_ptr ) ;
 if ( not_expr ) die ( "Negation and comparison should not be combined, please rewrite" ) ;
 if ( operand == LT_OP || operand == GT_OP ) {
 curr_ptr ++ ;
 }
 else {
 curr_ptr += 2 ;
 }
 while ( my_isspace ( charset_info , * curr_ptr ) ) curr_ptr ++ ;
 if ( curr_ptr == expr_end ) die ( "Missing right operand in comparison" ) ;
 while ( my_isspace ( charset_info , expr_end [ - 1 ] ) ) expr_end -- ;
 if ( * curr_ptr == '\'' || * curr_ptr == '"' ) {
 if ( expr_end [ - 1 ] != * curr_ptr ) die ( "Unterminated string value" ) ;
 curr_ptr ++ ;
 expr_end -- ;
 }
 VAR v2 ;
 var_init ( & v2 , 0 , 0 , 0 , 0 ) ;
 eval_expr ( & v2 , curr_ptr , & expr_end ) ;
 if ( ( operand != EQ_OP && operand != NE_OP ) && ! ( v . is_int && v2 . is_int ) ) die ( "Only == and != are supported for string values" ) ;
 switch ( operand ) {
 case EQ_OP : if ( v . is_int ) v . int_val = ( v2 . is_int && v2 . int_val == v . int_val ) ;
 else v . int_val = ! strcmp ( v . str_val , v2 . str_val ) ;
 break ;
 case NE_OP : if ( v . is_int ) v . int_val = ! ( v2 . is_int && v2 . int_val == v . int_val ) ;
 else v . int_val = ( strcmp ( v . str_val , v2 . str_val ) != 0 ) ;
 break ;
 case LT_OP : v . int_val = ( v . int_val < v2 . int_val ) ;
 break ;
 case LE_OP : v . int_val = ( v . int_val <= v2 . int_val ) ;
 break ;
 case GT_OP : v . int_val = ( v . int_val > v2 . int_val ) ;
 break ;
 case GE_OP : v . int_val = ( v . int_val >= v2 . int_val ) ;
 break ;
 case ILLEG_OP : die ( "Impossible operator, this cannot happen" ) ;
 }
 v . is_int = TRUE ;
 var_free ( & v2 ) ;
 }
 else {
 if ( * expr_start != '`' && ! my_isdigit ( charset_info , * expr_start ) ) die ( "Expression in if/while must beging with $, ` or a number" ) ;
 eval_expr ( & v , expr_start , & expr_end ) ;
 }
 NO_COMPARE : cur_block ++ ;
 cur_block -> cmd = cmd ;
 if ( v . is_int ) {
 cur_block -> ok = ( v . int_val != 0 ) ;
 }
 else {
 p = v . str_val ;
 while ( * p && ( ( my_isspace ( charset_info , * p ) || * p == '-' || * p == '+' ) ) ) p ++ ;
 cur_block -> ok = ( * p && * p != '0' ) ? TRUE : FALSE ;
 }
 if ( not_expr ) cur_block -> ok = ! cur_block -> ok ;
 if ( cur_block -> ok ) {
 cur_block -> delim [ 0 ] = '\0' ;
 }
 else {
 strcpy ( cur_block -> delim , delimiter ) ;
 }
 DBUG_PRINT ( "info" , ( "OK: %d" , cur_block -> ok ) ) ;
 var_free ( & v ) ;
 DBUG_VOID_RETURN ;
 }