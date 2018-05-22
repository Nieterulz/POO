#ifndef USUARIO_PEDIDO_HPP
#define USUARIO_PEDIDO_HPP

#include <map>
#include <set>
#include "pedido.hpp"
#include "usuario.hpp"

class Pedido;

class Usuario_Pedido
{
public:
  typedef std::set<Pedido*> Pedidos;
  typedef std::map<Usuario*,Pedidos> usuario_a_pedido;
  typedef std::map<Pedido*, Usuario*> pedido_a_usuario;
  void asocia(Usuario& U, Pedido& P);
  void asocia(Pedido& P, Usuario& U);
  Pedidos pedidos(Usuario& U){return U_P_[&U];}
  Usuario* cliente(Pedido& P){return P_U_[&P];}
private:
  usuario_a_pedido U_P_;
  pedido_a_usuario P_U_;
};

inline void Usuario_Pedido::asocia(Usuario& U, Pedido& P)
{
  U_P_[&U].insert(&P);
  P_U_[&P] = &U;
}

inline void Usuario_Pedido::asocia(Pedido& P, Usuario& U)
{
  return asocia(U, P);
}

#endif
