#pragma once

#include "gpu_init.h"

bool GPU_mem_stats_supported (void);

void GPU_mem_stats_get (int *totalmem, int *freemem);

long long GPU_mem_stats_totalmem ();
long long GPU_mem_stats_freemem ();

unsigned int GPU_get_max_textures ( );
