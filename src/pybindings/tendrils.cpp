#include <boost/python.hpp>

#include <ecto/ecto.hpp>
#include <ecto/module.hpp>

#include <ecto/python/std_map_indexing_suite.hpp>

namespace bp = boost::python;

namespace ecto
{
  namespace py
  {
    namespace
    {
      void setTendril(tendrils& t, const std::string& name, const std::string& doc, bp::object o)
      {
        t.declare<bp::object> (name, doc, o);
      }

      bp::object getTendril(tendrils& t, const std::string& name)
      {
        return t[name]->extract();
      }

      std::string strTendril(const tendrils& t)
      {
        std::string s = "tendrils:\n";
        for (tendrils::const_iterator iter = t.begin(), end = t.end(); iter != end; ++iter)
        {
          s += "    " + iter->first + " [" + iter->second->type_name() + "]\n";
        }
        return s;
      }

      bp::object tendril_get(const tendrils& ts, const std::string& name)
      {
        const tendril& t = *ts.at(name);
        return t.extract();
      }

      void tendril_set(tendrils& ts, const std::string& name, bp::object obj)
      {
        ts.at(name)->set(obj);
      }

      tendril::ptr tendril_at(tendrils& ts, const std::string& name)
      {
        return ts.at(name);
      }
    }

    void wrapTendrils()
    {
      bp::class_<tendrils, boost::shared_ptr<tendrils>, boost::noncopyable>("Tendrils")
        .def(bp::std_map_indexing_suite<tendrils, false>())
        .def("declare", &setTendril)
        .def("__str__", &strTendril)
        .def("__getattr__", &tendril_get)
        .def("__setattr__", &tendril_set)
        .def("__getitem__", &tendril_get)
        .def("at",tendril_at)
        ;
    }
  }
}
