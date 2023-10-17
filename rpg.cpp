//Trabalho de Programação orientada a objeto
//
// Obs. O programa deve ser compilado em g++
//

#include <cstdlib>
#include <iostream>
#define MAXPRS 30           //criei com 20
#define EFTMAX 5            //quantidade de efeito que um personagem pode ter
#define tamanhoDoTorneio 16 // pode ser impar, mas deixar par
#define totalDeClasse 6     // atualizar de acordo com quantidade de classes criadas, funciona na hora de dar uma classe a um personagem delcarado sem nenhuma

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
bool veSeTem(int quantidade, int velhoOeste[], int tamanho, int procurado)
{
  int contador = 0;
  for (int cidade = 0; cidade < tamanho; cidade++)
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
  int efeitos[EFTMAX][2];
  double maxVida = 0;
  double vida;
  double atk;
  double def;
  double danoEfetuado = 0;
  int qntTurno = 0;
  int qntEsp = 0;
  int indexDerrotados = 0;
  Personagem *derrotados[20];

public:
  // Get's
  std::string getNome() { return this->nome; }
  std::string getAtkEsp() { return this->atkEsp; }
  std::string getClasse() { return this->classe; }
  int getId() { return this->idPers; }
  double getMaxVida() { return this->maxVida; }
  double getVida() { return this->vida; }
  double getAtk() { return this->atk; }
  double getDef() { return this->def; }
  double getDanoEfetuado() { return this->danoEfetuado; }
  int getQntEsp() { return this->qntEsp; }
  int getQntTurno() { return this->qntTurno; }
  int getEfeitosDuracao(int posicao) { return this->efeitos[posicao][1]; }
  int getIndexDerrotados() { return this->indexDerrotados; }
  Personagem *getDerrotados(int posicao)
  {
    if (posicao < 0 || posicao > sizeof(this->derrotados) ||
        this->derrotados[posicao] == nullptr)
    {
      return nullptr;
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
  void setNome(std::string nome) { this->nome = nome; }
  void setAtkEsp(std::string atkEsp) { this->atkEsp = atkEsp; }
  void setClasse(std::string classe) { this->classe = classe; }
  void setId(int idPers) { this->idPers = idPers; }
  void setMaxVida(double maxVida) { this->maxVida = maxVida; }
  void setVida(double vida) { this->vida = vida; }
  void setAtk(double atk) { this->atk = atk; }
  void setDef(double def) { this->def = def; }
  void setIndexDerrotados(int indexDerrotados) { this->indexDerrotados = indexDerrotados; }
  void setDanoEfetuado(double danoEfetuado) { this->danoEfetuado = danoEfetuado; }
  void setQntEsp(int qntEsp) { this->qntEsp = qntEsp; }
  void setQntTurno(int qntTurno) { this->qntTurno = qntTurno; }
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
    for (int i = 0; i <= EFTMAX; i++)
    {
      if (this->efeitos[i][0] == semEfeito)
      {
        setEfeitos(efeito, i, duracao);
        break;
      }
    }
  }
  void adicionaDanoEfetuado(double dano) { this->setDanoEfetuado(this->getDanoEfetuado() + dano); }
  void adicionaQntEsp() { this->setQntEsp(this->getQntEsp() + 1); }
  void adicionaTurno() { this->setQntTurno(this->getQntTurno() + 1); }
  void fullHeal() { this->setVida(getMaxVida()); }
  void VeAVida()
  {
    if (this->getVida() > this->getMaxVida())
    {
      this->setVida(getMaxVida());
    }
    else if (this->getVida() <= 0)
    {
      this->setVida(0);
    }
  }
  void zerarEfeitos()
  {
    for (int i = 0; i <= EFTMAX; i++)
    {
      setEfeitos(semEfeito, i, -1);
    }
  }
  double DaDano(Personagem *oponente)
  {
    int dado;
    double dano;
    this->adicionaTurno();

    for (int i = 0; i <= EFTMAX; i++)
      switch (this->efeitos[i][0])
      {
      case semEfeito:
        break;
      case curaPassiva:
        setVida(getVida() + (getMaxVida() / 20));
        setEfeitosDuracao(i, getEfeitosDuracao(i) - 1);
        std::cout << this->getNome() << " se curou." << std::endl;
        if (getEfeitosDuracao(i) == 0)
          this->efeitos[i][0] = semEfeito;
        break;
      case sangramento:
        setVida(getVida() - (oponente->getAtk() / 10));
        setEfeitosDuracao(i, getEfeitosDuracao(i) - 1);
        std::cout << this->getNome() << " esta sangrando."
                  << std::endl
                  << (oponente->getAtk() / 10) << " de vida perdida"
                  << std::endl;
        if (getEfeitosDuracao(i) == 0)
          this->efeitos[i][0] = semEfeito;
        break;
      }

    if ((dado = (rand() % 100)) > 20)
    {
      dano = this->getAtaqueNormal(oponente, dado);
      this->adicionaDanoEfetuado(dano);
      if (dano < 0)
      {
        dano = 0;
      }
      return dano;
    }
    else
    {
      dano = this->getAtaqueEspecial(oponente, dado);
      this->adicionaQntEsp();
      this->adicionaDanoEfetuado(dano);
      if (dano < 0)
      {
        dano = 0;
      }
      return dano;
    }
  }
  virtual void mostrar()
  {
    std::cout << "------------------------------------" << std::endl
              << "Id:\t\t" << getId() << std::endl
              << "Nome:\t\t" << getNome() << std::endl
              << "Classe:\t\t" << getClasse() << std::endl
              << "Vida:\t\t" << getVida() << "/" << getMaxVida()
              << std::endl
              << "Atk:\t\t" << letraNoDano(getAtk()) << std::endl
              << "Def:\t\t" << getDef() << std::endl;
  }
  // dano efetuado, vida restante, numero de rounds, atksespeciais
  void estatisticas()
  {
    std::cout << "------------------------------------" << std::endl
              << "Id: \t\t\t" << getId() << std::endl
              << "Nome:\t\t\t" << getNome() << std::endl
              << "Classe:\t\t\t" << getClasse() << std::endl
              << "Vida Restante:\t\t" << getVida() << " de " << getMaxVida()
              << std::endl
              << "Turnos jogados:\t\t" << getQntTurno() << std::endl
              << "Ataque Especial:\t" << getAtkEsp() << std::endl
              << "Vezes Usado:\t\t" << getQntEsp() << std::endl
              << "Dano Total:\t\t" << letraNoDano(getDanoEfetuado())
              << std::endl
              << "------------------------------------" << std::endl;
  }
  Personagem(int id, std::string nomePadrao, double vida, double atk,
             double def)
  {
    setId(id);
    setNome(nomePadrao);
    setAtkEsp("Critico");
    setMaxVida(vida);
    setVida(vida);
    setAtk(atk);
    setDef(def);
    zerarEfeitos();
    // mostrar();
  }
  Personagem() {}
};

class Arcanista : public Personagem
{
private:
  double magia;

public:
  double getMagia() { return this->magia; }
  void setMagia(double magia) { this->magia = magia; }
  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << getAtkEsp() << ": " << this->getMagia() << std::endl;
    return this->getMagia();
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Magia:\t\t" << this->getMagia() << std::endl
              << "------------------------------------" << std::endl;
  }
  Arcanista(int id, std::string nomePadrao, double vida, double atk,
            double def, double magia)
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
    zerarEfeitos();
  }
};
class Monge : public Personagem
{
private:
  double fe;

public:
  double getFe() { return this->fe; }
  void setFe(double fe) { this->fe = fe; }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << getAtkEsp() << ": " << this->getFe() << std::endl;
    setVida(getVida() + getFe());
    return 0;
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Fe:\t\t" << this->getFe() << std::endl
              << "------------------------------------" << std::endl;
  }
  Monge(int id, std::string nomePadrao, double vida, double atk, double def,
        double fe)
  {
    setClasse("Monge");
    this->setAtkEsp("Cura Divina!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(200 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(50 + atk + (double)(rand() % 20));
    setDef(50 + def + (double)(rand() % 20));
    setFe(0 + fe + (double)(rand() % 2));
    zerarEfeitos();
  }
};
class Assassino : public Personagem
{
private:
  double penetracao;

public:
  double getPenetracao() { return this->penetracao; }
  void setPenetracao(double penetracao) { this->penetracao = penetracao; }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << this->getAtkEsp() << ": " << this->getPenetracao()
              << std::endl;
    oponente->adicionaEfeito(sangramento, 3);
    return this->getAtk() - (oponente->getDef() - this->getPenetracao());
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Penetracao:\t" << this->getPenetracao() << std::endl
              << "------------------------------------" << std::endl;
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
    setPenetracao(20 + chanceCritica + (double)(rand() % 20));
    zerarEfeitos();
  }
};
class Druida : public Personagem
{
private:
  double espirito;

public:
  double getEspirito() { return this->espirito; }
  void setEspirito(double espirito) { this->espirito = espirito; }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << this->getAtkEsp() << ": " << this->getEspirito()
              << std::endl;
    oponente->adicionaEfeito(curaPassiva, 2);
    setVida(getVida() + this->getEspirito());
    return 0;
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Espirito:\t" << this->getEspirito() << std::endl
              << "------------------------------------" << std::endl;
  }
  Druida(int id, std::string nomePadrao, double vida, double atk, double def, double espirito)
  {
    setClasse("Druida");
    this->setAtkEsp("Força animal!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(100 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(70 + atk + (double)(rand() % 30));
    setDef(20 + def + (double)(rand() % 10));
    setEspirito(20 + espirito + (double)(rand() % 20));
    zerarEfeitos();
  }
};
class Guerreiro : public Personagem
{
private:
  double sede;

public:
  double getSede() { return this->sede; }
  void setSede(double sede) { this->sede = sede; }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << this->getAtkEsp() << ": " << this->getSede()
              << std::endl;
    oponente->adicionaEfeito(sangramento, 3);
    setVida(getVida() + this->getSede());
    return (this->getAtk() * 1.5) - (oponente->getDef());
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Sede:\t" << this->getSede() << std::endl
              << "------------------------------------" << std::endl;
  }
  Guerreiro(int id, std::string nomePadrao, double vida, double atk, double def, double sede)
  {
    setClasse("Guerreiro");
    this->setAtkEsp("Vamos para a batalha!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(100 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(70 + atk + (double)(rand() % 30));
    setDef(20 + def + (double)(rand() % 10));
    setSede(20 + sede + (double)(rand() % 20));
    zerarEfeitos();
  }
};
class Paladino : public Personagem
{
private:
  double bencao;

public:
  double getBencao() { return this->bencao; }
  void setBencao(double bencao) { this->bencao = bencao; }

