#include <iostream>
#include <math.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include "camera.cpp"
#include "SOIL.h"

using namespace std;

const int MAXDOORANGLE = -90;
const int MINDOORANGLE = 0;

CCamera objCamera;
GLfloat fAspect;
GLuint textures[9];

int doorAngle;


GLfloat posicaoLuz0[] = {1.0f, 3.5f, -20.0f, 1.0f};
//GLfloat corLuz0[] = {0.3, 0.3, 0.3, 1.0};
GLfloat corLuz0[] = {0.8, 0.8, 0.8, 1.0};
GLfloat luzAmbiente[] = {0.4, 0.4, 0.4, 0.4};
 
//GLfloat posicaoLuz1[] = {-16.0f, 8.0f, -15.0f, 1.0f};
GLfloat posicaoLuz1[] = {30.0f, 3.5f, -20.0f, 1.0};
GLfloat corLuz1[] = {0.6f, 0.6f, 0.6f, 1.0f};
GLfloat direcaoLuz1[] = {0.0f, 0.0f, 1.0f, 1.0f};
GLint spot_luz1 = 250;
GLfloat spot_brilho[] = {2};
 
GLfloat sem_cor[] = {0.0, 0.0, 0.0, 1.0};
 
// Capacidade de brilho do material
GLfloat especularidade[4] = {1.0, 1.0, 1.0, 1.0};
GLint especMaterial = 30;


void drawLamp() {
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_NORMALIZE);
		
	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);
	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, corLuz1);
	glLightfv(GL_LIGHT0, GL_SPECULAR, corLuz1);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direcaoLuz1);
	glLightfv(GL_LIGHT0, GL_SPOT_EXPONENT, spot_brilho);
	glLightf (GL_LIGHT0, GL_SPOT_CUTOFF, spot_luz1);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, corLuz1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, corLuz1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direcaoLuz1);
	glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, spot_brilho);
	glLightf (GL_LIGHT1, GL_SPOT_CUTOFF, spot_luz1);

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita a luz de número 1
	glEnable(GL_LIGHT1);

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(posicaoLuz0[0], posicaoLuz0[1], posicaoLuz0[2]);
		glMaterialfv(GL_FRONT, GL_EMISSION, corLuz0);
		glutSolidSphere(0.3,5,5);
	glPopMatrix();

	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(posicaoLuz1[0], posicaoLuz1[1], posicaoLuz1[2]);
		glMaterialfv(GL_FRONT, GL_EMISSION, corLuz0);
		glutSolidSphere(0.3,5,5);
	glPopMatrix();
}

void loadTextureFile (char *filepath,int index)
{

	int width, height;
   	unsigned char* image = SOIL_load_image(filepath, &width, &height, 0, SOIL_LOAD_RGBA);

   	glGenTextures(1, &textures[index]);
   	glBindTexture(GL_TEXTURE_2D, textures[index]);

   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void moveDoor() { doorAngle == MAXDOORANGLE ? doorAngle = MINDOORANGLE : doorAngle = MAXDOORANGLE; }

void drawRectangle(GLdouble x, GLdouble y, GLdouble z) {
	glBegin(GL_QUADS);
        // Face frontal
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, 0.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, y, 0.0f);
        
        // Face posterior
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, z);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0f, z);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, y, z);
        
		// Face lateral direita
        glTexCoord2f(0.0f, 0.0f); glVertex3f(x, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x,  y, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(x, 0.0f,  z);

       	// Face lateral esquerda
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, y, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,  y, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f,  z);
        
        // Face superior
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, y, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x,  y,  0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, y, z);
        
        // Face inferior
        glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(x, 0.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(x, 0.0f, z);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, z);

    glEnd();
}

