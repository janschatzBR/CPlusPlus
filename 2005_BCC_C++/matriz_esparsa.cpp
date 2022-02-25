#include<cassert>
#include<stdlib.h>
#include<iostream>
using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;

class matriz_esparsa {
		struct no;
	    typedef no* pontno;
	    struct no {
		    float valor;
		    int n_linha, n_col;
		    pontno no_col, no_linha;
		};
	    pontno inicio_linha, inicio_col, fim;
	    int diml, dimc;
	    void insere(float, int, int);
    public:
		matriz_esparsa(int, int);
		friend istream & operator>>(istream&, matriz_esparsa&);
	    friend ostream & operator<<(ostream &, const matriz_esparsa&);
        matriz_esparsa operator+(matriz_esparsa &);
		matriz_esparsa operator-(matriz_esparsa &);
        matriz_esparsa operator*(matriz_esparsa &);

};


matriz_esparsa::matriz_esparsa(int l, int c) {
	assert(l > 0);
	assert(c > 0);
	dimc = c;
	diml = l;
    //criacao das cabecas das colunas
	inicio_col = new no;
	assert(inicio_col);
	inicio_col->n_linha = -1;
	inicio_col->n_col = 1;    
	inicio_col->no_col = inicio_col;
	inicio_col->no_linha = inicio_col;
	pontno fim = inicio_col;
	for(int i = 1; i < dimc; i++) {
		pontno novono = new no;
		assert(novono);
		novono->n_linha = -1;
		novono->n_col = i + 1;
		novono->no_linha = inicio_col;
		novono->no_col = novono;
		fim->no_linha = novono;
		fim = novono;
    }
	//criacao das cabecas das linhas
    inicio_linha = new no;
	assert(inicio_linha);
	inicio_linha->n_linha = 1;
	inicio_linha->n_col = -1;
	inicio_linha->no_linha = inicio_linha;
	inicio_linha->no_col = inicio_linha;
	fim = inicio_linha;
	for(i = 1; i < diml; i++) {
		pontno novono = new no;
		assert(novono);
		novono->n_linha = i + 1;
		novono->n_col = -1;
		novono->no_col = inicio_linha;
		novono->no_linha = novono;
		fim->no_col = novono;
		fim = novono;
    }
}


void matriz_esparsa::insere(float val, int l, int c) {
	if(l > diml || l < 0) {
		cout << "\n\nlinha fora do especificado";
        exit(1);
    }
	if(c > dimc || c < 0) {
		cout << "\n\ncoluna fora do especificado";
        exit(1);
	}
	pontno novono = new no;
	assert(novono);
    novono->valor = val;
	novono->n_linha = l;
	novono->n_col = c;
    //insere na lista correspondente a linha
	pontno aux = inicio_linha;
	while(aux->n_linha != l)
		aux = aux->no_col;
	if(aux->no_linha == aux) {//verificando se linha vazia
		novono->no_linha = aux;
		aux->no_linha = novono;   
    }
	else {
		pontno paux = aux;
		aux = aux->no_linha;
		while(aux->n_col != -1 && c > aux->n_col) {
			paux = aux;
			aux = aux->no_linha;
        }
		paux->no_linha = novono;
		novono->no_linha = aux;
    }
	//insere na lista correspondente a coluna
	aux = inicio_col;
	while(aux->n_col != c)
		aux = aux->no_linha;
	if(aux->no_col == aux) { //verifica se a coluna esta vazia
		novono->no_col = aux;
		aux->no_col = novono;
    }
	else {
		pontno paux = aux;
		aux = aux->no_col;
		while(aux->n_linha != -1 && l > aux->n_linha) {
			paux = aux;
			aux = aux->no_col;
        }
		paux->no_col = novono;
		novono->no_col = aux;
    }
}


istream & operator>>(istream &entrada, matriz_esparsa &mat) {
	float valor;
	for(int i = 1; i <= mat.diml; i++) {
		for(int j = 1; j <= mat.dimc; j++) {
			cout << "insira elemento<" << i << "," << j <<"> : ";
			entrada >> valor;
			if(valor != 0) {
				mat.insere(valor, i, j);
                cout << endl; 		    
			}
		}
	}
	return entrada;
}


