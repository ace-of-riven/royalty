#include <assert.h>
#include <stdio.h>

#include "../../console.h"

#include "../gpu_init.h"
#include "../gpu_backend.h"

static bool initialized = false;

static void GPU_is_ok ( const char *val , bool is_ok );

#if 1
#define EXTENSION_TO_ARG(i)		GPU_is_ok(#i ,(i))
#else
#define EXTENSION_TO_ARG(i)		(void)i
#endif

BOOL wglSwapIntervalEXT ( int i ) {
	typedef BOOL ( APIENTRY *PFNWGLSWAPINTERVALPROC )( int );
	return ( ( PFNWGLSWAPINTERVALPROC ) wglGetProcAddress ( "wglSwapIntervalEXT" ) ) ( i );
}

bool GPU_init ( void ) {
	if ( initialized ) {
		return true;
	}

	GLenum err = glewInit ( );

	if ( GLEW_OK != err ) {
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf ( stderr , "GLEW Error: %s\n" , glewGetErrorString ( err ) );
		return false;
	}

	fprintf ( stdout , "Using GLEW %s\n" , glewGetString ( GLEW_VERSION ) );

	GPU_platform_init ( ) ;

	printf ( "\n" );
	EXTENSION_TO_ARG ( GL_EXT_422_pixels );
	EXTENSION_TO_ARG ( GL_EXT_Cg_shader );
	EXTENSION_TO_ARG ( GL_EXT_EGL_image_array );
	EXTENSION_TO_ARG ( GL_EXT_YUV_target );
	EXTENSION_TO_ARG ( GL_EXT_abgr );
	EXTENSION_TO_ARG ( GL_EXT_base_instance );
	EXTENSION_TO_ARG ( GL_EXT_bgra );
	EXTENSION_TO_ARG ( GL_EXT_bindable_uniform );
	EXTENSION_TO_ARG ( GL_EXT_blend_color );
	EXTENSION_TO_ARG ( GL_EXT_blend_equation_separate );
	EXTENSION_TO_ARG ( GL_EXT_blend_func_extended );
	EXTENSION_TO_ARG ( GL_EXT_blend_func_separate );
	EXTENSION_TO_ARG ( GL_EXT_blend_logic_op );
	EXTENSION_TO_ARG ( GL_EXT_blend_minmax );
	EXTENSION_TO_ARG ( GL_EXT_blend_subtract );
	EXTENSION_TO_ARG ( GL_EXT_buffer_storage );
	EXTENSION_TO_ARG ( GL_EXT_clear_texture );
	EXTENSION_TO_ARG ( GL_EXT_clip_cull_distance );
	EXTENSION_TO_ARG ( GL_EXT_clip_volume_hint );
	EXTENSION_TO_ARG ( GL_EXT_cmyka );
	EXTENSION_TO_ARG ( GL_EXT_color_buffer_float );
	EXTENSION_TO_ARG ( GL_EXT_color_buffer_half_float );
	EXTENSION_TO_ARG ( GL_EXT_color_subtable );
	EXTENSION_TO_ARG ( GL_EXT_compiled_vertex_array );
	EXTENSION_TO_ARG ( GL_EXT_compressed_ETC1_RGB8_sub_texture );
	EXTENSION_TO_ARG ( GL_EXT_conservative_depth );
	EXTENSION_TO_ARG ( GL_EXT_convolution );
	EXTENSION_TO_ARG ( GL_EXT_coordinate_frame );
	EXTENSION_TO_ARG ( GL_EXT_copy_image );
	EXTENSION_TO_ARG ( GL_EXT_copy_texture );
	EXTENSION_TO_ARG ( GL_EXT_cull_vertex );
	EXTENSION_TO_ARG ( GL_EXT_debug_label );
	EXTENSION_TO_ARG ( GL_EXT_debug_marker );
	EXTENSION_TO_ARG ( GL_EXT_depth_bounds_test );
	EXTENSION_TO_ARG ( GL_EXT_direct_state_access );
	EXTENSION_TO_ARG ( GL_EXT_discard_framebuffer );
	EXTENSION_TO_ARG ( GL_EXT_draw_buffers );
	EXTENSION_TO_ARG ( GL_EXT_draw_buffers2 );
	EXTENSION_TO_ARG ( GL_EXT_draw_buffers_indexed );
	EXTENSION_TO_ARG ( GL_EXT_draw_elements_base_vertex );
	EXTENSION_TO_ARG ( GL_EXT_draw_instanced );
	EXTENSION_TO_ARG ( GL_EXT_draw_range_elements );
	EXTENSION_TO_ARG ( GL_EXT_external_buffer );
	EXTENSION_TO_ARG ( GL_EXT_float_blend );
	EXTENSION_TO_ARG ( GL_EXT_fog_coord );
	EXTENSION_TO_ARG ( GL_EXT_frag_depth );
	EXTENSION_TO_ARG ( GL_EXT_fragment_lighting );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_blit );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_multisample );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_multisample_blit_scaled );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_object );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_sRGB );
	EXTENSION_TO_ARG ( GL_EXT_geometry_point_size );
	EXTENSION_TO_ARG ( GL_EXT_geometry_shader );
	EXTENSION_TO_ARG ( GL_EXT_geometry_shader4 );
	EXTENSION_TO_ARG ( GL_EXT_gpu_program_parameters );
	EXTENSION_TO_ARG ( GL_EXT_gpu_shader4 );
	EXTENSION_TO_ARG ( GL_EXT_gpu_shader5 );
	EXTENSION_TO_ARG ( GL_EXT_histogram );
	EXTENSION_TO_ARG ( GL_EXT_index_array_formats );
	EXTENSION_TO_ARG ( GL_EXT_index_func );
	EXTENSION_TO_ARG ( GL_EXT_index_material );
	EXTENSION_TO_ARG ( GL_EXT_index_texture );
	EXTENSION_TO_ARG ( GL_EXT_instanced_arrays );
	EXTENSION_TO_ARG ( GL_EXT_light_texture );
	EXTENSION_TO_ARG ( GL_EXT_map_buffer_range );
	EXTENSION_TO_ARG ( GL_EXT_memory_object );
	EXTENSION_TO_ARG ( GL_EXT_memory_object_fd );
	EXTENSION_TO_ARG ( GL_EXT_memory_object_win32 );
	EXTENSION_TO_ARG ( GL_EXT_misc_attribute );
	EXTENSION_TO_ARG ( GL_EXT_multi_draw_arrays );
	EXTENSION_TO_ARG ( GL_EXT_multi_draw_indirect );
	EXTENSION_TO_ARG ( GL_EXT_multiple_textures );
	EXTENSION_TO_ARG ( GL_EXT_multisample );
	EXTENSION_TO_ARG ( GL_EXT_multisample_compatibility );
	EXTENSION_TO_ARG ( GL_EXT_multisampled_render_to_texture );
	EXTENSION_TO_ARG ( GL_EXT_multisampled_render_to_texture2 );
	EXTENSION_TO_ARG ( GL_EXT_multiview_draw_buffers );
	EXTENSION_TO_ARG ( GL_EXT_packed_depth_stencil );
	EXTENSION_TO_ARG ( GL_EXT_packed_float );
	EXTENSION_TO_ARG ( GL_EXT_packed_pixels );
	EXTENSION_TO_ARG ( GL_EXT_paletted_texture );
	EXTENSION_TO_ARG ( GL_EXT_pixel_buffer_object );
	EXTENSION_TO_ARG ( GL_EXT_pixel_transform );
	EXTENSION_TO_ARG ( GL_EXT_pixel_transform_color_table );
	EXTENSION_TO_ARG ( GL_EXT_point_parameters );
	EXTENSION_TO_ARG ( GL_EXT_polygon_offset );
	EXTENSION_TO_ARG ( GL_EXT_polygon_offset_clamp );
	EXTENSION_TO_ARG ( GL_EXT_post_depth_coverage );
	EXTENSION_TO_ARG ( GL_EXT_provoking_vertex );
	EXTENSION_TO_ARG ( GL_EXT_pvrtc_sRGB );
	EXTENSION_TO_ARG ( GL_EXT_raster_multisample );
	EXTENSION_TO_ARG ( GL_EXT_read_format_bgra );
	EXTENSION_TO_ARG ( GL_EXT_render_snorm );
	EXTENSION_TO_ARG ( GL_EXT_rescale_normal );
	EXTENSION_TO_ARG ( GL_EXT_sRGB );
	EXTENSION_TO_ARG ( GL_EXT_sRGB_write_control );
	EXTENSION_TO_ARG ( GL_EXT_scene_marker );
	EXTENSION_TO_ARG ( GL_EXT_secondary_color );
	EXTENSION_TO_ARG ( GL_EXT_semaphore );
	EXTENSION_TO_ARG ( GL_EXT_semaphore_fd );
	EXTENSION_TO_ARG ( GL_EXT_semaphore_win32 );
	EXTENSION_TO_ARG ( GL_EXT_separate_shader_objects );
	EXTENSION_TO_ARG ( GL_EXT_separate_specular_color );
	EXTENSION_TO_ARG ( GL_EXT_shader_framebuffer_fetch );
	EXTENSION_TO_ARG ( GL_EXT_shader_group_vote );
	EXTENSION_TO_ARG ( GL_EXT_shader_image_load_formatted );
	EXTENSION_TO_ARG ( GL_EXT_shader_image_load_store );
	EXTENSION_TO_ARG ( GL_EXT_shader_implicit_conversions );
	EXTENSION_TO_ARG ( GL_EXT_shader_integer_mix );
	EXTENSION_TO_ARG ( GL_EXT_shader_io_blocks );
	EXTENSION_TO_ARG ( GL_EXT_shader_non_constant_global_initializers );
	EXTENSION_TO_ARG ( GL_EXT_shader_pixel_local_storage );
	EXTENSION_TO_ARG ( GL_EXT_shader_pixel_local_storage2 );
	EXTENSION_TO_ARG ( GL_EXT_shader_texture_lod );
	EXTENSION_TO_ARG ( GL_EXT_shadow_funcs );
	EXTENSION_TO_ARG ( GL_EXT_shadow_samplers );
	EXTENSION_TO_ARG ( GL_EXT_shared_texture_palette );
	EXTENSION_TO_ARG ( GL_EXT_sparse_texture );
	EXTENSION_TO_ARG ( GL_EXT_sparse_texture2 );
	EXTENSION_TO_ARG ( GL_EXT_stencil_clear_tag );
	EXTENSION_TO_ARG ( GL_EXT_stencil_two_side );
	EXTENSION_TO_ARG ( GL_EXT_stencil_wrap );
	EXTENSION_TO_ARG ( GL_EXT_subtexture );
	EXTENSION_TO_ARG ( GL_EXT_texture );
	EXTENSION_TO_ARG ( GL_EXT_texture3D );
	EXTENSION_TO_ARG ( GL_EXT_texture_array );
	EXTENSION_TO_ARG ( GL_EXT_texture_buffer_object );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_astc_decode_mode );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_bptc );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_dxt1 );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_latc );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_rgtc );
	EXTENSION_TO_ARG ( GL_EXT_texture_compression_s3tc );
	EXTENSION_TO_ARG ( GL_EXT_texture_cube_map );
	EXTENSION_TO_ARG ( GL_EXT_texture_cube_map_array );
	EXTENSION_TO_ARG ( GL_EXT_texture_edge_clamp );
	EXTENSION_TO_ARG ( GL_EXT_texture_env );
	EXTENSION_TO_ARG ( GL_EXT_texture_env_add );
	EXTENSION_TO_ARG ( GL_EXT_texture_env_combine );
	EXTENSION_TO_ARG ( GL_EXT_texture_env_dot3 );
	EXTENSION_TO_ARG ( GL_EXT_texture_filter_anisotropic );
	EXTENSION_TO_ARG ( GL_EXT_texture_filter_minmax );
	EXTENSION_TO_ARG ( GL_EXT_texture_format_BGRA8888 );
	EXTENSION_TO_ARG ( GL_EXT_texture_integer );
	EXTENSION_TO_ARG ( GL_EXT_texture_lod_bias );
	EXTENSION_TO_ARG ( GL_EXT_texture_mirror_clamp );
	EXTENSION_TO_ARG ( GL_EXT_texture_norm16 );
	EXTENSION_TO_ARG ( GL_EXT_texture_object );
	EXTENSION_TO_ARG ( GL_EXT_texture_perturb_normal );
	EXTENSION_TO_ARG ( GL_EXT_texture_rectangle );
	EXTENSION_TO_ARG ( GL_EXT_texture_rg );
	EXTENSION_TO_ARG ( GL_EXT_texture_sRGB );
	EXTENSION_TO_ARG ( GL_EXT_texture_sRGB_R8 );
	EXTENSION_TO_ARG ( GL_EXT_texture_sRGB_RG8 );
	EXTENSION_TO_ARG ( GL_EXT_texture_sRGB_decode );
	EXTENSION_TO_ARG ( GL_EXT_texture_shared_exponent );
	EXTENSION_TO_ARG ( GL_EXT_texture_snorm );
	EXTENSION_TO_ARG ( GL_EXT_texture_storage );
	EXTENSION_TO_ARG ( GL_EXT_texture_swizzle );
	EXTENSION_TO_ARG ( GL_EXT_texture_type_2_10_10_10_REV );
	EXTENSION_TO_ARG ( GL_EXT_texture_view );
	EXTENSION_TO_ARG ( GL_EXT_timer_query );
	EXTENSION_TO_ARG ( GL_EXT_transform_feedback );
	EXTENSION_TO_ARG ( GL_EXT_unpack_subimage );
	EXTENSION_TO_ARG ( GL_EXT_vertex_array );
	EXTENSION_TO_ARG ( GL_EXT_vertex_array_bgra );
	EXTENSION_TO_ARG ( GL_EXT_vertex_array_setXXX );
	EXTENSION_TO_ARG ( GL_EXT_vertex_attrib_64bit );
	EXTENSION_TO_ARG ( GL_EXT_vertex_shader );
	EXTENSION_TO_ARG ( GL_EXT_vertex_weighting );
	EXTENSION_TO_ARG ( GL_EXT_win32_keyed_mutex );
	EXTENSION_TO_ARG ( GL_EXT_window_rectangles );
	EXTENSION_TO_ARG ( GL_EXT_x11_sync_object );
	printf ( "\n" ) ;

	EXTENSION_TO_ARG ( GL_KHR_blend_equation_advanced );
	EXTENSION_TO_ARG ( GL_KHR_blend_equation_advanced_coherent );
	EXTENSION_TO_ARG ( GL_KHR_context_flush_control );
	EXTENSION_TO_ARG ( GL_KHR_debug );
	EXTENSION_TO_ARG ( GL_KHR_no_error );
	EXTENSION_TO_ARG ( GL_KHR_parallel_shader_compile );
	EXTENSION_TO_ARG ( GL_KHR_robust_buffer_access_behavior );
	EXTENSION_TO_ARG ( GL_KHR_robustness );
	EXTENSION_TO_ARG ( GL_KHR_texture_compression_astc_hdr );
	EXTENSION_TO_ARG ( GL_KHR_texture_compression_astc_ldr );
	EXTENSION_TO_ARG ( GL_KHR_texture_compression_astc_sliced_3d );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_NV_3dvision_settings );
	EXTENSION_TO_ARG ( GL_NV_EGL_stream_consumer_external );
	EXTENSION_TO_ARG ( GL_NV_alpha_to_coverage_dither_control );
	EXTENSION_TO_ARG ( GL_NV_bgr );
	EXTENSION_TO_ARG ( GL_NV_bindless_multi_draw_indirect );
	EXTENSION_TO_ARG ( GL_NV_bindless_multi_draw_indirect_count );
	EXTENSION_TO_ARG ( GL_NV_bindless_texture );
	EXTENSION_TO_ARG ( GL_NV_blend_equation_advanced );
	EXTENSION_TO_ARG ( GL_NV_blend_equation_advanced_coherent );
	EXTENSION_TO_ARG ( GL_NV_blend_minmax_factor );
	EXTENSION_TO_ARG ( GL_NV_blend_square );
	EXTENSION_TO_ARG ( GL_NV_clip_space_w_scaling );
	EXTENSION_TO_ARG ( GL_NV_command_list );
	EXTENSION_TO_ARG ( GL_NV_compute_program5 );
	EXTENSION_TO_ARG ( GL_NV_conditional_render );
	EXTENSION_TO_ARG ( GL_NV_conservative_raster );
	EXTENSION_TO_ARG ( GL_NV_conservative_raster_dilate );
	EXTENSION_TO_ARG ( GL_NV_conservative_raster_pre_snap_triangles );
	EXTENSION_TO_ARG ( GL_NV_copy_buffer );
	EXTENSION_TO_ARG ( GL_NV_copy_depth_to_color );
	EXTENSION_TO_ARG ( GL_NV_copy_image );
	EXTENSION_TO_ARG ( GL_NV_deep_texture3D );
	EXTENSION_TO_ARG ( GL_NV_depth_buffer_float );
	EXTENSION_TO_ARG ( GL_NV_depth_clamp );
	EXTENSION_TO_ARG ( GL_NV_depth_range_unclamped );
	EXTENSION_TO_ARG ( GL_NV_draw_buffers );
	EXTENSION_TO_ARG ( GL_NV_draw_instanced );
	EXTENSION_TO_ARG ( GL_NV_draw_texture );
	EXTENSION_TO_ARG ( GL_NV_draw_vulkan_image );
	EXTENSION_TO_ARG ( GL_NV_evaluators );
	EXTENSION_TO_ARG ( GL_NV_explicit_attrib_location );
	EXTENSION_TO_ARG ( GL_NV_explicit_multisample );
	EXTENSION_TO_ARG ( GL_NV_fbo_color_attachments );
	EXTENSION_TO_ARG ( GL_NV_fence );
	EXTENSION_TO_ARG ( GL_NV_fill_rectangle );
	EXTENSION_TO_ARG ( GL_NV_float_buffer );
	EXTENSION_TO_ARG ( GL_NV_fog_distance );
	EXTENSION_TO_ARG ( GL_NV_fragment_coverage_to_color );
	EXTENSION_TO_ARG ( GL_NV_fragment_program );
	EXTENSION_TO_ARG ( GL_NV_fragment_program2 );
	EXTENSION_TO_ARG ( GL_NV_fragment_program4 );
	EXTENSION_TO_ARG ( GL_NV_fragment_program_option );
	EXTENSION_TO_ARG ( GL_NV_fragment_shader_interlock );
	EXTENSION_TO_ARG ( GL_NV_framebuffer_blit );
	EXTENSION_TO_ARG ( GL_NV_framebuffer_mixed_samples );
	EXTENSION_TO_ARG ( GL_NV_framebuffer_multisample );
	EXTENSION_TO_ARG ( GL_NV_framebuffer_multisample_coverage );
	EXTENSION_TO_ARG ( GL_NV_generate_mipmap_sRGB );
	EXTENSION_TO_ARG ( GL_NV_geometry_program4 );
	EXTENSION_TO_ARG ( GL_NV_geometry_shader4 );
	EXTENSION_TO_ARG ( GL_NV_geometry_shader_passthrough );
	EXTENSION_TO_ARG ( GL_NV_gpu_multicast );
	EXTENSION_TO_ARG ( GL_NV_gpu_program4 );
	EXTENSION_TO_ARG ( GL_NV_gpu_program5 );
	EXTENSION_TO_ARG ( GL_NV_gpu_program5_mem_extended );
	EXTENSION_TO_ARG ( GL_NV_gpu_program_fp64 );
	EXTENSION_TO_ARG ( GL_NV_gpu_shader5 );
	EXTENSION_TO_ARG ( GL_NV_half_float );
	EXTENSION_TO_ARG ( GL_NV_image_formats );
	EXTENSION_TO_ARG ( GL_NV_instanced_arrays );
	EXTENSION_TO_ARG ( GL_NV_internalformat_sample_query );
	EXTENSION_TO_ARG ( GL_NV_light_max_exponent );
	EXTENSION_TO_ARG ( GL_NV_multisample_coverage );
	EXTENSION_TO_ARG ( GL_NV_multisample_filter_hint );
	EXTENSION_TO_ARG ( GL_NV_non_square_matrices );
	EXTENSION_TO_ARG ( GL_NV_occlusion_query );
	EXTENSION_TO_ARG ( GL_NV_pack_subimage );
	EXTENSION_TO_ARG ( GL_NV_packed_depth_stencil );
	EXTENSION_TO_ARG ( GL_NV_packed_float );
	EXTENSION_TO_ARG ( GL_NV_packed_float_linear );
	EXTENSION_TO_ARG ( GL_NV_parameter_buffer_object );
	EXTENSION_TO_ARG ( GL_NV_parameter_buffer_object2 );
	EXTENSION_TO_ARG ( GL_NV_path_rendering );
	EXTENSION_TO_ARG ( GL_NV_path_rendering_shared_edge );
	EXTENSION_TO_ARG ( GL_NV_pixel_buffer_object );
	EXTENSION_TO_ARG ( GL_NV_pixel_data_range );
	EXTENSION_TO_ARG ( GL_NV_platform_binary );
	EXTENSION_TO_ARG ( GL_NV_point_sprite );
	EXTENSION_TO_ARG ( GL_NV_polygon_mode );
	EXTENSION_TO_ARG ( GL_NV_present_video );
	EXTENSION_TO_ARG ( GL_NV_primitive_restart );
	EXTENSION_TO_ARG ( GL_NV_read_depth );
	EXTENSION_TO_ARG ( GL_NV_read_depth_stencil );
	EXTENSION_TO_ARG ( GL_NV_read_stencil );
	EXTENSION_TO_ARG ( GL_NV_register_combiners );
	EXTENSION_TO_ARG ( GL_NV_register_combiners2 );
	EXTENSION_TO_ARG ( GL_NV_robustness_video_memory_purge );
	EXTENSION_TO_ARG ( GL_NV_sRGB_formats );
	EXTENSION_TO_ARG ( GL_NV_sample_locations );
	EXTENSION_TO_ARG ( GL_NV_sample_mask_override_coverage );
	EXTENSION_TO_ARG ( GL_NV_shader_atomic_counters );
	EXTENSION_TO_ARG ( GL_NV_shader_atomic_float );
	EXTENSION_TO_ARG ( GL_NV_shader_atomic_float64 );
	EXTENSION_TO_ARG ( GL_NV_shader_atomic_fp16_vector );
	EXTENSION_TO_ARG ( GL_NV_shader_atomic_int64 );
	EXTENSION_TO_ARG ( GL_NV_shader_buffer_load );
	EXTENSION_TO_ARG ( GL_NV_shader_noperspective_interpolation );
	EXTENSION_TO_ARG ( GL_NV_shader_storage_buffer_object );
	EXTENSION_TO_ARG ( GL_NV_shader_thread_group );
	EXTENSION_TO_ARG ( GL_NV_shader_thread_shuffle );
	EXTENSION_TO_ARG ( GL_NV_shadow_samplers_array );
	EXTENSION_TO_ARG ( GL_NV_shadow_samplers_cube );
	EXTENSION_TO_ARG ( GL_NV_stereo_view_rendering );
	EXTENSION_TO_ARG ( GL_NV_tessellation_program5 );
	EXTENSION_TO_ARG ( GL_NV_texgen_emboss );
	EXTENSION_TO_ARG ( GL_NV_texgen_reflection );
	EXTENSION_TO_ARG ( GL_NV_texture_array );
	EXTENSION_TO_ARG ( GL_NV_texture_barrier );
	EXTENSION_TO_ARG ( GL_NV_texture_border_clamp );
	EXTENSION_TO_ARG ( GL_NV_texture_compression_latc );
	EXTENSION_TO_ARG ( GL_NV_texture_compression_s3tc );
	EXTENSION_TO_ARG ( GL_NV_texture_compression_s3tc_update );
	EXTENSION_TO_ARG ( GL_NV_texture_compression_vtc );
	EXTENSION_TO_ARG ( GL_NV_texture_env_combine4 );
	EXTENSION_TO_ARG ( GL_NV_texture_expand_normal );
	EXTENSION_TO_ARG ( GL_NV_texture_multisample );
	EXTENSION_TO_ARG ( GL_NV_texture_npot_2D_mipmap );
	EXTENSION_TO_ARG ( GL_NV_texture_rectangle );
	EXTENSION_TO_ARG ( GL_NV_texture_rectangle_compressed );
	EXTENSION_TO_ARG ( GL_NV_texture_shader );
	EXTENSION_TO_ARG ( GL_NV_texture_shader2 );
	EXTENSION_TO_ARG ( GL_NV_texture_shader3 );
	EXTENSION_TO_ARG ( GL_NV_transform_feedback );
	EXTENSION_TO_ARG ( GL_NV_transform_feedback2 );
	EXTENSION_TO_ARG ( GL_NV_uniform_buffer_unified_memory );
	EXTENSION_TO_ARG ( GL_NV_vdpau_interop );
	EXTENSION_TO_ARG ( GL_NV_vertex_array_range );
	EXTENSION_TO_ARG ( GL_NV_vertex_array_range2 );
	EXTENSION_TO_ARG ( GL_NV_vertex_attrib_integer_64bit );
	EXTENSION_TO_ARG ( GL_NV_vertex_buffer_unified_memory );
	EXTENSION_TO_ARG ( GL_NV_vertex_program );
	EXTENSION_TO_ARG ( GL_NV_vertex_program1_1 );
	EXTENSION_TO_ARG ( GL_NV_vertex_program2 );
	EXTENSION_TO_ARG ( GL_NV_vertex_program2_option );
	EXTENSION_TO_ARG ( GL_NV_vertex_program3 );
	EXTENSION_TO_ARG ( GL_NV_vertex_program4 );
	EXTENSION_TO_ARG ( GL_NV_video_capture );
	EXTENSION_TO_ARG ( GL_NV_viewport_array );
	EXTENSION_TO_ARG ( GL_NV_viewport_array2 );
	EXTENSION_TO_ARG ( GL_NV_viewport_swizzle );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_SGIS_clip_band_hint );
	EXTENSION_TO_ARG ( GL_SGIS_color_range );
	EXTENSION_TO_ARG ( GL_SGIS_detail_texture );
	EXTENSION_TO_ARG ( GL_SGIS_fog_function );
	EXTENSION_TO_ARG ( GL_SGIS_generate_mipmap );
	EXTENSION_TO_ARG ( GL_SGIS_line_texgen );
	EXTENSION_TO_ARG ( GL_SGIS_multisample );
	EXTENSION_TO_ARG ( GL_SGIS_multitexture );
	EXTENSION_TO_ARG ( GL_SGIS_pixel_texture );
	EXTENSION_TO_ARG ( GL_SGIS_point_line_texgen );
	EXTENSION_TO_ARG ( GL_SGIS_shared_multisample );
	EXTENSION_TO_ARG ( GL_SGIS_sharpen_texture );
	EXTENSION_TO_ARG ( GL_SGIS_texture4D );
	EXTENSION_TO_ARG ( GL_SGIS_texture_border_clamp );
	EXTENSION_TO_ARG ( GL_SGIS_texture_edge_clamp );
	EXTENSION_TO_ARG ( GL_SGIS_texture_filter4 );
	EXTENSION_TO_ARG ( GL_SGIS_texture_lod );
	EXTENSION_TO_ARG ( GL_SGIS_texture_select );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_SGIX_async );
	EXTENSION_TO_ARG ( GL_SGIX_async_histogram );
	EXTENSION_TO_ARG ( GL_SGIX_async_pixel );
	EXTENSION_TO_ARG ( GL_SGIX_bali_g_instruments );
	EXTENSION_TO_ARG ( GL_SGIX_bali_r_instruments );
	EXTENSION_TO_ARG ( GL_SGIX_bali_timer_instruments );
	EXTENSION_TO_ARG ( GL_SGIX_blend_alpha_minmax );
	EXTENSION_TO_ARG ( GL_SGIX_blend_cadd );
	EXTENSION_TO_ARG ( GL_SGIX_blend_cmultiply );
	EXTENSION_TO_ARG ( GL_SGIX_calligraphic_fragment );
	EXTENSION_TO_ARG ( GL_SGIX_clipmap );
	EXTENSION_TO_ARG ( GL_SGIX_color_matrix_accuracy );
	EXTENSION_TO_ARG ( GL_SGIX_color_table_index_mode );
	EXTENSION_TO_ARG ( GL_SGIX_complex_polar );
	EXTENSION_TO_ARG ( GL_SGIX_convolution_accuracy );
	EXTENSION_TO_ARG ( GL_SGIX_cube_map );
	EXTENSION_TO_ARG ( GL_SGIX_cylinder_texgen );
	EXTENSION_TO_ARG ( GL_SGIX_datapipe );
	EXTENSION_TO_ARG ( GL_SGIX_decimation );
	EXTENSION_TO_ARG ( GL_SGIX_depth_pass_instrument );
	EXTENSION_TO_ARG ( GL_SGIX_depth_texture );
	EXTENSION_TO_ARG ( GL_SGIX_dvc );
	EXTENSION_TO_ARG ( GL_SGIX_flush_raster );
	EXTENSION_TO_ARG ( GL_SGIX_fog_blend );
	EXTENSION_TO_ARG ( GL_SGIX_fog_factor_to_alpha );
	EXTENSION_TO_ARG ( GL_SGIX_fog_layers );
	EXTENSION_TO_ARG ( GL_SGIX_fog_offset );
	EXTENSION_TO_ARG ( GL_SGIX_fog_patchy );
	EXTENSION_TO_ARG ( GL_SGIX_fog_scale );
	EXTENSION_TO_ARG ( GL_SGIX_fog_texture );
	EXTENSION_TO_ARG ( GL_SGIX_fragment_lighting_space );
	EXTENSION_TO_ARG ( GL_SGIX_fragment_specular_lighting );
	EXTENSION_TO_ARG ( GL_SGIX_fragments_instrument );
	EXTENSION_TO_ARG ( GL_SGIX_framezoom );
	EXTENSION_TO_ARG ( GL_SGIX_icc_texture );
	EXTENSION_TO_ARG ( GL_SGIX_igloo_interface );
	EXTENSION_TO_ARG ( GL_SGIX_image_compression );
	EXTENSION_TO_ARG ( GL_SGIX_impact_pixel_texture );
	EXTENSION_TO_ARG ( GL_SGIX_instrument_error );
	EXTENSION_TO_ARG ( GL_SGIX_interlace );
	EXTENSION_TO_ARG ( GL_SGIX_ir_instrument1 );
	EXTENSION_TO_ARG ( GL_SGIX_line_quality_hint );
	EXTENSION_TO_ARG ( GL_SGIX_list_priority );
	EXTENSION_TO_ARG ( GL_SGIX_mpeg1 );
	EXTENSION_TO_ARG ( GL_SGIX_mpeg2 );
	EXTENSION_TO_ARG ( GL_SGIX_nonlinear_lighting_pervertex );
	EXTENSION_TO_ARG ( GL_SGIX_nurbs_eval );
	EXTENSION_TO_ARG ( GL_SGIX_occlusion_instrument );
	EXTENSION_TO_ARG ( GL_SGIX_packed_6bytes );
	EXTENSION_TO_ARG ( GL_SGIX_pixel_texture );
	EXTENSION_TO_ARG ( GL_SGIX_pixel_texture_bits );
	EXTENSION_TO_ARG ( GL_SGIX_pixel_texture_lod );
	EXTENSION_TO_ARG ( GL_SGIX_pixel_tiles );
	EXTENSION_TO_ARG ( GL_SGIX_polynomial_ffd );
	EXTENSION_TO_ARG ( GL_SGIX_quad_mesh );
	EXTENSION_TO_ARG ( GL_SGIX_reference_plane );
	EXTENSION_TO_ARG ( GL_SGIX_resample );
	EXTENSION_TO_ARG ( GL_SGIX_scalebias_hint );
	EXTENSION_TO_ARG ( GL_SGIX_shadow );
	EXTENSION_TO_ARG ( GL_SGIX_shadow_ambient );
	EXTENSION_TO_ARG ( GL_SGIX_slim );
	EXTENSION_TO_ARG ( GL_SGIX_spotlight_cutoff );
	EXTENSION_TO_ARG ( GL_SGIX_sprite );
	EXTENSION_TO_ARG ( GL_SGIX_subdiv_patch );
	EXTENSION_TO_ARG ( GL_SGIX_subsample );
	EXTENSION_TO_ARG ( GL_SGIX_tag_sample_buffer );
	EXTENSION_TO_ARG ( GL_SGIX_texture_add_env );
	EXTENSION_TO_ARG ( GL_SGIX_texture_coordinate_clamp );
	EXTENSION_TO_ARG ( GL_SGIX_texture_lod_bias );
	EXTENSION_TO_ARG ( GL_SGIX_texture_mipmap_anisotropic );
	EXTENSION_TO_ARG ( GL_SGIX_texture_multi_buffer );
	EXTENSION_TO_ARG ( GL_SGIX_texture_phase );
	EXTENSION_TO_ARG ( GL_SGIX_texture_range );
	EXTENSION_TO_ARG ( GL_SGIX_texture_scale_bias );
	EXTENSION_TO_ARG ( GL_SGIX_texture_supersample );
	EXTENSION_TO_ARG ( GL_SGIX_vector_ops );
	EXTENSION_TO_ARG ( GL_SGIX_vertex_array_object );
	EXTENSION_TO_ARG ( GL_SGIX_vertex_preclip );
	EXTENSION_TO_ARG ( GL_SGIX_vertex_preclip_hint );
	EXTENSION_TO_ARG ( GL_SGIX_ycrcb );
	EXTENSION_TO_ARG ( GL_SGIX_ycrcb_subsample );
	EXTENSION_TO_ARG ( GL_SGIX_ycrcba );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_ANDROID_extension_pack_es31a );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_AMD_blend_minmax_factor );
	EXTENSION_TO_ARG ( GL_AMD_compressed_3DC_texture );
	EXTENSION_TO_ARG ( GL_AMD_compressed_ATC_texture );
	EXTENSION_TO_ARG ( GL_AMD_conservative_depth );
	EXTENSION_TO_ARG ( GL_AMD_debug_output );
	EXTENSION_TO_ARG ( GL_AMD_depth_clamp_separate );
	EXTENSION_TO_ARG ( GL_AMD_draw_buffers_blend );
	EXTENSION_TO_ARG ( GL_AMD_framebuffer_sample_positions );
	EXTENSION_TO_ARG ( GL_AMD_gcn_shader );
	EXTENSION_TO_ARG ( GL_AMD_gpu_shader_half_float );
	EXTENSION_TO_ARG ( GL_AMD_gpu_shader_int16 );
	EXTENSION_TO_ARG ( GL_AMD_gpu_shader_int64 );
	EXTENSION_TO_ARG ( GL_AMD_interleaved_elements );
	EXTENSION_TO_ARG ( GL_AMD_multi_draw_indirect );
	EXTENSION_TO_ARG ( GL_AMD_name_gen_delete );
	EXTENSION_TO_ARG ( GL_AMD_occlusion_query_event );
	EXTENSION_TO_ARG ( GL_AMD_performance_monitor );
	EXTENSION_TO_ARG ( GL_AMD_pinned_memory );
	EXTENSION_TO_ARG ( GL_AMD_program_binary_Z400 );
	EXTENSION_TO_ARG ( GL_AMD_query_buffer_object );
	EXTENSION_TO_ARG ( GL_AMD_sample_positions );
	EXTENSION_TO_ARG ( GL_AMD_seamless_cubemap_per_texture );
	EXTENSION_TO_ARG ( GL_AMD_shader_atomic_counter_ops );
	EXTENSION_TO_ARG ( GL_AMD_shader_ballot );
	EXTENSION_TO_ARG ( GL_AMD_shader_explicit_vertex_parameter );
	EXTENSION_TO_ARG ( GL_AMD_shader_stencil_export );
	EXTENSION_TO_ARG ( GL_AMD_shader_stencil_value_export );
	EXTENSION_TO_ARG ( GL_AMD_shader_trinary_minmax );
	EXTENSION_TO_ARG ( GL_AMD_sparse_texture );
	EXTENSION_TO_ARG ( GL_AMD_stencil_operation_extended );
	EXTENSION_TO_ARG ( GL_AMD_texture_gather_bias_lod );
	EXTENSION_TO_ARG ( GL_AMD_texture_texture4 );
	EXTENSION_TO_ARG ( GL_AMD_transform_feedback3_lines_triangles );
	EXTENSION_TO_ARG ( GL_AMD_transform_feedback4 );
	EXTENSION_TO_ARG ( GL_AMD_vertex_shader_layer );
	EXTENSION_TO_ARG ( GL_AMD_vertex_shader_tessellator );
	EXTENSION_TO_ARG ( GL_AMD_vertex_shader_viewport_index );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_ARB_compressed_texture_pixel_storage );
	EXTENSION_TO_ARG ( GL_ARB_conservative_depth );
	EXTENSION_TO_ARG ( GL_ARB_ES2_compatibility );
	EXTENSION_TO_ARG ( GL_ARB_get_program_binary );
	EXTENSION_TO_ARG ( GL_ARB_explicit_uniform_location );
	EXTENSION_TO_ARG ( GL_ARB_internalformat_query );
	EXTENSION_TO_ARG ( GL_ARB_internalformat_query2 );
	EXTENSION_TO_ARG ( GL_ARB_map_buffer_alignment );
	EXTENSION_TO_ARG ( GL_ARB_program_interface_query );
	EXTENSION_TO_ARG ( GL_ARB_separate_shader_objects );
	EXTENSION_TO_ARG ( GL_ARB_shading_language_420pack );
	EXTENSION_TO_ARG ( GL_ARB_shading_language_packing );
	EXTENSION_TO_ARG ( GL_ARB_texture_buffer_range );
	EXTENSION_TO_ARG ( GL_ARB_texture_storage );
	EXTENSION_TO_ARG ( GL_ARB_texture_view );
	EXTENSION_TO_ARG ( GL_ARB_vertex_attrib_binding );
	EXTENSION_TO_ARG ( GL_ARB_viewport_array );
	EXTENSION_TO_ARG ( GL_NV_texture_barrier );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_ARB_transform_feedback2 );
	EXTENSION_TO_ARG ( GL_ARB_transform_feedback3 );
	EXTENSION_TO_ARG ( GL_ARB_texture_buffer_object_rgb32 );
	EXTENSION_TO_ARG ( GL_ARB_shader_precision );
	EXTENSION_TO_ARG ( GL_ARB_draw_buffers_blend );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_ARB_vertex_array_object );
	EXTENSION_TO_ARG ( GL_ARB_framebuffer_object );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_EXT_framebuffer_object );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_blit );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_multisample );
	EXTENSION_TO_ARG ( GL_EXT_packed_depth_stencil. );
	EXTENSION_TO_ARG ( GL_ARB_map_buffer_range );
	EXTENSION_TO_ARG ( GL_ARB_copy_buffer );
	EXTENSION_TO_ARG ( GL_ARB_texture_rectangle );
	EXTENSION_TO_ARG ( GL_ARB_color_buffer_float );
	EXTENSION_TO_ARG ( GL_ARB_half_float_pixel );
	EXTENSION_TO_ARG ( GL_ARB_sync );
	printf ( "\n" );

	EXTENSION_TO_ARG ( GL_ARB_texture_rg );
	EXTENSION_TO_ARG ( GL_ARB_texture_compression_rgtc );
	EXTENSION_TO_ARG ( GL_EXT_bindable_uniform );
	EXTENSION_TO_ARG ( GL_EXT_draw_buffers2 );
	EXTENSION_TO_ARG ( GL_EXT_geometry_shader4 );
	EXTENSION_TO_ARG ( GL_EXT_gpu_shader4 );
	EXTENSION_TO_ARG ( GL_EXT_framebuffer_sRGB );
	printf ( "\n" );

	return initialized = true;
}

void GPU_exit ( void ) {
	assert ( initialized );

	GPU_platform_exit ( );

	initialized = false;
}

bool GPU_is_init ( void ) {
	return initialized;
}

//

static void GPU_is_ok ( const char *val , bool is_ok ) {
	const unsigned int len = 8;
	char tabs [ len ];

	memset ( tabs , '\t' , len );

	tabs [ ( len - ( strlen ( val ) / 8 ) ) ] = 0;

	CONSOLE_printf_gpu_error ( eGPU_error_level::eGPU_error_information , "%s%s " , val , tabs );

	if ( is_ok ) {
		unsigned short col = CONSOLE_get_current_color ( );
		CONSOLE_change_color ( CONSOLE_TXT_COLOR::TXT_LIGHT_GREEN );
		fprintf ( stderr , "OK" );
		CONSOLE_change_color ( col );
	}
	else {
		unsigned short col = CONSOLE_get_current_color ( );
		CONSOLE_change_color ( CONSOLE_TXT_COLOR::TXT_DARK_RED );
		fprintf ( stdout , "ERROR" );
		CONSOLE_change_color ( col );
	}

	CONSOLE_printf_gpu_error ( eGPU_error_level::eGPU_error_information , "!\n" );
}
