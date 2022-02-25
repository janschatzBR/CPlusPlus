// Computação Gráfica
// Exercício 6

/*
252808  Cleyton Vasconcelos
252751  Jan Schatz
252557  Manoel Rangel
252824  Thiago de Melo Lima
*/

#include <gl/glut.h>
#include <stdlib.h>


// globais
GLfloat eyex=20.0, eyey=30.0, eyez=0.0;


//Função chamada quando o GLUT percebe que precisa fazer alterações na renderização
void Desenha(void)
{
     //Limpa o buffer
     //   GL_COLOR_BUFFER_BIT
     //       Indicates the buffers currently enabled for color writing.
     //   GL_DEPTH_BUFFER_BIT
     //        Indicates the depth buffer.
     glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

     glLoadIdentity();
     //Define a posição da vista (observador)
     gluLookAt (eyex, eyey, eyez, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

     //Desenho dos sólidos
	 glColor3f(1.0f, 1.0f, 0.0f);
     glutWireSphere(5, 10, 10);
     glColor3f(0.0f, 1.0f, 0.0f);
     glutWireCube(10);
     glColor3f(0.0f, 0.0f, 1.0f);
     glutSolidSphere(1, 10, 10);

     //No caso de buffers duplos, realiza a troca deles
     //glFlush é executado pelo glutSwapBuffers
     glutSwapBuffers();

}
 

//Função chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	//Para prevenir uma divisão por zero no cálculo do aspect
	if ( h == 0 ) h = 1;

	//Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	//Especifica qual matriz alvo dos próximos comandos
	glMatrixMode(GL_PROJECTION);
	//Carrega a matriz identidade
	glLoadIdentity();

    //Multiplica a matriz corrente por uma matriz de perspectiva
    glFrustum (-1.0, 1.0, -1.0, 1.0, 2.0, 1000.0);
	
    //Especifica qual matriz alvo dos próximos comandos
	glMatrixMode(GL_MODELVIEW);
	//Carrega a matriz identidade
	glLoadIdentity();

}


//Tratamento de eventos do teclado
void keyboard ( unsigned char key, int x, int y ) 
{
   switch (key) {
      //Esc sai do programa
      case 27:
         exit(0);
      break;
      case '1':
           eyex=30.0;
           eyex=20.0;
           eyez=10.0;
      break;
      case '2':
           eyex=20.0;
           eyex=30.0;
           eyez=10.0;
      break;
      case '3':
           eyex=20.0;
           eyex=30.0;
           eyez=20.0;
      break;
      case '4':
           eyex=20.0;
           eyex=40.0;
           eyez=20.0;
      break; 
      case '5': 
           eyex=20.0;
           eyex=40.0;
           eyez=-10.0;
      break;
      case '6':      
           eyex=60.0;
           eyex=30.0;
           eyez=0.0;
      break;                      
   }  
   //Obriga a renderização  
   glutPostRedisplay();
}


//Tratamento de eventos do teclado (teclas especiais)
void setas(int key, int x, int y) 
{
     switch(key)
     {
      case GLUT_KEY_LEFT:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum (-2.0, 1.0, -1.0, 1.0, 2.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      break;    
      case GLUT_KEY_RIGHT:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum (-1.0, 2.0, -1.0, 1.0, 2.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      break;  
      case GLUT_KEY_UP:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum (-1.0, 1.0, -2.0, 1.0, 2.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      break;  
      case GLUT_KEY_DOWN:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum (-1.0, 1.0, -1.0, 2.0, 2.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
      break;   
      //Tecla F1 reseta para os parâmetros iniciais    
      case GLUT_KEY_F1:
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glFrustum (-1.0, 1.0, -1.0, 1.0, 2.0, 1000.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        eyex=20.0;
        eyey=30.0;
        eyez=0.0;
      break;               
   } 
   //Obriga a renderização   
   glutPostRedisplay();
}
     
     
//Programa Principal
int main()
{
    //Seta o modo do display para RGB e buffer duplo
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    //Posição da janela
    glutInitWindowPosition(0,0);
    //Tamanho da janela
	glutInitWindowSize(640,480);
    //Cria janela com título
	glutCreateWindow("Exercício 6");
    //Função chamada quando o GLUT percebe que precisa realizar alterações
	glutDisplayFunc(Desenha);
	//Função chamada quando não está realizando tarefas
    glutIdleFunc(Desenha);
    //Função chamada quando o tamanho da janela é alterado
	glutReshapeFunc(AlteraTamanhoJanela);
    //Função chamada quando um evento do teclado ocorre
    glutKeyboardFunc ( keyboard );
    //Função chamada quando um evento do teclado ocorre (teclas especiais)
    glutSpecialFunc ( setas );
    //Preenche o buffer de cor
    glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
    //Habilita a capacidade do OpenGL de comparar profundidades e atualizar o depth buffer
    glEnable(GL_DEPTH_TEST);
    //Faz o GLUT entrar no loop (nunca sai dessa função)
	glutMainLoop();
    return 0;	
}
