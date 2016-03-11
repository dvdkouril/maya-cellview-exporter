#include "MolecularExporter.h"
#include <iostream>
#include <maya/MItDag.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MFnTransform.h>
#include <maya/MVector.h>
#include<maya/MQuaternion.h>

/*
	Constructor
*/
MolecularExporter::MolecularExporter(char * filePath) {
	this->filePath = filePath;
}

/*
	Function accesses scene's DAG hierarchy and iterates through all the objects
*/
void MolecularExporter::exportScene() 
{
	std::cout << "\n" << std::endl;
	std::cout << "Exporting scene..." << std::endl;

	// open file for writing
	outputFile.open(this->filePath);
	if (!outputFile) {
		std::cout << "Error: file couldn't be opened." << std::endl;
		return;
	}

	MItDag itTran = MItDag(MItDag::kDepthFirst,/*MFn::kInvalid*/ MFn::kTransform);
	for (; !itTran.isDone(); itTran.next()) 
	{
		// fetch the current object
		MObject item = itTran.currentItem();

		// process the current object
		this->processObject(item);
	}

	// we are done writing objects data into the file
	outputFile.close();
}

/*
	Function processes a single scene object - gets it's name, translation and rotation (TODO) and outputs this data into an output file (and console)
*/
void MolecularExporter::processObject(MObject obj) 
{
	MStatus status;

	// getting the name from the object
	MFnDependencyNode nodeFn(obj);
	MString nodeName = nodeFn.name();
	
	// skip camera transformations
	if ((!strcmp(nodeName.asChar(), "persp")) ||
		(!strcmp(nodeName.asChar(), "top")) || 
		(!strcmp(nodeName.asChar(), "front")) || 
		(!strcmp(nodeName.asChar(), "side"))) {
		return;
	}

	MFnTransform fn(obj, &status);
	CHECK_MSTATUS(status);

	// translation
	MVector translation = fn.getTranslation(MSpace::kObject);

	// rotation
	MQuaternion rotation(0,0,0,1);
	fn.getRotation(rotation);

	// output info about this processed object
	/* TODO
		- make output to file binary
		- output animation (= output all frames)
		- output object/molecule type
	*/
	std::cout << nodeName.asChar() << std::endl;
	std::cout << "Translation: " << translation.x << ", " << translation.y << ", " << translation.z << std::endl;

	outputFile << "[" << translation.x << " " << translation.y << " " << translation.z << "]";
	outputFile << "[" << rotation.x << " " << rotation.y << " " << rotation.z << "]" << std::endl;
}