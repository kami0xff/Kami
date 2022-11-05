
//context is the current opengl state 
#include <engine/Engine.hpp>
#include <random/KamiRandom.hpp>
#include <iostream>


int main()
{
	KamiGlfwWindow KW;
	KW.init();
	KW.create();

	unsigned int VBOID;
	glGenBuffers(1, &VBOID);

	unsigned int VAOID;
	glGenVertexArrays(1, &VAOID);

	unsigned int EBOID;
	glGenBuffers(1, &EBOID);

	std::cout << std::filesystem::current_path() << std::endl;

	KamiShader kamiShader;
	kamiShader.createShaderProgram("program", "..\\..\\..\\..\\kamiEngine\\shader\\vertex.vert", "..\\..\\..\\..\\kamiEngine\\shader\\fragment.frag");

	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glBindVertexArray(VAOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(KamiShapePrimitive::g_cube), KamiShapePrimitive::g_cube, GL_STATIC_DRAW);


	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(KamiShapePrimitive::g_cube), KamiShapePrimitive::g_cube, GL_STATIC_DRAW);

	//would be cool to have a system to keep track of these 
	//i have the vao actually then i need a system that keeps track of the VAO and what object the VAO corresponds to 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //sets it for the current GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	//glEnableVertexAttribArray(2);

	//unbinding the buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create and generate texture
	KamiTexture containerTexture;
	containerTexture.readTexture("..\\..\\..\\..\\kami\\assets\\texture\\container.jpg"); //modifies object state
	containerTexture.createTexture();//3 below modify opengl state
	containerTexture.bindTexture(0);
	containerTexture.generateTexture();


	KamiTexture animeGirl;
	containerTexture.readTexture("..\\..\\..\\..\\kami\\assets\\texture\\wise.jpg"); //modifies object state
	containerTexture.createTexture();//3 below modify opengl state
	containerTexture.bindTexture(1);
	containerTexture.generateTexture();


	//model matrix
	glm::mat4 model = glm::mat4(1.0f);

	//view matrix
	glm::mat4 view = glm::mat4(1.0f);
	// note that we're translating the scene in the reverse direction of where we want to move
	view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

	//projection matrix 
	glm::mat4 projection;
	projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


	glUseProgram(kamiShader.m_shaderProgramMap["program"]);

	//texture units
	glUniform1i(glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "texture0"), 0);
	glUniform1i(glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "texture1"), 1);

	//unsigned int transformLoc = glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "transform");
	unsigned int modelLoc = glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "model");
	unsigned int viewLoc = glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "view");
	unsigned int projectionLoc = glGetUniformLocation(kamiShader.m_shaderProgramMap["program"], "projection");

	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));


	glBindVertexArray(VAOID);


	glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
	};


	int angle = 0;
	while (!glfwWindowShouldClose(KW.m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		view = glm::lookAt(glm::vec3(camX, 0.0, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		int i = 0;
		for (auto cube : cubePositions) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cube);
			float angle = 20.0f * i;
			i++;
			model = glm::rotate(model, glm::radians((float)glfwGetTime() * i), glm::vec3(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glfwSwapBuffers(KW.m_window);
		glfwPollEvents();
	}


	//TODO put this in a kami engine gl shutdown method
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAOID);
	glDeleteBuffers(1, &VBOID);
	glDeleteBuffers(1, &EBOID);
	glDeleteProgram(kamiShader.m_shaderProgramMap["program"]);
	glDeleteShader(kamiShader.m_vertexShaderMap["..\\engine\\shader\\vertex.vert"]);
	glDeleteShader(kamiShader.m_fragmentShaderMap["..\\engine\\shader\\fragment.frag"]);
	glfwTerminate();
	return 0;
}