  double getAtaqueEspecial(Personagem *oponente, int dado) override
  {
    std::cout << "Dado: " << dado << std::endl
              << this->getAtkEsp() << ": " << this->getBencao()
              << std::endl;
    return this->getVida() - (oponente->getDef() - this->getBencao());
  }
  void mostrar()
  {
    Personagem::mostrar();
    std::cout << "Bencao:\t" << this->getBencao() << std::endl
              << "------------------------------------" << std::endl;
  }
  Paladino(int id, std::string nomePadrao, double vida, double atk, double def, double armadura)
  {
    setClasse("Paladino");
    this->setAtkEsp("Bencao suprema!");
    setId(id);
    setNome(nomePadrao);
    setMaxVida(100 + vida + (double)(rand() % 10));
    setVida(getMaxVida());
    setAtk(70 + atk + (double)(rand() % 30));
    setDef(20 + def + (double)(rand() % 10));
    setBencao(20 + armadura + (double)(rand() % 20));
    zerarEfeitos();
  }
};
enum estado
{
  perdeu = -1,
  lutando = 0,
  vencendo = 1
};
class Torneio
{
private:
  Personagem *personagensDoTorneio[tamanhoDoTorneio] = {nullptr};
  int vencedores[tamanhoDoTorneio] = {0};
  int qntPersonagensDerrotados = 0;
  int histId[MAXPRS] = {0};
  bool resumida;

public:
  void donoDoturnoDestacado(Personagem *dono, Personagem *sub)
  {
    std::cout << "\033[1;29m-> " << dono->getNome()
              << " esta atacando...\033[0m\t" << std::endl;
    std::cout << "\033[1;30m-> " << sub->getNome()
              << " esta esperando...\033[0m\t" << std::endl;
  }
  void resetaVencedor(Personagem *vencedor)
  {
    vencedor->fullHeal();
    vencedor->zerarEfeitos();
  }
  int declaraVitoria(Personagem *vencedor, Personagem *p2)
  {
    vencedor->setDerrotados(p2);
    vencedores[histId[vencedor->getId()]] = vencendo;
    vencedores[histId[p2->getId()]] = perdeu;
    qntPersonagensDerrotados += 1;
    return histId[vencedor->getId()];
  }
  int verificaVitoria(Personagem *p1, Personagem *p2, int turnoAtual)
  {
    if (p2->getVida() <= 0 ||
        (turnoAtual >= 10 &&
         p1->getDanoEfetuado() > p2->getDanoEfetuado()))
    {
      std::cout << "\n\033[3;33m" << p1->getNome()
                << " Ganhou a Batalha\033[0m!" << std::endl;
      return declaraVitoria(p1, p2);
      ;
    }
    else if (p1->getVida() <= 0 ||
             (turnoAtual >= 10 &&
              p2->getDanoEfetuado() > p1->getDanoEfetuado()))
    {
      std::cout << "\n\033[3;33m" << p2->getNome()
                << " Ganhou a Batalha\033[0m!" << std::endl;
      return declaraVitoria(p2, p1);
    }
    else if (turnoAtual >= 10 &&
             p1->getDanoEfetuado() == p2->getDanoEfetuado())
    {
      std::cout << "\n\033[3;33m" << p1->getNome() << " e " << p2->getNome()
                << " Empataram\033[0m!" << p1->getNome() << " Continuara.." << std::endl;
      return declaraVitoria(p1, p2);
    }
    return -1;
  }
  void turno(Personagem *atacante, Personagem *defensor)
  {
    std::string cor = (atacante->getId() % 2 == 0) ? "\033[1;33m" : "\033[1;27m";
    double danoDoTurno = atacante->DaDano(defensor);

    if (danoDoTurno < 0)
    {
      danoDoTurno = 0;
    }

    std::cout << "Nome = " << atacante->getNome()
              << " | Id = " << atacante->getId() << " | Estado = "
              << vencedores[atacante->getId()] << std::endl;

    std::cout << cor << atacante->getNome() << " deu \033[0m\033[1;31m"
              << danoDoTurno << "\033[0m" << cor << " de dano! \033[0m\n"
              << std::endl;

    defensor->setVida(defensor->getVida() - danoDoTurno);
    atacante->VeAVida();
    defensor->VeAVida();
  }
  int luta(Personagem *p1, Personagem *p2)
  {
    int numeroTurno = 0;
    int idVencedor = -1;
    int danoGuardado1 = p1->getDanoEfetuado();
    int danoGuardado2 = p2->getDanoEfetuado();
    p1->setDanoEfetuado(0);
    p2->setDanoEfetuado(0);
    while (p1->getVida() > 0 && p2->getVida() > 0)
    {
      // Turnos
      std::cout << std::endl
                << "\033[1;34m-> Turno " << numeroTurno + 1 << "\033[0m\t"
                << std::endl;
      if (numeroTurno % 2 == 0)
      {
        donoDoturnoDestacado(p1, p2);
        // Tuno P-1
        if (!resumida)
        {
          p1->mostrar();
          p2->mostrar();
          turno(p1, p2);
          getchar();
          // system("cls");
        }
        else
        {
          turno(p1, p2);
        }
      }
      else
      {
        // Turno P-2
        donoDoturnoDestacado(p2, p1);
        if (!resumida)
        {
          p1->mostrar();
          p2->mostrar();
          turno(p2, p1);
          getchar();
          // system("cls");
        }
        else
        {
          turno(p2, p1);
        }
      }
      numeroTurno++;
      if ((idVencedor = verificaVitoria(p1, p2, numeroTurno)) != -1)
      {
        break;
      }
    }

    p1->mostrar();
    p2->mostrar();
    p1->setDanoEfetuado(danoGuardado1 + p1->getDanoEfetuado());
    p2->setDanoEfetuado(danoGuardado2 + p2->getDanoEfetuado());

    if (p1->getId() == idVencedor)
    {
      resetaVencedor(p1);
    }
    else if (p2->getId() == idVencedor)
    {
      resetaVencedor(p2);
    }
    getchar();
    // system("clear");
    return idVencedor;
  }
  void inicia()
  {
    int ultimoPers = 0;
    int idVencedor = -1;
    bool GuardaUm = false;
    for (int i = 0; i < tamanhoDoTorneio; i++)
    {
      vencedores[i] = lutando; // 0 = lutando
    }
    do
    {
      int id = 0;
      for (id = 0; id < tamanhoDoTorneio; id++)
      {
        if (personagensDoTorneio[id])
        {
          if (vencedores[id] != perdeu)
          {
            if (GuardaUm)
            {
              idVencedor = luta(personagensDoTorneio[id],
                                personagensDoTorneio[ultimoPers]);
              GuardaUm = false;
            }
            else if (!GuardaUm)
            {
              ultimoPers = id;
              GuardaUm = true;
            }
          }
        }
      }
    } while (veSeTem(2, vencedores, (sizeof(vencedores) / sizeof(vencedores[0])), vencendo));

    for (int id = 0; id < tamanhoDoTorneio; id++)
    {
      if (id == idVencedor)
      {
        std::cout << "===================================" << std::endl
                  << "------------VENCEDOR---------------" << std::endl
                  << "-----------DO-TORNEIO--------------" << std::endl
                  << "-----------------------------------" << std::endl
                  << "->" << std::endl
                  << "->" << personagensDoTorneio[id]->getNome() << std::endl
                  << "->" << std::endl
                  << "-----------------------------------" << std::endl
                  << "===================================" << std::endl;
        getchar();
        break;
      }
    }
  }
  void distribuiPersonagens(Personagem *todosOsPers[])
  {
    int idNovo = 0;
    int idAntigo = 0;
    bool podeAdicionar = true;
    bool diminui = true;
    int histTemp[tamanhoDoTorneio] = {-1};
    while (idNovo < tamanhoDoTorneio)
    {
      if (todosOsPers[idNovo])
      {
        if (podeAdicionar)
        {
          idAntigo = (rand() % tamanhoDoTorneio);
        }
        for (int a = 0; a <= idNovo; a++)
        {
          if (idAntigo == histTemp[a])
          {
            if (diminui)
            {
              idAntigo--;
              if (idAntigo < 0)
              {
                diminui = false;
              }
              break;
            }
            else if (!diminui)
            {
              idAntigo++;
              break;
            }
            if (idAntigo >= tamanhoDoTorneio)
            {
              podeAdicionar = true;
            }
            podeAdicionar = false;
            break;
          }
        }
        if (podeAdicionar)
        {
          this->personagensDoTorneio[idNovo] = todosOsPers[idAntigo];
          histTemp[idNovo] = idAntigo;
          histId[idAntigo] = idNovo;
          idNovo++;
        }
        podeAdicionar = true;
      }
    }
    getchar();
  }
  Torneio(Personagem *todosOsPers[], bool resumida)
  {
    this->resumida = resumida;
    this->distribuiPersonagens(todosOsPers);
    this->inicia();
  }
};

