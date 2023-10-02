#include <iostream>
#include <cstdlib>
#define MAXPRS 20
#define totalDeClasse 3
int potencia(int n, int p)
{
  if (p == 0)
  {
    return 1;
  }
  else
  {
    // (5,5) -> (5,4) -> (5,3) -> (5,2) -> (5,1) -> (5,0)
    //   5   *    5   *    5   *    5    *   5    *   1 (p=0 -> 1) = 5^5
    return n * potencia(n, p - 1);
  }
}
bool veSeTem(int velhoOeste[], int procurado, int quantidade)
{
  int contador = 0;
  for (int cidade = 0; cidade < sizeof(velhoOeste); cidade++)
  {
    if (procurado == velhoOeste[cidade])
    {
      contador++;
    }
  }
  if (contador >= quantidade)
    return true;
  else
  {
    return false;
  }
}
std::string toString(int num)
{

  char str[15 + sizeof(char)];
  sprintf_s(str, "%d", num);
  return std::string(str);
}
std::string letraNoDano(double dano)
{
  char str[15 + sizeof(char)];
  if (dano >= 1000 && dano < 1000000)
  {
    dano = dano / 1000;
    sprintf_s(str, "%.2f", dano);
    return std::string(str) + ("K");
  }
  else if (dano >= 1000000 && dano < 1000000000)
  {
    dano = dano / 1000000;
    sprintf_s(str, "%.2f", dano);
    return std::string(str) + ("M");
  }
  sprintf_s(str, "%.2f", dano);
  return str;
}

enum efeitos
{
  semEfeito = 0,
  curaPassiva = 1,
  sangramento = 2,

};
class Personagem
{

private:
  std::string nome = "";
  std::string classe = "Padrao";
  std::string atkEsp = "";
  int idPers;
  int efeitos[5][2];
  double maxVida;
  double vida;
  double atk;
  double def;
  double danoEfetuado = 0;
  int qntTurno = 1;
  int qntEsp = 0;
  int indexDerrotados = 0;
  Personagem *derrotados[20];

public:
  // Get's
  std::string getNome()
  {
    return this->nome;
  }
  std::string getAtkEsp()
  {
    return this->atkEsp;
  }
  std::string getClasse()
  {
    return this->classe;
  }
  int getId()
  {
    return this->idPers;
  }
  double getMaxVida()
  {
    return this->maxVida;
  }
  double getVida()
  {
    return this->vida;
  }
  double getAtk()
  {
    return this->atk;
  }
  double getDef()
  {
    return this->def;
  }
  double getDanoEfetuado()
  {
    return this->danoEfetuado;
  }
  int getQntEsp()
  {
    return this->qntEsp;
  }
  int getQntTurno()
  {
    return this->qntTurno;
  }
  int getEfeitosSize()
  {
    return sizeof(this->efeitos);
  }
  int getEfeitosDuracao(int posicao)
  {
    return this->efeitos[posicao][1];
  }
  int getIndexDerrotados(){
    return this->indexDerrotados;
  }
  Personagem *getDerrotados(int posicao)
  {
    if (posicao < 0 || posicao > sizeof(this->derrotados) || this->derrotados[posicao] == nullptr)
    {
      return NULL;
    }
    else
    {
      return this->derrotados[posicao];
    }
  }
  double getAtaqueNormal(Personagem *oponente, int dado)
  {
    double dano;
    std::cout << "Dado: " << dado << std::endl;
    dano = getAtk() - oponente->getDef();

    return dano;
  }
  virtual double getAtaqueEspecial(Personagem *oponente, int dado)
  {
    std::cout << "Dado: " << dado << " " << getAtkEsp() << std::endl;
    return getAtk() * 1.5;
  }

