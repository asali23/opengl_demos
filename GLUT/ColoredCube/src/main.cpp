#include <GL/glew.h>
#include <GL/freeglut.h>
//#define GLM_SWIZZLE
//#define GLM_MESSAGES
//#define GLM_FORCE_INLINE
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstdlib>
#include <iostream>
#include <fstream>

#include "object3d.h"
#include "camera.h"

static int WINDOW_HEIGHT = 800;
static int WINDOW_WIDTH = 600;
static int WINDOW_LOCATION_X = 100;
static int WINDOW_LOCATION_Y = 100;
static char WINDOW_TITLE[] = "ColoredCube";
static char VERTEX_SHADER_FILE_PATH[] = "C:/workspace/learning/OpenGL/ColoredCube/shaders/vertex_shader.glsl";
static char FRAGMENT_SHADER_FILE_PATH[] = "C:/workspace/learning/OpenGL/ColoredCube/shaders/fragment_shader.glsl";
static float FOV = 45.0f;
static float NEAR_PLANE = 0.01f;
static float FAR_PLANE = 100.0f;

using namespace std;

Object3D *cubeObject;
Camera *camera;

GLuint VAO_ID;	// This will identify our vertex array object
GLuint Vertices_VBO_ID;	// This will identify our vertex buffer object for vertices
GLuint Colors_VBO_ID;	// This will identify our vertex buffer object for colors
GLuint programID; // This will identify our shader program
int windowID;
struct point
{
	int x;
	int y;
} mousePosition;
float hAngle = 0.0f, vAngle = 0.0f;
glm::vec3 up(0.0f, 1.0f, 0.0f);

void RenderScene();
void ReshapeScene(int width, int height);
void KeyboardProcessing(unsigned char key, int x, int y);
void MouseProcessing(int x, int y);
void MousePassiveProcessing(int x, int y);

string loadFileContents(const char * filePath);
int compileShader(GLuint ShaderID, char const * ShaderSourcePointer);
GLuint LoadShaders(const char * VertexShaderFilePath, const char * FragmentShaderFilePath);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WINDOW_HEIGHT, WINDOW_WIDTH);
	glutInitWindowPosition(WINDOW_LOCATION_X, WINDOW_LOCATION_Y);
	windowID = glutCreateWindow(WINDOW_TITLE);
	glutSetWindow(windowID);
	glutDisplayFunc(RenderScene);
	glutReshapeFunc(ReshapeScene);
	//glutKeyboardFunc(KeyboardProcessing);
	glutMotionFunc(MouseProcessing);
	glutPassiveMotionFunc(MousePassiveProcessing);
	
	// Must be done after glut is initialized!
    GLenum res = glewInit();
    if (res != GLEW_OK)
	{
		std::cerr<<"Error: '"<<glewGetErrorString(res)<<"'"<<std::endl;
		return 1;
    }
	
	glGenVertexArrays(1, &VAO_ID);
	glBindVertexArray(VAO_ID);
	
	cubeObject = new Object3D();
    cubeObject->initializeCubeObject();
	camera = new Camera();
    camera->setCentre(glm::vec3(0.0f, 0.0f, 2.0f));
	hAngle = 0.0f; vAngle = 0.0f;
	
	glGenBuffers(1, &Vertices_VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Vertices_VBO_ID);
	glBufferData(GL_ARRAY_BUFFER,	// Type of buffer
				cubeObject->getModel()->getVertexCount() * sizeof(glm::vec3), // size of buffer
				cubeObject->getModel()->getVertexCoordinatesArray(), // pointer to contents of buffer
				GL_STATIC_DRAW); // nature of data in buffer
	
	glGenBuffers(1, &Colors_VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, Colors_VBO_ID);
	glBufferData(GL_ARRAY_BUFFER,	// Type of buffer
				cubeObject->getModel()->getVertexCount() * sizeof(glm::vec3), // size of buffer
				cubeObject->getModel()->getVertexColorsArray(), // pointer to contents of buffer
				GL_STATIC_DRAW); // nature of data in buffer
	
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
	
	// Create and compile our GLSL program from the shaders
	programID = LoadShaders(VERTEX_SHADER_FILE_PATH, FRAGMENT_SHADER_FILE_PATH);
	// Use our shader
	std::cout<<"Using Shader Program (ID: "<<programID<<")"<<std::endl;
	glUseProgram(programID);
	
	// Get a handles for our Model, View and Projection uniforms
	GLuint ModelMatrixID = glGetUniformLocation(programID, "Model");
	glm::mat4 Model = cubeObject->getModelMatrix();
	glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
	
	GLuint ViewMatrixID = glGetUniformLocation(programID, "View");
	glm::mat4 View = camera->getViewMatrix();
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
	
	GLuint ProjectionMatrixID = glGetUniformLocation(programID, "Projection");
	glm::mat4 Projection = glm::perspective(FOV, (float)WINDOW_HEIGHT / WINDOW_WIDTH, NEAR_PLANE, FAR_PLANE);
	glUniformMatrix4fv(ProjectionMatrixID, 1, GL_FALSE, &Projection[0][0]);
	
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glutMainLoop();
	
	glDeleteBuffers(1, &Vertices_VBO_ID);
	glDeleteBuffers(1, &Colors_VBO_ID);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VAO_ID);
		
	return 0;
}

void RenderScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);	
	glBindBuffer(GL_ARRAY_BUFFER, Vertices_VBO_ID);
	
	glVertexAttribPointer(
	0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
    3,                  // size
    GL_FLOAT,           // type
    GL_FALSE,           // normalized?
    0,                  // stride
    (void*)0            // array buffer offset
	);	
	
	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, Colors_VBO_ID);
	
	glVertexAttribPointer(
     1,            // attribute. No particular reason for 1, but must match the layout in the shader.
     3,            // size
     GL_FLOAT,     // type
     GL_FALSE,     // normalized?
     0,            // stride
     (void*)0      // array buffer offset
	);
	
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, cubeObject->getModel()->getVertexCount());
	//glDrawArrays(GL_QUADS, 0, cubeObject->getModel()->getVertexCount());
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
    glutSwapBuffers();
}

void ReshapeScene(int width, int height)
{
	
}

void KeyboardProcessing(unsigned char key, int x, int y)
{
	
}

void MouseProcessing(int x, int y)
{
	//std::cout<<"Mouse: ["<<x<<" "<<y<<"]"<<std::endl;
	if (up.y > 0)
		hAngle += -3.14/2.0f * (x - mousePosition.x) / (float)WINDOW_WIDTH;
	else
		hAngle -= -3.14/2.0f * (x - mousePosition.x) / (float)WINDOW_WIDTH;
	vAngle += 3.14/2.0f * (y - mousePosition.y) / (float)WINDOW_HEIGHT;
	//std::cout<<"hAngle = "<<hAngle<<" vAngle = "<<vAngle<<"]"<<std::endl;
	
	glm::vec3 c = camera->getCentre();
	float r = (float)sqrt((double)c.x * c.x + c.y * c.y + c.z * c.z);
	glm::vec3 direction = glm::vec3(r * sin(hAngle) * cos(vAngle), r * sin(vAngle), r * cos(hAngle) * cos(vAngle));
	camera->setCentre(direction);
	
	glm::vec3 right = glm::vec3(sin(hAngle - 1.67f), 0, cos(hAngle - 1.67f));
	up = glm::cross(right, direction);
	camera->setUpVector(up);
	//std::cout<<"up: ["<<up.x<<" "<<up.y<<" "<<up.z<<"]"<<std::endl;
	
	GLuint ViewMatrixID = glGetUniformLocation(programID, "View");
	glm::mat4 View = camera->getViewMatrix();
	glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &View[0][0]);
	
	glutPostRedisplay();

	mousePosition.x = x;
	mousePosition.y = y;	
}

void MousePassiveProcessing(int x, int y)
{
	mousePosition.x = x;
	mousePosition.y = y;
}

string loadFileContents(const char * filePath)
{
	std::string contents = "";
	ifstream fileStream(filePath, std::ios::in);
	if(fileStream.is_open())
	{
		std::string Line = "";
		while(getline(fileStream, Line))
			contents += "\n" + Line;
		fileStream.close();
	}
	else
	{
		std::cerr<<"Could not open "<<filePath<<std::endl;
	}
	return contents;
}

int compileShader(GLuint ShaderID, char const * ShaderSourcePointer)
{
	glShaderSource(ShaderID, 1, &ShaderSourcePointer , NULL);
	glCompileShader(ShaderID);
	
	GLint Result = GL_FALSE;
	int InfoLogLength;
	
	glGetShaderiv(ShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(ShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		char * ShaderCompileErrorMessage =  new char[InfoLogLength + 1];
		glGetShaderInfoLog(ShaderID, InfoLogLength, NULL, ShaderCompileErrorMessage);
		std::cout<<ShaderCompileErrorMessage<<std::endl;
		return -1;
	}
	return 0;
}

GLuint LoadShaders(const char * VertexShaderFilePath, const char * FragmentShaderFilePath)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Read the Vertex Shader code from the file
	string VertexShaderCode = loadFileContents(VertexShaderFilePath);
		
	// Read the Fragment Shader code from the file
	string FragmentShaderCode = loadFileContents(FragmentShaderFilePath);
	
	// Compile Vertex Shader
	std::cout<<"Compiling shader : "<<VertexShaderFilePath<<std::endl;
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	compileShader(VertexShaderID, VertexSourcePointer);
	
	// Compile Fragment Shader
	std::cout<<"Compiling shader : "<<FragmentShaderFilePath<<std::endl;
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	compileShader(FragmentShaderID, FragmentSourcePointer);
	
	// Link the program
	std::cout<<"Linking program"<<std::endl;
	GLuint ProgramID = glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	
	GLint Result = GL_FALSE;
	int InfoLogLength;
	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	
	if (InfoLogLength > 0)
	{
		char * ProgramErrorMessage =  new char[InfoLogLength + 1];
		glGetShaderInfoLog(ProgramID, InfoLogLength, NULL, ProgramErrorMessage);
		std::cout<<ProgramErrorMessage<<std::endl;
	}
	
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	
	return ProgramID;
}
