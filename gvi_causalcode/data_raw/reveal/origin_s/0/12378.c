void get_agg_clause_costs ( PlannerInfo * root , Node * clause , AggSplit aggsplit , AggClauseCosts * costs ) {
 get_agg_clause_costs_context context ;
 context . root = root ;
 context . aggsplit = aggsplit ;
 context . costs = costs ;
 ( void ) get_agg_clause_costs_walker ( clause , & context ) ;
 }