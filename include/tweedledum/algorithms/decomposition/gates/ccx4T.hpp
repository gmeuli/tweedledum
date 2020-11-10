/*--------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-------------------------------------------------------------------------------------------------*/
#pragma once

#include "../../../gates/gate.hpp"
#include "../../../networks/wire.hpp"


namespace tweedledum::detail {

/*                               ┌───┐   ┌───┐   ┌───┐                      
 *    x  ──────────────-●────────┤ X ├───┤ ┴ ├── ┤ X ├───────────────────
 *                      │        └───┘   └───┘   └───┘        
 *                      │        ┌─┴─┐   ┌───┐   ┌───┐    
 *    y  ───────────────┼────●───┤ X ├───┤ ┴ ├── ┤ X ├───────────────────
 *                      │    │   └───┘   └───┘   └───┘
 *        ┌───┐ ┌───┐ ┌─┴─┐┌─┴─┐   |     ┌───┐     | ┌───┐┌───┐
 *   |0> ─┤ H ├─┤ T ├─┤ X ├┤ X ├───●─────┤ T ├─────●─┤ H ├┤ S ├──────────
 *        └───┘ └───┘ └───┘└───┘         └───┘       └───┘└───┘                    
 *
 * NOTE: Important normalization: if only one control is complemented, it must be x. This means
 * that a complemented `y` implies (->) a complemented `x`.
 */
template<typename Network>
void ccx4T(Network& network, wire::id x, wire::id y, wire::id const z)
{
	assert(!z.is_complemented());
  if (x.is_complemented())
    network.create_op(gate_lib::x, x.wire());
  if (y.is_complemented())
    network.create_op(gate_lib::x, y.wire());

  network.create_op(gate_lib::h, z);
  network.create_op(gate_lib::t, z);

	network.create_op(gate_lib::cx, x.wire(), z);
	network.create_op(gate_lib::cx, y.wire(), z);

	network.create_op(gate_lib::cx, z, x.wire());
	network.create_op(gate_lib::cx, z, y.wire());

	network.create_op(gate_lib::t, z);
  network.create_op(gate_lib::tdg, x.wire());
  network.create_op(gate_lib::tdg, y.wire());

  network.create_op(gate_lib::cx, z, x.wire());
	network.create_op(gate_lib::cx, z, y.wire());

  network.create_op(gate_lib::h, z);
  network.create_op(gate_lib::s, z);

  if (x.is_complemented())
    network.create_op(gate_lib::x, x.wire());
  if (y.is_complemented())
    network.create_op(gate_lib::x, y.wire());

}

}//tweedledum::detail