/*------------------------------------------------------------------------------
| Part of Tweedledum Project.  This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-----------------------------------------------------------------------------*/
#pragma once

#include "../../Utils/UMatrix.h"

#include <array>
#include <string_view>

namespace tweedledum::Op {

// Pauli-X operator
class X {
    constexpr static std::array<Complex, 4> mat_ = {0., 1., 1., 0.};
public:
    static constexpr std::string_view kind()
    {
        return "std.x";
    }

    static X adjoint()
    {
        return X();
    }

    static UMatrix2 const matrix()
    {
        return Eigen::Map<UMatrix2 const>(mat_.data());
    }
};

} // namespace tweedledum
