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
#include "shared/helpers.h"
#include "wayland-server.h"

struct output_destroy {
	struct wl_event_loop *loop;
	struct wl_event_source *source;
	struct wl_listener destroy_listener;
};

static int
timer_handler(void *data)
{
        struct weston_compositor *ec = data;
	struct weston_output *output, *next;

	wl_list_for_each_safe(output, next, &ec->output_list, link)
		output->destroy(output);

	return 1;
}

static void
module_destroy(struct wl_listener *listener, void *data) {
	struct output_destroy *d =
                container_of(listener, struct output_destroy, destroy_listener);

	if (d->source) {
		wl_event_source_remove(d->source);
		d->source = NULL;
	}

	free (d);
}

WL_EXPORT int
module_init(struct weston_compositor *ec,
	    int *argc, char *argv[])
{
	struct output_destroy *d;

	d = zalloc(sizeof *d);
	if (!d) {
		weston_log("out of memory");
		return -1;
	}

	d->loop = wl_display_get_event_loop(ec->wl_display);
	d->source = wl_event_loop_add_timer(d->loop, timer_handler, ec);
	wl_event_source_timer_update(d->source, 10000);

	d->destroy_listener.notify = module_destroy;
        wl_signal_add(&ec->destroy_signal, &d->destroy_listener);

	return 0;
}
