#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdio.h>

int main()
{
	if(!glfwInit())
	{
		printf("Mega F\n");
		return 0;
	}
	printf("Good shit\n");
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", NULL, NULL);
	if(!window)
	{
		printf("F window\n");
		glfwTerminate();
		return 0;
	}

	unsigned int extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	printf("%u extensions supported\n", extensionCount);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}