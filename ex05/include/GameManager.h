#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include <tuple>
#include <vector>

#include <GL/glew.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include "Timer.h"
#include "GLUtils/GLUtils.hpp"
#include "GUI_RenderInfo.h"
#include <boost/thread.hpp>
/**
 * This class handles the game logic and display.
 * Uses SDL as the display manager, and glm for 
 * vector and matrix computations
 */
class GameManager {
public:

	/**
	 * Constructor
	 */
	GameManager();

	/**
	 * Destructor
	 */
	~GameManager();

	/**
	 * Initializes the game, including the OpenGL context
	 * and data required
	 */
	void init();

	/**
	 * The main loop of the game. Runs the SDL main loop
	 */
	void play();

	/**
	 * Quit function
	 */
	void quit();

	/**
	 * Function that handles rendering into the OpenGL context
	 */
	void render();

protected:
	/**
	 * Creates the OpenGL context using SDL
	 */
	void createOpenGLContext();

	/**
	 * Sets states for OpenGL that we want to keep persistent
	 * throughout the game
	 */
	void setOpenGLStates();

	/**
	 * Creates the matrices for the OpenGL transformations,
	 * perspective, etc.
	 */
	void createMatrices();

	/**
	 * Compiles, attaches, links, and sets uniforms for
	 * a simple OpenGL program
	 */
	void createHeightProgram();
	
	/**
	 * Creates vertex array objects
	 */
	void createHeightVAO();
	
	/**
	 * Compiles, attaches, links, and sets uniforms for
	 * the OpenGL program that renders the texture to the
	 * fullscreen quad
	 */
	void createFBOProgram();
	
	/**
	 * Creates vertex array objects for the fullscreen
	 * quad used to render the FBO texture to screen
	 */
	void createFBOVAO();

	/**
	  * Creates the framebuffer object
	  */
	void createFBO();

	//Width and height of our window
	static const unsigned int window_width = 1280;
	static const unsigned int window_height = 720;

	//Width and height of our fbo
	static const unsigned int fbo_width = 400;
	static const unsigned int fbo_height = 400;

private:
	
	bool VideoCapture;

	std::shared_ptr<GUI_RenderInfo> guiRenderInfo;

	void RenderScene();

	//Variables for our regular height map rendering
	GLuint height_vao; //< Vertex array object
	GLuint height_vertex_bo; //< VBO for vertex data
	GLuint height_index_bo; //< VBO for index data
	GLuint height_texture, color_texture; //< Different textures

	//Variables for the FBO 
	GLuint fbo; //< Frame buffer object id
	GLuint fbo_vao; //< Vertex array object for our FBO geometry (full-screen quad)
	GLuint fbo_vertex_bo; //< Vetex buffer object for fullscreen quad
	
	GLuint fbo_texture; //< framebuffer object color attachment (texture)
	GLuint fbo_depth; //< framebuffer object depth attachment (renerbuffer)

	Timer my_timer; //< Timer for machine independent motion

	glm::mat4 projection_matrix; //< OpenGL projection matrix
	glm::mat4 model_matrix; //< OpenGL model transformation matrix
	glm::mat4 view_matrix; //< OpenGL camera/view matrix
	glm::mat3 normal_matrix; //< OpenGL matrix to transfor normals

	glm::mat4 fbo_modelMatrix;
	glm::mat4 fbo_projectionMatrix;
	glm::mat4 fbo_viewMatrix;

	std::shared_ptr<GLUtils::Program> height_program, fbo_program;

	SDL_Window* main_window; //< Our window handle
	SDL_GLContext main_context; //< Our opengl context handle 
	
	struct TerrainMesh {
		std::vector<float> vertices;
		std::vector<unsigned int> indices;
		unsigned int restart_token;
	};
	unsigned int frameCounter;
	TerrainMesh mesh;

	/**
	 * Creates a mesh for us using triangle strips
	 * @param nx Number of elements in x direction
	 * @param ny Number of elements in y direction
	 * @param restart_token the integer in the index list that corresponds to primitive restart
	 * @return a tuple consisting of the vertex data, index data, and the restart index.
	 */
	TerrainMesh createTriangleStripMesh(unsigned int nx, unsigned int ny);

	/**
	 * Creates a mesh for us using triangle strips
	 * @param nx Number of elements in x direction
	 * @param ny Number of elements in y direction
	 * @param restart_token the integer in the index list that corresponds to primitive restart
	 * @return a tuple consisting of the vertex data, index data, and the restart index.
	 */
	TerrainMesh createTriangleFanMesh(unsigned int nx, unsigned int ny);

	/**
	  * Loads a texture into the OpenGL texture texture
	  */
	static GLuint loadTexture(std::string filename);

	
	boost::thread thread_1;
};

void SaveImageToDisk(unsigned int window_width, unsigned int window_height,
					unsigned int* frameCounter, std::string format = ".bmp");

#endif // _GAMEMANAGER_H_
