#pragma once

#include "ext_include.h"

#include "base/base_string.h"
#include "base/base_dynstr.h"

#include "gpu/gpu_init.h"
#include "gpu/gpu_backend.h"
#include "gpu/gpu_context.h"
#include "gpu/gpu_texture.h"
#include "gpu/gpu_batch.h"
#include "gpu/gpu_framebuffer.h"
#include "gpu/gpu_vertbuff.h"
#include "gpu/gpu_element.h"
#include "gpu/gpu_matrix.h"
#include "gpu/gpu_primitive.h"
#include "gpu/gpu_shader.h"
#include "gpu/gpu_uniform_buffer.h"
#include "gpu/gpu_vertformat.h"

#include "wm/wm.h"
#include "wm/dialog_modal.h"
#include "wm/dialog_main.h"
#include "wm/dialog_control.h"
#include "wm/window_control.h"
#include "wm/button.h"
#include "wm/radio.h"
#include "wm/checkbox.h"
#include "wm/gdi.h"

#include "eng/debug/eng_dbg_renderer.h"
#include "eng/eng_manager.h"
#include "eng/eng_proctor.h"
#include "eng/eng_gameobject.h"
#include "eng/eng_component.h"
#include "eng/eng_renderer.h"
#include "eng/eng_script.h"
#include "eng/eng_mesh.h"
#include "eng/eng_asset.h"
#include "eng/eng_light.h"
#include "eng/eng_camera.h"

#include "math/math_matrix.h"

void ROYALTY_init ( ) ;
void ROYALTY_update ( ) ;
void ROYALTY_exit ( );

double ROYALTY_time ( ) ;

void ROYALTY_MouseUpdate ( int x , int y ) ;

glm::vec2 ROYALTY_Mouse ( ) ;
glm::vec2 ROYALTY_DeltaMouse ( ) ;
float ROYALTY_MouseX ( ) ;
float ROYALTY_MouseY ( ) ;
