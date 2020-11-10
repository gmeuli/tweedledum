#pragma once

#include "../gates/gate.hpp"

#include <cassert>

namespace tweedledum {

/*! \brief Writes network in ProjecQ format into output stream
 *
 * An overloaded variant exists that writes the network into a file.
 *
 * \param network Network
 * \param os Output stream
 */
template<typename Network>
void write_qsharp( Network const& ntk, std::ostream& os, std::string const& funcname)
{
  os << "namespace AffineCosts\n{\n\topen Microsoft.Quantum.Canon;\n\topen Microsoft.Quantum.Intrinsic;\n\topen Microsoft.Quantum.Arrays;\n";
  os << fmt::format("\n\toperation {}(): Unit\n", funcname ) ;
  os << "\t{\n";
  os << fmt::format("\t\tusing (qs = Qubit[{}])\n", ntk.num_qubits());
  os << "\t\t{\n";

  using op_type = typename Network::op_type;
  ntk.foreach_op([&](op_type const& op) {
    os << "\t\t\t";
		switch (op.id()) {
		case gate_ids::h:
			os << fmt::format("H (qs[{}]);\n", op.target());
			break;

		case gate_ids::x:
			os << fmt::format("X (qs[{}]);\n", op.target());
			break;

		case gate_ids::y:
			os << fmt::format("Y (qs[{}]);\n", op.target());
			break;

		case gate_ids::z:
			os << fmt::format("Z (qs[{}]);\n", op.target());
			break;

		case gate_ids::s:
			os << fmt::format("S (qs[{}]);\n", op.target());
			break;

		case gate_ids::sdg:
			os << fmt::format("Adjoint S (qs[{}]);\n", op.target());
			break;

		case gate_ids::t:
			os << fmt::format("T (qs[{}]);\n", op.target());
			break;

		case gate_ids::tdg:
			os << fmt::format("Adjoint T (qs[{}]);\n", op.target());
			break;

		case gate_ids::cx:
		  os << fmt::format("CNOT ");
			op.foreach_control([&](wire::id c) {
				os << fmt::format(" (qs[{}], ", c);
			});
			os << fmt::format(" qs[{}]);\n", op.target());
			break;
		case gate_ids::ncx:
      if(op.num_controls() == 2)
      {
        os << fmt::format("CNOT ");
			  op.foreach_control([&](wire::id c) {
				  os << fmt::format(" (qs[{}] , ", c);
			  });
			  os << fmt::format(" qs[{}]);\n", op.target());
      }
      else
      {
        os << "GATE NON SUPPORTED\n";
      }
			break;

		case gate_ids::cy:
			os << fmt::format("Y");
			op.foreach_control([&](wire::id c) {
				os << fmt::format(" (qs[{}], ", c);
			});
			os << fmt::format(" qs[{}]);\n", op.target());
			break;

		case gate_ids::cz:
			os << fmt::format("Z");
			op.foreach_control([&](wire::id c) {
				os << fmt::format(" (qs[{}], ", c);
			});
			os << fmt::format(" qs[{}]);\n", op.target());
			break;

		default:
			break;
		}
	});

  os << "\n\t\t}\n\t}\n}\n";

}

template<class Network>
void write_qsharp( Network const& rnet, std::string const& filename, std::string const& funcname = "" )
{
  std::ofstream os( filename.c_str(), std::ofstream::app );
  write_qsharp( rnet, os, funcname );
  os.close();
}
}//TWEEDLEDUM