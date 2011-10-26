/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2003  Masao Mutoh
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "rbatkprivate.h"

#define RG_TARGET_NAMESPACE cRelation
#define _SELF(s) (ATK_RELATION(RVAL2GOBJ(s)))

static VALUE
rbatkrel_s_type_register(G_GNUC_UNUSED VALUE self, VALUE name)
{
    return GENUM2RVAL(atk_relation_type_register(RVAL2CSTR(name)), ATK_TYPE_RELATION_TYPE);
}

struct rval2atkobjects_args {
    VALUE ary;
    long n;
    AtkObject **result;
};

static VALUE
rval2atkobjects_body(VALUE value)
{
    long i;
    struct rval2atkobjects_args *args = (struct rval2atkobjects_args *)value;

    for (i = 0; i < args->n; i++)
            args->result[i] = ATK_OBJECT(RVAL2GOBJ(RARRAY_PTR(args->ary)[i]));

    return Qnil;
}

static G_GNUC_NORETURN VALUE
rval2atkobjects_rescue(VALUE value)
{
    g_free(((struct rval2atkobjects_args *)value)->result);

    rb_exc_raise(rb_errinfo());
}

static VALUE
rbatkrel_initialize(VALUE self, VALUE targets, VALUE rbrelationship)
{
    AtkRelationType relationship = RVAL2GENUM(rbrelationship, ATK_TYPE_RELATION_TYPE);
    struct rval2atkobjects_args args;
    AtkRelation *relation;

    args.ary = rb_ary_to_ary(targets);
    args.n = RARRAY_LEN(args.ary);
    args.result = g_new(AtkObject *, args.n + 1);

    rb_rescue(rval2atkobjects_body, (VALUE)&args,
              rval2atkobjects_rescue, (VALUE)&args);

    relation = atk_relation_new(args.result, args.n, relationship);

    g_free(args.result);

    G_INITIALIZE(self, relation);

    return Qnil;
}

#if ATK_CHECK_VERSION(1,9,0)
static VALUE
rbatkrel_add_target(VALUE self, VALUE obj)
{
    atk_relation_add_target(_SELF(self), ATK_OBJECT(RVAL2GOBJ(obj)));
    return self;
}
#endif

void
Init_atk_relation(void)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(ATK_TYPE_RELATION, "Relation", mAtk);
    rb_define_singleton_method(RG_TARGET_NAMESPACE, "type_register", rbatkrel_s_type_register, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "initialize", rbatkrel_initialize, 2);
#if ATK_CHECK_VERSION(1,9,0)
    rb_define_method(RG_TARGET_NAMESPACE, "add_target", rbatkrel_add_target, 1);
#endif

    Init_atk_relation_type(RG_TARGET_NAMESPACE);
}
