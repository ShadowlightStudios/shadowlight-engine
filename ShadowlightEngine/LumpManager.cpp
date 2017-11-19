#include "stdafx.h"
#include "LumpManager.h"

// This function loads a lump file and enters all of the lumps into it
void LumpManager::LoadLumpFile(string filename)
{
	FILE* f;
	// Open the file
	f = fopen(filename.data(), "rb");

	// If the file open failed
	if (f == 0)
	{
		// Raise an error and exit
		RaiseError("Failed to load file %s", filename.data());
		return;
	}

	Lump newLump;
	char ch;

	ch = 0;

	// Now, let's load some lumps!!!

	while (true)
	{
		// Start with an unnamed lump
		newLump.name = "";

		// Find the lump's name
		while (true)
		{
			// Read a character
			ch = fgetc(f);

			// Append it to the lump name
			if (ch != '\0' && ch != EOF)
			{
				printf("%c", ch);
				newLump.name += ch;
			}
			// But if it's a null or EOF, break
			else
			{
				break;
			}
		}

		// Now: if this string has length 0
		// (An empty string, or a solitary '\0' in the file)
		// We're going to pop up one level in the lump
		// tree

		if (newLump.name.length() == 0)
		{
			// TO BE CONTINUED . . .
		}

		printf("\n");
		
		// Check for EOF and if there is, exit the loop
		if (ch == EOF)
			break;

		// Now, we have the lump's name

		// Let's read the contentType:
		fread((void*)&newLump.contentType, sizeof(uint16_t), 1, f);

		printf("%d %04x\n", (signed int) newLump.contentType, newLump.contentType);

		// Now, let's read the JSON-formatted metadata
		
		newLump.metadata = "";

		while (true)
		{
			// Read a character
			ch = fgetc(f);

			// Append it to the lump name
			if (ch != '\0' && ch != EOF)
			{
				printf("%c", ch);
				newLump.metadata += ch;
			}
			// But if it's a null or EOF, break
			else
			{
				break;
			}
		}

		printf("\n");

		// Check for EOF and if there is, exit the loop
		if (ch == EOF)
			break;

		// Set loaded and index to blank
		newLump.index = -1;
		newLump.loaded = false;

		// Now we have our loaded lump!
		// Finally, enter into the tree.
		EnterLump(&newLump);

		break;
	}

	// Close the file and exit
	fclose(f);
	return;
}

// Just exits; nothing to do
void LumpManager::Cleanup()
{
	return;
}

Manager* LumpManager::ManagerFromLumpType(const Lump& in)
{
	// Let's do a switch on the type to get the right manager for it
	switch (in.contentType)
	{
	case LT_EMPTY:
		return NULL;
	case LT_VERTEX_SHADER:
	case LT_FRAGMENT_SHADER:
	case LT_GEOMETRY_SHADER:
	case LT_PROGRAM:
		return pEngine->shaderManager;
	case LT_UNIFORM:
	{
		printf("Uniform list");
		break;
	}
	case LT_VERTEX_ARRAY:
	{
		printf("Vertex array");
		break;
	}
	case LT_TEXTURE_1D:
	case LT_TEXTURE_1D_ARRAY:
	case LT_TEXTURE_2D:
	case LT_TEXTURE_2D_ARRAY:
	case LT_TEXTURE_2D_MULTISAMPLE:
	case LT_TEXTURE_2D_MULTISAMPLE_ARRAY:
	case LT_TEXTURE_3D:
	case LT_TEXTURE_CUBE:
	case LT_TEXTURE_CUBE_ARRAY:
	case LT_TEXTURE_RECT:
		return pEngine->textureManager;
	case LT_SOUND:
	case LT_MUSIC_OGG:
	case LT_MUSIC_MP3:
		return pEngine->soundManager;
	case LT_TEXT:
	case LT_INPUT_BINDINGS:
	case LT_MAP:
	case LT_TRANSFORM_FEEDBACK_BUFFER:
	default:
	{
		RaiseError("Unrecognized lump type in lump %s", in.name.data());
		break;
	}
	}
	return NULL;
}

// Simply cleanup
LumpManager::~LumpManager()
{
	Cleanup();
}
