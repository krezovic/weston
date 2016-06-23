/*
 * Copyright © 2012 Intel Corporation
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

#include "config.h"

#include <unistd.h>

#include "compositor.h"
#include "compositor-x11.h"
#include "compositor-x11-private.h"
#include "wayland-server.h"

static int
timer_handler(void *data)
{
        struct weston_compositor *ec = data;
	struct x11_backend *b = (struct x11_backend *)ec->backend;

	b->init_x11_outputs(b);

	return 1;
}

WL_EXPORT int
module_init(struct weston_compositor *ec,
	    int *argc, char *argv[])
{
	struct wl_event_loop *loop;
	struct wl_event_source *source;

	loop = wl_display_get_event_loop(ec->wl_display);
	source = wl_event_loop_add_timer(loop, timer_handler, ec);
	wl_event_source_timer_update(source, 30000);

	return 0;
}
