/*
 * Copyright © 2016 Benoit Gschwind
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

#ifndef WESTON_COMPOSITOR_WAYLAND_H
#define WESTON_COMPOSITOR_WAYLAND_H

#include "compositor.h"
#include "plugin-registry.h"

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define WESTON_WAYLAND_BACKEND_CONFIG_VERSION 1


#define WESTON_WAYLAND_OUTPUT_API_NAME "weston_wayland_output_api_v1"

struct weston_wayland_output_api {
	int (*output_configure)(struct weston_output *output);
};

static inline const struct weston_wayland_output_api *
weston_wayland_output_get_api(struct weston_compositor *compositor)
{
	const void *api;
	api = weston_plugin_api_get(compositor, WESTON_WAYLAND_OUTPUT_API_NAME,
				    sizeof(struct weston_wayland_output_api));

	return (const struct weston_wayland_output_api *)api;
}

struct weston_wayland_backend_config {
	struct weston_backend_config base;
	int use_pixman;
	int sprawl;
	char *display_name;
	int fullscreen;
	char *cursor_theme;
	int cursor_size;
	int num_outputs;
	struct weston_wayland_backend_output_config *outputs;
};

#ifdef  __cplusplus
}
#endif

#endif /* WESTON_COMPOSITOR_WAYLAND_H */
