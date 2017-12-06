/*
  Part of: CCTests
  Contents: condition objects
  Date: Nov 28, 2017

  Abstract



  Copyright (C) 2017 Marco Maggi <marco.maggi-ipsu@poste.it>

  This is free software; you  can redistribute it and/or modify it under
  the terms of the GNU Lesser General Public License as published by the
  Free Software  Foundation; either version  3.0 of the License,  or (at
  your option) any later version.

  This library  is distributed in the  hope that it will  be useful, but
  WITHOUT   ANY  WARRANTY;   without  even   the  implied   warranty  of
  MERCHANTABILITY  or FITNESS  FOR A  PARTICULAR PURPOSE.   See  the GNU
  Lesser General Public License for more details.

  You  should have  received a  copy of  the GNU  Lesser  General Public
  License along  with this library; if  not, write to  the Free Software
  Foundation, Inc.,  59 Temple Place,  Suite 330, Boston,  MA 02111-1307
  USA.

*/


/** --------------------------------------------------------------------
 ** Headers.
 ** ----------------------------------------------------------------- */

#include "cctests-internals.h"


/** --------------------------------------------------------------------
 ** Base exceptional condition descriptor.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	cctests_condition_static_message_base;

static cctests_descriptor_base_t cctests_descriptor_base_stru = {
  /* This  "parent" field  is  set below  by  the module  initialisation
     function. */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cctests_condition_static_message_base
};

cctests_descriptor_base_t const * const cctests_descriptor_base_ptr = &cctests_descriptor_base_stru;

/* ------------------------------------------------------------------ */

