#include "stdafx.h"
#include "ShaderManager.h"
#include "ShadowlightEngine.h"
#include "JSON.h"

ShaderManager::ShaderManager()
{
	// We don't have to initialize anything;
	// the AssetArrays automatically set
	// themselves up
}

int ShaderManager::Create(const Lump& in)
{
	int i;
	Document doc;
	// Let's see what kind of lump we have here
	switch (in.contentType)
	{
	case LT_VERTEX_SHADER:
	case LT_FRAGMENT_SHADER:
	case LT_GEOMETRY_SHADER:
	{
		// Parse the metadata
		doc.Parse(in.metadata.data());

		// Check for a valid JSON object
		if (!doc.IsObject())
		{
			// Raise an error, exit with -1
			RaiseError("Lump %s\'s metadata is not a valid JSON object", in.name.data());
			return -1;
		}

		// Make sure it has a type
		if (!doc.HasMember("shaderType"))
		{
			// Raise an error, exit with -1
			RaiseError("Shader lump %s does not have a type", in.name.data());
			return -1;
		}

		// Attempt to read it's type
		const char* shaderType = doc["shaderType"].GetString();

		GLenum shad = GL_NONE;
		
		if (strcmp(shaderType, "vertex") == 0)
			shad = GL_VERTEX_SHADER;
		else if (strcmp(shaderType, "fragment") == 0)
			shad = GL_FRAGMENT_SHADER;
		else if (strcmp(shaderType, "geometry") == 0)
			shad = GL_GEOMETRY_SHADER;
		else
		{
			// Raise an error, exit with -1
			RaiseError("Shader lump %s has invalid type", in.name.data());
			return -1;
		}

		// Load the file directory that it's stored in

		// Make sure that it has one
		if (!doc.HasMember("file"))
		{
			// Raise an error, exit with -1
			RaiseError("Shader lump %s does not have a file name", in.name.data());
			return -1;
		}

		// Grab the file name
		const char* shaderFile = doc["file"].GetString();

		// Now that we have everything we need except for the shader-specific stuff, create and load the shader
		i = shaders.Gen();
		Shader* shader = shaders.Get(i);
		// Load the shader while checking for errors
		if (!shader->CreateShader(shaderFile, shad))
		{
			// Raise an error, exit with -1
			RaiseError("Failed to load shader lump %s", in.name.data());
			return -1;
		}

		// Set the shader-specific things
		switch(shad)
		{
		case GL_VERTEX_SHADER:
		{
			// This is a vertex shader
			// Let's load the attributes
			// Check for them
			if (!doc.HasMember("attributes"))
			{
				// It's okay; some shaders can have no attributes
				// exit the loop
				break;
			}

			// Make sure that it's an object
			if (!doc["attributes"].IsObject())
			{
				// Raise an error; exit with -1
				RaiseError("Vertex shader lump %s has a non-object attribute list", in.name.data());
				return -1;
			}

			// Iterate over the attributes
			for (Value::ConstMemberIterator itr = doc["attributes"].MemberBegin();
				itr != doc["attributes"].MemberEnd(); ++itr)
			{
				// All non-integer keys are passed into atoi().
				// atoi() converts non-integer strings into 0,
				// so you could overwrite the existing attribute at 0.

				// Make sure that the value is a string
				if (!itr->value.IsString())
				{
					// Raise an error; exit with -1
					RaiseError("Vertex shader lump %s has a non-string attribute", in.name.data());
					return -1;
				}

				// Write the new attribute
				shader->SetShaderAttribute(itr->value.GetString(), atoi(itr->name.GetString()));
			}

			// Exit the loop
			break;
		}
		case GL_FRAGMENT_SHADER:
		{
			// Let's find the output colors from this fragment shader
			// This is very similar to finding the attributes in the vertex shader
			// Check for them
			if (!doc.HasMember("colorAttachments"))
			{
				// It's okay; some shaders can have no color attachments or write to gl_FragColor or gl_FragData[]
				// exit the loop
				break;
			}

			// Make sure that it's an object
			if (!doc["colorAttachments"].IsObject())
			{
				// Raise an error; exit with -1
				RaiseError("Fragment shader lump %s has a non-object color attachments list", in.name.data());
				return -1;
			}

			// Iterate over the attachments
			for (Value::ConstMemberIterator itr = doc["colorAttachments"].MemberBegin();
				itr != doc["colorAttachments"].MemberEnd(); ++itr)
			{
				// All non-integer keys are passed into atoi().
				// atoi() converts non-integer strings into 0,
				// so you could overwrite the existing attribute at 0 
				// if it's not a valid integer string.
				// * * * BE CAREFUL * * *

				// Make sure that the value is a string
				if (!itr->value.IsString())
				{
					// Raise an error; exit with -1
					RaiseError("Fragment shader lump %s has a non-string attribute", in.name.data());
					return -1;
				}

				// Write the color attachment
				shader->SetColorAttachment(itr->value.GetString(), atoi(itr->name.GetString()));
			}

			// Exit the loop
			break;
		}
		// It it's a geometry shader,
		// we don't need to do anything special.
		// Just break
		default:break;
		}

		// Now we have a shader!
		break;
	}
	default:
	{
		// Invalid shader type
		// Return an error code
		return -1;
	}
	}
	// We've successfully generated a shader/program!
	// Exit with the new index
	return i;
}

void ShaderManager::Cleanup()
{
	// We don't need to do anything except for clean up the AssetArrays
	shaders.~AssetArray();
	programs.~AssetArray();
}

ShaderManager::~ShaderManager()
{
	Cleanup();
}
