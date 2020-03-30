/*--------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-------------------------------------------------------------------------------------------------*/
#pragma once

#include "../generic/shallow_duplicate.hpp"

#include <type_traits>

namespace tweedledum {

/*! \brief Generic function to remove marked gates.
 *
 * For this function a node is marked when its value, returned by `netwokr.value(node)`, is not 0.
 * The orignal network is not modified.  A _new_ network is created and all nodes that are not
 * marked will be copied into it.
 * 
 * NOTE: This function requires a template parameter that cannot be inferred.  This is useful when
 * removing nodes and createing a different network format, e.g. `op_dag` <-> `netlist`
 * 
 * NOTE: Gate type _must_ be the same.
 * 
 * \param original The original quantum network (will not be modified)
 * \return A _new_ network without the marked gates.
*/
template<class NewNetwork, class Network>
NewNetwork remove_marked(Network const& original)
{
	using op_type = typename Network::op_type;
	using node_type = typename Network::node_type;

	static_assert(std::is_same_v<typename Network::op_type, typename NewNetwork::op_type>,
	              "Gate type _must_ be the same");

	NewNetwork result = shallow_duplicate<NewNetwork>(original);
	original.foreach_op([&](op_type const& op, node_type const& node) {
		if (original.value(node)) {
			return;
		}
		result.emplace_op(op);
	});
	return result;
}

/*! \brief Generic function to remove marked gates.
 *
 * For this function a node is marked when its value, returned by `netwokr.value(node)`, is not 0.
 * The orignal network is not modified.  A _new_ network is created and all nodes that are not
 * marked will be copied into it.
 * 
 * NOTE: the input and output networs are of the same type.
 * 
 * \param original The original quantum network (will not be modified)
 * \return A _new_ network without the marked gates.
 */
template<class Network>
Network remove_marked(Network const& original)
{
	return remove_marked<Network, Network>(original);
}

} // namespace tweedledum