
//context is the current opengl state 
#include <engine/Engine.hpp>
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


	//kamiShader.createShaderProgram("program","..\\engine\\shader\\vertex.vs","..\\engine\\shader\\fragment.fs");
	//the above version with the realtive paths did not work

	KamiShader kamiShader;
	kamiShader.createShaderProgram("program", "C:\\Dev\\C++_CMAKE_Learning\\engine\\shader\\vertex.vert", "C:\\Dev\\C++_CMAKE_Learning\\engine\\shader\\fragment.frag");


	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glBindVertexArray(VAOID);
	glBindBuffer(GL_ARRAY_BUFFER, VBOID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(KamiShapePrimitive::g_containerQuad), KamiShapePrimitive::g_containerQuad, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(KamiShapePrimitive::g_rectangleIndices), KamiShapePrimitive::g_rectangleIndices, GL_STATIC_DRAW);

	//would be cool to have a system to keep track of these 
	//i have the vao actually then i need a system that keeps track of the VAO and what object the VAO corresponds to 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //sets it for the current GL_ARRAY_BUFFER
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//unbinding the buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//create and generate texture
	KamiTexture containerTexture;
	containerTexture.readContainerTexture();
	containerTexture.createTexture();
	containerTexture.bindTexture();
	containerTexture.generateTexture();

	glUseProgram(kamiShader.m_shaderProgramMap["program"]);
	glBindTexture(GL_TEXTURE_2D, containerTexture.m_id);
	glBindVertexArray(VAOID);




	while (!glfwWindowShouldClose(KW.m_window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgramId, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		
		
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
	glDeleteShader(kamiShader.m_vertexShaderMap["C:\\Dev\\C++_CMAKE_Learning\\engine\\shader\\vertex.vert"]);
	glDeleteShader(kamiShader.m_fragmentShaderMap["C:\\Dev\\C++_CMAKE_Learning\\engine\\shader\\fragment.frag"]);
	glfwTerminate();
	return 0;
}
