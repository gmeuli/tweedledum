/*------------------------------------------------------------------------------
| Part of Tweedledum Project.  This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-----------------------------------------------------------------------------*/
#pragma once

#include "../../Utils/Angle.h"
#include "../../Utils/UMatrix.h"

#include <cmath>
#include <string_view>

namespace tweedledum::Op {

class Rxx {
public:
    static constexpr std::string_view kind()
    {
        return "ising.rxx";
    }

    Rxx(Angle angle) : angle_(angle)
    {}

    Rxx adjoint() const
    {
        return Rxx(-angle_);
    }

    UMatrix4 const matrix() const
    {
        Complex const a = std::cos(angle_.numeric_value());
        Complex const b = {0. -std::sin(angle_.numeric_value())};
        return (UMatrix4() << a, 0 ,0, b,
                              0, a, b, 0,
                              0, b, a, 0,
                              b, 0, 0, a).finished();
    }

    uint32_t num_targets() const
    {
        return 2u;
    }

private:
    Angle const angle_;
};

} // namespace tweedledum
