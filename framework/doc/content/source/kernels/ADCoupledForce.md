# ADCoupledForce

## Description

`ADCoupledForce` implements a source term within the domain $\Omega$ proportional to a coupled
variable:
\begin{equation}
\underbrace{-\sigma v}_{\textrm{CoupledForce}} + \sum_{i=1}^n \beta_i = 0 \in \Omega,
\end{equation}
where $\sigma$ is a known scalar coefficient, $v$ is a coupled unknown value, and the second term on
the left hand side corresponds to the strong forms of other kernels. In a species transport context,
the value $\sigma$ can be regarded as a reaction rate coefficient.

The weak form, in inner-product notation, is defined as

\begin{equation}
R_i(u_h) = (\psi_i, -\sigma v) \quad \forall \psi_i,
\end{equation}
where $\psi_i$ are the test functions and $u_h \in \mathcal{S}^h$
is the finite element solution of the weak formulation.

## Example Syntax

The kernel block below shows a variable $u$ that is diffusing and being produced at a rate
proportional to the concentration of a variable $v$ which is also diffusing.

!listing test/tests/bcs/coupled_dirichlet_bc/coupled_dirichlet_bc.i
         block=Kernels

!alert note
In this example the input parameter "coef" that corresponds to $\sigma$ is omitted. In this case the
"coef" value defaults to one.

!syntax parameters /Kernels/ADCoupledForce

!syntax inputs /Kernels/ADCoupledForce

!syntax children /Kernels/ADCoupledForce
