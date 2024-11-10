# mpirun -np 4 python example1.py

from mpi4py import MPI
from ngsolve import *

import ngs_mumps
from ngsolve.krylovspace import CGSolver



comm = MPI.COMM_WORLD
ngmesh = unit_square.GenerateMesh(maxh=0.1, comm=comm)

for l in range(3):
    ngmesh.Refine()
mesh = Mesh(ngmesh)

fes = H1(mesh, order=2, dirichlet=".*")
u,v = fes.TnT()
a = BilinearForm(grad(u)*grad(v)*dx).Assemble()
f = LinearForm(1*v*dx).Assemble()

gfu = GridFunction(fes)

inv = a.mat.Inverse(freedofs=fes.FreeDofs(), inverse="mumps")
gfu.vec.data = inv * f.vec

printonce("ip = ", InnerProduct(gfu.vec, f.vec))

