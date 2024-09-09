#pragma once

#include <vector>
#include <iostream>
#include <chrono>

#include <glad/glad.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

#include "Shaders/Shader.h"
#include "Mesh.h"
#include "RenderEngine/Loader.h"

namespace OG3D
{
	// Function identifier
	unsigned int LoadTextureFromFile(const char* name, const std::string& directory);

	class Model
	{
	public:
		Model(const char* path)
		{
			LoadModel(path);
		}

		void Draw(Shader& shader)
		{
			for (unsigned int i = 0; i < meshes.size(); i++)
				meshes[i].Draw(shader);
		}

	private:
		std::vector<Texture> textures_loaded;
		std::vector<Mesh> meshes;
		std::string directory;

		void LoadModel(std::string path)
		{
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
			{
				std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() <<"\n";
				return;
			}

			directory = path.substr(0, path.find_last_of('/'));

			ProcessNode(scene->mRootNode, scene);
		}

		void ProcessNode(aiNode* node, const aiScene* scene)
		{
			for (unsigned int i = 0; i < node->mNumMeshes; i++)
			{
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				meshes.push_back(ProcessMesh(mesh, scene));
			}

			for (unsigned int i = 0; i < node->mNumChildren; i++)
			{
				ProcessNode(node->mChildren[i], scene);
			}
		}

		Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene)
		{
			std::vector<Vertex> vertices;
			std::vector<unsigned int> indices;
			std::vector<Texture> textures;

			// Process Vertices
			for (unsigned int i = 0; i < mesh->mNumVertices; i++)
			{
				Vertex vertex;
				// Position
				glm::vec3 vector;
				vector.x = mesh->mVertices[i].x;
				vector.y = mesh->mVertices[i].y;
				vector.z = mesh->mVertices[i].z;
				vertex.Position = vector;
				// Normal
				vector.x = mesh->mNormals[i].x;
				vector.y = mesh->mNormals[i].y;
				vector.z = mesh->mNormals[i].z;
				vertex.Normal = vector;
				// Texture Coordinates
				if (mesh->mTextureCoords[0])
				{
					glm::vec2 texCoords;
					texCoords.x = mesh->mTextureCoords[0][i].x;
					texCoords.y = mesh->mTextureCoords[0][i].y;
					vertex.TexCoords = texCoords;
				}
				else vertex.TexCoords = glm::vec2(0.0f, 0.0f);

				vertices.push_back(vertex);
			}

			// Process indices
			for (unsigned int i = 0; i < mesh->mNumFaces; i++)
			{
				aiFace face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++)
					indices.push_back(face.mIndices[j]);
			}

			// Process Materials
			if (mesh->mMaterialIndex >= 0)
			{

				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

				std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
				textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

				std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
				textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
			}

			return Mesh(vertices, indices, textures);
		}

		std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, const char* typeName)
		{
			std::vector<Texture> textures;
			for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
			{
				aiString str;
				mat->GetTexture(type, i, &str);

				bool skip = false;
				for (unsigned int j = 0; j < textures_loaded.size(); j++)
				{
					if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
					{
						textures.push_back(textures_loaded[j]);
						skip = true;
						break;
					}
				}
				if (!skip)
				{
					Texture texture;
					texture.ID = LoadTextureFromFile(str.C_Str(), directory.c_str());
					texture.type = typeName;
					texture.path = str.C_Str();
					textures_loaded.push_back(texture);
				}	
			}
			return textures;
		}
	};

	// Utility function to load texture from file
	// ------------------------------------------
	unsigned int LoadTextureFromFile(const char* name, const std::string& directory)
	{
		std::string filename = name;
		filename = directory + '/' + filename;

		unsigned int textureID;
		glGenTextures(1, &textureID);

		int width, height, nrComponents;

		auto start = std::chrono::high_resolution_clock::now();
		unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);

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

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		}
		else
		{
			std::cout << "ERROR:: Texture failed to load at path: " << filename << std::endl;
		}
		stbi_image_free(data);

		return textureID;
	}
}