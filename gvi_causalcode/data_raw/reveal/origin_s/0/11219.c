inline void SetDeviceCapabilityState ( GLenum cap , bool enable ) {
 switch ( cap ) {
 case GL_BLEND : if ( enable_flags . cached_blend == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_blend = enable ;
 break ;
 case GL_CULL_FACE : if ( enable_flags . cached_cull_face == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_cull_face = enable ;
 break ;
 case GL_DEPTH_TEST : if ( enable_flags . cached_depth_test == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_depth_test = enable ;
 break ;
 case GL_DITHER : if ( enable_flags . cached_dither == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_dither = enable ;
 break ;
 case GL_POLYGON_OFFSET_FILL : if ( enable_flags . cached_polygon_offset_fill == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_polygon_offset_fill = enable ;
 break ;
 case GL_SAMPLE_ALPHA_TO_COVERAGE : if ( enable_flags . cached_sample_alpha_to_coverage == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_sample_alpha_to_coverage = enable ;
 break ;
 case GL_SAMPLE_COVERAGE : if ( enable_flags . cached_sample_coverage == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_sample_coverage = enable ;
 break ;
 case GL_SCISSOR_TEST : if ( enable_flags . cached_scissor_test == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_scissor_test = enable ;
 break ;
 case GL_STENCIL_TEST : if ( enable_flags . cached_stencil_test == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_stencil_test = enable ;
 break ;
 case GL_RASTERIZER_DISCARD : if ( enable_flags . cached_rasterizer_discard == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_rasterizer_discard = enable ;
 break ;
 case GL_PRIMITIVE_RESTART_FIXED_INDEX : if ( enable_flags . cached_primitive_restart_fixed_index == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_primitive_restart_fixed_index = enable ;
 break ;
 case GL_MULTISAMPLE_EXT : if ( enable_flags . cached_multisample_ext == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_multisample_ext = enable ;
 break ;
 case GL_SAMPLE_ALPHA_TO_ONE_EXT : if ( enable_flags . cached_sample_alpha_to_one_ext == enable && ! ignore_cached_state ) return ;
 enable_flags . cached_sample_alpha_to_one_ext = enable ;
 break ;
 default : NOTREACHED ( ) ;
 return ;
 }
 if ( enable ) glEnable ( cap ) ;
 else glDisable ( cap ) ;
 }