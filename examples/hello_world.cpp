/*--------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
*-------------------------------------------------------------------------------------------------*/
#include <iostream>
#include <tweedledum/gates/gate.hpp>
#include <tweedledum/io/write_utf8.hpp>
#include <tweedledum/networks/netlist.hpp>
#include <tweedledum/operations/wn32_op.hpp>
#include <tweedledum/algorithms/decomposition/decompose.hpp>

using namespace tweedledum;
using QuantumCircuit = netlist<wn32_op>;

static inline int t_count( QuantumCircuit const& netlist)
{
  int count = 0;
  netlist.foreach_op([&](const auto gate)
  {
    if (gate.is(gate_ids::t))
    {
      count++;
    }
    if (gate.is(gate_ids::tdg))
    {
      count++;
    }
  });

  return count;
}

int main()
{
	netlist<wn32_op> circuit;    
	decomp_params params;
	params.barenco_controls_threshold = 4;
	params.use_relative_phase = false;
	params.gate_set = gate_set::create(gate_ids::h, gate_ids::t, gate_ids::tdg, gate_ids::cx);

	auto a = circuit.create_qubit();
	auto b = circuit.create_qubit();
	auto c = circuit.create_qubit();
	auto d = circuit.create_qubit();
	auto e = circuit.create_qubit();

	circuit.create_op(gate_lib::ncx, {a,b, c, d}, {e});
	write_utf8(circuit);
	auto dec_circ = decompose(circuit, params);
	write_utf8(dec_circ);

	std::cout << t_count(dec_circ);
}