void drawAirConditioning(GLdouble x, GLdouble y, GLdouble z) {
	
	// glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glPushMatrix();
		glTranslatef(x, y, z);
		drawRectangle(0.5f, 0.5f, 3.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawRoom() {    
	glColor3f(0.8, 0.8, 0.8);

	glBindTexture(GL_TEXTURE_2D, textures[0]);
    //Parede Frontal Antes de Porta
	glPushMatrix();
		glTranslatef(-5.0f, -4.0f, -10.0f);
		drawRectangle(1.0f, 8.0f, 0.25f);
	glPopMatrix();

	//Parede Frontal Depois da Porta
	glPushMatrix();
		glTranslatef(-2.0f, -4.0f, -10.0f);
		drawRectangle(40.0f, 8.0f, 0.25f);				
	glPopMatrix();

	//Parede Lateral Esquerda
	glPushMatrix();
		glTranslatef(-5.0f, -4.0f, -30.0f);
		drawRectangle(0.25f, 8.0f, 20.0f);
	glPopMatrix();

	//Parede Posterior
	glPushMatrix();
		glTranslatef(-5.0f, -4.0f, -30.0f);
		drawRectangle(43.0f, 8.0f, 0.25f);
	glPopMatrix();

	//Parade Lateral Direita
	glPushMatrix();
		glTranslatef(38.0f, -4.0f, -30.0f);
		drawRectangle(0.25f, 8.0f, 20.25f);
	glPopMatrix();

	//Teto
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(-5.0f, 4.0f, -30.0f);
		drawRectangle(43.0f, 0.05f, 20.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);


	//chao
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
		glTranslatef(-10.0f, -4.0f, -30.0f);
		drawRectangle(80.0f, 0.05f, 40.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawWhiteBoard() {
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(-4.5f, -3.0f, -25.0f);
		drawRectangle(0.25f, 5.0f, 10.25f);
	glPopMatrix();
}

void drawWardrobe() {
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glPushMatrix();
		glTranslatef(0.0f, -4.0f, -12.0f);
		drawRectangle(2.0f, 6.0f, 2.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawDoor() {
	glColor3f(1.0,1.0,1.0);
	glBindTexture(GL_TEXTURE_2D, textures[6]);
	glPushMatrix();
		glTranslatef(-4.0f, -4.0f, -10.0f);
		glRotatef((GLfloat) doorAngle, 0.0, 1.0, 0.0);
		drawRectangle(2.0f, 8.0f, 0.25f);		
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void drawBancadaFront(float x, float y, float z) {    

	//Parede de tras
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glPushMatrix();
		glTranslatef(x-0.2, y, z);
		drawRectangle(6.0f, 4.0f, 0.2f);
	glPopMatrix();
	

	//Parede da direita	
	glPushMatrix();
		glTranslatef(x+5.7f, y, z);
		drawRectangle(0.2f, 4.0f, 4.0f);
	glPopMatrix();

	//Parede da Esquerda
	glPushMatrix();
		glTranslatef(x-0.4f, y, z);
		drawRectangle(0.2f, 4.0f, 4.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//Mesa de tras
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPushMatrix();
		glTranslatef(x-0.2 , y+2, z);
		drawRectangle(6.0f, 0.2f, 1.f);
	glPopMatrix();

	//Mesa Esquerda
	glPushMatrix();
		glTranslatef(x-0.1, y+2, z+1);
		drawRectangle(1.0f, 0.2f, 3.0f);
	glPopMatrix();

	//Mesa da direita
	glPushMatrix();
		glTranslatef(x+4.8f, y+2, z+1);
		drawRectangle(1.0f, 0.2f, 3.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	
}

void drawBancadaBack(float x, float y, float z) {    

	//Parede da direita	
	glBindTexture(GL_TEXTURE_2D, textures[2]);
    glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(x+5.7f, y, z);
		glRotatef(180, 0, 1, 0);
		drawRectangle(0.2f, 4.0f, 4.0f);
	glPopMatrix();

	//Parede de tras
	glPushMatrix();
		glTranslatef(x-0.2, y, z);
		drawRectangle(6.0f, 4.0f, 0.2f);
	glPopMatrix();

	//Parede Esquerda
	glPushMatrix();
		glTranslatef(x-0.2f, y, z);
		glRotatef(180, 0, 1, 0);
		drawRectangle(0.2f, 4.0f, 4.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//Mesa da direita
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glPushMatrix();
		glTranslatef(x+4.8f, y+2, z-1);
		glRotatef(180, 1, 0, 0);
		drawRectangle(1.0f, 0.2f, 3.0f);
	glPopMatrix();

	//Mesa de tras
	glPushMatrix();
		glTranslatef(x-0.2 , y+2, z);
		glRotatef(180, 1, 0, 0);
		drawRectangle(6.0f, 0.2f, 1.f);
	glPopMatrix();

	//Mesa Esquerda
	glPushMatrix();
		glTranslatef(x, y+2, z-1);
		glRotatef(180, 1, 0, 0);
		drawRectangle(1.0f, 0.2f, 3.0f);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
}

void draw(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawLamp();

	drawRoom();

	drawDoor(); 

	drawWhiteBoard(); 

	drawWardrobe();

	drawBancadaFront(31.4f, -4.0f, -29.5f);

	drawBancadaFront(24.8f, -4.0f, -29.5f);

	drawBancadaBack(31.4f, -4.0f, -20.5f);

	drawBancadaBack(24.8f, -4.0f, -20.5f);

	drawBancadaFront(31.4f, -4.0f, -19.5f);

	drawBancadaFront(24.8f, -4.0f, -19.5f);

	drawBancadaBack(31.4f, -4.0f, -10.5f);

	drawBancadaBack(24.8f, -4.0f, -10.5f);

	drawAirConditioning(-4.7f, 3.0f, -21.0f);

	drawAirConditioning(37.5f, 3.0f, -28.0f);

	drawAirConditioning(37.5f, 3.0f, -14.0f);

 	glutSwapBuffers();

 	glutPostRedisplay();
}

void init(void)
{ 
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	objCamera.Position_Camera(0, 2.5f, 5,	0, 2.5f, 0,   0, 1, 0);
	doorAngle = 0;
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	// glEnable(GL_TEXTURE_GEN_S);
	// glEnable(GL_TEXTURE_GEN_T);

	loadTextureFile("img/parede.png", 0);
	loadTextureFile("img/mesaBancada.png", 1);
	loadTextureFile("img/paredeBancada.png", 2);
	loadTextureFile("img/lateralArmario.png", 3);
	loadTextureFile("img/arcondicionado.png", 4);
	loadTextureFile("img/chao.png", 5);
	loadTextureFile("img/porta.png", 6);


	glShadeModel(GL_SMOOTH);
  	//glEnable(GL_DEPTH_TEST);
  	glEnable(GL_BLEND);
  	//glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_TEXTURE_2D);

}

void positionObserver(void)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
			  objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
			  objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
}

void specifiesParametersVisualization(void)
{
	const GLfloat angle = 10.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect ,0.5, 800);
	positionObserver();
}


void modifyWindowsSize(GLsizei w, GLsizei h)
{
	if ( h == 0 ) h = 1;

    glViewport(0, 0, w, h);
 
	fAspect = (GLfloat)w/(GLfloat)h;

	//specifiesParametersVisualization();
	const GLfloat angle = 45.0f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle, fAspect ,0.5, 800);

	//positionObserver();
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
			  objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
			  objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
}

void keys(GLint key, GLint x, GLint y)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			objCamera.Rotate_View(-CAMERASPEED_LR);
			break;
		case GLUT_KEY_RIGHT:
			objCamera.Rotate_View(CAMERASPEED_LR);
			break;
		case GLUT_KEY_DOWN:
			objCamera.Move_Camera(-CAMERASPEED_UD);
			break;
		case GLUT_KEY_UP:
			objCamera.Move_Camera(CAMERASPEED_UD);
			break;
		case GLUT_KEY_F1:
			moveDoor();
			break;
	}
	glLoadIdentity();
	gluLookAt(objCamera.mPos.x,  objCamera.mPos.y,  objCamera.mPos.z,	
			  objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,	
			  objCamera.mUp.x,   objCamera.mUp.y,   objCamera.mUp.z);
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500,500);
	glutCreateWindow("Easy LAB");
	glutDisplayFunc(draw);
    glutReshapeFunc(modifyWindowsSize);
	//glutMouseFunc(GerenciaMouse);
	glutSpecialFunc(keys);
	init();
	glutMainLoop();
}