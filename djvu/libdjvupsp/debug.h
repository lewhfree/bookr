//C-  -*- C++ -*-
//C- -------------------------------------------------------------------
//C- DjVuLibre-3.5
//C- Copyright (c) 2002  Leon Bottou and Yann Le Cun.
//C- Copyright (c) 2001  AT&T
//C-
//C- This software is subject to, and may be distributed under, the
//C- GNU General Public License, either Version 2 of the license,
//C- or (at your option) any later version. The license should have
//C- accompanied the software or you may obtain a copy of the license
//C- from the Free Software Foundation at http://www.fsf.org .
//C-
//C- This program is distributed in the hope that it will be useful,
//C- but WITHOUT ANY WARRANTY; without even the implied warranty of
//C- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//C- GNU General Public License for more details.
//C- 
//C- DjVuLibre-3.5 is derived from the DjVu(r) Reference Library from
//C- Lizardtech Software.  Lizardtech Software has authorized us to
//C- replace the original DjVu(r) Reference Library notice by the following
//C- text (see doc/lizard2002.djvu and doc/lizardtech2007.djvu):
//C-
//C-  ------------------------------------------------------------------
//C- | DjVu (r) Reference Library (v. 3.5)
//C- | Copyright (c) 1999-2001 LizardTech, Inc. All Rights Reserved.
//C- | The DjVu Reference Library is protected by U.S. Pat. No.
//C- | 6,058,214 and patents pending.
//C- |
//C- | This software is subject to, and may be distributed under, the
//C- | GNU General Public License, either Version 2 of the license,
//C- | or (at your option) any later version. The license should have
//C- | accompanied the software or you may obtain a copy of the license
//C- | from the Free Software Foundation at http://www.fsf.org .
//C- |
//C- | The computer code originally released by LizardTech under this
//C- | license and unmodified by other parties is deemed "the LIZARDTECH
//C- | ORIGINAL CODE."  Subject to any third party intellectual property
//C- | claims, LizardTech grants recipient a worldwide, royalty-free, 
//C- | non-exclusive license to make, use, sell, or otherwise dispose of 
//C- | the LIZARDTECH ORIGINAL CODE or of programs derived from the 
//C- | LIZARDTECH ORIGINAL CODE in compliance with the terms of the GNU 
//C- | General Public License.   This grant only confers the right to 
//C- | infringe patent claims underlying the LIZARDTECH ORIGINAL CODE to 
//C- | the extent such infringement is reasonably necessary to enable 
//C- | recipient to make, have made, practice, sell, or otherwise dispose 
//C- | of the LIZARDTECH ORIGINAL CODE (or portions thereof) and not to 
//C- | any greater extent that may be necessary to utilize further 
//C- | modifications or combinations.
//C- |
//C- | The LIZARDTECH ORIGINAL CODE is provided "AS IS" WITHOUT WARRANTY
//C- | OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
//C- | TO ANY WARRANTY OF NON-INFRINGEMENT, OR ANY IMPLIED WARRANTY OF
//C- | MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
//C- +------------------------------------------------------------------
// 
// $Id: debug.h,v 1.1 2007/10/17 20:28:58 cpayeur Exp $
// $Name:  $

#ifndef _DEBUG_H_
#define _DEBUG_H_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#if NEED_GNUG_PRAGMAS
# pragma interface
#endif

#include <stdio.h>
#ifdef WIN32
# include <atlbase.h> // USES_CONVERSION, A2CT macro
# include <windows.h> // OutputDebugString
#endif 


#ifdef HAVE_NAMESPACES
namespace DJVU {
# ifdef NOT_DEFINED // Just to fool emacs c++ mode
}
# endif
#endif