char const *
cctests_condition_static_message_base (cce_condition_t const * C CCE_UNUSED)
{
  return "CCTests base exceptional condition";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: test failure.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	cctests_condition_static_message_failure;

static cctests_descriptor_failure_t const cctests_descriptor_failure_stru = {
  .descriptor.parent		= &cctests_descriptor_base_stru.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cctests_condition_static_message_failure
};

cctests_descriptor_failure_t const * const cctests_descriptor_failure_ptr = &cctests_descriptor_failure_stru;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static cctests_condition_failure_t const cctests_condition_failure = {
  .base.root.condition.descriptor	= &cctests_descriptor_failure_stru.descriptor
};

/* ------------------------------------------------------------------ */

char const *
cctests_condition_static_message_failure (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests test failure";
}

/* ------------------------------------------------------------------ */

cce_condition_t const *
cctests_condition_new_failure (void)
{
  return (cce_condition_t *)&cctests_condition_failure;
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: failed assertion.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	cctests_condition_static_message_assertion;
static cce_condition_delete_fun_t		cctests_condition_delete_assertion;

static cctests_descriptor_assertion_t const cctests_descriptor_assertion_stru = {
  .descriptor.parent		= &cctests_descriptor_failure_stru.descriptor,
  .descriptor.delete		= cctests_condition_delete_assertion,
  .descriptor.final		= NULL,
  .descriptor.static_message	= cctests_condition_static_message_assertion
};

cctests_descriptor_assertion_t const * const cctests_descriptor_assertion_ptr = &cctests_descriptor_assertion_stru;

/* ------------------------------------------------------------------ */

void
cctests_condition_delete_assertion (cce_condition_t * C)
{
  free(C);
}

char const *
cctests_condition_static_message_assertion (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests assertion failure";
}

/* ------------------------------------------------------------------ */

void
cctests_condition_init_assertion (cctests_condition_assertion_t * C,
				  char const * const expr,
				  char const * const filename,
				  char const * const funcname,
				  int const linenum)
{
  fprintf(stderr, "%s: enter\n", __func__);

  /* Initialise the parent type. */
  cctests_condition_init_failure(&(C->failure));

  /* Initialise the fields of this type. */
  C->expr			= expr;
  C->filename			= filename;
  C->funcname			= funcname;
  C->linenum			= linenum;

  fprintf(stderr, "%s: done\n", __func__);
}

cce_condition_t const *
cctests_condition_new_assertion (cce_destination_t L,
				 char const * const expr, char const * const filename, char const * const funcname, int const linenum)
{
  cctests_condition_assertion_t *	C = cctests_sys_malloc(L, sizeof(cctests_condition_assertion_t));

  /* Initialise the basic condition fields. */
  cce_condition_init((cce_condition_t *)C, &cctests_descriptor_assertion_stru.descriptor);

  cctests_condition_init_assertion(C, expr, filename, funcname, linenum);

  return (cce_condition_t const *)C;
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: signal one.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_static_message_signal_1;

static cctests_descriptor_signal_1_t const descriptor_signal_1 = {
  .descriptor.parent		= &cctests_descriptor_base_stru.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_static_message_signal_1
};

cctests_descriptor_signal_1_t const * const cctests_descriptor_signal_1_ptr = &descriptor_signal_1;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static cctests_condition_signal_1_t const condition_signal_1 = {
  .base.root.condition.descriptor	= &descriptor_signal_1.descriptor
};

cce_condition_t const *
cctests_condition_new_signal_1 (void)
{
  return (cce_condition_t *)&condition_signal_1;
}

char const *
condition_static_message_signal_1 (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests exception signal 1";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: signal two.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_static_message_signal_2;

static cctests_descriptor_signal_2_t const descriptor_signal_2 = {
  .descriptor.parent		= &cctests_descriptor_base_stru.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_static_message_signal_2
};

cctests_descriptor_signal_2_t const * const cctests_descriptor_signal_2_ptr = &descriptor_signal_2;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static cctests_condition_signal_2_t const condition_signal_2 = {
  .base.root.condition.descriptor	= &descriptor_signal_2.descriptor
};

cce_condition_t const *
cctests_condition_new_signal_2 (void)
{
  return (cce_condition_t *)&condition_signal_2;
}

char const *
condition_static_message_signal_2 (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests exception signal 2";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: signal three.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_static_message_signal_3;

static cctests_descriptor_signal_3_t const descriptor_signal_3 = {
  .descriptor.parent		= &cctests_descriptor_base_stru.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_static_message_signal_3
};

cctests_descriptor_signal_3_t const * const cctests_descriptor_signal_3_ptr = &descriptor_signal_3;

/* This struct type has no dynamic fields, so there is only one instance
   of this struct type.  We allocate it statically. */
static cctests_condition_signal_3_t const condition_signal_3 = {
  .base.root.condition.descriptor	= &descriptor_signal_3.descriptor
};

cce_condition_t const *
cctests_condition_new_signal_3 (void)
{
  return (cce_condition_t *)&condition_signal_3;
}

char const *
condition_static_message_signal_3 (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests exception signal 3";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: regular expression error.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_static_message_regex_error;

static cctests_descriptor_regex_error_t descriptor_regex_error = {
  /* This field is set by the initialisation function to the pointer:
   *
   *	&(cce_descriptor_runtime_error_ptr->descriptor)
   */
  .descriptor.parent		= NULL,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_static_message_regex_error
};

cctests_descriptor_regex_error_t const * const cctests_descriptor_regex_error_ptr = &descriptor_regex_error;

void
cctests_condition_init_regex_error (cctests_condition_regex_error_t * C, int rv, void * rex)
{
  cce_condition_init_runtime_error(&(C->runtime_error));
  C->errcode = rv;
  regerror(rv, (regex_t *) rex, C->error_message, 1024);
}

cce_condition_t const *
cctests_condition_new_regex_error (cce_destination_t L, int rv, void * rex)
{
  cctests_condition_regex_error_t *	C = cctests_sys_malloc(L, sizeof(cctests_condition_regex_error_t));

  cce_condition_init((cce_condition_t *)C, &descriptor_regex_error.descriptor);
  cctests_condition_init_regex_error(C, rv, rex);
  return (cce_condition_t *)C;
}

char const *
condition_static_message_regex_error (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests regular expression error";
}


/** --------------------------------------------------------------------
 ** Exceptional condition descriptor: regular expression compilation error.
 ** ----------------------------------------------------------------- */

static cce_condition_static_message_fun_t	condition_static_message_regex_compilation_error;

static cctests_descriptor_regex_compilation_error_t const descriptor_regex_compilation_error = {
  .descriptor.parent		= &descriptor_regex_error.descriptor,
  .descriptor.delete		= NULL,
  .descriptor.final		= NULL,
  .descriptor.static_message	= condition_static_message_regex_compilation_error
};

cctests_descriptor_regex_compilation_error_t const * const cctests_descriptor_regex_compilation_error_ptr = &descriptor_regex_compilation_error;

void
cctests_condition_init_regex_compilation_error (cctests_condition_regex_compilation_error_t * C, int rv)
{
  /* For a compilation error we have  no valid "regex_t" argument, so we
     set it to NULL as described in the specification. */
  cctests_condition_init_regex_error(&(C->regex_error), rv, NULL);
}

cce_condition_t const *
cctests_condition_new_regex_compilation_error (cce_destination_t L, int rv)
{
  cctests_condition_regex_compilation_error_t *	C = \
    cctests_sys_malloc(L, sizeof(cctests_condition_regex_compilation_error_t));

  cce_condition_init((cce_condition_t *)C, &descriptor_regex_compilation_error.descriptor);
  cctests_condition_init_regex_compilation_error(C, rv);
  return (cce_condition_t *)C;
}

char const *
condition_static_message_regex_compilation_error (cce_condition_t const * C CCTESTS_UNUSED)
{
  return "CCTests regular expression compilation error";
}


/** --------------------------------------------------------------------
 ** Module initialisation.
 ** ----------------------------------------------------------------- */

void
cctests_conditions_module_initialisation (void)
{
  cce_descriptor_set_root_parent(&cctests_descriptor_base_stru.descriptor);
  descriptor_regex_error.descriptor.parent = &(cce_descriptor_runtime_error_ptr->descriptor);
}

/* end of file */
