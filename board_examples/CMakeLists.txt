cmake_minimum_required(VERSION 2.6)

project("all")

file(GLOB projects "." "*")

foreach (project ${projects})
	if (EXISTS ${project}/CMakelists.txt)
		add_subdirectory(${project})
	endif()
endforeach()
