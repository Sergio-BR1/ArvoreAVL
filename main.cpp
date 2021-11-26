
#include <iostream>

class no {
	private:
		int num;
		int bal;
		no* esq;
		no* dir;
		no* pai;
	public:
		no(int n) {
			num = n;
			pai =
			esq = 
			dir = NULL;
		}

	//Os métodos sets são usados para definir valor de uma variável do nó e os gets para retornar os valores
	
	void balEsq() { //Se um nó vai à esquerda do nó atual, o fator de balanceamento aumenta em 1
		bal++;
	}

	void balDir() { //Se um nó vai à direita do nó atual, o fator de balanceamento diminui em 1
		bal--;
	}

	int getBal() {
		return bal;
	}

	void setPai(no* p) {
		pai = p;
	}

	no* getPai() {
		return pai;
	}

	void setEsq(no* esquerdo) {
		esq = esquerdo;
	}

	void setDir(no* direito) {
		dir = direito;
	}

	no* getEsq() {
		return esq;
	}

	no* getDir() {
		return dir;
	}

	no** getEndEsq() {
		return &esq;
	}

	no** getEndDir() {
		return &dir;
	}

	no** getEndPai() {
		return &pai;
	}

	void setNum(int n) {
		num = n;
	}

	int getNum() {
		return num;
	}
};

class arvore {
	private:
		no* raiz;
		
	public:
		arvore() {
			raiz = NULL;
		}

		void setRaiz(no* r) {
			raiz = r;
		}

		no* getRaiz() {
			return raiz;
		}

		void insereNo(int n) { //Função auxiliar, faz a inserção sem que precise fazer uso direto da raiz no main e verifica se o valor já existe na árvore
			if (buscaVal(n)) {
				std::cout << "Erro, valor já existe na árvore" << std::endl;
				return;
			}	
			insereNoRec(n, &raiz, raiz);
		}


		void insereNoRec(int n, no** r, no* b) {
			if ((*r) == NULL) { //Se a raiz da sub-árvore é vazia, insere o nó
				no* novoNo = new no(n);
				(*r) = novoNo;
				if ((*r) != raiz) { 
					(*r)->setPai(b); //Se r for diferente da raiz, seta b (Nó acima dele) como seu pai
					if ((*r)->getNum() < b->getNum()) {  // Se r for menor que seu pai, seta r como filho esquerdo
						b->setEsq((*r));
					}
					else //Do contrário, seta como filho direito
						b->setDir((*r));
				}
				
				//std::cout << (*r)->getNum() << std::endl;
				balanc((*r));
				return;
			}

			//Caso contrário, faz a chamada recursiva para a esquerda ou direita
			else if((*r)->getNum() > n) {
				(*r)->balEsq();
				return insereNoRec(n, (*r)->getEndEsq(), (*r));
			}

			else {
				(*r)->balDir();
				return insereNoRec(n, (*r)->getEndDir(), (*r));
			}

		}


		no* buscaNo (int n) { //Função auxiliar, com mesmo objetivo da insereNo
			return (buscaNoRec(n, raiz));
		}


		no* buscaNoRec(int n, no* r) { 
			if (r == NULL) //Se r chegar a uma parte nula, o número não está presente na árvore
				return  NULL;

			if (r->getNum() == n) //Se o número está presente, retorna seu endereço
				return r;

			if (r->getNum() > n) //Do contrário, vai para a esquerda ou direita, avaliando se é maior ou menor do que o nó atual
				return buscaNoRec(n, r->getEsq());
			else 
				return buscaNoRec(n, r->getDir());
		}

		bool buscaVal(int n) { //Busca por valor auxiliar, mesma lógica das auxiliares acima
			return buscaValRec(n, raiz);
		}


		bool buscaValRec(int n, no* r) { //Busca por valor, retorna só se o número está ou não presente
			if (r == NULL) //Caso chegue em lugar nulo, o número não existe
				return  false;

			if (r->getNum() == n) //Se encontrar, retorna verdadeiro
				return true;

			if (r->getNum() > n) //Vai para a esquerda ou direito, depois de avaliar se o número buscado é maior ou menor que o do nó atual
				return buscaValRec(n, r->getEsq());
			else 
				return buscaValRec(n, r->getDir());
		}


		bool removeNo (int n) { 
			no* aux = buscaNo(n); // busca o nó a ser removido
			if (aux == NULL) //Caso não existe nó com o número informado, retorna falso
				return false;
			return removeNoRec(aux); //Do contrário, chama a função de remoção
		}


		bool removeNoRec(no* r) {

			if (r->getEsq() == NULL && r->getDir() == NULL) { //Se o nó não tem filhos, remove normalmente
				delete r;
				r = NULL;
				return true;
			}

			if (r->getEsq()!= NULL && r->getDir() == NULL) { //Caso o nó só tenha filho esquerdo
				if (r != raiz) { //Caso o nó não seja a raiz
					no* aux = r->getPai();	
					if (aux->getEsq() == r) { //Se a ser removido for o esquerdo de seu pai, seta seu filho como filho esquerdo do avô
						aux->setEsq(r->getEsq());
					}
					else { //Do contrário, seta o filho como filho direito do avô
						aux->setDir(r->getEsq());
					}
					delete r; //Deleta o nó
				}
				else { //Caso seja a raiz, seta a raiz para o novo nó e exclui o atual
					raiz = r->getEsq();
					delete r;
				}
				return true; //Indica que que nó foi removido
			}
			if (r->getEsq()== NULL && r->getDir() != NULL) { //Caso o nó a ser removido só tenha filho direito, faz operações análogas ao do caso acima
				if (r != raiz) {
					no* aux = r->getPai();	
					if (aux->getEsq() == r) {
						aux->setEsq(r->getDir());
					}
					else {
						aux->setDir(r->getDir());
					}
					delete r;
				}
				else {
					raiz = (r->getDir());
					delete r;
				}
				return true;
			}


			else { //Caso o nó tenha dois filhos, encontra o mais à esquerda do lado direito para fazer substituição
				no* aux = menorDir(r, r->getPai());
				r->setNum(aux->getNum());
				removeNoRec(aux);
				return true;
			}
		}