enum classe
{
  padrao = 0,
  arcanista = 1,
  monge = 2,
  assassino = 3,
  guerreiro = 4,
  paladino = 5,
  druida = 6
};
class JogoRpg
{
private:
  Personagem *pQ[MAXPRS]{nullptr};
  int indexPers = 0;

public:
  Personagem *getPers(int i) { return pQ[i]; }
  void adicionaPers(int qnt, std::string nomePadrao, double vida, double atk, double def, double atkEsp, int c)
  {
    for (int i = 0; i < qnt; i++)
    {
      std::string nomeSubstituto = nomePadrao;
      if (i != 0)
        nomeSubstituto += " " + toString(i);
      switch (c)
      {
      case arcanista:
        pQ[this->indexPers] = new Arcanista(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case monge:
        pQ[this->indexPers] = new Monge(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case assassino:
        pQ[this->indexPers] = new Assassino(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case guerreiro:
        pQ[this->indexPers] = new Guerreiro(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case paladino:
        pQ[this->indexPers] = new Paladino(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      case druida:
        pQ[this->indexPers] = new Druida(indexPers, nomeSubstituto, vida, atk, def, atkEsp);
        break;
      default:
        pQ[this->indexPers] = new Personagem(indexPers, nomeSubstituto, vida, atk, def);
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
      if (i != 0)
        nomeSubstituto += " " + toString(i);
      switch (rand() % totalDeClasse)
      {
      case arcanista: // Classe(id,nome,vida,ataque,defesa,atributoEspecial)
        pQ[this->indexPers] = new Arcanista(indexPers, nomeSubstituto,
                                            (double)(rand() % 30), (double)(rand() % 30),
                                            (double)(rand() % 30), (double)(rand() % 30));
        break;
      case monge:
        pQ[this->indexPers] = new Monge(indexPers, nomeSubstituto,
                                        (double)(rand() % 30), (double)(rand() % 30),
                                        (double)(rand() % 30), (double)(rand() % 30));
        break;
      case assassino:
        pQ[this->indexPers] = new Assassino(indexPers, nomeSubstituto,
                                            (double)(rand() % 30), (double)(rand() % 30),
                                            (double)(rand() % 30), (double)(rand() % 30));
        break;
      case guerreiro:
        pQ[this->indexPers] = new Guerreiro(indexPers, nomeSubstituto,
                                            (double)(rand() % 30), (double)(rand() % 30),
                                            (double)(rand() % 30), (double)(rand() % 30));
        break;
      case druida:
        pQ[this->indexPers] = new Druida(indexPers, nomeSubstituto,
                                         (double)(rand() % 30), (double)(rand() % 30),
                                         (double)(rand() % 30), (double)(rand() % 30));
        break;
      case paladino:
        pQ[this->indexPers] = new Paladino(indexPers, nomeSubstituto,
                                           (double)(rand() % 30), (double)(rand() % 30),
                                           (double)(rand() % 30), (double)(rand() % 30));
        break;
      default:
        pQ[this->indexPers] = new Personagem(indexPers, nomeSubstituto,
                                             (double)(rand() % 30), (double)(rand() % 30),
                                             (double)(rand() % 30));
        break;
      }
      this->indexPers++;
    }
  }
  void adicionaPers(int qnt, std::string nomePadrao, int c)
  {
    for (int i = 0; i < qnt; i++)
    {
      std::string nomeSubstituto = nomePadrao;
      if (i != 0)
        nomeSubstituto += " " + toString(i);
      switch (c)
      {
      case arcanista: // Classe(id,nome,vida,ataque,defesa,atributoEspecial)
        pQ[this->indexPers] =
            new Arcanista(indexPers, nomeSubstituto,
                          (double)(rand() % 30), (double)(rand() % 30),
                          (double)(rand() % 30), (double)(rand() % 30));
        break;
      case monge:
        pQ[this->indexPers] =
            new Monge(indexPers, nomeSubstituto,
                      (double)(rand() % 30), (double)(rand() % 30),
                      (double)(rand() % 30), (double)(rand() % 30));
        break;
      case assassino:
        pQ[this->indexPers] =
            new Assassino(indexPers, nomeSubstituto,
                          (double)(rand() % 30), (double)(rand() % 30),
                          (double)(rand() % 30), (double)(rand() % 30));
        break;
      case paladino:
        pQ[this->indexPers] =
            new Paladino(indexPers, nomeSubstituto,
                         (double)(rand() % 30), (double)(rand() % 30),
                         (double)(rand() % 30), (double)(rand() % 30));
        break;
      case guerreiro:
        pQ[this->indexPers] =
            new Guerreiro(indexPers, nomeSubstituto,
                          (double)(rand() % 30), (double)(rand() % 30),
                          (double)(rand() % 30), (double)(rand() % 30));
        break;
      case druida:
        pQ[this->indexPers] =
            new Druida(indexPers, nomeSubstituto,
                       (double)(rand() % 30), (double)(rand() % 30),
                       (double)(rand() % 30), (double)(rand() % 30));
        break;
      default:
        pQ[this->indexPers] =
            new Personagem(indexPers, nomeSubstituto,
                           (double)(rand() % 30), (double)(rand() % 30),
                           (double)(rand() % 30));
        break;
      }
      this->indexPers++;
    }
  }
  void mostraPers()
  {
    int i = 0;
    while (pQ[i] != nullptr)
    {
      pQ[i]->mostrar();
      i++;
    }
  }
  void mostraNomes()
  {
    int i = 0;
    while (pQ[i] != nullptr)
    {
      std::cout << pQ[i]->getId() << ". " << pQ[i]->getNome() << std::endl;
      i++;
    }
  }

  void mostraDerrotados()
  {
    int i = 0, posicao = 0;
    while (pQ[i] != nullptr)
    {
      if (pQ[i]->getDerrotados(0) != nullptr)
      {
        std::cout << pQ[i]->getNome() << "\033[1;31m Derrotou: \033[0m"
                  << std::endl;
        while (posicao >= 0 && posicao < pQ[i]->getIndexDerrotados() &&
               pQ[i]->getDerrotados(posicao) != nullptr)
        {
          std::cout << pQ[i]->getDerrotados(posicao)->getNome()
                    << std::endl;
          posicao++;
        }
        std::cout << std::endl;
        posicao = 0;
      }
      i++;
    }
  }
  void mostraEstatistica()
  {
    int i = 0;
    while (pQ[i] != nullptr)
    {
      pQ[i]->estatisticas();
      i++;
    }
  }
  void iniciaTorneio(bool resumida)
  {
    Torneio t = Torneio(pQ, resumida);
  }
  void deletaPonteiros()
  {
    for (int i = 0; i < indexPers; i++)
    {
      for (int a = 0; a < pQ[i]->getIndexDerrotados(); a++)
      {
        delete (pQ[i]->getDerrotados(a));
      }
      delete (pQ[i]);
    }
  }
  void menu()
  {
    int entrada;
    std::string nome = "";
    int classe = -1;
    int idDeletar = -1;
    bool sair = false;
    while (!sair)
    {
      std::cout << "O que quer fazer?" << std::endl;
      std::cout << "1. Iniciar Torneio " << std::endl;
      std::cout << "2. Adicionar Personagem" << std::endl;
      std::cout << "3. Mostrar Personagens derrotados" << std::endl;
      std::cout << "4. Mostrar estatisticas" << std::endl;
      std::cout << "5. Mostrar status" << std::endl;
      std::cout << "6. Sair" << std::endl;
      std::cin >> entrada;

      std::cout << std::endl;
      switch (entrada)
      {
      case 1:
        entrada = -1;
        while (entrada < 0 || entrada > 1)
        {
          std::cout << "Luta resumida ou nao? (0 ou 1)" << std::endl;
          std::cin >> entrada;
        }
        iniciaTorneio(entrada);
        break;
      case 2:
        std::cout << "Qual o nome?" << std::endl;
        std::cin >> nome;
        while (classe <= 0 || classe > totalDeClasse)
        {
          std::cout << "Qual a classe?" << std::endl
                    << "1. Arcanista" << std::endl
                    << "2. Monge" << std::endl
                    << "3. Assassino " << std::endl
                    << "4. Guerreiro " << std::endl
                    << "5. Paladino " << std::endl
                    << "6. Druida " << std::endl;

          std::cin >> classe;
        }
        adicionaPers(1, nome, classe);
        std::cout << pQ[indexPers - 1]->getNome() << " Foi adicionado e pode aparecer no torneio!" << std::endl;
        pQ[indexPers - 1]->mostrar();
        classe = -1;
        break;
      case 3:
        mostraDerrotados();
        getchar();
        break;
      case 4:
        mostraEstatistica();
        getchar();
        break;
      case 5:
        mostraPers();
        getchar();
        break;
      case 6:
      sair = true;
        break;
      default:
        break;
      }
    }
  }
  JogoRpg()
  {
    // adicionaPers(Quantidade, "Nome", Vida, Ataque, Defesa,AtributoDeClasse,classe)
    adicionaPers(2, "Blossom", arcanista);
    adicionaPers(2, "Fletcher", paladino);
    adicionaPers(2, "Blubbles", monge);
    adicionaPers(2, "Hermond", druida);
    adicionaPers(2, "Buttercup", assassino);
    adicionaPers(2, "Velma", guerreiro);
    adicionaPers(5, "Elemento X");
    menu();
    deletaPonteiros();
  }
};

int main()
{
  JogoRpg j = JogoRpg();
}