ostream & operator<<(ostream &saida, const matriz_esparsa &mat) {
    matriz_esparsa::pontno aux = mat.inicio_linha;
	matriz_esparsa::pontno paux;
	int col, nro, volta = 1;
	while(volta <= mat.diml) {
		paux = aux->no_linha;
		if(aux == paux)
			for(int i = 1; i <= mat.dimc; i++)
				saida << " 0 ";
			else {
				col = 1;
				while(paux != aux) {
					nro = paux->n_col;
					for(int i = col; i < nro; i++)
						saida << " 0 ";
					col = nro + 1;
					saida << " " << paux->valor << " ";
					paux = paux->no_linha;
                }
				if(col <= mat.dimc)
					for(int i = col; i <= mat.dimc; i++)
						saida << " 0 ";
            }
			saida << endl;
			aux = aux->no_col;
			volta++;
    }
	return saida;
}


matriz_esparsa matriz_esparsa::operator+(matriz_esparsa & mat) {
	int dimlin, dimcol, menorlinha, menorcol;
	//matriz_esparsa soma(diml, dimc);
	pontno aux1; 
	pontno aux2;
	pontno paux1 = inicio_linha;
	pontno paux2 = mat.inicio_linha;
	float aux3;
	if(mat.diml >= diml) {
		dimlin = mat.diml;
	    menorlinha = diml;
	}
	else {
		dimlin = diml;
        menorlinha = mat.diml;
	}
	if(mat.dimc >= dimc) {
		dimcol = mat.dimc;
	    menorcol = dimc;
	}
	else {
        dimcol = dimc;
        menorcol = mat.dimc;
    }
	matriz_esparsa soma(dimlin, dimcol);     
	
	    for(int i = 1; i <= menorlinha; i++) {
			aux1 = paux1;
			aux2 = paux2;
			for(int j = 1; j <= dimcol; j++) {
				if(aux1->no_linha->n_col == aux2->no_linha->n_col && aux1->no_linha->n_col == j && aux2->no_linha->n_col == j) {
					aux3 = aux1->no_linha->valor + aux2->no_linha->valor;
					soma.insere(aux3, i, j);
					aux1 = aux1->no_linha;
					aux2 = aux2->no_linha;
                }
				else 
					if(aux1->no_linha->n_col > aux2->no_linha->n_col && aux2->no_linha != paux2 ) {
						aux3 = aux2->no_linha->valor;
						soma.insere(aux3, i, j);
					   	aux2 = aux2->no_linha;
					}  
					else 
						if(aux1->no_linha->n_col < aux2->no_linha->n_col && aux1->no_linha != paux1) {
						    aux3 = aux1->no_linha->valor;
						    soma.insere(aux3, i, j);
						    aux1 = aux1->no_linha;
                        }
					     
						else 
							if(aux1->no_linha->n_col == aux2->no_linha->n_col && aux1->no_linha->n_col != j && aux2->no_linha->n_col != j) {
								int x = 0;
								//aux3 = aux1->no_linha->valor = aux2->no_linha->valor;
								//soma.insere(aux3, i, j);
							}
							else
								if(aux1->no_linha == paux1) {
									aux3 = aux2->no_linha->valor;
								    soma.insere(aux3, i, j);
					   	            aux2 = aux2->no_linha;

                                }
								else {
									 aux3 = aux1->no_linha->valor;
						             soma.insere(aux3, i, j);
						             aux1 = aux1->no_linha;
                                }
            
			}
		    paux2 = paux2->no_col;
			paux1 = paux1->no_col; 
		}
		if(diml > mat.diml) {
		    for(int i = 1; i <=dimlin - menorlinha; i++) {
			    aux1 = paux1;
			    //aux2 = paux2;
				for(int j = 1; j <= dimcol; j++) {
					aux1 = aux1->no_linha;
					if(aux1->n_col == j)
                        soma.insere(aux1->valor,aux1->n_linha, j);
					else
						int x = 0;
					//aux1 = aux1->no_linha;
                }
            paux1 = paux1->no_col;
			}
		}
		if(diml < mat.diml) {
		    for(int i = 1; i <=dimlin - menorlinha; i++) {
			    //aux1 = paux1;
			    aux2 = paux2;
				for(int j = 1; j <= dimcol; j++) {
					aux2 = aux2->no_linha;
					if(aux2->n_col == j)
                        soma.insere(aux2->valor,aux2->n_linha, j);
					else
						int x = 0;					
					//aux2 = aux2->no_linha;
                }
            paux2 = paux2->no_col;
			}
		}
    //}
	//else
	//	exit(1);
	return soma;
}



