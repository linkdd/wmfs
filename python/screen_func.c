/*
 *      screen_func.c
 *      Copyright © 2008 Martin Duquesnoy <xorg62@gmail.com>
 *      All rights reserved.
 *
 *      Redistribution and use in source and binary forms, with or without
 *      modification, are permitted provided that the following conditions are
 *      met:
 *
 *      * Redistributions of source code must retain the above copyright
 *        notice, this list of conditions and the following disclaimer.
 *      * Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following disclaimer
 *        in the documentation and/or other materials provided with the
 *        distribution.
 *      * Neither the name of the  nor the names of its
 *        contributors may be used to endorse or promote products derived from
 *        this software without specific prior written permission.
 *
 *      THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *      "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *      LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *      A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *      OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *      SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *      LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *      DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *      THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *      (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *      OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "libwmfs.h"

PyObject*
wmfs_screen_set(PyObject *self, PyObject *args)
{
     long data[5];
     int arg;

     if(!PyArg_ParseTuple(args, "i", &arg))
          return NULL;

     data[0] = arg;

     send_client_message("_WMFS_SET_SCREEN", data);

     Py_INCREF(Py_None);

     return Py_None;
}


PyObject*
wmfs_screen_get_cur(PyObject *self, PyObject *args)
{
     Atom rt;
     int rf;
     unsigned long ir, il;
     unsigned char *ret;
     int i = 0;

     PyArg_ParseTuple(args, "");

     if(XGetWindowProperty(dpy, ROOT, ATOM("_WMFS_CURRENT_SCREEN"), 0L, 4096,
                           False, XA_CARDINAL, &rt, &rf, &ir, &il, &ret) == Success);
     {
          i = *(long*)ret;
          XFree(ret);
     }

     return Py_BuildValue("i", i);
}

PyObject*
wmfs_screen_count(PyObject *self, PyObject *args)
{
     Atom rt;
     int rf;
     unsigned long ir, il;
     unsigned char *ret;
     int i = 1;

     PyArg_ParseTuple(args, "");

     if(XGetWindowProperty(dpy, ROOT, ATOM("_WMFS_SCREEN_COUNT"), 0L, 4096,
                           False, XA_CARDINAL, &rt, &rf, &ir, &il, &ret) == Success);
     {
          i = *(long*)ret;
          XFree(ret);
     }

     printf("screen count: %i\n", i);

     return Py_BuildValue("i", i);
}
