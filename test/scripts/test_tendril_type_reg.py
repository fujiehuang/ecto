#!/usr/bin/env python

import ecto
import ecto.ecto_test as ecto_test

for type_name in ecto.Tendril.listT():
    t = ecto.Tendril.createT(type_name)
    print(t.type_name, ' Value (', end=' ')
    try:
        print(t.val, end=' ')
    except TypeError as e:
        print('*NA*', end=' ')
    print(')')

str_t = ecto.Tendril.createT('std::string')
str_t.val = "foobar"
str_t_dest = ecto.Tendril()
str_t_dest.copy_value(str_t)
assert str_t_dest.val == 'foobar'

try:
    no = ecto.Tendril.createT('doesntexist::Foo')
    assert False and "shouldn't reach here!"
except ecto.TypeMismatch as e:
    print("Good, threw:", e)
