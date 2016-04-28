/*Programmed by:
	José Elías Hernández Villegas
*/

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

/*variables qe almacenan la posicion de raton 
tomada de la funcion glutMouseFunc y glutMotionFun*/
float Moverx=1.0f;
float Movery=1.0f;


/*variables para tomar los valores de los materiales*/
GLfloat Diffuse[3] = {};//Difucion
GLfloat Specular[3] = {};//Reflejo
GLfloat Ambient[3] = {};//Entorno
GLfloat Shininess[1] = {};//Brillo
GLfloat punto_luz[4] = {1.0, 1.0, -4.0, 1.5};//Hubicacion de la luz desde un punto especifico


void init(void)
{
	
	GLfloat luz_ambiente[] = {0.5,0.5,0.5}; 

	/*Valores iniciales de la textura de la esfera*/
       		Ambient[0] =  0.05, 0.05, 0.05;
    		Diffuse[0] =  0.5, 0.5, 0.5;
    		Specular[0] =  0.7, 0.7, 0.7;
    		Shininess[0] = 0.078125;

	
	glDepthFunc(GL_LESS); //comparación de profundidad
	glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
	glEnable(GL_LIGHTING);//Activamos la fuente de luz
	glEnable(GL_LIGHT0); //Activamos las luces en 0
	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luz_ambiente);
	glLightfv(GL_LIGHT0, GL_POSITION, punto_luz);
	glShadeModel(GL_SMOOTH);
}

void reshape(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);//Vista ortogonal
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y)
{
    //control de teclas que cambian el color de la esfera!
    switch (key)
    {
	
    case 'c'://Color Copper en la esfera
		Ambient[0]=  0.19125;
		Ambient[1]=  0.0735;
		Ambient[2]=  0.0225;
    		Diffuse[0]=  0.7038;
		Diffuse[1]=  0.27048;
		Diffuse[2]=  0.0828;
    		Specular[0]=  0.256777;
		Specular[0]=  0.137622;
		Specular[0]=  0.086014;
    		Shininess[0]= 0.1;
        break;

    case 'r'://Color Red plastic en la esfera
		Ambient[0]=  1.0;
		Ambient[1]=  0.0;
		Ambient[2]=  0.0;
    		Diffuse[0]=  1.0;
		Diffuse[1]=  0.0;
		Diffuse[2]=  0.0;
    		Specular[0]=  0.7;
		Specular[0]=  0.6;
		Specular[0]=  0.6;
    		Shininess[0]= 0.1;
        break;

   case 'g' ://Color Gold en la esfera
		Ambient[0]=  0.24725;
		Ambient[1]=  0.1995;
		Ambient[2]=  0.0745;
    		Diffuse[0]=  0.75164;
		Diffuse[1]=  0.60648;
		Diffuse[2]=  0.22648;
    		Specular[0]=  0.628281;
		Specular[0]=  0.555802;
		Specular[0]=  0.366065;
    		Shininess[0]= 0.4;
        break;

    case 'b' ://Color Brass en la esfera
		Ambient[0]=  0.329412;
		Ambient[1]=  0.223529;
		Ambient[2]=  0.027451;
    		Diffuse[0]=  0.780392;
		Diffuse[1]=  0.568627;
		Diffuse[2]=  0.113725;
    		Specular[0]=  0.992157;
		Specular[0]=  0.941176;
		Specular[0]=  0.807843;
    		Shininess[0]= 0.21794872;
	break;

    case 's' ://Color Silver en la esfera
		Ambient[0]=  0.19225;
		Ambient[1]=  0.19225;
		Ambient[2]=  0.19225;
    		Diffuse[0]=  0.50754;
		Diffuse[1]=  0.50754;
		Diffuse[2]=  0.50754;
    		Specular[0]=  0.508273;
		Specular[0]=  0.508273;
		Specular[0]=  0.508273;
    		Shininess[0]= 27.0;
        break;
    }
    glutPostRedisplay();//Refresca la pantalla
}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW_MATRIX );
    glLoadIdentity();
   //gluLookAt(1.0, 2.0, 3.0,   0.0, 0.0, 0.0,    0.0, 1.0, 0.0);/*Vista de la camara*/

		//SetMateial
    		glMaterialfv(GL_FRONT, GL_AMBIENT, Ambient);
    		glMaterialfv(GL_FRONT, GL_DIFFUSE, Diffuse);
    		glMaterialfv(GL_FRONT, GL_SPECULAR, Specular);
    		glMaterialfv(GL_FRONT, GL_SHININESS, Shininess);

    glutSolidSphere(1.5, 70, 70);//Dibuja una esfera   
    glTranslated((-Moverx*-0.01),(Movery*0.01),0.0); //Mueve la luz sobre la esfera
    glLightfv(GL_LIGHT0, GL_POSITION, punto_luz);//funcion donde se enciende la luz del foco
    glFlush();
    glutSwapBuffers();
}

/*Funcion para usar el clic izquierdo del raton*/
void FuncionRaton (int button, int state, int x, int y) 
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Moverx = x-250; Movery = 500 - y-250;
		glutPostRedisplay();//Refresca la pantalla
	}
 }

/*Funcion para usar el raton para mover la luz del foco por doquier*/
 void MovimientoRaton(int x, int y) 
{
 	Moverx = x-250; Movery = 500 - y-250;//valores para las variables para el plano x,y.
 	 glutPostRedisplay();//refresca la pnatalla 
}


 
int main(int argc, char* argv[])
{
    glutInit(& argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(450, 450);
    glutInitWindowPosition (0, 0);
    glutCreateWindow("Esfera de Colores");//Crea la vetana y le da un nombre a esta misma
    init();//inicializa el init
	/* retrollamadas */
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(FuncionRaton);//Funcion para las teclas del raton
    glutMotionFunc(MovimientoRaton);//funcion para
    glutMainLoop();//funcion de flujos del programa.
    return 0;
}