		no* menorDir(no* atual, no* pai) { //Função utilizada para encontrar o nó mais à esquerda do lado direito de um nó com 2 filhos, que precisa ser removido. Viaja sempre à esquerda até encontrar o menor.
			if (atual->getEsq() == NULL) 
				return atual;

			return menorDir(atual->getEsq(), atual);
		}


		void rotacao_sd(no* r) { //Rotação simples à direita
			no* aux = r->getEsq();
			if (r != raiz)
				r->getPai()->setEsq(aux); //Coloca o nó esquerdo do nó desequilibrado na posição esquerda de seu pai
			else 
				raiz = aux;
			
			r->setEsq(aux->getDir()); //Coloca o nó direito do antigo esquerdo de r na esquerda dele
			aux->setDir(r); //coloca r na direita de seu antigo nó esquerdo
			return;

		}


			void rotacao_se(no* r) { //Rotação simples à esquerda
			no* aux = r->getDir();
			if (r != raiz)
				r->getPai()->setDir(aux); //Coloca o nó direito do nó desequilibrado na posição direita de seu pai
			else 
				raiz = aux;
			r->setDir(aux->getEsq()); //Coloca o nó esquerdo do antigo direito de r na direita dele
			aux->setEsq(r); //coloca r na esquerda de seu antigo nó direito
			
			return;
		}


		void rotacao_dd (no* r, no* folha) { //rotação dupla à direita
			no* aux = folha->getPai();
			aux->getPai()->setEsq(folha);
			folha->setEsq(aux);
			aux->setDir(NULL);
			rotacao_sd(r);
		}


		void rotacao_de (no* r, no* folha) {
			no* aux = folha->getPai();
			aux->getPai()->setDir(folha);
			folha->setDir(aux);
			aux->setEsq(NULL);
			rotacao_se(r);
		}

	/*	no* buscaMinEsq(no *r) { //Encontra a folha da árvore do lado esquerdo
			if (r->getEsq() == NULL && r->getDir() == NULL)
				return r;
			if (r->getEsq())
				return buscaMinEsq(r->getEsq());
			
			return buscaMinEsq(r->getDir());
		}

		no* buscaMinDir(no *r) { //Encontra a folha da árvore do lado direito
			if (r->getEsq() == NULL && r->getDir() == NULL)
				return r;
			if (r->getDir())
				return buscaMinDir(r->getDir());
			
			return buscaMinDir(r->getEsq());
		} */

		void balanc(no* mBaixo) { //Pega o último nó inserido
			std::cout << mBaixo->getNum() << std::endl;
			if (mBaixo == raiz || mBaixo->getPai() == NULL) {//Caso seja raiz ou o pai ou avô não existam, não tem necessidade de fazer operação
				return;
			}
			no* p = mBaixo->getPai(); //Pai do nó inserido
			no* avo;
			if (p->getPai())
				avo = p->getPai(); //Avô do nó inserido
			else {
				return;
			}			
			if (fatorBal(avo) > 1) { //Árvore pendendo para a esquerda
				if (mBaixo == p->getDir()) //Se o nó mais baixo está à direita, faz a rotação dupla direita
					rotacao_dd(avo, mBaixo);
				else //Do contrário, faz a rotação simples direita
					rotacao_sd(avo);
			}
			if (fatorBal(avo) < 1 ) { //Análogo ao if acima
				if (mBaixo == p->getEsq())
					rotacao_de(avo, mBaixo);
				else
					rotacao_se(avo);
			}
			balanc(mBaixo->getPai());
		}


		int fatorBal(no* r) {
			int f = 0;
			if (r->getEsq()) {
				f = f + altura(r->getEsq());
			}
			if (r->getDir()) {
				f = f - altura(r->getDir());
			}
			return f;
		}


		int altura (no* r) {
			int altEsq = 0;
			int altDir = 0;

			if (r->getEsq())
				altEsq = altura(r->getEsq());
			if (r->getDir())
				altDir = altura(r->getDir());

			return max(altEsq, altDir) +1;

		}


		int max(int a, int b) { //retorna o maior número
			if (a > b)
				return a;
			else
				return b;
		}
		
};

int main() {
	arvore avl;
	avl.insereNo(50);
	avl.insereNo(40);
	no* aux = avl.buscaNo(40);
	std::cout << aux->getPai()->getNum() << std::endl;
	avl.insereNo(60);
	avl.insereNo(30);
	avl.insereNo(55);
	avl.insereNo(20);
	//std::cout << avl.altura(avl.getRaiz()) << std::endl;

	if (avl.buscaNo(30))
		std::cout << "Encontrado" << std::endl;
	if (avl.removeNo(30))
		std::cout << "Removido" << std::endl;
	
	if (!avl.buscaNo(30))
		std::cout << "Não encontrado" << std::endl;

	

	
} 