#include "stdafx.h"
#include "ShaderManager.h"
#include "ShadowlightEngine.h"
#include "VertexShader.h"
#include "GeometryShader.h"
#include "FragmentShader.h"
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
		// Switch for the right type
		switch (shad)
		{
		case GL_VERTEX_SHADER:
			i = shaders.Gen<VertexShader>();
			break;
		case GL_GEOMETRY_SHADER:
			i = shaders.Gen<GeometryShader>();
			break;
		case GL_FRAGMENT_SHADER:
			i = shaders.Gen<FragmentShader>();
			break;
		}

		// Generate the shader
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
				dynamic_cast<VertexShader*>(shader)->SetAttribute(itr->value.GetString(), atoi(itr->name.GetString()));
			}

			// Don't break, we need to check for transform feedback
		}
		case GL_GEOMETRY_SHADER:
		{
			// Let's load the xfb varyings
			// Check for them
			if (!doc.HasMember("xfbVaryings"))
			{
				// It's okay; some shaders can have no attributes
				// exit the loop
				break;
			}

			// Make sure that it's an object
			if (!doc["xfbVaryings"].IsArray())
			{
				// Raise an error; exit with -1
				RaiseError("Vertex/geometry shader lump %s has a non-array transform feedback varying list", in.name.data());
				return -1;
			}

			// Iterate over the xfbVaryings
			for (Value::ConstValueIterator itr = doc["xfbVaryings"].Begin();
				itr != doc["xfbVaryings"].End(); ++itr)
			{
				// Make sure that the value is a string
				if (!itr->IsString())
				{
					// Raise an error; exit with -1
					RaiseError("Vertex/geometry shader lump %s has a non-string transform feedback varying", in.name.data());
					return -1;
				}

				// Write the new attribute
				dynamic_cast<GeometryShader*>(shader)->SetXFBVarying(itr->GetString());
			}
			// Now we can break
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
				dynamic_cast<FragmentShader*>(shader)->SetColorAttachment(itr->value.GetString(), atoi(itr->name.GetString()));
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
	case LT_PROGRAM:
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

		// Make sure it has it's contents
		if (!doc.HasMember("link"))
		{
			// Raise an error, exit with -1
			RaiseError("Program lump %s does not have a list of links", in.name.data());
			return -1;
		}

		// Create an empty program
		int i = programs.Gen();
		Program* prog = programs.Get(i);
		Shader* shad;

		for (Value::ConstValueIterator itr = doc["link"].Begin();
			itr != doc["link"].End(); ++itr)
		{
			// Let's loop through and link all of the links
			// First, find the pointer to the Shader
			Lump* toLink = pEngine->lumpManager->FindLump(in, itr->GetString());

			// Make sure that we have a valid one
			if (!toLink)
			{
				// Otherwise, raise and exit
				RaiseError("Lump path %s does not exist", itr->GetString());
				return -1;
			}

			// Make sure that this shader is loaded before we try to link it
			pEngine->lumpManager->LoadLump(*toLink);

			// Let's grab the index of the Lump we're linking
			i = toLink->index;

			// Make sure that we have a valid index
			if (!(shad = shaders.Get(i)))
			{
				// If we don't, exit with an error
				RaiseError("Shader lump %s does not exist", toLink->name.data());
				return -1;
			}
			// Now, we can link it
			prog->Link(*shad);
		}
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