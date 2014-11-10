/*
 * Copyright (c) 2011 Rémi "Remram" Rampin <remirampin@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef _LIBMENU_H
#define _LIBMENU_H

#define MENU_ITEM_LABEL 0x1

#define MENU_ITEM_BUTTON 0x2

typedef struct _libmenu_menu menu_t;

typedef struct _libmenu_menu_item menu_item_t;

menu_t *menu_push(const char *title);

void menu_setwindow(menu_t *menu, int width, int height, int start_x, int start_y);

void menu_pop(menu_t *menu);

menu_item_t *menu_newitem(menu_t *menu, unsigned int type);

void menu_setitem(menu_item_t *item, const char *format, ...);

menu_item_t *menu_wait(menu_t *menu, int timeout);

#define MENU_QUIT ((menu_item_t*)0x01)

#endif
