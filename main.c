#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct Renderer {
	GLFWwindow* window;
	VkInstance instance;		
}Renderer;

int InitVulkan(VkInstance* instance){

	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Hellow triangle";
	appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
	appInfo.pEngineName = "VEngine";
	appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	//checking that the required extensions by glfw are present
	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	unsigned int extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, NULL);
	VkExtensionProperties* extensionProperties = (VkExtensionProperties*)malloc(sizeof(VkExtensionProperties)*extensionCount);
	vkEnumerateInstanceExtensionProperties(NULL, &extensionCount, extensionProperties);
	for(int i = 0; i<glfwExtensionCount; ++i)
	{
		for(int j = 0; j<extensionCount; ++j)
		{	if (strcmp(glfwExtensions[i], extensionProperties[j].extensionName) == 0)
			{
				printf("GLFW Required vulkan extension %s found\n", glfwExtensions[i]);
				break;
			}
			if(j == (extensionCount-1))
			{
				printf("ERROR: GLFW Required vulkan extension not %s found\n", glfwExtensions[i]);
				free(extensionProperties);
				return 0;
			}
		}
	}
	free(extensionProperties);
#ifndef NDEBUG
	const char* neededLayer = "VK_LAYER_KHRONOS_validation";
	unsigned int layerPropCount = 0;
	vkEnumerateInstanceLayerProperties(&layerPropCount, NULL);
	VkLayerProperties* layerProperties = (VkLayerProperties*)malloc(sizeof(VkLayerProperties)*layerPropCount);
	vkEnumerateInstanceLayerProperties(&layerPropCount, layerProperties);
	for(int i = 0; i < layerPropCount; ++i)
	{
		printf("%s\n", layerProperties[i].layerName);
		if(strcmp(neededLayer, layerProperties[i].layerName) == 0)
			break;
		if(i == (layerPropCount - 1))
		{
			printf("ERROR: Required vulkan validation layer %s not found\n", neededLayer);
				free(layerProperties);
				return 0;
		}
			
	}
	free(layerProperties);
#endif

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;
	createInfo.enabledExtensionCount = glfwExtensionCount;
	createInfo.ppEnabledExtensionNames = glfwExtensions;
#ifdef NDEBUG
	createInfo.enabledLayerCount = 0;
#else
	createInfo.enabledLayerCount = layerPropCount;
	createInfo.ppEnabledLayerNames = &neededLayer;
#endif

	if (vkCreateInstance(&createInfo, NULL, instance) != VK_SUCCESS)
	{
		printf("Error creating the vulkan instance\n");
		return 0;
	}
	return 1;
}

void CleanUp(Renderer* renderer)
{
	glfwDestroyWindow(renderer->window);
	vkDestroyInstance(renderer->instance, NULL);
	free(renderer);
	glfwTerminate();
}

int main()
{
	if(!glfwInit())
	{
		printf("Mega F\n");
		return 0;
	}
	printf("Good shit\n");
	
	Renderer* renderer = (Renderer*)malloc(sizeof(Renderer));
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	renderer->window = glfwCreateWindow(WIDTH, HEIGHT, "Vulkan window", NULL, NULL);
	if(!renderer->window)
	{
		printf("F window\n");
		free(renderer);
		glfwTerminate();
		return 0;
	}
	
	if (!InitVulkan(&renderer->instance))
	{
		CleanUp(renderer);
		return 0;
	}
	
	while(!glfwWindowShouldClose(renderer->window))
	{
		glfwPollEvents();
	}
	CleanUp(renderer);
	return 0;
}