#include "cliente.hpp"
#include "funcionario.hpp"
#include "cliente.hpp"

class cadastro{
  
  vector<cliente> cliente;
  vector<funcionario> funcionario;
  vector<onibus> onibus;
 
  
  public:
  
  cadastro();
  void adicionarFuncionario();
  void adicionarCliente();
  void adicionarOnibus();
  
};
