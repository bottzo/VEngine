#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>

#define WIDTH 800
#define HEIGHT 600

void InitVulkan(){

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hellow triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
	appInfo.pEngineName = "VEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
	createInfo.enabledLayerCount = 0;

	unsigned int extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	printf("%u extensions supported\n", extensionCount);
	VkExtensionProperties* properties = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties)*extensionCount);
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, properties);
	for (int i = 0; i < extensionCount; ++i)
		printf("%s\n", properties[i].extensionName);
	free(properties);

	VkInstance instance;
	if (vkCreateInstance(&createInfo, NULL, &instance) != VK_SUCCESS)
		printf("Error creating the vulkan instance\n");
}

int main()
{
	if(!glfwInit())
	{
		printf("Mega F\n");
		return 0;
	}
	printf("Good shit\n");
	
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", NULL, NULL);
	if(!window)
	{
		printf("F window\n");
		glfwTerminate();
		return 0;
	}
	
	InitVulkan();
	
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}