  // Set's
  void setNome(std::string nome)
  {
    this->nome = nome;
  }
  void setAtkEsp(std::string atkEsp)
  {
    this->atkEsp = atkEsp;
  }
  void setClasse(std::string classe)
  {
    this->classe = classe;
  }
  void setId(int idPers)
  {
    this->idPers = idPers;
  }
  void setMaxVida(double maxVida)
  {
    this->maxVida = maxVida;
  }
  void setVida(double vida)
  {
    this->vida = vida;
  }
  void setAtk(double atk)
  {
    this->atk = atk;
  }
  void setDef(double def)
  {
    this->def = def;
  }
  void setIndexDerrotados(int indexDerrotados){
    this->indexDerrotados = indexDerrotados;
  }
  void setDanoEfetuado(double danoEfetuado)
  {
    this->danoEfetuado = danoEfetuado;
  }
  void setQntEsp(int qntEsp)
  {
    this->qntEsp = qntEsp;
  }
  void setQntTurno(int qntTurno)
  {
    this->qntTurno = qntTurno;
  }
  void setDerrotados(Personagem *d1)
  {
    this->derrotados[this->indexDerrotados] = d1;
    this->indexDerrotados++;
  }
  void setEfeitos(int efeito, int posicao, int duracao)
  {
    this->efeitos[posicao][0] = efeito;
    this->efeitos[posicao][1] = duracao;
  }
  void setEfeitosDuracao(int posicao, int duracao)
  {
    this->efeitos[posicao][1] = duracao;
  }
  void adicionaEfeito(int efeito, int duracao)
  {
    for (int i = 0; i < getEfeitosSize(); i++)
    {
      if (this->efeitos[i][0] == semEfeito)
      {
        setEfeitos(efeito, i, duracao);
        break;
      }
    }
  }
  void adicionaDanoEfetuado(double dano)
  {
    this->setDanoEfetuado(this->getDanoEfetuado() + dano);
  }
  void adicionaQntEsp()
  {
    this->setQntEsp(this->getQntEsp() + 1);
  }
  void adicionaTurno()
  {
    this->setQntTurno(this->getQntTurno() + 1);
  }
  void fullHeal()
  {
    this->setVida(getMaxVida());
  }
  double DaDano(Personagem *oponente)
  {
    int dado;
    double dano;
    this->adicionaTurno();

    for (int i = 0; i <= getEfeitosSize(); i++)
      switch (this->efeitos[i][0])
      {
      case semEfeito:
        break;
      case curaPassiva:
        setVida(getVida() + (getMaxVida() / 20));
        setEfeitosDuracao(i, getEfeitosDuracao(i) - 1);
        this->efeitos[i][0] = semEfeito;
        break;
      case sangramento:
        setVida(getVida() - (oponente->getAtk() / 10));
        setEfeitosDuracao(i, getEfeitosDuracao(i) - 1);
        this->efeitos[i][0] = semEfeito;
        break;
      }
    if ((dado = (rand() % 100)) > 5)
    {
      dano = getAtaqueNormal(oponente, dado);
      adicionaDanoEfetuado(dano);
      return dano;
    }
    else
    {
      dano = getAtaqueEspecial(oponente, dado);
      adicionaQntEsp();
      adicionaDanoEfetuado(dano);
      return dano;
    }
  }
  void mostrar()
  {
    std::cout << "------------------------------------" << std::endl
              << "Id:\t\t" << getId() << std::endl
              << "Nome:\t\t" << getNome() << std::endl
              << "Classe:\t\t" << getClasse() << std::endl
              << "Vida:\t\t" << getVida() << "/" << getMaxVida() << std::endl
              << "Atk:\t\t" << letraNoDano(getAtk()) << std::endl
              << "Def:\t\t" << getDef() << std::endl
              << "------------------------------------" << std::endl;
  }
  // dano efetuado, vida restante, numero de rounds, atksespeciais
  void estatisticas()
  {
    std::cout << "------------------------------------" << std::endl
              << "Id: \t\t\t" << getId() << std::endl
              << "Nome:\t\t\t" << getNome() << std::endl
              << "Classe:\t\t\t" << getClasse() << std::endl
              << "Vida Restante:\t\t" << getVida() << " de " << getMaxVida() << std::endl
              << "Turnos jogados:\t\t" << getQntTurno() << std::endl
              << "Ataque Especial:\t" << getAtkEsp() << std::endl
              << "Vezes Usado:\t\t" << getQntEsp() << std::endl
              << "Dano Total:\t\t" << letraNoDano(getDanoEfetuado()) << std::endl
              << "------------------------------------" << std::endl;
  }
  Personagem(int id, std::string nomePadrao, double vida, double atk, double def)
  { 
    setId(id);
    setNome(nomePadrao);
    setAtkEsp("Critico");
    setMaxVida(vida);
    setVida(vida);
    setAtk(atk);
    setDef(def);
    for (int i = 0; i <= getEfeitosSize(); i++)
    {
      adicionaEfeito(semEfeito, -1);
    }
    // mostrar();
  }
  Personagem()
  {
  }
};

