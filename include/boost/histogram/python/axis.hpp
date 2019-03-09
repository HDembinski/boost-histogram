// Copyright 2015-2018 Hans Dembinski and Henry Schreiner
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/histogram.hpp>

#include <tuple>
#include <vector>

namespace bh = boost::histogram;

// Register bh::axis::Variant as a variant for PyBind11
namespace pybind11 { namespace detail {
    template <typename... Ts>
    struct type_caster<bh::axis::variant<Ts...>> : variant_caster<bh::axis::variant<Ts...>> {};
}} // namespace pybind11::detail


namespace axis {

// These match the Python names
using regular = bh::axis::regular<>;
using circular = bh::axis::circular<>;
using regular_log = bh::axis::regular<double, bh::axis::transform::log>;
using regular_sqrt = bh::axis::regular<double, bh::axis::transform::sqrt>;
using regular_pow = bh::axis::regular<double, bh::axis::transform::pow>;

} // namespace axis

namespace axes {

// The following list is all types supported
using any = std::vector<bh::axis::variant<axis::regular,
                                          axis::circular,
                                          axis::regular_log,
                                          axis::regular_pow,
                                          axis::regular_sqrt>>;

// Specialization for some speed improvement
using regular = std::vector<axis::regular>;

// Specializations for maximum speed!
using regular_1D = std::tuple<axis::regular>;
using regular_2D = std::tuple<axis::regular, axis::regular>;

} // namespace axes