/** @name debug.h

    Files #"debug.h"# and #"debug.cpp"# implement means to print debug
    messages in a multithread safe way.  Message are also marked with a thread
    identifier.  Under Windows, debug messages are directly sent to the
    debugger using the Win32 function #OutputDebugString#.  Under Unix, debug
    messages are printed on the controlling terminal, preferably using device
    #/dev/tty#.

    The preprocessor variable #DEBUGLVL# defines which debug code is going to
    be compiled.  Selecting #-DDEBUGLVL=0# (the default) disables all
    debugging code.  Selecting a positive values (e.g. #-DDEBUGLVL=4#) enables
    more and more debugging code.

    Message output is controlled by the current debugging level (an integer
    between #0# and #DEBUGLVL#). Greater values enable more messages.  The
    initial debugging level is set to the maximum value.  The debugging level
    can be changed using macro \Ref{DEBUG_SET_LEVEL}.

    Message indentation can be modified using macro \Ref{DEBUG_MAKE_INDENT}.
    Messages are generated by macro \Ref{DEBUG_MSG} or its variants.  The
    argument of the macro can contain several components separated by operator
    #<<#, as demonstrated in the example below:
    \begin{verbatim}
    DEBUG_MSG("The value of a[" << n << "] is " << a[n] << '\n');
    \end{verbatim}

    One more preprocessor variable #RUNTIME_DEBUG_ONLY# enables compilation
    of debug code, but does not enable the debug messages automatically.
    In order to see them the program should use \Ref{DEBUG_SET_LEVEL} to
    change the level to anything greater than 0. Normally this happens when
    user specifies option #-debug# in the command line. Usage of
    #RUNTIME_DEBUG_ONLY# implies #DEBUGLVL=1# if not specified otherwise.

    Finally, #-DNO_DEBUG# or #-DNDEBUG# can be used instead of #-DDEBUGLVL=0#,
    and #-D_DEBUG# can be used instead of #-DDEBUGLVL=0#.

    {\bf Historical Comment} --- Debug macros are rarely used in the reference
    DjVu library because Leon thinks that debugging messages unnecessarily
    clutter the code.  Debug macros are used everywhere in the plugin code
    because Andrew thinks that code without debugging messages is close to
    useless.  No agreement could be reached. Neither could they agree on
    if cluttering header files with huge documentation chunks helps to
    improve code readability.

    @memo 
    Macros for printing debug messages.
    @version 
    #$Id: debug.h,v 1.1 2007/10/17 20:28:58 cpayeur Exp $#
    @author
    Andrew Erofeev <eaf@geocities.com> -- initial implementation \\
    Leon Bottou <leonb@research.att.com> -- cleanups */
//@{

#ifndef DEBUGLVL
# ifdef NDEBUG
#  define DEBUGLVL 0
# endif 
#endif
#ifndef DEBUGLVL
# ifdef NO_DEBUG
#  define DEBUGLVL 0
# endif 
#endif
#ifndef DEBUGLVL
# ifdef RUNTIME_DEBUG_ONLY
#  define DEBUGLVL 1
# endif 
#endif
#ifndef DEBUGLVL
# ifdef _DEBUG
#  define DEBUGLVL 1
# endif 
#endif
#ifndef DEBUGLVL
#  define DEBUGLVL 0
#endif

#if DEBUGLVL <= 0

# ifndef NO_DEBUG
#  define NO_DEBUG
# endif
# ifndef NDEBUG
#  define NDEBUG
# endif
# ifdef _DEBUG
#  undef _DEBUG
# endif

# define DEBUG_MAKE_INDENT(x)
# define DEBUG_SET_LEVEL(level)
# define DEBUG_MSG_LVL(level,x)
# define DEBUG_MSGN_LVL(level,x)

#else

# ifdef NO_DEBUG
#  undef NO_DEBUG
# endif
# ifdef NDEBUG
#  undef NDEBUG
# endif
# ifndef _DEBUG
#  define _DEBUG
# endif

class GUTF8String;

// ------------ SUPPORT

