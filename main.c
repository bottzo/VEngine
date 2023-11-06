#include <stdio.h>
#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

int main()
{
	if(!glfwInit())
	{
		printf("Mega F");
		return 0;
	}
	printf("Good shit");
	GLFWwindow* window = glfwCreateWindow(640, 480, "MyTitle", NULL, NULL);
	if(!window)
	{
		printf("F window");
		glfwTerminate();
		return 0;
	}
	while(!glfwWindowShouldClose(window))
	{
	}
	glfwTerminate();
	return 0;
}