matriz_esparsa matriz_esparsa::operator-(matriz_esparsa & mat) {
	int dimlin, dimcol, menorlinha, menorcol;
	//matriz_esparsa subtracao(diml, dimc);
	pontno aux1; 
	pontno aux2;
	pontno paux1 = inicio_linha;
	pontno paux2 = mat.inicio_linha;
	float aux3;
	if(mat.diml >= diml) {
		dimlin = mat.diml;
	    menorlinha = diml;
	}
	else {
		dimlin = diml;
        menorlinha = mat.diml;
	}
	if(mat.dimc >= dimc) {
		dimcol = mat.dimc;
	    menorcol = dimc;
	}
	else {
        dimcol = dimc;
        menorcol = mat.dimc;
    }
	matriz_esparsa subtracao(dimlin, dimcol);    
	    for(int i = 1; i <= menorlinha; i++) {
			aux1 = paux1;
			aux2 = paux2;
			for(int j = 1; j <= dimcol; j++) {
				if(aux1->no_linha->n_col == aux2->no_linha->n_col && aux1->no_linha->n_col == j && aux2->no_linha->n_col == j) {
					aux3 = aux1->no_linha->valor - aux2->no_linha->valor;
					subtracao.insere(aux3, i, j);
					aux1 = aux1->no_linha;
					aux2 = aux2->no_linha;
                }
				else 
					if(aux1->no_linha->n_col > aux2->no_linha->n_col && aux2->no_linha != paux2 ) {
						aux3 = aux2->no_linha->valor;
						subtracao.insere(aux3, i, j);
					   	aux2 = aux2->no_linha;
					}  
					else 
						if(aux1->no_linha->n_col < aux2->no_linha->n_col && aux1->no_linha != paux1) {
						    aux3 = aux1->no_linha->valor;
						    subtracao.insere(aux3, i, j);
						    aux1 = aux1->no_linha;
                        }
					     
						else 
							if(aux1->no_linha->n_col == aux2->no_linha->n_col && aux1->no_linha->n_col != j && aux2->no_linha->n_col != j) {
								int x = 0;
								//aux3 = aux1->no_linha->valor = aux2->no_linha->valor;
								//soma.insere(aux3, i, j);
							}
							else
								if(aux1->no_linha == paux1) {
									aux3 = aux2->no_linha->valor;
								    subtracao.insere(aux3, i, j);
					   	            aux2 = aux2->no_linha;

                                }
								else {
									 aux3 = aux1->no_linha->valor;
						             subtracao.insere(aux3, i, j);
						             aux1 = aux1->no_linha;
                                }
            
			}
		    paux1 = paux1->no_col;
			paux2 = paux2->no_col;
		}
		if(diml > mat.diml) {
		    for(int i = 1; i <=dimlin - menorlinha; i++) {
			    aux1 = paux1;
			    //aux2 = paux2;
				for(int j = 1; j <= dimcol; j++) {
					aux1 = aux1->no_linha;
					if(aux1->n_col == j)
                        subtracao.insere(aux1->valor,aux1->n_linha, j);
					else
						int x = 0;
					//aux1 = aux1->no_linha;
                }
            paux1 = paux1->no_col;
			}          
		}
		if(diml < mat.diml) {
		    for(int i = 1; i <=dimlin - menorlinha; i++) {
			    //aux1 = paux1;
			    aux2 = paux2;
				for(int j = 1; j <= dimcol; j++) {
					aux2 = aux2->no_linha;
					if(aux2->n_col == j)
					    subtracao.insere(aux2->valor,aux2->n_linha, j);
					else
						int x = 0;
					//aux2 = aux2->no_linha;
                }
            paux2 = paux2->no_col;
			}            
		}
	
	//}
	//else
	//	exit(1);
	return subtracao;
}

            

