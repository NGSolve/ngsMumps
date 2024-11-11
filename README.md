# ngsMumps
Interface to parallel sparse direct solver MUMPS


**NGS-User:** You are installing regular releases of NGSolve 

    pip3 install git+https://github.com/NGSolve/ngsMumps.git
    mpirun -np 4  python3 -m ngs_mumps.demos.example1

**NGS-Developer:** You are using pre-releases, or compile NGSolve yourself:

    python -m pip install scikit-build-core pybind11_stubgen toml
    pip3 install --no-build-isolation git+https://github.com/NGSolve/ngsMumps.git
    mpirun -np 4  python3 -m ngs_mumps.demos.example1
