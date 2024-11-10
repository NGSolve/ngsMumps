#include <comp.hpp>
#include <python_comp.hpp>

#include "mumpsinverse.hpp"


using namespace ngla;

shared_ptr<BaseMatrix> CreateInverse (shared_ptr<BaseMatrix> mat, shared_ptr<BitArray> freedofs)
{
  cout << IM(0) << "create mumps inverse" << endl;

  if (auto parmat = dynamic_pointer_cast<ParallelMatrix> (mat))
    {
      auto pardofs = parmat->GetParallelDofs();
      auto locmat = dynamic_pointer_cast<BaseSparseMatrix> (parmat->GetMatrix());
      
      return make_shared<ParallelMumpsInverse<double>>(*locmat,
                                                       freedofs, nullptr, pardofs, false);
    }

  if (auto sparsemat = dynamic_pointer_cast<SparseMatrix<double>> (mat))
    {
      return make_shared<MumpsInverse<double>>(*sparsemat,
                                               freedofs, nullptr, false);
    }
  throw Exception("mumpsinverse - don't know how to invert matrix of type ",
                  typeid(*mat).name());
}


PYBIND11_MODULE(ngs_mumps, m) {
  cout << "Loading ngsMumps solvers" << endl;

  BaseMatrix::RegisterInverseCreator("mumps", CreateInverse);
}
