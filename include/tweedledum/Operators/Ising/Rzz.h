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

class Rzz {
public:
    static constexpr std::string_view kind()
    {
        return "ising.ryy";
    }

    Rzz(Angle angle) : angle_(angle)
    {}

    Rzz adjoint() const
    {
        return Rzz(-angle_);
    }

    UMatrix4 const matrix() const
    {
        Complex const p = std::exp(Complex(0., angle_.numeric_value() / 2));
        Complex const n = std::exp(Complex(0., -angle_.numeric_value() / 2));
        return (UMatrix4() << p, 0, 0, 0,
                              0, n, 0, 0,
                              0, 0, n, 0,
                              0, 0, 0, p).finished();
    }

    uint32_t num_targets() const
    {
        return 2u;
    }

private:
    Angle const angle_;
};

} // namespace tweedledum
