#include <GLCore.h>

#include "Player.h"

#include <GUI\imgui.h>
#include <GUI\imgui_impl_glfw.h>
#include <GUI\imgui_impl_opengl3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window, bool & freeCamOn);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadTexture(char const* path);
unsigned int loadCubemap(std::vector<std::string> faces);
GLFWwindow* initOpenGL();

bool procMouse = true;

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 700;

// camera
Camera camera(glm::vec3(0.0f, 2.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool freeCamOn = false;

Player player(camera);

// timing
float deltaTime = 0.0f; // time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
	GLFWwindow* window = initOpenGL();


	
	float skyboxVertices[] = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	Shader skyboxShader("shaders/skybox.vs", "shaders/skybox.fs");
	Shader lampShader("shaders/2.1.lamp.vs", "shaders/2.1.lamp.fs");


	std::vector<std::string> faces
	{
		/*"textures/skybox/right.jpg",
		"textures/skybox/left.jpg",
		"textures/skybox/top.jpg",
		"textures/skybox/bottom.jpg",
		"textures/skybox/front.jpg",
		"textures/skybox/back.jpg"*/

		"textures/skybox2/right.jpg",
		"textures/skybox2/left.jpg",
		"textures/skybox2/top.jpg",
		"textures/skybox2/bottom.jpg",
		"textures/skybox2/front.jpg",
		"textures/skybox2/back.jpg"
	};

	// skybox VAO
	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	unsigned int cubemapTexture = loadCubemap(faces);
	Renderer renderer = Renderer();
	World world = World(2);
	player.set_world(world);

	//---------------------------------------------
	// load textures (we now use a utility function to keep the code more organized)
	// -----------------------------------------------------------------------------
	int diffuseMap = loadTexture("textures/textures.png");
	int specularMap = loadTexture("textures/textures_specular.png");

	renderer.getShader().setInt("material.diffuse", 0);

	renderer.getShader().setInt("material.specular", 1);
	
	//---SOL---
	//---------
	//
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};
	// second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
	unsigned int lightVAO, lightVBO;
	glGenVertexArrays(1, &lightVAO);
	glGenBuffers(1, &lightVBO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);

	// we only need to bind to the VBO (to link it with glVertexAttribPointer), no need to fill it; the VBO's data already contains all we need (it's already bound, but we do it again for educational purposes)
	//nao e necessario pk ira ser o mesmo e este ja esta binded (acima)

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glm::vec3 sunPos(0.0, 5.0, 0.0);
	
	std::vector<Chunk> chunks = world.getChunks();
	const int from = -3, to = 3;

	for (auto && chunk : chunks)
	{
		const ChunkMesh* temp_mesh = new ChunkMesh(chunk.getMesh());
		renderer.r_chunks.push_back(temp_mesh);
	}

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);


	//GUI
	//----
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsClassic();

	// Setup Platform/Renderer bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 130");

	// Our state
	bool show_demo_window = true;
	bool show_sun_window = false;
	bool show_directional_light_window = false;
	bool show_flash_light_window = false;
	
	float scaleGUI[4] = { 5.0f, 5.0f, 5.0f, 1.0f };
	glm::vec3 scale(5.0f);

	ImVec4 lightColorGUI = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightColor = glm::vec3(1.0f);

	float specularStrength = 0.5f;
	float shininess = 32.0f;

	float lightSpeed = 1.0f;
	bool sunRotate = true;
	float lighStrenght = 100;

	ImVec4 dirLightColorGUI = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	float dirLighStrenght = 0.2f;

	glm::vec3 dirLightColor(1.0);


	ImVec4 flashLightColorGUI = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 flashLightColor(1.0);
	
	float flashLighStrenght = 0.5;
	float spotCutoff = 12.5f;
	
	// Lights
	//------------
	glm::vec3 ambientColor = lightColor * glm::vec3(0.05f);
	glm::vec3 diffuseColor = lightColor * glm::vec3(0.8f);
	glm::vec3 specularColor = glm::vec3(1.0f);
	float constantColor = 1.0f;
	float linearColor = 0.9;
	float quadraticColor = 0.032;
	
	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		// per-frame time logic
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//GUI
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		
		// input
		processInput(window,freeCamOn);

		// render
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		if (!freeCamOn) {
			player.update(deltaTime);
		}

		// be sure to activate shader when setting uniforms/drawing objects
		renderer.getShader().use();
		renderer.getShader().setVec3("viewPos", camera.Position);
		renderer.getShader().setFloat("material.shininess", shininess);



		// directional light
		renderer.getShader().setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
		renderer.getShader().setVec3("dirLight.ambient", dirLightColor * 0.05f);
		renderer.getShader().setVec3("dirLight.diffuse", diffuseColor * dirLighStrenght);
		renderer.getShader().setVec3("dirLight.specular", specularColor * dirLighStrenght);
		// point light 1
		renderer.getShader().setVec3("pointLights[0].position", sunPos);
		renderer.getShader().setVec3("pointLights[0].ambient", ambientColor);
		renderer.getShader().setVec3("pointLights[0].diffuse", lightColor * lighStrenght);
		renderer.getShader().setVec3("pointLights[0].specular", specularColor * specularStrength);
		renderer.getShader().setFloat("pointLights[0].constant", constantColor);
		renderer.getShader().setFloat("pointLights[0].linear", linearColor);
		renderer.getShader().setFloat("pointLights[0].quadratic", quadraticColor);
		// spotLight6
		renderer.getShader().setVec3("spotLight.position", camera.Position);
		renderer.getShader().setVec3("spotLight.direction", camera.Front);
		renderer.getShader().setVec3("spotLight.ambient", flashLightColor);
		renderer.getShader().setFloat("spotLight.cutOff", glm::cos(glm::radians(spotCutoff)));
		renderer.getShader().setFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotCutoff + 3.0)));
		renderer.getShader().setVec3("spotLight.diffuse", diffuseColor);
		renderer.getShader().setVec3("spotLight.specular", specularColor);
		renderer.getShader().setFloat("spotLight.constant", constantColor);
		renderer.getShader().setFloat("spotLight.linear", linearColor * flashLighStrenght);
		renderer.getShader().setFloat("spotLight.quadratic", quadraticColor);

		
		// Get MVP
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 model = glm::mat4(1.0f);

		// bind diffuse map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseMap);
		// bind specular map
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, specularMap);

		renderer.setMatrix(projection,view,model);
		renderer.render(camera);

		lampShader.use();
		lampShader.setMat4("view", view);
		lampShader.setMat4("projection", projection);
		lampShader.setVec3("lightColor", lightColor);

		//---Posicionamento da luz---
		model = glm::mat4(1.0f);
		//---Rotação da luz---
		if(lightSpeed != 0.0f)
		{
			sunPos.x = 50.0f * (sin(glfwGetTime() * glm::radians(lightSpeed * 75.0)));
			sunPos.y = 50.0f * (cos(glfwGetTime() * glm::radians(lightSpeed * 75.0)));
			sunPos.z = 0;
		}
		model = glm::translate(model, sunPos);
		if (sunRotate){
			model = glm::rotate(model, (float) (glfwGetTime() * glm::radians(75.0)), glm::vec3(0, 0, -1));
		}
		model = glm::scale(model, scale);
		lampShader.setMat4("model", model);

		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
		// draw skybox as last
		glDepthFunc(GL_LEQUAL);  // change depth function so depth test passes when values are equal to depth buffer's content
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
		skyboxShader.setMat4("projection", projection);
		skyboxShader.setMat4("view", view);

		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default





		//---GUI Window---
		//----------------
		float lightPosGUI[4] = { sunPos.x, sunPos.y, sunPos.z,1.0f };

		if (show_demo_window)
			// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
		{

			ImGui::Begin("General Painel");                          // Create a window called "Painel" and append into it.
			ImGui::Text("Windows are resizable be shure to see every option");
			ImGui::Text("Press ALT to interact with this window");
			ImGui::Text("Press F to enable wireframe (G to disable)");
			ImGui::Text("Press U to enable fly mode");
			ImGui::Text("mouse weel to zoom in/out");
			ImGui::Checkbox("Sun", &show_sun_window);
			ImGui::Checkbox("Directional Light", &show_directional_light_window);
			ImGui::Checkbox("Flashlight", &show_flash_light_window);
		
			ImGui::SliderFloat("Specular strength", &specularStrength, 0.0f, 2.0f);
			ImGui::SliderFloat("Shininess", &shininess, 2.0f, 256.0f);

			if (ImGui::Button("Reset")) {							// Buttons return true when clicked (most widgets return true when edited/activated)
				lightColor = glm::vec3(1.0f);
				ambientColor = lightColor * glm::vec3(0.05f);
				diffuseColor = lightColor * glm::vec3(0.8f);
				specularColor = glm::vec3(1.0f);
				constantColor = 1.0f;
				linearColor = 0.9;
				quadraticColor = 0.032;
				lightSpeed = 1.0f;
				sunRotate = true;
				lighStrenght = 100;
				dirLightColorGUI = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				dirLighStrenght = 0.2f;
				flashLightColorGUI = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
				flashLighStrenght = 0.5f;
				spotCutoff = 12.5;
			}
			//ImGui::SameLine();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}

		if (show_sun_window)
		{
			ImGui::Begin("Sun", &show_sun_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

			ImGui::SliderFloat3("Object scale", scaleGUI, 0.0f, 2.0f);
			ImGui::SliderFloat3("Light Position", lightPosGUI, -100, 100);
			ImGui::ColorEdit3("Light color", (float*)&lightColorGUI); // Edit 3 floats representing a color
			ImGui::SliderFloat("Light Speed", &lightSpeed, 0.0f, 10.0f);
			ImGui::SliderFloat("Light Strenght", &lighStrenght, 0.0f, 200.0f);
			ImGui::Checkbox("Sun Rotation", &sunRotate);

			ImGui::End();
		}

		if (show_directional_light_window)
		{
			ImGui::Begin("Directional Light", &show_directional_light_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

			ImGui::ColorEdit3("Light color", (float*)&dirLightColorGUI); // Edit 3 floats representing a color
			ImGui::SliderFloat("Light Strenght", &dirLighStrenght, 0.0f, 10.0f);

			ImGui::End();
		}

		if (show_flash_light_window)
		{
			ImGui::Begin("Flashlight", &show_flash_light_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)

			ImGui::ColorEdit3("Light color", (float*)&flashLightColorGUI); // Edit 3 floats representing a color
			ImGui::SliderFloat("Light Strenght", &flashLighStrenght, -0.255f, 1.0f);
			ImGui::SliderFloat("spotlight cutoff", &spotCutoff, 0.0f, 25.0f);

			ImGui::End();
		}
		
		//traduçao do IMGUI para gl
		scale = glm::vec3(scaleGUI[0], scaleGUI[1], scaleGUI[2]);
		sunPos = glm::vec3(lightPosGUI[0], lightPosGUI[1], lightPosGUI[2]);
		lightColor = glm::vec4(lightColorGUI.x, lightColorGUI.y, lightColorGUI.z, lightColorGUI.w);
		dirLightColor = glm::vec4(dirLightColorGUI.x, dirLightColorGUI.y, dirLightColorGUI.z, dirLightColorGUI.w);
		flashLightColor = glm::vec4(flashLightColorGUI.x, flashLightColorGUI.y, flashLightColorGUI.z, flashLightColorGUI.w);
		
		// Rendering----GUI----
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window, bool & freeCamOn)
{
	std::cout << "freeCam: " << freeCamOn << "\n";

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		procMouse = false;
	}
	else {
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		procMouse = true;
	}
	
	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
		if (freeCamOn) {
			freeCamOn = false;
		}
		else {
			freeCamOn = true;
		}
	}
	if (freeCamOn) {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera.ProcessKeyboard(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera.ProcessKeyboard(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera.ProcessKeyboard(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera.ProcessKeyboard(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			camera.ProcessKeyboard(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			camera.ProcessKeyboard(DOWN, deltaTime);
	}
	else {
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			player.move(FORWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			player.move(BACKWARD, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			player.move(LEFT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			player.move(RIGHT, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
			player.move(UP, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (procMouse) {

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos;

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	// load image, create texture and generate 
	int width, height, nrComponents;
	unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		// set the texture wrapping parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		// set texture filtering parameters
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}

GLFWwindow* initOpenGL() {
	//************************** CONTEXT **********************************
	// glfw: initialize and configure
	glfwInit();
	glfwWindowHint(GLFW_SAMPLES, 4); // anti-aliasing factor
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); //resizable window = false
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // use modern openGL

	// Open a window and create its OpenGL context
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "MiNaScRaFt", NULL, NULL);

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// Initialize GLEW
	glewInit();

	return window;
}