class DjVuDebug // DJVU_CLASS
{
private:
  int    id;
  int    block;
  int    indent;
  void   format(const char *fmt, ... );
public:
  // construction
  DjVuDebug();
  ~DjVuDebug();
  // access
  static void   set_debug_level(int lvl);
  static void	set_debug_file(FILE * file);
  void          modify_indent(int rindent);
  static DjVuDebug& lock(int lvl, int noindent);
  void          unlock();
  // printing
  DjVuDebug &	operator<<(bool b);
  DjVuDebug &	operator<<(char c);
  DjVuDebug &	operator<<(unsigned char c);
  DjVuDebug &	operator<<(int i);
  DjVuDebug &	operator<<(unsigned int i);
  DjVuDebug &	operator<<(short int i);
  DjVuDebug &	operator<<(unsigned short int i);
  DjVuDebug &	operator<<(long i);
  DjVuDebug &	operator<<(unsigned long i);
  DjVuDebug &	operator<<(const char * const ptr);
  DjVuDebug &	operator<<(const unsigned char * const ptr);
  DjVuDebug&    operator<<(const GUTF8String &ptr);
  DjVuDebug &	operator<<(float f);
  DjVuDebug &	operator<<(double d);
  DjVuDebug &	operator<<(const void * const p);
};

class DjVuDebugIndent // DJVU_CLASS
{
private:
  int inc;
public:
  DjVuDebugIndent(int inc=2);
  ~DjVuDebugIndent();
//#define DEBUG_MAKE_INDENT_2(x, y) DjVuDebugIndent debug_indent ## y (x)
//#define DEBUG_MAKE_INDENT_1(x, y) DEBUG_MAKE_INDENT_2(x, y)
#define DEBUG_MAKE_INDENT_1(x, y) DjVuDebugIndent debug_indent ## y (x)
};

// ------------ MAIN MACROS

# define DEBUG_MAKE_INDENT(x)     DEBUG_MAKE_INDENT_1(x, __LINE__)
# define DEBUG_SET_LEVEL(level)   DjVuDebug::set_debug_level(level)
# define DEBUG_MSG_LVL(level,x)   { ( DjVuDebug::lock(level,0) << x ).unlock(); }
# define DEBUG_MSGN_LVL(level,x)  { ( DjVuDebug::lock(level,1) << x ).unlock(); }
# define DEBUG_MSGF_LVL(level,x)  { ( DjVuDebug::lock(level,1) << x ).unlock(); }

#endif


// ------------ EAF MACROS

#if ( DEBUGLVL >= 1 )
/** Generates a level 1 message */
# define DEBUG1_MSG(x)  DEBUG_MSG_LVL(1,x)
# define DEBUG1_MSGF(x) DEBUG_MSGF_LVL(1,x)
#else
# define DEBUG1_MSG(x)
# define DEBUG1_MSGF(x)
#endif
#if ( DEBUGLVL >= 2 )
/** Generates a level 2 message */
# define DEBUG2_MSG(x)  DEBUG_MSG_LVL(2,x)
# define DEBUG2_MSGF(x) DEBUG_MSGF_LVL(2,x)
#else
# define DEBUG2_MSG(x)
# define DEBUG2_MSGF(x)
#endif
#if ( DEBUGLVL >= 3 )
/** Generates a level 3 message */
# define DEBUG3_MSG(x)  DEBUG_MSG_LVL(3,x)
# define DEBUG3_MSGF(x) DEBUG_MSGF_LVL(3,x)
#else
# define DEBUG3_MSG(x)
# define DEBUG3_MSGF(x)
#endif
#if ( DEBUGLVL >= 4 )
/** Generates a level 4 message */
# define DEBUG4_MSG(x)  DEBUG_MSG_LVL(4,x)
# define DEBUG4_MSGF(x) DEBUG_MSGF_LVL(4,x)
#else
# define DEBUG4_MSG(x)
# define DEBUG4_MSGF(x)
#endif

#define DEBUG_RUNTIME_SET_LEVEL(level) DEBUG_SET_LEVEL(level)
/** Generates a level 1 message. */
#define DEBUG_MSG(x)  DEBUG1_MSG(x)
/** Generates a level 1 message without indentation. */
#define DEBUG_MSGF(x) DEBUG1_MSGF(x)
/** Generates a level 1 message terminated with a newline. */
#define DEBUG_MSGN(x) DEBUG_MSG(x<<'\n')

//@}

// ------------ THE END

#ifdef HAVE_NAMESPACES
}
# ifndef NOT_USING_DJVU_NAMESPACE
using namespace DJVU;
# endif
#endif

#endif // DEBUG_H