matriz_esparsa matriz_esparsa::operator*(matriz_esparsa & mat) {
	matriz_esparsa multiplicacao(diml, mat.dimc);
	float mult = 0.0;
	pontno aux1, paux1;
	pontno aux2, paux2;
	//if(dimc >= mat.dimc) {
	paux1 = inicio_linha;
	paux2 = mat.inicio_col;
    aux2 = paux2;
	//}
	//else {
//		paux1 = mat.inicio_linha;
//		paux2 = inicio_col;
  //      aux2 = paux2;
	//}
	if(dimc != mat.diml) {
		cout << "Nao e possivel fazer multiplicacao\n\n\n";
		exit(1);
	}
	else {
		for(int i =1; i <= diml; i++) {
			aux1 = paux1;
			for(int j = 1; j <= mat.dimc; j++) {
				for(int k = 1; k <= mat.diml; k++) {
					if(aux1->no_linha->n_linha == i && aux1->no_linha->n_col == k && aux2->no_col->n_col == j && aux2->no_col->n_linha == k) {
						mult = mult + aux1->no_linha->valor * aux2->no_col->valor;
						aux1 = aux1->no_linha;
						aux2 = aux2->no_col;
                    }
					else if(aux1->no_linha->n_col > aux2->no_col->n_linha) 
							aux1 = aux1->no_linha;
						else if(aux1->no_linha->n_col < aux2->no_col->n_linha)
								aux2 = aux2->no_col;
							else
								int x = 0;
				}
				multiplicacao.insere(mult, i, j);
				mult = 0.0;
				paux2 = paux2->no_linha;
				aux2 = paux2;
			    aux1 = paux1;
			}
			paux1 = paux1->no_col;
		}
		return multiplicacao;

	}
}
		
	    
	 
void main() {
	cout << "\n\n\n                             SEJA BEM VINDO\n\n\n\n\n\n";
	cout << "     ###########################################################\n";
	cout << "     #                                                         #\n";  
	cout << "     #                SIMULADOR DE MATRIZ ESPARSA              # \n";
    cout << "     #                                                         #\n"; 
	cout << "     ###########################################################\n\n\n\n\n";
	system("PAUSE");
	system("CLS");
	cout << "Digite numero de linhas da primeira matriz: ";
	int l1, c1, l2, c2, l3, c3;
	cin >> l1;
	cout << "\nDigite numero de colunas da primeira matriz: ";
	cin >> c1;
    matriz_esparsa mat(l1, c1);
	cout << "\nEntre com os elementos da primeira matriz:\n\n";
	cin >> mat;
	cout << "\nMatriz esparsa 1 criada\n";
	cout << mat;
	cout << "\n\nDigite numero de linhas da segunda matriz";
    cin >> l2;
    cout << "\nDigite numero de colunas da segunda matriz";
	cin >> c2;
	matriz_esparsa mat2(l2, c2);
    cout << "\nEntre com os elementos da matriz 2:";
	cin >> mat2;
	cout << "\nMatriz esparsa 2 criada\n";
	cout << mat2;
	cout << "\n\nA matriz soma e:";
	if(l2 >= l1)
		l3 = l2;
	else
		l3 = l1;
    if(c2 >= c1)
		c3 = c2;
	else
		c3 = c1;
	matriz_esparsa soma(l3, c3);
	cout << endl << endl << endl;
	cout << mat + mat2;
	cout << "\n\nA matriz subtracao e:";
	matriz_esparsa subtracao(l3, c3);
	cout << endl << endl << endl;
	cout << mat - mat2;
	cout << "\nA matriz multiplicacao e: ";
	matriz_esparsa multiplicacao(l1, c2);
	cout << endl << endl << endl;
	cout << mat * mat2;
    cout << endl << endl;
	system("PAUSE");
    system("CLS");
	cout << "\n\n\n\n\n\n\n\n\n            ############   BY PAULO MENDES!!!!!! ###########  \n\n\n\n\n\n                 ";
	//system("PAUSE");

}






	