class Arcanista : public Personagem
{
private:
  double magia;

public:
  double getMagia()
  {
    return this->magia;
  }
  void setMagia(double magia)
  {
    this->magia = magia;
  }
  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << getAtkEsp() << ": " << this->getMagia() << std::endl;
    return this->getMagia();
  }

  Arcanista(int id, std::string nomePadrao, double vida, double atk, double def, double magia)
  {
    setClasse("Arcanista");
    setAtkEsp("Bola De Fogo!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(50 + vida + (double)(rand() % 20));
    setVida(getMaxVida());
    setAtk(20 + atk + (double)(rand() % 20));
    setDef(20 + def + (double)(rand() % 20));
    setMagia(20 + magia + (double)(rand() % 100));
  }
};
class Monge : public Personagem
{
private:
  double fe;

public:
  double getFe()
  {
    return this->fe;
  }
  void setFe(double fe)
  {
    this->fe = fe;
  }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << getAtkEsp() << ": " << this->getFe() << std::endl;
    if (getVida() + getFe() >= getMaxVida())
    {
      setVida(getMaxVida());
    }
    else
    {
      setVida(getVida() + getFe());
    }
    return 0;
  }

  Monge(int id, std::string nomePadrao, double vida, double atk, double def, double fe)
  { 
    setClasse("Monge");
    this->setAtkEsp("Cura Divina!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(200 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(50 + atk + (double)(rand() % 20));
    setDef(50 + def + (double)(rand() % 20));
    setFe(20 + fe + (double)(rand() % 20));
  }
};
class Assassino : public Personagem
{
private:
  double chanceCritica;

public:
  double getChanceCritica()
  {
    return this->chanceCritica;
  }
  void setChanceCritica(double chanceCritica)
  {
    this->chanceCritica = chanceCritica;
  }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << getAtkEsp() << ": " << this->getChanceCritica() << std::endl;
    oponente->adicionaEfeito(sangramento, 3);
    return 0;
  }

  Assassino(int id, std::string nomePadrao, double vida, double atk, double def, double chanceCritica)
  {
    setClasse("Assassino");
    this->setAtkEsp("Sangre!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(100 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(70 + atk + (double)(rand() % 30));
    setDef(20 + def + (double)(rand() % 10));
    setChanceCritica(20 + chanceCritica + (double)(rand() % 20));
  }
};
/*******************************
#define FelipeLilli Owner (kekw)
********************************/
enum estado
{
  perdeu = -1,
  lutando = 0,
  vencendo = 1
};
enum classe
{
  padrao = 0,
  arcanista = 1,
  monge = 2,
  assassino = 3
};
class JogoRpg
{
private:
  Personagem *pQ[MAXPRS];
  int indexPers = 0;
  int qntPersonagensDerrotados = 0;
  int vencedores[MAXPRS];
  bool resumida = true;

public:
  Personagem *getPers(int i)
  {
    return pQ[i];
  }
  void adicionaPers(int qnt, std::string nomePadrao, double vida, double atk, double def, double atkEsp, classe c)
  {
    for (int i = 0; i < qnt; i++)
    {
      std::string nomeSubstituto = nomePadrao;
      nomeSubstituto += " " + toString(i);
      switch (c)
      {
      case padrao:
        pQ[this->indexPers] = new Personagem(indexPers, nomeSubstituto, vida, atk, def);
        break;
      case arcanista:
        pQ[this->indexPers] = new Arcanista(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case monge:
        pQ[this->indexPers] = new Monge(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case assassino:
        pQ[this->indexPers] = new Assassino(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      }
      this->indexPers++;
    }
  }
  void adicionaPers(int qnt, std::string nomePadrao)
  {

    for (int i = 0; i < qnt; i++)
    {
      std::string nomeSubstituto = nomePadrao;
      nomeSubstituto += " " + toString(i);
      switch (rand() % totalDeClasse)
      {
      case arcanista: // Classe(id,nome,vida,ataque,defesa,atributoEspecial)
        pQ[this->indexPers] = new Arcanista(indexPers, nomeSubstituto, (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30));
        break;
      case monge:
        pQ[this->indexPers] = new Monge(indexPers, nomeSubstituto, (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30));
        break;
      case assassino:
        pQ[this->indexPers] = new Assassino(indexPers, nomeSubstituto, (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30), (double)(rand() % 30));
        break;
      }
      this->indexPers++;
    }
  }
  void mostraPers()
  {
    int i = 0;
    while (pQ[i] != NULL)
    {
      pQ[i]->mostrar();
      i++;
    }
  }

  void mostraDerrotados()
  {
    int i = 0, posicao = 0;
    while (pQ[i] != NULL)
    {
      std::cout << pQ[i]->getNome() << "\033[1;31m Derrotou: \033[0m";
      while (posicao >= 0 && posicao <= pQ[i]->getIndexDerrotados())
      {
        std::cout << pQ[i]->getDerrotados(posicao)->getNome() << std::endl;
        posicao++;
      }
      posicao = 0;
      i++;
    }
  }
  void mostraEstatistica()
  {
    int i = 0;
    while (pQ[i] != NULL)
    {
      pQ[i]->estatisticas();
      i++;
    }
  }
  int verificaVitoria(Personagem *atacante, Personagem *defensor)
  {
    if (defensor->getVida() <= 0)
    {
      defensor->setVida(0);
      std::cout << "\033[3;33m" << atacante->getNome() << " Ganhou a Batalha\033[0m!" << std::endl;
      atacante->setDerrotados(defensor);

      vencedores[atacante->getId()] = vencendo;
      atacante->fullHeal();
      vencedores[defensor->getId()] = perdeu;
      qntPersonagensDerrotados += 1;
      return atacante->getId();
    }
    return -1;
  }
  void turno(Personagem *atacante, Personagem *defensor)
  {
    std::string cor;
    if (atacante->getId() % 2 == 0)
    {
      cor = "\033[1;33m";
    }
    else
    {
      cor = "\033[1;27m";
    }
    double danoDoTurno = atacante->DaDano(defensor);
    if (danoDoTurno < 0)
    {
      danoDoTurno = 0;
    }
    std::cout << cor << atacante->getNome() << " deu \033[0m\033[1;31m" << danoDoTurno << "\033[0m" << cor << " de dano! \033[0m" << std::endl;
    defensor->setVida(defensor->getVida() - danoDoTurno);
  }

  int lutaMaximizada(Personagem *p1, Personagem *p2)
  {
    int numeroTurno = 0;
    int idVencedor = -1;
    while (p1->getVida() > 0 && p2->getVida() > 0)
    {
      // Turnos
      if (numeroTurno < 10)
      {
        std::cout << std::endl
                  << "\033[1;34m--->Turno: " << numeroTurno + 1 << "\033[0m\t" << std::endl;
        if (numeroTurno % 2 == 0)
        {
          // Tuno P-1
          std::cout << "Nome = " << p1->getNome() << " | Id = " << p1->getId() << " | Estado = " << vencedores[p1->getId()] << std::endl;
          turno(p1, p2);
          if ((idVencedor = verificaVitoria(p1, p2)) != -1)
          {
            break;
          }
        }
        else
        {
          // Turno P-2
          std::cout << "Nome = " << p2->getNome() << " | Id = " << p2->getId() << " | Estado = " << vencedores[p2->getId()] << std::endl;
          turno(p2, p1);
          if ((idVencedor = verificaVitoria(p2, p1)) != -1)
          {
            break;
          }
        }
        p1->mostrar();
        p2->mostrar();
        getchar();
        system("cls");
        numeroTurno++;
      }
      else
      {

        if (p1->getDanoEfetuado() > p2->getDanoEfetuado())
        {
          std::cout << "\033[3;33m" << p1->getNome() << " Ganhou a Batalha\033[0m!" << std::endl;
          p1->setDerrotados(p2);

          vencedores[p1->getId()] = vencendo;
          p1->fullHeal();
          vencedores[p2->getId()] = perdeu;
          qntPersonagensDerrotados += 1;
          idVencedor = p1->getId();
          break;
        }
        else if (p2->getVida() > p1->getVida())
        {
          std::cout << "\033[3;33m" << p2->getNome() << " Ganhou a Batalha\033[0m!" << std::endl;
          p2->setDerrotados(p1);

          vencedores[p2->getId()] = vencendo;
          p2->fullHeal();
          vencedores[p2->getId()] = perdeu;
          qntPersonagensDerrotados += 1;
          idVencedor = p2->getId();
          break;
        }
      }
    }
    p1->mostrar();
    p2->mostrar();
    return idVencedor;
  }
  int lutaMinimizada(Personagem *p1, Personagem *p2)
  {
    int numeroTurno = 0;
    int idVencedor = -1;
    std::cout << "\033[1;30m->P1: " << p1->getNome() << "\033[0m\t" << std::endl;
    std::cout << "\033[1;29m->P2: " << p2->getNome() << "\033[0m\t" << std::endl;
    while (p1->getVida() > 0 && p2->getVida() > 0)
    {
      // Turnos
      if (numeroTurno < 10)
      {
        std::cout << "\033[1;34m--->Turno: " << numeroTurno + 1 << "\033[0m\t" << std::endl;
        if (numeroTurno % 2 == 0)
        {
          // Tuno P-1
          std::cout << "Nome = " << p1->getNome() << " | Id = " << p1->getId() << " | Estado = " << vencedores[p1->getId()] << std::endl;
          turno(p1, p2);
          if ((idVencedor = verificaVitoria(p1, p2)) != -1)
          {
            break;
          }
        }
        else
        {
          // Turno P-2
          std::cout << "Nome = " << p2->getNome() << " | Id = " << p2->getId() << " | Estado = " << vencedores[p2->getId()] << std::endl;
          turno(p2, p1);
          if ((idVencedor = verificaVitoria(p2, p1)) != -1)
          {
            break;
          }
        }
      }
      else
      {
        if (p1->getDanoEfetuado() > p2->getDanoEfetuado())
        {
          idVencedor = p1->getId();
          std::cout << "\033[3;33m" << p1->getNome() << " Ganhou a Batalha\033[0m!" << std::endl;
          p1->setDerrotados(p2);

          vencedores[p1->getId()] = vencendo;
          p1->fullHeal();
          vencedores[p2->getId()] = perdeu;
          qntPersonagensDerrotados += 1;
          break;
        }
        else if (p2->getVida() > p1->getVida())
        {
          idVencedor = p2->getId();
          std::cout << "\033[3;33m" << p2->getNome() << " Ganhou a Batalha\033[0m!" << std::endl;
          p2->setDerrotados(p1);

          vencedores[p2->getId()] = vencendo;
          p2->fullHeal();
          vencedores[p2->getId()] = perdeu;
          qntPersonagensDerrotados += 1;
          break;
        }
      }
      numeroTurno++;
    }
    getchar();
    return idVencedor;
  }

  void torneio()
  {
    int sub = 0;
    int idVencedor = -1;
    bool t = false;
    for (int i = 0; i < MAXPRS; i++)
    {
      vencedores[i] = lutando; // 0 = lutando
    }
    // x < numeroDeAndares
    do
    {
      for (int i = 0; i < MAXPRS; i++)
      {
        if (vencedores[i] == vencendo || vencedores[i] == lutando && pQ[i] != NULL)
        {
          if (t)
          {
            if (resumida)
            {
              idVencedor = lutaMinimizada(pQ[i], pQ[sub]);
            }
            else
            {
              idVencedor = lutaMaximizada(pQ[i], pQ[sub]);
            }
            t = false;
          }
          else if (!t)
          {
            sub = i;
            t = true;
          }
        }
      }
    } while (veSeTem(vencedores, vencendo, 2));

    for (int y = 0; y < MAXPRS; y++)
    {
      if (pQ[y]->getId() == idVencedor)
      {
        std::cout
            << "===================================" << std::endl
            << "------------VENCEDOR---------------" << std::endl
            << "-----------DO-TORNEIO--------------" << std::endl
            << "-----------------------------------" << std::endl
            << "->" << std::endl
            << "->" << pQ[y]->getNome() << std::endl
            << "->" << std::endl
            << "-----------------------------------" << std::endl
            << "===================================" << std::endl;
        getchar();
        break;
      }
    }
  }

  void deletaPonteiros()
  {
    for (int i = 0; i < indexPers; i++)
    {
      delete (pQ[i]);
    }
  }
};

int main()
{

  JogoRpg j = JogoRpg();

  //  j.adicionaPers(Quantidade, "Nome", Vida, Ataque, Defesa,AtributoDeClasse,classe)
  // j.adicionaPers(2, "Trippo", 150, 30, 0, 0, padrao);
  j.adicionaPers(1, "Brigadeiro");
  j.adicionaPers(1, "Negrinho");
  j.torneio();
  // j.luta(j.getPers(0), j.getPers(1));
  j.mostraDerrotados();
  getchar();
  j.mostraEstatistica();
  getchar();
  j.mostraPers();
  getchar();
  j.deletaPonteiros();
}
