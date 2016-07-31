/*
 * Copyright © 2016 Collabora, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef WESTON_OUTPUT_API_H
#define WESTON_OUTPUT_API_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "plugin-registry.h"

struct weston_compositor;
struct weston_output;
struct weston_output_config;
struct weston_drm_backend_output_config;

#define WESTON_OUTPUT_API_NAME "weston_output_api_v1"

struct weston_output_api {
	int (*generic_output_init)(struct weston_output *output,
				   struct weston_output_config *config);

	int (*generic_output_create)(struct weston_compositor *compositor,
				     const char *name);

	int (*fbdev_output_init)(struct weston_output *output,
				 uint32_t transform);

	int (*drm_output_init)(struct weston_output *output,
			       struct weston_drm_backend_output_config *config);
};

static inline const struct weston_output_api *
weston_output_get_api(struct weston_compositor *compositor)
{
	const void *api;
	api = weston_plugin_api_get(compositor, WESTON_OUTPUT_API_NAME,
				    sizeof(struct weston_output_api));

	return (struct weston_output_api *)api;
}

#ifdef  __cplusplus
}
#endif

#endif /* WESTON_OUTPUT_API_H */
