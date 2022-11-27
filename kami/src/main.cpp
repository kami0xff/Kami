
//context is the current opengl state 
#include <engine/Engine.hpp>
#include "engine/appLayer/KamiAppLayer.hpp"
#include "engine/entity/KamiGameEntityFactory.hpp"
#include "engine/entity/KamiGameEntity.hpp"

#include "engine/system/KamiEntityRenderSystem.hpp"
#include <iostream>

#define _CRT_SECURE_NO_WARNINGS


int main()
{
	//will initialize ressource caches,window,object,RNG,client options,...
	KamiAppLayer::getInstance().initialiseAppLayer();

	KamiGameEntityFactory entityFactory{};

	KamiGameEntity cube = entityFactory.createEntity("Cube");

	KamiEntityRenderSystem render;
	while (!glfwWindowShouldClose(KamiAppLayer::getInstance().m_glfwWindow.m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		render.renderEntity(cube);

		glfwSwapBuffers(KamiAppLayer::getInstance().m_glfwWindow.m_window);
		glfwPollEvents();
	}


	//TODO put this in a kami engine gl shutdown method
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	//SHOULD BE IN THE OPENGL COMPONENT OF THE ENTITY WHEN IT IS DESTROYED / REMOVED FROM SCENE TODO
	//glDeleteVertexArrays(1, &VAOID);
	//glDeleteBuffers(1, &VBOID);
	//glDeleteBuffers(1, &EBOID);

	//SHOULD BE PERFORMED BY MY RESSOURCE CACHE
	//glDeleteProgram(kamiShader.m_shaderProgramMap["program"]);
	//glDeleteShader(kamiShader.m_vertexShaderMap["..\\engine\\shader\\vertex.vert"]);
	//glDeleteShader(kamiShader.m_fragmentShaderMap["..\\engine\\shader\\fragment.frag"]);

	glfwTerminate();
	return 0;
}




//const float radius = 10.0f;
//float camX = sin(glfwGetTime()) * radius;
//float camZ = cos(glfwGetTime()) * radius;
//view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

////glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//int i = 0;
//for (auto cube : cubePositions) {
//	glm::mat4 model = glm::mat4(1.0f);
//	model = glm::translate(model, cube);
//	float angle = 20.0f * i;
//	i++;
//	model = glm::rotate(model, glm::radians((float)glfwGetTime() * i), glm::vec3(1.0f, 0.3f, 0.5f));
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//	glDrawArrays(GL_TRIANGLES, 0, 36);
//}