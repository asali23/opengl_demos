#include "model.h"

Model::Model()
{
    nVertices = 0;
}

Model::~Model()
{
	delete[] coordinates;
	delete[] textureCoordinates;
}

void Model::initializeVertices(unsigned int numberOfVertices)
{
    nVertices = numberOfVertices;
    coordinates = new glm::vec3[nVertices];
	textureCoordinates = new glm::vec2[nVertices];
}

void Model::setVertexCoordinates(unsigned int n, glm::vec3 value)
{
    if (nVertices > 0 && n < nVertices)
        coordinates[n] = value;
}

void Model::setVertexTextureCoordinates(unsigned int n, glm::vec2 value)
{
	if (nVertices > 0 && n < nVertices)
        textureCoordinates[n] = value;
}

void Model::loadModelFromOBJFile(const char* filePath)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;
	
	std::ifstream fileStream(filePath, std::ios::in);
	if(fileStream.is_open())
	{
		std::string line = "";
		while(getline(fileStream, line))
		{
			if (line[0] == 'v' && line[1] == ' ')
			{
				glm::vec3 v;
				sscanf(line.c_str(), "v %f %f %f", &v.x, &v.y, &v.z);
				temp_vertices.push_back(v);
			}
			else if (line[0] == 'v' && line[1] == 't')
			{
				glm::vec2 uv;
				sscanf(line.c_str(), "vt %f %f", &uv.x, &uv.y);
				temp_uvs.push_back(uv);
			}
			else if (line[0] == 'v' && line[1] == 'n')
			{
				glm::vec3 n;
				sscanf(line.c_str(), "vn %f %f %f", &n.x, &n.y, &n.z);
				temp_normals.push_back(n);
			}
			else if (line[0] == 'f' && line[1] == ' ')
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
		}
		fileStream.close();
		
		unsigned int n = vertexIndices.size();
		initializeVertices(n);
		for (unsigned int i=0; i < n; i++)
		{
			coordinates[i] = temp_vertices[vertexIndices[i] - 1];
			textureCoordinates[i] = temp_uvs[uvIndices[i] - 1];
		}
	}
	else
		std::cerr<<"Could not open "<<filePath<<std::endl;
}

void Model::setTextureImage(const char* filePath)
{
	textureImage = new TextureImage(filePath);
}

glm::vec3 *Model::getVertexCoordinatesArray()
{
    return coordinates;
}

glm::vec2 *Model::getVertexTextureCoordinatesArray()
{
	return textureCoordinates;
}

TextureImage *Model::getTextureImage()
{
	return textureImage;
}

unsigned int Model::getVertexCount()
{
    return nVertices;
}
